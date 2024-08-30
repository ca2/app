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
   
   
      void get::set_out_header(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrPayload)
      {
         
         ::string strKey(scopedstrKey);
         
         strKey.make_lower();
      
         m_setOut[strKey] = scopedstrPayload;
         
      }
   
   
      bool get::only_headers() const
   {
    
      if(!m_setIn.has_property("only_headers"))
      {
       
         return false;
         
         
         
      }
      
      return m_setIn["only_headers"].as_bool();
      
   }

   
      void get::set_response(long http_status, const void * data, long size)
      {
         
         m_memory.assign(data, size);
         
         m_setOut["http_status_code"] = (::i64) http_status;
         
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


void nano_http_get_set_out_header(void * userdata, const char * pszKey, const char * pszPayload)
{
   
   auto pget = dynamic_cast <::nano::http::get *>((::subparticle*)userdata);
   
   pget->set_out_header(pszKey, pszPayload);

}

bool nano_http_get_only_headers(void * userdata)
{
   
   auto pget = dynamic_cast <::nano::http::get *>((::subparticle*)userdata);
   
   return pget->only_headers();

}



void nano_http_get_set_response(void * userdata, long http_status, const void * data, long size)
{
   
   auto pget = dynamic_cast <::nano::http::get *>((::subparticle*)userdata);
 

   pget->set_response(http_status, data, size);
   
}
