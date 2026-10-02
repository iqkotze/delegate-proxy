#include "dg_test.hpp"
#include <fstream>
#include <sys/resource.h>

int calcMaxDelegated(FileSize availBytes, long nofile);
FileSize getMeminfo(const char *name);
int raise_nofile_limit(int *before, int *hard);
int nofile_limit();
extern int DELEGATE_LISTEN;

namespace {
constexpr FileSize kMiB = 1024 * 1024;
constexpr FileSize kGiB = 1024 * kMiB;

/// Value of a /proc/meminfo field in bytes, or -1.
FileSize procMeminfo(const char *field) {
	std::ifstream in("/proc/meminfo");
	std::string name;
	long long kb;
	std::string unit;
	while (in >> name >> kb >> unit)
		if (name == std::string(field) + ":") return kb * 1024;
	return -1;
}
}  // namespace

TEST(Limits, MaxDelegatedFollowsMemory) {
	EXPECT_EQ(256, calcMaxDelegated(1 * kGiB, 20000));
	EXPECT_EQ(1024, calcMaxDelegated(4 * kGiB, 20000));
}

TEST(Limits, MaxDelegatedFollowsDescriptors) {
	EXPECT_EQ(468, calcMaxDelegated(64 * kGiB, 1000));
	EXPECT_EQ(2016, calcMaxDelegated(64 * kGiB, 4096));
}

TEST(Limits, MaxDelegatedIsCappedAndHasAFloor) {
	EXPECT_EQ(4096, calcMaxDelegated(1024 * kGiB, 1000000));
	EXPECT_EQ(64, calcMaxDelegated(32 * kMiB, 20000));
	EXPECT_EQ(64, calcMaxDelegated(64 * kGiB, 100));
	EXPECT_EQ(64, calcMaxDelegated(0, 0));
}

TEST(Limits, MeminfoDoesNotOverflowAbove2GB) {
	FileSize memfree = procMeminfo("MemFree");
	if (memfree < 0) GTEST_SKIP() << "no /proc/meminfo";
	FileSize ina = getMeminfo("inactive");
	EXPECT_GE(ina, memfree);
	FileSize avail = getMeminfo("available");
	EXPECT_GT(avail, 0);
}

TEST(Limits, RaiseNofileReachesTheHardLimit) {
	rlimit rl;
	ASSERT_EQ(0, getrlimit(RLIMIT_NOFILE, &rl));
	int before = 0, hard = 0;
	int now = raise_nofile_limit(&before, &hard);
	EXPECT_GE(now, before);
	EXPECT_EQ(now, nofile_limit());
	EXPECT_LE(now, 65536);
	if (rl.rlim_max != RLIM_INFINITY && rl.rlim_max <= 65536) EXPECT_EQ((int)rl.rlim_max, now);
	EXPECT_GE(now, 64);
}

TEST(Limits, ListenBacklogDefaultsToSomaxconn) {
	std::ifstream in("/proc/sys/net/core/somaxconn");
	int somaxconn = 0;
	if (!(in >> somaxconn) || somaxconn <= 0) GTEST_SKIP() << "no somaxconn";
	EXPECT_EQ(somaxconn, DELEGATE_LISTEN);
}
