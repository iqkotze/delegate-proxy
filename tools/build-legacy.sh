#!/usr/bin/env bash
# Builds a copy of delegate/ with the legacy make system and logs the link trace.
# Usage: tools/build-legacy.sh <cc>   (gcc or gcc-14). Env OUT=<dir> sets the target, DG_CFLAGS the C flags.
set -euo pipefail

cc=${1:?usage: build-legacy.sh <cc>}
root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
out=${OUT:-/tmp/dg-legacy-$cc}
cxx=${cc/gcc/g++}

command -v "$cc" >/dev/null || { echo "compiler not found: $cc" >&2; exit 2; }
command -v "$cxx" >/dev/null || { echo "compiler not found: $cxx" >&2; exit 2; }

rm -rf "$out"
mkdir -p "$out"
if command -v rsync >/dev/null; then
	rsync -a "$root/delegate/" "$out/delegate/"
else
	cp -a "$root/delegate" "$out/delegate"
fi
echo "ADMIN=root@localhost" > "$out/delegate/DELEGATE_CONF"

cd "$out/delegate"
export CC="$cc" CXX="$cxx"
if make CC="$cc" CFLAGS="${DG_CFLAGS:--O2 -Wno-narrowing}" ADMIN=root@localhost LDOPTS="-Wl,--trace" </dev/null > "$out/build.log" 2>&1; then
	rc=0
else
	rc=$?
fi

if [ "$rc" -eq 0 ] && [ -x src/delegated ]; then
	echo "OK $out/delegate/src/delegated"
else
	echo "FAILED (rc=$rc), see $out/build.log" >&2
	tail -n 20 "$out/build.log" >&2
	exit 1
fi
