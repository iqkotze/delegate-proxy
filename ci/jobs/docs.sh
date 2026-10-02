#!/usr/bin/env bash
# CI job docs, Doxygen HTML in build/debug/docs/html.
# Usage: ci/jobs/docs.sh
. "$(dirname "$0")/common.sh"
install_deps base docs
cmake -S delegate --preset debug -B build/debug
cmake --build build/debug --target docs
