#include "dg_test.hpp"
#include <sys/resource.h>
#include <unistd.h>
#include "ysocket.h"

int PollIn1(int fd, int timeout);
int PollIns(int timeout, int size, int *mask, int *rmask);
int PollOut(int fd, int timeout);
int PollInsOuts(int timeout, int nfds, int fdv[], int ev[], int rev[]);
int _PollIn1(int fd, int timeout);
int _PollIns(int timeout, int size, int *mask, int *rmask);

namespace {
constexpr int kHighFd = 1100;

/// Pipe whose ends are moved above FD_SETSIZE.
struct HighPipe {
	int rd = -1, wr = -1;
	bool ok = false;
	HighPipe() {
		rlimit rl;
		if (getrlimit(RLIMIT_NOFILE, &rl) != 0) return;
		if (rl.rlim_cur < kHighFd + 8) {
			rl.rlim_cur = kHighFd + 8 <= rl.rlim_max ? kHighFd + 8 : rl.rlim_max;
			setrlimit(RLIMIT_NOFILE, &rl);
		}
		int p[2];
		if (pipe(p) != 0) return;
		rd = dup2(p[0], kHighFd);
		wr = dup2(p[1], kHighFd + 1);
		close(p[0]);
		close(p[1]);
		ok = rd == kHighFd && wr == kHighFd + 1;
	}
	~HighPipe() {
		if (rd >= 0) close(rd);
		if (wr >= 0) close(wr);
	}
};
}

TEST(Poll, PollIn1WorksAboveFdSetSize) {
	HighPipe hp;
	if (!hp.ok) GTEST_SKIP() << "cannot create fds above 1024";
	EXPECT_EQ(0, PollIn1(hp.rd, 20));
	ASSERT_EQ(1, write(hp.wr, "x", 1));
	EXPECT_EQ(1, PollIn1(hp.rd, 20));
}

TEST(Poll, PollOutWorksAboveFdSetSize) {
	HighPipe hp;
	if (!hp.ok) GTEST_SKIP() << "cannot create fds above 1024";
	EXPECT_EQ(1, PollOut(hp.wr, 20));
}

TEST(Poll, PollInsReportsEachReadyDescriptor) {
	HighPipe hp;
	if (!hp.ok) GTEST_SKIP() << "cannot create fds above 1024";
	int low[2];
	ASSERT_EQ(0, pipe(low));
	ASSERT_EQ(1, write(hp.wr, "x", 1));
	int mask[4] = {low[0], -1, hp.rd, low[1]};
	int rmask[4] = {9, 9, 9, 9};
	EXPECT_EQ(1, PollIns(20, 4, mask, rmask));
	EXPECT_EQ(0, rmask[0]);
	EXPECT_EQ(0, rmask[1]);
	EXPECT_EQ(1, rmask[2]);
	EXPECT_EQ(0, rmask[3]);
	close(low[0]);
	close(low[1]);
}

TEST(Poll, PollInsTimesOutWithoutData) {
	HighPipe hp;
	if (!hp.ok) GTEST_SKIP() << "cannot create fds above 1024";
	int mask[1] = {hp.rd};
	int rmask[1] = {9};
	EXPECT_EQ(0, PollIns(20, 1, mask, rmask));
	EXPECT_EQ(0, rmask[0]);
}

TEST(Poll, PollInsOutsMapsEventsAboveFdSetSize) {
	HighPipe hp;
	if (!hp.ok) GTEST_SKIP() << "cannot create fds above 1024";
	ASSERT_EQ(1, write(hp.wr, "x", 1));
	int fdv[2] = {hp.rd, hp.wr};
	int ev[2] = {PS_IN, PS_OUT};
	int rev[2] = {0, 0};
	EXPECT_EQ(2, PollInsOuts(20, 2, fdv, ev, rev));
	EXPECT_EQ(PS_IN, rev[0] & PS_IN);
	EXPECT_EQ(PS_OUT, rev[1] & PS_OUT);
}

TEST(Poll, PollInsOutsIgnoresNegativeDescriptors) {
	int fdv[1] = {-1};
	int ev[1] = {PS_IN};
	int rev[1] = {7};
	EXPECT_EQ(0, PollInsOuts(TIMEOUT_IMM, 1, fdv, ev, rev));
	EXPECT_EQ(0, rev[0]);
}

TEST(Poll, UnderscorePollIn1WorksAboveFdSetSize) {
	HighPipe hp;
	if (!hp.ok) GTEST_SKIP() << "cannot create fds above 1024";
	EXPECT_EQ(0, _PollIn1(hp.rd, 20));
	ASSERT_EQ(1, write(hp.wr, "x", 1));
	EXPECT_EQ(1, _PollIn1(hp.rd, 20));
	EXPECT_EQ(-1, _PollIn1(-1, 20));
}

TEST(Poll, UnderscorePollInsWorksAboveFdSetSize) {
	HighPipe hp;
	if (!hp.ok) GTEST_SKIP() << "cannot create fds above 1024";
	ASSERT_EQ(1, write(hp.wr, "x", 1));
	int mask[2] = {-1, hp.rd};
	int rmask[2] = {9, 9};
	EXPECT_EQ(1, _PollIns(20, 2, mask, rmask));
	EXPECT_EQ(0, rmask[0]);
	EXPECT_EQ(1, rmask[1]);
}
