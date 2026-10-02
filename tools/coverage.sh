#!/usr/bin/env bash
# Builds with gcc --coverage, runs the tests and writes gcovr reports to build/coverage/report.
# Usage: tools/coverage.sh   (cobertura.xml and html/index.html; line and function coverage on stdout)
set -euo pipefail

root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
dir=$root/build/coverage
out=$dir/report

cmake -S "$root/delegate" --preset coverage -B "$dir" >/dev/null
cmake --build "$dir" >"$dir/build.log" 2>&1
find "$dir" -name '*.gcda' -delete
ctest --test-dir "$dir" --output-on-failure -j"$(nproc)"

mkdir -p "$out/html"
gcovr --root "$root" --filter "$root/delegate/" --exclude-unreachable-branches --exclude-throw-branches \
	--gcov-ignore-parse-errors=all --gcov-ignore-errors=no_working_dir_found \
	--cobertura-pretty --output "$out/cobertura.xml" \
	--html-details "$out/html/index.html" --txt "$out/summary.txt" --print-summary "$dir"
