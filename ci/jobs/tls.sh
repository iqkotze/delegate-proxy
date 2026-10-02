#!/usr/bin/env bash
# CI job tls, TLS integration tests of the debug build.
# Usage: ci/jobs/tls.sh
. "$(dirname "$0")/common.sh"
install_deps base
ensure_build debug
run_ctest debug tls -L tls
