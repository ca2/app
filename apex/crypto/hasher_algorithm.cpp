#include "framework.h"


::crypto::hasher_algorithm* __hasher_algorithm(enum_hash ehash)
{

   switch (ehash)
   {
   case e_hash_md5:
   {

      static auto s_phasher = __release_on_end(__create_hasher_algorithm(ehash));

      return s_phasher;

   }
   case e_hash_sha1:
   {

      static auto s_phasher = __release_on_end(__create_hasher_algorithm(ehash));

      return s_phasher;

   }
   case e_hash_sha256:
   {

      static auto s_phasher = __release_on_end(__create_hasher_algorithm(ehash));

      return s_phasher;

   }
   default:

      return nullptr;

   };


} // namespace openssl



