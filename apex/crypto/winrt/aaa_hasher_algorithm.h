#pragma once


namespace winrt
{


   class CLASS_DECL_APEX hasher_algorithm :
      public ::crypto::hasher_algorithm
   {
   public:


      ::winrt::Windows::Security::Cryptography::Core::HashAlgorithmProvider ^ m_pprovider;

      enum_hash m_ehash;


      hasher_algorithm(::winrt::Windows::Security::Cryptography::Core::HashAlgorithmProvider^ pprovider, enum_hash ehash);


      virtual enum_hash ehash() const override;

      virtual void hash(memory & memoryHash, const block & block) override;

      virtual __pointer(::crypto::hasher) create_hasher() override;


   };


} // namespace crypto



