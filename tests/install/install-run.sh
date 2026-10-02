#!/usr/bin/env bash
# Installs a build into a temporary prefix, starts the installed delegated with the installed example configuration and sends a proxy request.
# Usage: tests/install/install-run.sh <build-dir> [--keep]
set -euo pipefail

here=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
. "$here/../tls/lib.sh"

command -v curl >/dev/null || { echo "SKIP curl not found"; exit 77; }
build=$(readlink -f "${1:?usage: install-run.sh <build-dir> [--keep]}")
tls_setup "$build/delegated" "$([ "${2:-}" = "--keep" ] && echo 1 || echo 0)"

inst=$tmp/inst
cmake --install "$build" --prefix "$inst" >"$tmp/install.log" 2>&1 || { cat "$tmp/install.log"; exit 1; }
conf=$inst/etc/delegate/delegated.conf
new_port; origin=$PORT
new_port; port=$PORT
start_origin "$origin" || { echo "FAIL origin server did not start"; exit 1; }

sed -e "s#^-P8080\$#-P$port#" -e "s#/etc/delegate#$inst/etc/delegate#" \
	-e "s#/var/#$inst/var/#" -e "s#/run/delegate#$inst/run#" \
	"$inst/etc/delegate/delegated.conf.example" >"$conf"
mkdir -p "$inst/run"
chmod -R a+rX "$inst"
if [ "$(id -u)" = 0 ]; then chown -R nobody "$inst/var" "$inst/run"; fi
chmod 755 "$tmp"

setsid env -u SSL_CERT_FILE RES_WAIT=0 RESOLV=file "${drop[@]}" "$inst/sbin/delegated" -f \
	"DGROOT=$inst/var/lib/delegate" "+=$conf" >"$tmp/dg.log" 2>&1 &
pids+=($!)
wait_listen "$port" || { echo "FAIL delegated did not listen"; show_logs; exit 1; }

case_proxy() {
	[ "$(curl -s -m 10 -x "http://127.0.0.1:$port" "http://127.0.0.1:$origin/index.html")" = smoke-ok ]
}
case_paths() {
	[ -n "$(ls "$inst/var/log/delegate")" ] && [ -d "$inst/var/lib/delegate/adm" ] &&
		[ -e "$inst/var/log/delegate/$port" ] && [ ! -e "$inst/var/lib/delegate/log/$port" ] && [ -d "$inst/run/pid" ]
}

run "1 proxy request through the installed delegated" case_proxy
run "2 files below the installed FHS directories" case_paths
echo "failures: $fails"
exit "$fails"
