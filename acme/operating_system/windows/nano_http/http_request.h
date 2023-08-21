//
// From http.cpp by camilo on 20/08/2023 ~02:10 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "hinternet.h"


namespace windows
{


   class http_request :
      public hinternet
   {
   public:


      http_request(http_connect & connect, const ::scoped_string & scopedstrOperation, const ::scoped_string & scopedstrObject);
      ~http_request() override;

      bool send_request();

      bool get_response(::nano::http_response & httpresponse);


   };


} // namespace windows



