#include "framework.h"
#include "aura/graphics/draw2d/_draw2d.h"


namespace experience
{


   namespace anthill
   {



      frame::frame()
      {

         m_pointWindowIcon.x = 14;

         m_colorActiveCaptionTextBk = ::color::transparent;

         m_rectangleMarginNormal.set(5, 5, 5, 5);

         m_colorCaptionText = argb(255, 255, 255, 255);

      }


      frame::~frame()
      {

      }


      void frame::OnMove(__pointer(::user::interaction) pframewindow)
      {

         __UNREFERENCED_PARAMETER(pframewindow);

      }


      ::user::enum_style frame::get_style() const
      {

         return m_pframewindow->m_estyle;

      }


      bool frame::is_translucid() const
      {

         return m_pframewindow->is_translucid_user_style(m_pframewindow->m_estyle);

      }


      void frame::Glass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleParam)
      {

         auto pframewindow = m_pframewindow;

         ::rectangle_i32 rectangleClient(rectangleParam);

         ::rectangle_i32 rectangleInflate;

         if (rectangleClient.is_empty())
         {

            return;

         }

         i32 iInflate = 5; // raio 2 pixels + centro 1 pixel

         rectangleInflate = rectangleClient;
         rectangleInflate.inflate(iInflate, iInflate);

         //__pointer(::user::interaction) puserinteractionDesktop = psystem->get_desktop_window();

         ::rectangle_i32 rectangleScreen;

         pframewindow->best_monitor(rectangleScreen);

         ::image_pointer pimage1;

         ::image_pointer pimage2;

         pimage1 = m_pcontext->context_image()->create_image({rectangleClient.width() + iInflate * 2,  rectangleClient.height() + iInflate * 2});

         pimage2 = m_pcontext->context_image()->create_image({rectangleClient.width() + iInflate * 2,  rectangleClient.height() + iInflate * 2});
         ::rectangle_i32 rectangleWindow = rectangleClient;
         pframewindow->client_to_screen(rectangleWindow);
         //pimage = create_image({rectangleClient.width(),  rectangleClient.height()});
         //bool b = pimage2->get_graphics()->BitBlt(0, 0, rectangleClient.width() + iInflate * 2, rectangleClient.height() + iInflate * 2, pgraphics, rectangleClient.left - iInflate, rectangleClient.top - iInflate);

         {

            image_source imagesource(pgraphics,
               rectangle_f64(::point_i32(rectangleClient.left - iInflate, rectangleClient.top - iInflate), ::size_f64(rectangleClient.width() + iInflate * 2, rectangleClient.height() + iInflate * 2)));

            auto rectangle = rectangle_f64_dimension(0, 0, rectangleClient.width() + iInflate * 2, rectangleClient.height() + iInflate * 2);

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pimage2->get_graphics()->draw(imagedrawing);

         }
         //bool b = ::BitBlt(dc2, 0, 0, rectangleClient.width() + iInflate * 2, rectangleClient.height() + iInflate * 2, hdcScreen, rectangleClient.left - iInflate, rectangleClient.top - iInflate);

         m_blur1.blur(pimage1, 2, ::rectangle_i32(::size_i32(rectangleClient.width() + iInflate * 2, rectangleClient.height() + iInflate * 2)));

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

         {

            image_source imagesource(pimage1, ::rectangle_f64(point_f64(iInflate, iInflate), rectangleClient.size()));

            image_drawing_options imagedrawingoptions(rectangleClient);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }

      }

      status < ::color::color > frame::get_border_main_body_color()
      {
         return argb(255, 63, 150, 106);
      }

      //::user::front_end_schema * frame::get_user_front_end_schema()
      //{

      //   return &m_schema;

      //}


      void frame::ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, const ::color::color& color, const ::opacity& opacity)
      {

         /*Gdiplus::Graphics g((HDC) pgraphics->get_os_data());
         g.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
         Gdiplus::SolidBrush solidBrush(Gdiplus::Color(bAlpha, colorref_get_r_value(color32), colorref_get_g_value(color32), colorref_get_b_value(color32)));
         g.FillRectangle(&solidBrush, lprect->left, lprect->top, lprect->right - lprect->left, lprect->bottom - lprect->top);*/

         pgraphics->fill_rectangle(rectangle, color & opacity);

      }




      //void frame::set_style(e_style estyle)
      //{

      //   m_estyle = estyle;

      //   if (get_control_box().is_null())
      //      return;

      //   on_style_change();

      //}


      //void frame::set_style(const ::string & pszStyle)
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
         __UNREFERENCED_PARAMETER(i);
         return (frame::enum_element) (*((i32*)&eelement))++;
      }

      bool frame::get_element_rect(RECTANGLE_I32 * lprect, enum_element eelement)
      {
         switch (eelement)
         {
         case e_element_top_left_icon:

            if (m_pframewindow == nullptr || m_pframewindow->get_draw_icon() == nullptr)
               return false;

            lprect->left = m_pointWindowIcon.x;
            lprect->top = m_pointWindowIcon.y;
            //lprect->right = lprect->left + m_pframewindow->m_picon->get_size().cx;
            //lprect->bottom = lprect->top + m_pframewindow->m_picon->get_size().cy;
            lprect->right = lprect->left + 24;
            lprect->bottom = lprect->top + 24;

            return true;

         case e_element_move_grip_minimal:

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

        // auto psession = get_session();

         auto pframewindow = m_pframewindow;

         auto psystem = m_psystem->m_paurasystem;

         auto pdraw2d = psystem->draw2d();

         auto pgraphics = pdraw2d->create_memory_graphics();

         auto pstyle = pframewindow->get_style(pgraphics);

         auto crButtonHilite = pframewindow->get_color(pstyle, ::e_element_button_hilite);

         auto crButtonDarkShadow = pframewindow->get_color(pstyle, ::e_element_button_dark_shadow);

         auto crButtonFace = pframewindow->get_color(pstyle, ::e_element_button_background);

         auto crButtonShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

         m_ppenText1->create_solid(1, argb(255, 255, 255, 255));
         m_ppenFace1->create_solid(1, opaque(crButtonFace));
         m_ppenHilight1->create_solid(1, opaque(crButtonHilite));
         m_ppenShadow1->create_solid(1, opaque(crButtonShadow));
         m_ppenDkShadow1->create_solid(1, opaque(crButtonDarkShadow));
         m_colorDkShadow = crButtonDarkShadow;
         m_colorFrameBorder = argb(255, 0, 0, 0);


      }


      void frame::on_style_change_001_and_002(::draw2d::graphics_pointer & pgraphics)
      {

         auto pcontrolbox = get_control_box();

         if (pcontrolbox)
         {

            pcontrolbox->set_button_color_system_default_001();

         }

         __construct(m_ppenText1);
         __construct(m_ppenFace1);
         __construct(m_ppenHilight1);
         __construct(m_ppenShadow1);
         __construct(m_ppenDkShadow1);


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

            pgraphics->set(ppen);

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

         if ((eborder & e_border_right || eborder & e_border_bottom) && (!ppen || ppen->m_color != crBottomRight))
         {

            ppen.create(this);

            ppen->create_solid(1.0, crBottomRight);

            pgraphics->set(ppen);

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

        // auto psession = get_session();

         pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

         auto pframewindow = m_pframewindow;

         if (!pframewindow->layout().is_full_screen() && !pframewindow->layout().is_zoomed() && !pframewindow->layout().is_iconic() && !m_pframewindow->frame_is_transparent() && m_pframewindow->m_bShowControlBox)
         {

            on_draw_frame(pgraphics);

         }

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         if (pframewindow->layout().is_minimal())
         {

            ::rectangle_i32 rectangleIcon;

            if (get_element_rect(rectangleIcon, e_element_top_left_icon))
            {

               auto pdrawicon = m_pframewindow->get_draw_icon();

               if (pdrawicon != nullptr)
               {

                  image_source imagesource(pdrawicon);

                  image_drawing_options imagedrawingoptions(rectangleIcon);

                  image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  pgraphics->draw(imagedrawing);

               }

            }

            ::rectangle_i32 rectangleGrip;

            if (get_element_rect(rectangleGrip, e_element_move_grip_minimal))
            {

               int i = 0;

               while (i < rectangleGrip.width() - 5 + 1)
               {

                  pgraphics->draw_inset_3d_rectangle(rectangle_i32_dimension(rectangleGrip.left + i, rectangleGrip.top, 3, rectangleGrip.height()), argb(110, 230, 230, 230), argb(110, 130, 130, 130));

                  i += 5;

               }

               //pgraphics->Draw3dRect(rectangleGrip.left + 12,rectangleGrip.top,3,rectangleGrip.height(),argb(190, 255, 255, 255),argb(190, 90, 90, 90));

            }

         }
         else if (!pframewindow->layout().is_full_screen() && !m_pframewindow->frame_is_transparent())
         {

            if (m_pframewindow->is_active_window() && m_colorActiveCaptionTextBk.is_ok())
            {

               pgraphics->fill_rectangle(m_rectangleCaption, m_colorActiveCaptionTextBk);

            }
            else
            {

               pgraphics->fill_rectangle(m_rectangleCaption, m_colorCaptionTextBk);

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
        //    auto psession = get_session();

            auto pstyle = pframewindow->get_style(pgraphics);

            crMoveableBorder = pframewindow->get_color(pstyle, ::e_element_button_background);

            crMoveableBorderHilight = pframewindow->get_color(pstyle, ::e_element_button_hilite);

            crMoveableBorderShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

}

            ::rectangle_i32 rectangle;



            pframewindow->get_window_rect(rectangle);

            rectangle -= rectangle.top_left();

            if (get_element_rect(rectangleIcon, e_element_top_left_icon))
            {

               auto pdrawicon = m_pframewindow->get_draw_icon();

               if (pdrawicon != nullptr)
               {

                  image_source imagesource(pdrawicon);

                  image_drawing_options imagedrawingoptions(rectangleIcon);

                  image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  pgraphics->draw(imagedrawing);

               }

            }

            //class fonts & fonts = pdraw2d->fonts();

            auto pstyle = pframewindow->get_style(pgraphics);

            string wstrWindowText;

            pframewindow->get_window_text(wstrWindowText);

            auto pbrushText = __create < ::draw2d::brush > ();

            pbrushText->create_solid(m_colorCaptionText);

            pgraphics->set(pbrushText);

            pgraphics->set(pframewindow->get_font(pstyle));

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

         m_pframewindow->get_window_rect(prectangle);

         prectangle->offset(-prectangle->top_left());

         prectangle->deflate(10,10);

      }



   } // namespace anthill


} // namespace experience




