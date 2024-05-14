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
         virtual public ::transport_payload < get >
      {
      public:
         
         
         ::string                      m_strUrl;
         
         ::property_set                m_setIn;
         
         ::property_set                m_setOut;
         
         memory                        m_memory;
         
         transfer_progress_function    m_transferprogressfunction;

         
         
         void set_response(long http_status, const void * data, long size);

         
      };
   
   
   } //namespace http


} // namespace nano


