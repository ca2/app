//
// From http.cpp by camilo on 20/08/2023 02:30 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "http_session.h"


namespace windows
{


   http_session::http_session(const ::scoped_string & scopedstrAgent)
   {

      wstring wstrAgent(scopedstrAgent);

      m_hinternet = ::WinHttpOpen(wstrAgent, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

   }

   
   http_session::~http_session()
   {

   }


} // namespace windows





