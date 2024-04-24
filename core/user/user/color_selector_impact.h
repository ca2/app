#pragma once


#include "color_selector_control.h"
#include "base/user/user/show.h"


namespace user
{


   class CLASS_DECL_CORE color_selector_impact :
      virtual public ::user::show < ::user::color_selector_control >
   {
   public:


      //bool                             m_bMouseColorBeam;
      //::point_i32                      m_pointMouseColorBeam;
      //bool                             m_bCompact;
      //bool                             m_bLButtonPressed;
      //::user::plain_edit               m_editRed;
      //::user::plain_edit               m_editGreen;
      //::user::plain_edit               m_editBlue;
      //::user::plain_edit               m_editHex;

      ////::image_pointer                  m_pimageTemplate;
      ////::image_pointer                  m_pimage;
      ////::image_pointer                  m_pimageLuminance;

      //::color::hls                     m_hls;

      //::rectangle_i32                  m_rectangleColors;


      color_selector_impact();
      ~color_selector_impact() override;


      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

      void install_message_routing(::channel * pchannel) override;
      
      
      //void set_sel_color(const ::color::hls & hls) override;
      //::color::hls get_sel_color() override;
      
      
      void handle(::topic * ptopic, ::context * pcontext) override;

      //void handle(::topic * ptopic, ::context * pcontext) override;

      //virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void draw_beam(::draw2d::graphics_pointer & pgraphics, const ::point_i32 & point);
      //virtual void draw_level(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleW, int y);


      DECLARE_MESSAGE_HANDLER(on_message_create);
      //DECLARE_MESSAGE_HANDLER(on_message_show_window);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_up);

      //virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void on_mouse(const ::point_i32 & point);
      //virtual void rebuild_luminance();

      //virtual ::color::color get_color();
      //virtual void set_color(const ::color::color &color);


   };


} // namespace user



