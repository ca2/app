#pragma once



namespace experience
{


   namespace anthill
   {


            class CLASS_DECL_APP_EXPERIENCE_ANTHILL frame :
               public ::experience::frame
            {
            public:


               enum e_style
               {
                  StyleLightBlue,
                  StyleBlackBorder,
                  StyleLightGreen,
                  StyleRedOrange,
                  StyleDarkRed,
                  StyleBlueRedPurple,
                  StyleEveningSun,
                  StyleTranslucidLightBlue,
                  StyleTranslucidLightGreen,
                  StyleTranslucidWarmGray,
                  StyleTranslucidWarmLiteGray,
                  StyleDarkWarmBlue,
               };



               ::draw2d::fastblur               m_blur1;
               e_style                          m_estyle;
               //::user::front_end_schema         m_schema;
               COLORREF                         m_crFrame_border;
               COLORREF                         m_crMoveableBorderHilight;
               COLORREF                         m_crMoveableBorderDkShadow;
               COLORREF                         m_crCaptionTextBk;
               COLORREF                         m_crActiveCaptionTextBk;
               COLORREF                         m_crCaptionText;
               ::draw2d::pen_pointer                 m_penText1;
               ::draw2d::pen_pointer                 m_penFace1;
               ::draw2d::pen_pointer                 m_penHilight1;
               ::draw2d::pen_pointer                 m_penShadow1;
               ::draw2d::pen_pointer                 m_penDkShadow1;
               COLORREF                         m_crDkShadow;
               size                             m_minSize;

               ::draw2d::pen_pointer                 m_penHollow1;
               ::draw2d::pen_pointer                 m_penHollow2;
               ::draw2d::pen_pointer                 m_penHollow3;
               ::draw2d::pen_pointer                 m_penHollow4;
               ::draw2d::pen_pointer                 m_penHollow5;



               frame();

               virtual ~frame();

               virtual COLORREF get_border_main_body_color() override;

               virtual bool is_translucid_style(e_style estyle);

               virtual void set_moveable_border_color(COLORREF cr);

               virtual void set_button_color_schema_001(COLORREF crMoveableBorder);

               virtual void set_frame_color_system_default_001();

               virtual void on_style_change_001_and_002();

               virtual COLORREF get_style_moveable_border_color(e_style estyle);

               virtual void OnMove(__pointer(::user::interaction) pframewindow) override;

               virtual void set_style(e_style estyle);

               virtual void set_style(const char * pszStyle) override;

               virtual void on_style_change() override;

               //virtual void _001OnBeforeMove(const ::rect & rectWindow) override;

               //virtual void _001OnBeforeSize(const ::rect & rectWindow) override;

               virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

               virtual bool get_element_rect(LPRECT lprect, e_element eelement) override;

               virtual bool hit_test(const POINT &point, e_element &eelementParam);

               virtual void Glass(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);

               virtual void ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rect & rect, COLORREF cr, BYTE bAlpha);

               //virtual ::user::front_end_schema * get_user_front_end_schema();

               virtual void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rect & rect, e_border eborder, COLORREF crTopLeft, COLORREF crBottomRight);

               virtual void on_draw_frame(::draw2d::graphics_pointer & pgraphics);

               virtual bool is_control_box_moveable() override;



               virtual void GetFrameRect(rect * lprect) override;


            };


            frame::e_element operator++(frame::e_element & eelement, i32 i);


         } // namespace anthill


   } // namespace experience




