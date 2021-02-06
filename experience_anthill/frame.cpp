#include "framework.h"


namespace experience
{


   namespace anthill
   {



            frame::frame() :
               m_penText1(e_create),
               m_penFace1(e_create),
               m_penHilight1(e_create),
               m_penShadow1(e_create),
               m_penDkShadow1(e_create)
            {
               
               m_colorActiveCaptionTextBk = 0;
               //m_rectControlBoxMarginNormal = nullp();

               m_rectMarginNormal.set(5, 5, 5, 5);

               m_colorCaptionText = argb(255, 255, 255, 255);

               //m_rectClient = nullptr;

               //               m_iMargin = 7;


            }

            frame::~frame()
            {

            }


            void frame::OnMove(__pointer(::user::interaction) pframewindow)
            {

               UNREFERENCED_PARAMETER(pframewindow);

            }


            ::user::enum_style frame::get_style() const
            {

               return m_pframewindow->m_estyle;

            }


            bool frame::is_translucid() const
            {

               return m_pframewindow->is_translucid_user_style(m_pframewindow->m_estyle);

            }


            void frame::Glass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectParam)
            {

               auto pframewindow = m_pframewindow;

               ::rectangle_i32 rectClient(rectParam);

               ::rectangle_i32 rectInflate;

               if (rectClient.is_empty())
               {
                  
                  return;

               }

               i32 iInflate = 5; // raio 2 pixels + centro 1 pixel

               rectInflate = rectClient;
               rectInflate.inflate(iInflate, iInflate);

               //__pointer(::user::interaction) pwndDesktop = System.get_desktop_window();

               ::rectangle_i32 rectScreen;

               pframewindow->best_monitor(rectScreen);

               ::image_pointer pimage1;

               ::image_pointer pimage2;

               pimage1 = create_image({rectClient.width() + iInflate * 2,  rectClient.height() + iInflate * 2});

               pimage2 = create_image({rectClient.width() + iInflate * 2,  rectClient.height() + iInflate * 2});
               ::rectangle_i32 rectWindow = rectClient;
               pframewindow->_001ClientToScreen(rectWindow);
               //pimage = create_image({rectClient.width(),  rectClient.height()});
               //bool b = pimage2->get_graphics()->BitBlt(0, 0, rectClient.width() + iInflate * 2, rectClient.height() + iInflate * 2, pgraphics, rectClient.left - iInflate, rectClient.top - iInflate);
               pimage2->get_graphics()->draw(
                  ::rect_dim(0, 0, rectClient.width() + iInflate * 2, rectClient.height() + iInflate * 2),
                  pgraphics, 
                  ::point_i32(rectClient.left - iInflate, rectClient.top - iInflate));
               //bool b = ::BitBlt(dc2, 0, 0, rectClient.width() + iInflate * 2, rectClient.height() + iInflate * 2, hdcScreen, rectClient.left - iInflate, rectClient.top - iInflate);

               m_blur1.blur(pimage1, 2, ::rectangle_i32(size(rectClient.width() + iInflate * 2, rectClient.height() + iInflate * 2)));

               //spgraphics->Draw3dRect(rectClient, 127 << 24, 127 << 24);
               //rectClient.deflate(1, 1);
               //spgraphics->Draw3dRect(rectClient, 64 << 24, 64 << 24);
               /*b = imaging.bitmap_blend(pgraphics, lprect->left, lprect->top,
               rectWindow.width(),
               rectWindow.height(),
               &spgraphics,
               iInflate, iInflate, 128);*/
               /*BLENDFUNCTION bf;
               bf.AlphaFormat = AC_SRC_ALPHA;
               bf.BlendOp     = AC_SRC_OVER;
               bf.BlendFlags = 0;
               bf.SourceConstantAlpha = 255;
               ::alpha_blend(pgraphics->get_handle1(),
               lprect->left, lprect->top,
               rectWindow.width(),
               rectWindow.height(),
               spgraphics->get_handle1(),
               0, 0,
               rectWindow.width(),
               rectWindow.height(),
               bf);*/

               pgraphics->draw(rectClient, pimage1->g(), ::point_i32(iInflate, iInflate));

            }

            color32_t frame::get_border_main_body_color()
            {
               return argb(255, 63, 150, 106);
            }

            //::user::front_end_schema * frame::get_user_front_end_schema()
            //{

            //   return &m_schema;

            //}


            void frame::ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, color32_t cr, byte bAlpha)
            {

               /*Gdiplus::Graphics g((HDC) pgraphics->get_os_data());
               g.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
               Gdiplus::SolidBrush solidBrush(Gdiplus::Color(bAlpha, colorref_get_r_value(cr), colorref_get_g_value(cr), colorref_get_b_value(cr)));
               g.FillRectangle(&solidBrush, lprect->left, lprect->top, lprect->right - lprect->left, lprect->bottom - lprect->top);*/

               System.imaging().color_blend(pgraphics, rectangle, cr, bAlpha);

            }




            //void frame::set_style(e_style estyle)
            //{

            //   m_estyle = estyle;

            //   if (get_control_box().is_null())
            //      return;

            //   on_style_change();

            //}


            //void frame::set_style(const char * pszStyle)
            //{

            //   string strStyle(pszStyle);

            //   if (strStyle == "TranslucidWarmGray")
            //   {
            //      set_style(StyleTranslucidWarmGray);
            //   }
            //   else if (strStyle == "DarkWarmBlue")
            //   {
            //      set_style(StyleDarkWarmBlue);
            //   }
            //   else if (strStyle == "WarmGray")
            //   {
            //      set_style(StyleTranslucidWarmGray);
            //   }
            //   else if (strStyle == "BlueRedPurple")
            //   {
            //      set_style(StyleBlueRedPurple);
            //   }
            //   else if (strStyle == "RedOrange")
            //   {
            //      set_style(StyleRedOrange);
            //   }
            //   else if (strStyle == "DarkRed")
            //   {
            //      set_style(StyleDarkRed);
            //   }
            //   else if (strStyle == "LightBlue")
            //   {
            //      set_style(StyleLightBlue);
            //   }
            //   else if (strStyle == "LightGreen")
            //   {
            //      set_style(StyleLightGreen);
            //   }


            //}


            frame::enum_element operator++(frame::enum_element & eelement, i32 i)
            {
               UNREFERENCED_PARAMETER(i);
               return (frame::enum_element) (*((i32*)&eelement))++;
            }

            bool frame::get_element_rect(RECTANGLE_I32 * lprect, enum_element eelement)
            {
               switch (eelement)
               {
               case ElementTopLeftIcon:

                  if (m_pframewindow == nullptr || m_pframewindow->m_picon == nullptr)
                     return false;

                  lprect->left = m_pointWindowIcon.x;
                  lprect->top = m_pointWindowIcon.y;
                  //lprect->right = lprect->left + m_pframewindow->m_picon->get_size().cx;
                  //lprect->bottom = lprect->top + m_pframewindow->m_picon->get_size().cy;
                  lprect->right = lprect->left + 24;
                  lprect->bottom = lprect->top + 24;

                  return true;

               case ElementMoveGripMinimal:

                  if (m_pframewindow == nullptr || m_pframewindow->layout().design().display() != ::e_display_minimal)
                     return false;

                  //lprect->left = m_pointMoveGripMinimal.x + 2;
                  //lprect->top = m_pointMoveGripMinimal.y + 2;
                  lprect->right = lprect->left + get_caption_height() - 4;
                  lprect->bottom = lprect->top + get_caption_height() - 4;

                  return true;

               default:
                  break;
               }
               return false;

            }


            bool frame::hit_test(const POINT_I32 &point, enum_element &eelementParam)
            {
               
               ::rectangle_i32 rectangle;
               
               for (enum_element eelement = (enum_element)(ElementNone + 1);
                     eelement < ElementEnd;
                     eelement++)
               {
                  
                  get_element_rect(rectangle, eelement);

                  if (rectangle.contains(point))
                  {
                     
                     eelementParam = eelement;
                     
                     return true;

                  }

               }
               
               return false;

            }


            void frame::set_button_color_schema_001(color32_t crMoveableBorder)
            {

//               defer_create_user_schema(::user::schema_button);

//               color32_t crBase = crMoveableBorder;

//               color ca;
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.49, -0.49);
//               create_color(color_border, ca.get_rgb() | (0xff << 24));
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.11, -0.11);
//               create_color(color_button_background, ca.get_rgb() | (0xff << 24));
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.49, -0.49);
//               create_color(color_button_text, ca.get_rgb() | (0xff << 24));
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
//               create_color(color_button_background_hover, ca.get_rgb() | (0xff << 24));
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.55, 0.11);
//               create_color(color_button_text_hover, ca.get_rgb() | (0xff << 24));

            }



            void frame::set_frame_color_system_default_001()
            {

               auto psession = Session;

               auto pframewindow = m_pframewindow;

               auto pgraphics = pframewindow->create_memory_graphics();

               auto pstyle = pframewindow->get_style(pgraphics);

               auto crButtonHilite = pframewindow->get_color(pstyle, ::user::e_element_button_hilite);

               auto crButtonDarkShadow = pframewindow->get_color(pstyle, ::user::e_element_button_dark_shadow);

               auto crButtonFace = pframewindow->get_color(pstyle, ::user::e_element_button_background);

               auto crButtonShadow = pframewindow->get_color(pstyle, ::user::e_element_button_shadow);

               m_penText1->create_solid(1, argb(255, 255, 255, 255));
               m_penFace1->create_solid(1, crButtonFace | 0xff000000);
               m_penHilight1->create_solid(1, crButtonHilite | 0xff000000);
               m_penShadow1->create_solid(1, crButtonShadow | 0xff000000);
               m_penDkShadow1->create_solid(1, crButtonDarkShadow | 0xff000000);
               m_colorDkShadow = crButtonDarkShadow;
               m_colorFrameBorder = rgb(0, 0, 0) | 0xff000000;


            }


            void frame::on_style_change_001_and_002()
            {

               auto pcontrolbox = get_control_box();

               if (pcontrolbox)
               {

                  pcontrolbox->set_button_color_system_default_001();

               }

               m_minSize = size_i32(144, 48);
               m_minSize.cy = 48;

               set_frame_color_system_default_001();

               //set_moveable_border_color(get_style_moveable_border_color(m_estyle));

               set_button_color_schema_001(m_colorMoveableBorder);

               auto estyle = get_style();

               if (estyle == ::user::StyleTranslucidWarmGray || estyle == ::user::StyleDarkWarmBlue)
               {

                  pcontrolbox->m_colorBackground = m_colorCaptionTextBk;

               }

            }

            //color32_t frame::get_style_moveable_border_color(e_style estyle)
            //{
            //   switch (m_estyle)
            //   {
            //   case StyleLightBlue:
            //   case StyleTranslucidLightBlue:
            //      return argb(255, 116, 160, 220);
            //   case StyleTranslucidWarmGray:
            //      return argb(255, 190, 184, 177);
            //      break;
            //   case StyleDarkWarmBlue:
            //      return argb(255, 34, 54, 75);
            //      break;
            //   case StyleBlackBorder:
            //      return rgb(116, 160, 220) | 0xff000000;
            //   case StyleLightGreen:
            //   case StyleTranslucidLightGreen:
            //      return rgb(116, 220, 160) | 0xff000000;
            //   case StyleRedOrange:
            //      return rgb(255, 170, 136) | 0xff000000;
            //   case StyleBlueRedPurple:
            //      return rgb(200, 100, 220) | 0xff000000;
            //   case StyleEveningSun:
            //      return rgb(255, 210, 100) | 0xff000000;
            //   case StyleTranslucidWarmLiteGray:
            //      return rgb(239, 230, 219) | 0xff000000;
            //   default:
            //      return rgb(200, 100, 220) | 0xff000000;
            //   }


            //   // Light Green/Translucid Light Green
            //   return rgb(116, 220, 160) | 0xff000000;

            //}


            //bool frame::is_translucid_style(e_style estyle)
            //{

            //   return
            //   estyle == StyleTranslucidWarmGray
            //   || estyle == StyleTranslucidLightBlue
            //   || estyle == StyleTranslucidLightGreen
            //   || estyle == StyleTranslucidWarmLiteGray;


            //}


            void frame::Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectParam, enum_border eborder, color32_t crTopLeft, color32_t crBottomRight)
            {

               ::rectangle_i32 rectangle(rectParam);
               i32 x = rectangle.left;
               i32 y = rectangle.top;
               i32 cx = rectangle.width();
               i32 cy = rectangle.height();



               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

               ::draw2d::pen_pointer pen;

               if (eborder & e_border_top || eborder & e_border_left)
               {

                  pen.create(this);

                  pen->create_solid(1.0, crTopLeft);

                  pgraphics->set(pen);

               }

               if (eborder & e_border_top)
               {

                  pgraphics->move_to(x, y);

                  pgraphics->line_to(x + cx, y);

               }

               if (eborder & e_border_left)
               {

                  pgraphics->move_to(x, y);

                  pgraphics->line_to(x, y + cy);

               }

               if ((eborder & e_border_right || eborder & e_border_bottom) && (pen.is_null() || pen->m_color != crBottomRight))
               {

                  pen.create(this);

                  pen->create_solid(1.0, crBottomRight);

                  pgraphics->set(pen);

               }

               if (eborder & e_border_right)
               {

                  pgraphics->move_to(x + cx, y);

                  pgraphics->line_to(x + cx, y + cy);

               }

               if (eborder & e_border_bottom)
               {

                  pgraphics->move_to(x, y + cy);

                  pgraphics->line_to(x + cx, y + cy);

               }

            }



       /*     void frame::on_style_change()
            {


            }*/


            void frame::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
            {

               if (!m_pframewindow->is_frame_experience_enabled())
               {

                  return;

               }

               auto psession = Session;

               pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

               auto pframewindow = m_pframewindow;

               if (!pframewindow->layout().is_full_screen() && !pframewindow->layout().is_zoomed() && !pframewindow->layout().is_iconic() && !m_pframewindow->frame_is_transparent() && m_pframewindow->m_bShowControlBox)
               {

                  on_draw_frame(pgraphics);

               }

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

               if (pframewindow->layout().is_minimal())
               {

                  ::rectangle_i32 rectIcon;

                  if (get_element_rect(rectIcon, ElementTopLeftIcon))
                  {

                     ::draw2d::icon * picon = m_pframewindow->m_picon;

                     if (picon != nullptr)
                     {

                        pgraphics->draw(rectIcon, picon);

                     }

                  }

                  ::rectangle_i32 rectGrip;

                  if (get_element_rect(rectGrip, ElementMoveGripMinimal))
                  {

                     int i = 0;

                     while (i < rectGrip.width() - 5 + 1)
                     {

                        pgraphics->draw_3drect(::rect_dim(rectGrip.left + i, rectGrip.top, 3, rectGrip.height()), argb(110, 230, 230, 230), argb(110, 130, 130, 130));

                        i += 5;

                     }

                     //pgraphics->Draw3dRect(rectGrip.left + 12,rectGrip.top,3,rectGrip.height(),argb(190, 255, 255, 255),argb(190, 90, 90, 90));

                  }

               }
               else if (!pframewindow->layout().is_full_screen() && !m_pframewindow->frame_is_transparent())
               {

                  if (m_pframewindow->is_active() && m_colorActiveCaptionTextBk.is_set())
                  {

                     pgraphics->fill_rect(m_rectCaption, m_colorActiveCaptionTextBk);

                  }
                  else
                  {

                     pgraphics->fill_rect(m_rectCaption, m_colorCaptionTextBk);

                  }

                  ::rectangle_i32 rectIcon;

                  auto pframewindow = m_pframewindow;

                  color32_t    crMoveableBorder;

                  color32_t    crMoveableBorderHilight;

                  color32_t    crMoveableBorderShadow;

                  string str;

                  pframewindow->get_window_text(str);

                  if (pframewindow->m_fActive)
                  {

                     crMoveableBorder = m_colorMoveableBorder;

                     crMoveableBorderHilight = m_colorMoveableBorderHilight;

                     crMoveableBorderShadow = m_colorMoveableBorderShadow;

                  }
                  else
                  {
                  auto psession = Session;

                  auto pstyle = pframewindow->get_style(pgraphics);

                  crMoveableBorder = pframewindow->get_color(pstyle, ::user::e_element_button_background);

                  crMoveableBorderHilight = pframewindow->get_color(pstyle, ::user::e_element_button_hilite);

                  crMoveableBorderShadow = pframewindow->get_color(pstyle, ::user::e_element_button_shadow);

}

                  ::rectangle_i32 rectangle;

                  

                  pframewindow->get_window_rect(rectangle);

                  rectangle_i32 -= rectangle.top_left();

                  if (get_element_rect(rectIcon, ElementTopLeftIcon))
                  {

                     ::draw2d::icon * picon = m_pframewindow->m_picon;

                     if (picon != nullptr)
                     {

                        pgraphics->draw(rectIcon, picon);

                     }

                  }

                  //class font_department & fonts = System.draw2d().fonts();
                  
                  auto pstyle = pframewindow->get_style(pgraphics);

                  string wstrWindowText;

                  pframewindow->get_window_text(wstrWindowText);

                  ::draw2d::brush_pointer brushText(e_create);

                  brushText->create_solid(m_colorCaptionText);

                  pgraphics->set(brushText);

                  pgraphics->set(pframewindow->get_font(pstyle));

                  pgraphics->draw_text(wstrWindowText, m_rectWindowText, e_align_left_center, e_draw_text_no_prefix);

               }


            }


            void frame::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
            {

               UNREFERENCED_PARAMETER(pgraphics);

            }


            bool frame::is_control_box_moveable()
            {

               return false;

            }




            void frame::GetFrameRect(rectangle_i32 * prectangle)
            {

               m_pframewindow->get_window_rect(prectangle);

               prectangle->offset(-prectangle->top_left());

               prectangle->deflate(10,10);

            }



         } // namespace anthill


   } // namespace experience




