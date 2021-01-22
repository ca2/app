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

         m_colorActiveCaptionTextBk = 0;

         m_rectMarginNormal.set(0, 0, 0, 0);

         m_colorCaptionText = ARGB(255, 255, 255, 255);

         m_rectClient = nullptr;

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
         //bool b = pimage2->get_graphics()->BitBlt(0, 0, rectClient.width() + iInflate * 2, rectClient.height() + iInflate * 2, pgraphics, rectClient.left - iInflate, rectClient.top - iInflate);
         ////bool b = ::BitBlt(dc2, 0, 0, rectClient.width() + iInflate * 2, rectClient.height() + iInflate * 2, hdcScreen, rectClient.left - iInflate, rectClient.top - iInflate);
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

         //pgraphics->BitBlt(rectClient.left, rectClient.top, rectClient.width(), rectClient.height(), pimage->g(), iInflate, iInflate);

      }

      
      color32_t frame::get_border_main_body_color()
      {
         //return ARGB(255, 63, 150, 106);

         return m_pframewindow->get_border_main_body_color();

      }


      //::user::front_end_schema * frame::get_user_front_end_schema()
      //{

      //   return &m_schema;

      //}


      void frame::ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rect & rect, color32_t cr, byte bAlpha)

      {

         /*Gdiplus::Graphics g((HDC) pgraphics->get_os_data());
         g.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
         Gdiplus::SolidBrush solidBrush(Gdiplus::Color(bAlpha, colorref_get_r_value(cr), colorref_get_g_value(cr), colorref_get_b_value(cr)));
         g.FillRectangle(&solidBrush, prect->left, prect->top, prect->right - prect->left, prect->bottom - prect->top);*/


         System.imaging().color_blend(pgraphics, rect, cr, bAlpha);


      }




      //void frame::set_style(e_style estyle)
      //{

      //   m_estyle = estyle;

      //   if (get_control_box().is_null())
      //      return;

      //   on_style_change();

      //}


      //}


      frame::enum_element operator++(frame::enum_element & eelement, i32 i)
      {
         UNREFERENCED_PARAMETER(i);
         return (frame::enum_element) (*((i32*)&eelement))++;
      }

      bool frame::get_element_rect(RECT32 * prect, enum_element eelement)

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

            if (m_pframewindow == nullptr || m_pframewindow->layout().design().display() != ::e_display_minimal)
               return false;

            prect->left = m_pointMoveGripMinimal.x + 2;

            prect->top = m_pointMoveGripMinimal.y + 2;

            prect->right = prect->left + m_iCaptionHeight - 4;

            prect->bottom = prect->top + m_iCaptionHeight - 4;


            return true;

         default:
            break;
         }
         return false;

      }

      bool frame::hit_test(const point &point, enum_element &eelementParam)
      {
         ::rect rect;
         for (enum_element eelement = (enum_element)(ElementNone + 1);
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

         ///defer_create_user_schema(::user::schema_button);

         //color32_t crBase = crMoveableBorder;

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

         auto psession = Session;

         auto pframewindow = m_pframewindow;

         auto pgraphics = pframewindow->create_memory_graphics();

         auto pstyle = pframewindow->get_style(pgraphics);

         auto crButtonHilite = pframewindow->get_color(pstyle, ::user::e_element_button_hilite);

         auto crButtonDarkShadow = pframewindow->get_color(pstyle, ::user::e_element_button_dark_shadow);

         auto crButtonFace = pframewindow->get_color(pstyle, ::user::e_element_button_background);

         auto crButtonShadow = pframewindow->get_color(pstyle, ::user::e_element_button_shadow);

         m_penText1->create_solid(1, ARGB(255, 255, 255, 255));
         m_penFace1->create_solid(1, crButtonFace | 0xff000000);
         m_penHilight1->create_solid(1, crButtonHilite | 0xff000000);
         m_penShadow1->create_solid(1, crButtonShadow | 0xff000000);
         m_penDkShadow1->create_solid(1, crButtonDarkShadow | 0xff000000);
         m_colorDkShadow = crButtonDarkShadow;
         m_colorFrameBorder = RGB(0, 0, 0) | 0xff000000;


      }


      void frame::on_style_change_001_and_002()
      {


         auto pcontrolbox = get_control_box();


         m_minSize = size(144, 48);
         m_minSize.cy = 48;
         if (pcontrolbox)
         {
            pcontrolbox->set_button_color_system_default_001();

         }
         set_frame_color_system_default_001();
         set_moveable_border_color(m_pframewindow->get_moveable_border_color());

         auto estyle = m_pframewindow->m_estyle;

         set_button_color_schema_001(m_colorMoveableBorder);

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
      //      return ARGB(255, 116, 160, 220);
      //   case StyleTranslucidWarmGray:
      //      return ARGB(255, 184, 184, 177);
      //      break;
      //   case StyleDarkWarmBlue:
      //      return ARGB(255, 34, 54, 75);
      //      break;
      //   case StyleBlackBorder:
      //      return RGB(116, 160, 220) | 0xff000000;
      //   case StyleLightGreen:
      //   case StyleTranslucidLightGreen:
      //      return RGB(116, 220, 160) | 0xff000000;
      //   case StyleRedOrange:
      //      return RGB(255, 170, 136) | 0xff000000;
      //   case StyleBlueRedPurple:
      //      return RGB(200, 100, 220) | 0xff000000;
      //   case StyleEveningSun:
      //      return RGB(255, 210, 100) | 0xff000000;
      //   case StyleTranslucidWarmLiteGray:
      //      return RGB(239, 230, 219) | 0xff000000;
      //   default:
      //      return RGB(200, 100, 220) | 0xff000000;
      //   }


      //   // Light Green/Translucid Light Green
      //   return RGB(116, 220, 160) | 0xff000000;

      //}


      bool frame::is_translucid_style(::user::enum_style estyle)
      {

         return estyle == ::user::StyleTranslucidWarmGray
            || estyle == ::user::StyleTranslucidLightBlue
            || estyle == ::user::StyleTranslucidLightGreen
            || estyle == ::user::StyleTranslucidWarmLiteGray;

      }


      void frame::Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const rect & rectParam, enum_border eborder, color32_t crTopLeft, color32_t crBottomRight)
      {

         ::rect rect(rectParam);
         i32 x = rect.left;
         i32 y = rect.top;
         i32 cx = rect.width();
         i32 cy = rect.height();



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


      //void frame::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
      //{

      //   if(psubject->m_id == id_user_style_change)
      //   {

      //      on_style_change();

      //   }

      //}


      //void frame::on_style_change()
      //{


      //}


      void frame::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {

         if (!m_pframewindow->is_frame_experience_enabled())
         {

            return;

         }

         auto psession = Session;

         pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

         if (!m_pframewindow->layout().is_full_screen()
            && !m_pframewindow->layout().is_zoomed()
            && !m_pframewindow->layout().is_iconic()
            && !m_pframewindow->frame_is_transparent()
            && m_pframewindow->m_bShowControlBox)
         {

            millis tick1;

            tick1.Now();

            on_draw_frame(pgraphics);

            //printf("A. frame::on_draw_frame %d\n", tick1.elapsed().m_i);

         }

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         if (m_pframewindow->layout().is_minimal())
         {

            ::rect rectIcon;

            millis tick2;

            tick2.Now();

            if (get_element_rect(rectIcon, ElementTopLeftIcon))
            {

               ::draw2d::icon * picon = m_pframewindow->m_picon;

               if (picon != nullptr)
               {

                  pgraphics->draw(rectIcon, picon);

               }

            }

            //printf("B. frame::on_draw_frame %d\n", tick2.elapsed().m_i);

            millis tick3;

            tick3.Now();

            ::rect rectGrip;

            if (get_element_rect(rectGrip, ElementMoveGripMinimal))
            {

               int i = 0;

               while (i < rectGrip.width() - 5 + 1)
               {

                  auto rect3d = ::rectd_dim(rectGrip.left + i, rectGrip.top, 3, rectGrip.height());

                  pgraphics->draw_3drect(rect3d, ARGB(110, 230, 230, 230), ARGB(110, 130, 130, 130));

                  i += 5;

               }

               //pgraphics->Draw3dRect(rectGrip.left + 12,rectGrip.top,3,rectGrip.height(),ARGB(184,255,255,255),ARGB(184,84,84,84));

            }

            //printf("C. frame::on_draw_frame %d\n", tick3.elapsed().m_i);

         }
         else if (!m_pframewindow->layout().is_full_screen() && !m_pframewindow->frame_is_transparent() && m_pframewindow->m_bShowControlBox)
         {

            millis tick2;

            tick2.Now();

            //oswindow hwndDraw = m_pframewindow->get_handle();

            //oswindow hwndActiveWindow = get_active_window();

            //oswindow hwndActiveWindowOwner = ::GetWindow(hwndActiveWindow, GW_OWNER);

            //oswindow hwndActiveWindowParent = ::get_parent(hwndActiveWindow);

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
                  && m_colorActiveCaptionTextBk != 0)*/
            if(m_pframewindow->is_active())
            {

               pgraphics->fill_rect(m_rectCaptionTextBk, m_colorActiveCaptionTextBk);

            }
            else
            {


               pgraphics->fill_rect(m_rectCaptionTextBk, m_colorCaptionTextBk);

            }

            //printf("D. frame::on_draw_frame %d\n", tick2.elapsed().m_i);

            millis tick3;

            tick3.Now();

            ::rect rectIcon;

            auto pframewindow = m_pframewindow;

            color32_t    crMoveableBorder;

            color32_t    crMoveableBorderHilight;

            color32_t    crMoveableBorderShadow;

            string str;

            pframewindow->get_window_text(str);

            if (pframewindow->is_active())
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

            //printf("E. frame::on_draw_frame %d\n", tick3.elapsed().m_i);

            millis tick4;

            tick4.Now();

            ::rect rect;

            m_pframewindow->get_window_rect(rect);

            rect -= rect.top_left();

            if (get_element_rect(rectIcon, ElementTopLeftIcon))
            {

               ::draw2d::icon * picon = m_pframewindow->m_picon;

               if (picon != nullptr)
               {

                  pgraphics->draw(rectIcon, picon);

               }

            }

            //printf("F. frame::on_draw_frame %d\n", tick4.elapsed().m_i);

            //class font_department & fonts = System.draw2d().fonts();

            millis tick5;

            tick5.Now();

            string wstrWindowText;

            pframewindow->get_window_text(wstrWindowText);

            ::draw2d::brush_pointer brushText(e_create);

            brushText->create_solid(m_colorCaptionText);

            pgraphics->set(brushText);

            pgraphics->set_font(pframewindow, ::user::e_element_window_title);

            pgraphics->draw_text(wstrWindowText, m_rectWindowText, e_align_left_center, e_draw_text_no_prefix);

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

         prect->deflate(get_margin_rect());

      }


   } // namespace tranquillum


} // namespace experience



