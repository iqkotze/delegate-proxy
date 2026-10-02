#!/usr/bin/env bash
# CI job clang-tidy, fails on findings above ci/clang-tidy-baseline.txt.
# Usage: ci/jobs/clang-tidy.sh
. "$(dirname "$0")/common.sh"
install_deps base tidy
tools/analyze.sh clang-tidy
