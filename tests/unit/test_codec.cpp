#include "dg_test.hpp"

namespace {
struct Vector { const char *plain; const char *b64; };
const Vector kRfc4648[] = {
	{"", ""}, {"f", "Zg=="}, {"fo", "Zm8="}, {"foo", "Zm9v"},
	{"foob", "Zm9vYg=="}, {"fooba", "Zm9vYmE="}, {"foobar", "Zm9vYmFy"},
};
}

TEST(Codec, Base64EncodesRfc4648Vectors) {
	for (const auto &v : kRfc4648) {
		CStr(out, 64);
		str_to64(v.plain, strlen(v.plain), AVStr(out), sizeof(out), 0);
		EXPECT_EQ(v.b64, chomp(out)) << "input: " << v.plain;
	}
}

TEST(Codec, Base64DecodesRfc4648Vectors) {
	for (const auto &v : kRfc4648) {
		CStr(out, 64);
		int n = str_from64(v.b64, strlen(v.b64), AVStr(out), sizeof(out));
		EXPECT_EQ((int)strlen(v.plain), n) << "input: " << v.b64;
		EXPECT_STREQ(v.plain, out);
	}
}

TEST(Codec, Base64RoundTripsAllByteValues) {
	char in[255];
	for (int i = 0; i < 255; i++) in[i] = (char)(i + 1);
	CStr(enc, 1024);
	CStr(dec, 512);
	int elen = str_to64(in, sizeof(in), AVStr(enc), sizeof(enc), 0);
	ASSERT_GT(elen, 0);
	int dlen = str_from64(enc, elen, AVStr(dec), sizeof(dec));
	ASSERT_EQ((int)sizeof(in), dlen);
	EXPECT_EQ(0, memcmp(in, dec, sizeof(in)));
}

TEST(Codec, Base64WrapsLongOutputIntoShortLines) {
	std::string in(120, 'x');
	CStr(out, 512);
	str_to64(in.c_str(), in.size(), AVStr(out), sizeof(out), 0);
	size_t line = 0, longest = 0;
	for (const char *p = out; *p; p++) {
		line = (*p == '\n') ? 0 : line + 1;
		longest = std::max(longest, line);
	}
	EXPECT_LE(longest, 76u);
	EXPECT_NE(nullptr, strchr(out, '\n'));
}

TEST(Codec, Base64DecodeIgnoresLineBreaks) {
	CStr(out, 64);
	int n = str_from64("Zm9v\nYmFy\n", 10, AVStr(out), sizeof(out));
	EXPECT_EQ(6, n);
	EXPECT_STREQ("foobar", out);
}

TEST(Codec, QuotedPrintableEncodesEqualSignAndHighBytes) {
	CStr(out, 64);
	str_toqp("a=b c\xe4", 6, AVStr(out), sizeof(out));
	EXPECT_STREQ("a=3Db c=E4", out);
}

TEST(Codec, QuotedPrintableDecodesHexEscapes) {
	CStr(out, 64);
	int n = str_fromqp("a=3Db=41", 8, AVStr(out), sizeof(out));
	EXPECT_EQ(4, n);
	EXPECT_STREQ("a=bA", out);
}
