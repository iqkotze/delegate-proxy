#!/usr/bin/env bash
# Installs the apt packages of the given groups in CI (base clang tidy cppcheck coverage docs fuzz load).
# Usage: ci/jobs/install-deps.sh <group>...   (outside CI it only prints the packages unless DG_INSTALL_DEPS=1)
set -euo pipefail

root=$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)
pkgs=()
for g in "$@"; do
	case $g in
	base) pkgs+=(build-essential cmake ninja-build pkg-config libssl-dev zlib1g-dev libgtest-dev
		python3 curl openssl util-linux ca-certificates git ccache) ;;
	clang) pkgs+=(clang) ;;
	tidy) pkgs+=(clang clang-tidy) ;;
	cppcheck) pkgs+=(clang cppcheck) ;;
	coverage) pkgs+=(gcovr) ;;
	docs) pkgs+=(doxygen graphviz) ;;
	fuzz) pkgs+=(clang) ;;
	load) pkgs+=(wrk) ;;
	*) echo "unknown group $g" >&2; exit 2 ;;
	esac
done

if [ -z "${CI:-}" ] && [ "${DG_INSTALL_DEPS:-0}" != 1 ]; then
	echo "install-deps: skipped outside CI, packages ${pkgs[*]}"
	exit 0
fi

cache=$root/.apt-cache
mkdir -p "$cache/archives/partial"
rm -f /etc/apt/apt.conf.d/docker-clean
opts=(-o "Dir::Cache::archives=$cache/archives" -o APT::Keep-Downloaded-Packages=true)
apt-get "${opts[@]}" update -qq
apt-get "${opts[@]}" install -y -qq --no-install-recommends "${pkgs[@]}"

# libFuzzer lives in a versioned runtime package
for g in "$@"; do
	if [ "$g" = fuzz ]; then
		lib=$(clang --print-file-name=libclang_rt.fuzzer-x86_64.a)
		if [ ! -f "$lib" ]; then
			ver=$(clang --version | sed -n 's/.*version \([0-9]*\)\..*/\1/p' | head -n 1)
			apt-get "${opts[@]}" install -y -qq --no-install-recommends "libclang-rt-$ver-dev"
		fi
	fi
done
