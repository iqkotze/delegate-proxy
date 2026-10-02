#!/usr/bin/env bash
# CI job build-testing-gcc, gcc build of the debug preset (image debian:testing).
# Usage: ci/jobs/build-testing-gcc.sh
. "$(dirname "$0")/common.sh"
install_deps base
build_preset debug debug-testing
