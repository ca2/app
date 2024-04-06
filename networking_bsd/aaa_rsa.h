#pragma once


namespace crypto_openssl
{


   class CLASS_DECL_CRYPTO_OPENSSL rsa :
      virtual public ::crypto::rsa
   {
   public:


#if OPENSSL_VERSION_NUMBER >= 0x30000000

      EVP_PKEY* m_pkey;

#else

      RSA * m_prsa;

#endif

      rsa();

      rsa(
         const string& strN,
         const string& strE,
         const string& strD,
         const string& strP,
         const string& strQ,
         const string& strDmp1,
         const string& strDmq1,
         const string& strIqmp);

      rsa(const string& str);
      ~rsa() override;

      
      virtual int public_encrypt(memory& out, const memory& in, string& strError) override;
      virtual int private_decrypt(memory& out, const memory& in, string& strError) override;
      virtual int public_decrypt(memory& out, const memory& in, string& strError) override;
      virtual int private_encrypt(memory& out, const memory& in, string& strError) override;


   };


} // namespace crypto_openssl



