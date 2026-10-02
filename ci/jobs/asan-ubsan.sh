#!/usr/bin/env bash
# CI job asan-ubsan, all tests with AddressSanitizer and UBSan.
# Usage: ci/jobs/asan-ubsan.sh
. "$(dirname "$0")/common.sh"
install_deps base
build_preset asan
run_ctest asan asan
