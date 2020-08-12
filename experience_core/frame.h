#pragma once



   namespace experience
   {


         namespace aura
         {


            class CLASS_DECL_APP_EXPERIENCE_CORE frame :
               virtual public ::experience::frame
            {
            public:


               enum e_style
               {
                  StyleLightBlue,
                  StyleBlackBorder,
                  StyleLightGreen,
                  StyleRedOrange,
                  StyleBlueRedPurple,
                  StyleEveningSun,
                  StyleTranslucidLightBlue,
                  StyleTranslucidLightGreen,
                  StyleTranslucidWarmGray,
                  StyleTranslucidWarmLiteGray,
                  StyleDarkWarmBlue,
                  StyleBlackPiano,
               };




               e_style                             m_estyle;
               COLORREF                            m_crFrameBorder;
               COLORREF                            m_crMoveableBorderHilight;
               COLORREF                            m_crMoveableBorderDkShadow;
               COLORREF                            m_crCaptionTextBk;
               COLORREF                            m_crCaptionText;
               ::draw2d::pen_pointer               m_penText1;
               ::draw2d::pen_pointer               m_penFace1;
               ::draw2d::pen_pointer               m_penHilight1;
               ::draw2d::pen_pointer               m_penShadow1;
               ::draw2d::pen_pointer               m_penDkShadow1;
               COLORREF                            m_crDkShadow;
               size                                m_minSize;

               ::draw2d::pen_pointer               m_penHollow0;
               ::draw2d::pen_pointer               m_penHollow1;
               ::draw2d::pen_pointer               m_penHollow2;
               ::draw2d::pen_pointer               m_penHollow3;
               ::draw2d::pen_pointer               m_penHollow4;
               ::draw2d::pen_pointer               m_penHollow5;



               frame();
               virtual ~frame();


               virtual void on_initialize_experience_frame();


               virtual COLORREF get_border_main_body_color();

               virtual bool is_translucid_style(e_style estyle);

               virtual void set_moveable_border_color(COLORREF cr);

               virtual void set_button_color_schema_001(COLORREF crMoveableBorder);

               virtual void set_frame_color_system_default_001();

               virtual void on_style_change_001_and_002();

               virtual COLORREF get_style_moveable_border_color(e_style estyle);

               virtual void OnMove(__pointer(::user::interaction) pframewindow);

               virtual void set_style(e_style estyle);

               virtual e_style translate_style(const char * pszStyle);

               virtual void on_style_change();

               //virtual void _001OnBeforeMove(const RECT & lpcrectWindow);

               //virtual void _001OnBeforeSize(const RECT & lpcrectWindow);

               virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

               virtual bool get_element_rect(LPRECT lprect, e_element eelement);

               virtual bool _001HitTest(const POINT &point, e_element &eelementParam);

               virtual void Glass(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);

               virtual void ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rect & rect, COLORREF cr, BYTE bAlpha);

//               virtual ::user::front_end_schema * get_user_front_end_schema();

               virtual void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rect & rect, e_border eborder, COLORREF crTopLeft, COLORREF crBottomRight);

               virtual void on_draw_frame(::draw2d::graphics_pointer & pgraphics);


            };


            frame::e_element operator++(frame::e_element & eelement, i32 i);


   } // namespace aura


} // namespace experience



