#include "dg_test.hpp"
#include <type_traits>

void canon_date(PVStr(date));
int wdaytoi(PCStr(wday));

namespace {
/// Sun, 06 Nov 1994 08:49:37 GMT
const int kRfc1945Example = 784111777;
}

TEST(Strftime, FormatsGmtInRfc1123Style) {
	CStr(out, 64);
	StrftimeGMT(AVStr(out), sizeof(out), "%a, %d %b %Y %H:%M:%S GMT", kRfc1945Example, 0);
	EXPECT_STREQ("Sun, 06 Nov 1994 08:49:37 GMT", out);
}

TEST(Strftime, FormatsEpoch) {
	CStr(out, 64);
	StrftimeGMT(AVStr(out), sizeof(out), "%Y-%m-%d %H:%M:%S", 0, 0);
	EXPECT_STREQ("1970-01-01 00:00:00", out);
}

TEST(Strftime, ScanHttpTimeAcceptsRfc1123) {
	EXPECT_EQ(kRfc1945Example, scanHTTPtime("Sun, 06 Nov 1994 08:49:37 GMT"));
}

TEST(Strftime, ScanHttpTimeAcceptsRfc850) {
	EXPECT_EQ(kRfc1945Example, scanHTTPtime("Sunday, 06-Nov-94 08:49:37 GMT"));
}

TEST(Strftime, ScanHttpTimeAcceptsAnsiC) {
	EXPECT_EQ(kRfc1945Example, scanHTTPtime("Sun Nov  6 08:49:37 1994"));
}

TEST(Strftime, ScanHttpTimeRejectsGarbage) {
	EXPECT_EQ(-1, scanHTTPtime("garbage"));
}

TEST(Strftime, ScanHttpTimeReachesLastInt32Second) {
	EXPECT_EQ(2147483647, scanHTTPtime("Tue, 19 Jan 2038 03:14:07 GMT"));
}

TEST(Strftime, ScanHttpTimeAcceptsDatesAfter2038) {
	EXPECT_EQ(4102444800LL, scanHTTPtime("Fri, 01 Jan 2100 00:00:00 GMT"));
}

TEST(Strftime, ScanHttpTimeReturnsTimeT) {
	static_assert(std::is_same_v<time_t, decltype(scanHTTPtime(""))>);
}

TEST(Strftime, ScanCompactTimestamp) {
	char stamp[] = "19941106084937";
	EXPECT_EQ(kRfc1945Example, scanYmdHMS_GMT(stamp));
}

TEST(Strftime, ScanCompactTimestampKeepsConstInput) {
	EXPECT_EQ(kRfc1945Example, scanYmdHMS_GMT("19941106084937"));
}

TEST(Strftime, ScanCompactTimestampAcceptsDatesAfter2038) {
	EXPECT_EQ(4102444800LL, scanYmdHMS_GMT("21000101000000"));
}

TEST(Strftime, ScanCompactTimestampRejectsShortInput) {
	EXPECT_EQ(-1, scanYmdHMS_GMT("1994110608"));
}

TEST(Strftime, ParsesDateAndTimeWithZone) {
	char stamp[] = "19941106 084937 GMT";
	EXPECT_EQ(kRfc1945Example, YMD_HMS_toi(stamp));
}

TEST(Strftime, WeekdayNamesStartAtSunday) {
	EXPECT_EQ(0, wdaytoi("Sun"));
	EXPECT_EQ(6, wdaytoi("Sat"));
}

TEST(Strftime, CanonDateKeepsCanonicalForm) {
	CStr(d, 64);
	strcpy(d, "Sun, 06 Nov 1994 08:49:37 GMT");
	canon_date(AVStr(d));
	EXPECT_STREQ("Sun, 06 Nov 1994 08:49:37 GMT", d);
}
