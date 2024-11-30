#include "framework.h"
#include "frame_005.h"
#include "apex/platform/savings.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "base/user/experience/frame_window.h"
#include "base/user/experience/size_manager.h"
#include "base/user/experience/dock_manager.h"
#include "base/user/experience/move_manager.h"
#include "base/platform/session.h"
#include "base/platform/system.h"


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


   frame_005::frame_005()
   {

      //set_style(StyleLightGreen);

      //      SetStyle(StyleLightBlue);

   }

   frame_005::~frame_005()
   {

   }


   string frame_005::get_default_user_style() const
   {

      return "LightGreen";

   }


   void frame_005::on_initialize_experience_frame()
   {


      __øconstruct(m_pbrushGrip);
      __øconstruct(m_pbrushTextCaption);


      frame::on_initialize_experience_frame();

      m_pbrushGrip->create_solid(argb(0xff, 0x60, 0x65, 0x55));

      //

      auto pframewindow = m_pframewindow;

      auto psystem = system();

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(m_pframewindow);

      auto pstyle = pframewindow->get_style(pgraphics);

      auto colorCaptionText = pframewindow->get_color(pstyle, ::e_element_window_title);

      m_pbrushTextCaption->create_solid(colorCaptionText);
}


//    ::experience::enum_frame frame_005::experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder)
//   {
//       ::experience::enum_frame etest =  ::experience::e_frame_client;
//      {
//         //      m_pframewindow->GetEventWindow()->screen_to_client()(point);
//         ::int_rectangle rectangleEvent;
//         m_pframewindow->window_rectangle(rectangleEvent);
//         ::int_rectangle rectangle;
//         ::int_point pointCenter = rectangleEvent.center();
//         enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();
//
//         ::int_point pointHitTest = point;
//
//         if(rectangleEvent.left() < 0)
//            pointHitTest.x() -= rectangleEvent.left();
//         if(rectangleEvent.top() < 0)
//            pointHitTest.y() -= rectangleEvent.top();
//
//         if(egrip & e_grip_top_left)
//         {
//            rectangle = rectangleEvent;
//            rectangle.right() = rectangle.left() + 16;
//            rectangle.bottom() = rectangle.top() + 5;
//            if(rectangle.contains(pointHitTest))
//            {
//               etest =  ::experience::e_frame_sizing_top_left;
//               goto SizingSuccess;
//            }
//            rectangle = rectangleEvent;
//            rectangle.right() = rectangle.left() + 5;
//            rectangle.bottom() = rectangle.top() + 16;
//            if(rectangle.contains(pointHitTest))
//            {
//               etest =  ::experience::e_frame_sizing_top_left;
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
//               etest =  ::experience::e_frame_sizing_top_right;
//               goto SizingSuccess;
//            }
//            rectangle = rectangleEvent;
//            rectangle.left() = rectangle.right() - 5;
//            rectangle.bottom() = rectangle.top() + 16;
//            if(rectangle.contains(pointHitTest))
//            {
//               etest =  ::experience::e_frame_sizing_top_right;
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
//               etest =  ::experience::e_frame_sizing_bottom_right;
//               goto SizingSuccess;
//            }
//            rectangle = rectangleEvent;
//            rectangle.left() = rectangle.right() - 5;
//            rectangle.top() = rectangle.bottom() - 16;
//            if(rectangle.contains(pointHitTest))
//            {
//               etest =  ::experience::e_frame_sizing_bottom_right;
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
//               etest =  ::experience::e_frame_sizing_bottom_left;
//               goto SizingSuccess;
//            }
//            rectangle = rectangleEvent;
//            rectangle.right() = rectangle.left() + 5;
//            rectangle.top() = rectangle.bottom() - 16;
//            if(rectangle.contains(pointHitTest))
//            {
//               etest =  ::experience::e_frame_sizing_bottom_left;
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
//               etest =  ::experience::e_frame_sizing_top;
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
//               etest =  ::experience::e_frame_sizing_bottom;
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
//               etest =  ::experience::e_frame_sizing_left;
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
//               etest =  ::experience::e_frame_sizing_right;
//               goto SizingSuccess;
//            }
//         }
//         goto SizingNone;
//SizingSuccess:
//         return etest;
//SizingNone:;
//      }
//      return  ::experience::e_frame_client;
//   }
//



   void frame_005::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX,

         enum_border eside)
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

      if(estyle == ::user::StyleTranslucidWarmGray
            || estyle == ::user::StyleTranslucidLightBlue
            || estyle == ::user::StyleTranslucidLightGreen)
      {

         ::int_rectangle rectangle;

         GetBorderRectangle(rectangleX, &rectangle, eside);

         ColorGlass(pgraphics, rectangle, crMoveableBorder, 127);

      }
      else if(estyle == ::user::StyleLightBlue)
      {

         rectangleA.deflate(1, 1, 1, 1);
         Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorder, {});//m_colorMoveableBorderDkShadow);

         rectangleA.deflate(1, 1, 1, 1);
         Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorderHilight, crMoveableBorderShadow);

         rectangleA.deflate(1, 1, 1, 1);
         Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorder, crMoveableBorder);

         rectangleA.deflate(1, 1, 1, 1);
         Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorder, crMoveableBorder);

         ::int_rectangle rectangle;
         GetBorderRectangle(rectangleX, &rectangle, eside);

         //class imaging & imaging = psystem->imaging();
         //imaging.color_blend(
                     
            pgraphics->fill_rectangle(
                              rectangle,
                              crMoveableBorder &
                              127_opacity);
      }
      else
      {

         ::int_rectangle rectangle;
         GetBorderRectangle(rectangleX, &rectangle, eside);

         ColorGlass(pgraphics, rectangle, crMoveableBorder, 230);

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

   void frame_005::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
   {

      auto pframewindow = m_pframewindow;

      if(pframewindow == nullptr)
         return;

      if(!pframewindow->is_frame_experience_enabled())
         return;

      bool bZoomed = pframewindow->layout().is_zoomed();

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


      if(!pframewindow->layout().is_full_screen())
      {
         DrawBorder(pgraphics, rectangleNClient);
      }


      ///////////////////////
      //
      // Routine:
      // draw resize grip set
      //
      ///////////////////////

      if(!bZoomed && !pframewindow->layout().is_full_screen())
      {
         DrawGripSet(pgraphics, rectangleNClient);
      }

      //          pgraphics->SetBkMode(iOriginalBkMode);
      //            pgraphics->set_text_color(crOriginalTextColor);

   }


   void frame_005::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX)

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
         draw_border_side(pgraphics, rectangleX, e_border_top);

      }
      if(eborder & e_border_right)
      {
         draw_border_side(pgraphics, rectangleX, e_border_right);

      }
      if(eborder & e_border_bottom)
      {
         draw_border_side(pgraphics, rectangleX, e_border_bottom);

      }
      if(eborder & e_border_left)
      {
         draw_border_side(pgraphics, rectangleX, e_border_left);

      }

   }

   //void frame_005::GetBorderRectangle(
   //const ::int_rectangle & rectangleX,

   //::int_rectangle * prectangle,

   //enum_border eside)
   //{
   //   ::int_rectangle rectangleBig(rectangleX);

   //   ::int_rectangle rectangleSmall;
   //   rectangleSmall = client_rectangle2();
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


   void frame_005::Draw3dRectSide(::draw2d::graphics_pointer & pgraphics,const int_rectangle & rectangleParam,enum_border eborder,color32_t crTopLeft,color32_t crBottomRight)
   {

      



      ::int_rectangle rectangle(rectangleParam);
      int x = rectangle.left();
      int y = rectangle.top();
      int cx = rectangle.width();
      int cy = rectangle.height();

      ::int_rectangle rectangleDraw;

      if(eborder & e_border_top)
      {

         rectangleDraw = int_rectangle_dimension(x, y, cx, 1);

         if(session()->savings()->is_trying_to_save(::e_resource_processing))
         {

            pgraphics->fill_rectangle(rectangleDraw, crTopLeft);

         }
         else
         {
            ColorGlass(pgraphics, rectangleDraw, crTopLeft, 127);

         }

      }

      if(eborder & e_border_left)
      {

         rectangleDraw = int_rectangle_dimension(x, y + 1, 1, cy - 2);

         if(session()->savings()->is_trying_to_save(::e_resource_processing))
         {

            pgraphics->fill_rectangle(rectangleDraw, crTopLeft);

         }
         else
         {

            ColorGlass(pgraphics, rectangleDraw, crTopLeft, 127);

         }

      }

      if(eborder & e_border_right)
      {

         rectangleDraw = int_rectangle_dimension(x + cx - 1, y + 1, 1, cy - 2);

         if(session()->savings()->is_trying_to_save(e_resource_processing))
         {

            pgraphics->fill_rectangle(rectangleDraw, crBottomRight);

         }
         else
         {

            ColorGlass(pgraphics, rectangleDraw, crBottomRight, 127);

         }

      }

      if(eborder & e_border_bottom)
      {

         rectangleDraw = int_rectangle_dimension(x, y + cy - 1, cx, 1);

         if(session()->savings()->is_trying_to_save(e_resource_processing))
         {

            pgraphics->fill_rectangle(rectangleDraw, crBottomRight);

         }
         else
         {

            ColorGlass(pgraphics, rectangleDraw, crBottomRight, 127);

         }

      }

   }

   void frame_005::_on_style_change(::draw2d::graphics_pointer & pgraphics)
   {

      on_style_change_001_and_002(pgraphics);


   }

#define BEVEL_SMALL 2
#define BEVEL_LARGE 5
#define GRIP_SMALL 8
#define GRIP_LARGE 30

   void frame_005::DrawGrip(
   ::draw2d::graphics_pointer & pgraphics,
   const ::int_rectangle & rectangleXParam,

   enum_grip egrip)
   {

      const int size = 16;

      ::int_rectangle rectangleX(rectangleXParam);

      //            ::int_rectangle rectangleXB(rectangleX);
      ::int_rectangle rectangleA;
      ::int_point pointA;
      ::int_point pointB;
      ::int_point pointC;
      //            ::int_rectangle rectangle(rectangleX);
      switch(egrip)
      {
      case e_grip_top_left:
      {

         rectangleA = rectangleX;

         rectangleA.right() = 4;
         rectangleA.bottom() = size;

         pgraphics->fill_rectangle(rectangleA, m_pbrushGrip);

         rectangleA.right() = size;
         rectangleA.bottom() = 4;

         pgraphics->fill_rectangle(rectangleA, m_pbrushGrip);

      }
      break;
      case e_grip_top_right:
      {
         rectangleA = rectangleX;

         rectangleA.left() = rectangleA.right() - 4;
         rectangleA.bottom() = size;

         pgraphics->fill_rectangle(rectangleA, m_pbrushGrip);

         rectangleA.left() = rectangleA.right() - size;
         rectangleA.bottom() = 4;

         pgraphics->fill_rectangle(rectangleA, m_pbrushGrip);
      }
      break;
      case e_grip_bottom_left:
      {
         rectangleA = rectangleX;

         rectangleA.right() = 4;
         rectangleA.top() = rectangleA.bottom() - size;

         pgraphics->fill_rectangle(rectangleA, m_pbrushGrip);

         rectangleA.right() = size;
         rectangleA.top() = rectangleA.bottom() - 4;

         pgraphics->fill_rectangle(rectangleA, m_pbrushGrip);
      }
      break;
      case e_grip_bottom_right:
      {
         rectangleA = rectangleX;

         rectangleA.left() = rectangleA.right() - 4;
         rectangleA.top() = rectangleA.bottom() - size;

         pgraphics->fill_rectangle(rectangleA, m_pbrushGrip);

         rectangleA.left() = rectangleA.right() - size;
         rectangleA.top() = rectangleA.bottom() - 4;

         pgraphics->fill_rectangle(rectangleA, m_pbrushGrip);
      }
      break;
      case e_grip_top:
      {
         rectangleA = rectangleX;

         rectangleA.left() = rectangleA.left() + rectangleA.width() / 2 - size / 2;
         rectangleA.right() = rectangleA.left() + size;
         rectangleA.bottom() = 4;

         pgraphics->fill_rectangle(rectangleA, m_pbrushGrip);

      }
      break;
      case e_grip_bottom:
      {
         rectangleA = rectangleX;

         rectangleA.left() = rectangleA.left() + rectangleA.width() / 2 - size / 2;
         rectangleA.right() = rectangleA.left() + size;
         rectangleA.top() = rectangleA.bottom() - 4;

         pgraphics->fill_rectangle(rectangleA, m_pbrushGrip);
      }
      break;
      case e_grip_left:
      {

         rectangleA = rectangleX;

         rectangleA.right() = 4;
         rectangleA.top() = rectangleA.top() + rectangleA.height() / 2 - size / 2;
         rectangleA.bottom() = rectangleA.top() + size;

         pgraphics->fill_rectangle(rectangleA, m_pbrushGrip);

      }
      break;
      case e_grip_right:
      {

         rectangleA = rectangleX;

         rectangleA.left() = rectangleA.right() - 4;
         rectangleA.top() = rectangleA.top() + rectangleA.height() / 2 - size / 2;
         rectangleA.bottom() = rectangleA.top() + size;

         pgraphics->fill_rectangle(rectangleA, m_pbrushGrip);

      }
      break;
      default:
         break;
      }


   }


   void frame_005::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const int_rectangle & rectangleParam)
   {

      ///

      auto pframewindow = m_pframewindow;

      auto pstyle = pframewindow->get_style(pgraphics);

      auto crButtonHilite = pframewindow->get_color(pstyle, ::e_element_button_hilite);

      auto crButtonDarkShadow = pframewindow->get_color(pstyle, ::e_element_button_dark_shadow);

      auto crButtonFace = pframewindow->get_color(pstyle, ::e_element_button_background);

      auto crButtonShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

      ::int_rectangle rectangle(rectangleParam);

      pgraphics->draw_inset_3d_rectangle(rectangle, crButtonFace, crButtonDarkShadow, 1.0);

      rectangle.top()++;
      rectangle.bottom()--;
      rectangle.left()++;
      rectangle.right()--;

      pgraphics->draw_inset_3d_rectangle(rectangle, crButtonHilite, crButtonShadow, 1.0);

      rectangle.top()++;
      rectangle.bottom()--;
      rectangle.left()++;
      rectangle.right()--;

      pgraphics->fill_rectangle(rectangle, crButtonFace);

   }


   void frame_005::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX)
   {

      ::experience::size_manager * psizemanager = m_pframewindow->size_manager();

      if (psizemanager == nullptr)
      {

         return;

      }

      enum_grip egrip = psizemanager->GetGripMask();

      if(egrip & e_grip_top)
      {
         DrawGrip(pgraphics, rectangleX, e_grip_top);

      }
      if(egrip & e_grip_top_right)
      {
         DrawGrip(pgraphics, rectangleX, e_grip_top_right);

      }
      if(egrip & e_grip_right)
      {
         DrawGrip(pgraphics, rectangleX, e_grip_right);

      }
      if(egrip & e_grip_bottom_right)
      {
         DrawGrip(pgraphics, rectangleX, e_grip_bottom_right);

      }
      if(egrip & e_grip_bottom)
      {
         DrawGrip(pgraphics, rectangleX, e_grip_bottom);

      }
      if(egrip & e_grip_bottom_left)
      {
         DrawGrip(pgraphics, rectangleX, e_grip_bottom_left);

      }
      if(egrip & e_grip_left)
      {
         DrawGrip(pgraphics, rectangleX, e_grip_left);

      }
      if(egrip & e_grip_top_left)
      {
         DrawGrip(pgraphics, rectangleX, e_grip_top_left);

      }

   }


} // namespace experience_tranquillum



