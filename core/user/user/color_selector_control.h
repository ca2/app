// From userex/color_impact 2023-10-09 01:47 <3ThomasBorregaardSorensen!!
#pragma once


#include "axis/graphics/graphics/color_wheel.h"
#include "core/graphics/color_selector.h"
#include "aura/user/user/plain_edit.h"


namespace user
{


   class CLASS_DECL_CORE color_selector_control :
      virtual public ::user::interaction,
      virtual public ::core::graphics::color_selector,
      virtual public ::graphics::color_wheel
   {
   public:

      ::write_text::font_pointer m_pfont;
      //bool                             m_bMouseColorBeam;
      //::int_point                      m_pointMouseColorBeam;
      //bool                             m_bCompact;
      //bool                             m_bLButtonPressed;
      ::user::plain_edit               m_editRed;
      ::user::plain_edit               m_editGreen;
      ::user::plain_edit               m_editBlue;
      ::user::plain_edit               m_editHex;

      //::image::image_pointer                  m_pimageTemplate;
      //::image::image_pointer                  m_pimage;
      //::image::image_pointer                  m_pimageLuminance;

      //::color::hls                            m_hls;

      //::int_rectangle                           m_rectangleColors;
      bool m_bMode0;
      bool m_bColorWheel;


      color_selector_control();
      ~color_selector_control() override;


      void on_initialize_particle() override;


      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

      void install_message_routing(::channel * pchannel) override;


      void set_sel_color(const ::color::hls & hls) override;
      ::color::hls get_sel_color() override;


      void graphics_set_mouse_capture() override;
      void graphics_release_mouse_capture() override;
      void graphics_redraw() override;


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      //void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void on_draw_mode_0(::draw2d::graphics_pointer & pgraphics);
      //virtual void on_draw_color_wheel(::draw2d::graphics_pointer & pgraphics);

      //virtual void draw_beam(::draw2d::graphics_pointer & pgraphics, const ::int_point & point);
      //virtual void draw_level(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleW, int y);


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void on_mouse(const ::int_point & point);
      //virtual void rebuild_luminance();

      virtual ::color::hls get_color();
      virtual void set_color(const ::color::hls & hls);


      void on_color_change() override;


   };


} // namespace user


