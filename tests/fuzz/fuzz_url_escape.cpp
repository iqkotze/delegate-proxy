#include "fuzz_common.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	if (size < 1) return 0;
	int flag = data[0] & 1;
	std::string in = fuzzString(data + 1, size - 1);
	CStr(out, 4096);
	URL_unescape(in.c_str(), AVStr(out), flag, 0);
	nonxalpha_unescape(in.c_str(), AVStr(out), flag);
	url_escapeX(in.c_str(), AVStr(out), sizeof(out), "%?", "");
	safe_escapeX(in.c_str(), AVStr(out), sizeof(out));
	return 0;
}
