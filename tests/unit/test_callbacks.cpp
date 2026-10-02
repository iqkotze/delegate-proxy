#include "dg_test.hpp"
#include "file.h"
#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

int (allocaCall)(PCStr(what), int size, iFUNCP func, ...);
void *(callFuncTimeout)(int sec, void *xcode, pFUNCP func, ...);

namespace {
int count_with_args(const char *elem, int *total, const char *tag, int weight) {
	*total += (int)strlen(elem) * weight + (tag ? 1 : 0);
	return 0;
}
int stop_at(const char *elem, int *seen, const char *stop) {
	(*seen)++;
	return strcmp(elem, stop) == 0 ? 7 : 0;
}
int collect_var(const char *elem, ...) {
	va_list ap;
	va_start(ap, elem);
	std::vector<std::string> *out = va_arg(ap, std::vector<std::string> *);
	va_end(ap);
	out->push_back(elem);
	return 0;
}
int dir_entry(const char *name, std::vector<std::string> *out, int mark) {
	if (name[0] != '.') out->push_back(std::string(name) + (mark ? "!" : ""));
	return 0;
}
int stack_sum(const char *a, long b, int *out) {
	*out = (int)strlen(a) + (int)b;
	return 3;
}
void *timeout_func(const char *s, int *flag) {
	*flag = 1;
	return (void *)s;
}
}

TEST(Callbacks, ScanListPassesMixedArguments) {
	int total = 0;
	EXPECT_EQ(0, scan_commaList("ab,cde", 0, scanListCall count_with_args, &total, "t", 10));
	EXPECT_EQ(2 * 10 + 1 + 3 * 10 + 1, total);
}

TEST(Callbacks, ScanListStopsWithCallbackResult) {
	int seen = 0;
	EXPECT_EQ(7, scan_List("a+b+c+d", '+', 0, scanListCall stop_at, &seen, "c"));
	EXPECT_EQ(3, seen);
}

TEST(Callbacks, ScanListVariadicCallback) {
	std::vector<std::string> out;
	EXPECT_EQ(0, scan_commaListL("x,y,z", 0, collect_var, &out));
	ASSERT_EQ(3u, out.size());
	EXPECT_EQ("x", out[0]);
	EXPECT_EQ("z", out[2]);
}

TEST(Callbacks, ScanListlistSplitsElements) {
	CStr(a, 16);
	CStr(b, 16);
	CStr(c, 16);
	EXPECT_EQ(3, scan_Listlist("one:two:three", ':', AVStr(a), AVStr(b), AVStr(c), VStrNULL, VStrNULL));
	EXPECT_STREQ("one", a);
	EXPECT_STREQ("two", b);
	EXPECT_STREQ("three", c);
}

TEST(Callbacks, IsinListFindsPosition) {
	EXPECT_EQ(2, isinList("alpha,beta,gamma", "beta"));
	EXPECT_EQ(0, isinList("alpha,beta,gamma", "delta"));
	EXPECT_NE(0, isinListX("alpha,example", "www.example.org", "s"));
	EXPECT_NE(0, isinListX("ALPHA,BETA", "beta", "c"));
	EXPECT_EQ(0, isinListX("ALPHA,BETA", "beta", ""));
}

TEST(Callbacks, NumListElemsCountsWithoutCallback) {
	EXPECT_EQ(4, num_ListElems("a,b,c,d", ','));
}

TEST(Callbacks, ScandirCallsTypedCallback) {
	char dir[] = "/tmp/dg-cb-XXXXXX";
	ASSERT_NE(nullptr, mkdtemp(dir));
	std::string f = std::string(dir) + "/entry1";
	FILE *fp = fopen(f.c_str(), "w");
	ASSERT_NE(nullptr, fp);
	fclose(fp);
	std::vector<std::string> out;
	Scandir(dir, scanDirCall dir_entry, &out, 1);
	unlink(f.c_str());
	rmdir(dir);
	ASSERT_EQ(1u, out.size());
	EXPECT_EQ("entry1!", out[0]);
}

TEST(Callbacks, AllocaCallPassesArguments) {
	int out = 0;
	int rc = allocaCall("test", 4096, (iFUNCP)stack_sum, "abc", 40L, &out);
	EXPECT_EQ(3, rc);
	EXPECT_EQ(43, out);
}

TEST(Callbacks, CallFuncTimeoutReturnsPointer) {
	int flag = 0;
	void *r = callFuncTimeout(5, nullptr, (pFUNCP)timeout_func, "ptr", &flag);
	EXPECT_EQ(1, flag);
	EXPECT_STREQ("ptr", (const char *)r);
}

TEST(Callbacks, FunctionPointerWrapperCompares) {
	iFUNCP none;
	iFUNCP a = (iFUNCP)stack_sum;
	iFUNCP b = (iFUNCP)stack_sum;
	EXPECT_FALSE(none);
	EXPECT_TRUE(a);
	EXPECT_TRUE(a == b);
	EXPECT_TRUE(none != a);
	EXPECT_TRUE(none == (iFUNCP)0);
}
