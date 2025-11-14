#include "framework.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/pen.h"
#include "frame_008.h"
#include "aura/user/user/style.h"
#include "berg/user/experience/control_box.h"
#include "berg/user/experience/frame_window.h"
#include "berg/user/experience/size_manager.h"
#include "berg/user/experience/dock_manager.h"
#include "berg/user/experience/move_manager.h"


#define GRIP_CORNER_LARGE_CX 16
#define GRIP_CORNER_SMALL_CX 5
#define GRIP_CORNER_LARGE_CY 16
#define GRIP_CORNER_SMALL_CY 5


#define GRIP_CENTER_LARGE_CX 36
#define GRIP_CENTER_SMALL_CX 7
#define GRIP_CENTER_LARGE_CY 36
#define GRIP_CENTER_SMALL_CY 7


namespace experience_tranquillum
{


         frame_008::frame_008()
         {

            m_bHollow = false;


         }


         frame_008::~frame_008()
         {

         }


         string frame_008::get_default_user_style() const
         {

            return "TranslucidWarmLiteGray";

         }


//          ::experience::enum_frame frame_008::experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder)
//         {
//             ::experience::enum_frame etest =  ::experience::e_frame_client;
//            {
//               //      m_pframewindow->GetEventWindow()->screen_to_client()(point);
//               ::int_rectangle rectangleEvent;
//               m_pframewindow->window_rectangle(rectangleEvent);
//               ::int_rectangle rectangle;
//               //::int_point pointCenter = rectangleEvent.center();
//               enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();
//
//               
//               ::int_rectangle rectangleOuter(rectangleEvent);
//               
//               ::int_rectangle rectangleInner(rectangleEvent);
//               
//               rectangleInner.deflate(8);
//               
//               ::int_point pointHitTest = point;
//
////               if(rectangleEvent.left() < 0)
////                  pointHitTest.x -= rectangleEvent.left();
////               if(rectangleEvent.top() < 0)
////                  pointHitTest.y -= rectangleEvent.top();
//
//               if(egrip & e_grip_top_left)
//               {
//                  rectangle.top_left() = rectangleOuter.top_left();
//                  rectangle.bottom_right() = rectangleInner.top_left();
//                  if(rectangle.contains(pointHitTest))
//                  {
//                     etest =  ::experience::e_frame_sizing_top_left;
//                     goto SizingSuccess;
//                  }
//               }
//               if(egrip & e_grip_top_right)
//               {
//                  rectangle.top() = rectangleOuter.top();
//                  rectangle.left() = rectangleInner.right();
//                  rectangle.bottom() = rectangleInner.top();
//                  rectangle.right() = rectangleOuter.right();
//                  if(rectangle.contains(pointHitTest))
//                  {
//                     etest =  ::experience::e_frame_sizing_top_right;
//                     goto SizingSuccess;
//                  }
//               }
//               if(egrip & e_grip_bottom_right)
//               {
//                  rectangle.top_left() = rectangleInner.bottom_right();
//                  rectangle.bottom_right() = rectangleOuter.bottom_right();
//                  if(rectangle.contains(pointHitTest))
//                  {
//                     etest =  ::experience::e_frame_sizing_bottom_right;
//                     goto SizingSuccess;
//                  }
//               }
//               if(egrip & e_grip_bottom_left)
//               {
//                  rectangle.top() = rectangleInner.bottom();
//                  rectangle.left() = rectangleOuter.left();
//                  rectangle.bottom() = rectangleOuter.bottom();
//                  rectangle.right() = rectangleInner.left();
//                  if(rectangle.contains(pointHitTest))
//                  {
//                     etest =  ::experience::e_frame_sizing_bottom_left;
//                     goto SizingSuccess;
//                  }
//               }
//               if(egrip & e_grip_top)
//               {
//                  rectangle.top() = rectangleOuter.top();
//                  rectangle.left() = rectangleInner.left();
//                  rectangle.right() = rectangleInner.right();
//                  rectangle.bottom() = rectangleInner.top();
//                  if(rectangle.contains(pointHitTest))
//                  {
//                     etest =  ::experience::e_frame_sizing_top;
//                     goto SizingSuccess;
//                  }
//               }
//               if(egrip & e_grip_bottom)
//               {
//                  rectangle.top() = rectangleInner.bottom();
//                  rectangle.left() = rectangleInner.left();
//                  rectangle.right() = rectangleInner.right();
//                  rectangle.bottom() = rectangleOuter.bottom();
//                  if(rectangle.contains(pointHitTest))
//                  {
//                     etest =  ::experience::e_frame_sizing_bottom;
//                     goto SizingSuccess;
//                  }
//               }
//               if(egrip & e_grip_left)
//               {
//                  rectangle.top() = rectangleInner.top();
//                  rectangle.left() = rectangleOuter.left();
//                  rectangle.right() = rectangleInner.left();
//                  rectangle.bottom() = rectangleInner.bottom();
//                  if(rectangle.contains(pointHitTest))
//                  {
//                     etest =  ::experience::e_frame_sizing_left;
//                     goto SizingSuccess;
//                  }
//               }
//               if(egrip & e_grip_right)
//               {
//                  rectangle.top() = rectangleInner.top();
//                  rectangle.left() = rectangleInner.right();
//                  rectangle.right() = rectangleOuter.right();
//                  rectangle.bottom() = rectangleInner.bottom();
//                  if(rectangle.contains(pointHitTest))
//                  {
//                     etest =  ::experience::e_frame_sizing_right;
//                     goto SizingSuccess;
//                  }
//               }
//               goto SizingNone;
//SizingSuccess:
//               return etest;
//SizingNone:
//               ;
//            }
//            return  ::experience::e_frame_client;
//         }






         void frame_008::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX, enum_border eside)

         {

            auto pframewindow = m_pframewindow;

            if (pframewindow == nullptr)
            {

               return;

            }

            //

            status < ::color::color > crMoveableBorder;
            status < ::color::color > crMoveableBorderHilight;
            status < ::color::color > crMoveableBorderShadow;

            if(pframewindow->is_active_window())
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

            enum_dock edock = m_pframewindow->dock_manager()->get_dock_mask();
            ::int_rectangle rectangleA(rectangleX);

            auto estyle = pframewindow->m_estyle;

            if(m_bHollow)
            {


            }
            else if(estyle == ::user::StyleLightBlue || estyle == ::user::StyleRedOrange)
            {

               Draw3dRectSide(pgraphics, rectangleA, eside, color::black, color::black);

            }
            else if(estyle == ::user::StyleTranslucidWarmGray
                     || estyle == ::user::StyleTranslucidLightBlue
                     || estyle == ::user::StyleTranslucidLightGreen)
            {
               ::int_rectangle rectangle;
               GetBorderRectangle(rectangleX, &rectangle, eside);

               //class imaging & imaging = psystem->imaging();
               //imaging.color_blend(
                  pgraphics->fill_rectangle(
                                    rectangle,
                                    crMoveableBorder & ::opacity(0.5));
            }
            else
            {
               ::int_rectangle rectangle;
               GetBorderRectangle(rectangleX, &rectangle, eside);

               //class imaging & imaging = psystem->imaging();
               //imaging.color_blend(pgraphics,

               pgraphics->fill_rectangle(
                                    rectangle,
                                    crMoveableBorder & ::opacity(127));

               ::int_rectangle rectangleXB = rectangleA;

               rectangleXB.bottom()--;
               rectangleXB.right()--;

               rectangleA.top()++;
               rectangleA.bottom()--;
               rectangleA.left()++;
               rectangleA.right()--;
               if(edock == e_dock_none)
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
               if(edock == e_dock_none)
               {
                  Draw3dRectSide(pgraphics, rectangleA, eside, m_colorDkShadow, m_colorDkShadow);
               }
            }

         }

         void frame_008::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
         {

            auto pframewindow = m_pframewindow;

            if(pframewindow == nullptr)
               return;

            if(!pframewindow->is_frame_experience_enabled())
               return;

            ::int_rectangle rectangleX;
            rectangleX = pframewindow->rectangle();

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

            //auto timeBorder = ::time::now();

            if(!pframewindow->layout().is_full_screen())
            {

               DrawBorder(pgraphics, rectangleNClient);

            }

            //printf("border draw frame_008 %dms", tickBorder.elapsed().m_i);

         }


         void frame_008::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX)
         {

            auto pmovemanager = m_pframewindow->move_manager();

            auto eborder = pmovemanager->GetBorderMask();

            ::int_rectangle rectangleA(rectangleX);

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

            pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

            auto pframewindow = m_pframewindow;

            auto pstyle = pframewindow->get_style(pgraphics);

            if (pstyle->is_dark_mode())
            {

               pgraphics->draw_inset_rectangle(rectangleA, argb(255, 60, 60, 60), 1.0, eborder);

            }
            else
            {

               pgraphics->draw_inset_rectangle(rectangleA, argb(255, 255, 255, 255), 1.0, eborder);

            }

         }


         //void frame_008::GetBorderRectangle(const ::int_rectangle & rectangleBigParam, ::int_rectangle * prectangle, enum_border eside)
         //{
         //   
         //   ::int_rectangle rectangleBig(rectangleBigParam);

         //   auto rectangleSmall = client_rectangle();

         //   ::int_rectangle rectangle;

         //   if(eside == e_border_top)
         //   {

         //      rectangle.left() = rectangleBig.left();
         //      rectangle.right() = rectangleBig.right();
         //      rectangle.top() = rectangleBig.top();
         //      rectangle.bottom() = rectangleSmall.top();

         //   }
         //   else if(eside == e_border_left)
         //   {

         //      rectangle.left() = rectangleBig.left();
         //      rectangle.right() = rectangleSmall.left();
         //      rectangle.top() = rectangleSmall.top();
         //      rectangle.bottom() = rectangleSmall.bottom();

         //   }
         //   else if(eside == e_border_right)
         //   {

         //      rectangle.left() = rectangleSmall.right();
         //      rectangle.right() = rectangleBig.right();
         //      rectangle.top() = rectangleSmall.top();
         //      rectangle.bottom() = rectangleSmall.bottom();

         //   }
         //   else if(eside == e_border_bottom)
         //   {

         //      rectangle.left() = rectangleBig.left();
         //      rectangle.right() = rectangleBig.right();
         //      rectangle.top() = rectangleSmall.bottom();
         //      rectangle.bottom() = rectangleBig.bottom();

         //   }

         //   *prectangle = rectangle;

         //}


         void frame_008::_on_style_change(::draw2d::graphics_pointer & pgraphics)
         {

            øconstruct(m_ppenHollow1);
            øconstruct(m_ppenHollow2);
            øconstruct(m_ppenHollow3);
            øconstruct(m_ppenHollow4);
            øconstruct(m_ppenHollow5);


            on_style_change_001_and_002(pgraphics);
               
            auto pframewindow = m_pframewindow;

            auto estyle = pframewindow->m_estyle;

            if (estyle == ::user::StyleDarkRed)
            {
               //m_ppenHollow1->create_solid(1.0, argb(20, 0, 0, 0));
               //m_ppenHollow2->create_solid(1.0, argb(60, 20, 20, 20));
               //m_ppenHollow3->create_solid(1.0, argb(100, 40, 40, 40));
               //m_ppenHollow4->create_solid(1.0, argb(140, 60, 60, 60));
               //m_ppenHollow5->create_solid(1.0, argb(255, 90, 220, 100));
               m_colorCaptionTextBk = argb(255, 200, 200, 200);
               m_colorActiveCaptionTextBk = argb(255, 165, 32, 32);
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

               m_pcontrolbox->m_pbrushButtonBackSel = m_pcontrolbox->m_pbrushButtonBack;
               m_pcontrolbox->m_ppenButtonBackSel = m_pcontrolbox->m_ppenButtonBack;
               m_pcontrolbox->m_colorButtonForeSel = m_pcontrolbox->m_colorButtonFore;

            }

         }


         //color32_t frame_008::get_border_main_body_color()
         //{

         //   if (m_estyle == StyleRedOrange)
         //   {

         //      return argb(255, 255, 170, 136);

         //   }
         //   else
         //   {

         //      return argb(255, 50, 100, 200);

         //   }

         //}


         //bool frame_008::get_color(color32_t & color32, ::user::e_color ecolor, ::user::style_context * pstyle)
         //{

         //   return frame::get_color(color32, ecolor, pstyle);

         //}


} // namespace experience



