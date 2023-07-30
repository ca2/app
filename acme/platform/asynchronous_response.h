//
//  nano_http_response.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 23:16
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#include "acme/parallelization/manual_reset_event.h"


template < typename RESPONSE >
class asynchronous_response :
      virtual public ::particle
{
public:
   
   //::function < void(::pointer < asynchronous_response < PAYLOAD > > ) >               m_function;

   asynchronous_response(RESPONSE & response) :
      m_response(response)
   {

   }
   
   class ::time            m_timeTimeout;
   
   ::manual_reset_event    m_event;
   
   RESPONSE &              m_response;
   
   bool                    m_bTimeout;

};


