//
// From http.cpp by camilo on 20/08/2023 02:24 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "get.h"


namespace windows
{


   namespace nano
   {


      namespace http
      {


         get::get(connect& connect, const ::scoped_string& scopedstrObject) :
            request(connect, "GET", scopedstrObject)
         {

         }


         get::~get()
         {


         }


      } // namespace http


   }// namespace nano


} // namespace windows



