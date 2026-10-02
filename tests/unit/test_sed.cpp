#include "dg_test.hpp"

struct sed_env;
sed_env *sed_new();
void sed_free(sed_env *);
int sed_compile(sed_env *, const char *command);
void sed_execute1(sed_env *, PCStr(in), PVStr(out), int err);

TEST(Sed, SubstitutesFirstMatch) {
	sed_env *se = sed_new();
	ASSERT_EQ(0, sed_compile(se, "s/foo/bar/"));
	CStr(out, 64);
	sed_execute1(se, "a foo b foo", AVStr(out), 0);
	EXPECT_STREQ("a bar b foo", out);
	sed_free(se);
}

TEST(Sed, LeavesNonMatchingLineUnchanged) {
	sed_env *se = sed_new();
	ASSERT_EQ(0, sed_compile(se, "s/foo/bar/"));
	CStr(out, 64);
	sed_execute1(se, "nothing here", AVStr(out), 0);
	EXPECT_STREQ("nothing here", out);
	sed_free(se);
}

TEST(Sed, FreesEnvWithSeveralCommands) {
	sed_env *se = sed_new();
	ASSERT_EQ(0, sed_compile(se, "/foo/s/foo/bar/g"));
	ASSERT_EQ(0, sed_compile(se, "s/x/y/"));
	CStr(out, 64);
	sed_execute1(se, "foo foo", AVStr(out), 0);
	EXPECT_STREQ("bar bar", out);
	sed_free(se);
}

TEST(Sed, FreeAcceptsNull) {
	sed_free(nullptr);
}
