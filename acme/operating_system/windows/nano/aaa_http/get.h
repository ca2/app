//
// From http.cpp by camilo on 20/08/2023 02:26 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "request.h"


namespace windows
{



   namespace nano
   {


      namespace http
      {


         class get :
            public request
         {
         public:


            get(connect& connect, const ::scoped_string& scopedstrObject);
            ~get() override;


         };


      } // namespace http


   }// namespace nano


} // namespace windows