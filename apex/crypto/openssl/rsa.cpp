#include "framework.h"
#include "_openssl.h"


namespace openssl
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

      m_prsa = RSA_new();

      BIGNUM* n = BN_new();
      BIGNUM* e = BN_new();
      BIGNUM* d = BN_new();
      BIGNUM* point = BN_new();
      BIGNUM* q = BN_new();
      BIGNUM* dmp1 = BN_new();
      BIGNUM* dmq1 = BN_new();
      BIGNUM* iqmp = BN_new();

      BN_hex2bn(&n, strN);
      BN_hex2bn(&e, strE);
      BN_hex2bn(&d, strD);
      BN_hex2bn(&point, strP);
      BN_hex2bn(&q, strQ);
      BN_hex2bn(&dmp1, strDmp1);
      BN_hex2bn(&dmq1, strDmq1);
      BN_hex2bn(&iqmp, strIqmp);

#if defined(_UWP) && (OPENSSL_API_COMPAT < 0x10100000L)
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
      RSA_set0_factors(m_prsa, point, q);
      RSA_set0_crt_params(m_prsa, dmp1, dmq1, iqmp);
#endif

   }


   rsa::rsa(const string& nParam)
   {

      BIGNUM* n = BN_new();
      BIGNUM* e = BN_new();

      m_prsa = RSA_new();

      BN_hex2bn(&n, nParam);
      BN_hex2bn(&e, "10001");

#if (defined(_UWP)) && (OPENSSL_API_COMPAT < 0x10100000L)
      m_prsa->n = n;
      m_prsa->e = e;
#else
      RSA_set0_key(m_prsa, n, e, nullptr);
#endif

      //BN_free(n);
      //BN_free(e);

   }



   rsa::~rsa()
   {

      if (m_prsa != nullptr)
      {

         RSA_free(m_prsa);
         m_prsa = nullptr;

      }


   }


   int rsa::public_encrypt(memory& out, const memory& in, string& strError)
   {

      i32 i = RSA_public_encrypt((i32)in.get_size(), (const uchar*)(const char*)in.get_data(), out.get_data(), m_prsa, RSA_PKCS1_PADDING);

      strError = ERR_error_string(ERR_get_error(), nullptr);

      out.set_size(i);

      return int(out.get_size());


   }




   int rsa::private_decrypt(memory& out, const memory& in, string& strError)
   {


#if defined(_UWP) && !defined(HAVE_OPENSSL)



      out.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Decrypt(m_prsa, in.get_os_crypt_buffer(), nullptr));




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



      out.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Encrypt(m_prsa, in.get_os_crypt_buffer(), nullptr));




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



      out.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Decrypt(m_prsa, in.get_os_crypt_buffer(), nullptr));




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


} // namespace openssl


__pointer(::crypto::rsa) __create_rsa(const string& str)
{

   return __new(::openssl::rsa(str));

}



