#pragma once


#include <openssl/evp.h>


struct ssl_ticket_key
{
   static constexpr ::i32 hmac_key_len = SSL_SESSION_TICKET_HMAC_KEY_LEN;
   static constexpr ::i32 aes_key_len = SSL_SESSION_TICKET_AES_KEY_LEN;
   static constexpr ::i32 key_name_len = SSL_SESSION_TICKET_KEY_NAME_LEN;
   ::u8   key_name[key_name_len];
   ::u8   hmac_key[hmac_key_len];
   ::u8   aes_key[aes_key_len];
   static inline const EVP_CIPHER* cipher = EVP_aes_128_cbc();
   static inline const EVP_MD* hmac = EVP_sha256();
};
