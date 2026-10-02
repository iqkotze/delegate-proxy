#include "fuzz_common.hpp"

#include "dglib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	std::string in = fuzzString(data, size);
	CStr(proto, 64);
	CStr(site, 256);
	CStr(upath, 1024);
	decomp_absurl(in.c_str(), AVStr(proto), AVStr(site), AVStr(upath), 1024);
	CStr(userpasshost, 256);
	CStr(port, 32);
	decomp_URL_site(in.c_str(), AVStr(userpasshost), AVStr(port));
	return 0;
}
