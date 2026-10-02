#!/usr/bin/env bash
# Shared helpers for tools/smoke-test.sh and tests/tls/tls-tests.sh; source it, do not run it.

tls_setup() {
	bin=$(readlink -f "$1")
	[ -x "$bin" ] || { echo "not executable: $bin" >&2; exit 2; }
	keep=${2:-0}
	tmp=$(mktemp -d /tmp/dg-test.XXXXXX)
	chmod 755 "$tmp"
	pids=()
	ports=()
	fails=0
	DG_ENV=()
	trap tls_cleanup EXIT
	trap 'exit 130' INT TERM
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
}

tls_cleanup() {
	local p
	for p in "${pids[@]}"; do kill "$p" 2>/dev/null || true; done
	for p in "${ports[@]}"; do pkill -f -- "delegated.*-P$p |DeleGate.*-P$p " 2>/dev/null || true; done
	sleep 0.3
	for p in "${pids[@]}"; do kill -9 "$p" 2>/dev/null || true; done
	for p in "${ports[@]}"; do
		pkill -9 -f -- "delegated.*-P$p |DeleGate.*-P$p " 2>/dev/null || true
		rmdir "/tmp/.dg-port-$p" 2>/dev/null || true
	done
	if [ "$keep" = 1 ]; then echo "kept $tmp"; else rm -rf "$tmp"; fi
}

port_busy() { (exec 3<>"/dev/tcp/127.0.0.1/$1") 2>/dev/null; }

# Picks a free port into PORT and claims it for parallel test runs.
new_port() {
	local p
	while :; do
		p=$((20000 + RANDOM % 10000))
		if ! port_busy "$p" && mkdir "/tmp/.dg-port-$p" 2>/dev/null; then
			ports+=("$p")
			PORT=$p
			return
		fi
	done
}

# Waits until the port is in LISTEN state without connecting to it.
wait_listen() {
	local hex i tables=(/proc/net/tcp)
	hex=$(printf '%04X' "$1")
	[ -r /proc/net/tcp6 ] && tables+=(/proc/net/tcp6)
	for i in $(seq 1 100); do
		if awk -v h=":$hex" '$4 == "0A" && $2 ~ h"$" { f = 1 } END { exit !f }' "${tables[@]}"; then
			return 0
		fi
		sleep 0.1
	done
	return 1
}

wait_port() {
	local i
	for i in $(seq 1 100); do
		port_busy "$1" && return 0
		sleep 0.1
	done
	return 1
}

# Runs delegated in its own session (it signals its process group) without SSL_CERT_FILE; DG_ENV adds settings.
dg() {
	setsid env -u SSL_CERT_FILE RES_WAIT=0 RESOLV=file ${DG_ENV[@]+"${DG_ENV[@]}"} "${drop[@]}" "$tmp/bin/delegated" "$@"
}

# Creates an empty DGROOT for one test and selects it: new_root <name>
new_root() {
	DGROOT=$tmp/root-$1
	mkdir -p "$DGROOT"
	if [ "$(id -u)" = 0 ]; then chown nobody "$DGROOT"; fi
}

# Starts delegated in the background on port $1 with the remaining arguments and waits for it.
start_dg() {
	local p=$1
	shift
	dg -P"$p" DGROOT="${DGROOT:-$tmp/root}" ADMIN=test@localhost "$@" -f >"$tmp/dg-$p.log" 2>&1 &
	pids+=($!)
	last_pid=$!
	wait_listen "$p"
}

start_origin() {
	local p=$1
	(cd "$tmp/www" && exec python3 -m http.server "$p" --bind 127.0.0.1) >"$tmp/origin-$p.log" 2>&1 &
	pids+=($!)
	wait_port "$p"
}

# Creates a self-signed EC P-256 certificate and key: mk_cert <prefix> <cn> [san]
mk_cert() {
	openssl req -x509 -newkey ec -pkeyopt ec_paramgen_curve:P-256 -nodes \
		-keyout "$1-key.pem" -out "$1-cert.pem" -subj "/CN=$2" -days 2 \
		-addext "subjectAltName=${3:-DNS:localhost,IP:127.0.0.1}" >/dev/null 2>&1
	chmod 644 "$1-key.pem" "$1-cert.pem"
}

# Creates a CA: mk_ca <prefix> <cn>
mk_ca() {
	openssl req -x509 -newkey ec -pkeyopt ec_paramgen_curve:P-256 -nodes \
		-keyout "$1-key.pem" -out "$1.pem" -subj "/CN=$2" -days 2 \
		-addext basicConstraints=critical,CA:TRUE -addext keyUsage=keyCertSign >/dev/null 2>&1
	chmod 644 "$1-key.pem" "$1.pem"
}

# Issues a server certificate: mk_issued <ca-prefix> <prefix> [san]
mk_issued() {
	openssl req -newkey ec -pkeyopt ec_paramgen_curve:P-256 -nodes \
		-keyout "$2-key.pem" -out "$2.csr" -subj /CN=localhost >/dev/null 2>&1
	printf 'subjectAltName=%s\nbasicConstraints=CA:FALSE\n' "${3:-DNS:localhost,IP:127.0.0.1}" > "$2.ext"
	openssl x509 -req -in "$2.csr" -CA "$1.pem" -CAkey "$1-key.pem" -CAcreateserial \
		-out "$2-cert.pem" -days 2 -extfile "$2.ext" >/dev/null 2>&1
	chmod 644 "$2-key.pem" "$2-cert.pem"
}

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

run() { local name=$1; shift; if "$@"; then report "$name" 0; else report "$name" 1; fi; }

# Prints the TLS protocol and the HTTP body of one request: tls_get <port> <s_client option>...
tls_get() {
	local p=$1
	shift
	printf 'GET /index.html HTTP/1.0\r\n\r\n' |
		timeout 20 openssl s_client -connect "127.0.0.1:$p" -brief -ign_eof "$@" 2>&1
}
