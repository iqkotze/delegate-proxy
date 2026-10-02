#include "fuzz_common.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	std::string in = fuzzString(data, size);
	CStr(dec, 512);
	MIME_strHeaderDecode(in.c_str(), AVStr(dec), sizeof(dec));
	CStr(enc, 1024);
	MIME_strHeaderEncode(in.c_str(), AVStr(enc), sizeof(enc));
	CStr(strip, 512);
	RFC822_strip_commentX(in.c_str(), AVStr(strip), sizeof(strip));
	return 0;
}
