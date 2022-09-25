#include "framework.h"
#include "_openssl.h"


namespace openssl
{


   void hasher_algorithm::hash(memory& memoryHash, const block& block)
   {

      unsigned int digest_size = EVP_MD_get_size(m_pmd);

      memoryHash.set_size(digest_size);

      auto mdctx = EVP_MD_CTX_new();
      EVP_DigestInit_ex2(mdctx, m_pmd, NULL);
      EVP_DigestUpdate(mdctx, block.get_data(), block.get_size());
      EVP_DigestFinal_ex(mdctx, memoryHash.get_data(), &digest_size);
      EVP_MD_CTX_free(mdctx);

      memoryHash.set_size(digest_size);

   }


   ::crypto::hasher_algorithm* __create_hasher_algorithm(enum_hash ehash)
   {

      switch (ehash)
      {
      case e_hash_md5:
         return memory_new ::openssl::hasher_algorithm(ehash, EVP_md5());
      case e_hash_sha1:
         return memory_new ::openssl::hasher_algorithm(ehash, EVP_sha1());
      case e_hash_sha256:
         return memory_new ::openssl::hasher_algorithm(ehash, EVP_sha256());
      default:
         return nullptr;
      }

   }


   __pointer(::crypto::hasher) hasher_algorithm::create_hasher()
   {

      return __new(::openssl::hasher(this));

   }


} // namespace openssl



