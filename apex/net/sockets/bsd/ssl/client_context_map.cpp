#include "framework.h"
#include "apex/net/sockets/_.h"


namespace sockets
{


   ssl_client_context_map::ssl_client_context_map()
   {

      defer_create_mutex();

   }


   ssl_client_context_map::~ssl_client_context_map()
   {

   }


   __pointer(ssl_client_context) ssl_client_context_map::get_context(string strContext, const SSL_METHOD * pmethod)
   {

      __pointer(ssl_client_context) pcontext = m_map[strContext][pmethod];

      if (pcontext.is_null())
      {

         pcontext = __new(ssl_client_context(get_context_application(), pmethod));

      }

      return pcontext;

   }


} // namespace sockets







