#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
////#include "acme/prototype/prototype/object.h"


namespace simple_ui
{


   class CLASS_DECL_AXIS draw :
      virtual public ::object
   {
   public:


      draw();
      virtual ~draw();

      virtual void simple_ui_draw_auth_box(const ::int_rectangle & rectangle, ::draw2d::graphics_pointer& pgraphics);
      virtual void simple_ui_draw_frame_window_rect(const ::int_rectangle& rectangle, ::draw2d::graphics_pointer& pgraphics);
      virtual void simple_ui_draw_dark_glass(const ::int_rectangle& rectangle, ::draw2d::graphics_pointer& pgraphics);
      virtual void simple_ui_draw_pestana(const ::int_rectangle& rectangle, ::draw2d::graphics_pointer& pgraphics);
      virtual void simple_ui_draw_fuzzy_color_spread(const ::int_rectangle& rectangle, ::draw2d::graphics_pointer& pgraphics);

      virtual void simple_ui_draw_back_01_old(const ::int_rectangle& rectangle, ::draw2d::graphics_pointer& pgraphics);
      virtual void simple_ui_draw_back_01_new(const ::int_rectangle& rectangle, ::draw2d::graphics_pointer& pgraphics);


   };


} // namespace simple_ui


