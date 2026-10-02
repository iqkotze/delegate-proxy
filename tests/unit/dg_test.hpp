#pragma once
#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "ystring.h"

/// Strips one trailing newline from library output.
inline std::string chomp(const char *s) {
	std::string r(s);
	if (!r.empty() && r.back() == '\n') r.pop_back();
	return r;
}
