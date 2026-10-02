#include "dg_test.hpp"
#include <cstdio>

void toMD5X(const char *str, int len, char digest[]);
void ftoMD5(FILE *fp, char md5[]);

namespace {
std::string md5(const char *s) {
	char out[40];
	toMD5(s, out);
	return out;
}
}

/// Test vectors of RFC 1321 appendix A.5.
TEST(Md5, Rfc1321EmptyString) { EXPECT_EQ("d41d8cd98f00b204e9800998ecf8427e", md5("")); }
TEST(Md5, Rfc1321SingleLetter) { EXPECT_EQ("0cc175b9c0f1b6a831c399e269772661", md5("a")); }
TEST(Md5, Rfc1321Abc) { EXPECT_EQ("900150983cd24fb0d6963f7d28e17f72", md5("abc")); }
TEST(Md5, Rfc1321MessageDigest) { EXPECT_EQ("f96b697d7cb7938d525a2f31aaf161d0", md5("message digest")); }
TEST(Md5, Rfc1321LowercaseAlphabet) {
	EXPECT_EQ("c3fcd3d76192e4007dfb496cca67e13b", md5("abcdefghijklmnopqrstuvwxyz"));
}
TEST(Md5, Rfc1321Alphanumeric) {
	EXPECT_EQ("d174ab98d277d9f5a5611c2c9f419d9f",
		md5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"));
}
TEST(Md5, Rfc1321EightyDigits) {
	EXPECT_EQ("57edf4a22be3c955ac49da2e2107b67a",
		md5("12345678901234567890123456789012345678901234567890123456789012345678901234567890"));
}

TEST(Md5, BinaryDigestMatchesHexForm) {
	char digest[16];
	toMD5X("abc", 3, digest);
	static const unsigned char expect[16] = {0x90, 0x01, 0x50, 0x98, 0x3c, 0xd2, 0x4f, 0xb0,
		0xd6, 0x96, 0x3f, 0x7d, 0x28, 0xe1, 0x7f, 0x72};
	EXPECT_EQ(0, memcmp(digest, expect, 16));
}

TEST(Md5, HashesBytesBeyondEmbeddedNul) {
	char a[16], b[16];
	toMD5X("ab\0cd", 5, a);
	toMD5X("ab\0ce", 5, b);
	EXPECT_NE(0, memcmp(a, b, 16));
}

TEST(Md5, FileDigestMatchesStringDigest) {
	FILE *fp = tmpfile();
	ASSERT_NE(nullptr, fp);
	fputs("message digest", fp);
	rewind(fp);
	char out[40];
	ftoMD5(fp, out);
	fclose(fp);
	EXPECT_EQ("f96b697d7cb7938d525a2f31aaf161d0", std::string(out));
}
