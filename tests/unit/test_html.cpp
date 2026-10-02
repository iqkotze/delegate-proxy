#include "dg_test.hpp"

TEST(Html, EncodeEntitiesEscapesMarkup) {
	CStr(out, 64);
	encodeEntitiesX("a<b>&\"c", AVStr(out), sizeof(out));
	EXPECT_STREQ("a&lt;b&gt;&amp;&quot;c", out);
}

TEST(Html, DecodeEntitiesRestoresNamedEntities) {
	CStr(out, 64);
	decodeEntitiesX("&lt;p&gt; &amp; &quot;x&quot; &#39;", AVStr(out), sizeof(out), 1);
	EXPECT_STREQ("<p> & \"x\" '", out);
}

TEST(Html, DecodeEntitiesKeepsUnknownEntities) {
	CStr(out, 64);
	decodeEntitiesX("&foo; &amp;lt;", AVStr(out), sizeof(out), 1);
	EXPECT_STREQ("&foo; &lt;", out);
}

TEST(Html, DecodeEntitiesTruncatesToBufferSize) {
	CStr(out, 5);
	decodeEntitiesX("abcdefgh", AVStr(out), sizeof(out), 1);
	EXPECT_STREQ("abcd", out);
}
