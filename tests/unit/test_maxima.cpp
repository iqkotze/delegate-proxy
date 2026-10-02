#include "dg_test.hpp"
#include "delegate.h"

void minit_logs();
void scan_MAXIMA(Connection *Conn, PCStr(maxima));
extern int CON_RETRY;

TEST(Maxima, CallbackAppliesValues) {
	minit_logs();
	scan_MAXIMA(nullptr, "contry:5,nosuchitem:1,contry");
	EXPECT_EQ(5, CON_RETRY);
	scan_MAXIMA(nullptr, "contry:2");
	EXPECT_EQ(2, CON_RETRY);
}
