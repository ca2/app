#include "framework.h"
#include "frame.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/image/source.h"
#include "aura/graphics/image/icon.h"
#include "aura/graphics/image/drawing.h"
#include "base/platform/system.h"
#include "base/user/experience/control_box.h"
#include "base/user/experience/frame_window.h"
#include "base/user/experience/size_manager.h"


namespace experience_tranquillum
{


   frame::frame()
   {

      m_colorActiveCaptionTextBk = argb(255, 255, 255, 255);

      m_colorCaptionTextBk = argb(255, 192, 192, 192);

      m_rectangleMarginNormal.set(1, 1, 1, 1);

      m_colorCaptionText = argb(255, 255, 255, 255);

      //m_rectangleX = nullptr;

   }


   frame::~frame()
   {

   }


   void frame::_001OnBeforeMove(const ::int_rectangle & rectangle)
   {

   }


   void frame::OnMove(::pointer<::user::interaction>pframewindow)
   {

      __UNREFERENCED_PARAMETER(pframewindow);

   }


   void frame::Glass(::draw2d::graphics_pointer & pgraphics, const int_rectangle & rectangle)
   {

      //auto pframewindow = m_pframewindow;

      //class imaging & imaging = psystem->imaging();

      ::int_rectangle rectangleX(rectangle);

      ::int_rectangle rectangleInflate;

      if (rectangleX.area() <= 0)
      {

         return;

      }

      return;

      //int iInflate = 5; // raio 2 pixels + centro 1 pixel

      //rectangleInflate = rectangleX;
      //rectangleInflate.inflate(iInflate, iInflate);

      ////::pointer<::user::interaction>puserinteractionDesktop = psystem->get_desktop_window();

      //::int_rectangle rectangleScreen;

      //pframewindow->best_monitor(rectangleScreen);

      //::image::image_pointer pimage;

      //::image::image_pointer pimage2;

      //pimage = create_image({rectangleX.width() + iInflate * 2,  rectangleX.height() + iInflate * 2});

      //pimage2 = create_image({rectangleX.width() + iInflate * 2,  rectangleX.height() + iInflate * 2});
      //::int_rectangle rectangleWindow = rectangleX;
      //pframewindow->client_to_screen(rectangleWindow);
      ////pimage = create_image({rectangleX.width(),  rectangleX.height()});
      //bool b = pimage2->get_graphics()->BitBlt(0, 0, rectangleX.width() + iInflate * 2, rectangleX.height() + iInflate * 2, pgraphics, rectangleX.left() - iInflate, rectangleX.top() - iInflate);
      ////bool b = ::BitBlt(dc2, 0, 0, rectangleX.width() + iInflate * 2, rectangleX.height() + iInflate * 2, hdcScreen, rectangleX.left() - iInflate, rectangleX.top() - iInflate);
      //b = imaging.blur(pimage->g(), ::int_point(),
      //                 int_size(rectangleX.width() + iInflate * 2, rectangleX.height() + iInflate * 2),
      //                 pimage2->get_graphics(), ::int_point(), 2);

      ////spgraphics->Draw3dRect(rectangleX, 127 << 24, 127 << 24);
      ////rectangleX.deflate(1, 1);
      ////spgraphics->Draw3dRect(rectangleX, 64 << 24, 64 << 24);
      ////b = imaging.bitmap_blend(pgraphics, rectangle.left(), rectangle.top(),

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
      //rectangle.left(), rectangle.top(),

      //rectangleWindow.width(),
      //rectangleWindow.height(),
      //spgraphics->get_handle1(),
      //0, 0,
      //rectangleWindow.width(),
      //rectangleWindow.height(),
      //bf);*/

      //pgraphics->BitBlt(rectangleX.left(), rectangleX.top(), rectangleX.width(), rectangleX.height(), pimage->g(), iInflate, iInflate);

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


   void frame::ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, const ::color::color & color, const ::opacity & opacity)
   {

      /*Gdiplus::Graphics g((HDC) pgraphics->get_os_data());
      g.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
      Gdiplus::SolidBrush solidBrush(Gdiplus::Color(bAlpha, color32_byte_red(color32), color32_byte_green(color32), color32_byte_blue(color32)));
      g.FillRectangle(&solidBrush, rectangle.left(), rectangle.top(), rectangle.right() - rectangle.left(), rectangle.bottom() - rectangle.top());*/


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



   bool frame::get_element_rectangle(::int_rectangle & rectangle, enum_element eelement)
   {

      switch (eelement)
      {
      case e_element_top_left_icon:

         if (m_pframewindow == nullptr || m_pframewindow->get_draw_icon() == nullptr)
         {

            return false;

         }

         rectangle.left() = m_rectangleCaption.left() + m_pcontrolbox->m_iDefaultButtonMargin;

         rectangle.right() = rectangle.left() + 16;

         rectangle.bottom() = m_iTitleBottom;

         rectangle.top() = rectangle.bottom() - 16;

         return true;

      case e_element_move_grip_minimal:

         if (m_pframewindow == nullptr || m_pframewindow->const_layout().design().display() != ::e_display_minimal)
            return false;

         rectangle.left() = m_pointMoveGripMinimal.x() + 2;

         rectangle.top() = m_pointMoveGripMinimal.y() + 2;

         rectangle.right() = rectangle.left() + m_iCaptionHeight - 4;

         rectangle.bottom() = rectangle.top() + m_iCaptionHeight - 4;


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

      color = color32;
      color.hls_rate(0.0, 0.5, 0.0);
      m_colorMoveableBorderHilight = color;

      color = color32;
      color.hls_rate(0.0, -0.3, 0.0);
      m_colorMoveableBorderShadow = color;

      color = color32;
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

      //

      auto pframewindow = m_pframewindow;

      auto psystem = system();

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(m_pframewindow);

      auto pstyle = pframewindow->get_style(pgraphics);

      auto crButtonHilite = pframewindow->get_color(pstyle, ::e_element_button_hilite);

      auto crButtonDarkShadow = pframewindow->get_color(pstyle, ::e_element_button_dark_shadow);

      auto crButtonFace = pframewindow->get_color(pstyle, ::e_element_button_background);

      auto crButtonShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

      m_ppenText1->create_solid(1, argb(255, 255, 255, 255));
      m_ppenFace1->create_solid(1, crButtonFace.opaque());
      m_ppenHilight1->create_solid(1, crButtonHilite.opaque());
      m_ppenShadow1->create_solid(1, crButtonShadow.opaque());
      m_ppenDkShadow1->create_solid(1, crButtonDarkShadow.opaque());
      m_colorDkShadow = crButtonDarkShadow;
      m_colorFrameBorder = argb(255, 0, 0, 0);

   }


   void frame::on_style_change_001_and_002(::draw2d::graphics_pointer & pgraphics)
   {


      auto pcontrolbox = get_control_box();


      m_minSize = int_size(144, 48);
      m_minSize.cy() = 48;
      if (pcontrolbox)
      {
         pcontrolbox->set_button_color_system_default_001();

      }

      __øconstruct(m_ppenText1);
      __øconstruct(m_ppenFace1);
      __øconstruct(m_ppenHilight1);
      __øconstruct(m_ppenShadow1);
      __øconstruct(m_ppenDkShadow1);

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


   void frame::Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const int_rectangle & rectangleParam, enum_border eborder, const ::color::color & crTopLeft, const ::color::color & crBottomRight)
   {

      ::int_rectangle rectangle(rectangleParam);

      int x = rectangle.left();
      int y = rectangle.top();
      int cx = rectangle.width() - 1;
      int cy = rectangle.height() - 1;

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::draw2d::pen_pointer ppen;

      if (eborder & e_border_top || eborder & e_border_left)
      {

         __øconstruct(ppen);

         ppen->create_solid(1.0, crTopLeft);

         pgraphics->set(ppen);

      }

      if (eborder & e_border_top)
      {

         pgraphics->line(x, y,x + cx, y);

      }

      if (eborder & e_border_left)
      {

         pgraphics->line(x, y,x, y + cy);

      }

      if ((eborder & e_border_right || eborder & e_border_bottom) && (!ppen || ppen->m_color != crBottomRight))
      {

         __øconstruct(ppen);

         ppen->create_solid(1.0, crBottomRight);

         pgraphics->set(ppen);

      }

      if (eborder & e_border_right)
      {

         pgraphics->line(x + cx, y, x + cx, y + cy);

      }

      if (eborder & e_border_bottom)
      {

         pgraphics->line(x, y + cy,x + cx, y + cy);

      }

   }


   //void frame::handle(::topic * ptopic, ::handler_context * phandlercontext)
   //{

   //   if(ptopic->id() == id_user_style_change)
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

      //pgraphics->fill_solid_rectangle(::double_rectangle_dimension(0, 0, 16, 16), ::color::red);

      //return;

      if (!m_pframewindow->is_frame_experience_enabled())
      {

         return;

      }

      //

      //pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      if (!m_pframewindow->layout().is_full_screen()
         && !m_pframewindow->layout().is_zoomed()
         && !m_pframewindow->layout().is_iconic()
         && !m_pframewindow->frame_is_transparent()
         && m_pframewindow->m_bShowControlBox)
      {

         //auto time1 = ::time::now();

         on_draw_frame(pgraphics);

         //printf("A. frame::on_draw_frame %d\n", tick1.elapsed().m_i);

      }

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      if (m_pframewindow->layout().is_minimal())
      {

         ::int_rectangle rectangleIcon;

         //auto time2 = ::time::now();

         if (get_element_rectangle(rectangleIcon, e_element_top_left_icon))
         {

            auto pdrawicon = m_pframewindow->get_draw_icon();

            if (pdrawicon != nullptr)
            {

               ::image::image_source imagesource(pdrawicon);

               double_rectangle rectangleTarget(pdrawicon->get_smaller_size(rectangleIcon.size()));

               rectangleTarget.CenterOf(rectangleIcon);

               ::image::image_drawing_options imagedrawingoptions(rectangleTarget);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

         }

         //printf("B. frame::on_draw_frame %d\n", tick2.elapsed().m_i);

         //auto time3 = ::time::now();

         ::int_rectangle rectangleGrip;

         if (get_element_rectangle(rectangleGrip, e_element_move_grip_minimal))
         {

            int i = 0;

            while (i < rectangleGrip.width() - 5 + 1)
            {

               auto rect3d = ::double_rectangle_dimension(rectangleGrip.left() + i, rectangleGrip.top(), 3, rectangleGrip.height());

               pgraphics->draw_inset_3d_rectangle(rect3d, argb(110, 230, 230, 230), argb(110, 130, 130, 130), 1.0);

               i += 5;

            }

            //pgraphics->Draw3dRect(rectangleGrip.left() + 12,rectangleGrip.top(),3,rectangleGrip.height(),argb(184,255,255,255),argb(184,84,84,84));

         }

         //printf("C. frame::on_draw_frame %d\n", tick3.elapsed().m_i);

      }
      else if (!m_pframewindow->layout().is_full_screen() && !m_pframewindow->frame_is_transparent() && m_pframewindow->m_bShowControlBox)
      {

         //auto time2 = ::time::now();

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

         //::windowing::window * puiImplActive = oswindow_get(hwndActiveWindow);

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

         if (m_pframewindow->is_active_window())
         {

            pgraphics->fill_rectangle(m_rectangleCaptionTextBk, m_colorActiveCaptionTextBk);

         }
         else
         {

            pgraphics->fill_rectangle(m_rectangleCaptionTextBk, m_colorCaptionTextBk);

         }

         //auto time3 = ::time::now();

         ::int_rectangle rectangleIcon;

         auto pframewindow = m_pframewindow;

         status < ::color::color > crMoveableBorder;

         status < ::color::color > crMoveableBorderHilight;

         status < ::color::color > crMoveableBorderShadow;

         auto strWindowText = pframewindow->get_window_text();

         //pframewindow->get_window_text(str);

         if (pframewindow->is_active_window())
         {

            crMoveableBorder = m_colorMoveableBorder;

            crMoveableBorderHilight = m_colorMoveableBorderHilight;

            crMoveableBorderShadow = m_colorMoveableBorderShadow;

         }
         else
         {

            //

            auto pstyle = pframewindow->get_style(pgraphics);

            crMoveableBorder = pframewindow->get_color(pstyle, ::e_element_button_background);

            crMoveableBorderHilight = pframewindow->get_color(pstyle, ::e_element_button_hilite);

            crMoveableBorderShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

         }

         //printf("E. frame::on_draw_frame %d\n", tick3.elapsed().m_i);

         //auto time4 = ::time::now();

         ::int_rectangle rectangle;

         m_pframewindow->window_rectangle(rectangle);

         rectangle -= rectangle.top_left();

         if (get_element_rectangle(rectangleIcon, e_element_top_left_icon))
         {

            ::image::icon * picon = m_pframewindow->m_pdrawicon;

            if (::is_set(picon) && picon->is_ok())
            {

               ::image::image_source imagesource(picon);

               //double_rectangle rectangleTarget(picon->get_smaller_size(rectangleIcon.size()));

               //rectangleTarget.CenterOf(rectangleIcon);

               ::image::image_drawing_options imagedrawingoptions(rectangleIcon);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

         }

         //printf("F. frame::on_draw_frame %d\n", tick4.elapsed().m_i);

         //class fonts & fonts = pdraw2d->fonts();

         //auto time5 = ::time::now();

         //auto strWindowText = pframewindow->get_window_text();

         //pframewindow->get_window_text(wstrWindowText);

         auto pbrushText = __øcreate < ::draw2d::brush >();

         pbrushText->create_solid(m_colorCaptionText);

         pgraphics->set(pbrushText);

         pgraphics->set_font(pframewindow, ::e_element_window_title);

         pgraphics->set_text_rendering_hint(::write_text::e_rendering_clear_type_grid_fit);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->draw_text(strWindowText, m_rectangleWindowText, e_align_left_center, e_draw_text_no_prefix);

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


   void frame::GetFrameRect(int_rectangle & rectangle)
   {

      m_pframewindow->window_rectangle(rectangle);

      rectangle.offset(-rectangle.top_left());

      rectangle.deflate(get_margin_rectangle());

   }


   ::experience::enum_frame frame::experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder)
   {
      //::item_pointer pitemHi etest = ::experience::e_frame_client;
      {
         //      m_pframewindow->GetEventWindow()->screen_to_client()(point);
         //::int_rectangle rectangleEvent;

         auto rectangleEvent = m_pframewindow->window_rectangle();

         ::int_rectangle rectangle;
         //::int_point pointCenter = rectangleEvent.center();
         enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();


         ::int_rectangle rectangleOuter(rectangleEvent);

         ::int_rectangle rectangleInner(rectangleEvent);

         rectangleInner.deflate(2);

         ::int_point pointHitTest = point;

         //               if(rectangleEvent.left() < 0)
         //                  pointHitTest.x() -= rectangleEvent.left();
         //               if(rectangleEvent.top() < 0)
         //                  pointHitTest.y() -= rectangleEvent.top();

         if (egrip & e_grip_top_left)
         {
            rectangle.top_left() = rectangleOuter.top_left();
            rectangle.bottom_right() = rectangleInner.top_left();
            if (rectangle.contains(pointHitTest))
            {
               return ::experience::e_frame_sizing_top_left;
               //goto SizingSuccess;
            }
         }
         if (egrip & e_grip_top_right)
         {
            rectangle.top() = rectangleOuter.top();
            rectangle.left() = rectangleInner.right();
            rectangle.bottom() = rectangleInner.top();
            rectangle.right() = rectangleOuter.right();
            if (rectangle.contains(pointHitTest))
            {
               return ::experience::e_frame_sizing_top_right;
               //goto SizingSuccess;
            }
         }
         if (egrip & e_grip_bottom_right)
         {
            rectangle.top_left() = rectangleInner.bottom_right();
            rectangle.bottom_right() = rectangleOuter.bottom_right();
            if (rectangle.contains(pointHitTest))
            {
               return ::experience::e_frame_sizing_bottom_right;
               //goto SizingSuccess;
            }
         }
         if (egrip & e_grip_bottom_left)
         {
            rectangle.top() = rectangleInner.bottom();
            rectangle.left() = rectangleOuter.left();
            rectangle.bottom() = rectangleOuter.bottom();
            rectangle.right() = rectangleInner.left();
            if (rectangle.contains(pointHitTest))
            {
               return ::experience::e_frame_sizing_bottom_left;
               //goto SizingSuccess;
            }
         }
         if (egrip & e_grip_top)
         {
            rectangle.top() = rectangleOuter.top();
            rectangle.left() = rectangleInner.left();
            rectangle.right() = rectangleInner.right();
            rectangle.bottom() = rectangleInner.top();
            if (rectangle.contains(pointHitTest))
            {
               return ::experience::e_frame_sizing_top;
               //goto SizingSuccess;
            }
         }
         if (egrip & e_grip_bottom)
         {
            rectangle.top() = rectangleInner.bottom();
            rectangle.left() = rectangleInner.left();
            rectangle.right() = rectangleInner.right();
            rectangle.bottom() = rectangleOuter.bottom();
            if (rectangle.contains(pointHitTest))
            {
               return ::experience::e_frame_sizing_bottom;
               //goto SizingSuccess;
            }
         }
         if (egrip & e_grip_left)
         {
            rectangle.top() = rectangleInner.top();
            rectangle.left() = rectangleOuter.left();
            rectangle.right() = rectangleInner.left();
            rectangle.bottom() = rectangleInner.bottom();
            if (rectangle.contains(pointHitTest))
            {
               return ::experience::e_frame_sizing_left;
               //goto SizingSuccess;
            }
         }
         if (egrip & e_grip_right)
         {
            rectangle.top() = rectangleInner.top();
            rectangle.left() = rectangleInner.right();
            rectangle.right() = rectangleOuter.right();
            rectangle.bottom() = rectangleInner.bottom();
            if (rectangle.contains(pointHitTest))
            {
               return ::experience::e_frame_sizing_right;
               //goto SizingSuccess;
            }
         }
         if (m_rectangleCaption.contains(pointHitTest))
         {
            return ::experience::e_frame_title_bar;
         }
         return ::experience::e_frame_client;
         //goto SizingNone;
      //SizingSuccess:
         //return etest;
      //SizingNone:
        // ;
      }
      //return  ::experience::e_frame_client;
   }


   void frame::GetBorderRectangle(const ::int_rectangle & rectangleOuter, ::int_rectangle * prectangle, enum_border eside)
   {

      auto rectangleInner = hosting_rectangle();

      ::int_rectangle rectangle;

      if (eside == e_border_top)
      {

         rectangle.left() = rectangleOuter.left();
         rectangle.right() = rectangleOuter.right();
         rectangle.top() = rectangleOuter.top();
         rectangle.bottom() = rectangleInner.top();

      }
      else if (eside == e_border_left)
      {

         rectangle.left() = rectangleOuter.left();
         rectangle.right() = rectangleInner.left();
         rectangle.top() = rectangleInner.top();
         rectangle.bottom() = rectangleInner.bottom();

      }
      else if (eside == e_border_right)
      {

         rectangle.left() = rectangleInner.right();
         rectangle.right() = rectangleOuter.right();
         rectangle.top() = rectangleInner.top();
         rectangle.bottom() = rectangleInner.bottom();

      }
      else if (eside == e_border_bottom)
      {

         rectangle.left() = rectangleOuter.left();
         rectangle.right() = rectangleOuter.right();
         rectangle.top() = rectangleInner.bottom();
         rectangle.bottom() = rectangleOuter.bottom();

      }

      *prectangle = rectangle;

   }



} // namespace experience_tranquillum



