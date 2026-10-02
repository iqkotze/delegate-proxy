#!/usr/bin/env bash
# Runs clang-tidy or cppcheck on the sources and compares the findings with the baseline in ci/.
# Usage: tools/analyze.sh clang-tidy|cppcheck [--update-baseline]   (report in build/analyze/<tool>.txt)
set -euo pipefail

tool=${1:?usage: analyze.sh clang-tidy|cppcheck [--update-baseline]}
update=${2:-}
root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
dir=$root/build/analyze
jobs=$(nproc)

if [ ! -f "$dir/compile_commands.json" ]; then
	CXX=${CXX:-clang++} cmake -S "$root/delegate" --preset clang -B "$dir" -DDG_BUILD_TESTS=OFF >/dev/null
	cmake --build "$dir" --target dg_builtin_gen dg_params_gen >/dev/null
fi

report=$dir/$tool.txt
files=$(python3 -c "
import json,sys
for e in json.load(open('$dir/compile_commands.json')):
    f=e['file']
    if f.startswith('$root/delegate/'): print(f)
" | sort -u)

case $tool in
clang-tidy)
	# shellcheck disable=SC2086
	echo $files | tr ' ' '\n' | xargs -P"$jobs" -n4 clang-tidy -p "$dir" --quiet 2>/dev/null >"$report" || true ;;
cppcheck)
	cppcheck --project="$dir/compile_commands.json" --enable=warning,portability --inline-suppr \
		--suppress='*:*/build/*' --suppress=missingInclude -j"$jobs" --quiet \
		--template='{file}:{line}:{column}: {severity}: {message} [{id}]' 2>"$report" || true ;;
*) echo "unknown tool $tool" >&2; exit 2 ;;
esac

args=("$report" "$root/ci/$tool-baseline.txt" --root "$root" --codequality "$dir/$tool-codequality.json")
[ "$update" = "--update-baseline" ] && args+=(--update)
python3 "$root/tools/baseline.py" "${args[@]}"
