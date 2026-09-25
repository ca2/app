//
//  frame.cpp
//  aura
//
//  Created by camilo on 2026-09-24 00:25 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#include "platform.h"
#include "domain.h"
#include "frame.h"


namespace draw2d
{

   
   frame::frame()
   {
      
      
   }


   frame::~frame()
   {
      
   }


   void frame::initialize_draw2d_frame(::draw2d::domain * pdraw2ddomain)
   {
      
      m_pdraw2ddomain = pdraw2ddomain;
      
   }


   ::draw2d::domain * frame::draw2d_domain()
   {
      
      return m_pdraw2ddomain;
      
   }


   ::draw2d::window_attachment* frame::window_attachment()
   {

      return m_pdraw2dwindowattachemnt;

   }


} // namespace draw2d



