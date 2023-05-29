#include "framework.h"





   namespace experience
   {


      


         namespace lite

         {


            frame::frame(::particle * pparticle) :
               object(pparticle),
               ::experience::frame(pparticle),
               //m_schema(pparticle),
               m_ppenText1(e_create),
               m_ppenFace1(e_create),
               m_ppenHilight1(e_create),
               m_ppenShadow1(e_create),
               m_ppenDkShadow1(e_create),
               m_blur1(this)
            {
               m_colorActiveCaptionTextBk = 0;
               m_rectangleControlBoxMarginNormal = ::rectangle_i32();

               m_rectangleMarginNormal.set(5, 5, 5, 5);

               m_colorCaptionText = argb(255, 255, 255, 255);

               m_rectangleClient = ::rectangle_i32();

               //               m_iMargin = 7;


            }

            frame::~frame()
            {

            }


            void frame::_001OnBeforeMove(const ::rectangle_i32 & rectangle)
            {

               update_window_region(rectangle);

            }


            void frame::_001OnBeforeSize(const ::rectangle_i32 & rectangle)
            {

               __UNREFERENCED_PARAMETER(rectangle);

            }





            void frame::OnMove(::pointer<::user::interaction>pframewindow)
            {

               __UNREFERENCED_PARAMETER(pframewindow);

            }


            void frame::Glass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 &lprect)
            {

               auto pframewindow = m_pframewindow;

               //class imaging & imaging = psystem->imaging();

               ::rectangle_i32 rectangleClient(lprect);

               ::rectangle_i32 rectangleInflate;

               if (rectangleClient.area() <= 0)
                  return;



               i32 iInflate = 5; // raio 2 pixels + centro 1 pixel

               rectangleInflate = rectangleClient;
               rectangleInflate.inflate(iInflate, iInflate);

               //::pointer<::user::interaction>puserinteractionDesktop = psystem->get_desktop_window();

               ::rectangle_i32 rectangleScreen;

               pframewindow->best_monitor(rectangleScreen);

               ::image_pointer pimage1;

               ::image_pointer pimage2;

/*               pimage1 = create_image({rectangleClient.width() + iInflate * 2,  rectangleClient.height() + iInflate * 2});

/*               pimage2 = create_image({rectangleClient.width() + iInflate * 2,  rectangleClient.height() + iInflate * 2});
               ::rectangle_i32 rectangleWindow = rectangleClient;
               pframewindow->client_to_screen(rectangleWindow);
/*               //pimage = create_image({rectangleClient.width(),  rectangleClient.height()});
               //bool b = pimage2->get_graphics()->BitBlt(0, 0, rectangleClient.width() + iInflate * 2, rectangleClient.height() + iInflate * 2, pgraphics, rectangleClient.left - iInflate, rectangleClient.top - iInflate);
               pimage2->get_graphics()->BitBlt(0, 0, rectangleClient.width() + iInflate * 2, rectangleClient.height() + iInflate * 2, pgraphics, rectangleClient.left - iInflate, rectangleClient.top - iInflate);
               //bool b = ::BitBlt(dc2, 0, 0, rectangleClient.width() + iInflate * 2, rectangleClient.height() + iInflate * 2, hdcScreen, rectangleClient.left - iInflate, rectangleClient.top - iInflate);

               m_blur1.blur(pimage1, 2, ::rectangle_i32(size(rectangleClient.width() + iInflate * 2, rectangleClient.height() + iInflate * 2)));

               //spgraphics->Draw3dRect(rectangleClient, 127 << 24, 127 << 24);
               //rectangleClient.deflate(1, 1);
               //spgraphics->Draw3dRect(rectangleClient, 64 << 24, 64 << 24);
               /*b = imaging.bitmap_blend(pgraphics, lprect->left, lprect->top,
               rectangleWindow.width(),
               rectangleWindow.height(),
               &spgraphics,
               iInflate, iInflate, 128);*/
               /*BLENDFUNCTION bf;
               bf.AlphaFormat = AC_SRC_ALPHA;
               bf.BlendOp     = AC_SRC_OVER;
               bf.BlendFlags = 0;
               bf.SourceConstantAlpha = 255;
               ::alpha_blend(pgraphics->get_handle1(),
               lprect->left, lprect->top,
               rectangleWindow.width(),
               rectangleWindow.height(),
               spgraphics->get_handle1(),
               0, 0,
               rectangleWindow.width(),
               rectangleWindow.height(),
               bf);*/

               pgraphics->BitBlt(rectangleClient.left, rectangleClient.top, rectangleClient.width(), rectangleClient.height(), pimage1->g(), iInflate, iInflate);

            }

            color32_t frame::get_border_main_body_color()
            {
               return argb(255, 63, 150, 106);
            }

            //::user::front_end_schema * frame::get_user_front_end_schema()
            //{

            //   return &m_schema;

            //}


            void frame::ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 &lprect, color32_t color32, byte bAlpha)
            {

               /*Gdiplus::Graphics g((HDC) pgraphics->get_os_data());
               g.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
               Gdiplus::SolidBrush solidBrush(Gdiplus::Color(bAlpha, colorref_get_r_value(color32), colorref_get_g_value(color32), colorref_get_b_value(color32)));
               g.FillRectangle(&solidBrush, lprect->left, lprect->top, lprect->right - lprect->left, lprect->bottom - lprect->top);*/

               pgraphics->color_blend(lprect, color32, bAlpha);

            }




            void frame::set_style(e_style estyle)
            {

               m_estyle = estyle;

               if (get_control_box().is_null())
                  return;

               on_style_change();

            }


            void frame::set_style(const ::string & pszStyle)
            {

               string strStyle(pszStyle);

               if (strStyle == "TranslucidWarmGray")
               {
                  set_style(StyleTranslucidWarmGray);
               }
               else if (strStyle == "DarkWarmBlue")
               {
                  set_style(StyleDarkWarmBlue);
               }
               else if (strStyle == "WarmGray")
               {
                  set_style(StyleTranslucidWarmGray);
               }
               else if (strStyle == "BlueRedPurple")
               {
                  set_style(StyleBlueRedPurple);
               }
               else if (strStyle == "RedOrange")
               {
                  set_style(StyleRedOrange);
               }
               else if (strStyle == "DarkRed")
               {
                  set_style(StyleDarkRed);
               }
               else if (strStyle == "LightBlue")
               {
                  set_style(StyleLightBlue);
               }
               else if (strStyle == "LightGreen")
               {
                  set_style(StyleLightGreen);
               }


            }


            frame::enum_element operator++(frame::enum_element & eelement, i32 i)
            {
               __UNREFERENCED_PARAMETER(i);
               return (frame::enum_element) (*((i32*)&eelement))++;
            }

            bool frame::get_element_rect(::rectangle_i32 * lprect, enum_element eelement)
            {
               switch (eelement)
               {
               case e_element_top_left_icon:

                  if (m_pframewindow == nullptr || m_pframewindow->m_picon == nullptr)
                     return false;

                  lprect->left = m_pointWindowIcon.x();
                  lprect->top = m_pointWindowIcon.y();
                  //lprect->right = lprect->left + m_pframewindow->m_picon->get_size().cx();
                  //lprect->bottom = lprect->top + m_pframewindow->m_picon->get_size().cy();
                  lprect->right = lprect->left + 24;
                  lprect->bottom = lprect->top + 24;

                  return true;

               case e_element_move_grip_minimal:

                  if (m_pframewindow == nullptr || m_pframewindow->get_appearance() != ::e_display_minimal)
                     return false;

                  lprect->left = m_pointMoveGripMinimal.x() + 2;
                  lprect->top = m_pointMoveGripMinimal.y() + 2;
                  lprect->right = lprect->left + get_control_box_rect()->height() - 4;
                  lprect->bottom = lprect->top + get_control_box_rect()->height() - 4;

                  return true;

               default:
                  break;
               }
               return false;

            }

            bool frame::hit_test(const ::point_i32 &point, enum_element &eelementParam)
            {
               ::rectangle_i32 rectangle;
               for (enum_element eelement = (enum_element)(::e_element_none + 1);
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


            void frame::set_moveable_border_color(color32_t color32)
            {
               m_colorMoveableBorder = color32;

               ::color::color color;

               color.set_rgb(color32);
               color.hls_rate(0.0, 0.5, 0.0);
               m_colorMoveableBorderHilight = color.get_rgb() | (0xff << 24);

               color.set_rgb(color32);
               color.hls_rate(0.0, -0.3, 0.0);
               m_colorMoveableBorderShadow = color.get_rgb() | (0xff << 24);

               color.set_rgb(color32);
               color.hls_rate(8.0, -0.8, 0.0);
               m_colorMoveableBorderDkShadow = color.get_rgb() | (0xff << 24);


               m_colorCaptionTextBk = m_colorMoveableBorderShadow;

            }


            void frame::set_button_color_schema_001(color32_t crMoveableBorder)
            {

//               defer_create_user_schema(::user::schema_button);

               color32_t crBase = crMoveableBorder;

               color ca;

               ca.set_rgb(crBase);
               ca.hls_rate(0.0, -0.49, -0.49);
               create_color(color_border, ca.get_rgb() | (0xff << 24));

               ca.set_rgb(crBase);
               ca.hls_rate(0.0, -0.11, -0.11);
               create_color(color_button_background, ca.get_rgb() | (0xff << 24));

               ca.set_rgb(crBase);
               ca.hls_rate(0.0, -0.49, -0.49);
               create_color(color_button_text, ca.get_rgb() | (0xff << 24));




               ca.set_rgb(crBase);
               ca.hls_rate(0.0, -0.45, 0.11);
               create_color(color_border_hover, ca.get_rgb() | (0xff << 24));

               ca.set_rgb(crBase);
               ca.hls_rate(0.0, 0.33, 0.0);
               create_color(color_button_background_hover, ca.get_rgb() | (0xff << 24));

               ca.set_rgb(crBase);
               ca.hls_rate(0.0, -0.55, 0.11);
               create_color(color_button_text_hover, ca.get_rgb() | (0xff << 24));

            }



            void frame::set_frame_color_system_default_001()
            {

               m_ppenText1->create_solid(1, argb(255, 255, 255, 255));
               m_ppenFace1->create_solid(1, crButtonFace | 0xff000000);
               m_ppenHilight1->create_solid(1, crButtonHilite | 0xff000000);
               m_ppenShadow1->create_solid(1, crButtonShadow | 0xff000000);
               m_ppenDkShadow1->create_solid(1, crButtonDarkShadow | 0xff000000);
               m_colorDkShadow = crButtonDarkShadow;
               m_colorFrameBorder = rgb(0, 0, 0) | 0xff000000;


            }


            void frame::on_style_change_001_and_002(::draw2d::graphics_pointer & pgraphics)
            {


               auto pcontrolbox = get_control_box();


               m_minSize = size_i32(144, 48);
               m_minSize.cy() = 48;
               pcontrolbox->set_button_color_system_default_001();
               set_frame_color_system_default_001();
               set_moveable_border_color(get_style_moveable_border_color(m_estyle));

               set_button_color_schema_001(m_colorMoveableBorder);

               if (m_estyle == StyleTranslucidWarmGray || m_estyle == StyleDarkWarmBlue)
               {
                  pcontrolbox->m_colorBackground = m_colorCaptionTextBk;
               }



            }

            color32_t frame::get_style_moveable_border_color(e_style estyle)
            {
               switch (m_estyle)
               {
               case StyleLightBlue:
               case StyleTranslucidLightBlue:
                  return argb(255, 116, 160, 220);
               case StyleTranslucidWarmGray:
                  return argb(255, 184, 184, 177);
                  break;
               case StyleDarkWarmBlue:
                  return argb(255, 34, 54, 75);
                  break;
               case StyleBlackBorder:
                  return rgb(116, 160, 220) | 0xff000000;
               case StyleLightGreen:
               case StyleTranslucidLightGreen:
                  return rgb(116, 220, 160) | 0xff000000;
               case StyleRedOrange:
                  return rgb(255, 170, 136) | 0xff000000;
               case StyleBlueRedPurple:
                  return rgb(200, 100, 220) | 0xff000000;
               case StyleEveningSun:
                  return rgb(255, 210, 100) | 0xff000000;
               case StyleTranslucidWarmLiteGray:
                  return rgb(239, 230, 219) | 0xff000000;
               default:
                  return rgb(200, 100, 220) | 0xff000000;
               }


               // Light Green/Translucid Light Green
               return rgb(116, 220, 160) | 0xff000000;

            }


            bool frame::is_translucid_style(e_style estyle)
            {

               return
               estyle == StyleTranslucidWarmGray
               || estyle == StyleTranslucidLightBlue
               || estyle == StyleTranslucidLightGreen
               || estyle == StyleTranslucidWarmLiteGray;


            }


            void frame::Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleParam, enum_border eborder, color32_t crTopLeft, color32_t crBottomRight)
            {

               ::rectangle_i32 rectangle(rectangleParam);
               i32 x = rectangle.left;
               i32 y = rectangle.top;
               i32 cx = rectangle.width();
               i32 cy = rectangle.height();



               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               ::draw2d::pen_pointer ppen;

               if (eborder & e_border_top || eborder & e_border_left)
               {

                  ppen.create(this);

                  ppen->create_solid(1.0, crTopLeft);

                  pgraphics->SelectObject(pen);

               }

               if (eborder & e_border_top)
               {

                  pgraphics->set_current_point(x, y);

                  pgraphics->line_to(x + cx, y);

               }

               if (eborder & e_border_left)
               {

                  pgraphics->set_current_point(x, y);

                  pgraphics->line_to(x, y + cy);

               }

               if ((eborder & e_border_right || eborder & e_border_bottom) && (pen.is_null() || ppen->m_cr != crBottomRight))
               {

                  ppen.create(this);

                  ppen->create_solid(1.0, crBottomRight);

                  pgraphics->SelectObject(pen);

               }

               if (eborder & e_border_right)
               {

                  pgraphics->set_current_point(x + cx, y);

                  pgraphics->line_to(x + cx, y + cy);

               }

               if (eborder & e_border_bottom)
               {

                  pgraphics->set_current_point(x, y + cy);

                  pgraphics->line_to(x + cx, y + cy);

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

               pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

               appearance * pframewindow = m_pframewindow->get_display();

               if (!pframewindow->layout().is_full_screen() && !pframewindow->layout().is_zoomed() && !pframewindow->layout().is_iconic() && !m_pframewindow->GetWndDraw()->frame_is_transparent())
               {

                  on_draw_frame(pgraphics);

               }

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               if (pframewindow->layout().is_minimal())
               {

                  ::rectangle_i32 rectangleIcon;

                  if (get_element_rect(rectangleIcon, e_element_top_left_icon))
                  {

                     ::draw2d::icon * picon = m_pframewindow->m_picon;

                     if (picon != nullptr)
                     {

                        pgraphics->DrawIcon(rectangleIcon.left, rectangleIcon.top, picon, rectangleIcon.width(), rectangleIcon.height(), 0, nullptr, DI_NORMAL);

                     }

                  }

                  ::rectangle_i32 rectangleGrip;

                  if (get_element_rect(rectangleGrip, e_element_move_grip_minimal))
                  {

                     int i = 0;

                     while (i < rectangleGrip.width() - 5 + 1)
                     {

                        pgraphics->draw3d_rect_dim(rectangleGrip.left + i, rectangleGrip.top, 3, rectangleGrip.height(), argb(84 + 23, 230, 230, 230), argb(84 + 23, 108 + 23, 108 + 23, 108 + 23));

                        i += 5;

                     }

                     //pgraphics->Draw3dRect(rectangleGrip.left + 12,rectangleGrip.top,3,rectangleGrip.height(),argb(184,255,255,255),argb(184,84,84,84));

                  }

               }
               else if (!pframewindow->layout().is_full_screen() && !m_pframewindow->GetWndDraw()->frame_is_transparent())
               {

                  if (m_pframewindow->GetWndDraw()->is_active() && m_colorActiveCaptionTextBk != 0)
                  {

                     pgraphics->fill_rectangle(m_rectangleCaptionTextBk, m_colorActiveCaptionTextBk);

                  }
                  else
                  {

                     pgraphics->fill_rectangle(m_rectangleCaptionTextBk, m_colorCaptionTextBk);

                  }

                  ::rectangle_i32 rectangleIcon;

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
                  auto psession = get_session();

                  auto pstyle = pframewindow->get_style(pgraphics);

                  crMoveableBorder = pframewindow->get_color(pstyle, ::e_element_button_background);

                  crMoveableBorderHilight = pframewindow->get_color(pstyle, ::e_element_button_hilite);

                  crMoveableBorderShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

}

                  ::rectangle_i32 rectangle;

                  auto pframewindow = m_pframewindow;

                  pframewindow->window_rectangle(rectangle);

                  rectangle_i32 -= rectangle.top_left();

                  if (get_element_rect(rectangleIcon, e_element_top_left_icon))
                  {

                     ::draw2d::icon * picon = m_pframewindow->m_picon;

                     if (picon != nullptr)
                     {

                        pgraphics->DrawIcon(rectangleIcon.left, rectangleIcon.top, picon, rectangleIcon.width(), rectangleIcon.height(), 0, nullptr, DI_NORMAL);

                     }

                  }

                  //class fonts & fonts = pdraw2d->fonts();

                  string wstrWindowText;

                  pframewindow->get_window_text(wstrWindowText);

                  auto pbrushText = __create < ::draw2d::brush > ();

                  pbrushText->create_solid(m_colorCaptionText);

                  pgraphics->SelectObject(pbrushText);

                  pgraphics->SelectObject(pframewindow->_001GetFont(::user::font_default));

                  pgraphics->draw_text(wstrWindowText, m_rectangleWindowText, e_align_left_center, e_draw_text_no_prefix);

               }


            }


            void frame::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
            {

               __UNREFERENCED_PARAMETER(pgraphics);

            }


            bool frame::is_control_box_moveable()
            {

               return false;

            }




            void frame::GetFrameRect(rectangle_i32 * prectangle)
            {

               m_pframewindow->GetWndDraw()->window_rectangle(prectangle);

               prectangle->offset(-prectangle->top_left());

               prectangle->deflate(10,10);

            }


         } // namespace lite



      


   } // namespace experience















