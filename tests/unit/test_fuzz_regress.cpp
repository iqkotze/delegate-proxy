#include "dg_test.hpp"
#include <fstream>
#include <iterator>
#include "delegate.h"
#include "http.h"

void minit_logs();

namespace {
class LogEnv : public ::testing::Environment {
public:
	void SetUp() override { minit_logs(); }
};
const auto *const kLogEnv = ::testing::AddGlobalTestEnvironment(new LogEnv);

std::string readCrash(const char *rel) {
	std::ifstream f(std::string(DG_CRASH_DIR) + "/" + rel, std::ios::binary);
	return std::string(std::istreambuf_iterator<char>(f), {});
}
}

TEST(FuzzRegress, Base64EncodeTruncatesFuzzInput) {
	std::string in = readCrash("base64/crash-09fa7c260d35");
	ASSERT_FALSE(in.empty());
	CStr(out, 4096);
	int n = str_to64(in.c_str(), (int)in.size(), AVStr(out), sizeof(out), 1);
	EXPECT_LT(n, (int)sizeof(out));
	EXPECT_EQ(n, (int)strlen(out));
}

TEST(FuzzRegress, Base64EncodeTruncatesLongInput) {
	std::string in(4000, 'A');
	CStr(out, 4096);
	int n = str_to64(in.c_str(), (int)in.size(), AVStr(out), sizeof(out), 1);
	EXPECT_EQ(4095, n);
	EXPECT_EQ(4095, (int)strlen(out));
}

TEST(FuzzRegress, Base64DecodeKeepsBufferBounds) {
	std::string in(2000, 'Q');
	CStr(out, 64);
	int n = str_from64(in.c_str(), (int)in.size(), AVStr(out), sizeof(out));
	EXPECT_LT(n, (int)sizeof(out));
	EXPECT_EQ(n, (int)strlen(out));
}

TEST(FuzzRegress, HttpAuthKeepsBufferBounds) {
	std::string in = readCrash("http_header/crash-0ef8e9f6cff0");
	ASSERT_FALSE(in.empty());
	CStr(atype, 32);
	CStr(aval, 256);
	HTTP_decompAuth(in.c_str(), AVStr(atype), sizeof(atype), AVStr(aval), sizeof(aval));
	EXPECT_LT(strlen(atype), sizeof(atype));
	EXPECT_LT(strlen(aval), sizeof(aval));
}

TEST(FuzzRegress, HttpAuthTruncatesLongType) {
	std::string in = std::string(100, 'a') + " " + std::string(600, 'b');
	CStr(atype, 32);
	CStr(aval, 256);
	HTTP_decompAuth(in.c_str(), AVStr(atype), sizeof(atype), AVStr(aval), sizeof(aval));
	EXPECT_LT(strlen(atype), sizeof(atype));
}
