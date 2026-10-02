#!/usr/bin/env bash
# CI job build-trixie-gcc, gcc build of the debug preset.
# Usage: ci/jobs/build-trixie-gcc.sh
. "$(dirname "$0")/common.sh"
install_deps base
build_preset debug
