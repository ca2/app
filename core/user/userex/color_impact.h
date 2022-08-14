#pragma once


namespace userex
{


   class CLASS_DECL_CORE color_impact :
      virtual public ::user::impact
   {
   public:


      bool                             m_bMouseColorBeam;
      ::point_i32                      m_pointMouseColorBeam;
      bool                             m_bCompact;
      bool                             m_bLButtonPressed;
      ::user::plain_edit_impact          m_editRed;
      ::user::plain_edit_impact          m_editGreen;
      ::user::plain_edit_impact          m_editBlue;
      ::user::plain_edit_impact          m_editHex;

      ::image_pointer                  m_pimageTemplate;
      ::image_pointer                  m_pimage;
      ::image_pointer                  m_pimageLuminance;

      ::color::hls                            m_hls;

      ::rectangle_i32                           m_rectangleColors;


      color_impact();
      virtual ~color_impact();


      void assert_ok() const override;

      void dump(dump_context & dumpcontext) const override;

      void install_message_routing(::channel * pchannel) override;

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      //virtual void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void draw_beam(::draw2d::graphics_pointer & pgraphics, const ::point_i32 & point);
      virtual void draw_level(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleW, int y);


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_mouse(const ::point_i32 & point);
      virtual void rebuild_luminance();

      virtual ::color::color get_color();
      virtual void set_color(const ::color::color &color);


   };


} // namespace userex



namespace app_core_flag
{


   CLASS_DECL_CORE void dk(::draw2d::graphics_pointer & pgraphics, double x, double y, double w, double h);


} // namespace flag


namespace visual
{


   CLASS_DECL_CORE void colors_with_shades_of_grey(::image * pimage);

   CLASS_DECL_CORE void shades_of_luminance(::image * pimage, double dH, double dS);


} // namespace visual


