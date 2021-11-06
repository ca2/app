#pragma once


namespace winrt
{


   class CLASS_DECL_APEX hasher :
      public ::crypto::hasher
   {
   public:


      enum_hash      m_ehash;

      ::winrt::Windows::Security::Cryptography::Core::CryptographicHash^ m_phash;


      hasher(::winrt::Windows::Security::Cryptography::Core::CryptographicHash^ phash, enum_hash ehash);


      static String^ get_os_provider_name(enum_hash ehash);
      static ::winrt::Windows::Security::Cryptography::Core::HashAlgorithmProvider^ get_os_provider(enum_hash ehash);

      virtual enum_hash ehash() const override;

      virtual void update(const block& block) override;

      virtual memory get_hash_and_reset() override;


   };




} // namespace winrt



