//
// From http.cpp by camilo on 20/08/2023 02:26 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "http_request.h"


namespace windows
{


   class http_get :
      public http_request
   {
   public:


      http_get(http_connect & connect, const ::scoped_string & scopedstrObject);
      ~http_get() override;


   };


} // namespace windows