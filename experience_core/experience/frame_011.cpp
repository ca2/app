#include "framework.h"
#include "aura/graphics/draw2d/graphics.h"
#include "frame_011.h"
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


namespace experience_core
{


   frame_011::frame_011()
   {

   }


   frame_011::~frame_011()
   {

   }


   string frame_011::get_default_user_style() const
   {

      return "TranslucidWarmLiteGray";

   }


//   ::experience::enum_frame frame_011::experience_frame_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
//   {
//         
//      ::experience::enum_frame etest = ::experience::e_frame_client;
//         
//      {
//         //      m_pframewindow->screen_to_client()(point);
//         ::rectangle_i32 rectangleEvent;
//         m_pframewindow->window_rectangle(rectangleEvent);
//         ::rectangle_i32 rectangle;
//         ::point_i32 pointCenter = rectangleEvent.center();
//         enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();
//
//         ::point_i32 pointHitTest = point;
//
////                  if(rectangleEvent.left() < 0)
////                     pointHitTest.x() -= rectangleEvent.left();
////                  if(rectangleEvent.top() < 0)
////                     pointHitTest.y() -= rectangleEvent.top();
//
//         if(egrip & e_grip_top_left)
//         {
//            rectangle = rectangleEvent;
//            rectangle.right() = rectangle.left() + 16;
//            rectangle.bottom() = rectangle.top() + 5;
//            if(rectangle.contains(pointHitTest))
//            {
//               etest = ::experience::e_frame_sizing_top_left;
//               goto SizingSuccess;
//            }
//            rectangle = rectangleEvent;
//            rectangle.right() = rectangle.left() + 5;
//            rectangle.bottom() = rectangle.top() + 16;
//            if(rectangle.contains(pointHitTest))
//            {
//               etest = ::experience::e_frame_sizing_top_left;
//               goto SizingSuccess;
//            }
//         }
//         if(egrip & e_grip_top_right)
//         {
//            rectangle = rectangleEvent;
//            rectangle.left() = rectangle.right() - 16;
//            rectangle.bottom() = rectangle.top() + 5;
//            if(rectangle.contains(pointHitTest))
//            {
//               etest = ::experience::e_frame_sizing_top_right;
//               goto SizingSuccess;
//            }
//            rectangle = rectangleEvent;
//            rectangle.left() = rectangle.right() - 5;
//            rectangle.bottom() = rectangle.top() + 16;
//            if(rectangle.contains(pointHitTest))
//            {
//               etest = ::experience::e_frame_sizing_top_right;
//               goto SizingSuccess;
//            }
//         }
//         if(egrip & e_grip_bottom_right)
//         {
//            rectangle = rectangleEvent;
//            rectangle.left() = rectangle.right() - 16;
//            rectangle.top() = rectangle.bottom() - 5;
//            if(rectangle.contains(pointHitTest))
//            {
//               etest = ::experience::e_frame_sizing_bottom_right;
//               goto SizingSuccess;
//            }
//            rectangle = rectangleEvent;
//            rectangle.left() = rectangle.right() - 5;
//            rectangle.top() = rectangle.bottom() - 16;
//            if(rectangle.contains(pointHitTest))
//            {
//               etest = ::experience::e_frame_sizing_bottom_right;
//               goto SizingSuccess;
//            }
//         }
//         if(egrip & e_grip_bottom_left)
//         {
//            rectangle = rectangleEvent;
//            rectangle.right() = rectangle.left() + 16;
//            rectangle.top() = rectangle.bottom() - 5;
//            if(rectangle.contains(pointHitTest))
//            {
//               etest = ::experience::e_frame_sizing_bottom_left;
//               goto SizingSuccess;
//            }
//            rectangle = rectangleEvent;
//            rectangle.right() = rectangle.left() + 5;
//            rectangle.top() = rectangle.bottom() - 16;
//            if(rectangle.contains(pointHitTest))
//            {
//               etest = ::experience::e_frame_sizing_bottom_left;
//               goto SizingSuccess;
//            }
//         }
//         if(egrip & e_grip_top)
//         {
//            rectangle.top() = rectangleEvent.top();
//            rectangle.left() = pointCenter.x() - 8;
//            rectangle.right() = pointCenter.x() + 8;
//            rectangle.bottom() = rectangleEvent.top() + 5;
//            if(rectangle.contains(pointHitTest))
//            {
//               etest = ::experience::e_frame_sizing_top;
//               goto SizingSuccess;
//            }
//         }
//         if(egrip & e_grip_bottom)
//         {
//            rectangle.top() = rectangleEvent.bottom() - 5;
//            rectangle.left() = pointCenter.x() - 8;
//            rectangle.right() = pointCenter.x() + 8;
//            rectangle.bottom() = rectangleEvent.bottom();
//            if(rectangle.contains(pointHitTest))
//            {
//               etest = ::experience::e_frame_sizing_bottom;
//               goto SizingSuccess;
//            }
//         }
//         if(egrip & e_grip_left)
//         {
//            rectangle.top() = pointCenter.y() - 8;
//            rectangle.left() = rectangleEvent.left();
//            rectangle.right() = rectangleEvent.left() + 5;
//            rectangle.bottom() = pointCenter.y() + 8;
//            if(rectangle.contains(pointHitTest))
//            {
//               etest = ::experience::e_frame_sizing_left;
//               goto SizingSuccess;
//            }
//         }
//         if(egrip & e_grip_right)
//         {
//            rectangle.top() = pointCenter.y() - 8;
//            rectangle.left() = rectangleEvent.right() - 5;
//            rectangle.right() = rectangleEvent.right();
//            rectangle.bottom() = pointCenter.y() + 8;
//            if(rectangle.contains(pointHitTest))
//            {
//               etest = ::experience::e_frame_sizing_right;
//               goto SizingSuccess;
//            }
//         }
//         goto SizingNone;
//SizingSuccess:
//         return etest;
//SizingNone:;
//      }
//      return ::experience::e_frame_client;
//   }






   void frame_011::draw_border_side(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectangleX,enum_border eside)
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

         auto pstyle = pframewindow->get_style(pgraphics);

         crMoveableBorder = pframewindow->get_color(pstyle, ::e_element_button_background);

         crMoveableBorderHilight = pframewindow->get_color(pstyle, ::e_element_button_hilite);

         crMoveableBorderShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

      }

      enum_dock edock = m_pframewindow->dock_manager()->get_dock_mask();

      ::rectangle_i32 rectangleA(rectangleX);

      if(m_pframewindow->m_estyle == ::user::StyleTranslucidWarmGray
            || m_pframewindow->m_estyle == ::user::StyleTranslucidLightBlue
            || m_pframewindow->m_estyle == ::user::StyleTranslucidLightGreen)
      {

         ::rectangle_i32 rectangle;

         GetBorderRectangle(rectangleX,&rectangle,eside);

         pgraphics->fill_rectangle(rectangle, crMoveableBorder & ::opacity(127));
            
      }
      else if(m_pframewindow->m_estyle == ::user::StyleLightBlue)
      {
         rectangleA.deflate(1,1,1,1);
         //Draw3dRectSide(pgraphics,rectangleA,eside,crMoveableBorder,0);//m_colorMoveableBorderDkShadow);

         rectangleA.deflate(1,1,1,1);
         //Draw3dRectSide(pgraphics,rectangleA,eside,crMoveableBorderHilight,crMoveableBorderShadow);

         rectangleA.deflate(1,1,1,1);
         //Draw3dRectSide(pgraphics,rectangleA,eside,crMoveableBorder,crMoveableBorder);

         rectangleA.deflate(1,1,1,1);
         Draw3dRectSide(pgraphics,rectangleA,eside,crMoveableBorder,crMoveableBorder);

         //::rectangle_i32 rectangle;
         //GetBorderRectangle(rectangleX, &rectangle, eside);
         //class imaging & imaging = psystem->imaging();
         //imaging.color_blend(pgraphics,
         //   rectangle,
         //   crMoveableBorder,
         //   127);
      }
      else
      {
            
         ::rectangle_i32 rectangle;
            
         GetBorderRectangle(rectangleX,&rectangle,eside);

         pgraphics->fill_rectangle(rectangle, crMoveableBorder & ::opacity(127));

         ::rectangle_i32 rectangleXB = rectangleA;

         rectangleXB.bottom()--;
         rectangleXB.right()--;

         rectangleA.top()++;
         rectangleA.bottom()--;
         rectangleA.left()++;
         rectangleA.right()--;
            
         if(edock == e_dock_none)
         {
               
            Draw3dRectSide(pgraphics,rectangleA,eside,m_colorDkShadow,m_colorDkShadow);
               
         }

         rectangleA.top()++;
         rectangleA.bottom()--;
         rectangleA.left()++;
         rectangleA.right()--;
         Draw3dRectSide(pgraphics,rectangleA,eside,m_colorDkShadow,m_colorDkShadow);

         rectangleA.top()++;
         rectangleA.bottom()--;
         rectangleA.left()++;
         rectangleA.right()--;
         if(edock == e_dock_none)
         {
            Draw3dRectSide(pgraphics,rectangleA,eside,m_colorDkShadow,m_colorDkShadow);
         }
      }

   }

   
   void frame_011::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
   {

      auto pframewindow = m_pframewindow;

      if(pframewindow == nullptr)
         return;

      if(!pframewindow->is_frame_experience_enabled())
         return;

      bool bZoomed = pframewindow->layout().is_zoomed() != 0;

      //    CVMSApp * pApp = (CVMSApp *) System;
      //::aura::savings & savings = session()->savings();

      //auto rectangleX = pframewindow->rectangle();

      string str;

      ::rectangle_i32 rectangleNClient;

      pframewindow->window_rectangle(rectangleNClient);

      rectangleNClient -= rectangleNClient.top_left();

      ////////////////////
      //
      // Routine:
      // draw frame border
      //
      ////////////////////


      if(!pframewindow->layout().is_full_screen())
      {
            
         DrawBorder(pgraphics,rectangleNClient);
            
      }


      ///////////////////////
      //
      // Routine:
      // draw resize grip set
      //
      ///////////////////////

      if(!bZoomed && !pframewindow->layout().is_full_screen())
      {
         DrawGripSet(pgraphics,rectangleNClient);
      }

      //            pgraphics->SetBkMode(iOriginalBkMode);
      //          pgraphics->set_text_color(crOriginalTextColor);

   }


   void frame_011::DrawBorder(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectangleX)
   {

      auto pmovemanager = m_pframewindow->move_manager();

      enum_border eborder = pmovemanager->GetBorderMask();

      if(m_pframewindow->layout().is_zoomed())
      {
         eborder = (enum_border)
                     (eborder &
                     ~(e_border_right
                        | e_border_bottom
                        | e_border_left));
      }

      if(eborder & e_border_top)
      {
         draw_border_side(pgraphics,rectangleX,e_border_top);
      }
      if(eborder & e_border_right)
      {
         draw_border_side(pgraphics,rectangleX,e_border_right);
      }
      if(eborder & e_border_bottom)
      {
         draw_border_side(pgraphics,rectangleX,e_border_bottom);
      }
      if(eborder & e_border_left)
      {
         draw_border_side(pgraphics,rectangleX,e_border_left);
      }

   }

   //void frame_011::GetBorderRectangle(
   //const ::rectangle_i32 & rectangleX,
   //::rectangle_i32 * lprect,
   //enum_border eside)
   //{
   //   ::rectangle_i32 rectangleBig(rectangleX);
   //   ::rectangle_i32 rectangleSmall;
   //   rectangleSmall = m_pframewindow->client_rectangle2();
   //   ::rectangle_i32 rectangle;
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
   //   *lprect = rectangle;
   //}


   void frame_011::_on_style_change(::draw2d::graphics_pointer & pgraphics)
   {

      on_style_change_001_and_002(pgraphics);

   }


#define BEVEL_SMALL 2
#define BEVEL_LARGE 5
#define GRIP_SMALL 8
#define GRIP_LARGE 30

   void frame_011::DrawGrip(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectangleXParam,enum_grip egrip)
   {



      const i32 size = 16;

      ::rectangle_i32 rectangleX(rectangleXParam);
      //            ::rectangle_i32 rectangleXB(rectangleX);
      ::rectangle_i32 rectangleA;
      ::point_i32 pointA;
      ::point_i32 pointB;
      ::point_i32 pointC;
      //            ::rectangle_i32 rectangle(rectangleX);
      switch(egrip)
      {
      case e_grip_top_left:
      {

         rectangleA = rectangleX;

         rectangleA.right() = 4;
         rectangleA.bottom() = size;

         pgraphics->fill_rectangle(rectangleA,rgb(0x60,0x65,0x55));

         rectangleA.right() = size;
         rectangleA.bottom() = 4;

         pgraphics->fill_rectangle(rectangleA,rgb(0x60,0x65,0x55));

      }
      break;
      case e_grip_top_right:
      {
         rectangleA = rectangleX;

         rectangleA.left() = rectangleA.right() - 4;
         rectangleA.bottom() = size;

         pgraphics->fill_rectangle(rectangleA,rgb(0x60,0x65,0x55));

         rectangleA.left() = rectangleA.right() - size;
         rectangleA.bottom() = 4;

         pgraphics->fill_rectangle(rectangleA,rgb(0x60,0x65,0x55));
      }
      break;
      case e_grip_bottom_left:
      {
         rectangleA = rectangleX;

         rectangleA.right() = 4;
         rectangleA.top() = rectangleA.bottom() - size;

         pgraphics->fill_rectangle(rectangleA,rgb(0x60,0x65,0x55));

         rectangleA.right() = size;
         rectangleA.top() = rectangleA.bottom() - 4;

         pgraphics->fill_rectangle(rectangleA,rgb(0x60,0x65,0x55));
      }
      break;
      case e_grip_bottom_right:
      {
         rectangleA = rectangleX;

         rectangleA.left() = rectangleA.right() - 4;
         rectangleA.top() = rectangleA.bottom() - size;

         pgraphics->fill_rectangle(rectangleA,rgb(0x60,0x65,0x55));

         rectangleA.left() = rectangleA.right() - size;
         rectangleA.top() = rectangleA.bottom() - 4;

         pgraphics->fill_rectangle(rectangleA,rgb(0x60,0x65,0x55));
      }
      break;
      case e_grip_top:
      {
         rectangleA = rectangleX;

         rectangleA.left() = rectangleA.left() + rectangleA.width() / 2 - size / 2;
         rectangleA.right() = rectangleA.left() + size;
         rectangleA.bottom() = 4;

         pgraphics->fill_rectangle(rectangleA,rgb(0x60,0x65,0x55));

      }
      break;
      case e_grip_bottom:
      {
         rectangleA = rectangleX;

         rectangleA.left() = rectangleA.left() + rectangleA.width() / 2 - size / 2;
         rectangleA.right() = rectangleA.left() + size;
         rectangleA.top() = rectangleA.bottom() - 4;

         pgraphics->fill_rectangle(rectangleA,rgb(0x60,0x65,0x55));
      }
      break;
      case e_grip_left:
      {
         rectangleA = rectangleX;

         rectangleA.right() = 4;
         rectangleA.top() = rectangleA.top() + rectangleA.height() / 2 - size / 2;
         rectangleA.bottom() = rectangleA.top() + size;

         pgraphics->fill_rectangle(rectangleA,rgb(0x60,0x65,0x55));
      }
      break;
      case e_grip_right:
      {
         rectangleA = rectangleX;

         rectangleA.left() = rectangleA.right() - 4;
         rectangleA.top() = rectangleA.top() + rectangleA.height() / 2 - size / 2;
         rectangleA.bottom() = rectangleA.top() + size;

         pgraphics->fill_rectangle(rectangleA,rgb(0x60,0x65,0x55));
      }
      break;
      default:
         break;
      }


   }

   void frame_011::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectangleParam)
   {

      //

      ::rectangle_i32 rectangle(rectangleParam);

      auto pframewindow = m_pframewindow;

      auto pstyle = pframewindow->get_style(pgraphics);

      auto crButtonHilite = pframewindow->get_color(pstyle, ::e_element_button_hilite);

      auto crButtonDarkShadow = pframewindow->get_color(pstyle, ::e_element_button_dark_shadow);

      auto crButtonFace = pframewindow->get_color(pstyle, ::e_element_button_background);

      auto crButtonShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

      pgraphics->draw_inset_3d_rectangle(rectangle,crButtonFace,crButtonDarkShadow, 1.0);

      rectangle.top()++;
      rectangle.bottom()--;
      rectangle.left()++;
      rectangle.right()--;

      pgraphics->draw_inset_3d_rectangle(rectangle,crButtonHilite,crButtonShadow, 1.0);

      rectangle.top()++;
      rectangle.bottom()--;
      rectangle.left()++;
      rectangle.right()--;

      pgraphics->fill_rectangle(rectangle,crButtonFace);

   }


   void frame_011::DrawGripSet(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectangleX)
   {

      auto psizenager = m_pframewindow->size_manager();

      enum_grip egrip = psizenager->GetGripMask();

      if(egrip & e_grip_top)
      {
         DrawGrip(pgraphics,rectangleX,e_grip_top);
      }
      if(egrip & e_grip_top_right)
      {
         DrawGrip(pgraphics,rectangleX,e_grip_top_right);
      }
      if(egrip & e_grip_right)
      {
         DrawGrip(pgraphics,rectangleX,e_grip_right);
      }
      if(egrip & e_grip_bottom_right)
      {
         DrawGrip(pgraphics,rectangleX,e_grip_bottom_right);
      }
      if(egrip & e_grip_bottom)
      {
         DrawGrip(pgraphics,rectangleX,e_grip_bottom);
      }
      if(egrip & e_grip_bottom_left)
      {
         DrawGrip(pgraphics,rectangleX,e_grip_bottom_left);
      }
      if(egrip & e_grip_left)
      {
         DrawGrip(pgraphics,rectangleX,e_grip_left);
      }
      if(egrip & e_grip_top_left)
      {
         DrawGrip(pgraphics,rectangleX,e_grip_top_left);
      }

   }


} // namespace experience



