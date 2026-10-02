#!/usr/bin/env bash
# TLS integration tests of delegated against the system OpenSSL; exit code 77 means skipped.
# Usage: tests/tls/tls-tests.sh <delegated> <case> [--keep]   (cases: see the list at the end)
set -uo pipefail

here=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
. "$here/lib.sh"

[ $# -ge 2 ] || { echo "usage: tls-tests.sh <delegated> <case> [--keep]" >&2; exit 2; }
command -v openssl >/dev/null || { echo "SKIP openssl command not found"; exit 77; }
command -v curl >/dev/null || { echo "SKIP curl not found"; exit 77; }
tls_setup "$1" "$([ "${3:-}" = --keep ] && echo 1 || echo 0)"
testcase=$2

body() { grep -q smoke-ok <<<"$1"; }

# Starts the TLS terminating DeleGate in front of the plain origin; sets P and O.
start_terminator() {
	new_port; O=$PORT
	start_origin "$O" || return 1
	new_port; P=$PORT
	start_dg "$P" SERVER=http "$@" "MOUNT=/* http://127.0.0.1:$O/*" || return 1
}

case_tls13() {
	local out
	start_terminator STLS=fcl || return 1
	out=$(tls_get "$P" -tls1_3)
	grep -q 'Protocol version: TLSv1.3' <<<"$out" && body "$out" || return 1
	out=$(curl -sk -m 10 --tlsv1.3 --tls-max 1.3 "https://127.0.0.1:$P/index.html")
	[ "$out" = smoke-ok ]
}

case_tls12() {
	local out
	start_terminator STLS=fcl || return 1
	out=$(tls_get "$P" -tls1_2)
	grep -q 'Protocol version: TLSv1.2' <<<"$out" && body "$out" || return 1
	out=$(curl -sk -m 10 --tlsv1.2 --tls-max 1.2 "https://127.0.0.1:$P/index.html")
	[ "$out" = smoke-ok ]
}

# A client of this protocol must connect to a reference server, otherwise the test is meaningless.
client_can_talk() {
	local opt=$1 c out
	new_port; c=$PORT
	openssl s_server -accept "$c" -cert "$tmp/ctl-cert.pem" -key "$tmp/ctl-key.pem" "-$opt" \
		-cipher 'ALL:@SECLEVEL=0' -www -quiet >"$tmp/ctl-$opt.log" 2>&1 &
	pids+=($!)
	wait_port "$c" || return 1
	out=$(printf 'GET / HTTP/1.0\r\n\r\n' | timeout 10 openssl s_client -connect "127.0.0.1:$c" "-$opt" \
		-cipher 'ALL:@SECLEVEL=0' -brief -ign_eof 2>&1)
	grep -q 'Protocol version' <<<"$out"
}

# Sends a ClientHello with the given record version (0303, 0300) and prints the first bytes of the answer in hex.
raw_hello() {
	local ver=$1 rec body hs
	body="${ver}$(printf '%064d' 0)000002c02b01000016000a000400020017000b00020100000d000400020403"
	hs=$(printf '01%06x' $(( ${#body} / 2 )))$body
	rec="16030$([ "$ver" = 0300 ] && echo 0 || echo 1)$(printf '%04x' $(( ${#hs} / 2 )))$hs"
	(
		exec 3<>"/dev/tcp/127.0.0.1/$P"
		printf '%b' "$(sed 's/../\\x&/g' <<<"$rec")" >&3
		timeout 3 head -c 7 <&3 | od -An -tx1 | tr -d ' \n'
	) 2>/dev/null
}

case_old_protocols() {
	local opt out tested=0 hello
	mk_cert "$tmp/ctl" localhost
	start_terminator STLS=fcl || return 1
	# SSLv3 has no s_client option in current OpenSSL; a raw ClientHello with version 3.0 stands in for it.
	hello=$(raw_hello 0303)
	if [ "${hello:0:2}" = 16 ]; then
		hello=$(raw_hello 0300)
		[ "${hello:0:2}" != 16 ] || { echo "SSLv3 ClientHello was answered with a ServerHello"; return 1; }
		tested=$((tested + 1))
	else
		echo "SKIP ssl3 (the reference ClientHello gets no ServerHello: $hello)"
	fi
	for opt in tls1_1 tls1; do
		if ! openssl s_client -help 2>&1 | grep -q -- "-$opt\$\|-$opt "; then
			echo "SKIP $opt (s_client has no such option)"
			continue
		fi
		if ! client_can_talk "$opt"; then
			echo "SKIP $opt (the client cannot talk it to the reference server)"
			continue
		fi
		out=$(tls_get "$P" "-$opt" -cipher 'ALL:@SECLEVEL=0')
		if body "$out" || grep -q 'Protocol version: \(TLSv1\|SSLv3\)' <<<"$out"; then
			echo "$opt was accepted"
			return 1
		fi
		grep -q 'alert protocol version\|alert handshake failure' <<<"$out" || { echo "$opt: no alert: $out"; return 1; }
		tested=$((tested + 1))
	done
	[ "$tested" -gt 0 ] || { echo "SKIP no old protocol testable"; exit 77; }
}

case_legacy_tls1() {
	local out
	mk_cert "$tmp/ctl" localhost
	client_can_talk tls1 || { echo "SKIP the client cannot talk TLS 1.0"; exit 77; }
	DG_ENV=("SSL_CIPHER=ALL:@SECLEVEL=0")
	start_terminator "STLS=fcl,sslway -tls1" || return 1
	out=$(tls_get "$P" -tls1 -cipher 'ALL:@SECLEVEL=0')
	grep -q 'Protocol version: TLSv1$' <<<"$out" && body "$out" || { echo "$out"; return 1; }
	out=$(tls_get "$P" -tls1_2)
	body "$out" && return 1
	grep -rq 'SECLEVEL=0' "$tmp"/root/log "$tmp"/dg-"$P".log
}

# -ssl2 and -ssl3 are reported and ignored; -bugs only sets the option set of the library.
case_sslway_options() {
	local out opt
	for opt in -ssl2 -ssl3 -bugs; do
		start_terminator "STLS=fcl,sslway $opt" || return 1
		out=$(tls_get "$P" -tls1_2)
		grep -q 'Protocol version: TLSv1.2' <<<"$out" && body "$out" || return 1
		case $opt in
		-ssl2) grep -rq 'SSLv2 is not supported' "$tmp"/root/log || return 1 ;;
		-ssl3) grep -rq 'SSLv3 is not supported' "$tmp"/root/log || return 1 ;;
		esac
		kill "$last_pid"
		sleep 1
	done
}

# Starts a TLS origin with the given certificate prefix; sets O.
start_tls_origin() {
	new_port; O=$PORT
	(cd "$tmp/www" && exec openssl s_server -WWW -accept "$O" -cert "$1-cert.pem" -key "$1-key.pem" -quiet) \
		>"$tmp/tls-origin.log" 2>&1 &
	pids+=($!)
	wait_port "$O"
}

case_origin_ca_ok() {
	local out
	mk_ca "$tmp/ca" test-ca
	mk_issued "$tmp/ca" "$tmp/origin"
	start_tls_origin "$tmp/origin" || return 1
	new_port; P=$PORT
	start_dg "$P" SERVER=http "MOUNT=/* https://127.0.0.1:$O/*" "STLS=fsv,sslway -Vrfy -CAfile $tmp/ca.pem" || return 1
	out=$(curl -s -m 10 "http://127.0.0.1:$P/index.html")
	[ "$out" = smoke-ok ] && grep -rq 'server.s cert. = .*test-ca' "$tmp"/root/log
}

case_origin_ca_bad() {
	local out
	mk_ca "$tmp/ca" test-ca
	mk_ca "$tmp/other" other-ca
	mk_issued "$tmp/ca" "$tmp/origin"
	start_tls_origin "$tmp/origin" || return 1
	new_port; P=$PORT
	start_dg "$P" SERVER=http "MOUNT=/* https://127.0.0.1:$O/*" "STLS=fsv,sslway -Vrfy -CAfile $tmp/other.pem" || return 1
	out=$(curl -s -m 10 "http://127.0.0.1:$P/index.html")
	body "$out" && return 1
	grep -rq 'unable to get local issuer certificate' "$tmp"/root/log || return 1
	new_port; P=$PORT
	start_dg "$P" SERVER=http "MOUNT=/* https://127.0.0.1:$O/*" "STLS=fsv,sslway -Vrfy" || return 1
	out=$(curl -s -m 10 "http://127.0.0.1:$P/index.html")
	! body "$out"
}

case_origin_no_check() {
	local out
	mk_cert "$tmp/origin" localhost
	start_tls_origin "$tmp/origin" || return 1
	new_port; P=$PORT
	start_dg "$P" SERVER=http "MOUNT=/* https://127.0.0.1:$O/*" STLS=fsv || return 1
	out=$(curl -s -m 10 "http://127.0.0.1:$P/index.html")
	[ "$out" = smoke-ok ]
}

subject_of() {
	timeout 20 openssl s_client -connect "127.0.0.1:$1" -servername "$2" </dev/null 2>/dev/null |
		openssl x509 -noout -subject 2>/dev/null
}

case_sni() {
	local certs=$tmp/root/etc/certs a b
	mkdir -p "$certs"
	mk_cert "$tmp/sni" sni.test DNS:sni.test
	cat "$tmp/sni-cert.pem" "$tmp/sni-key.pem" >"$certs/sn.sni.test.pem"
	chown -R "$(id -u nobody 2>/dev/null || id -u)" "$tmp/root" 2>/dev/null
	start_terminator STLS=fcl || return 1
	a=$(subject_of "$P" sni.test)
	b=$(subject_of "$P" other.test)
	echo "sni.test: $a / other.test: $b"
	grep -q 'CN *= *sni.test' <<<"$a" && ! grep -q 'sni.test' <<<"$b" && [ -n "$b" ]
}

# Sends stdin to the port and closes the connection.
raw_send() {
	(exec 3<>"/dev/tcp/127.0.0.1/$1"; cat >&3; sleep 0.3) 2>/dev/null
}

case_abort() {
	local out
	start_terminator STLS=fcl || return 1
	# half a ClientHello, then close
	printf '\x16\x03\x01\x02\x00\x01\x00\x01\xfc\x03\x03' | raw_send "$P"
	# a connection without data
	(exec 3<>"/dev/tcp/127.0.0.1/$P"; exec 3>&-)
	# garbage instead of a handshake
	head -c 300 /dev/urandom | raw_send "$P"
	# a client that stops in the middle of a request
	(printf 'GET /index.html HTTP/1.1\r\nHost: x\r\nX-Pad: '; sleep 2) |
		timeout 1 openssl s_client -connect "127.0.0.1:$P" -quiet >/dev/null 2>&1
	# a client that kills the connection right after the handshake
	timeout 1 openssl s_client -connect "127.0.0.1:$P" </dev/null >/dev/null 2>&1
	sleep 1
	kill -0 "$last_pid" || return 1
	out=$(curl -sk -m 10 "https://127.0.0.1:$P/index.html")
	[ "$out" = smoke-ok ] || return 1
	! grep -rqi 'segmentation\|SIGSEGV\|SIGABRT\|abort(' "$tmp"/dg-"$P".log
}

# An origin that sends part of the body and closes the TLS connection.
case_origin_abort() {
	mk_cert "$tmp/origin" localhost
	new_port; O=$PORT
	python3 - "$O" "$tmp/origin-cert.pem" "$tmp/origin-key.pem" >"$tmp/trunc-origin.log" 2>&1 <<'PY' &
import socket, ssl, sys
port, cert, key = int(sys.argv[1]), sys.argv[2], sys.argv[3]
ctx = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
ctx.load_cert_chain(cert, key)
srv = socket.socket()
srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
srv.bind(("127.0.0.1", port))
srv.listen(8)
while True:
    c, _ = srv.accept()
    try:
        t = ctx.wrap_socket(c, server_side=True)
        t.recv(4096)
        t.sendall(b"HTTP/1.0 200 OK\r\nContent-Length: 100000\r\n\r\nsmoke-partial")
        c.shutdown(socket.SHUT_RDWR)
    except Exception:
        pass
    c.close()
PY
	pids+=($!)
	wait_port "$O" || return 1
	new_port; P=$PORT
	start_dg "$P" SERVER=http "MOUNT=/* https://127.0.0.1:$O/*" STLS=fsv || return 1
	curl -s -m 4 "http://127.0.0.1:$P/index.html" >"$tmp/partial.out" 2>/dev/null
	kill -0 "$last_pid" || return 1
	curl -s -m 4 "http://127.0.0.1:$P/index.html" >/dev/null 2>&1
	kill -0 "$last_pid" || return 1
	! grep -rqi 'segmentation\|SIGSEGV\|SIGABRT' "$tmp"/dg-"$P".log
}

case_generated_cert() {
	local certs=$tmp/root/etc/certs host cert text f1 f2 days
	host=$(hostname)
	start_terminator STLS=fcl || return 1
	[ "$(curl -sk -m 10 "https://127.0.0.1:$P/index.html")" = smoke-ok ] || return 1
	cert=$certs/server-cert.pem
	[ -f "$cert" ] && [ -f "$certs/server-key.pem" ] || return 1
	[ "$(stat -c %a "$certs/server-key.pem")" = 600 ] || return 1
	text=$(openssl x509 -in "$cert" -noout -text)
	grep -q 'Public Key Algorithm: id-ecPublicKey' <<<"$text" || return 1
	grep -q 'ASN1 OID: prime256v1' <<<"$text" || return 1
	grep -q 'Signature Algorithm: ecdsa-with-SHA256' <<<"$text" || return 1
	grep -q "Subject: CN *= *$host\$" <<<"$text" || return 1
	grep -q 'IP Address:127.0.0.1' <<<"$text" || return 1
	grep -q "DNS:$host" <<<"$text" || return 1
	days=$(( ( $(date -d "$(openssl x509 -in "$cert" -noout -enddate | cut -d= -f2)" +%s) - $(date +%s) ) / 86400 ))
	[ "$days" -ge 824 ] && [ "$days" -le 825 ] || { echo "validity $days days"; return 1; }
	# a restart keeps the certificate
	f1=$(openssl x509 -in "$cert" -noout -fingerprint -sha256)
	kill "$last_pid"; sleep 1
	new_port; P=$PORT
	start_dg "$P" SERVER=http STLS=fcl "MOUNT=/* http://127.0.0.1:$O/*" || return 1
	[ "$(curl -sk -m 10 "https://127.0.0.1:$P/index.html")" = smoke-ok ] || return 1
	f2=$(timeout 10 openssl s_client -connect "127.0.0.1:$P" </dev/null 2>/dev/null | openssl x509 -noout -fingerprint -sha256)
	[ "$f1" = "$f2" ]
}

case_cert_env() {
	local certs=$tmp/root/etc/certs bundle="$tmp/bundle.pem" pair="$tmp/pair.pem" s
	mk_cert "$tmp/pair" pair.test DNS:pair.test
	cat "$tmp/pair-cert.pem" "$tmp/pair-key.pem" >"$pair"
	cat "$tmp/pair-cert.pem" >"$bundle"
	chmod 644 "$pair" "$bundle"
	# a CA bundle without private key is not a server certificate
	new_port; O=$PORT
	start_origin "$O" || return 1
	new_port; P=$PORT
	DG_ENV=("SSL_CERT_FILE=$bundle")
	start_dg "$P" SERVER=http STLS=fcl "MOUNT=/* http://127.0.0.1:$O/*" || return 1
	[ "$(curl -sk -m 10 "https://127.0.0.1:$P/index.html")" = smoke-ok ] || return 1
	s=$(subject_of "$P" localhost)
	grep -q 'pair.test' <<<"$s" && return 1
	grep -rq 'SSL_CERT_FILE.*ignored' "$tmp"/root/log || return 1
	# a file with certificate and key is used
	new_port; P=$PORT
	DG_ENV=("SSL_CERT_FILE=$pair")
	start_dg "$P" SERVER=http STLS=fcl "MOUNT=/* http://127.0.0.1:$O/*" || return 1
	[ "$(curl -sk -m 10 "https://127.0.0.1:$P/index.html")" = smoke-ok ] || return 1
	s=$(subject_of "$P" localhost)
	grep -q 'pair.test' <<<"$s"
}

case_parallel() {
	local n
	start_terminator STLS=fcl || return 1
	n=$(seq 1 24 | xargs -P8 -I{} curl -sk -m 20 "https://127.0.0.1:$P/index.html" | grep -c '^smoke-ok$')
	[ "$n" = 24 ] && kill -0 "$last_pid"
}

# Bodies of several megabytes in both directions, through TLS on the client side and on the server side.
case_large() {
	local sum
	head -c 3000000 /dev/urandom >"$tmp/www/big.bin"
	chmod 644 "$tmp/www/big.bin"
	sum=$(sha256sum <"$tmp/www/big.bin")
	# download through the TLS terminator
	start_terminator STLS=fcl || return 1
	[ "$(curl -sk -m 30 "https://127.0.0.1:$P/big.bin" | sha256sum)" = "$sum" ] || { echo "download failed"; return 1; }
	# download from a TLS origin
	mk_cert "$tmp/origin" localhost
	start_tls_origin "$tmp/origin" || return 1
	new_port; P=$PORT
	start_dg "$P" SERVER=http "MOUNT=/* https://127.0.0.1:$O/*" STLS=fsv || return 1
	[ "$(curl -s -m 30 "http://127.0.0.1:$P/big.bin" | sha256sum)" = "$sum" ] || { echo "origin download failed"; return 1; }
	# upload through the TLS terminator to a plain sink that answers with the digest of the body
	new_port; O=$PORT
	python3 - "$O" >"$tmp/sink.log" 2>&1 <<'PY' &
import hashlib, http.server, sys
class H(http.server.BaseHTTPRequestHandler):
    def do_POST(self):
        n = int(self.headers["Content-Length"])
        d = hashlib.sha256(self.rfile.read(n)).hexdigest().encode()
        self.send_response(200)
        self.send_header("Content-Length", str(len(d)))
        self.end_headers()
        self.wfile.write(d)
http.server.HTTPServer(("127.0.0.1", int(sys.argv[1])), H).serve_forever()
PY
	pids+=($!)
	wait_port "$O" || return 1
	new_port; P=$PORT
	start_dg "$P" SERVER=http STLS=fcl "MOUNT=/* http://127.0.0.1:$O/*" || return 1
	[ "$(curl -sk -m 30 --data-binary @"$tmp/www/big.bin" "https://127.0.0.1:$P/up")" = "${sum%% *}" ] || { echo "upload failed"; return 1; }
}

case_cipher_list() {
	local out
	start_terminator "STLS=fcl,sslway -cipher ECDHE-ECDSA-AES128-GCM-SHA256" || return 1
	out=$(tls_get "$P" -tls1_2)
	grep -q 'Ciphersuite: ECDHE-ECDSA-AES128-GCM-SHA256' <<<"$out" && body "$out"
}

cases="tls13 tls12 old-protocols legacy-tls1 sslway-options origin-ca-ok origin-ca-bad origin-no-check sni abort origin-abort generated-cert cert-env parallel large cipher-list"
fn=case_${testcase//-/_}
if [ "$testcase" = list ]; then echo "$cases"; exit 0; fi
declare -F "$fn" >/dev/null || { echo "unknown case: $testcase (known: $cases)" >&2; exit 2; }
run "$testcase" "$fn"
exit "$fails"
