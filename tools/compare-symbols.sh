#!/usr/bin/env bash
# Compares a legacy delegated with a CMake build (exported symbols and linked archive members).
# Usage: tools/compare-symbols.sh <legacy-dir> <cmake-build-dir>   (legacy-dir holds delegated and linkmap.txt)
set -euo pipefail

old=${1:?usage: compare-symbols.sh <legacy-dir> <cmake-build-dir>}
new=${2:?usage: compare-symbols.sh <legacy-dir> <cmake-build-dir>}

ob=$old/delegated
[ -x "$ob" ] || ob=$old/delegate/src/delegated
[ -x "$ob" ] || { echo "no delegated in $old" >&2; exit 2; }
[ -x "$new/delegated" ] || { echo "no delegated in $new" >&2; exit 2; }
[ -f "$old/linkmap.txt" ] || { echo "no linkmap.txt in $old" >&2; exit 2; }
[ -f "$new/delegated.map" ] || { echo "no delegated.map in $new" >&2; exit 2; }

tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT

# CMake archive names to legacy archive names
sed -nE 's#^(.*/)?libdg_([a-z0-9]+)\.a\(([^)]+)\).*#\2 \3#p' "$new/delegated.map" |
	awk '
	BEGIN { m["core"]="libdelegate.a"; m["rary"]="library.a"; m["resolvy"]="libresolvy.a";
		m["teleport"]="libteleport.a"; m["md5"]="libmd5.a"; m["cfi"]="libcfi.a";
		m["gates"]="libgates.a"; m["mimekit"]="libmimekit.a"; m["fsx"]="libfsx.a";
		m["subst"]="libsubst.a" }
	{ sub(/\.c\.o$/, ".o", $2); print "(" m[$1] ")" $2 }' | sort -u > "$tmp/lm.new"
grep -v '^(libdelegate.a)srcsign.o$' "$old/linkmap.txt" | sort -u > "$tmp/lm.old"
grep -v '^(libdelegate.a)srcsign.o$' "$tmp/lm.new" > "$tmp/lm.new2"

nm --defined-only -g "$ob" | awk '{print $NF}' | sort -u > "$tmp/sym.old"
nm --defined-only -g "$new/delegated" | awk '{print $NF}' | sort -u > "$tmp/sym.new"

missing_lm=$(comm -23 "$tmp/lm.old" "$tmp/lm.new2")
extra_lm=$(comm -13 "$tmp/lm.old" "$tmp/lm.new2")
missing_sym=$(comm -23 "$tmp/sym.old" "$tmp/sym.new")
extra_sym=$(comm -13 "$tmp/sym.old" "$tmp/sym.new")

echo "Archive members: legacy $(wc -l < "$tmp/lm.old"), cmake $(wc -l < "$tmp/lm.new2")"
echo "Symbols: legacy $(wc -l < "$tmp/sym.old"), cmake $(wc -l < "$tmp/sym.new")"
show() {
	echo "$1"
	if [ -n "$2" ]; then echo "$2" | sed 's/^/  /'; fi
}
show "Members only in legacy" "$missing_lm"
show "Members only in cmake" "$extra_lm"
show "Symbols missing in cmake" "$missing_sym"
show "Symbols only in cmake" "$extra_sym"
[ -z "$missing_sym" ]
