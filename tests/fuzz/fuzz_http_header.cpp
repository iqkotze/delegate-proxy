#include "fuzz_common.hpp"
#include "delegate.h"
#include "http.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	std::string in = fuzzString(data, size);
	CStr(value, 256);
	getFieldValue2(in.c_str(), "Content-Type", AVStr(value), sizeof(value));
	getFieldValue2(in.c_str(), "Host", AVStr(value), sizeof(value));
	CStr(name, 64);
	CStr(body, 256);
	scan_field1(in.c_str(), AVStr(name), sizeof(name), AVStr(body), sizeof(body));
	CStr(atype, 32);
	CStr(aval, 256);
	HTTP_decompAuth(in.c_str(), AVStr(atype), sizeof(atype), AVStr(aval), sizeof(aval));
	return 0;
}
