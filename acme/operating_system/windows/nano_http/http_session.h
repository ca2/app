//
// From http.cpp by camilo on 20/08/2023 02:28 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "hinternet.h"


namespace windows
{


   class http_session :
      public hinternet
   {
   public:


      http_session(const ::scoped_string & scopedstrAgent = "nano_http");
      ~http_session() override;


   };


} // namespace windows



