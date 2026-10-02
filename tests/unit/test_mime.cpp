#include "dg_test.hpp"

int getParam(PVStr(params), PCStr(name), PVStr(val), int siz, int del);

namespace {
const char *kHead =
	"Subject: hi\nTo: a@b\nContent-Type: text/plain; charset=us-ascii\n\nbody";
}

TEST(Mime, FindFieldIsCaseInsensitive) {
	const char *value = nullptr;
	char *f = findField(kHead, "to", &value);
	ASSERT_NE(nullptr, f);
	EXPECT_EQ(0, strncmp(f, "To:", 3));
	EXPECT_EQ(0, strncmp(value, "a@b", 3));
}

TEST(Mime, FindFieldReturnsNullForMissingField) {
	EXPECT_EQ(nullptr, findField(kHead, "Cc", nullptr));
}

TEST(Mime, FindFieldValueSkipsFieldName) {
	char *v = findFieldValue(kHead, "Subject");
	ASSERT_NE(nullptr, v);
	EXPECT_EQ(0, strncmp(v, "hi\n", 3));
}

TEST(Mime, FieldValueIsExtracted) {
	CStr(val, 64);
	getFieldValue2(kHead, "Content-Type", AVStr(val), sizeof(val));
	EXPECT_STREQ("text/plain; charset=us-ascii", val);
}

TEST(Mime, RemoveFieldDeletesTheLine) {
	CStr(head, 256);
	strcpy(head, kHead);
	EXPECT_EQ(1, rmField(AVStr(head), "To"));
	EXPECT_EQ(nullptr, strstr(head, "To:"));
	EXPECT_NE(nullptr, strstr(head, "Subject: hi\nContent-Type"));
}

TEST(Mime, ReplaceFieldValueKeepsOtherFields) {
	CStr(head, 256);
	strcpy(head, kHead);
	replaceFieldValue(AVStr(head), "Subject", "new");
	EXPECT_EQ(0, strncmp(head, "Subject: new\nTo: a@b\n", 21));
}

TEST(Mime, CharsetIsTakenFromContentType) {
	CStr(cs, 32);
	get_charset("text/plain; charset=utf-8", AVStr(cs), sizeof(cs));
	EXPECT_STREQ("utf-8", cs);
}

TEST(Mime, DecodesBase64EncodedWord) {
	CStr(out, 64);
	MIME_strHeaderDecode("=?UTF-8?B?w6TDtg==?=", AVStr(out), sizeof(out));
	EXPECT_STREQ("\xc3\xa4\xc3\xb6", out);
}

TEST(Mime, PlainHeaderTextIsNotEncoded) {
	CStr(out, 64);
	MIME_strHeaderEncode("plain", AVStr(out), sizeof(out));
	EXPECT_STREQ("plain", out);
}

TEST(Mime, StripsCommentsFromAddress) {
	CStr(out, 64);
	RFC822_strip_commentX("Jane (comment) <j@x.org>", AVStr(out), sizeof(out));
	EXPECT_STREQ("Jane <j@x.org>", out);
}

TEST(Mime, ExtractsAddressPart) {
	CStr(out, 64);
	RFC822_addresspartX("Jane Doe <jane@x.org>", AVStr(out), sizeof(out));
	EXPECT_STREQ("jane@x.org", out);
}

TEST(Mime, ParameterValueIsExtracted) {
	CStr(params, 64);
	CStr(val, 32);
	strcpy(params, "a=1; b=two; c=3");
	getParam(AVStr(params), "b", AVStr(val), sizeof(val), 0);
	EXPECT_STREQ("two", val);
}
