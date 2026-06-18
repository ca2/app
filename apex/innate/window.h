//
//  window.h
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 04/04/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


namespace innate
{


   class CLASS_DECL_APEX window :
      public ::particle
   {
   public:
      
      ::pointer < ::innate_ui::window > m_pinnateuiwindow;
      
      window();
      ~window() override;
      
      
      
   };


} // namespace public

