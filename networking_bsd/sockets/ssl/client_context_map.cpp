#include "framework.h"
#include "client_context_map.h"
#include "client_context.h"


namespace sockets_bsd
{


   ssl_client_context_map::ssl_client_context_map()
   {

      defer_create_synchronization();

   }


   ssl_client_context_map::~ssl_client_context_map()
   {

   }


   ::pointer<ssl_client_context>ssl_client_context_map::get_context(string strContext, const SSL_METHOD * pmethod)
   {

      ::pointer<ssl_client_context>pcontext = m_map[strContext][pmethod];

      if (pcontext.is_null())
      {

         pcontext = __new(ssl_client_context(pmethod));

      }

      return pcontext;

   }


} // namespace sockets_bsd



