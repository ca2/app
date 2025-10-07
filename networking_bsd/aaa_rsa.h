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
         const ::scoped_string & scopedstrN,
         const ::scoped_string & scopedstrE,
         const ::scoped_string & scopedstrD,
         const ::scoped_string & scopedstrP,
         const ::scoped_string & scopedstrQ,
         const ::scoped_string & scopedstrDmp1,
         const ::scoped_string & scopedstrDmq1,
         const ::scoped_string & scopedstrIqmp);

      rsa(const ::scoped_string & scopedstr);
      ~rsa() override;

      
      virtual int public_encrypt(memory& out, const memory& in, string& strError) override;
      virtual int private_decrypt(memory& out, const memory& in, string& strError) override;
      virtual int public_decrypt(memory& out, const memory& in, string& strError) override;
      virtual int private_encrypt(memory& out, const memory& in, string& strError) override;


   };


} // namespace crypto_openssl



