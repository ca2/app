#include "framework.h"

namespace sockets
{

   void sip_client::invite(const char * pszTo, const char * pszFrom)
   {
      __UNREFERENCED_PARAMETER(pszTo);
      __UNREFERENCED_PARAMETER(pszFrom);
      /*m_psocket = new
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
