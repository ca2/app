// From userex/color_impact 2023-10-09 01:30 <3ThomasBorregaardSorensen!!
#pragma once


#include "axis/graphics/graphics/color_selector.h"


namespace core
{


   namespace graphics
   {


      class CLASS_DECL_CORE color_selector :
         virtual public ::graphics::color_selector
      {
      public:


         //bool                             m_bMouseColorBeam;
         ::int_point                      m_pointMouseColorBeam;
         bool                             m_bCompact;
         bool                             m_bLButtonPressedOnHue;
         bool                             m_bLButtonPressedOnLuminance;
         ::string                         m_strOk;
         ::write_text::font_pointer       m_pfontOk;
         //::user::plain_edit               m_editRed;
         //::user::plain_edit               m_editGreen;
         //::user::plain_edit               m_editBlue;
         //::user::plain_edit               m_editHex;

         ::int_rectangle                  m_rectangleTarget;

         ::image::image_pointer                  m_pimageTemplate;
         ::image::image_pointer                  m_pimage;
         ::image::image_pointer                  m_pimageLuminance;

         ::int_rectangle                  m_rectangleColors;


         double m_dLastLuminanceH;
         double m_dLastLuminanceS;


         //::color::hls                     m_hls;

         //::function < void(const ::color::hls & hls, bool bFinal) >    m_callbackHls;


         color_selector();
         ~color_selector() override;


         // void assert_ok() const override;

         // void dump(dump_context & dumpcontext) const override;

         //void install_message_routing(::channel * pchannel) override;


         virtual void on_initialize_particle() override;


         //virtual void set_sel_color(const ::color::hls & hls);
         //virtual ::color::hls get_sel_color();


         void handle(::topic * ptopic, ::context * pcontext) override;

         //void handle(::topic * ptopic, ::context * pcontext) override;

         virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

         virtual void draw_beam(::draw2d::graphics_pointer & pgraphics, const ::int_point & point);
         virtual void draw_level(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleW, int y);


         //DECLARE_MESSAGE_HANDLER(on_message_create);
         //DECLARE_MESSAGE_HANDLER(on_message_show_window);
         //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
         //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
         //DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
         void on_color_change() override;
         virtual void layout_color_selector(const ::int_rectangle & rectangle);

         virtual bool on_mouse_down(const ::int_point & point);
         virtual bool on_mouse_motion(const ::int_point & point);
         virtual bool on_mouse_up(const ::int_point & point);
         virtual bool is_ok_target(const ::int_point & point);
         virtual void rebuild_luminance();

         //virtual ::color::color color_selector_get_color();
         //virtual void color_selector_set_color(const ::color::color & color);


          //void on_color_change() override;


      };


   } // namespace graphics


} // namespace core


namespace app_core_flag
{


   CLASS_DECL_CORE void dk(::draw2d::graphics_pointer & pgraphics, double x, double y, double w, double h);


} // namespace flag


namespace graphics
{


   CLASS_DECL_CORE void colors_with_shades_of_grey(::image::image *pimage);

   CLASS_DECL_CORE void shades_of_luminance(::image::image *pimage, double dH, double dS);


} // namespace graphics



