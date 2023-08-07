//
//  nano_http_response.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 23:35
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#include "asynchronous_response.h"


namespace nano
{


   class CLASS_DECL_ACME http_response
   {
   public:
      
      
      ::property_set  &       m_set;
      
      memory          &       m_memory;

      http_response(::property_set & set, ::memory & memory) :
         m_set(set), m_memory(memory)
      {

      }
               
   
   };


   using asynchronous_http_response = ::asynchronous_response < http_response >;


} // namespace nano


