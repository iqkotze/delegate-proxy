#include "dg_test.hpp"
#include <regex.h>

void *Regcomp(const char *pat, int flag);
int Regexec(void *re, const char *str, int nm, int so, int eo, int flag);
void Regfree(void *re);

TEST(Regex, ExecWithoutMatchArrayFindsMatch) {
	void *re = Regcomp("b+", REG_EXTENDED);
	ASSERT_NE(nullptr, re);
	EXPECT_EQ(0, Regexec(re, "abbc", 0, 0, 0, 0));
	EXPECT_NE(0, Regexec(re, "xyz", 0, 0, 0, 0));
	Regfree(re);
}

TEST(Regex, ExecWithManyRequestedMatchesStaysInBounds) {
	void *re = Regcomp("(a)(b)(c)(d)(e)(f)(g)(h)", REG_EXTENDED);
	ASSERT_NE(nullptr, re);
	EXPECT_EQ(0, Regexec(re, "abcdefgh", 9, 0, 0, 0));
	Regfree(re);
}

TEST(Regex, CompileRejectsInvalidPattern) {
	EXPECT_EQ(nullptr, Regcomp("(", REG_EXTENDED));
}
