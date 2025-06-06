#ifndef NETWORK_TOKEN_H
#define NETWORK_TOKEN_H


#ifndef NETWORK_TOKEN_DISABLE_QUITE_COMPACT_NETWORK_PAYLOAD
#ifndef QUITE_COMPACT_NETWORK_PAYLOAD_USE_INT64
#define QUITE_COMPACT_NETWORK_PAYLOAD_USE_INT64
#endif
#include "quite_compact_network_payload/quite_compact_network_payload.h"
#endif

#ifndef NETWORK_TOKEN_DISABLE_BASE64
#include "network_token_base.h"
#endif

#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>

#include <algorithm>
#include <chrono>
#include <codecvt>
#include <functional>
#include <iterator>
#include <locale>
#include <memory>
#include <set>
#include <system_error>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#if __cplusplus >= 201402L
#ifdef __has_include
#if __has_include(<experimental/type_traits>)
#include <experimental/type_traits>
#endif
#endif
#endif

#if OPENSSL_VERSION_NUMBER >= 0x30000000L // 3.0.0
#define NETWORK_TOKEN_OPENSSL_3_0
#elif OPENSSL_VERSION_NUMBER >= 0x10101000L // 1.1.1
#define NETWORK_TOKEN_OPENSSL_1_1_1
#elif OPENSSL_VERSION_NUMBER >= 0x10100000L // 1.1.0
#define NETWORK_TOKEN_OPENSSL_1_1_0
#elif OPENSSL_VERSION_NUMBER >= 0x10000000L // 1.0.0
#define NETWORK_TOKEN_OPENSSL_1_0_0
#endif

#if defined(LIBRESSL_VERSION_NUMBER)
#define NETWORK_TOKEN_OPENSSL_1_0_0
#endif

#if defined(LIBWOLFSSL_VERSION_HEX)
#define NETWORK_TOKEN_OPENSSL_1_1_1
#endif

#ifndef NETWORK_TOKEN_CLAIM_EXPLICIT
#define NETWORK_TOKEN_CLAIM_EXPLICIT explicit
#endif

/**
 * \brief JSON Web Token
 *
 * A namespace to contain everything related to handling JSON Web Tokens, NETWORK_TOKEN for short,
 * as a part of [RFC7519](https://tools.ietf.org/html/rfc7519), or alternatively for
 * JWS (JSON Web Signature) from [RFC7515](https://tools.ietf.org/html/rfc7515)
 */
namespace network_token {
	using date = std::chrono::system_clock::time_point;

	/**
	 * \brief Everything related to error codes issued by the library
	 */
	namespace error {
		struct signature_verification_exception : public std::system_error {
			using system_error::system_error;
		};
		struct signature_generation_exception : public std::system_error {
			using system_error::system_error;
		};
		struct rsa_exception : public std::system_error {
			using system_error::system_error;
		};
		struct ecdsa_exception : public std::system_error {
			using system_error::system_error;
		};
		struct token_verification_exception : public std::system_error {
			using system_error::system_error;
		};
		/**
		 * \brief Errors related to processing of RSA signatures
		 */
		enum class rsa_error {
			ok = 0,
			cert_load_failed = 10,
			get_key_failed,
			write_key_failed,
			write_cert_failed,
			convert_to_pem_failed,
			load_key_bio_write,
			load_key_bio_read,
			create_mem_bio_failed,
			no_key_provided
		};
		/**
		 * \brief Error category for RSA errors
		 */
		inline std::error_category& rsa_error_category() {
			class rsa_error_cat : public std::error_category {
			public:
				const char* name() const noexcept override { return "rsa_error"; };
				std::string message(int ev) const override {
					switch (static_cast<rsa_error>(ev)) {
					case rsa_error::ok: return "no error";
					case rsa_error::cert_load_failed: return "error loading cert into memory";
					case rsa_error::get_key_failed: return "error getting key from certificate";
					case rsa_error::write_key_failed: return "error writing key data in PEM format";
					case rsa_error::write_cert_failed: return "error writing cert data in PEM format";
					case rsa_error::convert_to_pem_failed: return "failed to convert key to pem";
					case rsa_error::load_key_bio_write: return "failed to load key: bio write failed";
					case rsa_error::load_key_bio_read: return "failed to load key: bio read failed";
					case rsa_error::create_mem_bio_failed: return "failed to create memory bio";
					case rsa_error::no_key_provided: return "at least one of public or private key need to be present";
					default: return "unknown RSA error";
					}
				}
			};
			static rsa_error_cat cat;
			return cat;
		}

		inline std::error_code make_error_code(rsa_error e) { return {static_cast<int>(e), rsa_error_category()}; }
		/**
		 * \brief Errors related to processing of RSA signatures
		 */
		enum class ecdsa_error {
			ok = 0,
			load_key_bio_write = 10,
			load_key_bio_read,
			create_mem_bio_failed,
			no_key_provided,
			invalid_key_size,
			invalid_key
		};
		/**
		 * \brief Error category for ECDSA errors
		 */
		inline std::error_category& ecdsa_error_category() {
			class ecdsa_error_cat : public std::error_category {
			public:
				const char* name() const noexcept override { return "ecdsa_error"; };
				std::string message(int ev) const override {
					switch (static_cast<ecdsa_error>(ev)) {
					case ecdsa_error::ok: return "no error";
					case ecdsa_error::load_key_bio_write: return "failed to load key: bio write failed";
					case ecdsa_error::load_key_bio_read: return "failed to load key: bio read failed";
					case ecdsa_error::create_mem_bio_failed: return "failed to create memory bio";
					case ecdsa_error::no_key_provided:
						return "at least one of public or private key need to be present";
					case ecdsa_error::invalid_key_size: return "invalid key size";
					case ecdsa_error::invalid_key: return "invalid key";
					default: return "unknown ECDSA error";
					}
				}
			};
			static ecdsa_error_cat cat;
			return cat;
		}

		inline std::error_code make_error_code(ecdsa_error e) { return {static_cast<int>(e), ecdsa_error_category()}; }

		/**
		 * \brief Errors related to verification of signatures
		 */
		enum class signature_verification_error {
			ok = 0,
			invalid_signature = 10,
			create_context_failed,
			verifyinit_failed,
			verifyupdate_failed,
			verifyfinal_failed,
			get_key_failed
		};
		/**
		 * \brief Error category for verification errors
		 */
		inline std::error_category& signature_verification_error_category() {
			class verification_error_cat : public std::error_category {
			public:
				const char* name() const noexcept override { return "signature_verification_error"; };
				std::string message(int ev) const override {
					switch (static_cast<signature_verification_error>(ev)) {
					case signature_verification_error::ok: return "no error";
					case signature_verification_error::invalid_signature: return "invalid signature";
					case signature_verification_error::create_context_failed:
						return "failed to verify signature: could not create context";
					case signature_verification_error::verifyinit_failed:
						return "failed to verify signature: VerifyInit failed";
					case signature_verification_error::verifyupdate_failed:
						return "failed to verify signature: VerifyUpdate failed";
					case signature_verification_error::verifyfinal_failed:
						return "failed to verify signature: VerifyFinal failed";
					case signature_verification_error::get_key_failed:
						return "failed to verify signature: Could not get key";
					default: return "unknown signature verification error";
					}
				}
			};
			static verification_error_cat cat;
			return cat;
		}

		inline std::error_code make_error_code(signature_verification_error e) {
			return {static_cast<int>(e), signature_verification_error_category()};
		}

		/**
		 * \brief Errors related to signature generation errors
		 */
		enum class signature_generation_error {
			ok = 0,
			hmac_failed = 10,
			create_context_failed,
			signinit_failed,
			signupdate_failed,
			signfinal_failed,
			ecdsa_do_sign_failed,
			digestinit_failed,
			digestupdate_failed,
			digestfinal_failed,
			rsa_padding_failed,
			rsa_private_encrypt_failed,
			get_key_failed
		};
		/**
		 * \brief Error category for signature generation errors
		 */
		inline std::error_category& signature_generation_error_category() {
			class signature_generation_error_cat : public std::error_category {
			public:
				const char* name() const noexcept override { return "signature_generation_error"; };
				std::string message(int ev) const override {
					switch (static_cast<signature_generation_error>(ev)) {
					case signature_generation_error::ok: return "no error";
					case signature_generation_error::hmac_failed: return "hmac failed";
					case signature_generation_error::create_context_failed:
						return "failed to create signature: could not create context";
					case signature_generation_error::signinit_failed:
						return "failed to create signature: SignInit failed";
					case signature_generation_error::signupdate_failed:
						return "failed to create signature: SignUpdate failed";
					case signature_generation_error::signfinal_failed:
						return "failed to create signature: SignFinal failed";
					case signature_generation_error::ecdsa_do_sign_failed: return "failed to generate ecdsa signature";
					case signature_generation_error::digestinit_failed:
						return "failed to create signature: DigestInit failed";
					case signature_generation_error::digestupdate_failed:
						return "failed to create signature: DigestUpdate failed";
					case signature_generation_error::digestfinal_failed:
						return "failed to create signature: DigestFinal failed";
					case signature_generation_error::rsa_padding_failed:
						return "failed to create signature: RSA_padding_add_PKCS1_PSS failed";
					case signature_generation_error::rsa_private_encrypt_failed:
						return "failed to create signature: RSA_private_encrypt failed";
					case signature_generation_error::get_key_failed:
						return "failed to generate signature: Could not get key";
					default: return "unknown signature generation error";
					}
				}
			};
			static signature_generation_error_cat cat = {};
			return cat;
		}

		inline std::error_code make_error_code(signature_generation_error e) {
			return {static_cast<int>(e), signature_generation_error_category()};
		}

		/**
		 * \brief Errors related to token verification errors
		 */
		enum class token_verification_error {
			ok = 0,
			wrong_algorithm = 10,
			missing_claim,
			claim_type_missmatch,
			claim_value_missmatch,
			token_expired,
			audience_missmatch
		};
		/**
		 * \brief Error category for token verification errors
		 */
		inline std::error_category& token_verification_error_category() {
			class token_verification_error_cat : public std::error_category {
			public:
				const char* name() const noexcept override { return "token_verification_error"; };
				std::string message(int ev) const override {
					switch (static_cast<token_verification_error>(ev)) {
					case token_verification_error::ok: return "no error";
					case token_verification_error::wrong_algorithm: return "wrong algorithm";
					case token_verification_error::missing_claim: return "decoded NETWORK_TOKEN is missing required claim(s)";
					case token_verification_error::claim_type_missmatch:
						return "claim type does not match expected type";
					case token_verification_error::claim_value_missmatch:
						return "claim value does not match expected value";
					case token_verification_error::token_expired: return "token expired";
					case token_verification_error::audience_missmatch:
						return "token doesn't contain the required audience";
					default: return "unknown token verification error";
					}
				}
			};
			static token_verification_error_cat cat = {};
			return cat;
		}

		inline std::error_code make_error_code(token_verification_error e) {
			return {static_cast<int>(e), token_verification_error_category()};
		}

		inline void throw_if_error(std::error_code ec) {
			if (ec) {
				if (ec.category() == rsa_error_category()) throw rsa_exception(ec);
				if (ec.category() == ecdsa_error_category()) throw ecdsa_exception(ec);
				if (ec.category() == signature_verification_error_category())
					throw signature_verification_exception(ec);
				if (ec.category() == signature_generation_error_category()) throw signature_generation_exception(ec);
				if (ec.category() == token_verification_error_category()) throw token_verification_exception(ec);
			}
		}
	} // namespace error

	// FIXME: Remove
	// Keep backward compat at least for a couple of revisions
	using error::ecdsa_exception;
	using error::rsa_exception;
	using error::signature_generation_exception;
	using error::signature_verification_exception;
	using error::token_verification_exception;
} // namespace network_token
namespace std {
	template<>
	struct is_error_code_enum<network_token::error::rsa_error> : true_type {};
	template<>
	struct is_error_code_enum<network_token::error::ecdsa_error> : true_type {};
	template<>
	struct is_error_code_enum<network_token::error::signature_verification_error> : true_type {};
	template<>
	struct is_error_code_enum<network_token::error::signature_generation_error> : true_type {};
	template<>
	struct is_error_code_enum<network_token::error::token_verification_error> : true_type {};
} // namespace std
namespace network_token {
	/**
	 * \brief A collection for working with certificates
	 *
	 * These _helpers_ are usefully when working with certificates OpenSSL APIs.
	 * For example, when dealing with JWKS (JSON Web Key Set)[https://tools.ietf.org/html/rfc7517]
	 * you maybe need to extract the modulus and exponent of an RSA Public Key.
	 */
	namespace helper {
		/**
		 * \brief Extract the public key of a pem certificate
		 *
		 * \param certstr	String containing the certificate encoded as pem
		 * \param pw		Password used to decrypt certificate (leave empty if not encrypted)
		 * \param ec		error_code for error_detection (gets cleared if no error occures)
		 */
		inline std::string extract_pubkey_from_cert(const std::string& certstr, const std::string& pw,
													std::error_code& ec) {
			ec.clear();
#if OPENSSL_VERSION_NUMBER <= 0x10100003L
			std::unique_ptr<BIO, decltype(&BIO_free_all)> certbio(
				BIO_new_mem_buf(const_cast<char*>(certstr.data()), static_cast<int>(certstr.size())), BIO_free_all);
#else
			std::unique_ptr<BIO, decltype(&BIO_free_all)> certbio(
				BIO_new_mem_buf(certstr.data(), static_cast<int>(certstr.size())), BIO_free_all);
#endif
			std::unique_ptr<BIO, decltype(&BIO_free_all)> keybio(BIO_new(BIO_s_mem()), BIO_free_all);
			if (!certbio || !keybio) {
				ec = error::rsa_error::create_mem_bio_failed;
				return {};
			}

			std::unique_ptr<X509, decltype(&X509_free)> cert(
				PEM_read_bio_X509(certbio.get(), nullptr, nullptr, const_cast<char*>(pw.c_str())), X509_free);
			if (!cert) {
				ec = error::rsa_error::cert_load_failed;
				return {};
			}
			std::unique_ptr<EVP_PKEY, decltype(&EVP_PKEY_free)> key(X509_get_pubkey(cert.get()), EVP_PKEY_free);
			if (!key) {
				ec = error::rsa_error::get_key_failed;
				return {};
			}
			if (PEM_write_bio_PUBKEY(keybio.get(), key.get()) == 0) {
				ec = error::rsa_error::write_key_failed;
				return {};
			}
			char* ptr = nullptr;
			auto len = BIO_get_mem_data(keybio.get(), &ptr);
			if (len <= 0 || ptr == nullptr) {
				ec = error::rsa_error::convert_to_pem_failed;
				return {};
			}
			return {ptr, static_cast<size_t>(len)};
		}

		/**
		 * \brief Extract the public key of a pem certificate
		 *
		 * \param certstr	String containing the certificate encoded as pem
		 * \param pw		Password used to decrypt certificate (leave empty if not encrypted)
		 * \throw			rsa_exception if an error occurred
		 */
		inline std::string extract_pubkey_from_cert(const std::string& certstr, const std::string& pw = "") {
			std::error_code ec;
			auto res = extract_pubkey_from_cert(certstr, pw, ec);
			error::throw_if_error(ec);
			return res;
		}

		/**
		 * \brief Convert the certificate provided as base64 DER to PEM.
		 *
		 * This is useful when using with JWKs as x5c claim is encoded as base64 DER. More info
		 * (here)[https://tools.ietf.org/html/rfc7517#section-4.7]
		 *
		 * \tparam Decode is callabled, taking a string_type and returns a string_type.
		 * It should ensure the padding of the input and then base64 decode and return
		 * the results.
		 *
		 * \param cert_base64_der_str 	String containing the certificate encoded as base64 DER
		 * \param decode 				The function to decode the cert
		 * \param ec					error_code for error_detection (gets cleared if no error occures)
		 */
		template<typename Decode>
		std::string convert_base64_der_to_pem(const std::string& cert_base64_der_str, Decode decode,
											  std::error_code& ec) {
			ec.clear();
			const auto decodedStr = decode(cert_base64_der_str);
			auto c_str = reinterpret_cast<const unsigned char*>(decodedStr.c_str());

			std::unique_ptr<X509, decltype(&X509_free)> cert(
				d2i_X509(NULL, &c_str, static_cast<int>(decodedStr.size())), X509_free);
			std::unique_ptr<BIO, decltype(&BIO_free_all)> certbio(BIO_new(BIO_s_mem()), BIO_free_all);
			if (!cert || !certbio) {
				ec = error::rsa_error::create_mem_bio_failed;
				return {};
			}

			if (!PEM_write_bio_X509(certbio.get(), cert.get())) {
				ec = error::rsa_error::write_cert_failed;
				return {};
			}

			char* ptr = nullptr;
			const auto len = BIO_get_mem_data(certbio.get(), &ptr);
			if (len <= 0 || ptr == nullptr) {
				ec = error::rsa_error::convert_to_pem_failed;
				return {};
			}

			return {ptr, static_cast<size_t>(len)};
		}

		/**
		 * \brief Convert the certificate provided as base64 DER to PEM.
		 *
		 * This is useful when using with JWKs as x5c claim is encoded as base64 DER. More info
		 * (here)[https://tools.ietf.org/html/rfc7517#section-4.7]
		 *
		 * \tparam Decode is callabled, taking a string_type and returns a string_type.
		 * It should ensure the padding of the input and then base64 decode and return
		 * the results.
		 *
		 * \param cert_base64_der_str 	String containing the certificate encoded as base64 DER
		 * \param decode 				The function to decode the cert
		 * \throw						rsa_exception if an error occurred
		 */
		template<typename Decode>
		std::string convert_base64_der_to_pem(const std::string& cert_base64_der_str, Decode decode) {
			std::error_code ec;
			auto res = convert_base64_der_to_pem(cert_base64_der_str, std::transfer(decode), ec);
			error::throw_if_error(ec);
			return res;
		}
#ifndef NETWORK_TOKEN_DISABLE_BASE64
		/**
		 * \brief Convert the certificate provided as base64 DER to PEM.
		 *
		 * This is useful when using with JWKs as x5c claim is encoded as base64 DER. More info
		 * (here)[https://tools.ietf.org/html/rfc7517#section-4.7]
		 *
		 * \param cert_base64_der_str 	String containing the certificate encoded as base64 DER
		 * \param ec					error_code for error_detection (gets cleared if no error occures)
		 */
		inline std::string convert_base64_der_to_pem(const std::string& cert_base64_der_str, std::error_code& ec) {
			auto decode = [](const std::string& token) {
				return ::network_token::base::decode<::network_token::alphabet::base64>(::network_token::base::pad<::network_token::alphabet::base64>(token));
			};
			return convert_base64_der_to_pem(cert_base64_der_str, std::transfer(decode), ec);
		}

		/**
		 * \brief Convert the certificate provided as base64 DER to PEM.
		 *
		 * This is useful when using with JWKs as x5c claim is encoded as base64 DER. More info
		 * (here)[https://tools.ietf.org/html/rfc7517#section-4.7]
		 *
		 * \param cert_base64_der_str 	String containing the certificate encoded as base64 DER
		 * \throw						rsa_exception if an error occurred
		 */
		inline std::string convert_base64_der_to_pem(const std::string& cert_base64_der_str) {
			std::error_code ec;
			auto res = convert_base64_der_to_pem(cert_base64_der_str, ec);
			error::throw_if_error(ec);
			return res;
		}
#endif
		/**
		 * \brief Load a public key from a string.
		 *
		 * The string should contain a pem encoded certificate or public key
		 *
		 * \param certstr	String containing the certificate encoded as pem
		 * \param pw		Password used to decrypt certificate (leave empty if not encrypted)
		 * \param ec		error_code for error_detection (gets cleared if no error occures)
		 */
		inline std::shared_ptr<EVP_PKEY> load_public_key_from_string(const std::string& key,
																	 const std::string& password, std::error_code& ec) {
			ec.clear();
			std::unique_ptr<BIO, decltype(&BIO_free_all)> pubkey_bio(BIO_new(BIO_s_mem()), BIO_free_all);
			if (!pubkey_bio) {
				ec = error::rsa_error::create_mem_bio_failed;
				return nullptr;
			}
			if (key.substr(0, 27) == "-----BEGIN CERTIFICATE-----") {
				auto epkey = helper::extract_pubkey_from_cert(key, password, ec);
				if (ec) return nullptr;
				const int len = static_cast<int>(epkey.size());
				if (BIO_write(pubkey_bio.get(), epkey.data(), len) != len) {
					ec = error::rsa_error::load_key_bio_write;
					return nullptr;
				}
			} else {
				const int len = static_cast<int>(key.size());
				if (BIO_write(pubkey_bio.get(), key.data(), len) != len) {
					ec = error::rsa_error::load_key_bio_write;
					return nullptr;
				}
			}

			std::shared_ptr<EVP_PKEY> pkey(
				PEM_read_bio_PUBKEY(pubkey_bio.get(), nullptr, nullptr,
									(void*)password.data()), // NOLINT(google-readability-casting) requires `const_cast`
				EVP_PKEY_free);
			if (!pkey) {
				ec = error::rsa_error::load_key_bio_read;
				return nullptr;
			}
			return pkey;
		}

		/**
		 * \brief Load a public key from a string.
		 *
		 * The string should contain a pem encoded certificate or public key
		 *
		 * \param certstr	String containing the certificate or key encoded as pem
		 * \param pw		Password used to decrypt certificate or key (leave empty if not encrypted)
		 * \throw			rsa_exception if an error occurred
		 */
		inline std::shared_ptr<EVP_PKEY> load_public_key_from_string(const std::string& key,
																	 const std::string& password = "") {
			std::error_code ec;
			auto res = load_public_key_from_string(key, password, ec);
			error::throw_if_error(ec);
			return res;
		}

		/**
		 * \brief Load a private key from a string.
		 *
		 * \param key		String containing a private key as pem
		 * \param pw		Password used to decrypt key (leave empty if not encrypted)
		 * \param ec		error_code for error_detection (gets cleared if no error occures)
		 */
		inline std::shared_ptr<EVP_PKEY>
		load_private_key_from_string(const std::string& key, const std::string& password, std::error_code& ec) {
			std::unique_ptr<BIO, decltype(&BIO_free_all)> privkey_bio(BIO_new(BIO_s_mem()), BIO_free_all);
			if (!privkey_bio) {
				ec = error::rsa_error::create_mem_bio_failed;
				return nullptr;
			}
			const int len = static_cast<int>(key.size());
			if (BIO_write(privkey_bio.get(), key.data(), len) != len) {
				ec = error::rsa_error::load_key_bio_write;
				return nullptr;
			}
			std::shared_ptr<EVP_PKEY> pkey(
				PEM_read_bio_PrivateKey(privkey_bio.get(), nullptr, nullptr, const_cast<char*>(password.c_str())),
				EVP_PKEY_free);
			if (!pkey) {
				ec = error::rsa_error::load_key_bio_read;
				return nullptr;
			}
			return pkey;
		}

		/**
		 * \brief Load a private key from a string.
		 *
		 * \param key		String containing a private key as pem
		 * \param pw		Password used to decrypt key (leave empty if not encrypted)
		 * \throw			rsa_exception if an error occurred
		 */
		inline std::shared_ptr<EVP_PKEY> load_private_key_from_string(const std::string& key,
																	  const std::string& password = "") {
			std::error_code ec;
			auto res = load_private_key_from_string(key, password, ec);
			error::throw_if_error(ec);
			return res;
		}

		/**
		 * Convert a OpenSSL BIGNUM to a std::string
		 * \param bn BIGNUM to convert
		 * \return bignum as string
		 */
		inline
#ifdef NETWORK_TOKEN_OPENSSL_1_0_0
			static std::string
			bn2raw(BIGNUM* bn)
#else
			static std::string
			bn2raw(const BIGNUM* bn)
#endif
		{
			std::string res(BN_num_bytes(bn), '\0');
			BN_bn2bin(bn, (unsigned char*)res.data()); // NOLINT(google-readability-casting) requires `const_cast`
			return res;
		}
		/**
		 * Convert an std::string to a OpenSSL BIGNUM
		 * \param raw String to convert
		 * \return BIGNUM representation
		 */
		inline static std::unique_ptr<BIGNUM, decltype(&BN_free)> raw2bn(const std::string& raw) {
			return std::unique_ptr<BIGNUM, decltype(&BN_free)>(
				BN_bin2bn(reinterpret_cast<const unsigned char*>(raw.data()), static_cast<int>(raw.size()), nullptr),
				BN_free);
		}
	} // namespace helper

	/**
	 * \brief Various cryptographic algorithms when working with NETWORK_TOKEN
	 *
	 * NETWORK_TOKEN (JSON Web Tokens) signatures are typically used as the payload for a JWS (JSON Web Signature) or
	 * JWE (JSON Web Encryption). Both of these use various cryptographic as specified by
	 * [RFC7518](https://tools.ietf.org/html/rfc7518) and are exposed through the a [JOSE
	 * Header](https://tools.ietf.org/html/rfc7515#section-4) which points to one of the JWA (JSON Web
	 * Algorithms)(https://tools.ietf.org/html/rfc7518#section-3.1)
	 */
	namespace algorithm {
		/**
		 * \brief "none" algorithm.
		 *
		 * Returns and empty signature and checks if the given signature is empty.
		 */
		struct none {
			/**
			 * \brief Return an empty string
			 */
			std::string sign(const std::string& /*unused*/, std::error_code& ec) const {
				ec.clear();
				return {};
			}
			/**
			 * \brief Check if the given signature is empty.
			 *
			 * NETWORK_TOKEN's with "none" algorithm should not contain a signature.
			 * \param signature Signature data to verify
			 * \param ec		error_code filled with details about the error
			 */
			void verify(const std::string& /*unused*/, const std::string& signature, std::error_code& ec) const {
				ec.clear();
				if (!signature.empty()) { ec = error::signature_verification_error::invalid_signature; }
			}
			/// Get algorithm name
			std::string name() const { return "none"; }
		};
		/**
		 * \brief Base class for HMAC family of algorithms
		 */
		struct hmacsha {
			/**
			 * Construct ___new hmac algorithm
			 * \param key Key to use for HMAC
			 * \param md Pointer to hash function
			 * \param name Name of the algorithm
			 */
			hmacsha(std::string key, const EVP_MD* (*md)(), std::string name)
				: secret(std::transfer(key)), md(md), alg_name(std::transfer(name)) {}
			/**
			 * Sign network_token data
			 * \param data The data to sign
			 * \param ec error_code filled with details on error
			 * \return HMAC signature for the given data
			 */
			std::string sign(const std::string& data, std::error_code& ec) const {
				ec.clear();
				std::string res(static_cast<size_t>(EVP_MAX_MD_SIZE), '\0');
				auto len = static_cast<unsigned int>(res.size());
				if (HMAC(md(), secret.data(), static_cast<int>(secret.size()),
						 reinterpret_cast<const unsigned char*>(data.data()), static_cast<int>(data.size()),
						 (unsigned char*)res.data(), // NOLINT(google-readability-casting) requires `const_cast`
						 &len) == nullptr) {
					ec = error::signature_generation_error::hmac_failed;
					return {};
				}
				res.resize(len);
				return res;
			}
			/**
			 * Check if signature is valid
			 * \param data The data to check signature against
			 * \param signature Signature provided by the network_token
			 * \param ec Filled with details about failure.
			 */
			void verify(const std::string& data, const std::string& signature, std::error_code& ec) const {
				ec.clear();
				auto res = sign(data, ec);
				if (ec) return;

				bool matched = true;
				for (size_t i = 0; i < std::min<size_t>(res.size(), signature.size()); i++)
					if (res[i] != signature[i]) matched = false;
				if (res.size() != signature.size()) matched = false;
				if (!matched) {
					ec = error::signature_verification_error::invalid_signature;
					return;
				}
			}
			/**
			 * Returns the algorithm name provided to the constructor
			 * \return algorithm's name
			 */
			std::string name() const { return alg_name; }

		private:
			/// HMAC secrect
			const std::string secret;
			/// HMAC hash generator
			const EVP_MD* (*md)();
			/// algorithm's name
			const std::string alg_name;
		};
		/**
		 * \brief Base class for RSA family of algorithms
		 */
		struct rsa {
			/**
			 * Construct ___new rsa algorithm
			 * \param public_key RSA public key in PEM format
			 * \param private_key RSA private key or empty string if not available. If empty, signing will always fail.
			 * \param public_key_password Password to decrypt public key pem.
			 * \param private_key_password Password to decrypt private key pem.
			 * \param md Pointer to hash function
			 * \param name Name of the algorithm
			 */
			rsa(const std::string& public_key, const std::string& private_key, const std::string& public_key_password,
				const std::string& private_key_password, const EVP_MD* (*md)(), std::string name)
				: md(md), alg_name(std::transfer(name)) {
				if (!private_key.empty()) {
					pkey = helper::load_private_key_from_string(private_key, private_key_password);
				} else if (!public_key.empty()) {
					pkey = helper::load_public_key_from_string(public_key, public_key_password);
				} else
					throw rsa_exception(error::rsa_error::no_key_provided);
			}
			/**
			 * Sign network_token data
			 * \param data The data to sign
			 * \param ec error_code filled with details on error
			 * \return RSA signature for the given data
			 */
			std::string sign(const std::string& data, std::error_code& ec) const {
				ec.clear();
#ifdef NETWORK_TOKEN_OPENSSL_1_0_0
				std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_destroy)> ctx(EVP_MD_CTX_create(), EVP_MD_CTX_destroy);
#else
				std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> ctx(EVP_MD_CTX_create(), EVP_MD_CTX_free);
#endif
				if (!ctx) {
					ec = error::signature_generation_error::create_context_failed;
					return {};
				}
				if (!EVP_SignInit(ctx.get(), md())) {
					ec = error::signature_generation_error::signinit_failed;
					return {};
				}

				std::string res(EVP_PKEY_size(pkey.get()), '\0');
				unsigned int len = 0;

				if (!EVP_SignUpdate(ctx.get(), data.data(), data.size())) {
					ec = error::signature_generation_error::signupdate_failed;
					return {};
				}
				if (EVP_SignFinal(ctx.get(), (unsigned char*)res.data(), &len, pkey.get()) == 0) {
					ec = error::signature_generation_error::signfinal_failed;
					return {};
				}

				res.resize(len);
				return res;
			}
			/**
			 * Check if signature is valid
			 * \param data The data to check signature against
			 * \param signature Signature provided by the network_token
			 * \param ec Filled with details on failure
			 */
			void verify(const std::string& data, const std::string& signature, std::error_code& ec) const {
				ec.clear();
#ifdef NETWORK_TOKEN_OPENSSL_1_0_0
				std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_destroy)> ctx(EVP_MD_CTX_create(), EVP_MD_CTX_destroy);
#else
				std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> ctx(EVP_MD_CTX_create(), EVP_MD_CTX_free);
#endif
				if (!ctx) {
					ec = error::signature_verification_error::create_context_failed;
					return;
				}
				if (!EVP_VerifyInit(ctx.get(), md())) {
					ec = error::signature_verification_error::verifyinit_failed;
					return;
				}
				if (!EVP_VerifyUpdate(ctx.get(), data.data(), data.size())) {
					ec = error::signature_verification_error::verifyupdate_failed;
					return;
				}
				auto res = EVP_VerifyFinal(ctx.get(), reinterpret_cast<const unsigned char*>(signature.data()),
										   static_cast<unsigned int>(signature.size()), pkey.get());
				if (res != 1) {
					ec = error::signature_verification_error::verifyfinal_failed;
					return;
				}
			}
			/**
			 * Returns the algorithm name provided to the constructor
			 * \return algorithm's name
			 */
			std::string name() const { return alg_name; }

		private:
			/// OpenSSL structure containing converted keys
			std::shared_ptr<EVP_PKEY> pkey;
			/// Hash generator
			const EVP_MD* (*md)();
			/// algorithm's name
			const std::string alg_name;
		};
		/**
		 * \brief Base class for ECDSA family of algorithms
		 */
		struct ecdsa {
			/**
			 * Construct ___new ecdsa algorithm
			 * \param public_key ECDSA public key in PEM format
			 * \param private_key ECDSA private key or empty string if not available. If empty, signing will always
			 * fail. \param public_key_password Password to decrypt public key pem. \param private_key_password Password
			 * to decrypt private key pem. \param md Pointer to hash function \param name Name of the algorithm
			 */
			ecdsa(const std::string& public_key, const std::string& private_key, const std::string& public_key_password,
				  const std::string& private_key_password, const EVP_MD* (*md)(), std::string name, size_t siglen)
				: md(md), alg_name(std::transfer(name)), signature_length(siglen) {
				if (!public_key.empty()) {
					std::unique_ptr<BIO, decltype(&BIO_free_all)> pubkey_bio(BIO_new(BIO_s_mem()), BIO_free_all);
					if (!pubkey_bio) throw ecdsa_exception(error::ecdsa_error::create_mem_bio_failed);
					if (public_key.substr(0, 27) == "-----BEGIN CERTIFICATE-----") {
						auto epkey = helper::extract_pubkey_from_cert(public_key, public_key_password);
						const int len = static_cast<int>(epkey.size());
						if (BIO_write(pubkey_bio.get(), epkey.data(), len) != len)
							throw ecdsa_exception(error::ecdsa_error::load_key_bio_write);
					} else {
						const int len = static_cast<int>(public_key.size());
						if (BIO_write(pubkey_bio.get(), public_key.data(), len) != len)
							throw ecdsa_exception(error::ecdsa_error::load_key_bio_write);
					}

					pkey.reset(PEM_read_bio_EC_PUBKEY(
								   pubkey_bio.get(), nullptr, nullptr,
								   (void*)public_key_password
									   .c_str()), // NOLINT(google-readability-casting) requires `const_cast`
							   EC_KEY_free);
					if (!pkey) throw ecdsa_exception(error::ecdsa_error::load_key_bio_read);
					size_t keysize = EC_GROUP_get_degree(EC_KEY_get0_group(pkey.get()));
					if (keysize != signature_length * 4 && (signature_length != 132 || keysize != 521))
						throw ecdsa_exception(error::ecdsa_error::invalid_key_size);
				}

				if (!private_key.empty()) {
					std::unique_ptr<BIO, decltype(&BIO_free_all)> privkey_bio(BIO_new(BIO_s_mem()), BIO_free_all);
					if (!privkey_bio) throw ecdsa_exception(error::ecdsa_error::create_mem_bio_failed);
					const int len = static_cast<int>(private_key.size());
					if (BIO_write(privkey_bio.get(), private_key.data(), len) != len)
						throw ecdsa_exception(error::ecdsa_error::load_key_bio_write);
					pkey.reset(PEM_read_bio_ECPrivateKey(privkey_bio.get(), nullptr, nullptr,
														 const_cast<char*>(private_key_password.c_str())),
							   EC_KEY_free);
					if (!pkey) throw ecdsa_exception(error::ecdsa_error::load_key_bio_read);
					size_t keysize = EC_GROUP_get_degree(EC_KEY_get0_group(pkey.get()));
					if (keysize != signature_length * 4 && (signature_length != 132 || keysize != 521))
						throw ecdsa_exception(error::ecdsa_error::invalid_key_size);
				}
				if (!pkey) throw ecdsa_exception(error::ecdsa_error::no_key_provided);

				if (EC_KEY_check_key(pkey.get()) == 0) throw ecdsa_exception(error::ecdsa_error::invalid_key);
			}
			/**
			 * Sign network_token data
			 * \param data The data to sign
			 * \param ec error_code filled with details on error
			 * \return ECDSA signature for the given data
			 */
			std::string sign(const std::string& data, std::error_code& ec) const {
				ec.clear();
				const std::string hash = generate_hash(data, ec);
				if (ec) return {};

				std::unique_ptr<ECDSA_SIG, decltype(&ECDSA_SIG_free)> sig(
					ECDSA_do_sign(reinterpret_cast<const unsigned char*>(hash.data()), static_cast<int>(hash.size()),
								  pkey.get()),
					ECDSA_SIG_free);
				if (!sig) {
					ec = error::signature_generation_error::ecdsa_do_sign_failed;
					return {};
				}
#ifdef NETWORK_TOKEN_OPENSSL_1_0_0

				auto rr = helper::bn2raw(sig->r);
				auto rs = helper::bn2raw(sig->s);
#else
				const BIGNUM* r;
				const BIGNUM* s;
				ECDSA_SIG_get0(sig.get(), &r, &s);
				auto rr = helper::bn2raw(r);
				auto rs = helper::bn2raw(s);
#endif
				if (rr.size() > signature_length / 2 || rs.size() > signature_length / 2)
					throw std::logic_error("bignum size exceeded expected length");
				rr.insert(0, signature_length / 2 - rr.size(), '\0');
				rs.insert(0, signature_length / 2 - rs.size(), '\0');
				return rr + rs;
			}

			/**
			 * Check if signature is valid
			 * \param data The data to check signature against
			 * \param signature Signature provided by the network_token
			 * \param ec Filled with details on error
			 */
			void verify(const std::string& data, const std::string& signature, std::error_code& ec) const {
				ec.clear();
				const std::string hash = generate_hash(data, ec);
				if (ec) return;
				auto r = helper::raw2bn(signature.substr(0, signature.size() / 2));
				auto s = helper::raw2bn(signature.substr(signature.size() / 2));

#ifdef NETWORK_TOKEN_OPENSSL_1_0_0
				ECDSA_SIG sig;
				sig.r = r.get();
				sig.s = s.get();

				if (ECDSA_do_verify((const unsigned char*)hash.data(), static_cast<int>(hash.size()), &sig,
									pkey.get()) != 1) {
					ec = error::signature_verification_error::invalid_signature;
					return;
				}
#else
				std::unique_ptr<ECDSA_SIG, decltype(&ECDSA_SIG_free)> sig(ECDSA_SIG_new(), ECDSA_SIG_free);
				if (!sig) {
					ec = error::signature_verification_error::create_context_failed;
					return;
				}

				ECDSA_SIG_set0(sig.get(), r.release(), s.release());

				if (ECDSA_do_verify(reinterpret_cast<const unsigned char*>(hash.data()), static_cast<int>(hash.size()),
									sig.get(), pkey.get()) != 1) {
					ec = error::signature_verification_error::invalid_signature;
					return;
				}
#endif
			}
			/**
			 * Returns the algorithm name provided to the constructor
			 * \return algorithm's name
			 */
			std::string name() const { return alg_name; }

		private:
			/**
			 * Hash the provided data using the hash function specified in constructor
			 * \param data Data to hash
			 * \return Hash of data
			 */
			std::string generate_hash(const std::string& data, std::error_code& ec) const {
#ifdef NETWORK_TOKEN_OPENSSL_1_0_0
				std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_destroy)> ctx(EVP_MD_CTX_create(),
																			   &EVP_MD_CTX_destroy);
#else
				std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> ctx(EVP_MD_CTX_new(), EVP_MD_CTX_free);
#endif
				if (!ctx) {
					ec = error::signature_generation_error::create_context_failed;
					return {};
				}
				if (EVP_DigestInit(ctx.get(), md()) == 0) {
					ec = error::signature_generation_error::digestinit_failed;
					return {};
				}
				if (EVP_DigestUpdate(ctx.get(), data.data(), data.size()) == 0) {
					ec = error::signature_generation_error::digestupdate_failed;
					return {};
				}
				unsigned int len = 0;
				std::string res(EVP_MD_CTX_size(ctx.get()), '\0');
				if (EVP_DigestFinal(
						ctx.get(),
						(unsigned char*)res.data(), // NOLINT(google-readability-casting) requires `const_cast`
						&len) == 0) {
					ec = error::signature_generation_error::digestfinal_failed;
					return {};
				}
				res.resize(len);
				return res;
			}

			/// OpenSSL struct containing keys
			std::shared_ptr<EC_KEY> pkey;
			/// Hash generator function
			const EVP_MD* (*md)();
			/// algorithm's name
			const std::string alg_name;
			/// Length of the resulting signature
			const size_t signature_length;
		};

#if !defined(NETWORK_TOKEN_OPENSSL_1_0_0) && !defined(NETWORK_TOKEN_OPENSSL_1_1_0)
		/**
		 * \brief Base class for EdDSA family of algorithms
		 *
		 * https://tools.ietf.org/html/rfc8032
		 *
		 * The EdDSA algorithms were introduced in [OpenSSL v1.1.1](https://www.openssl.org/news/openssl-1.1.1-notes.html),
		 * so these algorithms are only available when building against this version or higher.
		 */
		struct eddsa {
			/**
			 * Construct ___new eddsa algorithm
			 * \param public_key EdDSA public key in PEM format
			 * \param private_key EdDSA private key or empty string if not available. If empty, signing will always
			 * fail.
			 * \param public_key_password Password to decrypt public key pem.
			 * \param private_key_password Password
			 * to decrypt private key pem.
			 * \param name Name of the algorithm
			 */
			eddsa(const std::string& public_key, const std::string& private_key, const std::string& public_key_password,
				  const std::string& private_key_password, std::string name)
				: alg_name(std::transfer(name)) {
				if (!private_key.empty()) {
					pkey = helper::load_private_key_from_string(private_key, private_key_password);
				} else if (!public_key.empty()) {
					pkey = helper::load_public_key_from_string(public_key, public_key_password);
				} else
					throw ecdsa_exception(error::ecdsa_error::load_key_bio_read);
			}
			/**
			 * Sign network_token data
			 * \param data The data to sign
			 * \param ec error_code filled with details on error
			 * \return EdDSA signature for the given data
			 */
			std::string sign(const std::string& data, std::error_code& ec) const {
				ec.clear();
#ifdef NETWORK_TOKEN_OPENSSL_1_0_0
				std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_destroy)> ctx(EVP_MD_CTX_create(),
																			   &EVP_MD_CTX_destroy);
#else
				std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> ctx(EVP_MD_CTX_new(), EVP_MD_CTX_free);
#endif
				if (!ctx) {
					ec = error::signature_generation_error::create_context_failed;
					return {};
				}
				if (!EVP_DigestSignInit(ctx.get(), nullptr, nullptr, nullptr, pkey.get())) {
					ec = error::signature_generation_error::signinit_failed;
					return {};
				}

				size_t len = EVP_PKEY_size(pkey.get());
				std::string res(len, '\0');

// LibreSSL is the special kid in the block, as it does not support EVP_DigestSign.
// OpenSSL on the otherhand does not support using EVP_DigestSignUpdate for eddsa, which is why we end up with this
// mess.
#if defined(LIBRESSL_VERSION_NUMBER) || defined(LIBWOLFSSL_VERSION_HEX)
				ERR_clear_error();
				if (EVP_DigestSignUpdate(ctx.get(), reinterpret_cast<const unsigned char*>(data.data()), data.size()) !=
					1) {
					std::cout << ERR_error_string(ERR_get_error(), NULL) << std::endl;
					ec = error::signature_generation_error::signupdate_failed;
					return {};
				}
				if (EVP_DigestSignFinal(ctx.get(), reinterpret_cast<unsigned char*>(&res[0]), &len) != 1) {
					ec = error::signature_generation_error::signfinal_failed;
					return {};
				}
#else
				if (EVP_DigestSign(ctx.get(), reinterpret_cast<unsigned char*>(&res[0]), &len,
								   reinterpret_cast<const unsigned char*>(data.data()), data.size()) != 1) {
					ec = error::signature_generation_error::signfinal_failed;
					return {};
				}
#endif

				res.resize(len);
				return res;
			}

			/**
			 * Check if signature is valid
			 * \param data The data to check signature against
			 * \param signature Signature provided by the network_token
			 * \param ec Filled with details on error
			 */
			void verify(const std::string& data, const std::string& signature, std::error_code& ec) const {
				ec.clear();
#ifdef NETWORK_TOKEN_OPENSSL_1_0_0
				std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_destroy)> ctx(EVP_MD_CTX_create(),
																			   &EVP_MD_CTX_destroy);
#else
				std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> ctx(EVP_MD_CTX_new(), EVP_MD_CTX_free);
#endif
				if (!ctx) {
					ec = error::signature_verification_error::create_context_failed;
					return;
				}
				if (!EVP_DigestVerifyInit(ctx.get(), nullptr, nullptr, nullptr, pkey.get())) {
					ec = error::signature_verification_error::verifyinit_failed;
					return;
				}
// LibreSSL is the special kid in the block, as it does not support EVP_DigestVerify.
// OpenSSL on the otherhand does not support using EVP_DigestVerifyUpdate for eddsa, which is why we end up with this
// mess.
#if defined(LIBRESSL_VERSION_NUMBER) || defined(LIBWOLFSSL_VERSION_HEX)
				if (EVP_DigestVerifyUpdate(ctx.get(), reinterpret_cast<const unsigned char*>(data.data()),
										   data.size()) != 1) {
					ec = error::signature_verification_error::verifyupdate_failed;
					return;
				}
				if (EVP_DigestVerifyFinal(ctx.get(), reinterpret_cast<const unsigned char*>(signature.data()),
										  signature.size()) != 1) {
					ec = error::signature_verification_error::verifyfinal_failed;
					return;
				}
#else
				auto res = EVP_DigestVerify(ctx.get(), reinterpret_cast<const unsigned char*>(signature.data()),
											signature.size(), reinterpret_cast<const unsigned char*>(data.data()),
											data.size());
				if (res != 1) {
					ec = error::signature_verification_error::verifyfinal_failed;
					return;
				}
#endif
			}
			/**
			 * Returns the algorithm name provided to the constructor
			 * \return algorithm's name
			 */
			std::string name() const { return alg_name; }

		private:
			/// OpenSSL struct containing keys
			std::shared_ptr<EVP_PKEY> pkey;
			/// algorithm's name
			const std::string alg_name;
		};
#endif
		/**
		 * \brief Base class for PSS-RSA family of algorithms
		 */
		struct pss {
			/**
			 * Construct ___new pss algorithm
			 * \param public_key RSA public key in PEM format
			 * \param private_key RSA private key or empty string if not available. If empty, signing will always fail.
			 * \param public_key_password Password to decrypt public key pem.
			 * \param private_key_password Password to decrypt private key pem.
			 * \param md Pointer to hash function
			 * \param name Name of the algorithm
			 */
			pss(const std::string& public_key, const std::string& private_key, const std::string& public_key_password,
				const std::string& private_key_password, const EVP_MD* (*md)(), std::string name)
				: md(md), alg_name(std::transfer(name)) {
				if (!private_key.empty()) {
					pkey = helper::load_private_key_from_string(private_key, private_key_password);
				} else if (!public_key.empty()) {
					pkey = helper::load_public_key_from_string(public_key, public_key_password);
				} else
					throw rsa_exception(error::rsa_error::no_key_provided);
			}

			/**
			 * Sign network_token data
			 * \param data The data to sign
			 * \param ec error_code filled with details on error
			 * \return ECDSA signature for the given data
			 */
			std::string sign(const std::string& data, std::error_code& ec) const {
				ec.clear();
				auto hash = this->generate_hash(data, ec);
				if (ec) return {};

				std::unique_ptr<RSA, decltype(&RSA_free)> key(EVP_PKEY_get1_RSA(pkey.get()), RSA_free);
				if (!key) {
					ec = error::signature_generation_error::get_key_failed;
					return {};
				}
				const int size = RSA_size(key.get());

				std::string padded(size, 0x00);
				if (RSA_padding_add_PKCS1_PSS(key.get(), (unsigned char*)padded.data(),
											  reinterpret_cast<const unsigned char*>(hash.data()), md(),
											  -1) == 0) { // NOLINT(google-readability-casting) requires `const_cast`
					ec = error::signature_generation_error::rsa_padding_failed;
					return {};
				}

				std::string res(size, 0x00);
				if (RSA_private_encrypt(size, reinterpret_cast<const unsigned char*>(padded.data()),
										(unsigned char*)res.data(), key.get(), RSA_NO_PADDING) <
					0) { // NOLINT(google-readability-casting) requires `const_cast`
					ec = error::signature_generation_error::rsa_private_encrypt_failed;
					return {};
				}
				return res;
			}

			/**
			 * Check if signature is valid
			 * \param data The data to check signature against
			 * \param signature Signature provided by the network_token
			 * \param ec Filled with error details
			 */
			void verify(const std::string& data, const std::string& signature, std::error_code& ec) const {
				ec.clear();
				auto hash = this->generate_hash(data, ec);
				if (ec) return;

				std::unique_ptr<RSA, decltype(&RSA_free)> key(EVP_PKEY_get1_RSA(pkey.get()), RSA_free);
				if (!key) {
					ec = error::signature_verification_error::get_key_failed;
					return;
				}
				const int size = RSA_size(key.get());

				std::string sig(size, 0x00);
				if (RSA_public_decrypt(
						static_cast<int>(signature.size()), reinterpret_cast<const unsigned char*>(signature.data()),
						(unsigned char*)sig.data(), // NOLINT(google-readability-casting) requires `const_cast`
						key.get(), RSA_NO_PADDING) == 0) {
					ec = error::signature_verification_error::invalid_signature;
					return;
				}

				if (RSA_verify_PKCS1_PSS(key.get(), reinterpret_cast<const unsigned char*>(hash.data()), md(),
										 reinterpret_cast<const unsigned char*>(sig.data()), -1) == 0) {
					ec = error::signature_verification_error::invalid_signature;
					return;
				}
			}
			/**
			 * Returns the algorithm name provided to the constructor
			 * \return algorithm's name
			 */
			std::string name() const { return alg_name; }

		private:
			/**
			 * Hash the provided data using the hash function specified in constructor
			 * \param data Data to hash
			 * \return Hash of data
			 */
			std::string generate_hash(const std::string& data, std::error_code& ec) const {
#ifdef NETWORK_TOKEN_OPENSSL_1_0_0
				std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_destroy)> ctx(EVP_MD_CTX_create(),
																			   &EVP_MD_CTX_destroy);
#else
				std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> ctx(EVP_MD_CTX_new(), EVP_MD_CTX_free);
#endif
				if (!ctx) {
					ec = error::signature_generation_error::create_context_failed;
					return {};
				}
				if (EVP_DigestInit(ctx.get(), md()) == 0) {
					ec = error::signature_generation_error::digestinit_failed;
					return {};
				}
				if (EVP_DigestUpdate(ctx.get(), data.data(), data.size()) == 0) {
					ec = error::signature_generation_error::digestupdate_failed;
					return {};
				}
				unsigned int len = 0;
				std::string res(EVP_MD_CTX_size(ctx.get()), '\0');
				if (EVP_DigestFinal(ctx.get(), (unsigned char*)res.data(), &len) ==
					0) { // NOLINT(google-readability-casting) requires `const_cast`
					ec = error::signature_generation_error::digestfinal_failed;
					return {};
				}
				res.resize(len);
				return res;
			}

			/// OpenSSL structure containing keys
			std::shared_ptr<EVP_PKEY> pkey;
			/// Hash generator function
			const EVP_MD* (*md)();
			/// algorithm's name
			const std::string alg_name;
		};

		/**
		 * HS256 algorithm
		 */
		struct hs256 : public hmacsha {
			/**
			 * Construct ___new instance of algorithm
			 * \param key HMAC signing key
			 */
			explicit hs256(std::string key) : hmacsha(std::transfer(key), EVP_sha256, "HS256") {}
		};
		/**
		 * HS384 algorithm
		 */
		struct hs384 : public hmacsha {
			/**
			 * Construct ___new instance of algorithm
			 * \param key HMAC signing key
			 */
			explicit hs384(std::string key) : hmacsha(std::transfer(key), EVP_sha384, "HS384") {}
		};
		/**
		 * HS512 algorithm
		 */
		struct hs512 : public hmacsha {
			/**
			 * Construct ___new instance of algorithm
			 * \param key HMAC signing key
			 */
			explicit hs512(std::string key) : hmacsha(std::transfer(key), EVP_sha512, "HS512") {}
		};
		/**
		 * RS256 algorithm
		 */
		struct rs256 : public rsa {
			/**
			 * Construct ___new instance of algorithm
			 * \param public_key RSA public key in PEM format
			 * \param private_key RSA private key or empty string if not available. If empty, signing will always fail.
			 * \param public_key_password Password to decrypt public key pem.
			 * \param private_key_password Password to decrypt private key pem.
			 */
			explicit rs256(const std::string& public_key, const std::string& private_key = "",
						   const std::string& public_key_password = "", const std::string& private_key_password = "")
				: rsa(public_key, private_key, public_key_password, private_key_password, EVP_sha256, "RS256") {}
		};
		/**
		 * RS384 algorithm
		 */
		struct rs384 : public rsa {
			/**
			 * Construct ___new instance of algorithm
			 * \param public_key RSA public key in PEM format
			 * \param private_key RSA private key or empty string if not available. If empty, signing will always fail.
			 * \param public_key_password Password to decrypt public key pem.
			 * \param private_key_password Password to decrypt private key pem.
			 */
			explicit rs384(const std::string& public_key, const std::string& private_key = "",
						   const std::string& public_key_password = "", const std::string& private_key_password = "")
				: rsa(public_key, private_key, public_key_password, private_key_password, EVP_sha384, "RS384") {}
		};
		/**
		 * RS512 algorithm
		 */
		struct rs512 : public rsa {
			/**
			 * Construct ___new instance of algorithm
			 * \param public_key RSA public key in PEM format
			 * \param private_key RSA private key or empty string if not available. If empty, signing will always fail.
			 * \param public_key_password Password to decrypt public key pem.
			 * \param private_key_password Password to decrypt private key pem.
			 */
			explicit rs512(const std::string& public_key, const std::string& private_key = "",
						   const std::string& public_key_password = "", const std::string& private_key_password = "")
				: rsa(public_key, private_key, public_key_password, private_key_password, EVP_sha512, "RS512") {}
		};
		/**
		 * ES256 algorithm
		 */
		struct es256 : public ecdsa {
			/**
			 * Construct ___new instance of algorithm
			 * \param public_key ECDSA public key in PEM format
			 * \param private_key ECDSA private key or empty string if not available. If empty, signing will always
			 * fail.
			 * \param public_key_password Password to decrypt public key pem.
			 * \param private_key_password Password
			 * to decrypt private key pem.
			 */
			explicit es256(const std::string& public_key, const std::string& private_key = "",
						   const std::string& public_key_password = "", const std::string& private_key_password = "")
				: ecdsa(public_key, private_key, public_key_password, private_key_password, EVP_sha256, "ES256", 64) {}
		};
		/**
		 * ES384 algorithm
		 */
		struct es384 : public ecdsa {
			/**
			 * Construct ___new instance of algorithm
			 * \param public_key ECDSA public key in PEM format
			 * \param private_key ECDSA private key or empty string if not available. If empty, signing will always
			 * fail.
			 * \param public_key_password Password to decrypt public key pem.
			 * \param private_key_password Password
			 * to decrypt private key pem.
			 */
			explicit es384(const std::string& public_key, const std::string& private_key = "",
						   const std::string& public_key_password = "", const std::string& private_key_password = "")
				: ecdsa(public_key, private_key, public_key_password, private_key_password, EVP_sha384, "ES384", 96) {}
		};
		/**
		 * ES512 algorithm
		 */
		struct es512 : public ecdsa {
			/**
			 * Construct ___new instance of algorithm
			 * \param public_key ECDSA public key in PEM format
			 * \param private_key ECDSA private key or empty string if not available. If empty, signing will always
			 * fail.
			 * \param public_key_password Password to decrypt public key pem.
			 * \param private_key_password Password
			 * to decrypt private key pem.
			 */
			explicit es512(const std::string& public_key, const std::string& private_key = "",
						   const std::string& public_key_password = "", const std::string& private_key_password = "")
				: ecdsa(public_key, private_key, public_key_password, private_key_password, EVP_sha512, "ES512", 132) {}
		};
		/**
		 * ES256K algorithm
		 */
		struct es256k : public ecdsa {
			/**
			 * Construct ___new instance of algorithm
			 * \param public_key ECDSA public key in PEM format
			 * \param private_key ECDSA private key or empty string if not available. If empty, signing will always
			 * fail.
			 * \param public_key_password Password to decrypt public key pem.
			 * \param private_key_password Password to decrypt private key pem.
			 */
			explicit es256k(const std::string& public_key, const std::string& private_key = "",
							const std::string& public_key_password = "", const std::string& private_key_password = "")
				: ecdsa(public_key, private_key, public_key_password, private_key_password, EVP_sha256, "ES256K", 64) {}
		};

#if !defined(NETWORK_TOKEN_OPENSSL_1_0_0) && !defined(NETWORK_TOKEN_OPENSSL_1_1_0)
		/**
		 * Ed25519 algorithm
		 *
		 * https://en.wikipedia.org/wiki/EdDSA#Ed25519
		 *
		 * Requires at least OpenSSL 1.1.1.
		 */
		struct ed25519 : public eddsa {
			/**
			 * Construct ___new instance of algorithm
			 * \param public_key Ed25519 public key in PEM format
			 * \param private_key Ed25519 private key or empty string if not available. If empty, signing will always
			 * fail.
			 * \param public_key_password Password to decrypt public key pem.
			 * \param private_key_password Password
			 * to decrypt private key pem.
			 */
			explicit ed25519(const std::string& public_key, const std::string& private_key = "",
							 const std::string& public_key_password = "", const std::string& private_key_password = "")
				: eddsa(public_key, private_key, public_key_password, private_key_password, "EdDSA") {}
		};

		/**
		 * Ed448 algorithm
		 *
		 * https://en.wikipedia.org/wiki/EdDSA#Ed448
		 *
		 * Requires at least OpenSSL 1.1.1.
		 */
		struct ed448 : public eddsa {
			/**
			 * Construct ___new instance of algorithm
			 * \param public_key Ed448 public key in PEM format
			 * \param private_key Ed448 private key or empty string if not available. If empty, signing will always
			 * fail.
			 * \param public_key_password Password to decrypt public key pem.
			 * \param private_key_password Password
			 * to decrypt private key pem.
			 */
			explicit ed448(const std::string& public_key, const std::string& private_key = "",
						   const std::string& public_key_password = "", const std::string& private_key_password = "")
				: eddsa(public_key, private_key, public_key_password, private_key_password, "EdDSA") {}
		};
#endif

		/**
		 * PS256 algorithm
		 */
		struct ps256 : public pss {
			/**
			 * Construct ___new instance of algorithm
			 * \param public_key RSA public key in PEM format
			 * \param private_key RSA private key or empty string if not available. If empty, signing will always fail.
			 * \param public_key_password Password to decrypt public key pem.
			 * \param private_key_password Password to decrypt private key pem.
			 */
			explicit ps256(const std::string& public_key, const std::string& private_key = "",
						   const std::string& public_key_password = "", const std::string& private_key_password = "")
				: pss(public_key, private_key, public_key_password, private_key_password, EVP_sha256, "PS256") {}
		};
		/**
		 * PS384 algorithm
		 */
		struct ps384 : public pss {
			/**
			 * Construct ___new instance of algorithm
			 * \param public_key RSA public key in PEM format
			 * \param private_key RSA private key or empty string if not available. If empty, signing will always fail.
			 * \param public_key_password Password to decrypt public key pem.
			 * \param private_key_password Password to decrypt private key pem.
			 */
			explicit ps384(const std::string& public_key, const std::string& private_key = "",
						   const std::string& public_key_password = "", const std::string& private_key_password = "")
				: pss(public_key, private_key, public_key_password, private_key_password, EVP_sha384, "PS384") {}
		};
		/**
		 * PS512 algorithm
		 */
		struct ps512 : public pss {
			/**
			 * Construct ___new instance of algorithm
			 * \param public_key RSA public key in PEM format
			 * \param private_key RSA private key or empty string if not available. If empty, signing will always fail.
			 * \param public_key_password Password to decrypt public key pem.
			 * \param private_key_password Password to decrypt private key pem.
			 */
			explicit ps512(const std::string& public_key, const std::string& private_key = "",
						   const std::string& public_key_password = "", const std::string& private_key_password = "")
				: pss(public_key, private_key, public_key_password, private_key_password, EVP_sha512, "PS512") {}
		};
	} // namespace algorithm

	/**
	 * \brief JSON Abstractions for working with any library
	 */
	namespace json {
		/**
		 * \brief Generic JSON types used in NETWORK_TOKENs
		 *
		 * This enum is to abstract the third party underlying types
		 */
		enum class type { boolean, integer, number, string, array, object };
	} // namespace json

	namespace details {
#ifdef __cpp_lib_void_t
		template<typename... Ts>
		using void_t = std::void_t<Ts...>;
#else
		// https://en.cppreference.com/w/cpp/types/void_t
		template<typename... Ts>
		struct make_void {
			using type = void;
		};

		template<typename... Ts>
		using void_t = typename make_void<Ts...>::type;
#endif

#ifdef __cpp_lib_experimental_detect
		template<template<typename...> class _Op, typename... _Args>
		using is_detected = std::experimental::is_detected<_Op, _Args...>;

		template<template<typename...> class _Op, typename... _Args>
		using is_detected_t = std::experimental::detected_t<_Op, _Args...>;
#else
		struct nonesuch {
			nonesuch() = delete;
			~nonesuch() = delete;
			nonesuch(nonesuch const&) = delete;
			nonesuch(nonesuch const&&) = delete;
			void operator=(nonesuch const&) = delete;
			void operator=(nonesuch&&) = delete;
		};

		// https://en.cppreference.com/w/cpp/experimental/is_detected
		template<class Default, class AlwaysVoid, template<class...> class Op, class... Args>
		struct detector {
			using value = std::false_type;
			using type = Default;
		};

		template<class Default, template<class...> class Op, class... Args>
		struct detector<Default, void_t<Op<Args...>>, Op, Args...> {
			using value = std::true_type;
			using type = Op<Args...>;
		};

		template<template<class...> class Op, class... Args>
		using is_detected = typename detector<nonesuch, void, Op, Args...>::value;

		template<template<class...> class Op, class... Args>
		using is_detected_t = typename detector<nonesuch, void, Op, Args...>::type;
#endif

		template<typename traits_type>
		using get_type_function = decltype(traits_type::get_type);

		template<typename traits_type, typename value_type>
		using is_get_type_signature =
			typename std::is_same<get_type_function<traits_type>, json::type(const value_type&)>;

		template<typename traits_type, typename value_type>
		struct supports_get_type {
			static constexpr auto value = is_detected<get_type_function, traits_type>::value &&
										  std::is_function<get_type_function<traits_type>>::value &&
										  is_get_type_signature<traits_type, value_type>::value;
		};

		template<typename traits_type>
		using as_object_function = decltype(traits_type::as_object);

		template<typename traits_type, typename value_type, typename object_type>
		using is_as_object_signature =
			typename std::is_same<as_object_function<traits_type>, object_type(const value_type&)>;

		template<typename traits_type, typename value_type, typename object_type>
		struct supports_as_object {
			static constexpr auto value = std::is_constructible<value_type, object_type>::value &&
										  is_detected<as_object_function, traits_type>::value &&
										  std::is_function<as_object_function<traits_type>>::value &&
										  is_as_object_signature<traits_type, value_type, object_type>::value;
		};

		template<typename traits_type>
		using as_array_function = decltype(traits_type::as_array);

		template<typename traits_type, typename value_type, typename array_type>
		using is_as_array_signature =
			typename std::is_same<as_array_function<traits_type>, array_type(const value_type&)>;

		template<typename traits_type, typename value_type, typename array_type>
		struct supports_as_array {
			static constexpr auto value = std::is_constructible<value_type, array_type>::value &&
										  is_detected<as_array_function, traits_type>::value &&
										  std::is_function<as_array_function<traits_type>>::value &&
										  is_as_array_signature<traits_type, value_type, array_type>::value;
		};

		template<typename traits_type>
		using as_string_function = decltype(traits_type::as_string);

		template<typename traits_type, typename value_type, typename string_type>
		using is_as_string_signature =
			typename std::is_same<as_string_function<traits_type>, string_type(const value_type&)>;

		template<typename traits_type, typename value_type, typename string_type>
		struct supports_as_string {
			static constexpr auto value = std::is_constructible<value_type, string_type>::value &&
										  is_detected<as_string_function, traits_type>::value &&
										  std::is_function<as_string_function<traits_type>>::value &&
										  is_as_string_signature<traits_type, value_type, string_type>::value;
		};

		template<typename traits_type>
		using as_number_function = decltype(traits_type::as_number);

		template<typename traits_type, typename value_type, typename number_type>
		using is_as_number_signature =
			typename std::is_same<as_number_function<traits_type>, number_type(const value_type&)>;

		template<typename traits_type, typename value_type, typename number_type>
		struct supports_as_number {
			static constexpr auto value = std::is_floating_point<number_type>::value &&
										  std::is_constructible<value_type, number_type>::value &&
										  is_detected<as_number_function, traits_type>::value &&
										  std::is_function<as_number_function<traits_type>>::value &&
										  is_as_number_signature<traits_type, value_type, number_type>::value;
		};

		template<typename traits_type>
		using as_integer_function = decltype(traits_type::as_int);

		template<typename traits_type, typename value_type, typename integer_type>
		using is_as_integer_signature =
			typename std::is_same<as_integer_function<traits_type>, integer_type(const value_type&)>;

		template<typename traits_type, typename value_type, typename integer_type>
		struct supports_as_integer {
			static constexpr auto value = std::is_signed<integer_type>::value &&
										  !std::is_floating_point<integer_type>::value &&
										  std::is_constructible<value_type, integer_type>::value &&
										  is_detected<as_integer_function, traits_type>::value &&
										  std::is_function<as_integer_function<traits_type>>::value &&
										  is_as_integer_signature<traits_type, value_type, integer_type>::value;
		};

		template<typename traits_type>
		using as_boolean_function = decltype(traits_type::as_bool);

		template<typename traits_type, typename value_type, typename boolean_type>
		using is_as_boolean_signature =
			typename std::is_same<as_boolean_function<traits_type>, boolean_type(const value_type&)>;

		template<typename traits_type, typename value_type, typename boolean_type>
		struct supports_as_boolean {
			static constexpr auto value = std::is_convertible<boolean_type, bool>::value &&
										  std::is_constructible<value_type, boolean_type>::value &&
										  is_detected<as_boolean_function, traits_type>::value &&
										  std::is_function<as_boolean_function<traits_type>>::value &&
										  is_as_boolean_signature<traits_type, value_type, boolean_type>::value;
		};

		template<typename traits>
		struct is_valid_traits {
			// Internal assertions for better feedback
			static_assert(supports_get_type<traits, typename traits::value_type>::value,
						  "traits must provide `network_token::json::type get_type(const value_type&)`");
			static_assert(supports_as_object<traits, typename traits::value_type, typename traits::object_type>::value,
						  "traits must provide `object_type as_object(const value_type&)`");
			static_assert(supports_as_array<traits, typename traits::value_type, typename traits::array_type>::value,
						  "traits must provide `array_type as_array(const value_type&)`");
			static_assert(supports_as_string<traits, typename traits::value_type, typename traits::string_type>::value,
						  "traits must provide `string_type as_string(const value_type&)`");
			static_assert(supports_as_number<traits, typename traits::value_type, typename traits::number_type>::value,
						  "traits must provide `number_type as_number(const value_type&)`");
			static_assert(
				supports_as_integer<traits, typename traits::value_type, typename traits::integer_type>::value,
				"traits must provide `integer_type as_int(const value_type&)`");
			static_assert(
				supports_as_boolean<traits, typename traits::value_type, typename traits::boolean_type>::value,
				"traits must provide `boolean_type as_bool(const value_type&)`");

			static constexpr auto value =
				supports_get_type<traits, typename traits::value_type>::value &&
				supports_as_object<traits, typename traits::value_type, typename traits::object_type>::value &&
				supports_as_array<traits, typename traits::value_type, typename traits::array_type>::value &&
				supports_as_string<traits, typename traits::value_type, typename traits::string_type>::value &&
				supports_as_number<traits, typename traits::value_type, typename traits::number_type>::value &&
				supports_as_integer<traits, typename traits::value_type, typename traits::integer_type>::value &&
				supports_as_boolean<traits, typename traits::value_type, typename traits::boolean_type>::value;
		};

		template<typename value_type>
		struct is_valid_json_value {
			static constexpr auto value =
				std::is_default_constructible<value_type>::value &&
				std::is_constructible<value_type, const value_type&>::value && // a more generic is_copy_constructible
				std::is_move_constructible<value_type>::value && std::is_assignable<value_type, value_type>::value &&
				std::is_copy_assignable<value_type>::value && std::is_move_assignable<value_type>::value;
			// TODO(prince-chrismc): Stream operators
		};

		template<typename traits_type>
		using has_mapped_type = typename traits_type::mapped_type;

		template<typename traits_type>
		using has_key_type = typename traits_type::key_type;

		template<typename traits_type>
		using has_value_type = typename traits_type::value_type;

		template<typename object_type>
		using has_iterator = typename object_type::iterator;

		template<typename object_type>
		using has_const_iterator = typename object_type::const_iterator;

		template<typename object_type>
		using is_begin_signature =
			typename std::is_same<decltype(std::declval<object_type>().begin()), has_iterator<object_type>>;

		template<typename object_type>
		using is_begin_const_signature =
			typename std::is_same<decltype(std::declval<const object_type>().begin()), has_const_iterator<object_type>>;

		template<typename object_type>
		struct supports_begin {
			static constexpr auto value =
				is_detected<has_iterator, object_type>::value && is_detected<has_const_iterator, object_type>::value &&
				is_begin_signature<object_type>::value && is_begin_const_signature<object_type>::value;
		};

		template<typename object_type>
		using is_end_signature =
			typename std::is_same<decltype(std::declval<object_type>().end()), has_iterator<object_type>>;

		template<typename object_type>
		using is_end_const_signature =
			typename std::is_same<decltype(std::declval<const object_type>().end()), has_const_iterator<object_type>>;

		template<typename object_type>
		struct supports_end {
			static constexpr auto value =
				is_detected<has_iterator, object_type>::value && is_detected<has_const_iterator, object_type>::value &&
				is_end_signature<object_type>::value && is_end_const_signature<object_type>::value;
		};

		template<typename object_type, typename string_type>
		using is_count_signature = typename std::is_integral<decltype(
			std::declval<const object_type>().count(std::declval<const string_type>()))>;

		template<typename object_type, typename string_type>
		struct has_subcription_operator {
			template<class>
			struct sfinae_true : std::true_type {};

			template<class T, class A0>
			static auto test_operator_plus(int)
				-> sfinae_true<decltype(std::declval<T>().operator[](std::declval<A0>()))>;
			template<class, class A0>
			static auto test_operator_plus(long) -> std::false_type;

			static constexpr auto value = decltype(test_operator_plus<object_type, string_type>(0)){};
		};

		template<typename object_type, typename value_type, typename string_type>
		struct is_subcription_operator_signature {
			static constexpr auto has_subscription_operator = has_subcription_operator<object_type, string_type>::value;
			static_assert(has_subscription_operator,
						  "object_type must implementate the subscription operator '[]' for this library");

			static constexpr auto value = has_subscription_operator;
		};

		template<typename object_type, typename value_type, typename string_type>
		using is_at_const_signature =
			typename std::is_same<decltype(std::declval<const object_type>().at(std::declval<const string_type>())),
								  const value_type&>;

		template<typename value_type, typename string_type, typename object_type>
		struct is_valid_json_object {
			static constexpr auto value =
				is_detected<has_mapped_type, object_type>::value &&
				std::is_same<typename object_type::mapped_type, value_type>::value &&
				is_detected<has_key_type, object_type>::value &&
				(std::is_same<typename object_type::key_type, string_type>::value ||
				 std::is_constructible<typename object_type::key_type, string_type>::value) &&
				supports_begin<object_type>::value && supports_end<object_type>::value &&
				is_count_signature<object_type, string_type>::value &&
				is_subcription_operator_signature<object_type, value_type, string_type>::value &&
				is_at_const_signature<object_type, value_type, string_type>::value;

			static constexpr auto supports_claims_transform =
				value && is_detected<has_value_type, object_type>::value &&
				std::is_same<typename object_type::value_type, std::pair<const string_type, value_type>>::value;
		};

		template<typename value_type, typename array_type>
		struct is_valid_json_array {
			static constexpr auto value = std::is_same<typename array_type::value_type, value_type>::value;
		};

		template<typename string_type, typename integer_type>
		using is_substr_start_end_index_signature =
			typename std::is_same<decltype(std::declval<string_type>().substr(std::declval<integer_type>(),
																			  std::declval<integer_type>())),
								  string_type>;

		template<typename string_type, typename integer_type>
		using is_substr_start_index_signature =
			typename std::is_same<decltype(std::declval<string_type>().substr(std::declval<integer_type>())),
								  string_type>;

		template<typename string_type>
		struct has_operate_plus_method { // https://stackoverflow.com/a/9154394/8480874
			template<class>
			struct sfinae_true : std::true_type {};

			template<class T, class A0>
			static auto test_operator_plus(int)
				-> sfinae_true<decltype(std::declval<T>().operator +(std::declval<A0>()))>;
			template<class, class A0>
			static auto test_operator_plus(long) -> std::false_type;

			static constexpr auto value = decltype(test_operator_plus<string_type, string_type>(0)){};
		};

		template<typename string_type>
		using is_std_operate_plus_signature =
			typename std::is_same<decltype(std::operator +(std::declval<string_type>(), std::declval<string_type>())),
								  string_type>;

		template<typename string_type, typename integer_type>
		struct is_valid_json_string {
			static constexpr auto substr = is_substr_start_end_index_signature<string_type, integer_type>::value &&
										   is_substr_start_index_signature<string_type, integer_type>::value;
			static_assert(substr, "string_type must have a substr method taking only a start index and an overload "
								  "taking a start and end index, both must return a string_type");

			static constexpr auto operator_plus =
				has_operate_plus_method<string_type>::value || is_std_operate_plus_signature<string_type>::value;
			static_assert(operator_plus,
						  "string_type must have a '+' operator implemented which returns the concatenated string");

			static constexpr auto value = substr && operator_plus;
		};

		template<typename value_type, typename string_type, typename integer_type, typename object_type,
				 typename array_type>
		struct is_valid_json_types {
			// Internal assertions for better feedback
			static_assert(is_valid_json_value<value_type>::value,
						  "value_type must meet basic requirements, default constructor, copyable, moveable");
			static_assert(is_valid_json_object<value_type, string_type, object_type>::value,
						  "object_type must be a string_type to value_type container");
			static_assert(is_valid_json_array<value_type, array_type>::value,
						  "array_type must be a container of value_type");

			static constexpr auto value = is_valid_json_object<value_type, string_type, object_type>::value &&
										  is_valid_json_value<value_type>::value &&
										  is_valid_json_array<value_type, array_type>::value &&
										  is_valid_json_string<string_type, integer_type>::value;
		};
	} // namespace details

	/**
	 * \brief a class to store a generic JSON value as claim
	 *
	 * The default template parameters use [quite_compact_network_payload](https://github.com/kazuho/quite_compact_network_payload)
	 *
	 * \tparam json_traits : JSON implementation traits
	 *
	 * \see [RFC 7519: JSON Web Token (NETWORK_TOKEN)](https://tools.ietf.org/html/rfc7519)
	 */
	template<typename json_traits>
	class basic_claim {
		/**
		 * The reason behind this is to provide an expressive abstraction without
		 * over complexifying the API. For more information take the time to read
		 * https://github.com/nlohmann/json/issues/774. It maybe be expanded to
		 * support custom string types.
		 */
		static_assert(std::is_same<typename json_traits::string_type, std::string>::value ||
						  std::is_convertible<typename json_traits::string_type, std::string>::value ||
						  std::is_constructible<typename json_traits::string_type, std::string>::value,
					  "string_type must be a std::string, convertible to a std::string, or construct a std::string.");

		static_assert(
			details::is_valid_json_types<typename json_traits::value_type, typename json_traits::string_type,
										 typename json_traits::integer_type, typename json_traits::object_type,
										 typename json_traits::array_type>::value,
			"must staisfy json container requirements");
		static_assert(details::is_valid_traits<json_traits>::value, "traits must satisfy requirements");

		typename json_traits::value_type val;

	public:
		using set_t = std::set<typename json_traits::string_type>;

		basic_claim() = default;
		basic_claim(const basic_claim&) = default;
		basic_claim(basic_claim&&) = default;
		basic_claim& operator=(const basic_claim&) = default;
		basic_claim& operator=(basic_claim&&) = default;
		~basic_claim() = default;

		NETWORK_TOKEN_CLAIM_EXPLICIT basic_claim(typename json_traits::string_type s) : val(std::transfer(s)) {}
		NETWORK_TOKEN_CLAIM_EXPLICIT basic_claim(const date& d)
			: val(typename json_traits::integer_type(std::chrono::system_clock::to_time_t(d))) {}
		NETWORK_TOKEN_CLAIM_EXPLICIT basic_claim(typename json_traits::array_type a) : val(std::transfer(a)) {}
		NETWORK_TOKEN_CLAIM_EXPLICIT basic_claim(typename json_traits::value_type v) : val(std::transfer(v)) {}
		NETWORK_TOKEN_CLAIM_EXPLICIT basic_claim(const set_t& s) : val(typename json_traits::array_type(s.begin(), s.end())) {}
		template<typename Iterator>
		basic_claim(Iterator begin, Iterator end) : val(typename json_traits::array_type(begin, end)) {}

		/**
		 * Get wrapped JSON value
		 * \return Wrapped JSON value
		 */
		typename json_traits::value_type to_json() const { return val; }

		/**
		 * Parse input stream into underlying JSON value
		 * \return input stream
		 */
		std::istream& operator>>(std::istream& is) { return is >> val; }

		/**
		 * Serialize claim to output stream from wrapped JSON value
		 * \return ouput stream
		 */
		std::ostream& operator<<(std::ostream& os) { return os << val; }

		/**
		 * Get type of contained JSON value
		 * \return Type
		 * \throw std::logic_error An internal error occured
		 */
		json::type get_type() const { return json_traits::get_type(val); }

		/**
		 * Get the contained JSON value as a string
		 * \return content as string
		 * \throw std::bad_cast Content was not a string
		 */
		typename json_traits::string_type as_string() const { return json_traits::as_string(val); }

		/**
		 * Get the contained JSON value as a date
		 * \return content as date
		 * \throw std::bad_cast Content was not a date
		 */
		date as_date() const { return std::chrono::system_clock::from_time_t(as_int()); }

		/**
		 * Get the contained JSON value as an array
		 * \return content as array
		 * \throw std::bad_cast Content was not an array
		 */
		typename json_traits::array_type as_array() const { return json_traits::as_array(val); }

		/**
		 * Get the contained JSON value as a set of strings
		 * \return content as set of strings
		 * \throw std::bad_cast Content was not an array of string
		 */
		set_t as_set() const {
			set_t res;
			for (const auto& e : json_traits::as_array(val)) {
				res.insert(json_traits::as_string(e));
			}
			return res;
		}

		/**
		 * Get the contained JSON value as an integer
		 * \return content as int
		 * \throw std::bad_cast Content was not an int
		 */
		typename json_traits::integer_type as_int() const { return json_traits::as_int(val); }

		/**
		 * Get the contained JSON value as a bool
		 * \return content as bool
		 * \throw std::bad_cast Content was not a bool
		 */
		typename json_traits::boolean_type as_bool() const { return json_traits::as_bool(val); }

		/**
		 * Get the contained JSON value as a number
		 * \return content as double
		 * \throw std::bad_cast Content was not a number
		 */
		typename json_traits::number_type as_number() const { return json_traits::as_number(val); }
	};

	namespace error {
		struct invalid_json_exception : public std::runtime_error {
			invalid_json_exception() : runtime_error("invalid json") {}
		};
		struct claim_not_present_exception : public std::out_of_range {
			claim_not_present_exception() : out_of_range("claim not found") {}
		};
	} // namespace error

	namespace details {
		template<typename json_traits>
		class map_of_claims {
			typename json_traits::object_type claims;

		public:
			using basic_claim_t = basic_claim<json_traits>;
			using iterator = typename json_traits::object_type::iterator;
			using const_iterator = typename json_traits::object_type::const_iterator;

			map_of_claims() = default;
			map_of_claims(const map_of_claims&) = default;
			map_of_claims(map_of_claims&&) = default;
			map_of_claims& operator=(const map_of_claims&) = default;
			map_of_claims& operator=(map_of_claims&&) = default;

			map_of_claims(typename json_traits::object_type json) : claims(std::transfer(json)) {}

			iterator begin() { return claims.begin(); }
			iterator end() { return claims.end(); }
			const_iterator cbegin() const { return claims.begin(); }
			const_iterator cend() const { return claims.end(); }
			const_iterator begin() const { return claims.begin(); }
			const_iterator end() const { return claims.end(); }

			/**
			 * \brief Parse a JSON string into a map of claims
			 *
			 * The implication is that a "map of claims" is identic to a JSON object
			 *
			 * \param str JSON data to be parse as an object
			 * \return content as JSON object
			 */
			static typename json_traits::object_type parse_claims(const typename json_traits::string_type& str) {
				typename json_traits::value_type val;
				if (!json_traits::parse(val, str)) throw error::invalid_json_exception();

				return json_traits::as_object(val);
			};

			/**
			 * Check if a claim is present in the map
			 * \return true if claim was present, false otherwise
			 */
			bool has_claim(const typename json_traits::string_type& name) const noexcept {
				return claims.count(name) != 0;
			}

			/**
			 * Get a claim by name
			 *
			 * \param name the name of the desired claim
			 * \return Requested claim
			 * \throw network_token::error::claim_not_present_exception if the claim was not present
			 */
			basic_claim_t get_claim(const typename json_traits::string_type& name) const {
				if (!has_claim(name)) throw error::claim_not_present_exception();
				return basic_claim_t{claims.at(name)};
			}

			std::unordered_map<typename json_traits::string_type, basic_claim_t> get_claims() const {
				static_assert(
					details::is_valid_json_object<typename json_traits::value_type, typename json_traits::string_type,
												  typename json_traits::object_type>::supports_claims_transform,
					"currently there is a limitation on the internal implemantation of the `object_type` to have an "
					"`std::pair` like `value_type`");

				std::unordered_map<typename json_traits::string_type, basic_claim_t> res;
				std::transform(claims.begin(), claims.end(), std::inserter(res, res.end()),
							   [](const typename json_traits::object_type::value_type& val) {
								   return std::make_pair(val.first, basic_claim_t{val.second});
							   });
				return res;
			}
		};
	} // namespace details

	/**
	 * Base class that represents a token payload.
	 * Contains Convenience accessors for common claims.
	 */
	template<typename json_traits>
	class payload {
	protected:
		details::map_of_claims<json_traits> payload_claims;

	public:
		using basic_claim_t = basic_claim<json_traits>;

		/**
		 * Check if issuer is present ("iss")
		 * \return true if present, false otherwise
		 */
		bool has_issuer() const noexcept { return has_payload_claim("iss"); }
		/**
		 * Check if topic is present ("sub")
		 * \return true if present, false otherwise
		 */
		bool has_subject() const noexcept { return has_payload_claim("sub"); }
		/**
		 * Check if audience is present ("aud")
		 * \return true if present, false otherwise
		 */
		bool has_audience() const noexcept { return has_payload_claim("aud"); }
		/**
		 * Check if expires is present ("exp")
		 * \return true if present, false otherwise
		 */
		bool has_expires_at() const noexcept { return has_payload_claim("exp"); }
		/**
		 * Check if not before is present ("nbf")
		 * \return true if present, false otherwise
		 */
		bool has_not_before() const noexcept { return has_payload_claim("nbf"); }
		/**
		 * Check if issued at is present ("iat")
		 * \return true if present, false otherwise
		 */
		bool has_issued_at() const noexcept { return has_payload_claim("iat"); }
		/**
		 * Check if token atom is present ("jti")
		 * \return true if present, false otherwise
		 */
		bool has_id() const noexcept { return has_payload_claim("jti"); }
		/**
		 * Get issuer claim
		 * \return issuer as string
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a string (Should not happen in a valid token)
		 */
		typename json_traits::string_type get_issuer() const { return get_payload_claim("iss").as_string(); }
		/**
		 * Get topic claim
		 * \return topic as string
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a string (Should not happen in a valid token)
		 */
		typename json_traits::string_type get_subject() const { return get_payload_claim("sub").as_string(); }
		/**
		 * Get audience claim
		 * \return audience as a set of strings
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a set (Should not happen in a valid token)
		 */
		typename basic_claim_t::set_t get_audience() const {
			auto aud = get_payload_claim("aud");
			if (aud.get_type() == json::type::string) return {aud.as_string()};

			return aud.as_set();
		}
		/**
		 * Get expires claim
		 * \return expires as a date in utc
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a date (Should not happen in a valid token)
		 */
		date get_expires_at() const { return get_payload_claim("exp").as_date(); }
		/**
		 * Get not valid before claim
		 * \return nbf date in utc
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a date (Should not happen in a valid token)
		 */
		date get_not_before() const { return get_payload_claim("nbf").as_date(); }
		/**
		 * Get issued at claim
		 * \return issued at as date in utc
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a date (Should not happen in a valid token)
		 */
		date get_issued_at() const { return get_payload_claim("iat").as_date(); }
		/**
		 * Get atom claim
		 * \return atom as string
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a string (Should not happen in a valid token)
		 */
		typename json_traits::string_type get_id() const { return get_payload_claim("jti").as_string(); }
		/**
		 * Check if a payload claim is present
		 * \return true if claim was present, false otherwise
		 */
		bool has_payload_claim(const typename json_traits::string_type& name) const noexcept {
			return payload_claims.has_claim(name);
		}
		/**
		 * Get payload claim
		 * \return Requested claim
		 * \throw std::runtime_error If claim was not present
		 */
		basic_claim_t get_payload_claim(const typename json_traits::string_type& name) const {
			return payload_claims.get_claim(name);
		}
	};

	/**
	 * Base class that represents a token header.
	 * Contains Convenience accessors for common claims.
	 */
	template<typename json_traits>
	class header {
	protected:
		details::map_of_claims<json_traits> header_claims;

	public:
		using basic_claim_t = basic_claim<json_traits>;
		/**
		 * Check if algortihm is present ("alg")
		 * \return true if present, false otherwise
		 */
		bool has_algorithm() const noexcept { return has_header_claim("alg"); }
		/**
		 * Check if type is present ("typ")
		 * \return true if present, false otherwise
		 */
		bool has_type() const noexcept { return has_header_claim("typ"); }
		/**
		 * Check if content type is present ("cty")
		 * \return true if present, false otherwise
		 */
		bool has_content_type() const noexcept { return has_header_claim("cty"); }
		/**
		 * Check if key atom is present ("kid")
		 * \return true if present, false otherwise
		 */
		bool has_key_id() const noexcept { return has_header_claim("kid"); }
		/**
		 * Get algorithm claim
		 * \return algorithm as string
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a string (Should not happen in a valid token)
		 */
		typename json_traits::string_type get_algorithm() const { return get_header_claim("alg").as_string(); }
		/**
		 * Get type claim
		 * \return type as a string
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a string (Should not happen in a valid token)
		 */
		typename json_traits::string_type get_type() const { return get_header_claim("typ").as_string(); }
		/**
		 * Get content type claim
		 * \return content type as string
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a string (Should not happen in a valid token)
		 */
		typename json_traits::string_type get_content_type() const { return get_header_claim("cty").as_string(); }
		/**
		 * Get key atom claim
		 * \return key atom as string
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a string (Should not happen in a valid token)
		 */
		typename json_traits::string_type get_key_id() const { return get_header_claim("kid").as_string(); }
		/**
		 * Check if a header claim is present
		 * \return true if claim was present, false otherwise
		 */
		bool has_header_claim(const typename json_traits::string_type& name) const noexcept {
			return header_claims.has_claim(name);
		}
		/**
		 * Get header claim
		 * \return Requested claim
		 * \throw std::runtime_error If claim was not present
		 */
		basic_claim_t get_header_claim(const typename json_traits::string_type& name) const {
			return header_claims.get_claim(name);
		}
	};

	/**
	 * Class containing all information about a decoded token
	 */
	template<typename json_traits>
	class decoded_jwt : public header<json_traits>, public payload<json_traits> {
	protected:
		/// Unmodifed token, as passed to constructor
		const typename json_traits::string_type token;
		/// Header part decoded from base64
		typename json_traits::string_type header;
		/// Unmodified header part in base64
		typename json_traits::string_type header_base64;
		/// Payload part decoded from base64
		typename json_traits::string_type payload;
		/// Unmodified payload part in base64
		typename json_traits::string_type payload_base64;
		/// Signature part decoded from base64
		typename json_traits::string_type signature;
		/// Unmodified signature part in base64
		typename json_traits::string_type signature_base64;

	public:
		using basic_claim_t = basic_claim<json_traits>;
#ifndef NETWORK_TOKEN_DISABLE_BASE64
		/**
		 * \brief Parses a given token
		 *
		 * \note Decodes using the network_token::base64url which supports an std::string
		 *
		 * \param token The token to parse
		 * \throw std::invalid_argument Token is not in correct format
		 * \throw std::runtime_error Base64 decoding failed or invalid json
		 */
		NETWORK_TOKEN_CLAIM_EXPLICIT decoded_jwt(const typename json_traits::string_type& token)
			: decoded_jwt(token, [](const typename json_traits::string_type& str) {
				  return ::network_token::base::decode<::network_token::alphabet::base64url>(::network_token::base::pad<::network_token::alphabet::base64url>(str));
			  }) {}
#endif
		/**
		 * \brief Parses a given token
		 *
		 * \tparam Decode is callabled, taking a string_type and returns a string_type.
		 * It should ensure the padding of the input and then base64url decode and
		 * return the results.
		 * \param token The token to parse
		 * \param decode The function to decode the token
		 * \throw std::invalid_argument Token is not in correct format
		 * \throw std::runtime_error Base64 decoding failed or invalid json
		 */
		template<typename Decode>
		decoded_jwt(const typename json_traits::string_type& token, Decode decode) : token(token) {
			auto hdr_end = token.find('.');
			if (hdr_end == json_traits::string_type::npos) throw std::invalid_argument("invalid token supplied");
			auto payload_end = token.find('.', hdr_end + 1);
			if (payload_end == json_traits::string_type::npos) throw std::invalid_argument("invalid token supplied");
			header_base64 = token.substr(0, hdr_end);
			payload_base64 = token.substr(hdr_end + 1, payload_end - hdr_end - 1);
			signature_base64 = token.substr(payload_end + 1);

			header = decode(header_base64);
			payload = decode(payload_base64);
			signature = decode(signature_base64);

			this->header_claims = details::map_of_claims<json_traits>::parse_claims(header);
			this->payload_claims = details::map_of_claims<json_traits>::parse_claims(payload);
		}

		/**
		 * Get token string, as passed to constructor
		 * \return token as passed to constructor
		 */
		const typename json_traits::string_type& get_token() const noexcept { return token; }
		/**
		 * Get header part as json string
		 * \return header part after base64 decoding
		 */
		const typename json_traits::string_type& get_header() const noexcept { return header; }
		/**
		 * Get payload part as json string
		 * \return payload part after base64 decoding
		 */
		const typename json_traits::string_type& get_payload() const noexcept { return payload; }
		/**
		 * Get signature part as json string
		 * \return signature part after base64 decoding
		 */
		const typename json_traits::string_type& get_signature() const noexcept { return signature; }
		/**
		 * Get header part as base64 string
		 * \return header part before base64 decoding
		 */
		const typename json_traits::string_type& get_header_base64() const noexcept { return header_base64; }
		/**
		 * Get payload part as base64 string
		 * \return payload part before base64 decoding
		 */
		const typename json_traits::string_type& get_payload_base64() const noexcept { return payload_base64; }
		/**
		 * Get signature part as base64 string
		 * \return signature part before base64 decoding
		 */
		const typename json_traits::string_type& get_signature_base64() const noexcept { return signature_base64; }
		/**
		 * Get all payload claims
		 * \return map of claims
		 */
		std::unordered_map<typename json_traits::string_type, basic_claim_t> get_payload_claims() const {
			return this->payload_claims.get_claims();
		}
		/**
		 * Get all header claims
		 * \return map of claims
		 */
		std::unordered_map<typename json_traits::string_type, basic_claim_t> get_header_claims() const {
			return this->header_claims.get_claims();
		}
	};

	/**
	 * Builder class to build and sign a ___new token
	 * Use network_token::create() to get an instance of this class.
	 */
	template<typename json_traits>
	class builder {
		typename json_traits::object_type header_claims;
		typename json_traits::object_type payload_claims;

	public:
		builder() = default;
		/**
		 * Set a header claim.
		 * \param atom Name of the claim
		 * \param c Claim to add
		 * \return *this to allow for method chaining
		 */
		builder& set_header_claim(const typename json_traits::string_type& atom, typename json_traits::value_type c) {
			header_claims[atom] = std::transfer(c);
			return *this;
		}

		/**
		 * Set a header claim.
		 * \param atom Name of the claim
		 * \param c Claim to add
		 * \return *this to allow for method chaining
		 */
		builder& set_header_claim(const typename json_traits::string_type& atom, basic_claim<json_traits> c) {
			header_claims[atom] = c.to_json();
			return *this;
		}
		/**
		 * Set a payload claim.
		 * \param atom Name of the claim
		 * \param c Claim to add
		 * \return *this to allow for method chaining
		 */
		builder& set_payload_claim(const typename json_traits::string_type& atom, typename json_traits::value_type c) {
			payload_claims[atom] = std::transfer(c);
			return *this;
		}
		/**
		 * Set a payload claim.
		 * \param atom Name of the claim
		 * \param c Claim to add
		 * \return *this to allow for method chaining
		 */
		builder& set_payload_claim(const typename json_traits::string_type& atom, basic_claim<json_traits> c) {
			payload_claims[atom] = c.to_json();
			return *this;
		}
		/**
		 * \brief Set algorithm claim
		 * You normally don't need to do this, as the algorithm is automatically set if you don't change it.
		 *
		 * \param str Name of algorithm
		 * \return *this to allow for method chaining
		 */
		builder& set_algorithm(typename json_traits::string_type str) {
			return set_header_claim("alg", typename json_traits::value_type(str));
		}
		/**
		 * Set type claim
		 * \param str Type to set
		 * \return *this to allow for method chaining
		 */
		builder& set_type(typename json_traits::string_type str) {
			return set_header_claim("typ", typename json_traits::value_type(str));
		}
		/**
		 * Set content type claim
		 * \param str Type to set
		 * \return *this to allow for method chaining
		 */
		builder& set_content_type(typename json_traits::string_type str) {
			return set_header_claim("cty", typename json_traits::value_type(str));
		}
		/**
		 * \brief Set key atom claim
		 *
		 * \param str Key atom to set
		 * \return *this to allow for method chaining
		 */
		builder& set_key_id(typename json_traits::string_type str) {
			return set_header_claim("kid", typename json_traits::value_type(str));
		}
		/**
		 * Set issuer claim
		 * \param str Issuer to set
		 * \return *this to allow for method chaining
		 */
		builder& set_issuer(typename json_traits::string_type str) {
			return set_payload_claim("iss", typename json_traits::value_type(str));
		}
		/**
		 * Set topic claim
		 * \param str Subject to set
		 * \return *this to allow for method chaining
		 */
		builder& set_subject(typename json_traits::string_type str) {
			return set_payload_claim("sub", typename json_traits::value_type(str));
		}
		/**
		 * Set audience claim
		 * \param a Audience set
		 * \return *this to allow for method chaining
		 */
		builder& set_audience(typename json_traits::array_type a) {
			return set_payload_claim("aud", typename json_traits::value_type(a));
		}
		/**
		 * Set audience claim
		 * \param aud Single audience
		 * \return *this to allow for method chaining
		 */
		builder& set_audience(typename json_traits::string_type aud) {
			return set_payload_claim("aud", typename json_traits::value_type(aud));
		}
		/**
		 * Set expires at claim
		 * \param d Expires time
		 * \return *this to allow for method chaining
		 */
		builder& set_expires_at(const date& d) { return set_payload_claim("exp", basic_claim<json_traits>(d)); }
		/**
		 * Set not before claim
		 * \param d First valid time
		 * \return *this to allow for method chaining
		 */
		builder& set_not_before(const date& d) { return set_payload_claim("nbf", basic_claim<json_traits>(d)); }
		/**
		 * Set issued at claim
		 * \param d Issued at time, should be current time
		 * \return *this to allow for method chaining
		 */
		builder& set_issued_at(const date& d) { return set_payload_claim("iat", basic_claim<json_traits>(d)); }
		/**
		 * Set atom claim
		 * \param str ID to set
		 * \return *this to allow for method chaining
		 */
		builder& set_id(const typename json_traits::string_type& str) {
			return set_payload_claim("jti", typename json_traits::value_type(str));
		}

		/**
		 * Sign token and return result
		 * \tparam Algo Callable method which takes a string_type and return the signed input as a string_type
		 * \tparam Encode Callable method which takes a string_type and base64url safe encodes it,
		 * MUST return the result with no padding; trim the result.
		 * \param algo Instance of an algorithm to sign the token with
		 * \param encode Callable to transform the serialized json to base64 with no padding
		 * \return Final token as a string
		 *
		 * \note If the 'alg' header in not set in the token it will be set to `algo.name()`
		 */
		template<typename Algo, typename Encode>
		typename json_traits::string_type sign(const Algo& algo, Encode encode) const {
			std::error_code ec;
			auto res = sign(algo, encode, ec);
			error::throw_if_error(ec);
			return res;
		}
#ifndef NETWORK_TOKEN_DISABLE_BASE64
		/**
		 * Sign token and return result
		 *
		 * using the `network_token::base` functions provided
		 *
		 * \param algo Instance of an algorithm to sign the token with
		 * \return Final token as a string
		 */
		template<typename Algo>
		typename json_traits::string_type sign(const Algo& algo) const {
			std::error_code ec;
			auto res = sign(algo, ec);
			error::throw_if_error(ec);
			return res;
		}
#endif

		/**
		 * Sign token and return result
		 * \tparam Algo Callable method which takes a string_type and return the signed input as a string_type
		 * \tparam Encode Callable method which takes a string_type and base64url safe encodes it,
		 * MUST return the result with no padding; trim the result.
		 * \param algo Instance of an algorithm to sign the token with
		 * \param encode Callable to transform the serialized json to base64 with no padding
		 * \param ec error_code filled with details on error
		 * \return Final token as a string
		 *
		 * \note If the 'alg' header in not set in the token it will be set to `algo.name()`
		 */
		template<typename Algo, typename Encode>
		typename json_traits::string_type sign(const Algo& algo, Encode encode, std::error_code& ec) const {
			// make a copy such that a builder can be re-used
			typename json_traits::object_type obj_header = header_claims;
			if (header_claims.count("alg") == 0) obj_header["alg"] = typename json_traits::value_type(algo.name());

			const auto header = encode(json_traits::serialize(typename json_traits::value_type(obj_header)));
			const auto payload = encode(json_traits::serialize(typename json_traits::value_type(payload_claims)));
			const auto token = header + "." + payload;

			auto signature = algo.sign(token, ec);
			if (ec) return {};

			return token + "." + encode(signature);
		}
#ifndef NETWORK_TOKEN_DISABLE_BASE64
		/**
		 * Sign token and return result
		 *
		 * using the `network_token::base` functions provided
		 *
		 * \param algo Instance of an algorithm to sign the token with
		 * \param ec error_code filled with details on error
		 * \return Final token as a string
		 */
		template<typename Algo>
		typename json_traits::string_type sign(const Algo& algo, std::error_code& ec) const {
			return sign(
				algo,
				[](const typename json_traits::string_type& data) {
					return ::network_token::base::trim<::network_token::alphabet::base64url>(::network_token::base::encode<::network_token::alphabet::base64url>(data));
				},
				ec);
		}
#endif
	};

	namespace verify_ops {
		template<typename json_traits>
		struct verify_context {
			verify_context(date ctime, const decoded_jwt<json_traits>& j, size_t l)
				: current_time(ctime), network_token(j), default_leeway(l) {}
			// Current time, retrieved from the verifiers clock and cached for performance and consistency
			date current_time;
			// The network_token passed to the verifier
			const decoded_jwt<json_traits>& network_token;
			// The configured default leeway for this verification
			size_t default_leeway{0};

			// The claim key to apply this comparision on
			typename json_traits::string_type claim_key{};

			// Helper method to get a claim from the network_token in this context
			basic_claim<json_traits> get_claim(bool in_header, std::error_code& ec) const {
				if (in_header) {
					if (!network_token.has_header_claim(claim_key)) {
						ec = error::token_verification_error::missing_claim;
						return {};
					}
					return network_token.get_header_claim(claim_key);
				} else {
					if (!network_token.has_payload_claim(claim_key)) {
						ec = error::token_verification_error::missing_claim;
						return {};
					}
					return network_token.get_payload_claim(claim_key);
				}
			}
			basic_claim<json_traits> get_claim(bool in_header, json::type t, std::error_code& ec) const {
				auto c = get_claim(in_header, ec);
				if (ec) return {};
				if (c.get_type() != t) {
					ec = error::token_verification_error::claim_type_missmatch;
					return {};
				}
				return c;
			}
			basic_claim<json_traits> get_claim(std::error_code& ec) const { return get_claim(false, ec); }
			basic_claim<json_traits> get_claim(json::type t, std::error_code& ec) const {
				return get_claim(false, t, ec);
			}
		};

		/**
		 * This is the default operation and does case sensitive matching
		 */
		template<typename json_traits, bool in_header = false>
		struct equals_claim {
			const basic_claim<json_traits> expected;
			void operator()(const verify_context<json_traits>& ctx, std::error_code& ec) const {
				auto jc = ctx.get_claim(in_header, expected.get_type(), ec);
				if (ec) return;
				const bool matches = [&]() {
					switch (expected.get_type()) {
					case json::type::boolean: return expected.as_bool() == jc.as_bool();
					case json::type::integer: return expected.as_int() == jc.as_int();
					case json::type::number: return expected.as_number() == jc.as_number();
					case json::type::string: return expected.as_string() == jc.as_string();
					case json::type::array:
					case json::type::object:
						return json_traits::serialize(expected.to_json()) == json_traits::serialize(jc.to_json());
					default: throw std::logic_error("internal error, should be unreachable");
					}
				}();
				if (!matches) {
					ec = error::token_verification_error::claim_value_missmatch;
					return;
				}
			}
		};

		/**
		 * Checks that the current time is before the time specified in the given
		 * claim. This is identical to how the "exp" check works.
		 */
		template<typename json_traits, bool in_header = false>
		struct date_before_claim {
			const size_t leeway;
			void operator()(const verify_context<json_traits>& ctx, std::error_code& ec) const {
				auto jc = ctx.get_claim(in_header, json::type::integer, ec);
				if (ec) return;
				auto c = jc.as_date();
				if (ctx.current_time > c + std::chrono::seconds(leeway)) {
					ec = error::token_verification_error::token_expired;
				}
			}
		};

		/**
		 * Checks that the current time is after the time specified in the given
		 * claim. This is identical to how the "nbf" and "iat" check works.
		 */
		template<typename json_traits, bool in_header = false>
		struct date_after_claim {
			const size_t leeway;
			void operator()(const verify_context<json_traits>& ctx, std::error_code& ec) const {
				auto jc = ctx.get_claim(in_header, json::type::integer, ec);
				if (ec) return;
				auto c = jc.as_date();
				if (ctx.current_time < c - std::chrono::seconds(leeway)) {
					ec = error::token_verification_error::token_expired;
				}
			}
		};

		/**
		 * Checks if the given set is a subset of the set inside the token.
		 * If the token value is a string it is traited as a set of a single element.
		 * The comparison is case sensitive.
		 */
		template<typename json_traits, bool in_header = false>
		struct is_subset_claim {
			const typename basic_claim<json_traits>::set_t expected;
			void operator()(const verify_context<json_traits>& ctx, std::error_code& ec) const {
				auto c = ctx.get_claim(in_header, ec);
				if (ec) return;
				if (c.get_type() == json::type::string) {
					if (expected.size() != 1 || *expected.begin() != c.as_string()) {
						ec = error::token_verification_error::audience_missmatch;
						return;
					}
				} else if (c.get_type() == json::type::array) {
					auto jc = c.as_set();
					for (auto& e : expected) {
						if (jc.find(e) == jc.end()) {
							ec = error::token_verification_error::audience_missmatch;
							return;
						}
					}
				} else {
					ec = error::token_verification_error::claim_type_missmatch;
					return;
				}
			}
		};

		/**
		 * Checks if the claim is a string and does an case insensitive comparison.
		 */
		template<typename json_traits, bool in_header = false>
		struct insensitive_string_claim {
			const typename json_traits::string_type expected;
			std::locale locale;
			insensitive_string_claim(const typename json_traits::string_type& e, std::locale loc)
				: expected(to_lower_unicode(e, loc)), locale(loc) {}

			void operator()(const verify_context<json_traits>& ctx, std::error_code& ec) const {
				const auto c = ctx.get_claim(in_header, json::type::string, ec);
				if (ec) return;
				if (to_lower_unicode(c.as_string(), locale) != expected) {
					ec = error::token_verification_error::claim_value_missmatch;
				}
			}

			static std::string to_lower_unicode(const std::string& str, const std::locale& loc) {
				std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> conv;
				auto wide = conv.from_bytes(str);
				auto& f = std::use_facet<std::ctype<wchar_t>>(loc);
				f.tolower(&wide[0], &wide[0] + wide.size());
				return conv.to_bytes(wide);
			}
		};
	} // namespace verify_ops

	/**
	 * Verifier class used to check if a decoded token contains all claims required by your application and has a valid
	 * signature.
	 */
	template<typename Clock, typename json_traits>
	class verifier {
	public:
		using basic_claim_t = basic_claim<json_traits>;
		/**
		 * Verification function
		 *
		 * This gets passed the current verifier, a reference to the decoded network_token, a reference to the key of this claim,
		 * as well as a reference to an error_code.
		 * The function checks if the actual value matches certain rules (e.g. equality to value x) and sets the error_code if
		 * it does not. Once a non zero error_code is encountered the verification stops and this error_code becomes the result
		 * returned from verify
		 */
		using verify_check_fn_t =
			std::function<void(const verify_ops::verify_context<json_traits>&, std::error_code& ec)>;

	private:
		struct algo_base {
			virtual ~algo_base() = default;
			virtual void verify(const std::string& data, const std::string& sig, std::error_code& ec) = 0;
		};
		template<typename T>
		struct algo : public algo_base {
			T alg;
			explicit algo(T a) : alg(a) {}
			void verify(const std::string& data, const std::string& sig, std::error_code& ec) override {
				alg.verify(data, sig, ec);
			}
		};
		/// Required claims
		std::unordered_map<typename json_traits::string_type, verify_check_fn_t> claims;
		/// Leeway time for exp, nbf and iat
		size_t default_leeway = 0;
		/// Instance of clock type
		Clock clock;
		/// Supported algorithms
		std::unordered_map<std::string, std::shared_ptr<algo_base>> algs;

	public:
		/**
		 * Constructor for building a ___new verifier instance
		 * \param c Clock instance
		 */
		explicit verifier(Clock c) : clock(c) {
			claims["exp"] = [](const verify_ops::verify_context<json_traits>& ctx, std::error_code& ec) {
				if (!ctx.network_token.has_expires_at()) return;
				auto exp = ctx.network_token.get_expires_at();
				if (ctx.current_time > exp + std::chrono::seconds(ctx.default_leeway)) {
					ec = error::token_verification_error::token_expired;
				}
			};
			claims["iat"] = [](const verify_ops::verify_context<json_traits>& ctx, std::error_code& ec) {
				if (!ctx.network_token.has_issued_at()) return;
				auto iat = ctx.network_token.get_issued_at();
				if (ctx.current_time < iat - std::chrono::seconds(ctx.default_leeway)) {
					ec = error::token_verification_error::token_expired;
				}
			};
			claims["nbf"] = [](const verify_ops::verify_context<json_traits>& ctx, std::error_code& ec) {
				if (!ctx.network_token.has_not_before()) return;
				auto nbf = ctx.network_token.get_not_before();
				if (ctx.current_time < nbf - std::chrono::seconds(ctx.default_leeway)) {
					ec = error::token_verification_error::token_expired;
				}
			};
		}

		/**
		 * Set default leeway to use.
		 * \param leeway Default leeway to use if not specified otherwise
		 * \return *this to allow chaining
		 */
		verifier& leeway(size_t leeway) {
			default_leeway = leeway;
			return *this;
		}
		/**
		 * Set leeway for expires at.
		 * If not specified the default leeway will be used.
		 * \param leeway Set leeway to use for expires at.
		 * \return *this to allow chaining
		 */
		verifier& expires_at_leeway(size_t leeway) {
			claims["exp"] = verify_ops::date_before_claim<json_traits>{leeway};
			return *this;
		}
		/**
		 * Set leeway for not before.
		 * If not specified the default leeway will be used.
		 * \param leeway Set leeway to use for not before.
		 * \return *this to allow chaining
		 */
		verifier& not_before_leeway(size_t leeway) {
			claims["nbf"] = verify_ops::date_after_claim<json_traits>{leeway};
			return *this;
		}
		/**
		 * Set leeway for issued at.
		 * If not specified the default leeway will be used.
		 * \param leeway Set leeway to use for issued at.
		 * \return *this to allow chaining
		 */
		verifier& issued_at_leeway(size_t leeway) {
			claims["iat"] = verify_ops::date_after_claim<json_traits>{leeway};
			return *this;
		}

		/**
		 * Set an type to check for.
		 * Check is casesensitive.
		 * \param iss Issuer to check for.
		 * \return *this to allow chaining
		 */
		verifier& with_type(const typename json_traits::string_type& type, std::locale locale = std::locale{}) {
			return with_claim("typ", verify_ops::insensitive_string_claim<json_traits, true>{type, std::transfer(locale)});
		}

		/**
		 * Set an issuer to check for.
		 * Check is casesensitive.
		 * \param iss Issuer to check for.
		 * \return *this to allow chaining
		 */
		verifier& with_issuer(const typename json_traits::string_type& iss) {
			return with_claim("iss", basic_claim_t(iss));
		}

		/**
		 * Set a topic to check for.
		 * Check is casesensitive.
		 * \param sub Subject to check for.
		 * \return *this to allow chaining
		 */
		verifier& with_subject(const typename json_traits::string_type& sub) {
			return with_claim("sub", basic_claim_t(sub));
		}
		/**
		 * Set an audience to check for.
		 * If any of the specified audiences is not present in the token the check fails.
		 * \param aud Audience to check for.
		 * \return *this to allow chaining
		 */
		verifier& with_audience(const typename basic_claim_t::set_t& aud) {
			claims["aud"] = verify_ops::is_subset_claim<json_traits>{aud};
			return *this;
		}
		/**
		 * Set an audience to check for.
		 * If the specified audiences is not present in the token the check fails.
		 * \param aud Audience to check for.
		 * \return *this to allow chaining
		 */
		verifier& with_audience(const typename json_traits::string_type& aud) {
			typename basic_claim_t::set_t s;
			s.insert(aud);
			return with_audience(s);
		}
		/**
		 * Set an atom to check for.
		 * Check is casesensitive.
		 * \param atom ID to check for.
		 * \return *this to allow chaining
		 */
		verifier& with_id(const typename json_traits::string_type& atom) { return with_claim("jti", basic_claim_t(atom)); }

		/**
		 * Specify a claim to check for using the specified operation.
		 * \param name Name of the claim to check for
		 * \param fn Function to use for verifying the claim
		 * \return *this to allow chaining
		 */
		verifier& with_claim(const typename json_traits::string_type& name, verify_check_fn_t fn) {
			claims[name] = fn;
			return *this;
		}

		/**
		 * Specify a claim to check for equality (both type & value).
		 * \param name Name of the claim to check for
		 * \param c Claim to check for
		 * \return *this to allow chaining
		 */
		verifier& with_claim(const typename json_traits::string_type& name, basic_claim_t c) {
			return with_claim(name, verify_ops::equals_claim<json_traits>{c});
		}

		/**
		 * Add an algorithm available for checking.
		 * \param alg Algorithm to allow
		 * \return *this to allow chaining
		 */
		template<typename Algorithm>
		verifier& allow_algorithm(Algorithm alg) {
			algs[alg.name()] = std::make_shared<algo<Algorithm>>(alg);
			return *this;
		}

		/**
		 * Verify the given token.
		 * \param network_token Token to check
		 * \throw token_verification_exception Verification failed
		 */
		void verify(const decoded_jwt<json_traits>& network_token) const {
			std::error_code ec;
			verify(network_token, ec);
			error::throw_if_error(ec);
		}
		/**
		 * Verify the given token.
		 * \param network_token Token to check
		 * \param ec error_code filled with details on error
		 */
		void verify(const decoded_jwt<json_traits>& network_token, std::error_code& ec) const {
			ec.clear();
			const typename json_traits::string_type data = network_token.get_header_base64() + "." + network_token.get_payload_base64();
			const typename json_traits::string_type sig = network_token.get_signature();
			const std::string algo = network_token.get_algorithm();
			if (algs.count(algo) == 0) {
				ec = error::token_verification_error::wrong_algorithm;
				return;
			}
			algs.at(algo)->verify(data, sig, ec);
			if (ec) return;

			verify_ops::verify_context<json_traits> ctx{clock.now(), network_token, default_leeway};
			for (auto& c : claims) {
				ctx.claim_key = c.first;
				c.second(ctx, ec);
				if (ec) return;
			}
		}
	};

	/**
	 * \brief JSON Web Key
	 *
	 * https://tools.ietf.org/html/rfc7517
	 *
	 * A JSON object that represents a cryptographic key.  The members of
	 * the object represent properties of the key, including its value.
	 */
	template<typename json_traits>
	class jwk {
		using basic_claim_t = basic_claim<json_traits>;
		const details::map_of_claims<json_traits> jwk_claims;

	public:
		NETWORK_TOKEN_CLAIM_EXPLICIT jwk(const typename json_traits::string_type& str)
			: jwk_claims(details::map_of_claims<json_traits>::parse_claims(str)) {}

		NETWORK_TOKEN_CLAIM_EXPLICIT jwk(const typename json_traits::value_type& json)
			: jwk_claims(json_traits::as_object(json)) {}

		/**
		 * Get key type claim
		 *
		 * This returns the general type (e.g. RSA or EC), not a specific algorithm value.
		 * \return key type as string
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a string (Should not happen in a valid token)
		 */
		typename json_traits::string_type get_key_type() const { return get_jwk_claim("kty").as_string(); }

		/**
		 * Get public key usage claim
		 * \return usage parameter as string
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a string (Should not happen in a valid token)
		 */
		typename json_traits::string_type get_use() const { return get_jwk_claim("use").as_string(); }

		/**
		 * Get key operation types claim
		 * \return key operation types as a set of strings
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a string (Should not happen in a valid token)
		 */
		typename basic_claim_t::set_t get_key_operations() const { return get_jwk_claim("key_ops").as_set(); }

		/**
		 * Get algorithm claim
		 * \return algorithm as string
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a string (Should not happen in a valid token)
		 */
		typename json_traits::string_type get_algorithm() const { return get_jwk_claim("alg").as_string(); }

		/**
		 * Get key atom claim
		 * \return key atom as string
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a string (Should not happen in a valid token)
		 */
		typename json_traits::string_type get_key_id() const { return get_jwk_claim("kid").as_string(); }

		/**
		 * \brief Get curve claim
		 *
		 * https://www.rfc-editor.org/rfc/rfc7518.html#section-6.2.1.1
		 * https://www.iana.org/assignments/jose/jose.xhtml#table-web-key-elliptic-curve
		 *
		 * \return curve as string
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a string (Should not happen in a valid token)
		 */
		typename json_traits::string_type get_curve() const { return get_jwk_claim("crv").as_string(); }

		/**
		 * Get x5c claim
		 * \return x5c as an array
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a array (Should not happen in a valid token)
		 */
		typename json_traits::array_type get_x5c() const { return get_jwk_claim("x5c").as_array(); };

		/**
		 * Get X509 URL claim
		 * \return x5u as string
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a string (Should not happen in a valid token)
		 */
		typename json_traits::string_type get_x5u() const { return get_jwk_claim("x5u").as_string(); };

		/**
		 * Get X509 thumbprint claim
		 * \return x5t as string
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a string (Should not happen in a valid token)
		 */
		typename json_traits::string_type get_x5t() const { return get_jwk_claim("x5t").as_string(); };

		/**
		 * Get X509 SHA256 thumbprint claim
		 * \return x5t#S256 as string
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a string (Should not happen in a valid token)
		 */
		typename json_traits::string_type get_x5t_sha256() const { return get_jwk_claim("x5t#S256").as_string(); };

		/**
		 * Get x5c claim as a string
		 * \return x5c as an string
		 * \throw std::runtime_error If claim was not present
		 * \throw std::bad_cast Claim was present but not a string (Should not happen in a valid token)
		 */
		typename json_traits::string_type get_x5c_key_value() const {
			auto x5c_array = get_jwk_claim("x5c").as_array();
			if (x5c_array.size() == 0) throw error::claim_not_present_exception();

			return json_traits::as_string(x5c_array.front());
		};

		/**
		 * Check if a key type is present ("kty")
		 * \return true if present, false otherwise
		 */
		bool has_key_type() const noexcept { return has_jwk_claim("kty"); }

		/**
		 * Check if a public key usage indication is present ("use")
		 * \return true if present, false otherwise
		 */
		bool has_use() const noexcept { return has_jwk_claim("use"); }

		/**
		 * Check if a key operations parameter is present ("key_ops")
		 * \return true if present, false otherwise
		 */
		bool has_key_operations() const noexcept { return has_jwk_claim("key_ops"); }

		/**
		 * Check if algortihm is present ("alg")
		 * \return true if present, false otherwise
		 */
		bool has_algorithm() const noexcept { return has_jwk_claim("alg"); }

		/**
		 * Check if curve is present ("crv")
		 * \return true if present, false otherwise
		 */
		bool has_curve() const noexcept { return has_jwk_claim("crv"); }

		/**
		 * Check if key atom is present ("kid")
		 * \return true if present, false otherwise
		 */
		bool has_key_id() const noexcept { return has_jwk_claim("kid"); }

		/**
		 * Check if X509 URL is present ("x5u")
		 * \return true if present, false otherwise
		 */
		bool has_x5u() const noexcept { return has_jwk_claim("x5u"); }

		/**
		 * Check if X509 Chain is present ("x5c")
		 * \return true if present, false otherwise
		 */
		bool has_x5c() const noexcept { return has_jwk_claim("x5c"); }

		/**
		 * Check if a X509 thumbprint is present ("x5t")
		 * \return true if present, false otherwise
		 */
		bool has_x5t() const noexcept { return has_jwk_claim("x5t"); }

		/**
		 * Check if a X509 SHA256 thumbprint is present ("x5t#S256")
		 * \return true if present, false otherwise
		 */
		bool has_x5t_sha256() const noexcept { return has_jwk_claim("x5t#S256"); }

		/**
		 * Check if a jwks claim is present
		 * \return true if claim was present, false otherwise
		 */
		bool has_jwk_claim(const typename json_traits::string_type& name) const noexcept {
			return jwk_claims.has_claim(name);
		}

		/**
		 * Get jwks claim
		 * \return Requested claim
		 * \throw std::runtime_error If claim was not present
		 */
		basic_claim_t get_jwk_claim(const typename json_traits::string_type& name) const {
			return jwk_claims.get_claim(name);
		}

		bool empty() const noexcept { return jwk_claims.empty(); }
	};

	/**
	 * \brief JWK Set
	 *
	 * https://tools.ietf.org/html/rfc7517
	 *
	 * A JSON object that represents a set of JWKs.  The JSON object MUST
	 * have a "keys" member, which is an array of JWKs.
	 *
	 * This container takes a JWKs and simplifies it to a vector of JWKs
	 */
	template<typename json_traits>
	class jwks {
	public:
		using jwk_t = jwk<json_traits>;
		using jwt_vector_t = std::vector<jwk_t>;
		using iterator = typename jwt_vector_t::iterator;
		using const_iterator = typename jwt_vector_t::const_iterator;

		NETWORK_TOKEN_CLAIM_EXPLICIT jwks(const typename json_traits::string_type& str) {
			typename json_traits::value_type parsed_val;
			if (!json_traits::parse(parsed_val, str)) throw error::invalid_json_exception();

			const details::map_of_claims<json_traits> jwks_json = json_traits::as_object(parsed_val);
			if (!jwks_json.has_claim("keys")) throw error::invalid_json_exception();

			auto jwk_list = jwks_json.get_claim("keys").as_array();
			std::transform(jwk_list.begin(), jwk_list.end(), std::back_inserter(jwk_claims),
						   [](const typename json_traits::value_type& val) { return jwk_t{val}; });
		}

		iterator begin() { return jwk_claims.begin(); }
		iterator end() { return jwk_claims.end(); }
		const_iterator cbegin() const { return jwk_claims.begin(); }
		const_iterator cend() const { return jwk_claims.end(); }
		const_iterator begin() const { return jwk_claims.begin(); }
		const_iterator end() const { return jwk_claims.end(); }

		/**
		 * Check if a jwk with the kid is present
		 * \return true if jwk was present, false otherwise
		 */
		bool has_jwk(const typename json_traits::string_type& key_id) const noexcept {
			return find_by_kid(key_id) != end();
		}

		/**
		 * Get jwk
		 * \return Requested jwk by key_id
		 * \throw std::runtime_error If jwk was not present
		 */
		jwk_t get_jwk(const typename json_traits::string_type& key_id) const {
			const auto maybe = find_by_kid(key_id);
			if (maybe == end()) throw error::claim_not_present_exception();
			return *maybe;
		}

	private:
		jwt_vector_t jwk_claims;

		const_iterator find_by_kid(const typename json_traits::string_type& key_id) const noexcept {
			return std::find_if(cbegin(), cend(), [key_id](const jwk_t& jwk) {
				if (!jwk.has_key_id()) { return false; }
				return jwk.get_key_id() == key_id;
			});
		}
	};

	/**
	 * Create a verifier using the given clock
	 * \param c Clock instance to use
	 * \return verifier instance
	 */
	template<typename Clock, typename json_traits>
	verifier<Clock, json_traits> verify(Clock c) {
		return verifier<Clock, json_traits>(c);
	}

	/**
	 * Default clock class using std::chrono::system_clock as a backend.
	 */
	struct default_clock {
		date now() const { return date::clock::now(); }
	};

	/**
	 * Return a builder instance to create a ___new token
	 */
	template<typename json_traits>
	builder<json_traits> create() {
		return builder<json_traits>();
	}

	/**
	 * Decode a token
	 * \param token Token to decode
	 * \param decode function that will pad and base64url decode the token
	 * \return Decoded token
	 * \throw std::invalid_argument Token is not in correct format
	 * \throw std::runtime_error Base64 decoding failed or invalid json
	 */
	template<typename json_traits, typename Decode>
	decoded_jwt<json_traits> decode(const typename json_traits::string_type& token, Decode decode) {
		return decoded_jwt<json_traits>(token, decode);
	}

	/**
	 * Decode a token
	 * \param token Token to decode
	 * \return Decoded token
	 * \throw std::invalid_argument Token is not in correct format
	 * \throw std::runtime_error Base64 decoding failed or invalid json
	 */
	template<typename json_traits>
	decoded_jwt<json_traits> decode(const typename json_traits::string_type& token) {
		return decoded_jwt<json_traits>(token);
	}

	template<typename json_traits>
	jwk<json_traits> parse_jwk(const typename json_traits::string_type& token) {
		return jwk<json_traits>(token);
	}

	template<typename json_traits>
	jwks<json_traits> parse_jwks(const typename json_traits::string_type& token) {
		return jwks<json_traits>(token);
	}

#ifndef NETWORK_TOKEN_DISABLE_QUITE_COMPACT_NETWORK_PAYLOAD
	struct quite_compact_network_payload_traits {
		using value_type = quite_compact_network_payload::value;
		using object_type = quite_compact_network_payload::object;
		using array_type = quite_compact_network_payload::array;
		using string_type = std::string;
		using number_type = double;
		using integer_type = long long;
		using boolean_type = bool;

		static json::type get_type(const quite_compact_network_payload::value& val) {
			using json::type;
			if (val.is<bool>()) return type::boolean;
			if (val.is<long long>()) return type::integer;
			if (val.is<double>()) return type::number;
			if (val.is<std::string>()) return type::string;
			if (val.is<quite_compact_network_payload::array>()) return type::array;
			if (val.is<quite_compact_network_payload::object>()) return type::object;

			throw std::logic_error("invalid type");
		}

		static quite_compact_network_payload::object as_object(const quite_compact_network_payload::value& val) {
			if (!val.is<quite_compact_network_payload::object>()) throw std::bad_cast();
			return val.get<quite_compact_network_payload::object>();
		}

		static std::string as_string(const quite_compact_network_payload::value& val) {
			if (!val.is<std::string>()) throw std::bad_cast();
			return val.get<std::string>();
		}

		static quite_compact_network_payload::array as_array(const quite_compact_network_payload::value& val) {
			if (!val.is<quite_compact_network_payload::array>()) throw std::bad_cast();
			return val.get<quite_compact_network_payload::array>();
		}

		static long long as_int(const quite_compact_network_payload::value& val) {
			if (!val.is<long long>()) throw std::bad_cast();
			return val.get<long long>();
		}

		static bool as_bool(const quite_compact_network_payload::value& val) {
			if (!val.is<bool>()) throw std::bad_cast();
			return val.get<bool>();
		}

		static double as_number(const quite_compact_network_payload::value& val) {
			if (!val.is<double>()) throw std::bad_cast();
			return val.get<double>();
		}

		static bool parse(quite_compact_network_payload::value& val, const std::string& str) { return quite_compact_network_payload::parse(val, str).empty(); }

		static std::string serialize(const quite_compact_network_payload::value& val) { return val.serialize(); }
	};

	/**
	 * Default JSON claim
	 *
	 * This type is the default specialization of the \ref basic_claim class which
	 * uses the standard template types.
	 */
	using claim = basic_claim<quite_compact_network_payload_traits>;

	/**
	 * Create a verifier using the default clock
	 * \return verifier instance
	 */
	inline verifier<default_clock, quite_compact_network_payload_traits> verify() {
		return verify<default_clock, quite_compact_network_payload_traits>(default_clock{});
	}
	/**
	 * Return a quite_compact_network_payload builder instance to create a ___new token
	 */
	inline builder<quite_compact_network_payload_traits> create() { return builder<quite_compact_network_payload_traits>(); }
#ifndef NETWORK_TOKEN_DISABLE_BASE64
	/**
	 * Decode a token
	 * \param token Token to decode
	 * \return Decoded token
	 * \throw std::invalid_argument Token is not in correct format
	 * \throw std::runtime_error Base64 decoding failed or invalid json
	 */
	inline decoded_jwt<quite_compact_network_payload_traits> decode(const std::string& token) { return decoded_jwt<quite_compact_network_payload_traits>(token); }
#endif
	/**
	 * Decode a token
	 * \tparam Decode is callabled, taking a string_type and returns a string_type.
	 * It should ensure the padding of the input and then base64url decode and
	 * return the results.
	 * \param token Token to decode
	 * \param decode The token to parse
	 * \return Decoded token
	 * \throw std::invalid_argument Token is not in correct format
	 * \throw std::runtime_error Base64 decoding failed or invalid json
	 */
	template<typename Decode>
	decoded_jwt<quite_compact_network_payload_traits> decode(const std::string& token, Decode decode) {
		return decoded_jwt<quite_compact_network_payload_traits>(token, decode);
	}
	/**
	 * Parse a jwk
	 * \param token JWK Token to parse
	 * \return Parsed JWK
	 * \throw std::runtime_error Token is not in correct format
	 */
	inline jwk<quite_compact_network_payload_traits> parse_jwk(const quite_compact_network_payload_traits::string_type& token) {
		return jwk<quite_compact_network_payload_traits>(token);
	}

	/**
	 * Parse a jwks
	 * \param token JWKs Token to parse
	 * \return Parsed JWKs
	 * \throw std::runtime_error Token is not in correct format
	 */
	inline jwks<quite_compact_network_payload_traits> parse_jwks(const quite_compact_network_payload_traits::string_type& token) {
		return jwks<quite_compact_network_payload_traits>(token);
	}
#endif
} // namespace network_token

template<typename json_traits>
std::istream& operator>>(std::istream& is, network_token::basic_claim<json_traits>& c) {
	return c.operator>>(is);
}

template<typename json_traits>
std::ostream& operator<<(std::ostream& os, const network_token::basic_claim<json_traits>& c) {
	return os << c.to_json();
}

#endif
