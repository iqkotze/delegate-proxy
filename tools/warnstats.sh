#!/usr/bin/env bash
# Counts compiler errors and warnings in <builddir>/build.log by category and by file.
# Usage: tools/warnstats.sh <builddir> [top-files]   (default 15 files)
set -euo pipefail

dir=${1:?usage: warnstats.sh <builddir> [top-files]}
top=${2:-15}
log=$dir/build.log
[ -f "$log" ] || { echo "no build.log in $dir" >&2; exit 2; }

tmp=$(mktemp)
trap 'rm -f "$tmp"' EXIT

# Columns: kind, category, file (deduplicated by file, line and column)
grep -E '^[^ :]+:[0-9]+:[0-9]+: (warning|error):' "$log" | sort -u |
	awk '{
		split($1, loc, ":")
		kind = ($2 == "error:") ? "error" : "warning"
		cat = "(none)"
		if (match($0, /\[-W[^]]+\]$/)) cat = substr($0, RSTART + 1, RLENGTH - 2)
		print kind, cat, loc[1]
	}' > "$tmp"

echo "Total"
awk '{ n[$1]++ } END { printf "  errors   %d\n  warnings %d\n", n["error"], n["warning"] }' "$tmp"

echo
echo "By category"
awk '{ n[$1 " " $2]++ } END { for (k in n) print n[k], k }' "$tmp" | sort -rn |
	awk 'BEGIN { printf "  %8s  %-8s  %s\n", "count", "kind", "category" } { printf "  %8d  %-8s  %s\n", $1, $2, $3 }'

echo
echo "By file (top $top)"
awk '{ n[$3]++ } END { for (k in n) print n[k], k }' "$tmp" | sort -rn | head -n "$top" |
	awk 'BEGIN { printf "  %8s  %s\n", "count", "file" } { printf "  %8d  %s\n", $1, $2 }'
