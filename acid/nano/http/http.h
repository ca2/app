//
//  nano_http.hpp
//  acid
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 22:01
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#include "acid/platform/department.h"
#include "get.h"


namespace nano
{

   
   namespace http
   {
   
   
      class CLASS_DECL_ACID http :
            virtual public ::acid::department
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
         virtual ::string get_effective_url(const ::scoped_string & scopedstr);
         
         
      };
      
   
   } // namespace http


} // namespace nano



