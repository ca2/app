//
//  nano_http.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 22:01
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#include "acme/platform/department.h"
#include "get.h"


namespace nano
{

   
   namespace http
   {
   
   
      class CLASS_DECL_ACME http :
            virtual public ::acme::department
      {
      public:
         
         
         http();
         ~http() override;
         
         
         inline static const char * represented_component_name()
         {
            
            return "nano_http";
            
         }
         

         virtual void sync(::nano::http::get * pget);
         
         
         virtual void async(::nano::http::get * pget);


         // Follow redirects and find final resource.
         virtual ::url::url get_effective_url(const ::url::url & url);

         virtual bool check_url_ok(const ::url::url & url);

         virtual ::string get(const ::url::url & url);

         virtual void download(const ::file::path & path, const ::url::url & url);


      };
      
   
   } // namespace http


} // namespace nano



