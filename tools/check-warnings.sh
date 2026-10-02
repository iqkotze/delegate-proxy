#!/usr/bin/env bash
# Builds with extra warnings and fails if the warning count exceeds ci/warnings-baseline.txt.
# Usage: tools/check-warnings.sh [--update-baseline]   (log in build/warnings/build.log)
set -euo pipefail

root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
dir=$root/build/warnings
baseline=$root/ci/warnings-baseline.txt

cmake -S "$root/delegate" --preset debug -B "$dir" -DDG_EXTRA_WARNINGS=ON -DDG_BUILD_TESTS=OFF >/dev/null
cmake --build "$dir" --clean-first >"$dir/build.log" 2>&1
stats=$("$root/tools/warnstats.sh" "$dir")
echo "$stats" | sed -n 1,3p
count=$(echo "$stats" | awk '$1 == "warnings" { print $2; exit }')
if [ "${1:-}" = "--update-baseline" ]; then
	echo "$count" >"$baseline"
	echo "baseline updated to $count"
	exit 0
fi
base=$(cat "$baseline")
echo "warnings $count, baseline $base"
[ "$count" -le "$base" ]
