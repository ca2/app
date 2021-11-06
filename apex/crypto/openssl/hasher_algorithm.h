#pragma once


namespace openssl
{


   template < typename CTX, enum_hash m_ehash >
   class hasher_algorithm :
      public ::crypto::hasher_algorithm
   {
   public:


      //int SHA1_Init(SHA_CTX* c);
      //int SHA1_Update(SHA_CTX* c, const void* data, size_t len);
      //int SHA1_Final(unsigned char* md, SHA_CTX* c);
      //unsigned char* SHA1(const unsigned char* d, size_t n, unsigned char* md);
      //void SHA1_Transform(SHA_CTX* c, const unsigned char* data);


      typedef int __HASH_INIT(CTX* pctx);
      typedef int __HASH_UPDATE(CTX* pctx, const void* data, size_t len);
      typedef int __HASH_FINAL(unsigned char* md, CTX* pctx);
      typedef unsigned char* __HASH_HASH(const unsigned char* d, size_t n, unsigned char* md);


      using HASH_INIT = __HASH_INIT*;
      using HASH_UPDATE = __HASH_UPDATE*;
      using HASH_FINAL = __HASH_FINAL*;
      using HASH_HASH = __HASH_HASH*;


      HASH_INIT            m_pinit;
      HASH_UPDATE          m_pupdate;
      HASH_FINAL           m_pfinal;
      HASH_HASH            m_phash;


      hasher_algorithm(HASH_INIT pinit, HASH_UPDATE pupdate, HASH_FINAL pfinal, HASH_HASH phash) :
         m_pinit(pinit),
         m_pupdate(pupdate),
         m_pfinal(pfinal),
         m_phash(phash)
      {

      }


      virtual enum_hash ehash() const override
      {

         return m_ehash;

      }


      virtual void hash(memory & memoryHash, const block & block) override
      {

         memoryHash.set_size(hash_digest_size(ehash()));

         m_phash((const unsigned char *) block.get_data(), block.get_size(), memoryHash.get_data());

      }


      virtual __pointer(::crypto::hasher) create_hasher() override;


   };


} // namespace openssl



