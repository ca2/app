//
//  domain_consumer.h
//  aura
//
//  Created by camilo on 2026-09-24 04:50 <3ThomasBorregaardSørense!! Mummi!! bilbo!!
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


#include "acme/graphics/draw2d/domain_consumer.h"


namespace draw2d
{

   
   class CLASS_DECL_AURA domain_consumer :
      virtual public ::acme::draw2d::domain_consumer
   {
   public:
      
      
      //::pointer < ::draw2d::domain >      m_pdraw2ddomain;
      
      
      domain_consumer();
      ~domain_consumer() override;
      
      
//      virtual void set_draw2d_domain(::draw2d::domain * pdraw2domain).
      
      
      virtual ::draw2d::domain * draw2d_domain();
      
      
   };


} // namespace draw2d




