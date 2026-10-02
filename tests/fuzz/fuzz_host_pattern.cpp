#include "fuzz_common.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	std::string in = fuzzString(data, size);
	size_t cut = in.find('\n');
	std::string pat = in.substr(0, cut);
	std::string str = cut == std::string::npos ? "" : in.substr(cut + 1);
	rexpmatch(pat.c_str(), str.c_str());
	rexpmatchX(pat.c_str(), str.c_str(), "c");
	return 0;
}
