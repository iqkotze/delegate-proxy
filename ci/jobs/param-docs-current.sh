#!/usr/bin/env bash
# CI job param-docs-current, fails if doc/reference/parameters.md differs from the generated file.
# Usage: ci/jobs/param-docs-current.sh
. "$(dirname "$0")/common.sh"
install_deps base
tmp=$(mktemp)
trap 'rm -f "$tmp"' EXIT
python3 tools/gen-params.py --root . --md "$tmp"
diff -u doc/reference/parameters.md "$tmp"
