//
// From http.cpp by camilo on 20/08/2023 02:24 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "http_connect.h"
#include "http_session.h"


namespace windows
{


   http_connect::http_connect(http_session & session, const ::scoped_string & scopedstrHost)
   {

      wstring wstrHost(scopedstrHost);

      m_hinternet = WinHttpConnect(session.m_hinternet, wstrHost, INTERNET_DEFAULT_HTTP_PORT, 0);

   }


   http_connect::~http_connect()
   {

   }


} // namespace windows



