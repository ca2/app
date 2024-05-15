//
// From http.cpp by camilo on 20/08/2023 02:24 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "connect.h"
#include "session.h"


namespace windows
{


   namespace nano
   {


      namespace http
      {


         connect::connect(session& session, const ::scoped_string& scopedstrHost)
         {

            wstring wstrHost(scopedstrHost);

            m_hinternet = WinHttpConnect(session.m_hinternet, wstrHost, INTERNET_DEFAULT_HTTP_PORT, 0);

         }


         connect::~connect()
         {

         }


      } // namespace http


   }// namespace nano


} // namespace windows



