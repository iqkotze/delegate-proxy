#!/usr/bin/env bash
# CI job fuzz, short libFuzzer run of all targets (FUZZ_SECONDS each, default 60) and replay of stored crashes.
# Usage: ci/jobs/fuzz.sh   (corpus and crashes in fuzz-work/, FUZZ_WORK overrides)
. "$(dirname "$0")/common.sh"
install_deps base fuzz
export FUZZ_WORK=${FUZZ_WORK:-$root/fuzz-work}
build_preset fuzz
status=0
tools/fuzz-run.sh -t "${FUZZ_SECONDS:-60}" || status=$?
ctest --test-dir build/fuzz --output-on-failure -L fuzz-regress \
	--output-junit "$root/build/fuzz/junit-fuzz-regress.xml" || status=$?
exit $status
