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
class particle_payload :
      virtual public ::particle
{
public:
   
   //::function < void(::pointer < asynchronous_response < PAYLOAD > > ) >               m_function;

   asynchronous_response(RESPONSE * presponse) :
      m_presponse(presponse)
   {

   }
   
   class ::time            m_timeTimeout;
   
   ::manual_reset_event    m_event;
   
   ::pointer < RESPONSE >  m_presponse;
   
   bool                    m_bTimeout;

};


