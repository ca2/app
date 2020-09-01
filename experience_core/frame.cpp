#include "framework.h"


namespace experience
{


   namespace aura
   {


            frame::frame() :
               m_penText1(e_create),
               m_penFace1(e_create),
               m_penHilight1(e_create),
               m_penShadow1(e_create),
               m_penDkShadow1(e_create)
            {

               m_estyle = StyleLightBlue;

               m_strStyle = "TranslucidWarmLiteGray";

               m_crCaptionText = ARGB(255, 0, 0, 0);

               m_rectClient.set(0, 0, 0, 0);

            }


            frame::~frame()
            {

            }


            void frame::on_initialize_experience_frame()
            {

               auto estyle = translate_style(m_strStyle);

               set_style(estyle);

            }



//            void frame::_001OnBeforeMove(const ::rect & rect)
//            {
//
//               update_window_region(rect);
//
//            }


            //void frame::_001OnBeforeSize(const ::rect & rect)
            //{

            //   UNREFERENCED_PARAMETER(rect);

            //}


            void frame::OnMove(__pointer(::user::interaction) pframewindow)
            {

               UNREFERENCED_PARAMETER(pframewindow);

            }


            void frame::Glass(::draw2d::graphics_pointer & pgraphics, const ::rect & rectParam)
            {

               auto pframewindow = m_pframewindow;

               auto imaging = System.imaging();

               ::rect rectClient(rectParam);

               ::rect rectInflate;

               if(rectClient.is_empty())
               {

                  return;

               }



               i32 iInflate = 5; // raio 2 pixels + centro 1 pixel

               rectInflate = rectClient;
               rectInflate.inflate(iInflate, iInflate);

               //__pointer(::user::interaction) pwndDesktop = System.get_desktop_window();

               ::rect rectScreen;

               pframewindow->best_monitor(rectScreen);

               ::image_pointer pimage1;

               ::image_pointer pimage2;

               pimage1 = create_image({rectClient.width() + iInflate * 2,  rectClient.height() + iInflate * 2});

               pimage2 = create_image({rectClient.width() + iInflate * 2,  rectClient.height() + iInflate * 2});

               ::rect rectWindow = rectClient;

               pframewindow->_001ClientToScreen(rectWindow);

               ::point pointInflate(iInflate, iInflate);

               auto point = rectClient.top_left();

               point -= pointInflate;

               bool b = pimage2->g()->draw(::rect(pimage1->get_size()), pgraphics, point, SRCCOPY);

               b = imaging.blur(pimage2, 2);

               //spgraphics->draw3d_rect(rectClient, 127 << 24, 127 << 24);
               //rectClient.deflate(1, 1);
               //spgraphics->draw3d_rect(rectClient, 64 << 24, 64 << 24);
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

               pgraphics->draw(rectClient, pimage2->g(), pointInflate, SRCCOPY);

            }


            COLORREF frame::get_border_main_body_color()
            {

               return RGB(63, 150, 106);

            }


            void frame::ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rect & rect, COLORREF cr, BYTE bAlpha)
            {

               /*Gdiplus::Graphics g((HDC) pgraphics->get_os_data());
               g.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
               Gdiplus::SolidBrush solidBrush(Gdiplus::Color(bAlpha, colorref_get_r_value(cr), colorref_get_g_value(cr), colorref_get_b_value(cr)));
               g.fill_rect(&solidBrush, lprect->left, lprect->top, lprect->right - lprect->left, lprect->bottom - lprect->top);*/

               System.imaging().color_blend(pgraphics, rect, cr, bAlpha);

            }




            void frame::set_style(e_style estyle)
            {

               m_estyle = estyle;

               if(get_control_box().is_null())
                  return;

               on_style_change();

            }


            frame::e_style frame::translate_style(const char * pszStyle)
            {

               string strStyle(pszStyle);

               if(strStyle == "TranslucidLightBlue")
               {
                  return StyleTranslucidLightBlue;
               }
               else if (strStyle == "TranslucidLightGreen")
               {
                  return StyleTranslucidLightGreen;
               }
               else if (strStyle == "TranslucidWarmGray")
               {
                  return StyleTranslucidWarmGray;
               }
               else if (strStyle == "TranslucidWarmLiteGray")
               {
                  return StyleTranslucidWarmLiteGray;
               }
               else if(strStyle == "DarkWarmBlue")
               {
                  return StyleDarkWarmBlue;
               }
               else if(strStyle == "WarmGray")
               {
                  return StyleTranslucidWarmGray;
               }
               else if(strStyle == "BlueRedPurple")
               {
                  return StyleBlueRedPurple;
               }
               else if(strStyle == "RedOrange")
               {
                  return StyleRedOrange;
               }
               else if(strStyle == "LightBlue")
               {
                  return StyleLightBlue;
               }
               else if (strStyle == "BlackBorder")
               {
                  return StyleBlackBorder;
               }
               else if (strStyle == "LightGreen")
               {
                  return StyleLightGreen;
               }
               else if (strStyle == "EveningSun")
               {
                  return StyleEveningSun;
               }
               else if (strStyle == "BlackPiano")
               {
                  return StyleBlackPiano;
               }
               else
               {
                  return StyleLightBlue;
               }

            }


            frame::e_element operator++(frame::e_element & eelement, i32 i)
            {
               UNREFERENCED_PARAMETER(i);
               return (frame::e_element) (*((i32*)&eelement))++;
            }

            bool frame::get_element_rect(LPRECT lprect, e_element eelement)
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

                  if (m_pframewindow == nullptr || m_pframewindow->display_state() != ::display_minimal)
                  {
                   
                     return false;

                  }

                  lprect->left = m_pointMoveGripMinimal.x + 2;
                  lprect->top = m_pointMoveGripMinimal.y + 2;
                  lprect->right = lprect->left + get_control_box_rect()->height() - 4;
                  lprect->bottom = lprect->top + get_control_box_rect()->height() - 4;

                  return true;

               default:
                  break;
               }
               return false;

            }

            bool frame::_001HitTest(const POINT &point, e_element &eelementParam)
            {
               ::rect rect;
               for(e_element eelement = (e_element)(ElementNone + 1);
                     eelement < ElementEnd;
                     eelement++)
               {
                  get_element_rect(rect, eelement);
                  if(rect.contains(point))
                  {
                     eelementParam = eelement;
                     return true;
                  }
               }
               return false;
            }


            void frame::set_moveable_border_color(COLORREF cr)
            {
               m_crMoveableBorder = cr;

               color color;

               color.set_rgb(cr);
               color.hls_rate(0.0, 0.5, 0.0);
               m_crMoveableBorderHilight = color.get_rgb() | (0xff << 24);

               color.set_rgb(cr);
               color.hls_rate(0.0, -0.3, 0.0);
               m_crMoveableBorderShadow = color.get_rgb() | (0xff << 24);

               color.set_rgb(cr);
               color.hls_rate(8.0, -0.8, 0.0);
               m_crMoveableBorderDkShadow = color.get_rgb() | (0xff << 24);


               m_crCaptionTextBk = m_crMoveableBorderShadow;

            }


            void frame::set_button_color_schema_001(COLORREF crMoveableBorder)
            {

//               defer_create_user_schema(schema_button);

//               COLORREF crBase = crMoveableBorder;
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

               m_penText1->create_solid(1, Session.get_default_color(COLOR_BTNTEXT) | 0xff000000);
               m_penFace1->create_solid(1, Session.get_default_color(COLOR_BTNFACE) | 0xff000000);
               m_penHilight1->create_solid(1, Session.get_default_color(COLOR_BTNHILIGHT) | 0xff000000);
               m_penShadow1->create_solid(1, Session.get_default_color(COLOR_BTNSHADOW) | 0xff000000);
               m_penDkShadow1->create_solid(1, Session.get_default_color(COLOR_3DDKSHADOW) | 0xff000000);
               m_crDkShadow = Session.get_default_color(COLOR_3DDKSHADOW);
               m_crFrameBorder = RGB(0, 0, 0) | 0xff000000;


            }


            void frame::on_style_change_001_and_002()
            {


               auto pcontrolbox = get_control_box();


               m_minSize = size(144, 48);
               m_minSize.cy = 48;
               pcontrolbox->set_button_color_system_default_001();
               set_frame_color_system_default_001();
               set_moveable_border_color(get_style_moveable_border_color(m_estyle));

               set_button_color_schema_001(m_crMoveableBorder);

               if(m_estyle == StyleTranslucidWarmGray || m_estyle == StyleDarkWarmBlue)
               {

                  pcontrolbox->m_crBackground = m_crCaptionTextBk;
                  m_crCaptionText = ARGB(255, 255, 255, 255);

               }
               else if (m_estyle == StyleBlackPiano || m_estyle == StyleBlackBorder)
               {

                  pcontrolbox->m_crBackground = m_crCaptionTextBk;
                  m_crCaptionText = ARGB(255, 255, 255, 255);

               }


            }

            COLORREF frame::get_style_moveable_border_color(e_style estyle)
            {
               switch(m_estyle)
               {
               case StyleLightBlue:
               case StyleTranslucidLightBlue:
                  return RGB(116, 160, 220);
               case StyleBlackPiano:
               case StyleBlackBorder:
                  return RGB(0, 0, 0);
               case StyleTranslucidWarmGray:
                  return ARGB(255, 190, 184, 177);
                  break;
               case StyleDarkWarmBlue:
                  return ARGB(255,34,54,75);
                  break;
               case StyleLightGreen:
               case StyleTranslucidLightGreen:
                  return RGB(116, 220, 160) | 0xff000000;
               case StyleRedOrange:
                  return RGB(255, 170, 136) | 0xff000000;
               case StyleBlueRedPurple:
                  return RGB(200, 100, 220) | 0xff000000;
               case StyleEveningSun:
                  return RGB(255, 210, 100) | 0xff000000;
               case StyleTranslucidWarmLiteGray:
                  return RGB(239, 230, 219) | 0xff000000;
               }


               // Light Green/Translucid Light Green
               return RGB(116, 220, 160) | 0xff000000;

            }


            bool frame::is_translucid_style(e_style estyle)
            {

               return
               estyle == StyleTranslucidWarmGray
               || estyle == StyleTranslucidLightBlue
               || estyle == StyleTranslucidLightGreen
               || estyle == StyleTranslucidWarmLiteGray;


            }


            void frame::Draw3dRectSide(::draw2d::graphics_pointer & pgraphics,const ::rect & rectParam,e_border eborder,COLORREF crTopLeft,COLORREF crBottomRight)
            {

               ::rect rect(rectParam);
               i32 x = rect.left;
               i32 y = rect.top;
               i32 cx = rect.width();
               i32 cy = rect.height();



               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

               ::draw2d::pen_pointer pen;

               if(eborder & border_top || eborder & border_left)
               {

                  pen.create(this);

                  pen->create_solid(1.0,crTopLeft);

                  pgraphics->set(pen);

               }

               if(eborder & border_top)
               {

                  pgraphics->move_to(x,y);

                  pgraphics->line_to(x + cx,y);

               }

               if(eborder & border_left)
               {

                  pgraphics->move_to(x,y);

                  pgraphics->line_to(x,y+cy);

               }

               if((eborder & border_right || eborder & border_bottom) && (pen.is_null() || pen->m_color != crBottomRight))
               {

                  pen.create(this);

                  pen->create_solid(1.0,crBottomRight);

                  pgraphics->set(pen);

               }

               if(eborder & border_right)
               {

                  pgraphics->move_to(x + cx,y);

                  pgraphics->line_to(x + cx,y + cy);

               }

               if(eborder & border_bottom)
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

               pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

               auto pframewindow = m_pframewindow;

               if(!pframewindow->window_is_full_screen() && !pframewindow->window_is_zoomed() && !pframewindow->window_is_iconic() && !m_pframewindow->frame_is_transparent() && m_pframewindow->m_bShowControlBox)
               {

                  on_draw_frame(pgraphics);

               }

               if(pframewindow->window_is_minimal())
               {

                  ::rect rectIcon;

                  if(get_element_rect(rectIcon,ElementTopLeftIcon))
                  {

                     ::draw2d::icon * picon = m_pframewindow->m_picon;

                     if(picon != nullptr)
                     {

                        pgraphics->DrawIcon(rectIcon.left,rectIcon.top,picon,rectIcon.width(),rectIcon.height(),0,nullptr,DI_NORMAL);

                     }

                  }

                  ::rect rectGrip;

                  if(get_element_rect(rectGrip,ElementMoveGripMinimal))
                  {

                     int i = 0;

                     while(i < rectGrip.width() - 5 + 1)
                     {

                        pgraphics->draw_3drect_dim(rectGrip.left + i,rectGrip.top,3,rectGrip.height(),ARGB(110,230,230,230),ARGB(110,130,130,130));

                        i += 5;

                     }

                  }

               }
               else if(!pframewindow->window_is_full_screen() && !m_pframewindow->frame_is_transparent())
               {

                  pgraphics->fill_rect(m_rectCaptionTextBk, m_crCaptionTextBk);

                  ::rect rectIcon;

                  auto pframewindow = m_pframewindow;

                  COLORREF    crMoveableBorder;

                  COLORREF    crMoveableBorderHilight;

                  COLORREF    crMoveableBorderShadow;

                  string str;

                  pframewindow->get_window_text(str);

                  if(pframewindow->is_active())
                  {

                     crMoveableBorder = m_crMoveableBorder;

                     crMoveableBorderHilight = m_crMoveableBorderHilight;

                     crMoveableBorderShadow = m_crMoveableBorderShadow;

                  }
                  else
                  {

                     crMoveableBorder = Session.get_default_color(COLOR_BTNFACE);

                     crMoveableBorderHilight = Session.get_default_color(COLOR_BTNHILIGHT);

                     crMoveableBorderShadow = Session.get_default_color(COLOR_BTNSHADOW);

                  }

                  ::rect rect;

                  pframewindow->get_window_rect(rect);

                  rect -= rect.top_left();

                  if(get_element_rect(rectIcon, ElementTopLeftIcon))
                  {

                     ::draw2d::icon * picon = m_pframewindow->m_picon;

                     if(picon != nullptr)
                     {

                        pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

                        pgraphics->DrawIcon(rectIcon.left, rectIcon.top, picon, rectIcon.width(), rectIcon.height(), 0, nullptr, DI_NORMAL);

                     }

                  }

                  string wstrWindowText;

                  pframewindow->get_window_text(wstrWindowText);

                  pgraphics->set_text_color(m_crCaptionText);

                  pgraphics->set_font(pframewindow, ::user::element_window_title);

                  pgraphics->_DrawText(wstrWindowText, m_rectWindowText, DT_LEFT | DT_VCENTER | DT_NOPREFIX);

               }


            }


            void frame::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
            {

               UNREFERENCED_PARAMETER(pgraphics);

            }


   } // namespace aura


} // namespace experience



