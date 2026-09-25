//
//  frame.h
//  aura
//
//  Created by camilo on 2026-09-24 00:24 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA frame :
      virtual public ::particle
   {
   public:
   
      
      ::pointer < ::draw2d::domain >               m_pdraw2ddomain;
      ::pointer < ::user::interaction >            m_puserinteractionAffinity;
      ::pointer < ::draw2d::window_attachment >    m_pdraw2dwindowattachemnt;
      
      
      frame();
      ~frame() override;
      
      
      virtual void initialize_draw2d_frame(::draw2d::domain * pdraw2ddomain);
      
      
      virtual ::draw2d::domain * draw2d_domain();


      virtual ::draw2d::window_attachment* window_attachment();
      

   };



} // namespace draw2d



