#include "framework.h"
#include "crypto_initializer.h"


namespace crypto
{


   //crypto::~crypto()
   //{


   //}


   void crypto::defer_initialize()
   {

      __defer_compose_new(m_pinitializer);

   }


   __pointer(hasher) crypto::create_hasher(enum_hash ehash)
   {

      defer_initialize();

      auto palgorithm = __hasher_algorithm(ehash);

      return palgorithm->create_hasher();

   }





} // namespace crypto



