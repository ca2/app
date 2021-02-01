#include "framework.h"


namespace experience
{


   namespace core
   {


            frame::frame() :
               m_penText1(e_create),
               m_penFace1(e_create),
               m_penHilight1(e_create),
               m_penShadow1(e_create),
               m_penDkShadow1(e_create)
            {

               m_colorCaptionText = ARGB(255, 0, 0, 0);

               m_rectClient.set(0, 0, 0, 0);

            }


            frame::~frame()
            {

            }


            void frame::on_initialize_experience_frame()
            {

/*               auto estyle = translate_style(m_strStyle);

               set_style(estyle)*/;

            }


            string frame::get_default_user_style() const
            {

               return "TranslucidWarmLiteGray";

            }


            void frame::OnMove(__pointer(::user::interaction) pframewindow)
            {

               UNREFERENCED_PARAMETER(pframewindow);

            }


            void frame::Glass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectParam)
            {

               auto pframewindow = m_pframewindow;

               auto imaging = System.imaging();

               ::rectangle_i32 rectClient(rectParam);

               ::rectangle_i32 rectInflate;

               if(rectClient.is_empty())
               {

                  return;

               }


               i32 iInflate = 5; // raio 2 pixels + centro 1 pixel

               rectInflate = rectClient;

               rectInflate.inflate(iInflate, iInflate);

               ::rectangle_i32 rectScreen;

               pframewindow->best_monitor(rectScreen);

               ::image_pointer pimage1;

               ::image_pointer pimage2;

               pimage1 = create_image({rectClient.width() + iInflate * 2,  rectClient.height() + iInflate * 2});

               pimage2 = create_image({rectClient.width() + iInflate * 2,  rectClient.height() + iInflate * 2});

               ::rectangle_i32 rectWindow = rectClient;

               pframewindow->_001ClientToScreen(rectWindow);

               ::point_i32 pointInflate(iInflate, iInflate);

               auto point = rectClient.top_left();

               point_i32 -= pointInflate;

               bool b = pimage2->g()->stretch(::rectangle_i32(pimage1->get_size()), pgraphics, ::rectangle_i32(point, pimage1->get_size()));

               b = imaging.blur(pimage2, 2);

               pgraphics->stretch(rectClient, pimage2->g(), ::rectangle_i32(pointInflate, rectClient.size()));

            }


            color32_t frame::get_border_main_body_color()
            {

               return RGB(63, 150, 106);

            }


            void frame::ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, color32_t cr, byte bAlpha)
            {

               System.imaging().color_blend(pgraphics, rectangle_i32, cr, bAlpha);

            }


            //void frame::set_user_style(::user::enum_style estyle)
            //{

            //   m_pframewindow->m_estyle = estyle;

            //   if (get_control_box().is_null())
            //   {

            //      return;

            //   }

            //   on_style_change();

            //}


            //frame::e_style frame::translate_style(const char * pszStyle)
            //{

            //   string strStyle(pszStyle);

            //   if(strStyle == "TranslucidLightBlue")
            //   {

            //      return StyleTranslucidLightBlue;

            //   }
            //   else if (strStyle == "TranslucidLightGreen")
            //   {

            //      return StyleTranslucidLightGreen;

            //   }
            //   else if (strStyle == "TranslucidWarmGray")
            //   {

            //      return StyleTranslucidWarmGray;

            //   }
            //   else if (strStyle == "TranslucidWarmLiteGray")
            //   {

            //      return StyleTranslucidWarmLiteGray;

            //   }
            //   else if(strStyle == "DarkWarmBlue")
            //   {

            //      return StyleDarkWarmBlue;

            //   }
            //   else if(strStyle == "WarmGray")
            //   {

            //      return StyleTranslucidWarmGray;

            //   }
            //   else if(strStyle == "BlueRedPurple")
            //   {

            //      return StyleBlueRedPurple;

            //   }
            //   else if(strStyle == "RedOrange")
            //   {

            //      return StyleRedOrange;

            //   }
            //   else if(strStyle == "LightBlue")
            //   {

            //      return StyleLightBlue;

            //   }
            //   else if (strStyle == "BlackBorder")
            //   {

            //      return StyleBlackBorder;

            //   }
            //   else if (strStyle == "LightGreen")
            //   {

            //      return StyleLightGreen;

            //   }
            //   else if (strStyle == "EveningSun")
            //   {

            //      return StyleEveningSun;

            //   }
            //   else if (strStyle == "BlackPiano")
            //   {

            //      return StyleBlackPiano;

            //   }
            //   else
            //   {

            //      return StyleLightBlue;

            //   }

            //}


            frame::enum_element operator++(frame::enum_element & eelement, i32 i)
            {
               UNREFERENCED_PARAMETER(i);
               return (frame::enum_element) (*((i32*)&eelement))++;
            }

            bool frame::get_element_rect(LPRECT32 lprect, enum_element eelement)
            {
               switch(eelement)
               {
               case ElementTopLeftIcon:

                  if(m_pframewindow == nullptr || m_pframewindow->m_picon == nullptr)
                     return false;

                  lprect->left = m_pointWindowIcon.x;
                  lprect->top = m_pointWindowIcon.y;
                  lprect->right = lprect->left + m_pframewindow->m_picon->get_size().cx;
                  lprect->bottom = lprect->top + m_pframewindow->m_picon->get_size().cy;

                  return true;

               case ElementMoveGripMinimal:

                  if (m_pframewindow == nullptr || m_pframewindow->layout().design().display() != ::e_display_minimal)
                  {
                   
                     return false;

                  }

                  //lprect->left = m_pointMoveGripMinimal.x + 2;
                  //lprect->top = m_pointMoveGripMinimal.y + 2;
                  lprect->right = lprect->left + m_iCaptionHeight - 4;
                  lprect->bottom = lprect->top + m_iCaptionHeight - 4;

                  return true;

               default:
                  break;
               }
               return false;

            }

            bool frame::_001HitTest(const POINT_I32 &point, enum_element &eelementParam)
            {
               ::rectangle_i32 rectangle;
               for(enum_element eelement = (enum_element)(ElementNone + 1);
                     eelement < ElementEnd;
                     eelement++)
               {
                  get_element_rect(rectangle, eelement);
                  if(rectangle.contains(point))
                  {
                     eelementParam = eelement;
                     return true;
                  }
               }
               return false;
            }


            void frame::set_moveable_border_color(color32_t cr)
            {
               m_colorMoveableBorder = cr;

               color color;

               color.set_rgb(cr);
               color.hls_rate(0.0, 0.5, 0.0);
               m_colorMoveableBorderHilight = color.get_rgb() | (0xff << 24);

               color.set_rgb(cr);
               color.hls_rate(0.0, -0.3, 0.0);
               m_colorMoveableBorderShadow = color.get_rgb() | (0xff << 24);

               color.set_rgb(cr);
               color.hls_rate(8.0, -0.8, 0.0);
               m_colorMoveableBorderDkShadow = color.get_rgb() | (0xff << 24);


               m_colorCaptionTextBk = m_colorMoveableBorderShadow;

            }


            void frame::set_button_color_schema_001(color32_t crMoveableBorder)
            {

//               defer_create_user_schema(schema_button);

//               color32_t crBase = crMoveableBorder;
//
//               color ca;
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.49, -0.49);
//               create_color(color_border, ca.get_rgb() | (0xff << 24));
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.11, -0.11);
//               create_color(color_background, ca.get_rgb() | (0xff << 24));
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.49, -0.49);
//               create_color(color_text_normal, ca.get_rgb() | (0xff << 24));
//
//
//
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.45, 0.11);
//               create_color(color_border_hover, ca.get_rgb() | (0xff << 24));
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, 0.33, 0.0);
//               create_color(color_background_hover,ca.get_rgb() | (0xff << 24));
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.55, 0.11);
//               create_color(color_text_hover, ca.get_rgb() | (0xff << 24));

            }


            void frame::set_frame_color_system_default_001()
            {

               auto pframewindow = m_pframewindow;

               auto pgraphics = pframewindow->create_memory_graphics();

               auto pstyle = pframewindow->get_style(pgraphics);

               m_penText1->create_solid(1, pframewindow->get_color(pstyle, ::user::e_element_button_text));
               m_penFace1->create_solid(1, pframewindow->get_color(pstyle, ::user::e_element_button_background));
               m_penHilight1->create_solid(1, pframewindow->get_color(pstyle, ::user::e_element_button_hilite));
               m_penShadow1->create_solid(1, pframewindow->get_color(pstyle, ::user::e_element_button_shadow));
               m_penDkShadow1->create_solid(1, pframewindow->get_color(pstyle, ::user::e_element_button_dark_shadow));
               m_colorDkShadow = pframewindow->get_color(pstyle, ::user::e_element_button_dark_shadow);
               m_colorFrameBorder = RGB(0, 0, 0) | 0xff000000;

            }


            void frame::on_style_change_001_and_002()
            {

               auto pcontrolbox = get_control_box();

               m_minSize = size_i32(144, 48);

               m_minSize.cy = 48;

               if (pcontrolbox)
               {

                  pcontrolbox->set_button_color_system_default_001();

               }

               set_frame_color_system_default_001();

               auto pframewindow = m_pframewindow;

               auto estyle = pframewindow->m_estyle;

               auto colorBorder = pframewindow->get_moveable_border_color();

               set_moveable_border_color(colorBorder);

               set_button_color_schema_001(m_colorMoveableBorder);

               if(m_pframewindow->m_estyle == ::user::StyleTranslucidWarmGray || m_pframewindow->m_estyle == ::user::StyleDarkWarmBlue)
               {

                  pcontrolbox->m_colorBackground = m_colorCaptionTextBk;

                  m_colorCaptionText = ARGB(255, 255, 255, 255);

               }
               else if (m_pframewindow->m_estyle == ::user::StyleBlackPiano || m_pframewindow->m_estyle == ::user::StyleBlackBorder)
               {

                  pcontrolbox->m_colorBackground = m_colorCaptionTextBk;

                  m_colorCaptionText = ARGB(255, 255, 255, 255);

               }

            }


            //color32_t frame::get_style_moveable_border_color(::user::enum_style estyle)
            //{
            //   switch(m_pframewindow->m_estyle)
            //   {
            //   case ::user::StyleLightBlue:
            //   case ::user::StyleTranslucidLightBlue:
            //      return RGB(116, 160, 220);
            //   case ::user::StyleBlackPiano:
            //   case ::user::StyleBlackBorder:
            //      return RGB(0, 0, 0);
            //   case ::user::StyleTranslucidWarmGray:
            //      return ARGB(255, 190, 184, 177);
            //      break;
            //   case ::user::StyleDarkWarmBlue:
            //      return ARGB(255,34,54,75);
            //      break;
            //   case ::user::StyleLightGreen:
            //   case ::user::StyleTranslucidLightGreen:
            //      return RGB(116, 220, 160) | 0xff000000;
            //   case ::user::StyleRedOrange:
            //      return RGB(255, 170, 136) | 0xff000000;
            //   case ::user::StyleBlueRedPurple:
            //      return RGB(200, 100, 220) | 0xff000000;
            //   case ::user::StyleEveningSun:
            //      return RGB(255, 210, 100) | 0xff000000;
            //   case ::user::StyleTranslucidWarmLiteGray:
            //      return RGB(239, 230, 219) | 0xff000000;
            //   }


            //   // Light Green/Translucid Light Green
            //   return RGB(116, 220, 160) | 0xff000000;

            //}


            //bool frame::is_translucid_style(e_style estyle)
            //{


            //}


            void frame::Draw3dRectSide(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectParam,enum_border eborder,color32_t crTopLeft,color32_t crBottomRight)
            {

               ::rectangle_i32 rectangle(rectParam);

               i32 x = rectangle.left;
               i32 y = rectangle.top;
               i32 cx = rectangle.width();
               i32 cy = rectangle.height();

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

               ::draw2d::pen_pointer pen;

               if(eborder & e_border_top || eborder & e_border_left)
               {

                  pen.create(this);

                  pen->create_solid(1.0,crTopLeft);

                  pgraphics->set(pen);

               }

               if(eborder & e_border_top)
               {

                  pgraphics->move_to(x,y);

                  pgraphics->line_to(x + cx,y);

               }

               if(eborder & e_border_left)
               {

                  pgraphics->move_to(x,y);

                  pgraphics->line_to(x,y+cy);

               }

               if((eborder & e_border_right || eborder & e_border_bottom) && (pen.is_null() || pen->m_color != crBottomRight))
               {

                  pen.create(this);

                  pen->create_solid(1.0,crBottomRight);

                  pgraphics->set(pen);

               }

               if(eborder & e_border_right)
               {

                  pgraphics->move_to(x + cx,y);

                  pgraphics->line_to(x + cx,y + cy);

               }

               if(eborder & e_border_bottom)
               {

                  pgraphics->move_to(x,y + cy);

                  pgraphics->line_to(x + cx,y + cy);

               }

            }


            void frame::on_style_change()
            {


            }


            void frame::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
            {

               if (!m_pframewindow->is_frame_experience_enabled())
               {

                  return;

               }

               auto psession = Session;

               pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

               auto pframewindow = m_pframewindow;

               if(!pframewindow->layout().is_full_screen() && !pframewindow->layout().is_zoomed() && !pframewindow->layout().is_iconic() && !m_pframewindow->frame_is_transparent() && m_pframewindow->m_bShowControlBox)
               {

                  on_draw_frame(pgraphics);

               }

               if(pframewindow->layout().is_minimal())
               {

                  ::rectangle_i32 rectIcon;

                  if(get_element_rect(rectIcon,ElementTopLeftIcon))
                  {

                     ::draw2d::icon * picon = m_pframewindow->m_picon;

                     if(picon != nullptr)
                     {

                        pgraphics->draw(rectIcon,picon);

                     }

                  }

                  ::rectangle_i32 rectGrip;

                  if(get_element_rect(rectGrip,ElementMoveGripMinimal))
                  {

                     int i = 0;

                     while(i < rectGrip.width() - 5 + 1)
                     {

                        ::rectangle_f64 rectangle_i32(rectGrip.left + i, rectGrip.top, 3, rectGrip.height());

                        pgraphics->draw_3drect(rectangle, ARGB(110,230,230,230),ARGB(110,130,130,130));

                        i += 5;

                     }

                  }

               }
               else if(!pframewindow->layout().is_full_screen() && !m_pframewindow->frame_is_transparent())
               {

                  //pgraphics->fill_rect(m_rectCaptionTextBk, m_colorCaptionTextBk);
                  pgraphics->fill_rect(m_rectCaption, m_colorCaptionTextBk);

                  ::rectangle_i32 rectIcon;

                  auto pframewindow = m_pframewindow;

                  color32_t    crMoveableBorder;

                  color32_t    crMoveableBorderHilight;

                  color32_t    crMoveableBorderShadow;

                  string str;

                  pframewindow->get_window_text(str);

                  if(pframewindow->is_active())
                  {

                     crMoveableBorder = m_colorMoveableBorder;

                     crMoveableBorderHilight = m_colorMoveableBorderHilight;

                     crMoveableBorderShadow = m_colorMoveableBorderShadow;

                  }
                  else
                  {

                     auto pstyle = pframewindow->get_style(pgraphics);

                     crMoveableBorder = pframewindow->get_color(pstyle, ::user::e_element_button_background);

                     crMoveableBorderHilight = pframewindow->get_color(pstyle, ::user::e_element_button_hilite);

                     crMoveableBorderShadow = pframewindow->get_color(pstyle, ::user::e_element_button_shadow);

                  }

                  ::rectangle_i32 rectangle;

                  pframewindow->get_window_rect(rectangle);

                  rectangle_i32 -= rectangle.top_left();

                  if(get_element_rect(rectIcon, ElementTopLeftIcon))
                  {

                     ::draw2d::icon * picon = m_pframewindow->m_picon;

                     if(picon != nullptr)
                     {

                        pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

                        pgraphics->draw(rectIcon, picon);

                     }

                  }

                  string wstrWindowText;

                  pframewindow->get_window_text(wstrWindowText);

                  pgraphics->set_text_color(m_colorCaptionText);

                  pgraphics->set_font(pframewindow, ::user::e_element_window_title);

                  pgraphics->_DrawText(wstrWindowText, m_rectWindowText, { e_align_left, e_align_vertical_center}, e_draw_text_no_prefix);

               }


            }


            void frame::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
            {

               UNREFERENCED_PARAMETER(pgraphics);

            }


   } // namespace core


} // namespace experience



