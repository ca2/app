#include "framework.h"
#include "rsa.h"
#include "acme/exception/resource.h"
#include "acme/parallelization/single_lock.h"
#include "acme/primitive/primitive/memory.h"


namespace crypto_openssl
{


   rsa::rsa()
   {


   }


   rsa::rsa(
      const string& strN,
      const string& strE,
      const string& strD,
      const string& strP,
      const string& strQ,
      const string& strDmp1,
      const string& strDmq1,
      const string& strIqmp)
   {

      BIGNUM* n = BN_new();
      BIGNUM* e = BN_new();
      BIGNUM* d = BN_new();
      BIGNUM* p = BN_new();
      BIGNUM* q = BN_new();
      BIGNUM* dmp1 = BN_new();
      BIGNUM* dmq1 = BN_new();
      BIGNUM* iqmp = BN_new();

      BN_hex2bn(&n, strN);
      BN_hex2bn(&e, strE);
      BN_hex2bn(&d, strD);
      BN_hex2bn(&p, strP);
      BN_hex2bn(&q, strQ);
      BN_hex2bn(&dmp1, strDmp1);
      BN_hex2bn(&dmq1, strDmq1);
      BN_hex2bn(&iqmp, strIqmp);


#if OPENSSL_VERSION_NUMBER >= 0x30000000


      //OSSL_PARAM_BLD* params_build = OSSL_PARAM_BLD_new();
      //if (params_build == NULL) {
      //   goto OPENSSL_ERROR;
      //}
      //if (!OSSL_PARAM_BLD_push_BN(params_build, "n", modulus)) {
      //   ERROR("Error: failed to push modulus into param build.\n");
      //   goto OPENSSL_ERROR;
      //}
      //if (!OSSL_PARAM_BLD_push_BN(params_build, "e", exponent)) {
      //   ERROR("Error: failed to push exponent into param build.\n");
      //   goto OPENSSL_ERROR;
      //}
      //if (!OSSL_PARAM_BLD_push_BN(params_build, "d", NULL)) {
      //   ERROR("Error: failed to push NULL into param build.\n");
      //   goto OPENSSL_ERROR;
      //}
      //OSSL_PARAM* params = OSSL_PARAM_BLD_to_param(params_build);
      //if (params == NULL) {
      //   ERROR("Error: failed to construct params from build.\n");
      //   goto OPENSSL_ERROR;
      //}
      OSSL_PARAM params[] = {
         OSSL_PARAM_BN("n", n, (size_t)BN_num_bytes(n)),
         OSSL_PARAM_BN("e", e, (size_t)BN_num_bytes(e)),
         OSSL_PARAM_BN("d", d, (size_t)BN_num_bytes(d)),
         OSSL_PARAM_BN("p", p, (size_t)BN_num_bytes(p)),
         OSSL_PARAM_BN("q", q, (size_t)BN_num_bytes(q)),
         OSSL_PARAM_BN("dmp1", dmq1, (size_t)BN_num_bytes(dmp1)),
         OSSL_PARAM_BN("dmq1", dmq1, (size_t)BN_num_bytes(dmq1)),
         OSSL_PARAM_BN("iqmp", iqmp, (size_t)BN_num_bytes(iqmp)),
         OSSL_PARAM_END
      };

      EVP_PKEY_CTX* pctx = EVP_PKEY_CTX_new_from_name(NULL, "RSA", NULL);

      m_pkey = NULL;

      if (pctx == NULL
         || EVP_PKEY_fromdata_init(pctx) <= 0
         || EVP_PKEY_fromdata(pctx, &m_pkey, EVP_PKEY_KEYPAIR, params) <= 0)
      {

         throw resource_exception();

      }

      EVP_PKEY_CTX_free(pctx);

#else

      m_prsa = RSA_new();

#if OPENSSL_VERSION_NUMBER < 0x10100000L

      m_prsa->n = n;
      m_prsa->e = e;
      m_prsa->d = d;
      m_prsa->p = point;
      m_prsa->q = q;
      m_prsa->dmp1 = dmp1;
      m_prsa->dmq1 = dmq1;
      m_prsa->iqmp = iqmp;

#else

      RSA_set0_key(m_prsa, n, e, d);
      RSA_set0_factors(m_prsa, p, q);
      RSA_set0_crt_params(m_prsa, dmp1, dmq1, iqmp);

#endif

#endif


      //#if OPENSSL_VERSION_NUMBER < 0x10100000L
      //      m_prsa->n = n;
      //      m_prsa->e = e;
      //      m_prsa->d = d;
      //      m_prsa->p = p;
      //      m_prsa->q = q;
      //      m_prsa->dmp1 = dmp1;
      //      m_prsa->dmq1 = dmq1;
      //      m_prsa->iqmp = iqmp;
      //#else
      //      RSA_set0_key(m_prsa, n, e, d);
      //      RSA_set0_factors(m_prsa, p, q);
      //      RSA_set0_crt_params(m_prsa, dmp1, dmq1, iqmp);
      //#endif

   }


   rsa::rsa(const string& nParam)
   {

      BIGNUM* n = BN_new();
      BIGNUM* e = BN_new();

      BN_hex2bn(&n, nParam);
      BN_hex2bn(&e, "10001");

#if OPENSSL_VERSION_NUMBER >= 0x30000000

      OSSL_PARAM params[] = {
         OSSL_PARAM_BN("n", n, (size_t)BN_num_bytes(n)),
         OSSL_PARAM_BN("e", e, (size_t)BN_num_bytes(e)),
         OSSL_PARAM_END
      };


      EVP_PKEY_CTX* pctx = EVP_PKEY_CTX_new_from_name(NULL, "RSA", NULL);

      m_pkey = NULL;

      if (pctx == NULL
         || EVP_PKEY_fromdata_init(pctx) <= 0
         || EVP_PKEY_fromdata(pctx, &m_pkey, EVP_PKEY_KEYPAIR, params) <= 0)
      {

         throw resource_exception();

      }

      EVP_PKEY_CTX_free(pctx);

#else


      m_prsa = RSA_new();

#if OPENSSL_VERSION_NUMBER < 0x10100000L

      m_prsa->n = n;
      m_prsa->e = e;

#else

      RSA_set0_key(m_prsa, n, e, nullptr);

#endif


#endif

   }


   rsa::~rsa()
   {

#if OPENSSL_VERSION_NUMBER >= 0x30000000

      if (m_pkey != nullptr)
      {

         EVP_PKEY_free(m_pkey);

      }

#else

      if (m_prsa != nullptr)
      {

         RSA_free(m_prsa);

      }

#endif

   }


   int rsa::public_encrypt(memory& out, const memory& in, string& strError)
   {


#if OPENSSL_VERSION_NUMBER >= 0x30000000

      auto pctx = EVP_PKEY_CTX_new(m_pkey, nullptr);

      if (EVP_PKEY_encrypt_init(pctx) <= 0)
      {

         return -1;

      }

      if (EVP_PKEY_CTX_set_rsa_padding(pctx, RSA_PKCS1_PADDING) <= 0)
      {

         return -1;

      }

      size_t out_len = 0;

      i32 i = EVP_PKEY_encrypt(pctx, nullptr, &out_len, (const uchar*)(const char*)in.get_data(), (i32)in.get_size());

      out.set_size(out_len);

      i = EVP_PKEY_encrypt(pctx, out.get_data(), &out_len, (const uchar*)(const char*)in.get_data(), (i32)in.get_size());

      if (i < 0)
      {

         strError = ERR_error_string(ERR_get_error(), nullptr);

         out.set_size(0);

      }
      else
      {

         out.set_size(i);

      }

      EVP_PKEY_CTX_free(pctx);

#else


      i32 i = RSA_public_encrypt((i32)in.get_size(), (const uchar*)(const char*)in.get_data(), out.get_data(), m_prsa, RSA_PKCS1_PADDING);

      strError = ERR_error_string(ERR_get_error(), nullptr);

      out.set_size(i);

      return int(out.get_size());


#endif

      return int(out.get_size());

   }


   int rsa::private_decrypt(memory& out, const memory& in, string& strError)
   {


#if defined(_UWP) && !defined(HAVE_OPENSSL)

      out.set_os_crypt_buffer(::winrt::Windows::Security::Cryptography::Core::CryptographicEngine::Decrypt(m_prsa, in.get_os_crypt_buffer(), nullptr));

#elif OPENSSL_VERSION_NUMBER >= 0x30000000

      single_lock synchronouslock(synchronization(), true);

      auto pctx = EVP_PKEY_CTX_new(m_pkey, nullptr);

      if (EVP_PKEY_decrypt_init(pctx) <= 0)
      {

         return -1;

      }

      if (EVP_PKEY_CTX_set_rsa_padding(pctx, RSA_PKCS1_PADDING) <= 0)
      {

         return -1;

      }

      size_t out_len = 0;

      i32 i = EVP_PKEY_decrypt(pctx, nullptr, &out_len, (const uchar*)(const char*)in.get_data(), (i32)in.get_size());

      out.set_size(out_len);

      i = EVP_PKEY_decrypt(pctx, out.get_data(), &out_len, (const uchar*)(const char*)in.get_data(), (i32)in.get_size());

      if (i < 0)
      {

         strError = ERR_error_string(ERR_get_error(), nullptr);

         out.set_size(0);

      }
      else
      {

         out.set_size(i);

      }

      EVP_PKEY_CTX_free(pctx);

#else


      single_lock sl(mutex(), true);

      i32 iRsaSize = 8192;

      out.set_size(iRsaSize);

      out.set(0);

      ::count i = RSA_private_decrypt((int)in.get_size(), in.get_data(), out.get_data(), m_prsa, RSA_PKCS1_PADDING);

      if (i < 0 || i >(1024 * 1024))
      {

         strError = ERR_error_string(ERR_get_error(), nullptr);

         return (int)i;

      }

      out.set_size(i);


#endif

      return int(out.get_size());

   }


   int rsa::private_encrypt(memory& out, const memory& in, string& strError)
   {

#ifdef MACOS_DEPRECATED

      SecTransformRef transform = SecEncryptTransformCreate(m_prsa, &error);

      if (error != nullptr)
      {

         CFRelease(error);

         return "";

      }

      SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);

      if (error != nullptr)
      {

         CFRelease(transform);

         CFRelease(error);

         return "";

      }

      memory memDataIn;

      memDataIn.from_hex(strRsaModulus);

      CFDataRef dataIn = memDataIn.get_os_cf_data();

      SecTransformSetAttribute(transform, kSecTransformInputAttributeName, dataIn, &error);

      if (error != nullptr)
      {

         CFRelease(dataIn);

         CFRelease(transform);

         CFRelease(error);

         return "";

      }

      /* Encrypt the data. */

      CFDataRef data = (CFDataRef)SecTransformExecute(transform, &error);

      if (error != nullptr)
      {

         CFRelease(dataIn);

         CFRelease(transform);

         CFRelease(error);

         return "";

      }

      string strHex;

      memory memory;

      memory.set_os_cf_data(data);

      memory.to_hex(strHex);

      CFRelease(data);

      CFRelease(dataIn);

      CFRelease(transform);

#elif defined(_UWP) && !defined(HAVE_OPENSSL)

      out.set_os_crypt_buffer(::winrt::Windows::Security::Cryptography::Core::CryptographicEngine::Encrypt(m_prsa, in.get_os_crypt_buffer(), nullptr));




#elif OPENSSL_VERSION_NUMBER >= 0x30000000

      //auto iInSize = (i32)in.get_size();

      //auto pInData = (const uchar*)(const char*)in.get_data();

      //auto pOutData = out.get_data();

      auto pctx = EVP_PKEY_CTX_new(m_pkey, nullptr);

      if (EVP_PKEY_encrypt_init(pctx) <= 0)
      {

         return -1;

      }

      if (EVP_PKEY_CTX_set_rsa_padding(pctx, RSA_PKCS1_PADDING) <= 0)
      {

         return -1;

      }

      size_t out_len = 0;

      i32 i = EVP_PKEY_encrypt(pctx, nullptr, &out_len, (const uchar*)(const char*)in.get_data(), (i32)in.get_size());

      out.set_size(out_len);

      i = EVP_PKEY_encrypt(pctx, out.get_data(), &out_len, (const uchar*)(const char*)in.get_data(), (i32)in.get_size());

      if (i < 0)
      {

         strError = ERR_error_string(ERR_get_error(), nullptr);

         out.set_size(0);

      }
      else
      {

         out.set_size(i);

      }

      EVP_PKEY_CTX_free(pctx);

#else

      auto iInSize = (i32)in.get_size();

      auto pInData = (const uchar*)(const char*)in.get_data();

      auto pOutData = out.get_data();

      auto prsa = m_prsa;

      i32 i = RSA_private_encrypt(iInSize, pInData, pOutData, prsa, RSA_PKCS1_PADDING);

      strError = ERR_error_string(ERR_get_error(), nullptr);

      out.set_size(i);


#endif

      return int(out.get_size());

   }


   int rsa::public_decrypt(memory& out, const memory& in, string& strError)
   {


#if defined(_UWP) && !defined(HAVE_OPENSSL)

      out.set_os_crypt_buffer(::winrt::Windows::Security::Cryptography::Core::CryptographicEngine::Decrypt(m_prsa, in.get_os_crypt_buffer(), nullptr));

#elif OPENSSL_VERSION_NUMBER >= 0x30000000

      single_lock synchronouslock(synchronization(), true);

      auto pctx = EVP_PKEY_CTX_new(m_pkey, nullptr);

      if (EVP_PKEY_decrypt_init(pctx) <= 0)
      {

         return -1;

      }


      if (EVP_PKEY_CTX_set_rsa_padding(pctx, RSA_PKCS1_PADDING) <= 0)
      {

         return -1;

      }

      size_t out_len = 0;

      ::count i = EVP_PKEY_decrypt(pctx, nullptr, &out_len, in.get_data(), (int)in.get_size());

      if (i < 0)
      {

         strError = ERR_error_string(ERR_get_error(), nullptr);

         return (int)i;

      }

      out.set_size(i);

      i = EVP_PKEY_decrypt(pctx, out.get_data(), &out_len, in.get_data(), (int)in.get_size());

      if (i < 0)
      {

         strError = ERR_error_string(ERR_get_error(), nullptr);

         return (int)i;

      }

      out.set_size(i);

#else


      single_lock sl(mutex(), true);

      i32 iRsaSize = 8192;

      out.set_size(iRsaSize);

      out.set(0);

      ::count i = RSA_public_decrypt((int)in.get_size(), in.get_data(), out.get_data(), m_prsa, RSA_PKCS1_PADDING);

      if (i < 0 || i >(1024 * 1024))
      {

         strError = ERR_error_string(ERR_get_error(), nullptr);

         return (int)i;

      }

      out.set_size(i);


#endif

      return int(out.get_size());

   }


} //  namespace crypto_openssl

//
//::pointer<::crypto::rsa>__create_rsa(const string& str)
//{
//
//   return __new(::openssl::rsa(str));
//
//}
//


