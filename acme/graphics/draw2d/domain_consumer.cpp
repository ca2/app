//
//  domain_consumer.cpp
//  aura
//
//  Created by camilo on 2026-09-24 05:10 <3ThomasBorregaardSørense!! Mummi!! bilbo!!
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#include "platform.h"
#include "domain_consumer.h"
#include "domain.h"


namespace acme
{


   namespace draw2d
   {


      domain_consumer::domain_consumer()
      {
         
         
      }


      domain_consumer::~domain_consumer()
      {
         
         
      }


      void domain_consumer::set_draw2d_domain(::acme::draw2d::domain * pacmedraw2domain)
      {
         
         m_pacmedraw2ddomain = pacmedraw2domain;
         
      }


      ::acme::draw2d::domain * domain_consumer::acme_draw2d_domain()
      {
         
         return m_pacmedraw2ddomain;
         
      }


   } // namespace draw2d


} // namespace acme



