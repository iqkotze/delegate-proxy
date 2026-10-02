#!/bin/sh
# CI job docker, builds the images of ci/docker/ (pushes them when DG_PUSH_IMAGES=1 and a registry is set).
# Usage: ci/jobs/docker.sh   (needs a Docker daemon)
set -eu
cd "$(dirname "$0")/../.."

for v in trixie testing; do
	tag=${CI_REGISTRY_IMAGE:-delegate-build}/build-$v:${CI_COMMIT_SHORT_SHA:-local}
	docker build -f "ci/docker/Dockerfile.$v" -t "$tag" .
	if [ "${DG_PUSH_IMAGES:-0}" = 1 ] && [ -n "${CI_REGISTRY:-}" ]; then
		echo "$CI_JOB_TOKEN" | docker login -u "$CI_REGISTRY_USER" --password-stdin "$CI_REGISTRY"
		docker push "$tag"
	fi
done
