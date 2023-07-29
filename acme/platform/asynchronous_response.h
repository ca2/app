//
//  nano_http_response.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 23:16
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#include "acme/parallelization/manual_reset_event.h"


template < typename PAYLOAD >
class asynchronous_response :
      virtual public ::particle
{
public:
   
   //::function < void(::pointer < asynchronous_response < PAYLOAD > > ) >               m_function;
   
   class ::time            m_timeTimeout;
   
   ::manual_reset_event    m_event;
   
   PAYLOAD                 m_data;
   
   bool                    m_bTimeout;

};


