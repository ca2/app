#include "framework.h"


namespace crypto
{


   //crypto::~crypto()
   //{


   //}


   __pointer(hasher) crypto::create_hasher(enum_hash ehash)
   {

      auto palgorithm = __hasher_algorithm(ehash);

      return palgorithm->create_hasher();

   }





} // namespace crypto



