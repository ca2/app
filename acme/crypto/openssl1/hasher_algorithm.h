#pragma once


namespace openssl
{


   //template < typename CTX, enum_hash m_ehash >
   class hasher_algorithm :
      public ::crypto::hasher_algorithm
   {
   public:


      //::i32 SHA1_Init(SHA_CTX* c);
      //::i32 SHA1_Update(SHA_CTX* c, const void* data, size_t len);
      //::i32 SHA1_Final(::u8* md, SHA_CTX* c);
      //::u8* SHA1(const ::u8* d, size_t n, ::u8* md);
      //void SHA1_Transform(SHA_CTX* c, const ::u8* data);


      //typedef ::i32 __HASH_INIT(EVP_MD_CTX* pctx);
      //typedef ::i32 __HASH_UPDATE(CTX* pctx, const void* data, size_t len);
      //typedef ::i32 __HASH_FINAL(::u8* md, CTX* pctx);
      //typedef ::u8* __HASH_HASH(const ::u8* d, size_t n, ::u8* md);


      //using HASH_INIT = __HASH_INIT*;
      //using HASH_UPDATE = __HASH_UPDATE*;
      //using HASH_FINAL = __HASH_FINAL*;
      //using HASH_HASH = __HASH_HASH*;


      //HASH_INIT            m_pinit;
      //HASH_UPDATE          m_pupdate;
      //HASH_FINAL           m_pfinal;
      //HASH_HASH            m_phash;
      const enum_hash         m_ehash;
      const EVP_MD *          m_pmd;


      hasher_algorithm(enum_hash ehash, const EVP_MD * pmd) :
         m_ehash(ehash),
         m_pmd(pmd)
      {

      }


      virtual enum_hash ehash() const override
      {

         return m_ehash;

      }


      virtual void hash(memory& memoryHash, const block& block) override;


      virtual ::pointer<::crypto::hasher>create_hasher() override;


   };


} // namespace openssl



