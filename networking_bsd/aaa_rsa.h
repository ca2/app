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

      
      virtual ::i32 public_encrypt(memory& out, const memory& in, string& strError) override;
      virtual ::i32 private_decrypt(memory& out, const memory& in, string& strError) override;
      virtual ::i32 public_decrypt(memory& out, const memory& in, string& strError) override;
      virtual ::i32 private_encrypt(memory& out, const memory& in, string& strError) override;


   };


} // namespace crypto_openssl



