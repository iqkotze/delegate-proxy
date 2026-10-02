#include "dg_test.hpp"

int uudec_body(PCStr(src), PVStr(dst));

TEST(Uu, DecodesLine) {
	CStr(out, 64);
	EXPECT_EQ(3, uudec_body("#86)C", AVStr(out)));
	EXPECT_STREQ("abc", out);
}

TEST(Uu, DecodesZeroBytesWrittenAsBackquote) {
	CStr(out, 64);
	EXPECT_EQ(4, uudec_body("$````", AVStr(out)));
	EXPECT_EQ(0, out[0]);
}

TEST(Uu, RejectsInvalidLengthCharacter) {
	CStr(out, 64);
	EXPECT_EQ(-1, uudec_body("\x7f", AVStr(out)));
}
