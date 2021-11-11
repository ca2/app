#pragma once


namespace crypto_openssl
{


   class CLASS_DECL_CRYPTO_OPENSSL rsa :
      virtual public ::crypto::rsa
   {
   public:

      
      EVP_PKEY* m_pkey;


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

      virtual ~rsa();

      
      virtual int public_encrypt(memory& out, const memory& in, string& strError) override;
      virtual int private_decrypt(memory& out, const memory& in, string& strError) override;
      virtual int public_decrypt(memory& out, const memory& in, string& strError) override;
      virtual int private_encrypt(memory& out, const memory& in, string& strError) override;


   };


} // namespace crypto_openssl



