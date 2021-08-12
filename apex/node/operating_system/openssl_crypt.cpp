#include "framework.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/node/operating_system/ansi/_pthread.h"


#endif


#include <openssl/ssl.h>
#include <openssl/md5.h>
#include <openssl/err.h>


i32 openssl_crypto_encrypt(memory & storageEncrypt, const memory & storageDecrypt, memory & key)
{
   i32 plainlen = (i32)storageDecrypt.get_size();
   i32 cipherlen, tmplen;
   unsigned char iv[8] = { 1,2,3,4,5,6,7,8 };
   EVP_CIPHER_CTX * pctx = EVP_CIPHER_CTX_new();
   EVP_EncryptInit(pctx, EVP_bf_cbc(), (unsigned char *)key.get_data(), iv);
   cipherlen = (i32)(storageDecrypt.get_size() + 16 - 1); //; 16 = key size_i32
   storageEncrypt.set_size(cipherlen);
   if (!EVP_EncryptUpdate(pctx, (unsigned char *)storageEncrypt.get_data(), &cipherlen, (const unsigned char *)storageDecrypt.get_data(), plainlen))
   {
      return -1;
   }
   if (!EVP_EncryptFinal(pctx, ((unsigned char *)storageEncrypt.get_data()) + cipherlen, &tmplen))
   {
      return -1;
   }
   cipherlen += tmplen;
   storageEncrypt.set_size(cipherlen);
   EVP_CIPHER_CTX_free(pctx);
   return cipherlen;
}

i32 openssl_crypto_decrypt(memory & storageDecrypt, const memory & storageEncrypt, memory & key)
{
   i32 cipherlen = (i32)storageEncrypt.get_size();
   i32 plainlen, tmplen;
   unsigned char iv[8] = { 1,2,3,4,5,6,7,8 };
   EVP_CIPHER_CTX * pctx = EVP_CIPHER_CTX_new();
   EVP_DecryptInit(pctx, EVP_bf_cbc(), (const unsigned char *)key.get_data(), iv);
   plainlen = (i32)storageEncrypt.get_size();
   storageDecrypt.set_size(plainlen);
   if (!EVP_DecryptUpdate(pctx, (unsigned char *)storageDecrypt.get_data(), &plainlen, (const unsigned char *)storageEncrypt.get_data(), cipherlen))
   {
      return -1;
   }
   if (!EVP_DecryptFinal(pctx, ((unsigned char *)storageDecrypt.get_data()) + plainlen, &tmplen))
   {
      storageDecrypt.set_size(plainlen);
      EVP_CIPHER_CTX_free(pctx);
      return plainlen;
   }
   plainlen += tmplen;
   storageDecrypt.set_size(plainlen);
   EVP_CIPHER_CTX_free(pctx);
   return plainlen;
}

