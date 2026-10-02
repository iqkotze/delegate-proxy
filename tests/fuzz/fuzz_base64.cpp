#include "fuzz_common.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	std::string in = fuzzString(data, size);
	CStr(dec, 1024);
	str_from64(in.c_str(), (int)in.size(), AVStr(dec), sizeof(dec));
	CStr(enc, 4096);
	str_to64(in.c_str(), (int)in.size(), AVStr(enc), sizeof(enc), 1);
	return 0;
}
