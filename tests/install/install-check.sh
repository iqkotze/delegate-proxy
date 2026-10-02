#!/usr/bin/env bash
# Installs a build into a temporary prefix and checks file list, modes, unit and configuration paths.
# Usage: tests/install/install-check.sh <build-dir> [--keep]
set -euo pipefail

here=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
repo=$(cd "$here/../.." && pwd)
build=$(readlink -f "${1:?usage: install-check.sh <build-dir> [--keep]}")
tmp=$(mktemp -d /tmp/dg-install.XXXXXX)
trap '[ "${2:-}" = --keep ] && echo "kept $tmp" || rm -rf "$tmp"' EXIT
inst=$tmp/inst
fails=0

fail() { echo "FAIL $*"; fails=$((fails + 1)); }

cmake --install "$build" --prefix "$inst" >"$tmp/install.log" 2>&1 || { cat "$tmp/install.log"; exit 1; }
grep -q 'delegated.conf.example to delegated.conf' "$tmp/install.log" || fail "install hint missing"

expected=$tmp/expected
{
	echo sbin/delegated
	echo etc/delegate/delegated.conf.example
	echo lib/systemd/system/delegated.service
	echo lib/sysusers.d/delegate.conf
	echo lib/tmpfiles.d/delegate.conf
	echo share/man/man8/delegated.8
	echo share/doc/delegate/CHANGELOG.md
	[ -f "$repo/README.md" ] && echo share/doc/delegate/README.md
	(cd "$repo/doc" && { find reference examples -type f 2>/dev/null || true; } | sed 's#^#share/doc/delegate/#')
	if grep -q '^DG_BUILD_SUBIN:BOOL=ON' "$build/CMakeCache.txt"; then
		for p in dgbind dgchroot dgcpnod dgdate dgforkpty dgpam; do echo "lib/delegate/$p"; done
	fi
	echo var/lib/delegate/
	echo var/log/delegate/
	echo var/cache/delegate/
} | sort >"$expected"

(cd "$inst" && { find . -type f; find . -type d -empty -printf '%p/\n'; } | sed 's#^\./##' | sort) >"$tmp/actual"
diff -u "$expected" "$tmp/actual" || fail "file list differs"

[ -x "$inst/sbin/delegated" ] || fail "delegated is not executable"
if grep -q '^DG_INSTALL_SETUID:BOOL=ON' "$build/CMakeCache.txt"; then
	[ "$(find "$inst" -perm -6000 -printf '%f\n' | sort | tr '\n' ' ')" = "dgbind dgchroot dgpam " ] || fail "setuid helpers"
else
	[ -z "$(find "$inst" -perm /6000)" ] || fail "setuid or setgid bit set"
fi
for d in lib log cache; do
	[ "$(stat -c %a "$inst/var/$d/delegate")" = 750 ] || fail "mode of var/$d/delegate"
done

conf=$repo/contrib/etc/delegated.conf
unit=$repo/contrib/systemd/delegated.service
tmpf=$repo/contrib/systemd/delegate.tmpfiles
rw=$(sed -n 's/^ReadWritePaths=//p' "$unit")
for key in LOGDIR CACHEDIR CERTDIR; do
	path=$(sed -n "s/^$key=//p" "$conf")
	grep -qw -- "$path" <<<"$rw" || fail "$key $path is not in ReadWritePaths"
	grep -q "^d $path " "$tmpf" || fail "$key $path is not in the tmpfiles snippet"
done
run=$(sed -n 's/^ACTDIR=//p' "$conf")
grep -q "^RuntimeDirectory=${run#/run/}\$" "$unit" || fail "ACTDIR $run does not match RuntimeDirectory"
grep -q "^ExecStart=/usr/sbin/delegated .*+=/etc/delegate/delegated.conf" "$unit" || fail "ExecStart"
grep -q '^LimitNOFILE=65536$' "$unit" || fail "LimitNOFILE"
grep -q '^u delegate ' "$repo/contrib/systemd/delegate.sysusers" || fail "sysusers entry"

if command -v systemd-analyze >/dev/null; then
	sed "s#/usr/sbin/delegated#$inst/sbin/delegated#; s#^ConditionPathExists=.*##" "$unit" >"$tmp/delegated.service"
	if ! systemd-analyze verify "$tmp/delegated.service" >"$tmp/verify.log" 2>&1; then
		cat "$tmp/verify.log"
		fail "systemd-analyze verify"
	elif grep -v 'User\|Group' "$tmp/verify.log" | grep -q .; then
		cat "$tmp/verify.log"
		fail "systemd-analyze verify output"
	fi
else
	echo "SKIP systemd-analyze not found"
fi

echo "failures: $fails"
exit "$fails"
