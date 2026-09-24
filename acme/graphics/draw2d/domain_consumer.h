//
//  domain_consumer.h
//  aura
//
//  Created by camilo on 2026-09-24 05:57 <3ThomasBorregaardSørense!! Mummi!! bilbo!!
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


namespace acme
{


   namespace draw2d
   {


      class CLASS_DECL_ACME domain_consumer :
         virtual public ::particle
      {
      public:
         
         
         ::pointer < ::acme::draw2d::domain >      m_pacmedraw2ddomain;
         
         
         domain_consumer();
         ~domain_consumer() override;
         
         
         virtual void set_draw2d_domain(::acme::draw2d::domain * pacmedraw2domain);
         
         
         virtual ::acme::draw2d::domain * acme_draw2d_domain();
         
         
      };


   } // namespace draw2d


} // namespace acme



