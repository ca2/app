#include "framework.h"
//#include "_openssl.h"


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


   ::e_status hasher_algorithm::initialize_hasher_algorithm(enum_hash ehash)
   {

      m_ehash = ehash;

      m_pmd = __evp_md(ehash);

      return ::is_set(m_pmd) ? ::success : ::error_failed;

   }


   ::e_status hasher_algorithm::hash(memory& memoryHash, const block& block)
   {

      unsigned int digest_size = EVP_MD_get_size(m_pmd);

      memoryHash.set_size(digest_size);

      auto mdctx = EVP_MD_CTX_new();

      EVP_DigestInit_ex2(mdctx, m_pmd, NULL);

      EVP_DigestUpdate(mdctx, block.get_data(), block.get_size());

      EVP_DigestFinal_ex(mdctx, memoryHash.get_data(), &digest_size);

      EVP_MD_CTX_free(mdctx);

      memoryHash.set_size(digest_size);

      return ::success;

   }


   //::crypto::hasher_algorithm* __create_hasher_algorithm(enum_hash ehash)
   //{

   //   switch (ehash)
   //   {
   //   case e_hash_md5:
   //      return new ::cryptopenssl::hasher_algorithm(ehash, EVP_md5());
   //   case e_hash_sha1:
   //      return new ::openssl::hasher_algorithm(ehash, EVP_sha1());
   //   case e_hash_sha256:
   //      return new ::openssl::hasher_algorithm(ehash, EVP_sha256());
   //   default:
   //      return nullptr;
   //   }

   //}


   __transport(::crypto::hasher) hasher_algorithm::create_hasher()
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
      }
      return nullptr;

   }


} // namespace crypto_openssl



