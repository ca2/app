#pragma once


#include "base/user/experience/frame.h"


namespace experience_anthill
{


   class CLASS_DECL_APP_EXPERIENCE_ANTHILL frame :
      public ::experience::frame
   {
   public:


      //enum e_style
      //{
      //   StyleLightBlue,
      //   StyleBlackBorder,
      //   StyleLightGreen,
      //   StyleRedOrange,
      //   StyleDarkRed,
      //   StyleBlueRedPurple,
      //   StyleEveningSun,
      //   StyleTranslucidLightBlue,
      //   StyleTranslucidLightGreen,
      //   StyleTranslucidWarmGray,
      //   StyleTranslucidWarmLiteGray,
      //   StyleDarkWarmBlue,
      //};



      ::pointer<::draw2d::fastblur>         m_pfastblur;
      ::draw2d::pen_pointer                  m_ppenText1;
      ::draw2d::pen_pointer                  m_ppenFace1;
      ::draw2d::pen_pointer                  m_ppenHilight1;
      ::draw2d::pen_pointer                  m_ppenShadow1;
      ::draw2d::pen_pointer                  m_ppenDkShadow1;
      status < ::color::color >              m_colorDkShadow;
      status < ::color::color >              m_colorFrameBorder;
      size_i32                               m_minSize;

      ::draw2d::pen_pointer                  m_ppenHollow1;
      ::draw2d::pen_pointer                  m_ppenHollow2;
      ::draw2d::pen_pointer                  m_ppenHollow3;
      ::draw2d::pen_pointer                  m_ppenHollow4;
      ::draw2d::pen_pointer                  m_ppenHollow5;



      frame();

      virtual ~frame();

      virtual status < ::color::color > get_border_main_body_color() override;

      //virtual bool is_translucid_user_style(enum_style estyle);

      virtual void set_button_color_schema_001(color32_t crMoveableBorder);

      virtual void set_frame_color_system_default_001();

      virtual void on_style_change_001_and_002(::draw2d::graphics_pointer & pgraphics);

      virtual void OnMove(::pointer<::user::interaction>pframewindow) override;

      virtual ::user::enum_style get_style() const;

      virtual bool is_translucid() const;


      //virtual void set_style(e_style estyle);

      //virtual void set_style(const ::string & pszStyle) override;

      //virtual void on_style_change() override;

      //virtual void _001OnBeforeMove(const ::rectangle_i32 & rectangleWindow) override;

      //virtual void _001OnBeforeSize(const ::rectangle_i32 & rectangleWindow) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool get_element_rect(::rectangle_i32 & rect, enum_element eelement) override;

      virtual void Glass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);

      virtual void ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, const ::color::color & color, const ::opacity & opacity);

      //virtual ::user::front_end_schema * get_user_front_end_schema();

      virtual void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, enum_border eborder, color32_t crTopLeft, color32_t crBottomRight);

      virtual void on_draw_frame(::draw2d::graphics_pointer & pgraphics);

      virtual bool is_control_box_moveable() override;



      virtual void GetFrameRect(rectangle_i32 & rect) override;


   };


} // namespace experience_anthill



