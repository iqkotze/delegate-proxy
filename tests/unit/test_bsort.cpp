#include "dg_test.hpp"

void Bsort(char base[], int nel, int width, int (*compar)(const char *, const char *));

namespace {
int cmp(const char *a, const char *b) { return strcmp(a, b); }
}

TEST(Bsort, SortsFixedWidthRecords) {
	char rec[4][8] = {"delta", "alpha", "charlie", "bravo"};
	Bsort(&rec[0][0], 4, 8, cmp);
	EXPECT_STREQ("alpha", rec[0]);
	EXPECT_STREQ("bravo", rec[1]);
	EXPECT_STREQ("charlie", rec[2]);
	EXPECT_STREQ("delta", rec[3]);
}

TEST(Bsort, KeepsEqualRecordsInOriginalOrder) {
	char rec[3][4] = {"b1", "a1", "b0"};
	auto first = [](const char *a, const char *b) { return a[0] - b[0]; };
	Bsort(&rec[0][0], 3, 4, first);
	EXPECT_STREQ("a1", rec[0]);
	EXPECT_STREQ("b1", rec[1]);
	EXPECT_STREQ("b0", rec[2]);
}
