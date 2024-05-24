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

            m_wstrHost = scopedstrHost;

            m_hinternet = WinHttpConnect(session.m_hinternet, m_wstrHost, INTERNET_DEFAULT_HTTPS_PORT, 0);

         }


         connect::~connect()
         {

         }


      } // namespace http


   }// namespace nano


} // namespace windows



