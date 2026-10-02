#!/usr/bin/env bash
# CI job unit, GoogleTest unit tests of the debug build.
# Usage: ci/jobs/unit.sh
. "$(dirname "$0")/common.sh"
install_deps base
ensure_build debug
run_ctest debug unit -L unit
