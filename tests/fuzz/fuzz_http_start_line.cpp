#include "fuzz_common.hpp"
#include "delegate.h"
#include "http.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	std::string in = fuzzString(data, size);
	HttpRequest req;
	decomp_http_request(in.c_str(), &req);
	HttpResponse res;
	decomp_http_status(in.c_str(), &res);
	return 0;
}
