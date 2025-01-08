//
//  nano_http_response.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 23:35
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#include "acme/platform/transport_payload.h"


namespace nano
{

   
   namespace http
   {
   
   
      class CLASS_DECL_ACME get :
         virtual public ::transport_payload < get >,
         virtual public ::property_object
      {
      public:


         ::e_status                    m_estatusRet;

         ::url::url                    m_url;

         //::property_set                m_setIn;

         //::property_set                m_setOut;

         //property_set                     m_setPost;
         //property_set                     m_setHeaders;


         //memory                        m_memory;

         transfer_progress_function    m_transferprogressfunction;
         
         
         get();
         
         ~get() override;

         auto& url() {return m_url; }

         virtual void set_out_header(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrPayload);
         
         virtual void set_response(long http_status, const void * data, long size);
         virtual void append_response(const void * data, long size);
         virtual void set_status(long http_status);

         virtual bool only_headers() const;

         virtual get * this_transport_payload() override;

         virtual void run() override;
         void want_memory_response(memory_base * pusermessage = nullptr);
         void want_string_response();

         memory_pointer get_memory_response();
         string get_string_response();

      };
   
   
   } //namespace http


} // namespace nano


