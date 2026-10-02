#include "dg_test.hpp"
#include <set>
#include "dgparam.h"

namespace {
const DgParam *find(const char *name) {
	for (int i = 0; i < dg_params_count; i++)
		if (strcmp(dg_params[i].name, name) == 0) return &dg_params[i];
	return nullptr;
}
}

TEST(Params, TableIsNotEmpty) {
	EXPECT_GT(dg_params_count, 100);
}

TEST(Params, NamesAreUniqueAndSorted) {
	std::set<std::string> seen;
	for (int i = 0; i < dg_params_count; i++) {
		EXPECT_TRUE(seen.insert(dg_params[i].name).second) << dg_params[i].name;
		if (i > 0) EXPECT_LT(strcmp(dg_params[i - 1].name, dg_params[i].name), 0);
	}
}

TEST(Params, EntriesAreComplete) {
	for (int i = 0; i < dg_params_count; i++) {
		const DgParam &p = dg_params[i];
		EXPECT_NE('\0', p.syntax[0]) << p.name;
		EXPECT_NE('\0', p.dflt[0]) << p.name;
		EXPECT_NE('\0', p.desc[0]) << p.name;
		EXPECT_NE('\0', p.example[0]) << p.name;
		EXPECT_NE('\0', p.file[0]) << p.name;
		EXPECT_LE(strlen(p.desc), 100u) << p.name;
		EXPECT_EQ(0, strncmp(p.example, p.name, strlen(p.name))) << p.name;
	}
}

TEST(Params, MaximaHasSubOptions) {
	const DgParam *p = find("MAXIMA");
	ASSERT_NE(nullptr, p);
	EXPECT_GT(p->nsubs, 0);
	bool listen = false;
	for (int i = 0; i < p->nsubs; i++) {
		EXPECT_NE('\0', p->subs[i].desc[0]) << p->subs[i].name;
		if (strcmp(p->subs[i].name, "listen") == 0) listen = true;
	}
	EXPECT_TRUE(listen);
}

TEST(Params, TimeoutHasSubOptions) {
	const DgParam *p = find("TIMEOUT");
	ASSERT_NE(nullptr, p);
	EXPECT_GT(p->nsubs, 0);
}

TEST(Params, ConfParametersHaveSubOptions) {
	const char *names[] = {"HTTPCONF", "FTPCONF", "SMTPCONF", "NNTPCONF", "POPCONF", "DNSCONF", "ICPCONF",
		"TELNETCONF", "SOXCONF", "YYCONF", "ARPCONF", "PAMCONF", "MHGWCONF", "DELAY", "SOCKOPT", "IPV6",
		"HTMLCONV", "MIMECONV", "COUNTER", "CACHE", "SYSLOG", "DGDEF", "STLS", "RELAY", "CONNECT", "MOUNT",
		"DYCONF", "MAXIMA", "TIMEOUT", "TLSCONF"};
	for (const char *name : names) {
		const DgParam *p = find(name);
		ASSERT_NE(nullptr, p) << name;
		EXPECT_GT(p->nsubs, 0) << name;
		std::set<std::string> seen;
		for (int i = 0; i < p->nsubs; i++) {
			EXPECT_TRUE(seen.insert(p->subs[i].name).second) << name << "/" << p->subs[i].name;
			EXPECT_LE(strlen(p->subs[i].desc), 100u) << name << "/" << p->subs[i].name;
			EXPECT_EQ(0, strncmp(p->subs[i].example, name, strlen(name))) << name << "/" << p->subs[i].name;
		}
	}
}
