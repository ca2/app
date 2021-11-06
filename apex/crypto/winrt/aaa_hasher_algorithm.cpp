#include "framework.h"
#include "_winrt.h"


CLASS_DECL_APEX ::crypto::hasher_algorithm * __create_hasher_algorithm(enum_hash ehash)
{

   auto pprovider = ::winrt::hasher::get_os_provider(ehash);

   auto palgorithm = new ::winrt::hasher_algorithm(pprovider, ehash);

   return palgorithm;

}


namespace winrt
{


   hasher_algorithm::hasher_algorithm(::winrt::Windows::Security::Cryptography::Core::HashAlgorithmProvider^ pprovider, enum_hash ehash) :
      m_pprovider(pprovider),
      m_ehash(ehash)
   {

   }


   enum_hash hasher_algorithm::ehash() const
   {

      return m_ehash;

   }


   void hasher_algorithm::hash(class memory& memoryHash, const block & block)
   {

      memoryHash.set_os_buffer(m_pprovider->HashData(block.get_os_buffer()));

   }


   __pointer(::crypto::hasher) hasher_algorithm::create_hasher()
   {

      return __new(hasher(m_pprovider->CreateHash(), ehash()));
      
   }


} // namespace winrt



