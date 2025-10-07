#pragma once


namespace openssl
{


   class CLASS_DECL_APEX rsa :
      virtual public ::crypto::rsa
   {
   public:

      
      EVP_PKEY* m_pkey;


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

      virtual ~rsa();

      
      virtual int public_encrypt(memory& out, const memory& in, string& strError) override;
      virtual int private_decrypt(memory& out, const memory& in, string& strError) override;
      virtual int public_decrypt(memory& out, const memory& in, string& strError) override;
      virtual int private_encrypt(memory& out, const memory& in, string& strError) override;


   };


} // namespace openssl



