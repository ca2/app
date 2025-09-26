//
// From http.cpp by camilo on 20/08/2023 ~02:10 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "hinternet.h"


namespace windows
{



   namespace nano
   {


      namespace http
      {


         class request :
            public hinternet
         {
         public:

            connect& m_connect;

            request(connect& connect, const ::scoped_string& scopedstrOperation, const ::scoped_string& scopedstrObject);
            ~request() override;

            bool send_request();

            bool get_response(::nano::http::get * defer_get);


         };



      } // namespace http


   }// namespace nano


} // namespace windows



