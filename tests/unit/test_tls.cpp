#include "dg_test.hpp"
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/x509v3.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "ssl_raii.h"

int sslway_selfsigned(const char *host, EVP_PKEY **pkeyp, X509 **certp);
int sslway_autocertFiles(const char *dir, char *certpath, char *keypath, int psiz);
int signRSA(EVP_PKEY *pkey, PCStr(md5), int mlen, PVStr(sig), unsigned int *slen);
int verifyRSA(EVP_PKEY *pkey, PCStr(md5), int mlen, PCStr(sig), unsigned int slen);
int SignRSA(PCStr(privkey), PCStr(data), PCStr(pass), PCStr(md5), int mlen, PVStr(sig), unsigned int *slen);
int VerifyRSA(PCStr(pubkey), PCStr(data), PCStr(md5), int mlen, PCStr(sig), unsigned int slen);
int pubDecyptRSA(PCStr(pubkey), int len, PCStr(enc), PVStr(dec));
int rsa_main(int ac, const char *av[]);

typedef struct {
	unsigned int x, y;
	unsigned int data[256];
} RC4_KEY;
void myRC4_set_key(RC4_KEY *key, int len, const unsigned char *data);
void myRC4(RC4_KEY *key, unsigned long len, const unsigned char *in, unsigned char *out);

namespace {

/// A key and certificate pair made with the openssl command; the signature covers MD5("abc").
const char kKatKey[] =
	"-----BEGIN RSA PRIVATE KEY-----\n"
	"MIIEoQIBAAKCAQEA3Qi0NJR7HSg06TSnb+f1OE0OAF0UG/B3TLerPtsSbQABroDv\n"
	"l2Hbg/t2IGuobIstBKbLLUiEcmici3SOD+Qme8uofEIo7aItqhI8Nq18ON1p35Ym\n"
	"uZ8xwFJdyroylttIHIWUHoO13viUEJLOUojNhzesGoslhl+EOmWYfjZ8hC163Bk4\n"
	"YLsyZP6ZKbmkD6r0xNLQHIgXoTxSv8kOhWwuKuUf4Mv/Gv3WiCpiG/CIFEPaouvw\n"
	"ZVOnpbqMUjADCodbr/c+9sxlTW7sf3Fl17k5OzQ+om2aO3k94hLo5YKiYBBnJ7N8\n"
	"IvdDimARwh2Wx9c5EYmERbecRGemakJYASRS9QIDAQABAoH/M317Mz9Tr3OfGBBc\n"
	"kGh1OEpdNGk9grcYGDQSrsLOqRiG4rxCNPAcU5psCHkXHV/97wR6f5/dyVTcIBl1\n"
	"tXmIRxpniClGp0aqE+uxMFS8hpDCvBUMAMo0pLHTjGU3owtjme3hDvgjhh4Vye7q\n"
	"dViB8I0wGivfCj5vsSvTp+mAFd1PlIwcP8jYpcbQB+NTmgxUTCTSjtAZHf16ojDB\n"
	"LNW23nnmYtNgkXLbulaI8XdgjTX861JAqgF5m/9x1c2JJpfKU5M3Q3J5tG94S985\n"
	"uBGkbyHBpPGCNG7IbJVhpKOh4PG7avJWOSl3f/3Ot+RdHjB4JLPTM0nGuYVZ4pIe\n"
	"IztZAoGBAO9rTFU4aCCgjINUYeNZn0QUrLzFCCqsWq5b/oWMCGr/LI2PBc2RoGnK\n"
	"3MuCn8dPTz7jKVV3QGkHL9eQ4Vkwh/OweLUIkkKCzpPjD+osx2WqpcTNo0j1T5SB\n"
	"tRYovhDwbB91nJqnf1z2CjzZdN+q1A50WD5Tlj0+4UbFidx+OPLdAoGBAOxXc+Bp\n"
	"J2wiW2Sz36+/4VmwZtTZbLOdx7yPskoAlLndFKwp74a9vQ1OjYO7v/BJCo3xZvl6\n"
	"kcbUkX6zeAWJjRvuzJadBBO6WHHN5QcJa8e6KC6+EneuR6sxkC1JWt8dcAJi8QVp\n"
	"4tuOtV1Im5xZ8oN8QZXNHg42FzaIGp3OreL5AoGBAMBOvkyBd1olu1fN0qbMGRqV\n"
	"RL6HwOyN7nS43fMlLKnM91tpMy8QtvnjAYDSFkcAlFWeH1hP5kO2ix4qeGesjLcX\n"
	"240GKn0UFpxBOUpO14b5EBfJWUvEBzzxBqSa6zgt9Zs7XCP5QFtKIaUIwlDaJWTK\n"
	"3QqLF1VwiYDQMNET7ehdAoGALAKtBWEPgkdzlXEZenTU1grPW1uRrnD3PNnVbYpm\n"
	"J6ZPry+v9vtmNRAnshxIRcqUOJJ3hoWYl9oFrf5ln0JaEJWLa5CZrcLJrYeV2pWa\n"
	"iHrV+L5UWg0OM4brPkOmtF2a+hbKoyNwp0oP4+sdbyQg0PNWkzq7GhJgiDsYGcLf\n"
	"BqECgYBh6jL1JR7U9TgJin7ydunvzKKVD7V2USBL9FtRBwQ0AMLIZVhrCDZZS3Kk\n"
	"Dcev4wCTkm2xKHyC37lGKyeqZy0fF3iINhdxDZgE5wQC0/YZlW6kv7n1QDSDtGw0\n"
	"67u2WEuvPDIHPC2VAIK4FV0VWwRiIGAkaQdEKxQkS/LaDybAEQ==\n"
	"-----END RSA PRIVATE KEY-----\n";

const char kKatPub[] =
	"-----BEGIN PUBLIC KEY-----\n"
	"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA3Qi0NJR7HSg06TSnb+f1\n"
	"OE0OAF0UG/B3TLerPtsSbQABroDvl2Hbg/t2IGuobIstBKbLLUiEcmici3SOD+Qm\n"
	"e8uofEIo7aItqhI8Nq18ON1p35YmuZ8xwFJdyroylttIHIWUHoO13viUEJLOUojN\n"
	"hzesGoslhl+EOmWYfjZ8hC163Bk4YLsyZP6ZKbmkD6r0xNLQHIgXoTxSv8kOhWwu\n"
	"KuUf4Mv/Gv3WiCpiG/CIFEPaouvwZVOnpbqMUjADCodbr/c+9sxlTW7sf3Fl17k5\n"
	"OzQ+om2aO3k94hLo5YKiYBBnJ7N8IvdDimARwh2Wx9c5EYmERbecRGemakJYASRS\n"
	"9QIDAQAB\n"
	"-----END PUBLIC KEY-----\n";

const char kKatCert[] =
	"-----BEGIN CERTIFICATE-----\n"
	"MIIC/zCCAeegAwIBAgIUWrGKS058wXeAwiMp4bVmK+gHnJowDQYJKoZIhvcNAQEL\n"
	"BQAwDjEMMAoGA1UEAwwDa2F0MCAXDTI2MTAwMjAzMDU1M1oYDzIxMjYwOTA4MDMw\n"
	"NTUzWjAOMQwwCgYDVQQDDANrYXQwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEK\n"
	"AoIBAQDdCLQ0lHsdKDTpNKdv5/U4TQ4AXRQb8HdMt6s+2xJtAAGugO+XYduD+3Yg\n"
	"a6hsiy0EpsstSIRyaJyLdI4P5CZ7y6h8Qijtoi2qEjw2rXw43Wnflia5nzHAUl3K\n"
	"ujKW20gchZQeg7Xe+JQQks5SiM2HN6waiyWGX4Q6ZZh+NnyELXrcGThguzJk/pkp\n"
	"uaQPqvTE0tAciBehPFK/yQ6FbC4q5R/gy/8a/daIKmIb8IgUQ9qi6/BlU6eluoxS\n"
	"MAMKh1uv9z72zGVNbux/cWXXuTk7ND6ibZo7eT3iEujlgqJgEGcns3wi90OKYBHC\n"
	"HZbH1zkRiYRFt5xEZ6ZqQlgBJFL1AgMBAAGjUzBRMB0GA1UdDgQWBBTwNDKfJLYv\n"
	"WSLTDRU5m5e/qjzdNjAfBgNVHSMEGDAWgBTwNDKfJLYvWSLTDRU5m5e/qjzdNjAP\n"
	"BgNVHRMBAf8EBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQBB7MLJr4idaRUqQOj/\n"
	"BEuh3vqi4MmcD/ZeYP6VNTOACXPvSvK8XFoGTaBWouEvGll5ni5B/93J/3AbyxyX\n"
	"O5h0SvahtptAitfckjNU0UejPpDeP8ei150h/RugkzWtQvxdbc+lSf0K4Ry9vTmH\n"
	"38PzeYaqpoOqT6w0NUvu6Cw3S7Q7lJ0J/QRAFQ3+nul39IOMiVPg6LRfyzyA6i+n\n"
	"yDW32w7W0Vc94026NdYQJKzqdxKnY/enVLIsgIot9YmJpXoksrslzXUXcKUXtfQu\n"
	"bP/OgcND6BUnY163atpBsMmUJ4Npvyi0bmZlMrzbaXmxvNh0neBA6DI9aGX6aaXg\n"
	"+Mfu\n"
	"-----END CERTIFICATE-----\n";

const char kKatSigHex[] =
	"7ec2f432684f6001e2d402b519efab99ec49f06cffb88ab3f5bae19d2667a76ffa5e567126c9e825b8a0fd5e3408687f0466cf512e795d9197443961905c186554da9c3f95c5473e477c59c5803f510378ccca5d67ad37e07cdb2552eaad59a88fe6bea02f2ff2ea1e5f2b3086861b3e90dcdd2dc37bdf9a0728a89c1d9eac124800601fb1c05d0cd51796e8d95c559df7eb0ae85904182c2587828197313eed5461aa789785d5c4b95f3c723422c4562e19b93eb747adea7eb056449c41a67da957f77f1f639d05a7482a913eb31e7c0925bcbdf16352bc7fe3cdcfaaee2b00f8f6e53137d13e23993b5f369293db8179876000e3d707a09cbe7042d529aa36";

std::string hex(const unsigned char *p, size_t n) {
	static const char d[] = "0123456789abcdef";
	std::string s;
	for (size_t i = 0; i < n; i++) {
		s += d[p[i] >> 4];
		s += d[p[i] & 15];
	}
	return s;
}

std::string unhex(const std::string &h) {
	std::string r;
	for (size_t i = 0; i + 1 < h.size(); i += 2) r += (char)strtol(h.substr(i, 2).c_str(), nullptr, 16);
	return r;
}

/// The MD5 digest of "abc" in binary form.
std::string abcDigest() { return unhex("900150983cd24fb0d6963f7d28e17f72"); }

dgssl::PKeyPtr readKey(const char *pem) {
	dgssl::BioPtr bio = dgssl::bioFromMem(pem, -1);
	return dgssl::PKeyPtr(PEM_read_bio_PrivateKey(bio.get(), nullptr, nullptr, nullptr));
}

std::string makeTempDir() {
	char tmpl[] = "/tmp/dg-tls-test.XXXXXX";
	char *d = mkdtemp(tmpl);
	return d ? d : "";
}

int exIndexFreed;
void countFree(void *, void *data, CRYPTO_EX_DATA *, int, long, void *) { if (data) exIndexFreed++; }

}

TEST(SslRaii, ContextIsFreedOnScopeExit) {
	int idx = SSL_CTX_get_ex_new_index(0, nullptr, nullptr, nullptr, countFree);
	exIndexFreed = 0;
	{
		dgssl::CtxPtr ctx(SSL_CTX_new(TLS_server_method()));
		ASSERT_TRUE(ctx);
		SSL_CTX_set_ex_data(ctx.get(), idx, ctx.get());
	}
	EXPECT_EQ(1, exIndexFreed);
}

TEST(SslRaii, ConnectionIsFreedOnScopeExit) {
	dgssl::CtxPtr ctx(SSL_CTX_new(TLS_client_method()));
	int idx = SSL_get_ex_new_index(0, nullptr, nullptr, nullptr, countFree);
	exIndexFreed = 0;
	{
		dgssl::SslPtr ssl(SSL_new(ctx.get()));
		ASSERT_TRUE(ssl);
		SSL_set_ex_data(ssl.get(), idx, ssl.get());
	}
	EXPECT_EQ(1, exIndexFreed);
}

TEST(SslRaii, CertificateIsFreedOnScopeExit) {
	int idx = X509_get_ex_new_index(0, nullptr, nullptr, nullptr, countFree);
	exIndexFreed = 0;
	{
		dgssl::X509Ptr x(X509_new());
		ASSERT_TRUE(x);
		X509_set_ex_data(x.get(), idx, x.get());
	}
	EXPECT_EQ(1, exIndexFreed);
}

TEST(SslRaii, SessionIsFreedOnScopeExit) {
	int idx = SSL_SESSION_get_ex_new_index(0, nullptr, nullptr, nullptr, countFree);
	exIndexFreed = 0;
	{
		dgssl::SessionPtr s(SSL_SESSION_new());
		ASSERT_TRUE(s);
		SSL_SESSION_set_ex_data(s.get(), idx, s.get());
	}
	EXPECT_EQ(1, exIndexFreed);
}

TEST(SslRaii, BioIsFreedOnScopeExit) {
	int idx = BIO_get_ex_new_index(0, nullptr, nullptr, nullptr, countFree);
	exIndexFreed = 0;
	{
		dgssl::BioPtr b(BIO_new(BIO_s_mem()));
		ASSERT_TRUE(b);
		BIO_set_ex_data(b.get(), idx, b.get());
	}
	EXPECT_EQ(1, exIndexFreed);
}

TEST(SslRaii, MoveTransfersOwnership) {
	int idx = SSL_CTX_get_ex_new_index(0, nullptr, nullptr, nullptr, countFree);
	exIndexFreed = 0;
	{
		dgssl::CtxPtr a(SSL_CTX_new(TLS_server_method()));
		SSL_CTX_set_ex_data(a.get(), idx, a.get());
		dgssl::CtxPtr b = std::move(a);
		EXPECT_FALSE(a);
		EXPECT_TRUE(b);
		EXPECT_EQ(0, exIndexFreed);
	}
	EXPECT_EQ(1, exIndexFreed);
}

TEST(SslRaii, NullPointersAreHarmless) {
	dgssl::CtxPtr c;
	dgssl::SslPtr s;
	dgssl::X509Ptr x;
	dgssl::PKeyPtr k;
	dgssl::PKeyCtxPtr kc;
	dgssl::BioPtr b;
	dgssl::SessionPtr se;
	EXPECT_FALSE(c || s || x || k || kc || b || se);
}

TEST(SslRaii, MemoryBioReadsTheGivenBytes) {
	dgssl::BioPtr b = dgssl::bioFromMem("abc", 3);
	char buf[8] = {0};
	ASSERT_TRUE(b);
	EXPECT_EQ(3, BIO_read(b.get(), buf, sizeof(buf)));
	EXPECT_STREQ("abc", buf);
}

namespace {
struct Generated {
	EVP_PKEY *pkey = nullptr;
	X509 *cert = nullptr;
	~Generated() {
		EVP_PKEY_free(pkey);
		X509_free(cert);
	}
};

bool hasSan(X509 *x, int type, const std::string &value) {
	GENERAL_NAMES *names = (GENERAL_NAMES *)X509_get_ext_d2i(x, NID_subject_alt_name, nullptr, nullptr);
	bool found = false;
	for (int i = 0; names && i < sk_GENERAL_NAME_num(names); i++) {
		GENERAL_NAME *n = sk_GENERAL_NAME_value(names, i);
		if (n->type != type) continue;
		if (type == GEN_DNS) {
			std::string v((const char *)ASN1_STRING_get0_data(n->d.dNSName), ASN1_STRING_length(n->d.dNSName));
			found |= v == value;
		} else if (type == GEN_IPADD) {
			found |= hex(ASN1_STRING_get0_data(n->d.iPAddress), ASN1_STRING_length(n->d.iPAddress)) == value;
		}
	}
	GENERAL_NAMES_free(names);
	return found;
}

std::string subjectCN(X509 *x) {
	char buf[256] = {0};
	X509_NAME_get_text_by_NID(X509_get_subject_name(x), NID_commonName, buf, sizeof(buf));
	return buf;
}
}

TEST(SelfSigned, KeyIsEcP256) {
	Generated g;
	ASSERT_EQ(0, sslway_selfsigned("proxy.example.org", &g.pkey, &g.cert));
	EXPECT_TRUE(EVP_PKEY_is_a(g.pkey, "EC"));
	char group[64] = {0};
	size_t len = 0;
	ASSERT_TRUE(EVP_PKEY_get_utf8_string_param(g.pkey, "group", group, sizeof(group), &len));
	EXPECT_STREQ("prime256v1", group);
	EXPECT_EQ(256, EVP_PKEY_get_bits(g.pkey));
}

TEST(SelfSigned, SignedWithSha256) {
	Generated g;
	ASSERT_EQ(0, sslway_selfsigned("proxy.example.org", &g.pkey, &g.cert));
	EXPECT_EQ(NID_ecdsa_with_SHA256, X509_get_signature_nid(g.cert));
}

TEST(SelfSigned, IsSelfSignedAndVerifies) {
	Generated g;
	ASSERT_EQ(0, sslway_selfsigned("proxy.example.org", &g.pkey, &g.cert));
	EXPECT_EQ(1, X509_verify(g.cert, g.pkey));
	EXPECT_EQ(0, X509_NAME_cmp(X509_get_subject_name(g.cert), X509_get_issuer_name(g.cert)));
	EXPECT_EQ(3, X509_get_version(g.cert) + 1);
}

TEST(SelfSigned, SubjectIsTheHost) {
	Generated g;
	ASSERT_EQ(0, sslway_selfsigned("proxy.example.org", &g.pkey, &g.cert));
	EXPECT_EQ("proxy.example.org", subjectCN(g.cert));
}

TEST(SelfSigned, AltNamesHoldHostAndLoopback) {
	Generated g;
	ASSERT_EQ(0, sslway_selfsigned("proxy.example.org", &g.pkey, &g.cert));
	EXPECT_TRUE(hasSan(g.cert, GEN_DNS, "proxy.example.org"));
	EXPECT_TRUE(hasSan(g.cert, GEN_IPADD, "7f000001"));
	EXPECT_EQ(1, X509_check_host(g.cert, "proxy.example.org", 0, 0, nullptr));
	EXPECT_EQ(1, X509_check_ip_asc(g.cert, "127.0.0.1", 0));
}

TEST(SelfSigned, AddressHostBecomesIpAltName) {
	Generated g;
	ASSERT_EQ(0, sslway_selfsigned("10.1.2.3", &g.pkey, &g.cert));
	EXPECT_TRUE(hasSan(g.cert, GEN_IPADD, "0a010203"));
	EXPECT_TRUE(hasSan(g.cert, GEN_IPADD, "7f000001"));
	EXPECT_FALSE(hasSan(g.cert, GEN_DNS, "10.1.2.3"));
}

TEST(SelfSigned, LoopbackHostGivesOneAltName) {
	Generated g;
	ASSERT_EQ(0, sslway_selfsigned("127.0.0.1", &g.pkey, &g.cert));
	GENERAL_NAMES *names = (GENERAL_NAMES *)X509_get_ext_d2i(g.cert, NID_subject_alt_name, nullptr, nullptr);
	ASSERT_NE(nullptr, names);
	EXPECT_EQ(1, sk_GENERAL_NAME_num(names));
	GENERAL_NAMES_free(names);
}

TEST(SelfSigned, ValidFor825Days) {
	Generated g;
	ASSERT_EQ(0, sslway_selfsigned("proxy.example.org", &g.pkey, &g.cert));
	time_t now = time(nullptr);
	ASSERT_TRUE(ASN1_TIME_cmp_time_t(X509_get0_notBefore(g.cert), now) <= 0);
	int days = 0, secs = 0;
	ASN1_TIME *from = ASN1_TIME_adj(nullptr, now, 0, 0);
	ASSERT_TRUE(ASN1_TIME_diff(&days, &secs, from, X509_get0_notAfter(g.cert)));
	ASN1_STRING_free(from);
	EXPECT_EQ(825, days);
}

TEST(SelfSigned, MarksAServerLeafCertificate) {
	Generated g;
	ASSERT_EQ(0, sslway_selfsigned("proxy.example.org", &g.pkey, &g.cert));
	EXPECT_EQ(0, X509_check_ca(g.cert));
	EXPECT_TRUE(X509_get_extended_key_usage(g.cert) & XKU_SSL_SERVER);
	EXPECT_TRUE(X509_get_key_usage(g.cert) & KU_DIGITAL_SIGNATURE);
}

TEST(SelfSigned, InvalidHostFallsBackToTheMachineName) {
	Generated g;
	ASSERT_EQ(0, sslway_selfsigned("bad host;name", &g.pkey, &g.cert));
	EXPECT_NE("bad host;name", subjectCN(g.cert));
	EXPECT_FALSE(subjectCN(g.cert).empty());
}

TEST(SelfSigned, SerialNumbersDiffer) {
	Generated a, b;
	ASSERT_EQ(0, sslway_selfsigned("proxy.example.org", &a.pkey, &a.cert));
	ASSERT_EQ(0, sslway_selfsigned("proxy.example.org", &b.pkey, &b.cert));
	EXPECT_NE(0, ASN1_INTEGER_cmp(X509_get_serialNumber(a.cert), X509_get_serialNumber(b.cert)));
}

TEST(SelfSigned, FilesAreStoredWithPrivateKeyMode) {
	std::string dir = makeTempDir();
	ASSERT_FALSE(dir.empty());
	char cert[1100], key[1100];
	ASSERT_EQ(0, sslway_autocertFiles((dir + "/etc/certs").c_str(), cert, key, sizeof(cert)));
	struct stat st;
	ASSERT_EQ(0, stat(key, &st));
	EXPECT_EQ(0600, st.st_mode & 0777);
	ASSERT_EQ(0, stat(cert, &st));
	EXPECT_EQ(0, st.st_mode & 0022);
	EXPECT_EQ(dir + "/etc/certs/server-cert.pem", cert);
	EXPECT_EQ(dir + "/etc/certs/server-key.pem", key);

	FILE *fp = fopen(cert, "r");
	ASSERT_NE(nullptr, fp);
	dgssl::X509Ptr x(PEM_read_X509(fp, nullptr, nullptr, nullptr));
	fclose(fp);
	fp = fopen(key, "r");
	ASSERT_NE(nullptr, fp);
	dgssl::PKeyPtr k(PEM_read_PrivateKey(fp, nullptr, nullptr, nullptr));
	fclose(fp);
	ASSERT_TRUE(x && k);
	EXPECT_EQ(1, X509_check_private_key(x.get(), k.get()));
	EXPECT_TRUE(EVP_PKEY_is_a(k.get(), "EC"));

	std::string cmd = "rm -r '" + dir + "'";
	ASSERT_EQ(0, system(cmd.c_str()));
}

TEST(SelfSigned, ExistingFilesAreKept) {
	std::string dir = makeTempDir();
	ASSERT_FALSE(dir.empty());
	char cert[1100], key[1100], cert2[1100], key2[1100];
	ASSERT_EQ(0, sslway_autocertFiles(dir.c_str(), cert, key, sizeof(cert)));
	auto slurp = [](const char *p) {
		std::string s;
		FILE *fp = fopen(p, "r");
		char b[512];
		size_t n;
		while (fp && (n = fread(b, 1, sizeof(b), fp)) > 0) s.append(b, n);
		if (fp) fclose(fp);
		return s;
	};
	std::string before = slurp(cert) + slurp(key);
	ASSERT_EQ(0, sslway_autocertFiles(dir.c_str(), cert2, key2, sizeof(cert2)));
	EXPECT_EQ(before, slurp(cert2) + slurp(key2));
	std::string cmd = "rm -r '" + dir + "'";
	ASSERT_EQ(0, system(cmd.c_str()));
}

TEST(SelfSigned, UnwritableDirectoryIsReported) {
	char cert[1100], key[1100];
	EXPECT_NE(0, sslway_autocertFiles("/proc/dg-no-such/certs", cert, key, sizeof(cert)));
}

TEST(Rc4, KnownVectorKeyPlaintext) {
	RC4_KEY k;
	const unsigned char key[] = "Key";
	const unsigned char in[] = "Plaintext";
	unsigned char out[9];
	myRC4_set_key(&k, 3, key);
	myRC4(&k, 9, in, out);
	EXPECT_EQ("bbf316e8d940af0ad3", hex(out, 9));
}

TEST(Rc4, KnownVectorWikipedia) {
	RC4_KEY k;
	const unsigned char key[] = "Wiki";
	const unsigned char in[] = "pedia";
	unsigned char out[5];
	myRC4_set_key(&k, 4, key);
	myRC4(&k, 5, in, out);
	EXPECT_EQ("1021bf0420", hex(out, 5));
}

TEST(Rc4, KnownVectorAttackAtDawn) {
	RC4_KEY k;
	const unsigned char key[] = "Secret";
	const unsigned char in[] = "Attack at dawn";
	unsigned char out[14];
	myRC4_set_key(&k, 6, key);
	myRC4(&k, 14, in, out);
	EXPECT_EQ("45a01f645fc35b383552544b9bf5", hex(out, 14));
}

TEST(Rc4, Rfc6229KeyStream40Bit) {
	RC4_KEY k;
	const unsigned char key[] = {1, 2, 3, 4, 5};
	unsigned char zero[16] = {0}, out[16];
	myRC4_set_key(&k, 5, key);
	myRC4(&k, 16, zero, out);
	EXPECT_EQ("b2396305f03dc027ccc3524a0a1118a8", hex(out, 16));
}

TEST(Rc4, Rfc6229KeyStream128Bit) {
	RC4_KEY k;
	const unsigned char key[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	unsigned char zero[16] = {0}, out[16];
	myRC4_set_key(&k, 16, key);
	myRC4(&k, 16, zero, out);
	EXPECT_EQ("9ac7cc9a609d1ef7b2932899cde41b97", hex(out, 16));
}

TEST(Rc4, ChunkedUseEqualsOneCall) {
	RC4_KEY a, b;
	const unsigned char key[] = "chunk";
	unsigned char in[100], o1[100], o2[100];
	for (int i = 0; i < 100; i++) in[i] = (unsigned char)i;
	myRC4_set_key(&a, 5, key);
	myRC4(&a, 100, in, o1);
	myRC4_set_key(&b, 5, key);
	myRC4(&b, 33, in, o2);
	myRC4(&b, 67, in + 33, o2 + 33);
	EXPECT_EQ(0, memcmp(o1, o2, 100));
}

TEST(Rc4, DecryptionIsTheSameOperation) {
	RC4_KEY a, b;
	const unsigned char key[] = "roundtrip";
	const unsigned char in[] = "The quick brown fox";
	unsigned char enc[sizeof(in)], dec[sizeof(in)];
	myRC4_set_key(&a, 9, key);
	myRC4(&a, sizeof(in), in, enc);
	myRC4_set_key(&b, 9, key);
	myRC4(&b, sizeof(in), enc, dec);
	EXPECT_EQ(0, memcmp(in, dec, sizeof(in)));
}

TEST(RsaSign, MatchesTheLegacyMd5Signature) {
	dgssl::PKeyPtr k = readKey(kKatKey);
	ASSERT_TRUE(k);
	std::string md5 = abcDigest();
	CStr(sig, 512);
	unsigned int slen = 512;
	ASSERT_EQ(1, signRSA(k.get(), md5.data(), 16, AVStr(sig), &slen));
	ASSERT_EQ(256u, slen);
	EXPECT_EQ(kKatSigHex, hex((const unsigned char *)sig, slen));
}

TEST(RsaSign, VerifiesTheLegacyMd5Signature) {
	dgssl::PKeyPtr k = readKey(kKatKey);
	ASSERT_TRUE(k);
	std::string md5 = abcDigest(), sig = unhex(kKatSigHex);
	EXPECT_EQ(1, verifyRSA(k.get(), md5.data(), 16, sig.data(), sig.size()));
}

TEST(RsaSign, RejectsAChangedDigest) {
	dgssl::PKeyPtr k = readKey(kKatKey);
	std::string md5 = abcDigest(), sig = unhex(kKatSigHex);
	md5[0] ^= 1;
	EXPECT_EQ(0, verifyRSA(k.get(), md5.data(), 16, sig.data(), sig.size()));
}

TEST(RsaSign, RejectsAChangedSignature) {
	dgssl::PKeyPtr k = readKey(kKatKey);
	std::string md5 = abcDigest(), sig = unhex(kKatSigHex);
	sig[10] ^= 1;
	EXPECT_EQ(0, verifyRSA(k.get(), md5.data(), 16, sig.data(), sig.size()));
}

TEST(RsaSign, RejectsASignatureOfAnotherKey) {
	dgssl::PKeyPtr other(EVP_RSA_gen(2048));
	ASSERT_TRUE(other);
	std::string md5 = abcDigest(), sig = unhex(kKatSigHex);
	EXPECT_EQ(0, verifyRSA(other.get(), md5.data(), 16, sig.data(), sig.size()));
}

TEST(RsaSign, RejectsADigestOfWrongLength) {
	dgssl::PKeyPtr k = readKey(kKatKey);
	CStr(sig, 512);
	unsigned int slen = 512;
	EXPECT_EQ(0, signRSA(k.get(), "short", 5, AVStr(sig), &slen));
}

TEST(RsaSign, RefusesASmallSignatureBuffer) {
	dgssl::PKeyPtr k = readKey(kKatKey);
	std::string md5 = abcDigest();
	CStr(sig, 512);
	unsigned int slen = 100;
	EXPECT_EQ(0, signRSA(k.get(), md5.data(), 16, AVStr(sig), &slen));
}

TEST(RsaSign, NewKeysSignAndVerify) {
	dgssl::PKeyPtr k(EVP_RSA_gen(2048));
	ASSERT_TRUE(k);
	std::string md5 = abcDigest();
	CStr(sig, 512);
	unsigned int slen = 512;
	ASSERT_EQ(1, signRSA(k.get(), md5.data(), 16, AVStr(sig), &slen));
	EXPECT_EQ(1, verifyRSA(k.get(), md5.data(), 16, sig, slen));
}

TEST(RsaSign, PemApiSignsAndVerifiesWithTheCertificate) {
	std::string md5 = abcDigest();
	CStr(sig, 512);
	unsigned int slen = 512;
	ASSERT_EQ(1, SignRSA("kat-key.pem", kKatKey, "", md5.data(), 16, AVStr(sig), &slen));
	EXPECT_EQ(kKatSigHex, hex((const unsigned char *)sig, slen));
	EXPECT_EQ(1, VerifyRSA("kat-cert.pem", kKatCert, md5.data(), 16, sig, slen));
	md5[3] ^= 1;
	EXPECT_EQ(0, VerifyRSA("kat-cert.pem", kKatCert, md5.data(), 16, sig, slen));
}

TEST(RsaSign, PemApiReadsAnEncryptedKey) {
	dgssl::PKeyPtr k = readKey(kKatKey);
	dgssl::BioPtr out(BIO_new(BIO_s_mem()));
	ASSERT_EQ(1, PEM_write_bio_PrivateKey_traditional(out.get(), k.get(), EVP_des_ede3_cbc(),
		(const unsigned char *)"secret", 6, nullptr, nullptr));
	char *p;
	long n = BIO_get_mem_data(out.get(), &p);
	std::string pem(p, n);
	ASSERT_NE(std::string::npos, pem.find("DES-EDE3-CBC"));
	std::string md5 = abcDigest();
	CStr(sig, 512);
	unsigned int slen = 512;
	EXPECT_EQ(0, SignRSA("enc-bad.pem", pem.c_str(), "wrong", md5.data(), 16, AVStr(sig), &slen));
	ASSERT_EQ(1, SignRSA("enc-key.pem", pem.c_str(), "secret", md5.data(), 16, AVStr(sig), &slen));
	EXPECT_EQ(kKatSigHex, hex((const unsigned char *)sig, slen));
}

TEST(RsaSign, PemApiRejectsAnEcKey) {
	Generated g;
	ASSERT_EQ(0, sslway_selfsigned("proxy.example.org", &g.pkey, &g.cert));
	dgssl::BioPtr out(BIO_new(BIO_s_mem()));
	ASSERT_EQ(1, PEM_write_bio_PrivateKey(out.get(), g.pkey, nullptr, nullptr, 0, nullptr, nullptr));
	char *p;
	long n = BIO_get_mem_data(out.get(), &p);
	std::string pem(p, n);
	std::string md5 = abcDigest();
	CStr(sig, 512);
	unsigned int slen = 512;
	EXPECT_EQ(0, SignRSA("ec-key.pem", pem.c_str(), "", md5.data(), 16, AVStr(sig), &slen));
}

TEST(RsaSign, PublicKeyRecoversThePrivateKeyBlock) {
	dgssl::PKeyPtr k = readKey(kKatKey);
	dgssl::PKeyCtxPtr pc(EVP_PKEY_CTX_new(k.get(), nullptr));
	ASSERT_TRUE(pc);
	ASSERT_GT(EVP_PKEY_sign_init(pc.get()), 0);
	ASSERT_GT(EVP_PKEY_CTX_set_rsa_padding(pc.get(), RSA_PKCS1_PADDING), 0);
	const unsigned char msg[] = "hello rsa";
	unsigned char enc[256];
	size_t elen = sizeof(enc);
	ASSERT_GT(EVP_PKEY_sign(pc.get(), enc, &elen, msg, sizeof(msg)), 0);
	CStr(dec, 512);
	int dlen = pubDecyptRSA(kKatPub, elen, (const char *)enc, AVStr(dec));
	ASSERT_EQ((int)sizeof(msg), dlen);
	EXPECT_EQ(0, memcmp(dec, msg, sizeof(msg)));
}

TEST(RsaSign, PublicKeyRejectsGarbage) {
	CStr(dec, 512);
	unsigned char junk[256];
	memset(junk, 0x5a, sizeof(junk));
	EXPECT_EQ(-1, pubDecyptRSA(kKatPub, sizeof(junk), (const char *)junk, AVStr(dec)));
	EXPECT_EQ(-1, pubDecyptRSA("not a key", 4, "abcd", AVStr(dec)));
}

TEST(RsaTool, NewKeyIsWrittenInPkcs1Format) {
	std::string dir = makeTempDir();
	ASSERT_FALSE(dir.empty());
	std::string file = dir + "/rsa.pem";
	const char *av[] = {"rsa", "-nopass", "-f", file.c_str(), "new", "1024"};
	ASSERT_EQ(0, rsa_main(6, av));
	std::string pem;
	FILE *fp = fopen(file.c_str(), "r");
	ASSERT_NE(nullptr, fp);
	char b[512];
	size_t n;
	while ((n = fread(b, 1, sizeof(b), fp)) > 0) pem.append(b, n);
	fclose(fp);
	EXPECT_NE(std::string::npos, pem.find("-----BEGIN RSA PRIVATE KEY-----"));
	EXPECT_NE(std::string::npos, pem.find("-----BEGIN RSA PUBLIC KEY-----"));

	const char *av2[] = {"rsa", "-f", file.c_str(), "-i", "hello", "enc"};
	testing::internal::CaptureStdout();
	ASSERT_EQ(0, rsa_main(6, av2));
	std::string out = testing::internal::GetCapturedStdout();
	EXPECT_NE(std::string::npos, out.find("->(6) hello"));

	std::string cmd = "rm -r '" + dir + "'";
	ASSERT_EQ(0, system(cmd.c_str()));
}

namespace {
struct Link {
	dgssl::CtxPtr sctx, cctx;
	dgssl::SslPtr s, c;
	EVP_PKEY *pkey = nullptr;
	X509 *cert = nullptr;
	bool ok = false;
	int version;

	explicit Link(int ver) : version(ver) {
		if (sslway_selfsigned("proxy.example.org", &pkey, &cert) != 0) return;
		sctx.reset(SSL_CTX_new(TLS_server_method()));
		cctx.reset(SSL_CTX_new(TLS_client_method()));
		ok = sctx && cctx && SSL_CTX_use_certificate(sctx.get(), cert) == 1 &&
			SSL_CTX_use_PrivateKey(sctx.get(), pkey) == 1;
		for (SSL_CTX *x : {sctx.get(), cctx.get()}) {
			if (!x) continue;
			SSL_CTX_set_min_proto_version(x, ver);
			SSL_CTX_set_max_proto_version(x, ver);
		}
	}
	~Link() {
		EVP_PKEY_free(pkey);
		X509_free(cert);
	}

	/// Runs a handshake over a pair of memory BIOs, optionally resuming the session.
	bool connect(SSL_SESSION *resume = nullptr) {
		s.reset(SSL_new(sctx.get()));
		c.reset(SSL_new(cctx.get()));
		BIO *b1 = nullptr, *b2 = nullptr;
		if (!s || !c || !BIO_new_bio_pair(&b1, 0, &b2, 0)) return false;
		SSL_set_bio(s.get(), b1, b1);
		SSL_set_bio(c.get(), b2, b2);
		SSL_set_accept_state(s.get());
		SSL_set_connect_state(c.get());
		if (resume) SSL_set_session(c.get(), resume);
		bool sdone = false, cdone = false;
		for (int i = 0; i < 100 && !(sdone && cdone); i++) {
			if (!cdone) cdone = SSL_do_handshake(c.get()) == 1;
			if (!sdone) sdone = SSL_do_handshake(s.get()) == 1;
		}
		return sdone && cdone;
	}

	/// Moves one application record to the client; TLS 1.3 sends the session ticket before it.
	bool exchange() {
		char buf[8];
		if (SSL_write(s.get(), "x", 1) != 1) return false;
		return SSL_read(c.get(), buf, sizeof(buf)) == 1;
	}
};
}

TEST(TlsSession, Tls12ClientSessionHasAnIdAndVersion) {
	Link l(TLS1_2_VERSION);
	ASSERT_TRUE(l.ok && l.connect());
	ASSERT_TRUE(l.exchange());
	SSL_SESSION *sess = SSL_get_session(l.c.get());
	unsigned int len = 0;
	const unsigned char *id = SSL_SESSION_get_id(sess, &len);
	ASSERT_NE(nullptr, id);
	EXPECT_EQ(32u, len);
	EXPECT_EQ(TLS1_2_VERSION, SSL_SESSION_get_protocol_version(sess));
}

TEST(TlsSession, Tls13SessionHasAVersion) {
	Link l(TLS1_3_VERSION);
	ASSERT_TRUE(l.ok && l.connect());
	ASSERT_TRUE(l.exchange());
	EXPECT_EQ(TLS1_3_VERSION, SSL_SESSION_get_protocol_version(SSL_get_session(l.c.get())));
}

TEST(TlsSession, Tls12SessionResumesAfterDerRoundTrip) {
	Link l(TLS1_2_VERSION);
	ASSERT_TRUE(l.ok && l.connect());
	ASSERT_TRUE(l.exchange());
	unsigned char der[4096], *p = der;
	int len = i2d_SSL_SESSION(SSL_get_session(l.c.get()), &p);
	ASSERT_GT(len, 0);
	const unsigned char *q = der;
	dgssl::SessionPtr back(d2i_SSL_SESSION(nullptr, &q, len));
	ASSERT_TRUE(back);
	ASSERT_TRUE(l.connect(back.get()));
	EXPECT_EQ(1, SSL_session_reused(l.c.get()));
}

TEST(TlsSession, Tls13SessionResumesAfterDerRoundTrip) {
	Link l(TLS1_3_VERSION);
	ASSERT_TRUE(l.ok && l.connect());
	ASSERT_TRUE(l.exchange());
	unsigned char der[4096], *p = der;
	int len = i2d_SSL_SESSION(SSL_get_session(l.c.get()), &p);
	ASSERT_GT(len, 0);
	const unsigned char *q = der;
	dgssl::SessionPtr back(d2i_SSL_SESSION(nullptr, &q, len));
	ASSERT_TRUE(back);
	ASSERT_TRUE(l.connect(back.get()));
	EXPECT_EQ(1, SSL_session_reused(l.c.get()));
}
