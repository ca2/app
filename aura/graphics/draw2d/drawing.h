//
//  drawing.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 20/06/26 09:14.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


namespace draw2d
{

   class CLASS_DECL_AURA drawing:
   virtual public ::particle
   {
   public:
      
      
      drawing();
      ~drawing();
      
      
      virtual void on_draw(::draw2d::graphics * pgraphics, const ::f64_rectangle & rectangle);
      
   };


} // namespace draw2d
