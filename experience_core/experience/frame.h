#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "base/user/experience/frame.h"


namespace experience_core
{


   class CLASS_DECL_APP_EXPERIENCE_CORE frame :
      virtual public ::experience::frame
   {
   public:

      //e_style                           m_pframewindow->m_estyle;
      status < ::color::color >           m_colorFrameBorder;
      status < ::color::color >           m_colorMoveableBorderHilight;
      status < ::color::color >           m_colorMoveableBorderDkShadow;
      status < ::color::color >           m_colorCaptionTextBk;
      status < ::color::color >           m_colorCaptionText;
      ::draw2d::pen_pointer               m_ppenText1;
      ::draw2d::pen_pointer               m_ppenFace1;
      ::draw2d::pen_pointer               m_ppenHilight1;
      ::draw2d::pen_pointer               m_ppenShadow1;
      ::draw2d::pen_pointer               m_ppenDkShadow1;
      status < ::color::color >           m_colorDkShadow;
      size_i32                            m_minSize;

      ::draw2d::pen_pointer               m_ppenHollow0;
      ::draw2d::pen_pointer               m_ppenHollow1;
      ::draw2d::pen_pointer               m_ppenHollow2;
      ::draw2d::pen_pointer               m_ppenHollow3;
      ::draw2d::pen_pointer               m_ppenHollow4;
      ::draw2d::pen_pointer               m_ppenHollow5;
      ::size_i32                          m_sizeIcon;

      frame();
      ~frame() override;


      void on_initialize_experience_frame() override;

      string get_default_user_style() const override;

      status < ::color::color > get_border_main_body_color() override;

      void set_moveable_border_color(const ::color::color& colorMoveableBorder) override;

      virtual void set_button_color_schema_001(const ::color::color& colorMoveableBorder);

      virtual void set_frame_color_system_default_001();

      virtual void on_style_change_001_and_002(::draw2d::graphics_pointer & pgraphics);

      void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics) override;

      //virtual ::color::color get_style_moveable_border_color(::user::enum_style estyle);

      void OnMove(::pointer<::user::interaction>pframewindow) override;

      //virtual void set_style(::user::enum_style estyle);

      //virtual enum_style translate_style(const ::string & pszStyle);

      virtual void _on_style_change(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void _001OnBeforeMove(const ::rectangle_i32 &lpcrectWindow);

      //virtual void _001OnBeforeSize(const ::rectangle_i32 &lpcrectWindow);

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      bool get_element_rectangle(::rectangle_i32 & lprect, enum_element eelement) override;

      //bool _001HitTest(const ::point_i32 &point, enum_element &eelementParam) override;

      //::experience::enum_frame experience_frame_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;

      //::item_pointer experience_frame_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;

      virtual void Glass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);

      virtual void ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, const ::color::color& color, ::u8 bAlpha);

//               virtual ::user::front_end_schema * get_user_front_end_schema();

      virtual void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, enum_border eborder, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight);

      virtual void on_draw_frame(::draw2d::graphics_pointer & pgraphics);


      virtual void GetBorderRectangle(const ::rectangle_i32 & rectangleOuter, ::rectangle_i32 * lprect, enum_border eside);
      virtual void GetBorderRectangle(const ::rectangle_i32 & rectangleOuter, int iDeflate, ::rectangle_i32 * lprect, enum_border eside);

      ::rectangle_i32 outer_frame() override;

      ::experience::enum_frame experience_frame_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;
      void place_set_need_redraw(const ::rectangle_i32 & rectangleAfter, const ::rectangle_i32 & rectangleBefore, ::draw2d::graphics * pgraphics) override;

   };


} // namespace experience_core



