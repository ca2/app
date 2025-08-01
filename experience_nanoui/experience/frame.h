#pragma once


#include "base/user/experience/frame.h"


namespace experience_nanoui
{


   class CLASS_DECL_APP_EXPERIENCE_CORE frame :
      virtual public ::experience::frame
   {
   public:


      //e_style                           m_pframewindow->m_estyle;
      status < ::color::color >    m_colorFrameBorder;
      status < ::color::color >    m_colorMoveableBorderHilight;
      status < ::color::color >    m_colorMoveableBorderDkShadow;
      status < ::color::color >    m_colorCaptionTextBk;
      status < ::color::color >    m_colorCaptionText;
      ::draw2d::pen_pointer               m_ppenText1;
      ::draw2d::pen_pointer               m_ppenFace1;
      ::draw2d::pen_pointer               m_ppenHilight1;
      ::draw2d::pen_pointer               m_ppenShadow1;
      ::draw2d::pen_pointer               m_ppenDkShadow1;
      status < ::color::color >    m_colorDkShadow;
      int_size                            m_minSize;

      ::draw2d::pen_pointer               m_ppenHollow0;
      ::draw2d::pen_pointer               m_ppenHollow1;
      ::draw2d::pen_pointer               m_ppenHollow2;
      ::draw2d::pen_pointer               m_ppenHollow3;
      ::draw2d::pen_pointer               m_ppenHollow4;
      ::draw2d::pen_pointer               m_ppenHollow5;
      ::int_size                          m_sizeIcon;

      frame();
      virtual ~frame();


      void on_initialize_experience_frame() override;

      string get_default_user_style() const override;

      status < ::color::color > get_border_main_body_color() override;

      void set_moveable_border_color(const ::color::color& colorMoveableBorder) override;

      virtual void set_button_color_schema_001(const ::color::color& colorMoveableBorder);

      virtual void set_frame_color_system_default_001();

      virtual void on_style_change_001_and_002(::draw2d::graphics_pointer & pgraphics);

      //virtual ::color::color get_style_moveable_border_color(::user::enum_style estyle);

      void OnMove(::pointer<::user::interaction>pframewindow) override;

      //virtual void set_style(::user::enum_style estyle);

      //virtual enum_style translate_style(const ::scoped_string & scopedstrStyle);

      virtual void _on_style_change(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void _001OnBeforeMove(const ::int_rectangle &lpcrectWindow);

      //virtual void _001OnBeforeSize(const ::int_rectangle &lpcrectWindow);

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      bool get_element_rectangle(::int_rectangle & rectangle, enum_element eelement) override;

      void GetBorderRectangle(const ::int_rectangle & rectangleX, ::int_rectangle * lprect, enum_border eside);

      //bool experience_frame_hit_test(const ::int_point &point, enum_element &eelementParam) override;

      ::experience::enum_frame experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;

      virtual void Glass(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);

      virtual void ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, const ::color::color& color, unsigned char bAlpha);

//               virtual ::user::front_end_schema * get_user_front_end_schema();

      virtual void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, enum_border eborder, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight);

      virtual void on_draw_frame(::draw2d::graphics_pointer & pgraphics);


   };


   //frame::enum_frame operator ++(frame::enum_element & eelement, int i);



} // namespace experience_nanoui



