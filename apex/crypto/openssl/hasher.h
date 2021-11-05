#pragma once


namespace openssl
{


   template < typename CTX, enum_hash m_ehash >
   class hasher :
      public ::crypto::hasher
   {
   public:


      CTX                                    m_ctx;
      hasher_algorithm < CTX, m_ehash > *    m_phasheralgorithm;


      hasher(hasher_algorithm < CTX, m_ehash >* palgorithm)
      {

         m_phasheralgorithm = palgorithm;

         m_phasheralgorithm->m_pinit(&m_ctx);

      }


      virtual enum_hash ehash() const override
      {

         return m_ehash;

      }

      virtual void update(const block & block) override
      {

         m_phasheralgorithm->m_pupdate(&m_ctx, block.get_data(), block.get_size());

      }


      virtual memory get_hash_and_reset() override
      {

         memory mem;
         
         mem.set_size(hash_digest_size(ehash()));

         m_phasheralgorithm->m_pfinal(mem.get_data(), &m_ctx);

         m_phasheralgorithm->m_pinit(&m_ctx);

         return mem;

      }


   };


} // namespace winrt



