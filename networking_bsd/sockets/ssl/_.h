// Created by camilo on 2022-08-28 00:04 <3ThomasBorregaardSørensen!!
#pragma once


#define SSL_SESSION_TICKET_KEY_NAME_LEN 16
#define SSL_SESSION_TICKET_AES_KEY_LEN  16
#define SSL_SESSION_TICKET_HMAC_KEY_LEN 16
#define SSL_SESSION_TICKET_KEY_SIZE     48


namespace sockets_bsd
{

   class SSLInitializer;

   class ssl_context;
   class ssl_client_context_map;


} // namespace sockets




