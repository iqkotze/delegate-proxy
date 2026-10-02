#!/usr/bin/env bash
# TLS session cache tests of delegated with a large environment; exit code 77 means skipped.
# Usage: tests/tls/session-tests.sh <delegated> <case> [--keep]   (cases: session-resume session-latency)
set -uo pipefail

here=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
. "$here/lib.sh"

[ $# -ge 2 ] || { echo "usage: session-tests.sh <delegated> <case> [--keep]" >&2; exit 2; }
command -v openssl >/dev/null || { echo "SKIP openssl command not found"; exit 77; }
tls_setup "$1" "$([ "${3:-}" = --keep ] && echo 1 || echo 0)"
testcase=$2

# Starts the TLS terminator with 200 extra environment variables; sets P and O.
start_terminator() {
	local i
	DG_ENV=()
	for i in $(seq 1 200); do DG_ENV+=("DGPAD_$i=x"); done
	new_port; O=$PORT
	start_origin "$O" || return 1
	new_port; P=$PORT
	start_dg "$P" SERVER=http STLS=fcl "MOUNT=/* http://127.0.0.1:$O/*" || return 1
}

# Requests the page with a TLS 1.2 session ID (no ticket); extra s_client options select save or reuse.
session_get() {
	printf 'GET /index.html HTTP/1.0\r\n\r\n' |
		timeout 20 openssl s_client -connect "127.0.0.1:$P" -tls1_2 -no_ticket -ign_eof "$@" 2>&1
}

# Prints the setup times in seconds of all connections from the SSLway log in time order.
setup_times() {
	grep -rh "## SSLway ## " "$tmp/root/log" | sort | sed -n 's/.*## SSLway ## \([0-9.]*\) .*/\1/p'
}

case_session_resume() {
	local out
	start_terminator || return 1
	session_get -sess_out "$tmp/sess" | grep -q '^New, TLSv1.2' || return 1
	out=$(session_get -sess_in "$tmp/sess")
	grep -q '^Reused, TLSv1.2' <<<"$out" || return 1
	out=$(session_get -sess_in "$tmp/sess")
	grep -q '^Reused, TLSv1.2' <<<"$out" || return 1
	! grep -rq 'cache lock NG\|CGIENV OVERFLOW' "$tmp/root/log" "$tmp/dg-$P.log"
}

case_session_latency() {
	local i full best
	start_terminator || return 1
	session_get -sess_out "$tmp/sess" >/dev/null
	for i in 1 2 3; do
		session_get -sess_in "$tmp/sess" >/dev/null
	done
	sleep 0.3
	full=$(setup_times | sed -n 1p)
	best=$(setup_times | sed 1d | sort -n | sed -n 1p)
	echo "setup time full handshake: ${full:-none} s, best resumed: ${best:-none} s"
	[ -n "$best" ] && awk -v b="$best" 'BEGIN { exit !(b < 0.03) }'
}

cases="session-resume session-latency"
fn=case_${testcase//-/_}
if [ "$testcase" = list ]; then echo "$cases"; exit 0; fi
declare -F "$fn" >/dev/null || { echo "unknown case: $testcase (known: $cases)" >&2; exit 2; }
run "$testcase" "$fn"
exit "$fails"
