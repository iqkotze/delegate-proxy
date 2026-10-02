#!/usr/bin/env bash
# CI job smoke, smoke test of the debug build.
# Usage: ci/jobs/smoke.sh
. "$(dirname "$0")/common.sh"
install_deps base
ensure_build debug
run_ctest debug smoke -R "^smoke$"
