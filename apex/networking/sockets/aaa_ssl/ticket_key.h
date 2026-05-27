#pragma once





struct ssl_ticket_key
{
   ::u8   key_name[SSL_SESSION_TICKET_KEY_NAME_LEN];
   ::u8   hmac_key[SSL_SESSION_TICKET_HMAC_KEY_LEN];
   ::u8   aes_key[SSL_SESSION_TICKET_AES_KEY_LEN];
};
