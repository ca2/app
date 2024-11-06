#pragma once


#include "frame.h"


namespace experience_core
{


   class CLASS_DECL_APP_EXPERIENCE_CORE frame_008 :
         public frame
   {
   public:

         
      bool     m_bHollow;


      frame_008();
      ~frame_008() override;


      void _on_style_change(::draw2d::graphics_pointer & pgraphics) override;



      void on_draw_frame(::draw2d::graphics_pointer & pgraphics) override;
      void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX);
      void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX, enum_border eside);
      //void GetBorderRectangle(const ::int_rectangle & rectangleX, ::int_rectangle * lprect, enum_border eside);
      void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX);
      void DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX, enum_grip egrip);
      void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);

      //::experience::enum_frame experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;

      //::item_pointer experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;


   };



} // namespace experience_core



