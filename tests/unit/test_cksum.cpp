#include "dg_test.hpp"

int strCRC32(PCStr(str), int len);

namespace {
unsigned cksum(const char *s) { return (unsigned)strCRC32(s, strlen(s)); }
}

/// Expected values are those of POSIX cksum(1).
TEST(Cksum, MatchesPosixCksumOfCheckString) { EXPECT_EQ(930766865u, cksum("123456789")); }
TEST(Cksum, MatchesPosixCksumOfEmptyInput) { EXPECT_EQ(4294967295u, cksum("")); }
TEST(Cksum, MatchesPosixCksumOfSingleByte) { EXPECT_EQ(1220704766u, cksum("a")); }
TEST(Cksum, MatchesPosixCksumOfLine) { EXPECT_EQ(3015617425u, cksum("hello\n")); }
