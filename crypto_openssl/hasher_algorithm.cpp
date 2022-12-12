#include "framework.h"
#include "hasher_algorithm.h"
#include "hasher.h"
////#include "acme/exception/exception.h"
#include "acme/primitive/primitive/memory.h"


namespace crypto_openssl
{


   const EVP_MD* __evp_md(enum_hash ehash);


   hasher_algorithm::hasher_algorithm() :
      m_ehash(e_hash_none),
      m_pmd(nullptr)
   {

   }


   hasher_algorithm::~hasher_algorithm()
   {


   }


   void hasher_algorithm::initialize_hasher_algorithm(enum_hash ehash)
   {

      m_ehash = ehash;

      m_pmd = __evp_md(ehash);

      if (!::is_set(m_pmd))
      {
       
         throw ::exception(error_resource);

      }

   }


   void hasher_algorithm::hash(memory& memoryHash, const block& block)
   {

#if OPENSSL_VERSION_NUMBER >= 0x30000000

      unsigned int digest_size = EVP_MD_get_size(m_pmd);

#else

      unsigned int digest_size = EVP_MD_size(m_pmd);

#endif

      memoryHash.set_size(digest_size);

      auto mdctx = EVP_MD_CTX_new();

#if OPENSSL_VERSION_NUMBER >= 0x30000000

      EVP_DigestInit_ex2(mdctx, m_pmd, NULL);

#else

      EVP_DigestInit_ex(mdctx, m_pmd, nullptr);

#endif


      EVP_DigestUpdate(mdctx, block.data(), block.size());

      EVP_DigestFinal_ex(mdctx, memoryHash.data(), &digest_size);

      EVP_MD_CTX_free(mdctx);

      memoryHash.set_size(digest_size);

      //return ::success;

   }


   //::crypto::hasher_algorithm* __create_hasher_algorithm(enum_hash ehash)
   //{

   //   switch (ehash)
   //   {
   //   case e_hash_md5:
   //      return memory_new ::cryptopenssl::hasher_algorithm(ehash, EVP_md5());
   //   case e_hash_sha1:
   //      return memory_new ::openssl::hasher_algorithm(ehash, EVP_sha1());
   //   case e_hash_sha256:
   //      return memory_new ::openssl::hasher_algorithm(ehash, EVP_sha256());
   //   default:
   //      return nullptr;
   //   }

   //}


   ::pointer<::crypto::hasher>hasher_algorithm::create_hasher()
   {

      return __new(::crypto_openssl::hasher(this));

   }


   const EVP_MD* __evp_md(enum_hash ehash)
   {

      switch (ehash)
      {
      case e_hash_md5:
         return EVP_md5();
      case e_hash_sha1:
         return EVP_sha1();
      case e_hash_sha256:
         return EVP_sha256();
      case e_hash_nessie:
         return EVP_whirlpool();
      case e_hash_none:
         break;
      }
      return nullptr;

   }


} // namespace crypto_openssl



