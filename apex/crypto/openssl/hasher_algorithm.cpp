#include "framework.h"
#include "_openssl.h"


::crypto::hasher_algorithm* __create_hasher_algorithm(enum_hash ehash)
{

   switch (ehash)
   {
   case e_hash_md5:
      return new ::openssl::hasher_algorithm < MD5_CTX, e_hash_md5 >(&MD5_Init, &MD5_Update, &MD5_Final, &MD5);
   case e_hash_sha1:
      return new ::openssl::hasher_algorithm < SHA_CTX, e_hash_sha1 >(&SHA1_Init, &SHA1_Update, &SHA1_Final, &SHA1);
   case e_hash_sha256:
      return new ::openssl::hasher_algorithm < SHA256_CTX, e_hash_sha256 >(&SHA256_Init, &SHA256_Update, &SHA256_Final, &SHA256);
   default:
      return nullptr;
   }

}






