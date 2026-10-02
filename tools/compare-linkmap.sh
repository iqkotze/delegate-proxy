#!/usr/bin/env bash
# Compares linkmap.txt and the exported symbols of delegated in two build directories.
# Usage: tools/compare-linkmap.sh <alt> <neu>   (directories with linkmap.txt; delegated is taken from <dir>/delegated or <dir>/delegate/src/delegated)
set -euo pipefail

old=${1:?usage: compare-linkmap.sh <alt> <neu>}
new=${2:?usage: compare-linkmap.sh <alt> <neu>}

bin() {
	for p in "$1/delegated" "$1/delegate/src/delegated"; do
		[ -x "$p" ] && { echo "$p"; return; }
	done
	echo "no delegated in $1" >&2
	return 1
}

for d in "$old" "$new"; do
	[ -f "$d/linkmap.txt" ] || { echo "no linkmap.txt in $d" >&2; exit 2; }
done
ob=$(bin "$old")
nb=$(bin "$new")

tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT

sort -u "$old/linkmap.txt" > "$tmp/lm.old"
sort -u "$new/linkmap.txt" > "$tmp/lm.new"
nm --defined-only -g "$ob" | awk '{print $NF}' | sort -u > "$tmp/sym.old"
nm --defined-only -g "$nb" | awk '{print $NF}' | sort -u > "$tmp/sym.new"

echo "Linkmap members only in $old"
comm -23 "$tmp/lm.old" "$tmp/lm.new" | sed 's/^/  /'
echo "Linkmap members only in $new"
comm -13 "$tmp/lm.old" "$tmp/lm.new" | sed 's/^/  /'
echo "Exported symbols only in $old"
comm -23 "$tmp/sym.old" "$tmp/sym.new" | sed 's/^/  /'
echo "Exported symbols only in $new"
comm -13 "$tmp/sym.old" "$tmp/sym.new" | sed 's/^/  /'
