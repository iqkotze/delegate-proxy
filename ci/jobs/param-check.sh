#!/usr/bin/env bash
# CI job param-check, consistency check of the parameter declarations.
# Usage: ci/jobs/param-check.sh
. "$(dirname "$0")/common.sh"
install_deps base
ensure_build debug
run_ctest debug param-check -R "^param-check$"
