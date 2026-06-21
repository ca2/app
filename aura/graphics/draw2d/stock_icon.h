//
//  stock_icon.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 20/06/26 09:18.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


#include "aura/graphics/draw2d/drawing.h"

namespace draw2d
{

   class CLASS_DECL_AURA stock_icon:
      virtual public ::draw2d::drawing
{
public:
   
   ::f64_rectangle m_rectangle;
   enum_stock_icon m_estockicon;
   enum_stock_icon m_estockiconNew;
   ::pointer < ::draw2d::pen > m_ppenBase;
   ::pointer < ::draw2d::pen > m_ppen1;
   f64_point_array m_pointa;
   ::pointer<::draw2d::path> m_ppath;
   
   stock_icon();
   ~stock_icon();
   
   
   void on_draw(::draw2d::graphics * pgraphics, const ::f64_rectangle & rectangle) override;
   
};

} // namespace draw2d
