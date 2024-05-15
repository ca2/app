//
// Created by camilo on 20/08/2023 02:22 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "hinternet.h"


namespace windows
{


   namespace nano
   {


      namespace http
      {



         class connect :
            public hinternet
         {
         public:


            connect(session& session, const ::scoped_string& scopedstrHost);
            ~connect() override;

         };


      } // namespace http


   }// namespace nano


} // namespace windows



