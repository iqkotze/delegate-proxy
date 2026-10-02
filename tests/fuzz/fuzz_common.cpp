#include "fuzz_common.hpp"

void minit_logs();

/// Allocates the log environment that ERRMSG and the log functions need.
extern "C" int LLVMFuzzerInitialize(int *, char ***) {
	minit_logs();
	return 0;
}
