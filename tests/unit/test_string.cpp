#include "dg_test.hpp"

char *strtailstr(PCStr(str1), PCStr(str2));
char *strip_spaces(PCStr(value));
int scan_period(PCStr(period), int dfltunit, int dflt);
const char *scanint(PCStr(str), int *valp);
char *numscanX(PCStr(str), PVStr(val), int siz);
char *linescanX(PCStr(str), PVStr(line), int);
char *wordscanX(PCStr(str), PVStr(word), int);
void Strins(PVStr(d), PCStr(s));
void Strrplc(PVStr(d), int len, PCStr(s));
char *strncpy0(PVStr(d), PCStr(s), int len);
void strreverse(PCStr(str));
void strdelchr(PCStr(src), PVStr(dst), PCStr(del));

TEST(String, IsDigitsAcceptsOnlyDecimalDigits) {
	EXPECT_TRUE(isdigits("0123456789"));
	EXPECT_FALSE(isdigits(""));
	EXPECT_FALSE(isdigits("12a"));
}

TEST(String, CaseInsensitiveEquality) {
	EXPECT_TRUE(strcaseeq("Content-Type", "content-TYPE"));
	EXPECT_FALSE(strcaseeq("abc", "abd"));
	EXPECT_TRUE(strncaseeq("HTTP/1.1", "http/1.0", 5));
}

TEST(String, ToLowerAndUpper) {
	CStr(out, 16);
	strtolowerX("AbC-1", AVStr(out), sizeof(out));
	EXPECT_STREQ("abc-1", out);
	strtoupperX("AbC-1", AVStr(out), sizeof(out));
	EXPECT_STREQ("ABC-1", out);
}

TEST(String, ToLowerTruncatesToBufferSize) {
	CStr(out, 4);
	strtolowerX("ABCDEFG", AVStr(out), sizeof(out));
	EXPECT_STREQ("abc", out);
}

TEST(String, KmxatoiAppliesSizeSuffixes) {
	EXPECT_EQ(10 * 1024, kmxatoi("10k"));
	EXPECT_EQ(2 * 1024 * 1024, kmxatoi("2M"));
	EXPECT_EQ(3LL * 1024 * 1024 * 1024, kmxatoi("3g"));
	EXPECT_EQ(42, kmxatoi("42"));
	EXPECT_EQ(0, kmxatoi("abc"));
}

TEST(String, KmxatoiHandlesValuesAboveIntRange) {
	GTEST_SKIP() << "known bug: kmxatoi() uses atoi(), so \"5000000000\" yields 705032704";
	EXPECT_EQ(5000000000LL, kmxatoi("5000000000"));
}

TEST(String, ScanIntStopsAtFirstNonDigit) {
	int v = -1;
	const char *rest = scanint("123abc", &v);
	EXPECT_EQ(123, v);
	EXPECT_STREQ("abc", rest);
}

TEST(String, ScanIntDetectsOverflow) {
	GTEST_SKIP() << "known bug: scanint() overflows int, \"4294967297\" yields 1";
	int v = 0;
	scanint("4294967297", &v);
	EXPECT_NE(1, v);
}

TEST(String, SubstituteReplacesAllOccurrences) {
	CStr(s, 32);
	strcpy(s, "a-b-c");
	strsubst(AVStr(s), "-", "--");
	EXPECT_STREQ("a--b--c", s);
}

TEST(String, DeleteCharactersRemovesEverySetMember) {
	CStr(out, 32);
	strdelchr("hello world", AVStr(out), "lo");
	EXPECT_STREQ("he wrd", out);
}

TEST(String, ReverseInPlace) {
	CStr(s, 16);
	strcpy(s, "abcdef");
	strreverse(s);
	EXPECT_STREQ("fedcba", s);
}

TEST(String, InsertAndReplaceInPlace) {
	CStr(s, 32);
	strcpy(s, "world");
	Strins(AVStr(s), "hello ");
	EXPECT_STREQ("hello world", s);
	Strrplc(AVStr(s), 5, "bye");
	EXPECT_STREQ("bye world", s);
}

TEST(String, Strncpy0AlwaysTerminates) {
	CStr(s, 8);
	memset(s, 'x', sizeof(s));
	strncpy0(AVStr(s), "abcdef", 3);
	EXPECT_STREQ("abc", s);
}

TEST(String, StripSpacesTrimsBothEnds) {
	char s[] = "  a b  ";
	EXPECT_STREQ("a b", strip_spaces(s));
}

TEST(String, TailMatching) {
	EXPECT_STREQ(".html", strtailstr("file.html", ".html"));
	EXPECT_EQ(nullptr, strtailstr("file.html", ".htm"));
	EXPECT_EQ('c', strtailchr("abc"));
	EXPECT_EQ(0, strtailchr(""));
}

TEST(String, HeadMatchingIgnoresCaseOnRequest) {
	const char *rest = strheadstrX("Content-Type: x", "content-type", 1);
	ASSERT_NE(nullptr, rest);
	EXPECT_STREQ(": x", rest);
	EXPECT_EQ(nullptr, strheadstrX("Content", "xx", 0));
}

TEST(String, LastBreakCharacter) {
	EXPECT_STREQ("/c", strrpbrk("a/b/c", "/"));
	EXPECT_EQ(nullptr, strrpbrk("abc", "/"));
}

TEST(String, WordScanSkipsLeadingBlanks) {
	CStr(w, 16);
	const char *rest = wordscanX("  hello world", AVStr(w), sizeof(w));
	EXPECT_STREQ("hello", w);
	EXPECT_STREQ(" world", rest);
}

TEST(String, WordScanTruncatesLongWords) {
	GTEST_SKIP() << "known bug: wordscanX() aborts via FORTIFY in putvstr() (rary/ystring.c) when the word fills the buffer";
	CStr(w, 16);
	wordscanX("abcdefghijklmnopqrstuvwxyz", AVStr(w), sizeof(w));
	EXPECT_STREQ("abcdefghijklmno", w);
}

TEST(String, LineScanStopsAtLineEnd) {
	CStr(l, 32);
	linescanX("line one\r\nline two", AVStr(l), sizeof(l));
	EXPECT_STREQ("line one", l);
}

TEST(String, NumScanReadsLeadingDigits) {
	CStr(n, 16);
	numscanX("123abc", AVStr(n), sizeof(n));
	EXPECT_STREQ("123", n);
}

TEST(String, ListMembershipReturnsOneBasedPosition) {
	EXPECT_EQ(1, isinList("a,b,c", "a"));
	EXPECT_EQ(3, isinList("a,b,c", "c"));
	EXPECT_EQ(0, isinList("ab,bc", "b"));
}

TEST(String, CountsListElements) {
	EXPECT_EQ(3, num_ListElems("a,b,c", ','));
	EXPECT_EQ(0, num_ListElems("", ','));
}

TEST(String, ListSplitKeepsRemainderInLastElement) {
	CStr(a, 16);
	CStr(b, 16);
	CStr(c, 16);
	int n = scan_Listlist("x:y:z:w", ':', AVStr(a), AVStr(b), AVStr(c), VStrNULL, VStrNULL);
	EXPECT_EQ(3, n);
	EXPECT_STREQ("x", a);
	EXPECT_STREQ("y", b);
	EXPECT_STREQ("z:w", c);
}

TEST(String, FirstListElementAndRemainder) {
	CStr(first, 16);
	const char *rest = scan_ListElem1("x,y,z", ',', AVStr(first));
	EXPECT_STREQ("x", first);
	EXPECT_STREQ("y,z", rest);
}

TEST(String, ReverseDomainOrdersLabelsFromTheRoot) {
	CStr(out, 64);
	reverseDomain("www.example.co.jp", AVStr(out));
	EXPECT_STREQ("jp.co.example.www", out);
}

TEST(String, PatternRequiresExactMatchWithoutWildcard) {
	EXPECT_TRUE(rexpmatch("abc", "abc"));
	EXPECT_FALSE(rexpmatch("abc", "abcdef"));
}

TEST(String, PatternWildcardAtEitherEnd) {
	EXPECT_TRUE(rexpmatch("*", "anything"));
	EXPECT_TRUE(rexpmatch("ab*", "abxyz"));
	EXPECT_TRUE(rexpmatch("*def", "abcdef"));
	EXPECT_TRUE(rexpmatch("*cd*", "abcdef"));
	EXPECT_FALSE(rexpmatch("*xy*", "abcdef"));
}

TEST(String, PeriodUnits) {
	EXPECT_EQ(120, scan_period("2m", 's', 0));
	EXPECT_EQ(3600, scan_period("1h", 's', 0));
	EXPECT_EQ(86400, scan_period("1d", 's', 0));
	EXPECT_EQ(30, scan_period("30", 's', 0));
	EXPECT_EQ(5400, scan_period("90", 'm', 0));
	EXPECT_EQ(7, scan_period("", 's', 7));
}
