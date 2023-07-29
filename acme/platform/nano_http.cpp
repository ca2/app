//
//  nano_http.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 22:01
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "nano_http.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/manual_reset_event.h"
#include "acme/primitive/primitive/factory.h"


namespace nano
{


   http::http()
   {
      
      
   }


   http::~http()
   {
      
      
   }


   ::pointer < asynchronous_http_response > http::memory(const ::scoped_string & scopedstrUrl, ::property_set & set, const class ::time & timeTimeout)
   {
      
      auto pasynchronoushttpresponse = __create_new < asynchronous_http_response >();
      
      pasynchronoushttpresponse->m_timeTimeout = timeTimeout;
      
      asynchronous_memory(scopedstrUrl, pasynchronoushttpresponse);
      
      if(!pasynchronoushttpresponse->m_event.wait(1_day))
      {
         
         pasynchronoushttpresponse->m_bTimeout = true;
         
      }
      else
      {
         
         set = pasynchronoushttpresponse->m_data.m_set;
         
      }
      
      return pasynchronoushttpresponse;
      
   }


   void http::asynchronous_memory(const ::scoped_string & scopedstrUrl, ::pointer < asynchronous_http_response > pasynchronoushttpresponse)
   {
   
      throw ::interface_only();
   
   }


} // namespace nano


void operating_system_initialize_nano_http(::factory::factory * pfactory);


bool g_bNanoInitializeHttp = false;


CLASS_DECL_ACME void initialize_nano_http()
{

   if(g_bNanoInitializeHttp)
   {

      return;

   }

   operating_system_initialize_nano_http(::get_system_factory());

   g_bNanoInitializeHttp = true;

}

