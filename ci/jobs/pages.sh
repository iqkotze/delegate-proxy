#!/usr/bin/env bash
# CI job pages, publishes the Doxygen HTML as public/ for GitLab Pages.
# Usage: ci/jobs/pages.sh
. "$(dirname "$0")/docs.sh"
rm -rf public
cp -r build/debug/docs/html public
