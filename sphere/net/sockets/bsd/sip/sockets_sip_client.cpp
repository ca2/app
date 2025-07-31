#include "framework.h" // #include "axis/net/sockets/bsd/sockets.h"
#include "aura/net/net_sockets.h"


namespace sockets
{


   void sip_client::invite(const ::scoped_string & scopedstrTo, const ::scoped_string & scopedstrFrom)
   {

      __UNREFERENCED_PARAMETER(scopedstrTo);
      __UNREFERENCED_PARAMETER(scopedstrFrom);
      /*m_psocket = aaa_memory_new
      m_psocket->m_strTo = pszTo;
      m_psocket->m_strFrom = pszFrom;
      socket_handler handler(this);
      handler.add(&socket);
      while(handler.get_count() > 0)
      {
         handler.Select(120, 0);
      }*/

   }


} // namespace sockets








