#pragma once


#include <openssl/evp.h>


struct ssl_ticket_key
{
   static constexpr int hmac_key_len = SSL_SESSION_TICKET_HMAC_KEY_LEN;
   static constexpr int aes_key_len = SSL_SESSION_TICKET_AES_KEY_LEN;
   static constexpr int key_name_len = SSL_SESSION_TICKET_KEY_NAME_LEN;
   unsigned char   key_name[key_name_len];
   unsigned char   hmac_key[hmac_key_len];
   unsigned char   aes_key[aes_key_len];
   static inline const EVP_CIPHER* cipher = EVP_aes_128_cbc();
   static inline const EVP_MD* hmac = EVP_sha256();
};
