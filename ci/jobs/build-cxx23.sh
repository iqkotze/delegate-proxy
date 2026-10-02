#!/usr/bin/env bash
# CI job build-cxx23, build of the cxx23 preset.
# Usage: ci/jobs/build-cxx23.sh
. "$(dirname "$0")/common.sh"
install_deps base
build_preset cxx23
