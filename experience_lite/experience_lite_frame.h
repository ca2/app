#pragma once





   namespace experience
   {


      


         namespace lite

         {


            class CLASS_DECL_APP_EXPERIENCE_LITE frame :
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



               ::image::fastblur               m_blur1;
               e_style                          m_estyle;
               //::user::front_end_schema         m_schema;
               color32_t                         m_colorFrameBorder;
               color32_t                         m_colorMoveableBorderHilight;
               color32_t                         m_colorMoveableBorderDkShadow;
               color32_t                         m_colorCaptionTextBk;
               color32_t                         m_colorActiveCaptionTextBk;
               color32_t                         m_colorCaptionText;
               ::draw2d::pen_pointer                 m_ppenText1;
               ::draw2d::pen_pointer                 m_ppenFace1;
               ::draw2d::pen_pointer                 m_ppenHilight1;
               ::draw2d::pen_pointer                 m_ppenShadow1;
               ::draw2d::pen_pointer                 m_ppenDkShadow1;
               color32_t                         m_colorDkShadow;
               int_size                             m_minSize;

               ::draw2d::pen_pointer                 m_ppenHollow1;
               ::draw2d::pen_pointer                 m_ppenHollow2;
               ::draw2d::pen_pointer                 m_ppenHollow3;
               ::draw2d::pen_pointer                 m_ppenHollow4;
               ::draw2d::pen_pointer                 m_ppenHollow5;



               frame(::particle * pparticle);

               virtual ~frame();

               virtual color32_t get_border_main_body_color() override;

               virtual bool is_translucid_style(e_style estyle);

               virtual void set_moveable_border_color(color32_t color32);

               virtual void set_button_color_schema_001(color32_t crMoveableBorder);

               virtual void set_frame_color_system_default_001();

               virtual void on_style_change_001_and_002(::draw2d::graphics_pointer & pgraphics);

               virtual color32_t get_style_moveable_border_color(e_style estyle);

               virtual void OnMove(::pointer<::user::interaction>pframewindow) override;

               virtual void set_style(e_style estyle);

               virtual void set_style(const ::scoped_string & scopedstrStyle) override;

               virtual void on_style_change() override;

               virtual void _001OnBeforeMove(const ::int_rectangle &lpcrectWindow);

               virtual void _001OnBeforeSize(const ::int_rectangle &lpcrectWindow) override;

               virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

               virtual bool get_element_rectangle(::int_rectangle * lprect, enum_element eelement) override;

               virtual bool hit_test(const ::int_point &point, enum_element &eelementParam);

               virtual void Glass(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle &lprect);

               virtual void ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle &lprect, color32_t color32, unsigned char bAlpha);

               //virtual ::user::front_end_schema * get_user_front_end_schema();

               virtual void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, enum_border eborder, color32_t crTopLeft, color32_t crBottomRight);

               virtual void on_draw_frame(::draw2d::graphics_pointer & pgraphics);

               virtual bool is_control_box_moveable() override;



               virtual void GetFrameRect(int_rectangle * lprect) override;


            };


            frame::enum_element operator ++(frame::enum_element & eelement, int i);


         } // namespace lite



      


   } // namespace experience







