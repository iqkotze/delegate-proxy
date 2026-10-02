#include "fuzz_common.hpp"

#include "delegate.h"
void scan_MAXIMA(Connection *Conn, PCStr(maxima));

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	std::string in = fuzzString(data, size);
	scan_MAXIMA(nullptr, in.c_str());
	kmxatoi(in.c_str());
	return 0;
}
