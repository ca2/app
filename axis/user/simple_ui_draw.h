#pragma once


namespace simple_ui
{


   class CLASS_DECL_AXIS draw :
      virtual public ::object
   {
   public:


      draw();
      virtual ~draw();

      virtual void simple_ui_draw_auth_box(const ::rect & rect, ::draw2d::graphics_pointer& pgraphics);
      virtual void simple_ui_draw_frame_window_rect(const ::rect& rect, ::draw2d::graphics_pointer& pgraphics);
      virtual void simple_ui_draw_dark_glass(const ::rect& rect, ::draw2d::graphics_pointer& pgraphics);
      virtual void simple_ui_draw_pestana(const ::rect& rect, ::draw2d::graphics_pointer& pgraphics);
      virtual void simple_ui_draw_fuzzy_color_spread(const ::rect& rect, ::draw2d::graphics_pointer& pgraphics);

      virtual void simple_ui_draw_back_01_old(const ::rect& rect, ::draw2d::graphics_pointer& pgraphics);
      virtual void simple_ui_draw_back_01_new(const ::rect& rect, ::draw2d::graphics_pointer& pgraphics);


   };


} // namespace simple_ui


