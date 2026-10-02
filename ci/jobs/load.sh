#!/usr/bin/env bash
# CI job load, load test with 1200 connections via ctest label load.
# Usage: ci/jobs/load.sh
. "$(dirname "$0")/common.sh"
install_deps base load
build_preset release release-load -DDG_LOAD_TESTS=ON
run_ctest release-load load -L load
