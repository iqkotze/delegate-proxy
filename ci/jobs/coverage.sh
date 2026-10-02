#!/usr/bin/env bash
# CI job coverage, gcc coverage run with gcovr reports in build/coverage/report.
# Usage: ci/jobs/coverage.sh
. "$(dirname "$0")/common.sh"
install_deps base coverage
tools/coverage.sh
