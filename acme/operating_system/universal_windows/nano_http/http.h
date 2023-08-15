//
// Created by camilo on 26/07/2023 23:20 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/platform/nano_http.h"


namespace windows
{


   class CLASS_DECL_ACME nano_http :
      virtual public ::nano::http
   {
   public:
      
      
      nano_http();
      ~nano_http() override;
      
      //static void s_http_response(long http_status, const void * data, long size, void * userdata);
      
      //void asynchronous_memory(const ::scoped_string & scopedstrUrl, ::pointer < ::nano::asynchronous_http_response > pasynchronoushttpresponse) override;


      void memory(const ::scoped_string & scopedstrUrl, ::nano::http_response & httpresponse, const class ::time & timeTimeout = 5_min) override;
      
      

   
   };


} // namespace windows





