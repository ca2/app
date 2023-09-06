//
// From http.cpp by camilo on 20/08/2023 02:24 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "http_get.h"


namespace windows
{


   http_get::http_get(http_connect & connect, const ::scoped_string & scopedstrObject) :
      http_request(connect, "GET", scopedstrObject)
   {

   }


   http_get::~http_get()
   {


   }


} // namespace windows



