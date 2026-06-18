#pragma once


namespace winrt
{


   class CLASS_DECL_APEX rsa :
      virtual public ::crypto::rsa
   {
   public:


      ::winrt::Windows::Security::Cryptography::Core::CryptographicKey ^ m_pkey;


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


      virtual ::i32 public_encrypt(memory& out, const memory& in, string& strError) override;
      virtual ::i32 private_decrypt(memory& out, const memory& in, string& strError) override;
      virtual ::i32 public_decrypt(memory& out, const memory& in, string& strError) override;
      virtual ::i32 private_encrypt(memory& out, const memory& in, string& strError) override;


   };


} // namespace winrt



