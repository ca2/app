#pragma once


#include "acme/user/user/_style.h"
#include "base/user/experience/frame.h"


namespace experience_tranquillum
{


   class CLASS_DECL_APP_EXPERIENCE_TRANQUILLUM frame :
      public ::experience::frame
   {
      public:


      ::int_rectangle                        m_rectangleCaptionTextBk;
      ::int_point                            m_pointMoveGripMinimal;
      //::write_text::font_pointer           m_pfontButton;
      //::write_text::font_pointer           m_pfontCaption;
      //e_style                              m_estyle;
      //::user::front_end_schema             m_schema;
      status < ::color::color >       m_colorFrameBorder;
      status < ::color::color >       m_colorMoveableBorderHilight;
      status < ::color::color >       m_colorMoveableBorderDkShadow;
      status < ::color::color >       m_colorCaptionTextBk;
      status < ::color::color >       m_colorActiveCaptionTextBk;
      status < ::color::color >       m_colorCaptionText;
      ::draw2d::pen_pointer                  m_ppenText1;
      ::draw2d::pen_pointer                  m_ppenFace1;
      ::draw2d::pen_pointer                  m_ppenHilight1;
      ::draw2d::pen_pointer                  m_ppenShadow1;
      ::draw2d::pen_pointer                  m_ppenDkShadow1;
      status < ::color::color >       m_colorDkShadow;
      int_size                               m_minSize;

      ::draw2d::pen_pointer                  m_ppenHollow1;
      ::draw2d::pen_pointer                  m_ppenHollow2;
      ::draw2d::pen_pointer                  m_ppenHollow3;
      ::draw2d::pen_pointer                  m_ppenHollow4;
      ::draw2d::pen_pointer                  m_ppenHollow5;



      frame();
      ~frame() override;


      virtual status < ::color::color > get_border_main_body_color() override;

      virtual bool is_translucid_style(::user::enum_style estyle);

      void set_moveable_border_color(const ::color::color & color) override;

      virtual void set_button_color_schema_001(const ::color::color& crMoveableBorder);

      virtual void set_frame_color_system_default_001();

      virtual void on_style_change_001_and_002(::draw2d::graphics_pointer & pgraphics);

      //virtual color32_t get_style_moveable_border_color(e_style estyle);

      virtual void OnMove(::pointer<::user::interaction>pframewindow) override;


      virtual void title_bar_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnBeforeMove(const ::int_rectangle & rectangleWindow);


//               virtual void _001OnBeforeSize(const ::int_rectangle & rectangleWindow) override;


      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool get_element_rectangle(::int_rectangle & rectangle, enum_element eelement) override;



      virtual void Glass(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);


      virtual void ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, const ::color::color & color, const class ::opacity & opacity);


      //virtual ::user::front_end_schema * get_user_front_end_schema();

      virtual void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, enum_border eborder, const ::color::color & colorTopLeft, const ::color::color & colorBottomRight);

      virtual void on_draw_frame(::draw2d::graphics_pointer & pgraphics);

      virtual bool is_control_box_moveable() override;



      virtual void GetFrameRect(int_rectangle & rectangle) override;
      virtual void GetBorderRectangle(const ::int_rectangle & rectangleX, ::int_rectangle * prectangle, enum_border eside);

      ::experience::enum_frame experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;


   };



} // namespace experience_tranquillum



