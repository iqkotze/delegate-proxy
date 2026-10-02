#include "dg_test.hpp"
#include <vector>

namespace {
struct Seen {
	std::vector<std::string> elems;
	std::vector<void*> a1, a2;
};

int collect(const char *elem, Seen *seen, void *x, void *y) {
	seen->elems.push_back(elem);
	seen->a1.push_back(x);
	seen->a2.push_back(y);
	return 0;
}

int fmtArgs(const char *fmt, ...) {
	VARGS(4, fmt);
	int n = 0;
	for (char *a : va)
		if (a) n++;
	return n;
}
}

TEST(Vargs, CountsFormatConversions) {
	EXPECT_EQ(0, vargs_fmtc("plain"));
	EXPECT_EQ(0, vargs_fmtc("100%%"));
	EXPECT_EQ(2, vargs_fmtc("%s and %d"));
	EXPECT_EQ(2, vargs_fmtc("%-5.3ld %s"));
	EXPECT_EQ(3, vargs_fmtc("%*d %s"));
	EXPECT_EQ(0, vargs_fmtc("trailing %"));
}

TEST(Vargs, FormatStyleReadsOnlyConsumedArguments) {
	EXPECT_EQ(0, fmtArgs("none"));
	EXPECT_EQ(1, fmtArgs("%s", "a"));
	EXPECT_EQ(2, fmtArgs("%s %s", "a", "b"));
}

TEST(Vargs, ScanCommaListPassesNoExtraArguments) {
	Seen seen;
	scan_commaList("a,b", 0, (scanListFuncP)collect, &seen);
	ASSERT_EQ(2u, seen.elems.size());
	EXPECT_EQ(nullptr, seen.a1[0]);
	EXPECT_EQ(nullptr, seen.a2[1]);
}

TEST(Vargs, ScanCommaListForwardsGivenArguments) {
	Seen seen;
	int x = 1, y = 2;
	scan_commaList("a,b", 0, (scanListFuncP)collect, &seen, &x, &y);
	ASSERT_EQ(2u, seen.elems.size());
	EXPECT_EQ(&x, seen.a1[0]);
	EXPECT_EQ(&y, seen.a2[1]);
}

TEST(Vargs, ScanListWithoutExtraArgumentsStaysInBounds) {
	Seen seen;
	scan_List("a b", ' ', 0, (scanListFuncP)collect, &seen);
	ASSERT_EQ(2u, seen.elems.size());
	EXPECT_EQ(nullptr, seen.a1[1]);
}
