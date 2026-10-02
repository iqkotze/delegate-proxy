#!/usr/bin/env bash
# Smoke test for a delegated binary (version, HTTP proxies, TLS termination, TLS to the origin, generated certificate).
# Usage: tools/smoke-test.sh <delegated> [--keep]   (SMOKE_TLS=0 skips the TLS cases)
set -euo pipefail

here=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
. "$here/../tests/tls/lib.sh"

[ $# -ge 1 ] || { echo "usage: smoke-test.sh <delegated> [--keep]" >&2; exit 2; }
tls_setup "$1" "$([ "${2:-}" = "--keep" ] && echo 1 || echo 0)"

new_port
origin_port=$PORT
start_origin "$origin_port" || { echo "FAIL origin server did not start"; exit 1; }

case_version() {
	local out rc
	out=$(dg -Fver 2>&1) && rc=0 || rc=$?
	[ "$rc" = 0 ] && grep -q "9\.9\.13" <<<"$out" && grep -q "Loaded: OpenSSL 3\." <<<"$out"
}

case_forward() {
	local p out
	new_port; p=$PORT
	start_dg "$p" SERVER=http || return 1
	out=$(curl -s -m 10 -x "http://127.0.0.1:$p" "http://127.0.0.1:$origin_port/index.html") || return 1
	[ "$out" = "smoke-ok" ]
}

case_reverse() {
	local p out
	new_port; p=$PORT
	start_dg "$p" SERVER=http "MOUNT=/* http://127.0.0.1:$origin_port/*" || return 1
	out=$(curl -s -m 10 "http://127.0.0.1:$p/index.html") || return 1
	[ "$out" = "smoke-ok" ]
}

# TLS terminated by delegated with a configured EC P-256 certificate
case_tls_terminate() {
	local p out certs
	new_root terminate
	certs=$DGROOT/etc/certs
	mkdir -p "$certs"
	mk_cert "$tmp/term" localhost
	cp "$tmp/term-cert.pem" "$certs/server-cert.pem"
	cp "$tmp/term-key.pem" "$certs/server-key.pem"
	if [ "$(id -u)" = 0 ]; then chown -R nobody "$DGROOT"; fi
	new_port; p=$PORT
	start_dg "$p" SERVER=http STLS=fcl "MOUNT=/* http://127.0.0.1:$origin_port/*" || return 1
	out=$(curl -sk -m 10 "https://127.0.0.1:$p/index.html") || return 1
	[ "$out" = "smoke-ok" ] || return 1
	out=$(tls_get "$p" | grep -c 'Protocol version: TLSv1\.[23]')
	[ "$out" = 1 ] &&
		[ "$(openssl s_client -connect "127.0.0.1:$p" </dev/null 2>/dev/null |
			openssl x509 -noout -fingerprint -sha256)" = "$(openssl x509 -in "$tmp/term-cert.pem" -noout -fingerprint -sha256)" ]
}

# TLS from delegated to an openssl s_server origin
case_tls_origin() {
	local p o out
	mk_cert "$tmp/org" localhost
	new_port; o=$PORT
	(cd "$tmp/www" && exec openssl s_server -WWW -accept "$o" -cert "$tmp/org-cert.pem" -key "$tmp/org-key.pem" -quiet) \
		>"$tmp/tls-origin.log" 2>&1 &
	pids+=($!)
	wait_port "$o" || return 1
	new_root origin
	new_port; p=$PORT
	start_dg "$p" SERVER=http "MOUNT=/* https://127.0.0.1:$o/*" STLS=fsv || return 1
	out=$(curl -s -m 10 "http://127.0.0.1:$p/index.html") || return 1
	[ "$out" = "smoke-ok" ]
}

# TLS terminated with the certificate that delegated generates when none is configured
case_tls_generated() {
	local p out key
	new_root generated
	new_port; p=$PORT
	start_dg "$p" SERVER=http STLS=fcl "MOUNT=/* http://127.0.0.1:$origin_port/*" || return 1
	out=$(curl -sk -m 10 "https://127.0.0.1:$p/index.html") || return 1
	[ "$out" = "smoke-ok" ] || return 1
	key=$DGROOT/etc/certs/server-key.pem
	[ -f "$DGROOT/etc/certs/server-cert.pem" ] && [ "$(stat -c %a "$key")" = 600 ] &&
		openssl x509 -in "$DGROOT/etc/certs/server-cert.pem" -noout -text | grep -q 'ASN1 OID: prime256v1'
}

run "1 version" case_version
run "2 http forward proxy" case_forward
run "3 http reverse proxy" case_reverse
if [ "${SMOKE_TLS:-1}" != 1 ]; then
	echo "SKIP tls (SMOKE_TLS=0)"
elif ! command -v openssl >/dev/null || ! command -v curl >/dev/null; then
	echo "SKIP tls (openssl or curl not found)"
else
	run "4 tls termination" case_tls_terminate
	run "5 tls to the origin" case_tls_origin
	run "6 generated certificate" case_tls_generated
fi

echo "failures: $fails"
exit "$fails"
