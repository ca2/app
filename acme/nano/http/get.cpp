//
//  nano_http_response.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 23:05
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "get.h"


namespace nano
{

   namespace http
   {
   
   
      void get::set_response(long http_status, const void * data, long size)
      {
         
         m_memory.assign(data, size);
         
         m_setOut["http_status_code"] = http_status;
         
         //passynchronoushttpdata->m_function(passynchronoushttpdata);
         
      }


      get * get::this_transport_payload()
      {

         return this;

      }


      // void get::on_http_get_finished()
      // {
      //
      //    m_functionOnHttpGetFinished(this);
      //
      // }


   }//namespace http


} // namespace nano




void nano_http_get_transfer_progress(void * userdata, long done, long total)
{
   
   auto pget = dynamic_cast <::nano::http::get *>((::subparticle*)userdata);
 
   auto & function = pget->m_transferprogressfunction;

   if(function)
   {
      
      function(
               (double) done / (double) total,
               done,
               total);
      
   }
   
}


void nano_http_get_set_response(void * userdata, long http_status, const void * data, long size)
{
   
   auto pget = dynamic_cast <::nano::http::get *>((::subparticle*)userdata);
 

   pget->set_response(http_status, data, size);
   
}
