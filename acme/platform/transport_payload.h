//
//  nano_http_response.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 23:16
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


template < typename TRANSPORT_PAYLOAD >
class transport_payload :
      virtual public ::particle
{
public:
   

   transport_payload()
   {
      
   }
   
   
   ~transport_payload() override
   {
      
   }
   
   
   class ::time                                 m_timeSyncTimeout;
   
   ::function < void(TRANSPORT_PAYLOAD *) >     m_callbackAsync;
//
//
//   
//   class ::time            m_timeTimeout;
   
   //::manual_reset_event    m_event;
   
   //::pointer < RESPONSE >  m_presponse;
   
   bool                    m_bTimeout;

};


