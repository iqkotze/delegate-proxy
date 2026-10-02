#!/usr/bin/env bash
# Runs the libFuzzer targets of a fuzz build for a fixed time each.
# Usage: tools/fuzz-run.sh [-t seconds] [-b builddir] [target...]   (default 60 s, build/fuzz, all targets)
set -uo pipefail

root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
secs=60
dir=$root/build/fuzz
while getopts "t:b:" o; do
	case $o in t) secs=$OPTARG ;; b) dir=$OPTARG ;; *) exit 2 ;; esac
done
shift $((OPTIND - 1))

bindir=$dir/tests/fuzz
work=${FUZZ_WORK:-$dir/fuzz-work}
targets=("$@")
if [ ${#targets[@]} -eq 0 ]; then
	for f in "$bindir"/fuzz_*; do [ -x "$f" ] && targets+=("$(basename "$f" | sed 's/^fuzz_//')"); done
fi
[ ${#targets[@]} -gt 0 ] || { echo "no fuzz targets in $bindir" >&2; exit 2; }

fail=0
for t in "${targets[@]}"; do
	mkdir -p "$work/corpus/$t" "$work/crashes/$t"
	echo "== fuzz_$t ($secs s)"
	"$bindir/fuzz_$t" -max_total_time="$secs" -timeout=10 -rss_limit_mb=2048 \
		-artifact_prefix="$work/crashes/$t/" "$work/corpus/$t" "$root/tests/fuzz/corpus/$t" \
		2>&1 | tee "$work/$t.log" | tail -n 6
	if [ "${PIPESTATUS[0]}" -ne 0 ]; then echo "FAILED fuzz_$t"; fail=1; fi
done
exit $fail
