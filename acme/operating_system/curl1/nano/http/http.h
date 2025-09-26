//
// Created by camilo on 26/07/2023 23:20 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/http/http.h"


namespace curl
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

            //static void s_http_response(long http_status, const void * data, long size, void * userdata);

            //void asynchronous_memory(const ::scoped_string & scopedstrUrl, ::pointer < ::nano::httasynchronous_http_response > pasynchronoushttpresponse) override;

            void async(::nano::http::get * defer_get) override;


         };


      } // namespace http


   } // namespace nano


} // namespace apple





