//
// Created by camilo on 26/07/2023 23:20 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acid/nano/http/http.h"


namespace apple
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
            
            
            static void s_http_response(long lHttpStatus, const void * data, long size, void * userdata);
            

            void async(::nano::http::get * pget) override;
            
            
         };


      } // namespace http


   } // namespace nano

} // namespace apple





