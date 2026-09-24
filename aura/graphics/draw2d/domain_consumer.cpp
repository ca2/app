//
//  domain_consumer.cpp
//  aura
//
//  Created by camilo on 2026-09-24 04:55 <3ThomasBorregaardSørense!! Mummi!! bilbo!!
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#include "platform.h"
#include "domain.h"
#include "domain_consumer.h"


namespace draw2d
{


   domain_consumer::domain_consumer()
   {
      
      
   }


   domain_consumer::~domain_consumer()
   {
   
   
   }


//   void domain_consumer::set_draw2d_domain(::draw2d::domain * pdraw2domain)
//   {
//
//      m_pdraw2ddomain = pdraw2domain;
//
//   }


   ::draw2d::domain * domain_consumer::draw2d_domain()
   {
      
      ::cast < ::draw2d::domain > pdraw2ddomain = acme_draw2d_domain();
      
      return pdraw2ddomain;
      
   }
   

} // namespace draw2d
