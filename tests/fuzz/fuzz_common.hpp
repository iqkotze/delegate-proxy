#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include "ystring.h"

/// Copies the fuzzer input into a NUL-terminated string.
inline std::string fuzzString(const uint8_t *data, size_t size) {
	return std::string(reinterpret_cast<const char *>(data), size);
}
