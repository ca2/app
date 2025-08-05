#pragma once


#include "acme/user/user/_style.h"
#include "berg/user/experience/frame.h"


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



      ::pointer<::image::fastblur>         m_pfastblur;
      ::draw2d::pen_pointer                  m_ppenText1;
      ::draw2d::pen_pointer                  m_ppenFace1;
      ::draw2d::pen_pointer                  m_ppenHilight1;
      ::draw2d::pen_pointer                  m_ppenShadow1;
      ::draw2d::pen_pointer                  m_ppenDkShadow1;
      status < ::color::color >              m_colorDkShadow;
      status < ::color::color >              m_colorFrameBorder;
      int_size                               m_minSize;

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

      //virtual void set_style(const ::scoped_string & scopedstrStyle) override;

      //virtual void on_style_change() override;

      //virtual void _001OnBeforeMove(const ::int_rectangle & rectangleWindow) override;

      //virtual void _001OnBeforeSize(const ::int_rectangle & rectangleWindow) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool get_element_rectangle(::int_rectangle & rect, enum_element eelement) override;

      virtual void Glass(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);

      virtual void ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, const ::color::color & color, const ::opacity & opacity);

      //virtual ::user::front_end_schema * get_user_front_end_schema();

      virtual void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, enum_border eborder, color32_t crTopLeft, color32_t crBottomRight);

      virtual void on_draw_frame(::draw2d::graphics_pointer & pgraphics);

      virtual bool is_control_box_moveable() override;



      virtual void GetFrameRect(int_rectangle & rect) override;
      virtual void GetBorderRectangle(const ::int_rectangle & rectangleX, ::int_rectangle * prectangle, enum_border eside);


      ::experience::enum_frame experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;


   };


} // namespace experience_anthill



