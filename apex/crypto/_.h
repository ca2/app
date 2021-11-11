#pragma once


enum enum_hash
{

   e_hash_none,
   e_hash_md5,
   e_hash_sha1,
   e_hash_sha256,
   e_hash_nessie,

};


namespace crypto
{

   
   class hasher;
   class hasher_algorithm;


} // namespace crypto


inline constexpr int hash_digest_size(enum_hash ehash) 
{

   switch (ehash)
   {
   case e_hash_md5:
      return 16;
   case e_hash_sha1:
      return 20;
   case e_hash_sha256:
      return 32;
   default:
      return -1;
   }

}


#include "hasher_algorithm.h"
#include "hasher.h"
#include "rsa.h"



