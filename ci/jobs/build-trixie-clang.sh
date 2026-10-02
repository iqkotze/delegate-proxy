#!/usr/bin/env bash
# CI job build-trixie-clang, clang build of the clang preset.
# Usage: ci/jobs/build-trixie-clang.sh
. "$(dirname "$0")/common.sh"
install_deps base clang
build_preset clang
