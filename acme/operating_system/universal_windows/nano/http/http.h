//
// Created by camilo on 26/07/2023 23:20 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/http/http.h"


namespace universal_windows
{


   namespace nano
   {


      namespace http
      {


         class CLASS_DECL_ACME http :
            virtual public ::nano::http::http
         {
         public:


            http();
            ~http() override;


            void perform(::nano::http::get * defer_get) override;


         };


      } // namespace http


   } // namespace nano


} // namespace windows





