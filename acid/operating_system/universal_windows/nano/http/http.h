//
// Created by camilo on 26/07/2023 23:20 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acid/nano/http/http.h"


namespace universal_windows
{


   namespace nano
   {


      namespace http
      {


         class CLASS_DECL_ACID http :
            virtual public ::nano::http::http
         {
         public:


            http();
            ~http() override;


            void sync(::nano::http::get * pget) override;


         };


      } // namespace http


   } // namespace nano


} // namespace windows





