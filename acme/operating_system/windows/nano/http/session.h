//
// From http.cpp by camilo on 20/08/2023 02:28 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "hinternet.h"


namespace windows
{



   namespace nano
   {


      namespace http
      {


         class session :
            public hinternet
         {
         public:


            session(const ::scoped_string& scopedstrAgent = "nano_http");
            ~session() override;


         };



      } // namespace http


   }// namespace nano


} // namespace windows



