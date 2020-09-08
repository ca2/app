#include "framework.h"


namespace experience
{


   namespace tranquillum
   {


      frame::frame() :
         m_penText1(e_create),
         m_penFace1(e_create),
         m_penHilight1(e_create),
         m_penShadow1(e_create),
         m_penDkShadow1(e_create)
      {
         m_crActiveCaptionTextBk = 0;
         m_rectControlBoxMarginNormal = nullptr;

         m_rectMarginNormal.set(5, 5, 5, 5);

         m_crCaptionText = ARGB(255, 255, 255, 255);

         m_rectClient = nullptr;

         //               m_iMargin = 7;

         //class font_department & fonts = System.draw2d().fonts();

         //
         //fonts.GetCaptionFont()->create_point_font("MS Sans Serif", 9.0);

         

         //create_point_font(::user::font_button, "MS Sans Serif", 9.0);
         //create_point_font(::user::font_window_title, "MS Sans Serif", 12.0);

         //m_fontEdit->m_etextrenderinghint = ::draw2d::text_rendering_hint_anti_alias_grid_fit;
         //m_fontList->m_etextrenderinghint = ::draw2d::text_rendering_hint_anti_alias_grid_fit;
         //m_fontButton->m_etextrenderinghint = ::draw2d::text_rendering_hint_anti_alias_grid_fit;
         //m_fontCaption->m_etextrenderinghint = ::draw2d::text_rendering_hint_anti_alias_grid_fit;

      }

      frame::~frame()
      {

      }


      void frame::_001OnBeforeMove(const ::rect & rect)
      {

      }


      void frame::OnMove(__pointer(::user::interaction) pframewindow)
      {

         UNREFERENCED_PARAMETER(pframewindow);

      }


      void frame::Glass(::draw2d::graphics_pointer & pgraphics, const rect & rect)
      {

         //auto pframewindow = m_pframewindow;

         //class imaging & imaging = System.imaging();

         ::rect rectClient(rect);

         ::rect rectInflate;

         if (rectClient.area() <= 0)
         {

            return;

         }

         return;

         //i32 iInflate = 5; // raio 2 pixels + centro 1 pixel

         //rectInflate = rectClient;
         //rectInflate.inflate(iInflate, iInflate);

         ////__pointer(::user::interaction) pwndDesktop = System.get_desktop_window();

         //::rect rectScreen;

         //pframewindow->best_monitor(rectScreen);

         //::image_pointer pimage;

         //::image_pointer pimage2;

         //pimage = create_image({rectClient.width() + iInflate * 2,  rectClient.height() + iInflate * 2});

         //pimage2 = create_image({rectClient.width() + iInflate * 2,  rectClient.height() + iInflate * 2});
         //::rect rectWindow = rectClient;
         //pframewindow->_001ClientToScreen(rectWindow);
         ////pimage = create_image({rectClient.width(),  rectClient.height()});
         //bool b = pimage2->get_graphics()->BitBlt(0, 0, rectClient.width() + iInflate * 2, rectClient.height() + iInflate * 2, pgraphics, rectClient.left - iInflate, rectClient.top - iInflate, SRCCOPY);
         ////bool b = ::BitBlt(dc2, 0, 0, rectClient.width() + iInflate * 2, rectClient.height() + iInflate * 2, hdcScreen, rectClient.left - iInflate, rectClient.top - iInflate, SRCCOPY);
         //b = imaging.blur(pimage->g(), ::point(),
         //                 size(rectClient.width() + iInflate * 2, rectClient.height() + iInflate * 2),
         //                 pimage2->get_graphics(), ::point(), 2);

         ////spgraphics->Draw3dRect(rectClient, 127 << 24, 127 << 24);
         ////rectClient.deflate(1, 1);
         ////spgraphics->Draw3dRect(rectClient, 64 << 24, 64 << 24);
         ////b = imaging.bitmap_blend(pgraphics, prect->left, prect->top,

         //rectWindow.width(),
         //rectWindow.height(),
         //&spgraphics,
         //iInflate, iInflate, 128);*/
         ///*BLENDFUNCTION bf;
         //bf.AlphaFormat = AC_SRC_ALPHA;
         //bf.BlendOp     = AC_SRC_OVER;
         //bf.BlendFlags = 0;
         //bf.SourceConstantAlpha = 255;
         //::alpha_blend(pgraphics->get_handle1(),
         //prect->left, prect->top,

         //rectWindow.width(),
         //rectWindow.height(),
         //spgraphics->get_handle1(),
         //0, 0,
         //rectWindow.width(),
         //rectWindow.height(),
         //bf);*/

         //pgraphics->BitBlt(rectClient.left, rectClient.top, rectClient.width(), rectClient.height(), pimage->g(), iInflate, iInflate, SRCCOPY);

      }

      COLORREF frame::get_border_main_body_color()
      {
         return ARGB(255, 63, 150, 106);
      }

      //::user::front_end_schema * frame::get_user_front_end_schema()
      //{

      //   return &m_schema;

      //}


      void frame::ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rect & rect, COLORREF cr, BYTE bAlpha)

      {

         /*Gdiplus::Graphics g((HDC) pgraphics->get_os_data());
         g.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
         Gdiplus::SolidBrush solidBrush(Gdiplus::Color(bAlpha, colorref_get_r_value(cr), colorref_get_g_value(cr), colorref_get_b_value(cr)));
         g.FillRectangle(&solidBrush, prect->left, prect->top, prect->right - prect->left, prect->bottom - prect->top);*/


         System.imaging().color_blend(pgraphics, rect, cr, bAlpha);


      }




      void frame::set_style(e_style estyle)
      {

         m_estyle = estyle;

         if (get_control_box().is_null())
            return;

         on_style_change();

      }


      void frame::set_style(const char * pszStyle)
      {

         ::experience::frame::set_style(pszStyle);

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


      frame::e_element operator++(frame::e_element & eelement, i32 i)
      {
         UNREFERENCED_PARAMETER(i);
         return (frame::e_element) (*((i32*)&eelement))++;
      }

      bool frame::get_element_rect(RECT * prect, e_element eelement)

      {
         switch (eelement)
         {
         case ElementTopLeftIcon:

            if (m_pframewindow == nullptr || m_pframewindow->m_picon == nullptr)
               return false;

            prect->left = m_pointWindowIcon.x;

            prect->top = m_pointWindowIcon.y;

            //prect->right = prect->left + m_pframewindow->m_picon->get_size().cx;

            //prect->bottom = prect->top + m_pframewindow->m_picon->get_size().cy;

            prect->right = prect->left + 24;

            prect->bottom = prect->top + 24;


            return true;

         case ElementMoveGripMinimal:

            if (m_pframewindow == nullptr || m_pframewindow->layout().design().display() != ::display_minimal)
               return false;

            prect->left = m_pointMoveGripMinimal.x + 2;

            prect->top = m_pointMoveGripMinimal.y + 2;

            prect->right = prect->left + get_control_box_rect()->height() - 4;

            prect->bottom = prect->top + get_control_box_rect()->height() - 4;


            return true;

         default:
            break;
         }
         return false;

      }

      bool frame::hit_test(const point &point, e_element &eelementParam)
      {
         ::rect rect;
         for (e_element eelement = (e_element)(ElementNone + 1);
               eelement < ElementEnd;
               eelement++)
         {
            get_element_rect(rect, eelement);
            if (rect.contains(point))
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

         ///defer_create_user_schema(::user::schema_button);

         //COLORREF crBase = crMoveableBorder;

         //color ca;

         //ca.set_rgb(crBase);
         //ca.hls_rate(0.0, -0.49, -0.49);
         //create_color(color_border, ca.get_rgb() | (0xff << 24));

         //ca.set_rgb(crBase);
         //ca.hls_rate(0.0, -0.11, -0.11);
         //create_color(color_background, ca.get_rgb() | (0xff << 24));

         //ca.set_rgb(crBase);
         //ca.hls_rate(0.0, -0.49, -0.49);
         //create_color(color_text_normal, ca.get_rgb() | (0xff << 24));




         //ca.set_rgb(crBase);
         //ca.hls_rate(0.0, -0.45, 0.11);
         //create_color(color_border_hover, ca.get_rgb() | (0xff << 24));

         //ca.set_rgb(crBase);
         //ca.hls_rate(0.0, 0.33, 0.0);
         //create_color(color_background_hover, ca.get_rgb() | (0xff << 24));

         //ca.set_rgb(crBase);
         //ca.hls_rate(0.0, -0.55, 0.11);
         //create_color(color_text_hover, ca.get_rgb() | (0xff << 24));

      }



      void frame::set_frame_color_system_default_001()
      {

         m_penText1->create_solid(1, ARGB(255, 255, 255, 255));
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

         if (m_estyle == StyleTranslucidWarmGray || m_estyle == StyleDarkWarmBlue)
         {
            pcontrolbox->m_crBackground = m_crCaptionTextBk;
         }



      }

      COLORREF frame::get_style_moveable_border_color(e_style estyle)
      {
         switch (m_estyle)
         {
         case StyleLightBlue:
         case StyleTranslucidLightBlue:
            return ARGB(255, 116, 160, 220);
         case StyleTranslucidWarmGray:
            return ARGB(255, 184, 184, 177);
            break;
         case StyleDarkWarmBlue:
            return ARGB(255, 34, 54, 75);
            break;
         case StyleBlackBorder:
            return RGB(116, 160, 220) | 0xff000000;
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
         default:
            return RGB(200, 100, 220) | 0xff000000;
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


      void frame::Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const rect & rectParam, e_border eborder, COLORREF crTopLeft, COLORREF crBottomRight)
      {

         ::rect rect(rectParam);
         i32 x = rect.left;
         i32 y = rect.top;
         i32 cx = rect.width();
         i32 cy = rect.height();



         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         ::draw2d::pen_pointer pen;

         if (eborder & border_top || eborder & border_left)
         {

            pen.create(this);

            pen->create_solid(1.0, crTopLeft);

            pgraphics->set(pen);

         }

         if (eborder & border_top)
         {

            pgraphics->move_to(x, y);

            pgraphics->line_to(x + cx, y);

         }

         if (eborder & border_left)
         {

            pgraphics->move_to(x, y);

            pgraphics->line_to(x, y + cy);

         }

         if ((eborder & border_right || eborder & border_bottom) && (pen.is_null() || pen->m_color != crBottomRight))
         {

            pen.create(this);

            pen->create_solid(1.0, crBottomRight);

            pgraphics->set(pen);

         }

         if (eborder & border_right)
         {

            pgraphics->move_to(x + cx, y);

            pgraphics->line_to(x + cx, y + cy);

         }

         if (eborder & border_bottom)
         {

            pgraphics->move_to(x, y + cy);

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

         pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

         if (!m_pframewindow->layout().is_full_screen()
            && !m_pframewindow->layout().is_zoomed()
            && !m_pframewindow->layout().is_iconic()
            && !m_pframewindow->frame_is_transparent()
            && m_pframewindow->m_bShowControlBox)
         {

            tick tick1;

            tick1.Now();

            on_draw_frame(pgraphics);

            //printf("A. frame::on_draw_frame %d\n", tick1.elapsed().m_i);

         }

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         if (m_pframewindow->layout().is_minimal())
         {

            ::rect rectIcon;

            tick tick2;

            tick2.Now();

            if (get_element_rect(rectIcon, ElementTopLeftIcon))
            {

               ::draw2d::icon * picon = m_pframewindow->m_picon;

               if (picon != nullptr)
               {

                  pgraphics->DrawIcon(rectIcon.left, rectIcon.top, picon, rectIcon.width(), rectIcon.height(), 0, nullptr, DI_NORMAL);

               }

            }

            //printf("B. frame::on_draw_frame %d\n", tick2.elapsed().m_i);

            tick tick3;

            tick3.Now();

            ::rect rectGrip;

            if (get_element_rect(rectGrip, ElementMoveGripMinimal))
            {

               int i = 0;

               while (i < rectGrip.width() - 5 + 1)
               {

                  pgraphics->draw_3drect_dim(rectGrip.left + i, rectGrip.top, 3, rectGrip.height(), ARGB(110, 230, 230, 230), ARGB(110, 130, 130, 130));

                  i += 5;

               }

               //pgraphics->Draw3dRect(rectGrip.left + 12,rectGrip.top,3,rectGrip.height(),ARGB(184,255,255,255),ARGB(184,84,84,84));

            }

            //printf("C. frame::on_draw_frame %d\n", tick3.elapsed().m_i);

         }
         else if (!m_pframewindow->layout().is_full_screen() && !m_pframewindow->frame_is_transparent() && m_pframewindow->m_bShowControlBox)
         {

            tick tick2;

            tick2.Now();

            //oswindow hwndDraw = m_pframewindow->get_handle();

            //oswindow hwndActiveWindow = get_active_window();

            //oswindow hwndActiveWindowOwner = ::GetWindow(hwndActiveWindow, GW_OWNER);

            //oswindow hwndActiveWindowParent = ::GetParent(hwndActiveWindow);

            //::user::interaction * puiInactive = m_pframewindow;

            //::user::interaction * puiInactiveTopLevel = nullptr;

            //if (puiInactive != nullptr)
            //{

            //   puiInactiveTopLevel = puiInactive->GetTopLevelOwner();

            //   if (puiInactiveTopLevel == nullptr)
            //   {

            //      puiInactiveTopLevel = puiInactive;

            //   }

            //}

            //::user::interaction_impl * puiImplActive = oswindow_get(hwndActiveWindow);

            //::user::interaction * puiActive = nullptr;

            //::user::interaction * puiActiveTopLevel = nullptr;

            //if (puiImplActive != nullptr)
            //{

            //   puiActive = puiImplActive->m_puserinteraction;

            //   if (puiActive != nullptr)
            //   {

            //      puiActiveTopLevel = puiActive->GetTopLevelOwner();

            //      if (puiActiveTopLevel == nullptr)
            //      {

            //         puiActiveTopLevel = puiActive;

            //      }

            //   }

            //}

            /*  if ((hwndDraw == hwndActiveWindow
                  || hwndDraw == hwndActiveWindowOwner
                  || hwndDraw == hwndActiveWindowParent
                  || puiInactiveTopLevel == puiActiveTopLevel)
                  && m_crActiveCaptionTextBk != 0)*/
            if(m_pframewindow->is_active())
            {

               pgraphics->fill_rect(m_rectCaptionTextBk, m_crActiveCaptionTextBk);

            }
            else
            {


               pgraphics->fill_rect(m_rectCaptionTextBk, m_crCaptionTextBk);

            }

            //printf("D. frame::on_draw_frame %d\n", tick2.elapsed().m_i);

            tick tick3;

            tick3.Now();

            ::rect rectIcon;

            auto pframewindow = m_pframewindow;

            COLORREF    crMoveableBorder;

            COLORREF    crMoveableBorderHilight;

            COLORREF    crMoveableBorderShadow;

            string str;

            pframewindow->get_window_text(str);

            if (pframewindow->is_active())
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

            //printf("E. frame::on_draw_frame %d\n", tick3.elapsed().m_i);

            tick tick4;

            tick4.Now();

            ::rect rect;

            m_pframewindow->get_window_rect(rect);

            rect -= rect.top_left();

            if (get_element_rect(rectIcon, ElementTopLeftIcon))
            {

               ::draw2d::icon * picon = m_pframewindow->m_picon;

               if (picon != nullptr)
               {

                  pgraphics->DrawIcon(rectIcon.left, rectIcon.top, picon, rectIcon.width(), rectIcon.height(), 0, nullptr, DI_NORMAL);

               }

            }

            //printf("F. frame::on_draw_frame %d\n", tick4.elapsed().m_i);

            //class font_department & fonts = System.draw2d().fonts();

            tick tick5;

            tick5.Now();

            string wstrWindowText;

            pframewindow->get_window_text(wstrWindowText);

            ::draw2d::brush_pointer brushText(e_create);

            brushText->create_solid(m_crCaptionText);

            pgraphics->set(brushText);

            pgraphics->set_font(pframewindow, ::user::element_window_title);

            pgraphics->draw_text(wstrWindowText, m_rectWindowText, DT_LEFT | DT_VCENTER | DT_NOPREFIX);

            //printf("G. frame::on_draw_frame %d\n", tick5.elapsed().m_i);

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




      void frame::GetFrameRect(rect * prect)
      {

         m_pframewindow->get_window_rect(prect);

         prect->offset(-prect->top_left());

         prect->deflate(*get_margin_rect());

      }


   } // namespace tranquillum


} // namespace experience



