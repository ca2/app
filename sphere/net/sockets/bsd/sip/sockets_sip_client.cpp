#include "framework.h" // #include "axis/net/sockets/bsd/sockets.h"
#include "aura/net/net_sockets.h"


namespace sockets
{


   void sip_client::invite(const ::string & pszTo, const ::string & pszFrom)
   {

      UNREFERENCED_PARAMETER(pszTo);
      UNREFERENCED_PARAMETER(pszFrom);
      /*m_psocket = memory_new
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








