//
//  nano_http_response.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 23:05
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "get.h"
#include "acme/nano/http/http.h"
#include "acme/nano/nano.h"


namespace nano
{

   namespace http
   {
   
   
      void get::set_out_header(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrPayload)
      {
         
         ::string strKey(scopedstrKey);
         
         strKey.make_lower();
      
         payload("out_header")[strKey] = scopedstrPayload;
         
      }
   
   
      bool get::only_headers() const
   {
    
      if(!payload("in_header").has_property("only_headers"))
      {
       
         return false;
         
         
         
      }
      
      return payload("only_headers").as_bool();
      
   }

   
      void get::set_response(long http_status, const void * data, long size)
      {
         
         get_memory_response()->assign(data, size);
         
         payload("http_status_code") = (huge_integer) http_status;
         
         //passynchronoushttpdata->m_function(passynchronoushttpdata);
         
      }


      get * get::this_transport_payload()
      {

         return this;

      }


      void get::run()
      {

         nano()->http()->perform(this);

      }


      // void get::on_http_get_finished()
      // {
      //
      //    m_functionOnHttpGetFinished(this);
      //
      // }
      void get::want_memory_response(memory_base * pmemory)
      {

         if (::is_set(pmemory))
         {

            payload("get_memory") = pmemory;

         }
         else
         {

            payload("get_memory") = create_memory();

         }

      }


      void get::want_string_response()
      {

         want_memory_response();

      }


      memory_pointer get::get_memory_response()
      {

         return payload("get_memory").cast < memory>();

      }


      string get::get_string_response()
      {

         auto pmemory = get_memory_response();

         if (::is_null(pmemory))
         {

            return "";

         }

         string str;

         str = pmemory->get_string();

         return str;

      }


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
