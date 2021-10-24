#include "framework.h"
#include "_winrt.h"


//namespace winrt
//{
//
//
//   CLASS_DECL_APEX __pointer(::crypto::hasher) __create_hasher(enum_hash ehash)
//   {
//
//      auto pprovider = ::winrt::hasher::get_os_provider(ehash);
//
//      auto phash = pprovider->CreateHash();
//
//      auto phasher = __new(::winrt::hasher(phash));
//
//      return phasher;
//
//   }
//
//
//} // namespace winrt
//



namespace winrt
{


   hasher::hasher(::winrt::Windows::Security::Cryptography::Core::CryptographicHash^ phash, enum_hash ehash) :
      m_phash(phash), 
      m_ehash(ehash)
   {


   }


   enum_hash hasher::ehash() const
   {

      return m_ehash;

   }


   void hasher::update(const block& block)
   {

      m_phash->Append(block.get_os_buffer());

   }


   memory hasher::get_hash_and_reset()
   {

      memory mem;

      mem.set_os_buffer(m_phash->GetValueAndReset());

      return mem;

   }


   String^ hasher::get_os_provider_name(enum_hash ehash)
   {

      switch (ehash)
      {
      case e_hash_md5:
         return ::winrt::Windows::Security::Cryptography::Core::HashAlgorithmNames::Md5;
      case e_hash_sha1:
         return ::winrt::Windows::Security::Cryptography::Core::HashAlgorithmNames::Sha1;
      case e_hash_sha256:
         return ::winrt::Windows::Security::Cryptography::Core::HashAlgorithmNames::Sha256;
      default:
         return "";

      }

   }


   ::winrt::Windows::Security::Cryptography::Core::HashAlgorithmProvider^ hasher::get_os_provider(enum_hash ehash)
   {

      return ::winrt::Windows::Security::Cryptography::Core::HashAlgorithmProvider::OpenAlgorithm(get_os_provider_name(ehash));

   }


} // namespace crypto


