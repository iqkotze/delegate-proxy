#ifndef _SSL_RAII_H
#define _SSL_RAII_H
#include <memory>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/ssl.h>
#include <openssl/x509.h>

namespace dgssl {

/// Releases OpenSSL objects with their matching free function.
struct Deleter {
	void operator()(SSL_CTX *p) const { SSL_CTX_free(p); }
	void operator()(SSL *p) const { SSL_free(p); }
	void operator()(SSL_SESSION *p) const { SSL_SESSION_free(p); }
	void operator()(X509 *p) const { X509_free(p); }
	void operator()(EVP_PKEY *p) const { EVP_PKEY_free(p); }
	void operator()(EVP_PKEY_CTX *p) const { EVP_PKEY_CTX_free(p); }
	void operator()(BIO *p) const { BIO_free(p); }
};

template <class T> using Ptr = std::unique_ptr<T, Deleter>;
using CtxPtr = Ptr<SSL_CTX>;
using SslPtr = Ptr<SSL>;
using SessionPtr = Ptr<SSL_SESSION>;
using X509Ptr = Ptr<X509>;
using PKeyPtr = Ptr<EVP_PKEY>;
using PKeyCtxPtr = Ptr<EVP_PKEY_CTX>;
using BioPtr = Ptr<BIO>;

/// Returns a memory BIO holding a copy of the bytes.
inline BioPtr bioFromMem(const void *data, int len) {
	return BioPtr(BIO_new_mem_buf(data, len));
}

}
#endif
