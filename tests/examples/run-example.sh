#!/usr/bin/env bash
# Starts delegated with one example from doc/examples and checks the expected behaviour.
# Usage: tests/examples/run-example.sh <delegated> <example> [--keep]   (list prints the examples)
set -euo pipefail

here=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
repo=$(cd "$here/../.." && pwd)
examples=$(cd "$repo/doc/examples" && ls ./*.conf | sed 's#^\./##; s#\.conf$##')

if [ "${1:-}" = list ]; then echo "$examples"; exit 0; fi
[ $# -ge 2 ] || { echo "usage: run-example.sh <delegated> <example> [--keep]" >&2; exit 2; }
grep -qx "$2" <<<"$examples" || { echo "unknown example: $2" >&2; exit 2; }
for tool in curl openssl python3; do
	command -v "$tool" >/dev/null || { echo "SKIP $tool not found"; exit 77; }
done

. "$here/../tls/lib.sh"
tls_setup "$1" "$([ "${3:-}" = "--keep" ] && echo 1 || echo 0)"
example=$2
src=$repo/doc/examples/$example.conf

# Writes the example with the placeholders @NAME@ replaced: render <out> NAME=value...
render() {
	local out=$1 kv
	shift
	cp "$src" "$out"
	for kv in "$@"; do sed -i "s|@${kv%%=*}@|${kv#*=}|g" "$out"; done
	chmod 644 "$out"
	if grep -q '@[A-Z_]*@' "$out"; then echo "unreplaced placeholder in $out"; return 1; fi
}

# Starts delegated with a rendered example: start_conf <port> <conf>
start_conf() {
	new_root "ex$1"
	dg DGROOT="$DGROOT" "+=$2" -f >"$tmp/dg-$1.log" 2>&1 &
	pids+=($!)
	wait_listen "$1"
}

mkdir -p "$tmp/www/data" "$tmp/www/new" "$tmp/www/sub"
echo data-a >"$tmp/www/data/a.txt"
echo new-b >"$tmp/www/new/b.txt"
echo sub-c >"$tmp/www/sub/c.txt"
head -c 600000 /dev/zero >"$tmp/www/big.bin"
chmod -R a+rX "$tmp/www"
new_port; origin=$PORT
start_origin "$origin" || { echo "FAIL origin server did not start"; exit 1; }
new_port; port=$PORT
conf=$tmp/example.conf

case_forward_proxy() {
	render "$conf" PORT="$port" && start_conf "$port" "$conf" || return 1
	[ "$(curl -s -m 10 -x "http://127.0.0.1:$port" "http://127.0.0.1:$origin/index.html")" = smoke-ok ] &&
		[ "$(curl -s -m 10 -x "http://127.0.0.1:$port" "http://127.0.0.1:$origin/data/a.txt")" = data-a ]
}

case_reverse_proxy() {
	render "$conf" PORT="$port" ORIGIN="127.0.0.1:$origin" && start_conf "$port" "$conf" || return 1
	[ "$(curl -s -m 10 "http://127.0.0.1:$port/index.html")" = smoke-ok ] &&
		[ "$(curl -s -m 10 "http://127.0.0.1:$port/sub/c.txt")" = sub-c ] &&
		[ "$(curl -s -m 10 -o /dev/null -w '%{http_code}' "http://127.0.0.1:$port/missing")" = 404 ]
}

case_tls_termination() {
	local certs=$tmp/certs out
	mkdir -p "$certs"
	mk_cert "$tmp/term" localhost
	cp "$tmp/term-cert.pem" "$certs/server-cert.pem"
	cp "$tmp/term-key.pem" "$certs/server-key.pem"
	render "$conf" PORT="$port" ORIGIN="127.0.0.1:$origin" CERTDIR="$certs" && start_conf "$port" "$conf" || return 1
	[ "$(curl -sk -m 10 "https://127.0.0.1:$port/index.html")" = smoke-ok ] || return 1
	out=$(tls_get "$port" | grep -c 'Protocol version: TLSv1\.[23]')
	[ "$out" = 1 ] &&
		[ "$(openssl s_client -connect "127.0.0.1:$port" </dev/null 2>/dev/null | openssl x509 -noout -fingerprint -sha256)" = \
			"$(openssl x509 -in "$tmp/term-cert.pem" -noout -fingerprint -sha256)" ]
}

# TLS origin with the certificate name <san>: tls_origin <san> <expected: ok|bad>
tls_origin() {
	local o p out rc=0
	mk_ca "$tmp/ca" example-ca
	mk_issued "$tmp/ca" "$tmp/org" "$1"
	new_port; o=$PORT
	(cd "$tmp/www" && exec openssl s_server -WWW -accept "$o" -cert "$tmp/org-cert.pem" -key "$tmp/org-key.pem" -quiet) \
		>"$tmp/tls-origin.log" 2>&1 &
	pids+=($!)
	wait_port "$o" || return 1
	new_port; p=$PORT
	render "$conf" PORT="$p" ORIGIN_NAME="localhost:$o" CA="$tmp/ca.pem" && start_conf "$p" "$conf" || return 1
	out=$(curl -s -m 10 "http://127.0.0.1:$p/index.html") || rc=$?
	if [ "$2" = ok ]; then [ "$out" = smoke-ok ]; else [ "$out" != smoke-ok ]; fi
}

case_tls_to_origin() {
	tls_origin DNS:localhost ok && tls_origin DNS:other.test bad
}

case_socks_proxy() {
	render "$conf" PORT="$port" && start_conf "$port" "$conf" || return 1
	[ "$(curl -s -m 10 --socks5 "127.0.0.1:$port" "http://127.0.0.1:$origin/index.html")" = smoke-ok ]
}

case_ftp_gateway() {
	local f out
	mkdir -p "$tmp/ftp/pub"
	echo ftp-ok >"$tmp/ftp/pub/hello.txt"
	chmod -R a+rX "$tmp/ftp"
	new_port; f=$PORT
	python3 "$here/ftpd.py" "$f" "$tmp/ftp" >"$tmp/ftpd.log" 2>&1 &
	pids+=($!)
	wait_port "$f" || return 1
	render "$conf" PORT="$port" FTP="127.0.0.1:$f" && start_conf "$port" "$conf" || return 1
	[ "$(curl -s -m 10 "http://127.0.0.1:$port/ftp/pub/hello.txt")" = ftp-ok ] &&
		curl -s -m 10 "http://127.0.0.1:$port/ftp/pub/" | grep -q hello.txt
}

# Access to the host of delegated itself is always permitted, so remote names are used
case_access_control() {
	local p2 page
	denied() { curl -s -m 10 -x "http://127.0.0.1:$1" "http://$2/" | grep -q "Reason: $3"; }
	render "$conf" PORT="$port" CLIENTS=127.0.0.1 && start_conf "$port" "$conf" || return 1
	[ "$(curl -s -m 10 -x "http://127.0.0.1:$port" "http://127.0.0.1:$origin/index.html")" = smoke-ok ] || return 1
	denied "$port" www.blocked.example "matched REJECT" || return 1
	! curl -s -m 10 -x "http://127.0.0.1:$port" "http://www.allowed.example/" | grep -q "Forbidden by DeleGate" || return 1
	new_port; p2=$PORT
	render "$conf" PORT="$p2" CLIENTS=192.0.2.1 && start_conf "$p2" "$conf" || return 1
	denied "$p2" www.allowed.example "'localhost' not RELIABLE"
}

case_cache() {
	local dir=$tmp/cache n
	mkdir -p "$dir"
	if [ "$(id -u)" = 0 ]; then chown nobody "$dir"; fi
	render "$conf" PORT="$port" ORIGIN="127.0.0.1:$origin" CACHEDIR="$dir" && start_conf "$port" "$conf" || return 1
	[ "$(curl -s -m 10 "http://127.0.0.1:$port/index.html")" = smoke-ok ] || return 1
	sleep 1
	[ "$(curl -s -m 10 "http://127.0.0.1:$port/index.html")" = smoke-ok ] || return 1
	n=$(grep -c 'GET /index.html' "$tmp/origin-$origin.log" || true)
	[ "$n" = 1 ] && [ -n "$(find "$dir" -type f | head -n 1)" ]
}

case_logging() {
	local dir=$tmp/logs
	mkdir -p "$dir"
	if [ "$(id -u)" = 0 ]; then chown nobody "$dir"; fi
	render "$conf" PORT="$port" ORIGIN="127.0.0.1:$origin" LOGDIR="$dir" && start_conf "$port" "$conf" || return 1
	[ "$(curl -s -m 10 "http://127.0.0.1:$port/index.html")" = smoke-ok ] || return 1
	sleep 1
	[ -s "$dir/delegate.log" ] && grep -q '"GET http://[^ ]*/index.html HTTP[^"]*" 200' "$dir/access.log"
}

case_limits() {
	local t0 t1 c third
	render "$conf" PORT="$port" ORIGIN="127.0.0.1:$origin" && start_conf "$port" "$conf" || return 1
	[ "$(curl -s -m 10 "http://127.0.0.1:$port/index.html")" = smoke-ok ] || return 1
	# MAXIMA conpch:2 refuses a third parallel connection of one client host
	exec 7<>"/dev/tcp/127.0.0.1/$port" 8<>"/dev/tcp/127.0.0.1/$port"
	sleep 0.5
	third=$(curl -s -m 5 -o /dev/null -w '%{http_code}' "http://127.0.0.1:$port/index.html") || true
	exec 7>&- 8>&-
	[ "$third" = 000 ] || return 1
	sleep 0.5
	[ "$(curl -s -m 10 "http://127.0.0.1:$port/index.html")" = smoke-ok ] || return 1
	# MAXIMA bps:2m (bits per second) slows down 600000 bytes to at least two seconds
	t0=$(date +%s.%N)
	curl -s -m 30 -o /dev/null "http://127.0.0.1:$port/big.bin" || return 1
	t1=$(date +%s.%N)
	awk -v a="$t0" -v b="$t1" 'BEGIN { exit !(b - a >= 2) }' || return 1
	# TIMEOUT io:3 closes an idle connection
	c=$( (exec 3<>"/dev/tcp/127.0.0.1/$port"; t=$(date +%s); timeout 15 cat <&3 >/dev/null; echo $(( $(date +%s) - t ))) )
	[ "$c" -ge 2 ] && [ "$c" -le 8 ]
}

case_mount_rewrite() {
	render "$conf" PORT="$port" ORIGIN="127.0.0.1:$origin" && start_conf "$port" "$conf" || return 1
	[ "$(curl -s -m 10 "http://127.0.0.1:$port/api/a.txt")" = data-a ] &&
		[ "$(curl -s -m 10 -o /dev/null -w '%{http_code} %{redirect_url}' "http://127.0.0.1:$port/old/b.txt")" = \
			"302 http://127.0.0.1:$origin/new/b.txt" ] &&
		[ "$(curl -s -m 10 "http://127.0.0.1:$port/INDEX")" = smoke-ok ] &&
		[ "$(curl -s -m 10 "http://127.0.0.1:$port/sub/c.txt")" = sub-c ]
}

case_auth() {
	render "$conf" PORT="$port" ORIGIN="127.0.0.1:$origin" && start_conf "$port" "$conf" || return 1
	[ "$(curl -s -m 10 -o /dev/null -w '%{http_code}' "http://127.0.0.1:$port/index.html")" = 401 ] &&
		[ "$(curl -s -m 10 -o /dev/null -w '%{http_code}' -u alice:wrong "http://127.0.0.1:$port/index.html")" = 401 ] &&
		[ "$(curl -s -m 10 -u alice:secret "http://127.0.0.1:$port/index.html")" = smoke-ok ] &&
		[ "$(curl -s -m 10 -u bob:hunter2 "http://127.0.0.1:$port/sub/c.txt")" = sub-c ]
}

fn=case_${example//-/_}
declare -F "$fn" >/dev/null || { echo "FAIL no check for $example"; exit 1; }
run "$example" "$fn"
echo "failures: $fails"
exit "$fails"
