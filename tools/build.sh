#!/usr/bin/env bash
# Configures, builds and tests delegated with CMake and a preset from delegate/CMakePresets.json.
# Usage: tools/build.sh <preset> [extra cmake -D options]   (CC/CXX select the compiler, the build directory then gets a suffix)
set -euo pipefail

preset=${1:?usage: build.sh <preset> [cmake options]}
shift
root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
dir=${BUILD_DIR:-$root/build/$preset${CC:+-$CC}}

cmake -S "$root/delegate" --preset "$preset" -B "$dir" "$@"
cmake --build "$dir"
ctest --test-dir "$dir" --output-on-failure -j"$(nproc)"
