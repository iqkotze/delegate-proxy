#!/usr/bin/env bash
# CI job cppcheck, fails on findings above ci/cppcheck-baseline.txt.
# Usage: ci/jobs/cppcheck.sh
. "$(dirname "$0")/common.sh"
install_deps base cppcheck
tools/analyze.sh cppcheck
