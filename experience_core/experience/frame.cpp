#include "framework.h"
#include "frame.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/source.h"
#include "aura/graphics/image/icon.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/imaging.h"
#include "aura/windowing/windowing.h"
#include "base/user/experience/control_box.h"
#include "base/user/experience/frame_window.h"
#include "base/user/experience/size_manager.h"


namespace experience_core
{


   frame::frame()
   {

      m_pointWindowIcon.x() = 5;

      m_sizeIcon.cx() = 32;

      m_sizeIcon.cy() = 32;

      m_colorCaptionText = argb(255, 0, 0, 0);

      //m_rectangleX.set(0, 0, 0, 0);

   }


   frame::~frame()
   {

   }


   void frame::on_initialize_experience_frame()
   {

      __construct(m_ppenText1);
      __construct(m_ppenFace1);
      __construct(m_ppenHilight1);
      __construct(m_ppenShadow1);
      __construct(m_ppenDkShadow1);


      /*               auto estyle = translate_style(m_strStyle);

            set_style(estyle)*/;

   }


   string frame::get_default_user_style() const
   {

      return "TranslucidWarmLiteGray";

   }


   void frame::on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::experience::frame::on_perform_top_down_layout(pgraphics);

      auto pointBottomRight = m_pframewindow->const_layout().layout().raw_rectangle().bottom_right();

      auto pointLastBottomRight = m_pframewindow->const_layout().window().raw_rectangle().bottom_right();

      if (pointBottomRight != pointLastBottomRight)
      {

         auto pointInnerBottomRight = pointBottomRight - ::size_i32(9, 9);

         auto pointInnerLastBottomRight = pointLastBottomRight - ::size_i32(9, 9);

         auto pointMinimumInnerBottomRight = pointInnerBottomRight.minimum(pointInnerLastBottomRight);

         ::rectangle_i32 rectangleLeft;

         rectangleLeft.left() = 0;
         rectangleLeft.right() = pointBottomRight.x();
         rectangleLeft.top() = 0;
         rectangleLeft.bottom() = 7;

         pgraphics->user_redraw()->set_need_redraw(rectangleLeft);

         ::rectangle_i32 rectangleTop;

         rectangleTop.left() = 0;
         rectangleTop.right() = 7;
         rectangleTop.top() = 0;
         rectangleTop.bottom() = pointBottomRight.y();

         pgraphics->user_redraw()->set_need_redraw(rectangleTop);

         ::rectangle_i32 rectangleRight;

         rectangleRight.left() = pointMinimumInnerBottomRight.a();
         rectangleRight.right() = pointBottomRight.x();
         rectangleRight.top() = 0;
         rectangleRight.bottom() = pointBottomRight.y();

         rectangleRight.normalize();

         pgraphics->user_redraw()->set_need_redraw(rectangleRight);

         ::rectangle_i32 rectangleBottom;

         rectangleBottom.left() = 0;
         rectangleBottom.right() = pointBottomRight.x();
         rectangleBottom.top() = pointMinimumInnerBottomRight.b();
         rectangleBottom.bottom() = pointBottomRight.y();

         rectangleBottom.normalize();

         pgraphics->user_redraw()->set_need_redraw(rectangleBottom);

      }

   }

   void frame::OnMove(::pointer<::user::interaction>pframewindow)
   {

      UNREFERENCED_PARAMETER(pframewindow);

   }


   void frame::Glass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleParam)
   {

      auto pframewindow = m_pframewindow;

      auto psystem = acmesystem()->m_paurasystem;

      auto imaging = psystem->imaging();

      ::rectangle_i32 rectangleX(rectangleParam);

      ::rectangle_i32 rectangleInflate;

      if (rectangleX.is_empty())
      {

         return;

      }


      i32 iInflate = 5; // raio 2 pixels + centro 1 pixel

      rectangleInflate = rectangleX;

      rectangleInflate.inflate(iInflate, iInflate);

      ::rectangle_i32 rectangleScreen;

      pframewindow->best_monitor(&rectangleScreen);

      ::image_pointer pimage1;

      ::image_pointer pimage2;

      pimage1 = m_pcontext->m_pauracontext->create_image({ rectangleX.width() + iInflate * 2,  rectangleX.height() + iInflate * 2 });

      pimage2 = m_pcontext->m_pauracontext->create_image({ rectangleX.width() + iInflate * 2,  rectangleX.height() + iInflate * 2 });

      ::rectangle_i32 rectangleWindow = rectangleX;

      pframewindow->client_to_screen()(rectangleWindow);

      ::point_i32 pointInflate(iInflate, iInflate);

      auto point = rectangleX.top_left();

      point -= pointInflate;

      //bool b;

      {

         rectangle_f64 rectangleSource(point, pimage1->get_size());

         image_source imagesource(pgraphics, rectangleSource);

         rectangle_f64 rectangleTarget(pimage1->get_size());

         image_drawing_options imagedrawingoptions(rectangleTarget);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         //b = 

         pimage2->g()->draw(imagedrawing);

      }

      //b = 

      imaging.blur(pimage2, 2);

      {

         rectangle_f64 rectangleSource(pointInflate, rectangleX.size());

         image_source imagesource(pimage2, rectangleSource);

         rectangle_f64 rectangleTarget(rectangleX);

         image_drawing_options imagedrawingoptions(rectangleTarget);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

      }

   }


   status < ::color::color > frame::get_border_main_body_color()
   {

      return rgb(63, 150, 106);

   }


   void frame::ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, const ::color::color & color32, ::u8 bAlpha)
   {

      pgraphics->fill_rectangle(rectangle, color32 & ::opacity(bAlpha));

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


   //frame::e_style frame::translate_style(const ::string & pszStyle)
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



   bool frame::get_element_rectangle(::rectangle_i32 & rectangle, enum_element eelement)
   {

      switch (eelement)
      {
      case e_element_top_left_icon:
      {

         auto pdrawicon = m_pframewindow->get_draw_icon();

         if (m_pframewindow == nullptr || pdrawicon == nullptr)
         {

            return false;

         }

         rectangle.left() = m_pointWindowIcon.x();
         rectangle.top() = m_pointWindowIcon.y();
         rectangle.right() = rectangle.left() + m_sizeIcon.cx();
         rectangle.bottom() = rectangle.top() + m_sizeIcon.cy();

         //rectangle.right() = rectangle.left() + pdrawicon->get_size().cx();
         //rectangle.bottom() = rectangle.top() + pdrawicon->get_size().cy();

         return true;

      }

      case e_element_move_grip_minimal:

         if (m_pframewindow == nullptr || m_pframewindow->const_layout().design().display() != ::e_display_minimal)
         {

            return false;

         }

         //rectangle.left() = m_pointMoveGripMinimal.x() + 2;
         //rectangle.top() = m_pointMoveGripMinimal.y() + 2;
         rectangle.right() = rectangle.left() + m_iCaptionHeight - 4;
         rectangle.bottom() = rectangle.top() + m_iCaptionHeight - 4;

         return true;

      default:
         break;
      }
      return false;

   }


   //   ::experience::enum_frame frame::experience_frame_hit_test(const ::point_i32 &point, ::user::e_zorder ezorder)
   //   {
   //
   //      return ::experience::frame::experience_frame_hit_test(point, ezorder);
   ////               ::rectangle_i32 rectangle;
   ////               for(enum_element eelement = (enum_element)(::e_element_none + 1);
   ////                     eelement < ElementEnd;
   ////                     eelement++)
   ////               {
   ////                  get_element_rectangle(rectangle, eelement);
   ////                  if(rectangle.contains(point))
   ////                  {
   ////                     eelementParam = eelement;
   ////                     return true;
   ////                  }
   ////               }
   ////               return false;
   //   }
   //

   void frame::set_moveable_border_color(const ::color::color & colorMoveableBorder)
   {

      m_colorMoveableBorder = colorMoveableBorder;

      ::color::color color;

      color = colorMoveableBorder;
      color.hls_rate(0.0, 0.5, 0.0);
      m_colorMoveableBorderHilight = color;
      m_colorMoveableBorderHilight.m_u8Opacity = 255;

      color = colorMoveableBorder;
      color.hls_rate(0.0, -0.3, 0.0);
      m_colorMoveableBorderShadow = color;
      m_colorMoveableBorderShadow.m_u8Opacity = 255;

      color = colorMoveableBorder;
      color.hls_rate(8.0, -0.8, 0.0);
      m_colorMoveableBorderDkShadow = color;
      m_colorMoveableBorderDkShadow.m_u8Opacity = 255;

      m_colorCaptionTextBk = m_colorMoveableBorderShadow;

   }


   void frame::set_button_color_schema_001(const ::color::color & colorMoveableBorder)
   {

      //               defer_create_user_schema(schema_button);

      //               ::color::color crBase = crMoveableBorder;
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

      auto psystem = acmesystem()->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(m_pframewindow);

      auto pstyle = pframewindow->get_style(pgraphics);

      m_ppenText1->create_solid(1, pframewindow->get_color(pstyle, ::e_element_button_text));
      m_ppenFace1->create_solid(1, pframewindow->get_color(pstyle, ::e_element_button_background));
      m_ppenHilight1->create_solid(1, pframewindow->get_color(pstyle, ::e_element_button_hilite));
      m_ppenShadow1->create_solid(1, pframewindow->get_color(pstyle, ::e_element_button_shadow));
      m_ppenDkShadow1->create_solid(1, pframewindow->get_color(pstyle, ::e_element_button_dark_shadow));
      m_colorDkShadow = pframewindow->get_color(pstyle, ::e_element_button_dark_shadow);
      m_colorFrameBorder = argb(255, 0, 0, 0);

   }


   void frame::on_style_change_001_and_002(::draw2d::graphics_pointer & pgraphics)
   {

      auto pcontrolbox = get_control_box();

      m_minSize = size_i32(144, 48);

      m_minSize.cy() = 48;

      if (pcontrolbox)
      {

         pcontrolbox->set_button_color_system_default_001();

      }

      set_frame_color_system_default_001();

      auto pframewindow = m_pframewindow;

      //auto estyle = pframewindow->m_estyle;

      auto colorBorder = pframewindow->get_moveable_border_color();

      set_moveable_border_color(colorBorder);

      set_button_color_schema_001(m_colorMoveableBorder);

      if (m_pframewindow->m_estyle == ::user::StyleTranslucidWarmGray || m_pframewindow->m_estyle == ::user::StyleDarkWarmBlue)
      {

         pcontrolbox->m_colorBackground = m_colorCaptionTextBk;

         m_colorCaptionText = argb(255, 255, 255, 255);

      }
      else if (m_pframewindow->m_estyle == ::user::StyleBlackPiano || m_pframewindow->m_estyle == ::user::StyleBlackBorder)
      {

         pcontrolbox->m_colorBackground = m_colorCaptionTextBk;

         m_colorCaptionText = argb(255, 255, 255, 255);

      }

   }


   //::color::color frame::get_style_moveable_border_color(::user::enum_style estyle)
   //{
   //   switch(m_pframewindow->m_estyle)
   //   {
   //   case ::user::StyleLightBlue:
   //   case ::user::StyleTranslucidLightBlue:
   //      return rgb(116, 160, 220);
   //   case ::user::StyleBlackPiano:
   //   case ::user::StyleBlackBorder:
   //      return rgb(0, 0, 0);
   //   case ::user::StyleTranslucidWarmGray:
   //      return argb(255, 190, 184, 177);
   //      break;
   //   case ::user::StyleDarkWarmBlue:
   //      return argb(255,34,54,75);
   //      break;
   //   case ::user::StyleLightGreen:
   //   case ::user::StyleTranslucidLightGreen:
   //      return rgb(116, 220, 160) | 0xff000000;
   //   case ::user::StyleRedOrange:
   //      return rgb(255, 170, 136) | 0xff000000;
   //   case ::user::StyleBlueRedPurple:
   //      return rgb(200, 100, 220) | 0xff000000;
   //   case ::user::StyleEveningSun:
   //      return rgb(255, 210, 100) | 0xff000000;
   //   case ::user::StyleTranslucidWarmLiteGray:
   //      return rgb(239, 230, 219) | 0xff000000;
   //   }


   //   // Light Green/Translucid Light Green
   //   return rgb(116, 220, 160) | 0xff000000;

   //}


   //bool frame::is_translucid_style(e_style estyle)
   //{


   //}


   void frame::Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleParam, enum_border eborder, const ::color::color & colorTopLeft, const ::color::color & colorBottomRight)
   {

      ::rectangle_i32 rectangle(rectangleParam);

      i32 x = rectangle.left();
      i32 y = rectangle.top();
      i32 cx = rectangle.width();
      i32 cy = rectangle.height();

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::draw2d::pen_pointer ppen;

      if (eborder & e_border_top || eborder & e_border_left)
      {

         ppen.create(this);

         ppen->create_solid(1.0, colorTopLeft);

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

      if ((eborder & e_border_right || eborder & e_border_bottom) && (!ppen || ppen->m_color != colorBottomRight))
      {

         ppen.create(this);

         ppen->create_solid(1.0, colorBottomRight);

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


   void frame::_on_style_change(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void frame::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //return; // abcxxx


      if (!m_pframewindow->is_frame_experience_enabled())
      {

         return;

      }

      //auto psession = get_session();

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      auto pframewindow = m_pframewindow;

      if (!pframewindow->layout().is_full_screen() && !pframewindow->layout().is_zoomed() && !pframewindow->layout().is_iconic() && !m_pframewindow->frame_is_transparent() && m_pframewindow->m_bShowControlBox)
      {

         on_draw_frame(pgraphics);

      }

      if (pframewindow->layout().is_minimal())
      {

         ::rectangle_i32 rectangleIcon;

         if (get_element_rectangle(rectangleIcon, e_element_top_left_icon))
         {

            auto pdrawicon = m_pframewindow->get_draw_icon();

            if (::is_set(pdrawicon))
            {

               image_source imagesource(pdrawicon);

               image_drawing_options imagedrawingoptions(rectangleIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

         }

         ::rectangle_i32 rectangleGrip;

         if (get_element_rectangle(rectangleGrip, e_element_move_grip_minimal))
         {

            int i = 0;

            while (i < rectangleGrip.width() - 5 + 1)
            {

               ::rectangle_f64 rectangle(rectangleGrip.left() + i, rectangleGrip.top(), 3, rectangleGrip.height());

               pgraphics->draw_inset_3d_rectangle(rectangle, argb(110, 230, 230, 230), argb(110, 130, 130, 130), 1.0);

               i += 5;

            }

         }

      }
      else if (!pframewindow->layout().is_full_screen() && !m_pframewindow->frame_is_transparent())
      {

         //pgraphics->fill_rectangle(m_rectangleCaptionTextBk, m_colorCaptionTextBk);
         pgraphics->fill_rectangle(m_rectangleCaption, m_colorCaptionTextBk);

         ::rectangle_i32 rectangleIcon;

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

            auto pstyle = pframewindow->get_style(pgraphics);

            crMoveableBorder = pframewindow->get_color(pstyle, ::e_element_button_background);

            crMoveableBorderHilight = pframewindow->get_color(pstyle, ::e_element_button_hilite);

            crMoveableBorderShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

         }

         ::rectangle_i32 rectangle;

         pframewindow->window_rectangle(rectangle);

         rectangle -= rectangle.top_left();

         if (get_element_rectangle(rectangleIcon, e_element_top_left_icon))
         {

            auto pdrawicon = m_pframewindow->get_draw_icon();

            if (::is_set(pdrawicon) && pdrawicon->is_ok())
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(pdrawicon);

               image_drawing_options imagedrawingoptions(rectangleIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

         }

         auto wstrWindowText = pframewindow->get_window_text();

         pgraphics->set_text_color(m_colorCaptionText);

         pgraphics->set_font(pframewindow, ::e_element_window_title);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->_DrawText(wstrWindowText, m_rectangleWindowText, { e_align_left, e_align_vertical_center }, e_draw_text_no_prefix);

      }


   }


   void frame::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

   }


   ::experience::enum_frame frame::experience_frame_hit_test(const ::point_i32 & pointCursor, ::user::e_zorder ezorder)
   {

      //::experience::enum_frame etest = ::item_t{::e_element_client;
      //{
         //      m_pframewindow->GetEventWindow()->screen_to_client()(point);

         auto rectangleEvent = m_pframewindow->raw_rectangle();

         if(m_pframewindow->windowing()->has_readily_gettable_absolute_coordinates())
         {

            m_pframewindow->client_to_screen()(rectangleEvent);

         }

         ::rectangle_i32 rectangle;
         ::point_i32 pointCenter = rectangleEvent.center();
         enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();

         ::point_i32 pointHitTest = pointCursor;

         //                  if(rectangleEvent.left() < 0)
         //                     pointHitTest.x() -= rectangleEvent.left();
         //                  if(rectangleEvent.top() < 0)
         //                     pointHitTest.y() -= rectangleEvent.top();

         if (egrip & e_grip_top_left)
         {
            rectangle = rectangleEvent;
            rectangle.right() = rectangle.left() + 16;
            rectangle.bottom() = rectangle.top() + 5;
            if (rectangle.contains(pointHitTest))
            {
               return ::experience::e_frame_sizing_top_left;
               // goto SizingSuccess;
            }
            rectangle = rectangleEvent;
            rectangle.right() = rectangle.left() + 5;
            rectangle.bottom() = rectangle.top() + 16;
            if (rectangle.contains(pointHitTest))
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
            if (rectangle.contains(pointHitTest))
            {
               return ::experience::e_frame_sizing_top_right;
               // goto SizingSuccess;
            }
            rectangle = rectangleEvent;
            rectangle.left() = rectangle.right() - 5;
            rectangle.bottom() = rectangle.top() + 16;
            if (rectangle.contains(pointHitTest))
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
            if (rectangle.contains(pointHitTest))
            {
               return ::experience::e_frame_sizing_bottom_right;
               // goto SizingSuccess;
            }
            rectangle = rectangleEvent;
            rectangle.left() = rectangle.right() - 5;
            rectangle.top() = rectangle.bottom() - 16;
            if (rectangle.contains(pointHitTest))
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
            if (rectangle.contains(pointHitTest))
            {
               return ::experience::e_frame_sizing_bottom_left;
               // goto SizingSuccess;
            }
            rectangle = rectangleEvent;
            rectangle.right() = rectangle.left() + 5;
            rectangle.top() = rectangle.bottom() - 16;
            if (rectangle.contains(pointHitTest))
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
            if (rectangle.contains(pointHitTest))
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
            if (rectangle.contains(pointHitTest))
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
            if (rectangle.contains(pointHitTest))
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
            if (rectangle.contains(pointHitTest))
            {
               return ::experience::e_frame_sizing_right;
               // goto SizingSuccess;
            }
         }
         return ::experience::e_frame_client;
//            return m_pframewindow->m_pitemClient;
      //   goto SizingNone;
      //SizingSuccess:
      //   return etest;
      //SizingNone:;
      //}
      //return ::item_t{::e_element_client;
   }


   //::item_pointer frame::experience_frame_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
   //{

   //   //::experience::enum_frame etest = ::item_t{::e_element_client;

   //   {
   //      //      m_pframewindow->screen_to_client()(point);
   //      ::rectangle_i32 rectangleEvent;
   //      m_pframewindow->window_rectangle(rectangleEvent);
   //      ::rectangle_i32 rectangle;
   //      ::point_i32 pointCenter = rectangleEvent.center();
   //      enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();

   //      ::point_i32 pointHitTest = point;

   //      //if(rectangleEvent.left() < 0)
   //      // pointHitTest.x() -= rectangleEvent.left();
   //      //if(rectangleEvent.top() < 0)
   //      // pointHitTest.y() -= rectangleEvent.top();

   //      if ((egrip & e_grip_top_left) == e_grip_top_left)
   //      {
   //         rectangle = rectangleEvent;
   //         rectangle.right() = rectangle.left() + 16;
   //         rectangle.bottom() = rectangle.top() + 5;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            return m_pframewindow->defer_item(::item_t{ ::e_element_sizing_top_left });
   //            // goto SizingSuccess;
   //         }
   //         rectangle = rectangleEvent;
   //         rectangle.right() = rectangle.left() + 5;
   //         rectangle.bottom() = rectangle.top() + 16;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            return m_pframewindow->defer_item(::item_t{ ::e_element_sizing_top_left });
   //            // goto SizingSuccess;
   //         }
   //      }
   //      if ((egrip & e_grip_top_right) == e_grip_top_right)
   //      {
   //         rectangle = rectangleEvent;
   //         rectangle.left() = rectangle.right() - 16;
   //         rectangle.bottom() = rectangle.top() + 5;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            return m_pframewindow->defer_item(::item_t{ ::e_element_sizing_top_right });
   //            // goto SizingSuccess;
   //         }
   //         rectangle = rectangleEvent;
   //         rectangle.left() = rectangle.right() - 5;
   //         rectangle.bottom() = rectangle.top() + 16;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            return m_pframewindow->defer_item(::item_t{ ::e_element_sizing_top_right });
   //            // goto SizingSuccess;
   //         }
   //      }
   //      if ((egrip & e_grip_bottom_right) == e_grip_bottom_right)
   //      {
   //         rectangle = rectangleEvent;
   //         rectangle.left() = rectangle.right() - 16;
   //         rectangle.top() = rectangle.bottom() - 5;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            return m_pframewindow->defer_item(::item_t{ ::e_element_sizing_bottom_right });
   //            // goto SizingSuccess;
   //         }
   //         rectangle = rectangleEvent;
   //         rectangle.left() = rectangle.right() - 5;
   //         rectangle.top() = rectangle.bottom() - 16;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            return m_pframewindow->defer_item(::item_t{ ::e_element_sizing_bottom_right });
   //            // goto SizingSuccess;
   //         }
   //      }
   //      if ((egrip & e_grip_bottom_left) == e_grip_bottom_left)
   //      {
   //         rectangle = rectangleEvent;
   //         rectangle.right() = rectangle.left() + 16;
   //         rectangle.top() = rectangle.bottom() - 5;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            return m_pframewindow->defer_item(::item_t{ ::e_element_sizing_bottom_left });
   //            // goto SizingSuccess;
   //         }
   //         rectangle = rectangleEvent;
   //         rectangle.right() = rectangle.left() + 5;
   //         rectangle.top() = rectangle.bottom() - 16;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            return m_pframewindow->defer_item(::item_t{ ::e_element_sizing_bottom_left });
   //            // goto SizingSuccess;
   //         }
   //      }
   //      if ((egrip & e_grip_top) == e_grip_top)
   //      {
   //         rectangle.top() = rectangleEvent.top();
   //         rectangle.left() = pointCenter.x() - 8;
   //         rectangle.right() = pointCenter.x() + 8;
   //         rectangle.bottom() = rectangleEvent.top() + 5;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            return m_pframewindow->defer_item(::item_t{ ::e_element_sizing_top });
   //            // goto SizingSuccess;
   //         }
   //      }
   //      if ((egrip & e_grip_bottom) == e_grip_bottom)
   //      {
   //         rectangle.top() = rectangleEvent.bottom() - 5;
   //         rectangle.left() = pointCenter.x() - 8;
   //         rectangle.right() = pointCenter.x() + 8;
   //         rectangle.bottom() = rectangleEvent.bottom();
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            return m_pframewindow->defer_item(::item_t{ ::e_element_sizing_bottom });
   //            // goto SizingSuccess;
   //         }
   //      }
   //      if ((egrip & e_grip_left) == e_grip_left)
   //      {
   //         rectangle.top() = pointCenter.y() - 8;
   //         rectangle.left() = rectangleEvent.left();
   //         rectangle.right() = rectangleEvent.left() + 5;
   //         rectangle.bottom() = pointCenter.y() + 8;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            return m_pframewindow->defer_item(::item_t{ ::e_element_sizing_left });
   //            // goto SizingSuccess;
   //         }
   //      }
   //      if ((egrip & e_grip_right) == e_grip_right)
   //      {
   //         rectangle.top() = pointCenter.y() - 8;
   //         rectangle.left() = rectangleEvent.right() - 5;
   //         rectangle.right() = rectangleEvent.right();
   //         rectangle.bottom() = pointCenter.y() + 8;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            return m_pframewindow->defer_item(::item_t{ ::e_element_sizing_right });
   //            // goto SizingSuccess;
   //         }
   //      }
   //      goto SizingNone;
   //   SizingSuccess:
   //      return etest;
   //   SizingNone:;
   //   }
   //   return ::item_t{::e_element_client;
   //}

   
   void frame::place_set_need_redraw(const ::rectangle_i32 & rectangleAfter, const ::rectangle_i32 & rectangleBefore, ::draw2d::graphics * pgraphics)
   {

      auto rectangle = rectangleAfter.get_union(rectangleBefore);
   
      m_pframewindow->set_need_redraw({ rectangle }, pgraphics);

   }


   void frame::GetBorderRectangle(const ::rectangle_i32 & rectangleOuter, ::rectangle_i32 * lprect, enum_border eside)
   {

      ::rectangle_i32 rectangleHosting;

      rectangleHosting = m_pframewindow->hosting_rectangle();

      ::rectangle_i32 rectangle;

      if (eside == e_border_top)
      {

         rectangle.left() = rectangleOuter.left();
         rectangle.right() = rectangleOuter.right();
         rectangle.top() = rectangleOuter.top();
         rectangle.bottom() = rectangleHosting.top();

      }
      else if (eside == e_border_left)
      {

         rectangle.left() = rectangleOuter.left();
         rectangle.right() = rectangleHosting.left();
         rectangle.top() = rectangleHosting.top();
         rectangle.bottom() = rectangleHosting.bottom();

      }
      else if (eside == e_border_right)
      {

         rectangle.left() = rectangleHosting.right();
         rectangle.right() = rectangleOuter.right();
         rectangle.top() = rectangleHosting.top();
         rectangle.bottom() = rectangleHosting.bottom();

      }
      else if (eside == e_border_bottom)
      {
         
         rectangle.left() = rectangleOuter.left();
         rectangle.right() = rectangleOuter.right();
         rectangle.top() = rectangleHosting.bottom();
         rectangle.bottom() = rectangleOuter.bottom();

      }
      
      *lprect = rectangle;

   }


   void frame::GetBorderRectangle(const ::rectangle_i32 & rectangleOuter, int iDeflate, ::rectangle_i32 * lprect, enum_border eside)
   {

      enum_display edisplay = m_pframewindow->const_layout().design().display();

      ::rectangle_i32 rectangleInner(rectangleOuter);

      rectangleInner.deflate(
         edisplay & e_display_left ? 0 : 1,
         edisplay & e_display_top ? 0 : 1,
         edisplay & e_display_right ? 0 : 1,
         edisplay & e_display_bottom ? 0 : 1);

      ::rectangle_i32 rectangle;

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
      *lprect = rectangle;
   }


   ::rectangle_i32 frame::outer_frame()
   {

      auto rectangle = m_pframewindow->raw_rectangle();

      rectangle.deflate(3);

      return rectangle;

   }


} // namespace experience



