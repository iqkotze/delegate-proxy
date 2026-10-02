#!/usr/bin/env bash
# CI job warnings, fails if the warning count exceeds ci/warnings-baseline.txt.
# Usage: ci/jobs/warnings.sh
. "$(dirname "$0")/common.sh"
install_deps base
tools/check-warnings.sh
