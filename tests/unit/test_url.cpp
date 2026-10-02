#include "dg_test.hpp"

int h2toi(PCStr(h2));

TEST(Url, UnescapeDecodesPercentSequences) {
	CStr(out, 64);
	int n = URL_unescape("a%20b%2fc+d", AVStr(out), 0, 0);
	EXPECT_EQ(2, n);
	EXPECT_STREQ("a b/c+d", out);
}

TEST(Url, UnescapeFormDecodesPlusAsSpace) {
	CStr(out, 64);
	URL_unescape("a%20b+c", AVStr(out), 1, 0);
	EXPECT_STREQ("a b c", out);
}

TEST(Url, UnescapeKeepsMalformedSequences) {
	CStr(out, 64);
	URL_unescape("100%zz and 5%", AVStr(out), 0, 0);
	EXPECT_STREQ("100%zz and 5%", out);
}

TEST(Url, NonxalphaUnescapeKeepsWhitespaceByDefault) {
	CStr(out, 64);
	int n = nonxalpha_unescape("a%41%20b", AVStr(out), 0);
	EXPECT_EQ(1, n);
	EXPECT_STREQ("aA%20b", out);
}

TEST(Url, NonxalphaUnescapeDecodesSpaceOnRequest) {
	CStr(out, 64);
	nonxalpha_unescape("a%41%20b", AVStr(out), 1);
	EXPECT_STREQ("aA b", out);
}

TEST(Url, SafeEscapeEncodesMarkupCharacters) {
	CStr(out, 64);
	safe_escapeX("a<b>&\"c", AVStr(out), sizeof(out));
	EXPECT_STREQ("a%3cb%3e%26%22c", out);
}

TEST(Url, EscapeThenUnescapeRestoresOriginal) {
	CStr(esc, 64);
	CStr(back, 64);
	url_escapeX("a b/c?d", AVStr(esc), sizeof(esc), "%?", "");
	EXPECT_NE(nullptr, strstr(esc, "%3f"));
	URL_unescape(esc, AVStr(back), 0, 0);
	EXPECT_STREQ("a b/c?d", back);
}

TEST(Url, HexPairToInteger) {
	EXPECT_EQ(0x7e, h2toi("7e"));
	EXPECT_EQ(255, h2toi("FF"));
	EXPECT_EQ(-1, h2toi("zz"));
}
