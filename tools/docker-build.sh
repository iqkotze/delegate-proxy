#!/usr/bin/env bash
# Builds and tests delegated with a CMake preset inside a compiler image (cmake and ninja come from pip wheels).
# Usage: tools/docker-build.sh <trixie|testing|gcc15|gcc16> [preset]   (starts dockerd if it is not running)
set -euo pipefail

variant=${1:?usage: docker-build.sh <trixie|testing|gcc15|gcc16> [preset]}
preset=${2:-debug}
root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
wheels=$root/tools/.cache/wheels

case "$variant" in
	trixie) image=mirror.gcr.io/library/buildpack-deps:trixie ;;
	testing) image=mirror.gcr.io/library/buildpack-deps:testing ;;
	gcc15) image=mirror.gcr.io/library/gcc:15 ;;
	gcc16) image=mirror.gcr.io/library/gcc:latest ;;
	*) echo "unknown variant: $variant" >&2; exit 2 ;;
esac

if ! docker info >/dev/null 2>&1; then
	echo "starting dockerd" >&2
	nohup dockerd --storage-driver=vfs --iptables=false >/tmp/dockerd.log 2>&1 &
	for _ in $(seq 1 60); do
		docker info >/dev/null 2>&1 && break
		sleep 1
	done
	docker info >/dev/null 2>&1 || { echo "dockerd did not start, see /tmp/dockerd.log" >&2; exit 1; }
fi

if ! ls "$wheels"/cmake-*.whl "$wheels"/ninja-*.whl >/dev/null 2>&1; then
	mkdir -p "$wheels"
	pip3 download cmake ninja --only-binary=:all: --platform manylinux_2_17_x86_64 \
		--platform manylinux2014_x86_64 -d "$wheels"
fi

docker image inspect "$image" >/dev/null 2>&1 || docker pull "$image"

docker run --rm --network none -e PRESET="$preset" -e RES_WAIT=0 -e RESOLV=file \
	-v "$root":/src:ro -v "$wheels":/wheels:ro "$image" bash -euxo pipefail -c '
	for w in /wheels/cmake-*.whl /wheels/ninja-*.whl; do python3 -m zipfile -e "$w" /opt/py; done
	cp -r /opt/py/cmake/data /opt/cmake
	mkdir -p /opt/ninja && cp /opt/py/ninja-*.data/scripts/ninja /opt/ninja/
	chmod +x /opt/cmake/bin/* /opt/ninja/ninja
	export PATH=/opt/cmake/bin:/opt/ninja:$PATH
	cmake --version
	cmake -S /src/delegate --preset "$PRESET" -B /tmp/build
	cmake --build /tmp/build
	ctest --test-dir /tmp/build --output-on-failure
'
