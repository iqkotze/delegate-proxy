# Shared helpers for the CI job scripts (sourced, not run).
root=$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)
cd "$root"
set -euo pipefail

export CCACHE_DIR=${CCACHE_DIR:-$root/.ccache}
command -v ccache >/dev/null 2>&1 && export CMAKE_CXX_COMPILER_LAUNCHER=ccache
jobs=$(nproc)

# Installs the packages of the given groups, see install-deps.sh
install_deps() { "$root/ci/jobs/install-deps.sh" "$@"; }

# Configures and builds a preset into build/<dir> (dir defaults to the preset name)
build_preset() {
	local preset=$1 dir=${2:-$1}
	shift 2 || shift $#
	cmake -S delegate --preset "$preset" -B "build/$dir" "$@"
	cmake --build "build/$dir" 2>&1 | tee "build/$dir/build.log"
}

# Builds the preset unless a delegated binary of an earlier job is present
ensure_build() {
	local preset=$1
	[ -x "build/$preset/delegated" ] || build_preset "$preset"
}

# Runs ctest in build/<dir> with a JUnit report build/<dir>/junit-<name>.xml
run_ctest() {
	local dir=$1 name=$2
	shift 2
	ctest --test-dir "build/$dir" --output-on-failure -j"$jobs" \
		--output-junit "$root/build/$dir/junit-$name.xml" "$@"
}
