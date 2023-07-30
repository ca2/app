//
//  nano_http.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 22:01
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#include "department.h"
#include "nano_http_response.h"


namespace nano
{


   class http_response;


   class CLASS_DECL_ACME http :
      virtual public ::acme::department
   {
   public:
      
      
      http();
      ~http() override;
      
      
      virtual void memory(const ::scoped_string & scopedstrUrl, http_response & httpresponse, const class ::time & timeTimeout = 5_min);
      
      virtual void asynchronous_memory(const ::scoped_string & scopedstrUrl, ::pointer < asynchronous_http_response > pasynchronoushttpresponse);

      
   };


} // namespace nano



