#!/usr/bin/env bash
# Lists the archive members linked into delegated as (libX.a)member.o in <builddir>/linkmap.txt.
# Usage: tools/legacy-linkmap.sh <builddir>   (the OUT directory of build-legacy.sh)
set -euo pipefail

dir=${1:?usage: legacy-linkmap.sh <builddir>}
log=$dir/build.log
src=$dir/delegate/src
[ -f "$log" ] && [ -d "$src" ] || { echo "no build in $dir" >&2; exit 2; }

# ld --trace lists archives but not their members, so the last delegated link is repeated with -Map
cmd=$(grep -E '^[^ ]*(gcc|cc)[^ ]* .* -o dg\.exe ' "$log" | tail -n 1 || true)
[ -n "$cmd" ] || { echo "no link command found in $log" >&2; exit 1; }
cmd=${cmd/ -o dg.exe / -o $dir/relink.out }

map=$dir/link.map
(cd "$src" && eval "$cmd -Wl,-Map=$map" >/dev/null)

awk '
	/^Archive member included/ { on = 1; next }
	on && /^$/ { next }
	on && /^[^ ]/ && /\.a\(.*\)$/ { print $1; next }
	on && /^(Discarded|Memory|As-needed)/ { on = 0 }
' "$map" | sed -E 's|^.*/([^/]+\.a)\(([^)]+)\)$|(\1)\2|' | sort -u > "$dir/linkmap.txt"

rm -f "$dir/relink.out"
echo "$(wc -l < "$dir/linkmap.txt") members -> $dir/linkmap.txt"
