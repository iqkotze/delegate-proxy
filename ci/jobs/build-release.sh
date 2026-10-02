#!/usr/bin/env bash
# CI job build-release, release preset with LTO.
# Usage: ci/jobs/build-release.sh
. "$(dirname "$0")/common.sh"
install_deps base
build_preset release
