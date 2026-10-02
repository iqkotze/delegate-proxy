#!/usr/bin/env bash
# Configures, builds and tests delegated with CMake and a preset from delegate/CMakePresets.json.
# Usage: tools/build.sh [preset] [extra cmake -D options]   (preset defaults to debug; CC/CXX select the compiler, the build directory then gets a suffix)
set -euo pipefail

preset=${1:-debug}
if [ $# -gt 0 ]; then shift; fi
root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
dir=${BUILD_DIR:-$root/build/$preset${CC:+-$CC}}

cmake -S "$root/delegate" --preset "$preset" -B "$dir" "$@"
cmake --build "$dir" 2>&1 | tee "$dir/build.log"
ctest --test-dir "$dir" --output-on-failure -j"$(nproc)"
