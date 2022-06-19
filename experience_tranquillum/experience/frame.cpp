#include "framework.h"
#include "aura/graphics/draw2d/_draw2d.h"


namespace experience_tranquillum
{


      frame::frame()
      {

         m_colorActiveCaptionTextBk = ::color::transparent;

         m_rectangleMarginNormal.set(1, 1, 1, 1);

         m_colorCaptionText = argb(255, 255, 255, 255);

         m_rectangleClient = nullptr;

      }


      frame::~frame()
      {

      }


      void frame::_001OnBeforeMove(const ::rectangle_i32 & rectangle)
      {

      }


      void frame::OnMove(__pointer(::user::interaction) pframewindow)
      {

         __UNREFERENCED_PARAMETER(pframewindow);

      }


      void frame::Glass(::draw2d::graphics_pointer & pgraphics, const rectangle_i32 & rectangle)
      {

         //auto pframewindow = m_pframewindow;

         //class imaging & imaging = psystem->imaging();

         ::rectangle_i32 rectangleClient(rectangle);

         ::rectangle_i32 rectangleInflate;

         if (rectangleClient.area() <= 0)
         {

            return;

         }

         return;

         //i32 iInflate = 5; // raio 2 pixels + centro 1 pixel

         //rectangleInflate = rectangleClient;
         //rectangleInflate.inflate(iInflate, iInflate);

         ////__pointer(::user::interaction) puserinteractionDesktop = psystem->get_desktop_window();

         //::rectangle_i32 rectangleScreen;

         //pframewindow->best_monitor(rectangleScreen);

         //::image_pointer pimage;

         //::image_pointer pimage2;

         //pimage = create_image({rectangleClient.width() + iInflate * 2,  rectangleClient.height() + iInflate * 2});

         //pimage2 = create_image({rectangleClient.width() + iInflate * 2,  rectangleClient.height() + iInflate * 2});
         //::rectangle_i32 rectangleWindow = rectangleClient;
         //pframewindow->client_to_screen(rectangleWindow);
         ////pimage = create_image({rectangleClient.width(),  rectangleClient.height()});
         //bool b = pimage2->get_graphics()->BitBlt(0, 0, rectangleClient.width() + iInflate * 2, rectangleClient.height() + iInflate * 2, pgraphics, rectangleClient.left - iInflate, rectangleClient.top - iInflate);
         ////bool b = ::BitBlt(dc2, 0, 0, rectangleClient.width() + iInflate * 2, rectangleClient.height() + iInflate * 2, hdcScreen, rectangleClient.left - iInflate, rectangleClient.top - iInflate);
         //b = imaging.blur(pimage->g(), ::point_i32(),
         //                 size_i32(rectangleClient.width() + iInflate * 2, rectangleClient.height() + iInflate * 2),
         //                 pimage2->get_graphics(), ::point_i32(), 2);

         ////spgraphics->Draw3dRect(rectangleClient, 127 << 24, 127 << 24);
         ////rectangleClient.deflate(1, 1);
         ////spgraphics->Draw3dRect(rectangleClient, 64 << 24, 64 << 24);
         ////b = imaging.bitmap_blend(pgraphics, prectangle->left, prectangle->top,

         //rectangleWindow.width(),
         //rectangleWindow.height(),
         //&spgraphics,
         //iInflate, iInflate, 128);*/
         ///*BLENDFUNCTION bf;
         //bf.AlphaFormat = AC_SRC_ALPHA;
         //bf.BlendOp     = AC_SRC_OVER;
         //bf.BlendFlags = 0;
         //bf.SourceConstantAlpha = 255;
         //::alpha_blend(pgraphics->get_handle1(),
         //prectangle->left, prectangle->top,

         //rectangleWindow.width(),
         //rectangleWindow.height(),
         //spgraphics->get_handle1(),
         //0, 0,
         //rectangleWindow.width(),
         //rectangleWindow.height(),
         //bf);*/

         //pgraphics->BitBlt(rectangleClient.left, rectangleClient.top, rectangleClient.width(), rectangleClient.height(), pimage->g(), iInflate, iInflate);

      }

      
      status < ::color::color > frame::get_border_main_body_color()
      {
         //return argb(255, 63, 150, 106);

         return m_pframewindow->get_border_main_body_color();

      }


      //::user::front_end_schema * frame::get_user_front_end_schema()
      //{

      //   return &m_schema;

      //}


      void frame::ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, const ::color::color & color, const ::opacity & opacity)
      {

         /*Gdiplus::Graphics g((HDC) pgraphics->get_os_data());
         g.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
         Gdiplus::SolidBrush solidBrush(Gdiplus::Color(bAlpha, colorref_get_r_value(color32), colorref_get_g_value(color32), colorref_get_b_value(color32)));
         g.FillRectangle(&solidBrush, prectangle->left, prectangle->top, prectangle->right - prectangle->left, prectangle->bottom - prectangle->top);*/


         pgraphics->fill_rectangle(rectangle, color & opacity);


      }




      //void frame::set_style(e_style estyle)
      //{

      //   m_estyle = estyle;

      //   if (get_control_box().is_null())
      //      return;

      //   on_style_change();

      //}


      //}



      bool frame::get_element_rect(RECTANGLE_I32 * prectangle, enum_element eelement)
      {

         switch (eelement)
         {
         case e_element_top_left_icon:

            if (m_pframewindow == nullptr || m_pframewindow->get_draw_icon() == nullptr)
            {

               return false;

            }

            prectangle->left = m_rectangleCaption.left + m_pcontrolbox->m_iDefaultButtonMargin;

            prectangle->right = prectangle->left + 16;

            prectangle->bottom = m_iTitleBottom;

            prectangle->top = prectangle->bottom - 16;

            return true;

         case e_element_move_grip_minimal:

            if (m_pframewindow == nullptr || m_pframewindow->const_layout().design().display() != ::e_display_minimal)
               return false;

            prectangle->left = m_pointMoveGripMinimal.x + 2;

            prectangle->top = m_pointMoveGripMinimal.y + 2;

            prectangle->right = prectangle->left + m_iCaptionHeight - 4;

            prectangle->bottom = prectangle->top + m_iCaptionHeight - 4;


            return true;

         default:
            break;
         }
         return false;

      }




      void frame::set_moveable_border_color(const ::color::color & color32)
      {

         m_colorMoveableBorder = color32;

         ::color::color color;

         color.set_rgb(color32);
         color.hls_rate(0.0, 0.5, 0.0);
         m_colorMoveableBorderHilight = color;

         color.set_rgb(color32);
         color.hls_rate(0.0, -0.3, 0.0);
         m_colorMoveableBorderShadow = color;

         color.set_rgb(color32);
         color.hls_rate(8.0, -0.8, 0.0);
         m_colorMoveableBorderDkShadow = color;


         m_colorCaptionTextBk = m_colorMoveableBorderShadow;

      }


      void frame::set_button_color_schema_001(const ::color::color & crMoveableBorder)
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

         //auto psession = get_session();

         auto pframewindow = m_pframewindow;

         auto psystem = m_psystem->m_paurasystem;

         auto pdraw2d = psystem->draw2d();

         auto pgraphics = pdraw2d->create_memory_graphics(m_pframewindow);

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


         m_minSize = size_i32(144, 48);
         m_minSize.cy = 48;
         if (pcontrolbox)
         {
            pcontrolbox->set_button_color_system_default_001();

         }

         __construct(m_ppenText1);
         __construct(m_ppenFace1);
         __construct(m_ppenHilight1);
         __construct(m_ppenShadow1);
         __construct(m_ppenDkShadow1);

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
      //      return argb(255, 116, 160, 220);
      //   case StyleTranslucidWarmGray:
      //      return argb(255, 184, 184, 177);
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


      bool frame::is_translucid_style(::user::enum_style estyle)
      {

         return estyle == ::user::StyleTranslucidWarmGray
            || estyle == ::user::StyleTranslucidLightBlue
            || estyle == ::user::StyleTranslucidLightGreen
            || estyle == ::user::StyleTranslucidWarmLiteGray;

      }


      void frame::Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const rectangle_i32 & rectangleParam, enum_border eborder, const ::color::color & crTopLeft, const ::color::color & crBottomRight)
      {

         ::rectangle_i32 rectangle(rectangleParam);

         i32 x = rectangle.left;
         i32 y = rectangle.top;
         i32 cx = rectangle.width() - 1;
         i32 cy = rectangle.height() - 1;

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

            pgraphics->set_current_point(x, y);

            pgraphics->line_to(x + cx, y);

         }

         if (eborder & e_border_left)
         {

            pgraphics->set_current_point(x, y);

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

            pgraphics->set_current_point(x + cx, y);

            pgraphics->line_to(x + cx, y + cy);

         }

         if (eborder & e_border_bottom)
         {

            pgraphics->set_current_point(x, y + cy);

            pgraphics->line_to(x + cx, y + cy);

         }

      }


      //void frame::handle(::topic * ptopic, ::context * pcontext)
      //{

      //   if(ptopic->m_atom == id_user_style_change)
      //   {

      //      on_style_change();

      //   }

      //}


      //void frame::on_style_change()
      //{


      //}


      void frame::title_bar_layout(::draw2d::graphics_pointer & pgraphics)
      {

         ::experience::frame::title_bar_layout(pgraphics);

         m_rectangleCaptionTextBk = m_rectangleCaption;

      }



      void frame::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {

         if (!m_pframewindow->is_frame_experience_enabled())
         {

            return;

         }

         //auto psession = get_session();

         //pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);



         if (!m_pframewindow->layout().is_full_screen()
            && !m_pframewindow->layout().is_zoomed()
            && !m_pframewindow->layout().is_iconic()
            && !m_pframewindow->frame_is_transparent()
            && m_pframewindow->m_bShowControlBox)
         {

            ::duration tick1;

            tick1.Now();

            on_draw_frame(pgraphics);

            //printf("A. frame::on_draw_frame %d\n", tick1.elapsed().m_i);

         }

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         if (m_pframewindow->layout().is_minimal())
         {

            ::rectangle_i32 rectangleIcon;

            ::duration tick2;

            tick2.Now();

            if (get_element_rect(rectangleIcon, e_element_top_left_icon))
            {

               auto pdrawicon = m_pframewindow->get_draw_icon();

               if (pdrawicon != nullptr)
               {

                  image_source imagesource(pdrawicon);

                  rectangle_f64 rectangleTarget(pdrawicon->get_smaller_size(rectangleIcon.size()));

                  rectangleTarget.CenterOf(rectangleIcon);

                  image_drawing_options imagedrawingoptions(rectangleTarget);

                  image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  pgraphics->draw(imagedrawing);

               }

            }

            //printf("B. frame::on_draw_frame %d\n", tick2.elapsed().m_i);

            ::duration tick3;

            tick3.Now();

            ::rectangle_i32 rectangleGrip;

            if (get_element_rect(rectangleGrip, e_element_move_grip_minimal))
            {

               int i = 0;

               while (i < rectangleGrip.width() - 5 + 1)
               {

                  auto rect3d = ::rectangle_f64_dimension(rectangleGrip.left + i, rectangleGrip.top, 3, rectangleGrip.height());

                  pgraphics->draw_inset_3d_rectangle(rect3d, argb(110, 230, 230, 230), argb(110, 130, 130, 130));

                  i += 5;

               }

               //pgraphics->Draw3dRect(rectangleGrip.left + 12,rectangleGrip.top,3,rectangleGrip.height(),argb(184,255,255,255),argb(184,84,84,84));

            }

            //printf("C. frame::on_draw_frame %d\n", tick3.elapsed().m_i);

         }
         else if (!m_pframewindow->layout().is_full_screen() && !m_pframewindow->frame_is_transparent() && m_pframewindow->m_bShowControlBox)
         {

            ::duration tick2;

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
            pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

            pgraphics->set_compositing_quality(::draw2d::e_compositing_quality_none);

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

            if(m_pframewindow->is_active_window())
            {

               pgraphics->fill_rectangle(m_rectangleCaptionTextBk, m_colorActiveCaptionTextBk);

            }
            else
            {

               pgraphics->fill_rectangle(m_rectangleCaptionTextBk, m_colorCaptionTextBk);

            }

            ::duration tick3;

            tick3.Now();

            ::rectangle_i32 rectangleIcon;

            auto pframewindow = m_pframewindow;

            status < ::color::color > crMoveableBorder;

            status < ::color::color > crMoveableBorderHilight;

            status < ::color::color > crMoveableBorderShadow;

            string str;

            pframewindow->get_window_text(str);

            if (pframewindow->is_active_window())
            {

               crMoveableBorder = m_colorMoveableBorder;

               crMoveableBorderHilight = m_colorMoveableBorderHilight;

               crMoveableBorderShadow = m_colorMoveableBorderShadow;

            }
            else
            {

               //auto psession = get_session();

               auto pstyle = pframewindow->get_style(pgraphics);

               crMoveableBorder = pframewindow->get_color(pstyle, ::e_element_button_background);

               crMoveableBorderHilight = pframewindow->get_color(pstyle, ::e_element_button_hilite);

               crMoveableBorderShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

            }

            //printf("E. frame::on_draw_frame %d\n", tick3.elapsed().m_i);

            ::duration tick4;

            tick4.Now();

            ::rectangle_i32 rectangle;

            m_pframewindow->get_window_rect(rectangle);

            rectangle -= rectangle.top_left();

            if (get_element_rect(rectangleIcon, e_element_top_left_icon))
            {

               ::draw2d::icon * picon = m_pframewindow->m_pdrawicon;

               if (::is_ok(picon))
               {

                  image_source imagesource(picon);

                  //rectangle_f64 rectangleTarget(picon->get_smaller_size(rectangleIcon.size()));

                  //rectangleTarget.CenterOf(rectangleIcon);

                  image_drawing_options imagedrawingoptions(rectangleIcon);

                  image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  pgraphics->draw(imagedrawing);

               }

            }

            //printf("F. frame::on_draw_frame %d\n", tick4.elapsed().m_i);

            //class fonts & fonts = pdraw2d->fonts();

            ::duration tick5;

            tick5.Now();

            string wstrWindowText;

            pframewindow->get_window_text(wstrWindowText);

            auto pbrushText = __create < ::draw2d::brush > ();

            pbrushText->create_solid(m_colorCaptionText);

            pgraphics->set(pbrushText);

            pgraphics->set_font(pframewindow, ::e_element_window_title);

            pgraphics->set_text_rendering_hint(::write_text::e_rendering_clear_type_grid_fit);

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

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

         prectangle->deflate(get_margin_rect());

      }


} // namespace experience_tranquillum



