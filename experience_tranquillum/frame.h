#pragma once





   namespace experience
   {


      


         namespace tranquillum

         {


            class CLASS_DECL_APP_EXPERIENCE_TRANQUILLUM frame :
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




               //::draw2d::font_pointer                m_fontButton;
               //::draw2d::font_pointer                m_fontCaption;
               e_style                          m_estyle;
               //::user::front_end_schema         m_schema;
               color32_t                         m_crFrameBorder;
               color32_t                         m_crMoveableBorderHilight;
               color32_t                         m_crMoveableBorderDkShadow;
               color32_t                         m_crCaptionTextBk;
               color32_t                         m_crActiveCaptionTextBk;
               color32_t                         m_crCaptionText;
               ::draw2d::pen_pointer                 m_penText1;
               ::draw2d::pen_pointer                 m_penFace1;
               ::draw2d::pen_pointer                 m_penHilight1;
               ::draw2d::pen_pointer                 m_penShadow1;
               ::draw2d::pen_pointer                 m_penDkShadow1;
               color32_t                         m_crDkShadow;
               size                             m_minSize;

               ::draw2d::pen_pointer                 m_penHollow1;
               ::draw2d::pen_pointer                 m_penHollow2;
               ::draw2d::pen_pointer                 m_penHollow3;
               ::draw2d::pen_pointer                 m_penHollow4;
               ::draw2d::pen_pointer                 m_penHollow5;



               frame();

               virtual ~frame();

               virtual color32_t get_border_main_body_color() override;

               virtual bool is_translucid_style(e_style estyle);

               virtual void set_moveable_border_color(color32_t cr);

               virtual void set_button_color_schema_001(color32_t crMoveableBorder);

               virtual void set_frame_color_system_default_001();

               virtual void on_style_change_001_and_002();

               virtual color32_t get_style_moveable_border_color(e_style estyle);

               virtual void OnMove(__pointer(::user::interaction) pframewindow) override;

               virtual void set_style(e_style estyle);

               virtual void set_style(const char * pszStyle) override;

               virtual void on_style_change() override;

               virtual void _001OnBeforeMove(const ::rect & rectWindow);


//               virtual void _001OnBeforeSize(const ::rect & rectWindow) override;


               virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

               virtual bool get_element_rect(RECT32 * prect, enum_element eelement) override;


               virtual bool hit_test(const point &point, enum_element &eelementParam);

               virtual void Glass(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);


               virtual void ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rect & rect, color32_t cr, byte bAlpha);


               //virtual ::user::front_end_schema * get_user_front_end_schema();

               virtual void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rect & rect, e_border eborder, color32_t crTopLeft, color32_t crBottomRight);

               virtual void on_draw_frame(::draw2d::graphics_pointer & pgraphics);

               virtual bool is_control_box_moveable() override;



               virtual void GetFrameRect(rect * prect) override;



            };


            frame::enum_element operator++(frame::enum_element & eelement, i32 i);


      } // namespace tranquillum


   } // namespace experience



