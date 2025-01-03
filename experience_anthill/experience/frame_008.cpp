#include "framework.h"
#include "frame_008.h"
#include "control_box.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/pen.h"
#include "base/user/experience/frame_window.h"
#include "base/user/experience/size_manager.h"
#include "base/user/experience/dock_manager.h"
#include "base/user/experience/move_manager.h"


#define GRIP_CORNER_LARGE_CX 16
#define GRIP_CORNER_SMALL_CX 5
#define GRIP_CORNER_LARGE_CY 16
#define GRIP_CORNER_SMALL_CY 5


#define GRIP_CENTER_LARGE_CX 36
#define GRIP_CENTER_SMALL_CX 7
#define GRIP_CENTER_LARGE_CY 36
#define GRIP_CENTER_SMALL_CY 7


namespace experience_anthill
{


   frame_008::frame_008()
   {

      m_bHollow = false;

      m_rectangleCaptionTextPadding.left() = 4;
      m_rectangleCaptionTextPadding.right() = 4;
      m_rectangleCaptionTextPadding.top() = 0;
      m_rectangleCaptionTextPadding.bottom() = 0;


      // set_style(StyleTranslucidWarmLiteGray);


      m_rectangleMarginNormal.set(10, 10, 10, 10);



   }


   frame_008::~frame_008()
   {

   }


   void frame_008::initialize(::particle* pparticle)
   {

      frame::initialize(pparticle);


      __øconstruct(m_ppenHollow1);
      __øconstruct(m_ppenHollow2);
      __øconstruct(m_ppenHollow3);
      __øconstruct(m_ppenHollow4);
      __øconstruct(m_ppenHollow5);

   }

   //string frame_008::get_default_user_style() const
   //{

   //   return "TranslucidWarmLiteGray";

   //}




   // ::experience::enum_frame frame_008::experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder)
   //{
   //    ::experience::enum_frame etest = ::experience::e_frame_client;
   //   {
   //      //      m_pframewindow->GetEventWindow()->screen_to_client()(point);
   //      ::int_rectangle rectangleEvent;
   //      m_pframewindow->window_rectangle(rectangleEvent);
   //      ::int_rectangle rectangle;
   //      //::int_point pointCenter = rectangleEvent.center();
   //      enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();

   //      ::int_point pointHitTest = point;

   //      //                  if(rectangleEvent.left() < 0)
   //      //                     pointHitTest.x() -= rectangleEvent.left();
   //      //                  if(rectangleEvent.top() < 0)
   //      //                     pointHitTest.y() -= rectangleEvent.top();

   //      if (egrip & e_grip_top_left)
   //      {
   //         rectangle = rectangleEvent;
   //         rectangle.right() = rectangle.left() + 16;
   //         rectangle.bottom() = rectangle.top() + 5;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            etest = ::experience::e_frame_sizing_top_left;
   //            goto SizingSuccess;
   //         }
   //         rectangle = rectangleEvent;
   //         rectangle.right() = rectangle.left() + 5;
   //         rectangle.bottom() = rectangle.top() + 16;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            etest = ::experience::e_frame_sizing_top_left;
   //            goto SizingSuccess;
   //         }
   //      }
   //      if (egrip & e_grip_top_right)
   //      {
   //         rectangle = rectangleEvent;
   //         rectangle.left() = rectangle.right() - 16;
   //         rectangle.bottom() = rectangle.top() + 5;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            etest = ::experience::e_frame_sizing_top_right;
   //            goto SizingSuccess;
   //         }
   //         rectangle = rectangleEvent;
   //         rectangle.left() = rectangle.right() - 5;
   //         rectangle.bottom() = rectangle.top() + 16;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            etest = ::experience::e_frame_sizing_top_right;
   //            goto SizingSuccess;
   //         }
   //      }
   //      if (egrip & e_grip_bottom_right)
   //      {
   //         rectangle = rectangleEvent;
   //         rectangle.left() = rectangle.right() - 16;
   //         rectangle.top() = rectangle.bottom() - 5;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            etest = ::experience::e_frame_sizing_bottom_right;
   //            goto SizingSuccess;
   //         }
   //         rectangle = rectangleEvent;
   //         rectangle.left() = rectangle.right() - 5;
   //         rectangle.top() = rectangle.bottom() - 16;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            etest = ::experience::e_frame_sizing_bottom_right;
   //            goto SizingSuccess;
   //         }
   //      }
   //      if (egrip & e_grip_bottom_left)
   //      {
   //         rectangle = rectangleEvent;
   //         rectangle.right() = rectangle.left() + 16;
   //         rectangle.top() = rectangle.bottom() - 5;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            etest = ::experience::e_frame_sizing_bottom_left;
   //            goto SizingSuccess;
   //         }
   //         rectangle = rectangleEvent;
   //         rectangle.right() = rectangle.left() + 5;
   //         rectangle.top() = rectangle.bottom() - 16;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            etest = ::experience::e_frame_sizing_bottom_left;
   //            goto SizingSuccess;
   //         }
   //      }
   //      if (egrip & e_grip_top)
   //      {
   //         rectangle.top() = rectangleEvent.top();
   //         rectangle.left() = rectangleEvent.left();
   //         rectangle.right() = rectangleEvent.right();
   //         rectangle.bottom() = rectangleEvent.top() + 5;
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            etest = ::experience::e_frame_sizing_top;
   //            goto SizingSuccess;
   //         }
   //      }
   //      if (egrip & e_grip_bottom)
   //      {
   //         rectangle.top() = rectangleEvent.bottom() - 5;
   //         rectangle.left() = rectangleEvent.left();
   //         rectangle.right() = rectangleEvent.right();
   //         rectangle.bottom() = rectangleEvent.bottom();
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            etest = ::experience::e_frame_sizing_bottom;
   //            goto SizingSuccess;
   //         }
   //      }
   //      if (egrip & e_grip_left)
   //      {
   //         rectangle.top() = rectangleEvent.top();
   //         rectangle.left() = rectangleEvent.left();
   //         rectangle.right() = rectangleEvent.left() + 5;
   //         rectangle.bottom() = rectangleEvent.bottom();
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            etest = ::experience::e_frame_sizing_left;
   //            goto SizingSuccess;
   //         }
   //      }
   //      if (egrip & e_grip_right)
   //      {
   //         rectangle.top() = rectangleEvent.top();
   //         rectangle.left() = rectangleEvent.right() - 5;
   //         rectangle.right() = rectangleEvent.right();
   //         rectangle.bottom() = rectangleEvent.bottom();
   //         if (rectangle.contains(pointHitTest))
   //         {
   //            etest = ::experience::e_frame_sizing_right;
   //            goto SizingSuccess;
   //         }
   //      }
   //      goto SizingNone;
   //   SizingSuccess:
   //      return etest;
   //   SizingNone:
   //      ;
   //   }
   //   return ::experience::e_frame_client;
   //}






   void frame_008::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX, enum_border eside)
   {

      auto pframewindow = m_pframewindow;

      if (pframewindow == nullptr)
      {

         return;

      }

      //  

      auto estyle = get_style();

      ::color::color    colorMoveableBorder;
      ::color::color    colorMoveableBorderHilight;
      ::color::color    colorMoveableBorderShadow;

      if (pframewindow->m_fActive)
      {
         colorMoveableBorder = m_colorMoveableBorder;
         colorMoveableBorderHilight = m_colorMoveableBorderHilight;
         colorMoveableBorderShadow = m_colorMoveableBorderShadow;
      }
      else
      {

         // 

         auto pstyle = pframewindow->get_style(pgraphics);

         colorMoveableBorder = pframewindow->get_color(pstyle, ::e_element_button_background);

         colorMoveableBorderHilight = pframewindow->get_color(pstyle, ::e_element_button_hilite);

         colorMoveableBorderShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

      }

      enum_dock edock = m_pframewindow->dock_manager()->get_dock_mask();
      ::int_rectangle rectangleA(rectangleX);

      if (m_bHollow)
      {

         int iR = 128;
         int iG = 128;
         int iB = 128;

         auto estyle = get_style();

         if (pframewindow->m_fActive)
         {

            if (estyle == ::user::StyleDarkRed)
            {

               iR = 220;
               iG = 40;
               iB = 60;

            }
            else if (estyle == ::user::StyleRedOrange)
            {

               iR = 255;
               iG = 170;
               iB = 136;

            }
            else if (estyle == ::user::StyleLightGreen)
            {

               iR = 128;
               iG = 230;
               iB = 150;

            }
            else
            {

               iR = 0x07;
               iG = 0x6D;
               iB = 0x91;

            }

         }

         ::int_rectangle rectangleA(rectangleX);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

         pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

         auto rectangle = get_margin_rectangle();


         for (::collection::index i = 0; i < 11; i++)
         {

            auto ppen = __øcreate < ::draw2d::pen >();

            ppen->create_solid(1.0, argb((unsigned char)((i + 1) * 10), iR, iG, iB));

            pgraphics->set(ppen);

            pgraphics->draw_rect_side(rectangleA, eside);

            rectangleA.deflate(
               rectangle.left() > 0 ? 1 : 0,
               rectangle.top() > 0 ? 1 : 0,
               rectangle.right() > 0 ? 1 : 0,
               rectangle.bottom() > 0 ? 1 : 0);

         }

         //if (m_pframewindow->is_active_window())
         //{

         //   ::int_rectangle rectangleA(rectangleX);

         //   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         //   pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

         //   for (::collection::index i = 0; i < 9; i++)
         //   {

         //      pgraphics->draw_round_rect(rectangleA, pen, (int) (10 - i));

         //      rectangleA.deflate(1, 1, 1, 1);

         //   }

         //   //rectangleA.deflate(9, 9, 9, 9);

         //   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

         //   pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);




      }
      else if (estyle == ::user::StyleLightBlue || estyle == ::user::StyleRedOrange)
      {
         //rectangleA.deflate(1,1,1,1);
         Draw3dRectSide(pgraphics, rectangleA, eside, colorMoveableBorderHilight, ::color::transparent);//m_colorMoveableBorderDkShadow);

         //if(!m_bHollow)
         //{

         //   rectangleA.deflate(1,1,1,1);
         //   Draw3dRectSide(pgraphics,rectangleA,eside,crMoveableBorderHilight,crMoveableBorderShadow);

         //   rectangleA.deflate(1,1,1,1);
         //   Draw3dRectSide(pgraphics,rectangleA,eside,crMoveableBorder,crMoveableBorder);

         //   rectangleA.deflate(1,1,1,1);
         //   Draw3dRectSide(pgraphics,rectangleA,eside,crMoveableBorder,crMoveableBorder);

         //   ::int_rectangle rectangle;
         //   GetBorderRectangle(rectangleX, &rectangle, eside);
         //   class imaging & imaging = psystem->imaging();
         //   imaging.fill_rectangle(pgraphics,
         //      rectangle,
         //      crMoveableBorder,
         //      127);

         //}

      }
      else if (estyle == ::user::StyleTranslucidWarmGray
         || estyle == ::user::StyleTranslucidLightBlue
         || estyle == ::user::StyleTranslucidLightGreen)
      {
         ::int_rectangle rectangle;
         GetBorderRectangle(rectangleX, &rectangle, eside);

         pgraphics->fill_rectangle(
            rectangle,
            colorMoveableBorder &
            127_opacity);
      }
      else
      {
         ::int_rectangle rectangle;
         GetBorderRectangle(rectangleX, &rectangle, eside);

         pgraphics->fill_rectangle(
            rectangle,
            colorMoveableBorder &
            127_opacity);

         ::int_rectangle rectangleXB = rectangleA;

         rectangleXB.bottom()--;
         rectangleXB.right()--;

         rectangleA.top()++;
         rectangleA.bottom()--;
         rectangleA.left()++;
         rectangleA.right()--;
         if (edock == e_dock_none)
         {
            Draw3dRectSide(pgraphics, rectangleA, eside, m_colorDkShadow, m_colorDkShadow);
         }

         rectangleA.top()++;
         rectangleA.bottom()--;
         rectangleA.left()++;
         rectangleA.right()--;
         Draw3dRectSide(pgraphics, rectangleA, eside, m_colorDkShadow, m_colorDkShadow);

         rectangleA.top()++;
         rectangleA.bottom()--;
         rectangleA.left()++;
         rectangleA.right()--;
         if (edock == e_dock_none)
         {
            Draw3dRectSide(pgraphics, rectangleA, eside, m_colorDkShadow, m_colorDkShadow);
         }
      }

   }


   void frame_008::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
   {

      auto pframewindow = m_pframewindow;

      if (pframewindow == nullptr)
         return;

      if (!pframewindow->is_frame_experience_enabled())
         return;

      string str;


      ::int_rectangle rectangleNClient;

      pframewindow->window_rectangle(rectangleNClient);

      rectangleNClient -= rectangleNClient.top_left();

      ////////////////////
      //
      // Routine:
      // draw frame border
      //
      ////////////////////


      if (!pframewindow->layout().is_full_screen())
      {
         DrawBorder(pgraphics, rectangleNClient);
      }



   }


   void frame_008::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX)
   {

      auto pmovemanager = m_pframewindow->move_manager();

      enum_border eborder = pmovemanager->GetBorderMask();

      if (m_pframewindow->layout().is_zoomed())
      {
         eborder = (enum_border)
            (eborder &
               ~(e_border_right
                  | e_border_bottom
                  | e_border_left));
      }



      //if(m_bHollow)
      //{
      //   //return;
      //   ::int_rectangle rectangleA(rectangleX);

      //   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

      //   pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

      //   for (::collection::index i = 0; i < 9; i++)
      //   {

      //      pgraphics->draw_inset_3d_rectangle(rectangleA, argb(0, 0, 0, 0), argb(0, 0, 0, 0));

      //      rectangleA.deflate(1, 1, 1, 1);

      //   }

      //   if (m_pframewindow->is_active_window())
      //   {

      //      ::int_rectangle rectangleA(rectangleX);

      //      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      //      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

      //      for (::collection::index i = 0; i < 9; i++)
      //      {

      //         auto ppen = __øcreate < ::draw2d::pen > ();

      //         ppen->create_solid(1.0, argb((i+1) * 5, 0, 0, 0));

      //         pgraphics->draw_round_rect(rectangleA, pen, (int) (10 - i));

      //         rectangleA.deflate(1, 1, 1, 1);

      //      }

      //      //rectangleA.deflate(9, 9, 9, 9);

      //      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

      //      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);


      //      if (m_estyle == StyleRedOrange)
      //      {

      //         pgraphics->draw_inset_3d_rectangle(rectangleA, argb(255, 255, 170, 136), argb(255, 255, 170, 136));

      //      }
      //      else if (m_estyle == StyleLightGreen)
      //      {

      //         pgraphics->draw_inset_3d_rectangle(rectangleA, argb(255, 128, 230, 150), argb(255, 128, 230, 150));

      //      }
      //      else
      //      {

      //         pgraphics->draw_inset_3d_rectangle(rectangleA, argb(255, 0x07, 0x6D, 0x91), argb(255, 0x07, 0x6D, 0x91));

      //      }

      //   }
      //   else
      //   {

      //      //rectangleA.deflate(9, 9, 9, 9);
      //      pgraphics->draw_inset_3d_rectangle(rectangleA, argb(255, 128, 128, 128), argb(255, 128, 128, 128));
      //   }


      //}
      //else
      {

         if (eborder & e_border_top)
         {
            draw_border_side(pgraphics, rectangleX, e_border_top);
         }
         if (eborder & e_border_right)
         {
            draw_border_side(pgraphics, rectangleX, e_border_right);
         }
         if (eborder & e_border_bottom)
         {
            draw_border_side(pgraphics, rectangleX, e_border_bottom);
         }
         if (eborder & e_border_left)
         {
            draw_border_side(pgraphics, rectangleX, e_border_left);
         }

      }

   }

   //void frame_008::GetBorderRectangle(
   //   const ::int_rectangle & rectangleX,
   //   ::int_rectangle * lprect,
   //   enum_border eside)
   //{
   //   ::int_rectangle rectangleBig(rectangleX);
   //   ::int_rectangle rectangleSmall;

   //   rectangleSmall = m_pframewindow->rectangle();

   //   ::int_rectangle rectangle;
   //   if (eside == e_border_top)
   //   {
   //      rectangle.left() = rectangleBig.left();
   //      rectangle.right() = rectangleBig.right();
   //      rectangle.top() = rectangleBig.top();
   //      rectangle.bottom() = rectangleSmall.top();
   //   }
   //   else if (eside == e_border_left)
   //   {
   //      rectangle.left() = rectangleBig.left();
   //      rectangle.right() = rectangleSmall.left();
   //      rectangle.top() = rectangleSmall.top();
   //      rectangle.bottom() = rectangleSmall.bottom();
   //   }
   //   else if (eside == e_border_right)
   //   {
   //      rectangle.left() = rectangleSmall.right();
   //      rectangle.right() = rectangleBig.right();
   //      rectangle.top() = rectangleSmall.top();
   //      rectangle.bottom() = rectangleSmall.bottom();
   //   }
   //   else if (eside == e_border_bottom)
   //   {
   //      rectangle.left() = rectangleBig.left();
   //      rectangle.right() = rectangleBig.right();
   //      rectangle.top() = rectangleSmall.bottom();
   //      rectangle.bottom() = rectangleBig.bottom();
   //   }
   //   *lprect = rectangle;
   //}


   void frame_008::_on_style_change(::draw2d::graphics_pointer & pgraphics)
   {

      frame::on_style_change();

      on_style_change_001_and_002(pgraphics);

      auto colorMoveableBorder = m_colorMoveableBorder;

      m_colorActiveCaptionTextBk = colorMoveableBorder;

      auto colorMoveableInactive = colorMoveableBorder;

      colorMoveableBorder.make_black_and_white();

      m_colorActiveCaptionTextBk = m_pframewindow->get_moveable_border_color();

      auto estyle = get_style();

      if (estyle == ::user::StyleDarkRed)
      {
         //m_ppenHollow1->create_solid(1.0, argb(20, 0, 0, 0));
         //m_ppenHollow2->create_solid(1.0, argb(60, 20, 20, 20));
         //m_ppenHollow3->create_solid(1.0, argb(100, 40, 40, 40));
         //m_ppenHollow4->create_solid(1.0, argb(140, 60, 60, 60));
         //m_ppenHollow5->create_solid(1.0, argb(255, 90, 220, 100));
         m_colorCaptionTextBk = argb(255, 135, 32, 32);
         m_colorActiveCaptionTextBk = argb(255, 165, 32, 32);
         //                  create_color(::user::color_button_background, argb(255, 165, 32, 32));
         //                  create_color(::user::color_button_background_hover, argb(255, 195, 64, 64));
         //                  create_color(::user::color_button_background_press, argb(255, 208, 72, 72));

         if (m_pcontrolbox)
         {


            m_pcontrolbox->m_ppenButtonBack->create_solid(2, argb(255, 255, 180, 170));
            m_pcontrolbox->m_ppenButtonBackSel->create_solid(2, argb(255, 255, 255, 255));


         }

      }
      else if (estyle == ::user::StyleLightGreen)
      {
         //m_ppenHollow1->create_solid(1.0, argb(20, 0, 0, 0));
         //m_ppenHollow2->create_solid(1.0, argb(60, 20, 20, 20));
         //m_ppenHollow3->create_solid(1.0, argb(100, 40, 40, 40));
         //m_ppenHollow4->create_solid(1.0, argb(140, 60, 60, 60));
         //m_ppenHollow5->create_solid(1.0, argb(255, 90, 220, 100));
         m_colorCaptionTextBk = argb(255, 200, 200, 200);
         m_colorActiveCaptionTextBk = argb(255, 140, 200, 160);
      }
      else
      {
         m_colorCaptionTextBk = argb(255, 200, 200, 200);
         m_colorActiveCaptionTextBk = argb(255, 0x07, 0x6D, 0x91);
         //m_ppenHollow1->create_solid(1.0, argb(20, 50, 100, 200));
         //m_ppenHollow2->create_solid(1.0, argb(60, 50, 100, 200));
         //m_ppenHollow3->create_solid(1.0, argb(100, 50, 100, 200));
         //m_ppenHollow4->create_solid(1.0, argb(140, 50, 100, 200));
         //m_ppenHollow5->create_solid(1.0, argb(255, 50, 100, 200));
      }

      if (m_pcontrolbox.is_set())
      {

         //m_pcontrolbox->m_pbrushButtonBackSel = m_pcontrolbox->m_pbrushButtonBack;
         //m_pcontrolbox->m_ppenButtonBackSel = m_pcontrolbox->m_ppenButtonBack;
         //m_pcontrolbox->m_colorButtonForeSel = m_pcontrolbox->m_colorButtonFore;

      }

   }


   //color32_t frame_008::get_border_main_body_color()
   //{

   //   auto estyle = get_style();

   //   if (estyle == ::user::StyleRedOrange)
   //   {

   //      return argb(255, 255, 170, 136);

   //   }
   //   else
   //   {

   //      return argb(255, 50, 100, 200);

   //   }

   //}


//            bool frame_008::get_color(color32_t & color32, ::user::e_color ecolor, ::user::style_context * pcontext)
//            {
//
//               //if (m_estyle == StyleLightGreen)
//               //{
//
//               //   if (ecolor == ::user::color_face_lite)
//               //   {
//
//               //      color32 = argb(80, 160, 160, 160);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_text)
//               //   {
//
//               //      color32 = argb(200, 80, 80, 80);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_text_hover)
//               //   {
//
//               //      color32 = argb(200, 80, 80, 80);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_text_highlight)
//               //   {
//
//               //      color32 = argb(200, 80, 80, 80);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_background_hover)
//               //   {
//
//               //      color32 = argb(20, 0, 0, 0);
//
//               //      return true;
//
//               //   }
//
//               //   return ::experience::frame::get_color(color32, ecolor, pcontext );
//
//               //}
//               //else // if (m_estyle != StyleLightGreen)
//               //{
//
//               //   if (ecolor == ::user::color_background)
//               //   {
//
//               //      color32 = argb(255, 255, 255, 255);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_list_background)
//               //   {
//
//               //      color32 = argb(255, 255, 255, 255);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_edit_background)
//               //   {
//
//               //      color32 = argb(255, 255, 255, 255);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_tree_background)
//               //   {
//
//               //      color32 = argb(255, 255, 255, 255);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_impact_background)
//               //   {
//
//               //      color32 = argb(255, 255, 255, 255);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_scrollbar_background)
//               //   {
//
//               //      color32 = argb(255, 255, 255, 255);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_tab_layout_background)
//               //   {
//
//               //      color32 = argb(255, 255, 255, 255);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_tab_client_background)
//               //   {
//
//               //      color32 = argb(255, 0xF3, 0XF5, 0xF5);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_split_layout_background)
//               //   {
//
//               //      color32 = argb(255, 255, 255, 255);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_background_selected)
//               //   {
//
//               //      color32 = argb(255, 155, 185, 255);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_list_header)
//               //   {
//
//               //      color32 = argb(255, 255, 255, 255);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_list_header_background)
//               //   {
//
//               //      color32 = argb(255, 0x58, 0x5C, 0x5D);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_list_item_background)
//               //   {
//
//               //      color32 = argb(30, 0, 0, 0);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_list_header_separator)
//               //   {
//
//               //      color32 = 0;
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_toolbar_background)
//               //   {
//
//               //      color32 = argb(255, 0xF3, 0XF5, 0xF5);
//
//               //      return true;
//
//
//               //   }
//               //   else if (ecolor == ::user::color_button_background_disabled)
//               //   {
//
//               //      color32 = argb(255, 128, 128, 128);
//
//               //      return true;
//
//
//               //   }
//               //   else if (ecolor == ::user::color_button_background_hover)
//               //   {
//
//               //      if (m_estyle == StyleDarkRed)
//               //      {
//               //         color32 = argb(255, 205, 72, 72);
//               //      }
//               //      else
//               //      {
//               //         color32 = argb(255, 0x55, 0x99, 0xC2);
//
//               //      }
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_button_background)
//               //   {
//
//               //      if (m_estyle == StyleDarkRed)
//               //      {
//               //         color32 = argb(255, 165, 32, 32);
//               //      }
//               //      else
//               //      {
//               //         color32 = argb(255, 0x30, 0x75, 0xA0);
//               //      }
//
//
//               //      return true;
//               //   }
//               //   else if (ecolor == ::user::color_button_background_press)
//               //   {
//
//               //      color32 = argb(255, 0x07, 0x6D, 0x91);
//
//               //      return true;
//               //   }
//               //   else if (ecolor == ::user::color_button_text_disabled)
//               //   {
//
//               //      color32 = argb(255, 0xD0, 0xD0, 0xD0);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_button_text_hover)
//               //   {
//
//               //      color32 = argb(255, 255, 255, 255);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_button_text)
//               //   {
//
//               //      color32 = argb(255, 255, 255, 255);
//
//               //      return true;
//
//               //   }
//               //   else if (ecolor == ::user::color_button_text_press)
//               //   {
//
//               //      color32 = argb(255, 255, 255, 255);
//
//               //      return true;
//
//               //   }
//
//               //}
//
//               return frame::get_color(color32, ecolor, pcontext);
//
//            }


} // namespace experience_anthill



