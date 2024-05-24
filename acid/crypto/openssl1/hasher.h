#pragma once


namespace openssl
{


   class hasher :
      public ::crypto::hasher
   {
   public:


      enum_hash                              m_ehash;
      EVP_MD_CTX *                           m_pctx;
      hasher_algorithm *                     m_phasheralgorithm;


      hasher(hasher_algorithm* palgorithm);
      ~hasher() override;


      enum_hash ehash() const override;
      
      void update(const block& block) override;
      
      memory get_hash_and_reset() override;


   };


} // namespace winrt



