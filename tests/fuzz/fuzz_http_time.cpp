#include "fuzz_common.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	std::string in = fuzzString(data, size);
	scanHTTPtime(in.c_str());
	return 0;
}
