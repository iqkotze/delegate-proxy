#include "dg_test.hpp"

namespace {
/// Hsearch() with this pointer as data looks up a key.
const char *const kNone = "";
}

TEST(Hash, StoresAndFindsValues) {
	int h = Hcreate(16, kNone);
	Hsearch(h, "key", "value");
	EXPECT_STREQ("value", Hsearch(h, "key", kNone));
}

TEST(Hash, UnknownKeyYieldsNullValue) {
	int h = Hcreate(16, kNone);
	EXPECT_EQ(kNone, Hsearch(h, "missing", kNone));
}

TEST(Hash, OverwritesExistingKey) {
	int h = Hcreate(16, kNone);
	Hsearch(h, "one", "1");
	Hsearch(h, "one", "uno");
	EXPECT_STREQ("uno", Hsearch(h, "one", kNone));
}

TEST(Hash, EnumeratesAllEntries) {
	int h = Hcreate(16, kNone);
	Hsearch(h, "one", "1");
	Hsearch(h, "two", "2");
	int seen = 0;
	const char *key, *data;
	for (int i = Hnext(h, -1, &key, &data); i >= 0; i = Hnext(h, i, &key, &data)) {
		if (strcmp(key, "one") == 0) EXPECT_STREQ("1", data);
		if (strcmp(key, "two") == 0) EXPECT_STREQ("2", data);
		seen++;
	}
	EXPECT_EQ(2, seen);
}

TEST(Hash, FqdnHashMatchesReferenceValues) {
	EXPECT_EQ(0u, FQDN_hash(""));
	EXPECT_EQ(101092771u, FQDN_hash("a.b.c"));
	EXPECT_EQ(3101556432u, FQDN_hash("www.example.com"));
}
