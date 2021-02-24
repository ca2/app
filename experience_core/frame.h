#pragma once



   namespace experience
   {


         namespace core
         {


            class CLASS_DECL_APP_EXPERIENCE_CORE frame :
               virtual public ::experience::frame
            {
            public:




               //e_style                             m_pframewindow->m_estyle;
               __status < ::color::color >         m_colorFrameBorder;
               __status < ::color::color >         m_colorMoveableBorderHilight;
               __status < ::color::color >         m_colorMoveableBorderDkShadow;
               __status < ::color::color >         m_colorCaptionTextBk;
               __status < ::color::color >         m_colorCaptionText;
               ::draw2d::pen_pointer               m_penText1;
               ::draw2d::pen_pointer               m_penFace1;
               ::draw2d::pen_pointer               m_penHilight1;
               ::draw2d::pen_pointer               m_penShadow1;
               ::draw2d::pen_pointer               m_penDkShadow1;
               color32_t                            m_colorDkShadow;
               size_i32                                m_minSize;

               ::draw2d::pen_pointer               m_penHollow0;
               ::draw2d::pen_pointer               m_penHollow1;
               ::draw2d::pen_pointer               m_penHollow2;
               ::draw2d::pen_pointer               m_penHollow3;
               ::draw2d::pen_pointer               m_penHollow4;
               ::draw2d::pen_pointer               m_penHollow5;



               frame();
               virtual ~frame();


               virtual void on_initialize_experience_frame();

               virtual string get_default_user_style() const;

               virtual color32_t get_border_main_body_color();

               virtual void set_moveable_border_color(color32_t cr);

               virtual void set_button_color_schema_001(color32_t crMoveableBorder);

               virtual void set_frame_color_system_default_001();

               virtual void on_style_change_001_and_002(::draw2d::graphics_pointer & pgraphics);

               //virtual color32_t get_style_moveable_border_color(::user::enum_style estyle);

               virtual void OnMove(__pointer(::user::interaction) pframewindow);

               //virtual void set_style(::user::enum_style estyle);

               //virtual enum_style translate_style(const char * pszStyle);

               virtual void _on_style_change(::draw2d::graphics_pointer & pgraphics) override;

               //virtual void _001OnBeforeMove(const RECTANGLE_I32 & lpcrectWindow);

               //virtual void _001OnBeforeSize(const RECTANGLE_I32 & lpcrectWindow);

               virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

               virtual bool get_element_rect(RECTANGLE_I32 * lprect, enum_element eelement);

               virtual bool _001HitTest(const POINT_I32 &point, enum_element &eelementParam);

               virtual void Glass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);

               virtual void ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, color32_t cr, byte bAlpha);

//               virtual ::user::front_end_schema * get_user_front_end_schema();

               virtual void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, enum_border eborder, color32_t crTopLeft, color32_t crBottomRight);

               virtual void on_draw_frame(::draw2d::graphics_pointer & pgraphics);


            };


            frame::enum_element operator++(frame::enum_element & eelement, i32 i);


   } // namespace core


} // namespace experience



