#pragma once


#include "acme/primitive/geometry2d/_geometry2d.h"
//#include "acme/primitive/primitive/object.h"


namespace simple_ui
{


   class CLASS_DECL_AXIS draw :
      virtual public ::object
   {
   public:


      draw();
      virtual ~draw();

      virtual void simple_ui_draw_auth_box(const ::rectangle_i32 & rectangle, ::draw2d::graphics_pointer& pgraphics);
      virtual void simple_ui_draw_frame_window_rect(const ::rectangle_i32& rectangle, ::draw2d::graphics_pointer& pgraphics);
      virtual void simple_ui_draw_dark_glass(const ::rectangle_i32& rectangle, ::draw2d::graphics_pointer& pgraphics);
      virtual void simple_ui_draw_pestana(const ::rectangle_i32& rectangle, ::draw2d::graphics_pointer& pgraphics);
      virtual void simple_ui_draw_fuzzy_color_spread(const ::rectangle_i32& rectangle, ::draw2d::graphics_pointer& pgraphics);

      virtual void simple_ui_draw_back_01_old(const ::rectangle_i32& rectangle, ::draw2d::graphics_pointer& pgraphics);
      virtual void simple_ui_draw_back_01_new(const ::rectangle_i32& rectangle, ::draw2d::graphics_pointer& pgraphics);


   };


} // namespace simple_ui


