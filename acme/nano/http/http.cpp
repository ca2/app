//
//  nano_http.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 22:01
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "http.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/manual_reset_event.h"
#include "acme/primitive/primitive/factory.h"


namespace nano
{


namespace http
{

http::http()
{
   
   
}


http::~http()
{
   
   
}


   void http::sync(::nano::http::get * pget)
   {
   
      auto pevent = __create_new < ::manual_reset_event >();
      
      pget->m_callbackAsync = [pevent](auto)
      {
      
         pevent->SetEvent();
      
      };
      
      if(!pget->m_transferprogressfunction)
      {
       
         pget->m_transferprogressfunction = pget->m_setIn["transfer_progress_function"];
         
      }
   
      async(pget);
   
      if(!pevent->wait(pget->m_timeSyncTimeout))
      {
         
         throw ::exception(error_timeout);
         
      }
   
   }

   
   void http::async(::nano::http::get * pget)
   {
      
      ::pointer < ::nano::http::get > pgetHold(pget);
      
      if(!pget->m_transferprogressfunction)
      {
       
         pget->m_transferprogressfunction = pget->m_setIn["transfer_progress_function"];
         
      }
   
      fork([this, pgetHold]()
           {
         
               sync(pgetHold);
         
               pgetHold->m_callbackAsync(pgetHold);
         
            });
   
      }


   } // namespace http

} // namespace nano


void operating_system_initialize_nano_http(::factory::factory * pfactory);


bool g_bNanoInitializeHttp = false;


CLASS_DECL_ACME void initialize_nano_http(::factory::factory * pfactory)
{

   if(g_bNanoInitializeHttp)
   {

      return;

   }

   operating_system_initialize_nano_http(pfactory);

   g_bNanoInitializeHttp = true;

}

