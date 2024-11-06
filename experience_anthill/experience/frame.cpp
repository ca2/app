#include "framework.h"
#include "frame.h"
#include "control_box.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/fastblur.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/source.h"
#include "aura/graphics/image/icon.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/windowing/windowing.h"
#include "base/user/experience/frame_window.h"
#include "base/user/experience/size_manager.h"


namespace experience_anthill
{


   frame::frame()
   {

      m_pointWindowIcon.x() = 14;

      m_colorActiveCaptionTextBk = ::color::transparent;

      m_rectangleMarginNormal.set(5, 5, 5, 5);

      m_colorCaptionText = argb(255, 255, 255, 255);

   }


   frame::~frame()
   {

   }


   void frame::OnMove(::pointer<::user::interaction>pframewindow)
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


   void frame::Glass(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleParam)
   {

      auto pframewindow = m_pframewindow;

      ::int_rectangle rectangleX(rectangleParam);

      ::int_rectangle rectangleInflate;

      if (rectangleX.is_empty())
      {

         return;

      }

      int iInflate = 5; // raio 2 pixels + centro 1 pixel

      rectangleInflate = rectangleX;
      rectangleInflate.inflate(iInflate, iInflate);

      //::pointer<::user::interaction>puserinteractionDesktop = psystem->get_desktop_window();

      ::int_rectangle rectangleScreen;

      pframewindow->best_monitor(&rectangleScreen);

      ::image::image_pointer pimage1;

      ::image::image_pointer pimage2;

      pimage1 = image()->create_image({ rectangleX.width() + iInflate * 2,  rectangleX.height() + iInflate * 2 });

      pimage2 = image()->create_image({ rectangleX.width() + iInflate * 2,  rectangleX.height() + iInflate * 2 });
      ::int_rectangle rectangleWindow = rectangleX;
      pframewindow->client_to_screen()(rectangleWindow);
      //pimage = create_image({rectangleX.width(),  rectangleX.height()});
      //bool b = pimage2->get_graphics()->BitBlt(0, 0, rectangleX.width() + iInflate * 2, rectangleX.height() + iInflate * 2, pgraphics, rectangleX.left() - iInflate, rectangleX.top() - iInflate);

      {

         ::image::image_source imagesource(pgraphics,
            double_rectangle(::int_point(rectangleX.left() - iInflate, rectangleX.top() - iInflate), ::double_size(rectangleX.width() + iInflate * 2, rectangleX.height() + iInflate * 2)));

         auto rectangle = double_rectangle_dimension(0, 0, rectangleX.width() + iInflate * 2, rectangleX.height() + iInflate * 2);

         ::image::image_drawing_options imagedrawingoptions(rectangle);

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pimage2->get_graphics()->draw(imagedrawing);

      }
      //bool b = ::BitBlt(dc2, 0, 0, rectangleX.width() + iInflate * 2, rectangleX.height() + iInflate * 2, hdcScreen, rectangleX.left() - iInflate, rectangleX.top() - iInflate);

      m_pfastblur->blur(pimage1, ::int_rectangle(::int_size(rectangleX.width() + iInflate * 2, rectangleX.height() + iInflate * 2)));

      //spgraphics->Draw3dRect(rectangleX, 127 << 24, 127 << 24);
      //rectangleX.deflate(1, 1);
      //spgraphics->Draw3dRect(rectangleX, 64 << 24, 64 << 24);
      /*b = imaging.bitmap_blend(pgraphics, rectangle.left(), rectangle.top(),
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
      rectangle.left(), rectangle.top(),
      rectangleWindow.width(),
      rectangleWindow.height(),
      spgraphics->get_handle1(),
      0, 0,
      rectangleWindow.width(),
      rectangleWindow.height(),
      bf);*/

      {

         ::image::image_source imagesource(pimage1, ::double_rectangle(double_point(iInflate, iInflate), rectangleX.size()));

         ::image::image_drawing_options imagedrawingoptions(rectangleX);

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

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


   bool frame::get_element_rectangle(::int_rectangle & rectangle, enum_element eelement)
   {
      
      switch (eelement)
      {
      case e_element_top_left_icon:

         if (m_pframewindow == nullptr || m_pframewindow->get_draw_icon() == nullptr)
            return false;

         rectangle.left() = m_pointWindowIcon.x();
         rectangle.top() = m_pointWindowIcon.y();
         //rectangle.right() = rectangle.left() + m_pframewindow->m_picon->get_size().cx();
         //rectangle.bottom() = rectangle.top() + m_pframewindow->m_picon->get_size().cy();
         rectangle.right() = rectangle.left() + 24;
         rectangle.bottom() = rectangle.top() + 24;

         return true;

      case e_element_move_grip_minimal:

         if (m_pframewindow == nullptr || m_pframewindow->const_layout().design().display() != ::e_display_minimal)
            return false;

         //rectangle.left() = m_pointMoveGripMinimal.x() + 2;
         //rectangle.top() = m_pointMoveGripMinimal.y() + 2;
         rectangle.right() = rectangle.left() + get_caption_height() - 4;
         rectangle.bottom() = rectangle.top() + get_caption_height() - 4;

         return true;

      default:
         break;
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

      if (pcontrolbox)
      {

         pcontrolbox->set_button_color_system_default_001();

      }

      __construct(m_ppenText1);
      __construct(m_ppenFace1);
      __construct(m_ppenHilight1);
      __construct(m_ppenShadow1);
      __construct(m_ppenDkShadow1);


      m_minSize = int_size(144, 48);
      m_minSize.cy() = 48;

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


   void frame::Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleParam, enum_border eborder, color32_t crTopLeft, color32_t crBottomRight)
   {

      ::int_rectangle rectangle(rectangleParam);
      int x = rectangle.left();
      int y = rectangle.top();
      int cx = rectangle.width();
      int cy = rectangle.height();



      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::draw2d::pen_pointer ppen;

      if (eborder & e_border_top || eborder & e_border_left)
      {

         __construct(ppen);

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

         __construct(ppen);

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



   /*     void frame::on_style_change()
        {


        }*/


   void frame::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (!m_pframewindow->is_frame_experience_enabled())
      {

         return;

      }

      // 

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      auto pframewindow = m_pframewindow;

      if (!pframewindow->layout().is_full_screen() && !pframewindow->layout().is_zoomed() && !pframewindow->layout().is_iconic() && !m_pframewindow->frame_is_transparent() && m_pframewindow->m_bShowControlBox)
      {

         on_draw_frame(pgraphics);

      }

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      if (pframewindow->layout().is_minimal())
      {

         ::int_rectangle rectangleIcon;

         if (get_element_rectangle(rectangleIcon, e_element_top_left_icon))
         {

            auto pdrawicon = m_pframewindow->get_draw_icon();

            if (pdrawicon != nullptr)
            {

               ::image::image_source imagesource(pdrawicon);

               ::image::image_drawing_options imagedrawingoptions(rectangleIcon);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

         }

         ::int_rectangle rectangleGrip;

         if (get_element_rectangle(rectangleGrip, e_element_move_grip_minimal))
         {

            int i = 0;

            while (i < rectangleGrip.width() - 5 + 1)
            {

               pgraphics->draw_inset_3d_rectangle(int_rectangle_dimension(rectangleGrip.left() + i, rectangleGrip.top(), 3, rectangleGrip.height()), argb(110, 230, 230, 230), argb(110, 130, 130, 130), 1.0);

               i += 5;

            }

            //pgraphics->Draw3dRect(rectangleGrip.left() + 12,rectangleGrip.top(),3,rectangleGrip.height(),argb(190, 255, 255, 255),argb(190, 90, 90, 90));

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

         ::int_rectangle rectangleIcon;

         auto pframewindow = m_pframewindow;

         color32_t    crMoveableBorder;

         color32_t    crMoveableBorderHilight;

         color32_t    crMoveableBorderShadow;

         auto str = pframewindow->get_window_text();

         if (pframewindow->m_fActive)
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

         ::int_rectangle rectangle;



         pframewindow->window_rectangle(rectangle);

         rectangle -= rectangle.top_left();

         if (get_element_rectangle(rectangleIcon, e_element_top_left_icon))
         {

            auto pdrawicon = m_pframewindow->get_draw_icon();

            if (::is_ok(pdrawicon))
            {

               ::image::image_source imagesource(pdrawicon);

               ::image::image_drawing_options imagedrawingoptions(rectangleIcon);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

         }

         //class fonts & fonts = pdraw2d->fonts();

         auto pstyle = pframewindow->get_style(pgraphics);

         auto strWindowText = pframewindow->get_window_text();

         if(strWindowText.has_character())
         {

            auto pbrushText = __create<::draw2d::brush>();

            pbrushText->create_solid(m_colorCaptionText);

            pgraphics->set(pbrushText);

            pgraphics->set(pframewindow->get_font(pstyle));

            pgraphics->draw_text(strWindowText, m_rectangleWindowText, e_align_left_center, e_draw_text_no_prefix);

         }

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

      rectangle.deflate(10, 10);

   }


   ::experience::enum_frame frame::experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder)
   ////::item_pointer frame::experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder)
   {
      //::experience::enum_frame etest = ::e_element_client;
      //{
         //      m_pframewindow->GetEventWindow()->screen_to_client()(point);
         
      auto rectangleEvent = m_pframewindow->raw_rectangle();

      if (m_pframewindow->windowing()->has_readily_gettable_absolute_coordinates())
      {

         m_pframewindow->client_to_screen()(rectangleEvent);

      }

         ::int_rectangle rectangle;
         ::int_point pointCenter = rectangleEvent.center();
         enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();

         if (egrip & e_grip_top_left)
         {
            rectangle = rectangleEvent;
            rectangle.right() = rectangle.left() + 16;
            rectangle.bottom() = rectangle.top() + 5;
            if (rectangle.contains(point))
            {
               return ::experience::e_frame_sizing_top_left;
               // goto SizingSuccess;
            }
            rectangle = rectangleEvent;
            rectangle.right() = rectangle.left() + 5;
            rectangle.bottom() = rectangle.top() + 16;
            if (rectangle.contains(point))
            {
               return ::experience::e_frame_sizing_top_left;
               // goto SizingSuccess;
            }
         }
         if (egrip & e_grip_top_right)
         {
            rectangle = rectangleEvent;
            rectangle.left() = rectangle.right() - 16;
            rectangle.bottom() = rectangle.top() + 5;
            if (rectangle.contains(point))
            {
               return ::experience::e_frame_sizing_top_right;
               // goto SizingSuccess;
            }
            rectangle = rectangleEvent;
            rectangle.left() = rectangle.right() - 5;
            rectangle.bottom() = rectangle.top() + 16;
            if (rectangle.contains(point))
            {
               return ::experience::e_frame_sizing_top_right;
               // goto SizingSuccess;
            }
         }
         if (egrip & e_grip_bottom_right)
         {
            rectangle = rectangleEvent;
            rectangle.left() = rectangle.right() - 16;
            rectangle.top() = rectangle.bottom() - 5;
            if (rectangle.contains(point))
            {
               return ::experience::e_frame_sizing_bottom_right;
               // goto SizingSuccess;
            }
            rectangle = rectangleEvent;
            rectangle.left() = rectangle.right() - 5;
            rectangle.top() = rectangle.bottom() - 16;
            if (rectangle.contains(point))
            {
               return ::experience::e_frame_sizing_bottom_right;
               // goto SizingSuccess;
            }
         }
         if (egrip & e_grip_bottom_left)
         {
            rectangle = rectangleEvent;
            rectangle.right() = rectangle.left() + 16;
            rectangle.top() = rectangle.bottom() - 5;
            if (rectangle.contains(point))
            {
               return ::experience::e_frame_sizing_bottom_left;
               // goto SizingSuccess;
            }
            rectangle = rectangleEvent;
            rectangle.right() = rectangle.left() + 5;
            rectangle.top() = rectangle.bottom() - 16;
            if (rectangle.contains(point))
            {
               return ::experience::e_frame_sizing_bottom_left;
               // goto SizingSuccess;
            }
         }
         if (egrip & e_grip_top)
         {
            rectangle.top() = rectangleEvent.top();
            rectangle.left() = pointCenter.x() - 8;
            rectangle.right() = pointCenter.x() + 8;
            rectangle.bottom() = rectangleEvent.top() + 5;
            if (rectangle.contains(point))
            {
               return ::experience::e_frame_sizing_top;
               // goto SizingSuccess;
            }
         }
         if (egrip & e_grip_bottom)
         {
            rectangle.top() = rectangleEvent.bottom() - 5;
            rectangle.left() = pointCenter.x() - 8;
            rectangle.right() = pointCenter.x() + 8;
            rectangle.bottom() = rectangleEvent.bottom();
            if (rectangle.contains(point))
            {
               return ::experience::e_frame_sizing_bottom;
               // goto SizingSuccess;
            }
         }
         if (egrip & e_grip_left)
         {
            rectangle.top() = pointCenter.y() - 8;
            rectangle.left() = rectangleEvent.left();
            rectangle.right() = rectangleEvent.left() + 5;
            rectangle.bottom() = pointCenter.y() + 8;
            if (rectangle.contains(point))
            {
               return ::experience::e_frame_sizing_left;
               // goto SizingSuccess;
            }
         }
         if (egrip & e_grip_right)
         {
            rectangle.top() = pointCenter.y() - 8;
            rectangle.left() = rectangleEvent.right() - 5;
            rectangle.right() = rectangleEvent.right();
            rectangle.bottom() = pointCenter.y() + 8;
            if (rectangle.contains(point))
            {
               return ::experience::e_frame_sizing_right;
               // goto SizingSuccess;
            }
         }
         if (m_rectangleCaption.contains(point))
         {

            return ::experience::e_frame_title_bar;
         }
         return ::experience::e_frame_client;
      //   goto SizingNone;
      //SizingSuccess:
      //   return etest;
      //SizingNone:;
      //}
      //return ::e_element_client;
   }


   void frame::GetBorderRectangle(const ::int_rectangle & rectangleX, ::int_rectangle * lprect, enum_border eside)
   {

      ::int_rectangle rectangleBig(rectangleX);

      ::int_rectangle rectangleSmall;

      rectangleSmall = m_pframewindow->rectangle();

      ::int_rectangle rectangle;

      if (eside == e_border_top)
      {
         rectangle.left() = rectangleBig.left();
         rectangle.right() = rectangleBig.right();
         rectangle.top() = rectangleBig.top();
         rectangle.bottom() = rectangleSmall.top();
      }
      else if (eside == e_border_left)
      {
         rectangle.left() = rectangleBig.left();
         rectangle.right() = rectangleSmall.left();
         rectangle.top() = rectangleSmall.top();
         rectangle.bottom() = rectangleSmall.bottom();
      }
      else if (eside == e_border_right)
      {
         rectangle.left() = rectangleSmall.right();
         rectangle.right() = rectangleBig.right();
         rectangle.top() = rectangleSmall.top();
         rectangle.bottom() = rectangleSmall.bottom();
      }
      else if (eside == e_border_bottom)
      {
         rectangle.left() = rectangleBig.left();
         rectangle.right() = rectangleBig.right();
         rectangle.top() = rectangleSmall.bottom();
         rectangle.bottom() = rectangleBig.bottom();
      }
      *lprect = rectangle;
   }



} // namespace experience_anthill




