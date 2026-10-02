#include "dg_test.hpp"

void strrot13(char str[]);
int aencryptyX(PCStr(key), int klen, PCStr(ins), int ilen, PVStr(out));
int adecrypty(PCStr(key), int klen, PCStr(ins), int ilen, char out[]);

TEST(Pelcgb, Rot13ShiftsLettersOnly) {
	char s[] = "Hello, World 123";
	strrot13(s);
	EXPECT_STREQ("Uryyb, Jbeyq 123", s);
}

TEST(Pelcgb, Rot13IsItsOwnInverse) {
	char s[] = "The Quick Brown Fox";
	strrot13(s);
	strrot13(s);
	EXPECT_STREQ("The Quick Brown Fox", s);
}

TEST(Pelcgb, EncryptedTextIsUppercaseHex) {
	CStr(enc, 128);
	int n = aencryptyX("secret", 6, "hello", 5, AVStr(enc));
	ASSERT_GT(n, 0);
	EXPECT_EQ(n, (int)strlen(enc));
	EXPECT_EQ(std::string::npos, std::string(enc).find_first_not_of("0123456789ABCDEF"));
}

TEST(Pelcgb, DecryptRestoresPlaintext) {
	CStr(enc, 128);
	char dec[128];
	int n = aencryptyX("secret", 6, "hello", 5, AVStr(enc));
	int m = adecrypty("secret", 6, enc, n, dec);
	EXPECT_EQ(5, m);
	EXPECT_STREQ("hello", dec);
}

TEST(Pelcgb, DifferentKeysGiveDifferentCiphertext) {
	CStr(a, 128);
	CStr(b, 128);
	aencryptyX("secret", 6, "hello", 5, AVStr(a));
	aencryptyX("Secret", 6, "hello", 5, AVStr(b));
	EXPECT_STRNE(a, b);
}
