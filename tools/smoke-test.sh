#!/usr/bin/env bash
# Smoke test for a delegated binary (version, HTTP forward proxy, reverse proxy).
# Usage: tools/smoke-test.sh <delegated> [--keep]   (SMOKE_TLS=1 enables the TLS cases)
set -euo pipefail

bin=${1:?usage: smoke-test.sh <delegated> [--keep]}
keep=0
[ "${2:-}" = "--keep" ] && keep=1
bin=$(readlink -f "$bin")
[ -x "$bin" ] || { echo "not executable: $bin" >&2; exit 2; }

tmp=$(mktemp -d /tmp/dg-smoke.XXXXXX)
chmod 755 "$tmp"
pids=()
ports=()
fails=0

cleanup() {
	local p
	for p in "${pids[@]}"; do kill "$p" 2>/dev/null || true; done
	for p in "${ports[@]}"; do pkill -f -- "delegated.*-P$p |DeleGate.*-P$p " 2>/dev/null || true; done
	sleep 0.3
	for p in "${pids[@]}"; do kill -9 "$p" 2>/dev/null || true; done
	for p in "${ports[@]}"; do pkill -9 -f -- "delegated.*-P$p |DeleGate.*-P$p " 2>/dev/null || true; done
	if [ "$keep" = 1 ]; then echo "kept $tmp"; else rm -rf "$tmp"; fi
}
trap cleanup EXIT
trap 'exit 130' INT TERM

port_busy() { (exec 3<>"/dev/tcp/127.0.0.1/$1") 2>/dev/null; }

free_port() {
	local p
	while :; do
		p=$((20000 + RANDOM % 10000))
		port_busy "$p" || { echo "$p"; return; }
	done
}

wait_port() {
	local i
	for i in $(seq 1 100); do
		port_busy "$1" && return 0
		sleep 0.1
	done
	return 1
}

# Copy of the binary and a DGROOT that the unprivileged user can use
mkdir -p "$tmp/bin" "$tmp/www" "$tmp/root"
cp "$bin" "$tmp/bin/delegated"
chmod 755 "$tmp/bin" "$tmp/bin/delegated"
echo "smoke-ok" > "$tmp/www/index.html"
chmod 755 "$tmp/www"
chmod 644 "$tmp/www/index.html"

drop=()
if [ "$(id -u)" = 0 ]; then
	chown nobody "$tmp/root"
	drop=(setpriv --reuid=nobody --regid=nogroup --clear-groups)
fi

dg() { env -u SSL_CERT_FILE "${drop[@]}" "$tmp/bin/delegated" "$@"; }

report() {
	if [ "$2" = 0 ]; then
		echo "PASS $1"
	else
		echo "FAIL $1"
		fails=$((fails + 1))
		show_logs
	fi
}

show_logs() {
	local f
	for f in "$tmp"/*.log "$tmp"/root/log/*; do
		[ -f "$f" ] || continue
		echo "--- $f"
		tail -n 20 "$f"
	done
}

origin_port=$(free_port)
(cd "$tmp/www" && exec python3 -m http.server "$origin_port" --bind 127.0.0.1) >"$tmp/origin.log" 2>&1 &
pids+=($!)
wait_port "$origin_port" || { echo "FAIL origin server did not start"; exit 1; }

case_version() {
	local out rc
	out=$(dg -Fver 2>&1) && rc=0 || rc=$?
	[ "$rc" = 0 ] && grep -q "9\.9\.13" <<<"$out"
}

case_forward() {
	local p out
	p=$(free_port)
	ports+=("$p")
	dg -P"$p" DGROOT="$tmp/root" ADMIN=test@localhost SERVER=http -f >"$tmp/forward.log" 2>&1 &
	pids+=($!)
	wait_port "$p" || return 1
	out=$(curl -s -m 10 -x "http://127.0.0.1:$p" "http://127.0.0.1:$origin_port/index.html") || return 1
	[ "$out" = "smoke-ok" ]
}

case_reverse() {
	local p out
	p=$(free_port)
	ports+=("$p")
	dg -P"$p" DGROOT="$tmp/root" ADMIN=test@localhost SERVER=http \
		"MOUNT=/* http://127.0.0.1:$origin_port/*" -f >"$tmp/reverse.log" 2>&1 &
	pids+=($!)
	wait_port "$p" || return 1
	out=$(curl -s -m 10 "http://127.0.0.1:$p/index.html") || return 1
	[ "$out" = "smoke-ok" ]
}

case_tls() {
	echo "SKIP tls (not implemented)"
}

run() { local name=$1; shift; if "$@"; then report "$name" 0; else report "$name" 1; fi; }

run "1 version" case_version
run "2 http forward proxy" case_forward
run "3 http reverse proxy" case_reverse
if [ "${SMOKE_TLS:-0}" = 1 ]; then case_tls; else echo "SKIP tls (SMOKE_TLS=0)"; fi

echo "failures: $fails"
exit "$fails"
