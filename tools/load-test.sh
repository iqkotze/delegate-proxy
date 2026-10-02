#!/usr/bin/env bash
# Measures throughput and latency of delegated with wrk as forward, reverse and TLS terminating proxy.
# Usage: tools/load-test.sh [-c "100 500 1200"] [-d seconds] [-T wrk-timeout-seconds] [-v "forward reverse tls"] [-o file] [--check] <delegated> [delegated args]
set -uo pipefail

here=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
. "$here/../tests/tls/lib.sh"

conns="100 500 1200"
duration=15
timeout=30
variants="forward reverse tls"
outfile=
check=0
while [ $# -gt 0 ]; do
	case $1 in
	-c) conns=$2; shift 2 ;;
	-d) duration=$2; shift 2 ;;
	-T) timeout=$2; shift 2 ;;
	-v) variants=$2; shift 2 ;;
	-o) outfile=$2; shift 2 ;;
	--check) check=1; shift ;;
	-*) echo "unknown option: $1" >&2; exit 2 ;;
	*) break ;;
	esac
done
[ $# -ge 1 ] || { echo "usage: load-test.sh [-c conns] [-d seconds] [-T seconds] [-v variants] [-o file] [--check] <delegated> [delegated args]" >&2; exit 2; }
command -v wrk >/dev/null || { echo "SKIP wrk not found (apt-get install wrk)"; exit 77; }
command -v python3 >/dev/null || { echo "SKIP python3 not found"; exit 77; }
bin=$1
shift
dgargs=("$@")

hard=$(ulimit -H -n)
ulimit -n "$hard" 2>/dev/null || true
tls_setup "$bin" 0

# Converts a wrk time such as 850.20us, 12.5ms or 1.2s to milliseconds.
to_ms() {
	awk -v v="$1" 'BEGIN {
		n = v + 0
		if (v ~ /us$/) n /= 1000; else if (v ~ /ms$/) n = n; else if (v ~ /s$/) n *= 1000
		printf "%.2f", n
	}'
}

# Writes the highest number of established connections to the port into the file, sampled every 0.5 s.
sample_peak() {
	local port=$1 file=$2 cur max=0 hex tables=(/proc/net/tcp)
	hex=$(printf ':%04X' "$port")
	[ -r /proc/net/tcp6 ] && tables+=(/proc/net/tcp6)
	while :; do
		cur=$(awk -v h="$hex" '$4 == "01" && $2 ~ h"$" { n++ } END { print n + 0 }' "${tables[@]}")
		[ "$cur" -le "$max" ] || max=$cur
		echo "$max" >"$file"
		sleep 0.5
	done
}

# Runs wrk for one variant and connection count and prints one table row; sets rowfail when errors occurred.
run_wrk() {
	local variant=$1 n=$2 url=$3 script=$4 out threads rps p50 p99 serr non2xx errs peak peakfile sampler
	threads=$(( n < 4 ? n : 4 ))
	peakfile=$(mktemp)
	sample_peak "$P" "$peakfile" &
	sampler=$!
	out=$(wrk -t"$threads" -c"$n" -d"${duration}s" --timeout "${timeout}s" --latency ${script:+-s "$script"} "$url" 2>&1)
	kill "$sampler" 2>/dev/null
	wait "$sampler" 2>/dev/null
	rps=$(awk '/^Requests\/sec:/ { print $2 }' <<<"$out")
	p50=$(awk '$1 == "50%" { print $2 }' <<<"$out")
	p99=$(awk '$1 == "99%" { print $2 }' <<<"$out")
	serr=$(awk '/^ *Socket errors:/ { gsub(",", ""); print $4 + $6 + $8 + $10 }' <<<"$out")
	non2xx=$(awk '/Non-2xx or 3xx responses:/ { print $NF }' <<<"$out")
	peak=$(cat "$peakfile")
	rm -f "$peakfile"
	errs=$(( ${serr:-0} + ${non2xx:-0} ))
	[ $(( ${peak:-0} * 10 )) -ge $(( n * 9 )) ] || errs=$((errs + 1))
	[ -n "$rps" ] || { echo "$out" >&2; rps=0; errs=$((errs + 1)); }
	[ "$errs" = 0 ] || rowfail=1
	printf '| %s | %d | %s | %s | %s | %d | %d | %d |\n' "$variant" "$n" "${rps:-0}" \
		"$([ -n "$p50" ] && to_ms "$p50" || echo -)" "$([ -n "$p99" ] && to_ms "$p99" || echo -)" "${serr:-0}" "${non2xx:-0}" "${peak:-0}"
}

new_port; O=$PORT
python3 "$here/load-origin.py" "$O" >"$tmp/origin-$O.log" 2>&1 &
pids+=($!)
wait_port "$O" || { echo "origin did not start" >&2; exit 1; }

cat >"$tmp/forward.lua" <<LUA
request = function()
	return wrk.format("GET", "http://127.0.0.1:$O/index.html", { Host = "127.0.0.1:$O" })
end
LUA

rows=$(mktemp)
rowfail=0
for variant in $variants; do
	new_root "$variant"
	new_port; P=$PORT
	case $variant in
	forward) start_dg "$P" SERVER=http "${dgargs[@]}" || { echo "delegated did not start" >&2; exit 1; }
		url=http://127.0.0.1:$P/; script=$tmp/forward.lua ;;
	reverse) start_dg "$P" SERVER=http "MOUNT=/* http://127.0.0.1:$O/*" "${dgargs[@]}" || { echo "delegated did not start" >&2; exit 1; }
		url=http://127.0.0.1:$P/index.html; script= ;;
	tls) start_dg "$P" SERVER=http STLS=fcl "MOUNT=/* http://127.0.0.1:$O/*" "${dgargs[@]}" || { echo "delegated did not start" >&2; exit 1; }
		url=https://127.0.0.1:$P/index.html; script= ;;
	*) echo "unknown variant: $variant" >&2; exit 2 ;;
	esac
	for n in $conns; do
		run_wrk "$variant" "$n" "$url" "$script" >>"$rows"
	done
	kill "$last_pid" 2>/dev/null
	pkill -f -- "delegated.*-P$P " 2>/dev/null
	sleep 1
done

{
	echo "| Variante | Verbindungen | Requests/s | p50 (ms) | p99 (ms) | Socket-Fehler | Non-2xx | Spitze Verbindungen |"
	echo "|---|---|---|---|---|---|---|---|"
	cat "$rows"
} | if [ -n "$outfile" ]; then tee "$outfile"; else cat; fi
rm -f "$rows"
if [ "$check" = 1 ] && [ "$rowfail" != 0 ]; then
	echo "FAIL load test reported errors" >&2
	exit 1
fi
exit 0
