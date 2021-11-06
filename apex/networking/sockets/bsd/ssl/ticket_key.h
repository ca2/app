#pragma once




#define SSL_SESSION_TICKET_KEY_NAME_LEN 16
#define SSL_SESSION_TICKET_AES_KEY_LEN  16
#define SSL_SESSION_TICKET_HMAC_KEY_LEN 16
#define SSL_SESSION_TICKET_KEY_SIZE     48


struct ssl_ticket_key
{
   unsigned char   key_name[SSL_SESSION_TICKET_KEY_NAME_LEN];
   unsigned char   hmac_key[SSL_SESSION_TICKET_HMAC_KEY_LEN];
   unsigned char   aes_key[SSL_SESSION_TICKET_AES_KEY_LEN];
};
