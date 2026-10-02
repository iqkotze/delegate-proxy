#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "global.h"
#include "md5.h"

static_assert(sizeof(UINT2) == 2);
static_assert(sizeof(UINT4) == 4);
static_assert(sizeof(MD5_CTX) == 88);

TEST(Md5Types, LegacyWordSizeDefineIsNotNeeded) {
#ifdef m64
	FAIL() << "m64 must not be defined";
#endif
	EXPECT_EQ(4u, sizeof(UINT4));
}

TEST(Md5Types, ContextDigestMatchesRfc1321Vector) {
	MD5_CTX ctx;
	unsigned char digest[16];
	unsigned char msg[] = "abc";
	MD5Init(&ctx);
	MD5Update(&ctx, msg, 3);
	MD5Final(digest, &ctx);
	char hex[33];
	for (int i = 0; i < 16; i++) snprintf(hex + i * 2, 3, "%02x", digest[i]);
	EXPECT_STREQ("900150983cd24fb0d6963f7d28e17f72", hex);
}
