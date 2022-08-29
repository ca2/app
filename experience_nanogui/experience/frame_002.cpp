#include "framework.h"
#include "aura/graphics/draw2d/_component.h"


#define GRIP_CORNER_LARGE_CX 16
#define GRIP_CORNER_SMALL_CX 5
#define GRIP_CORNER_LARGE_CY 16
#define GRIP_CORNER_SMALL_CY 5

#undef GRIP_CENTER_LARGE_CX
#undef GRIP_CENTER_SMALL_CX
#undef GRIP_CENTER_LARGE_CY
#undef GRIP_CENTER_SMALL_CY

#define GRIP_CENTER_LARGE_CX 36
#define GRIP_CENTER_SMALL_CX 7
#define GRIP_CENTER_LARGE_CY 36
#define GRIP_CENTER_SMALL_CY 7



namespace experience_nanogui
{


   frame_002::frame_002()
   {

      //m_strStyle = "LightGreen";

      //m_rectangleControlBoxMarginNormal.top = 0;


   }


   frame_002::~frame_002()
   {

   }


   string frame_002::get_default_user_style() const
   {

      return "LightGreen";

   }


   ::experience::enum_frame frame_002::experience_frame_hit_test(const ::point_i32 & pointCursor)
   {
      ::experience::enum_frame etest = ::experience::e_frame_client;
      {
         //      m_pframewindow->screen_to_client()(point);
         ::rectangle_i32 rectangleEvent;
         m_pframewindow->get_window_rect(rectangleEvent);
         ::rectangle_i32 rectangle;
         ::point_i32 pointCenter = rectangleEvent.center();
         enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();

         if(egrip & e_grip_top_left)
         {
            rectangle = rectangleEvent;
            rectangle.right = rectangle.left + 16;
            rectangle.bottom = rectangle.top + 5;
            if(rectangle.contains(pointCursor))
            {
               etest = ::experience::e_frame_sizing_top_left;
               goto SizingSuccess;
            }
            rectangle = rectangleEvent;
            rectangle.right = rectangle.left + 5;
            rectangle.bottom = rectangle.top + 16;
            if(rectangle.contains(pointCursor))
            {
               etest = ::experience::e_frame_sizing_top_left;
               goto SizingSuccess;
            }
         }
         if(egrip & e_grip_top_right)
         {
            rectangle = rectangleEvent;
            rectangle.left = rectangle.right - 16;
            rectangle.bottom = rectangle.top + 5;
            if(rectangle.contains(pointCursor))
            {
               etest = ::experience::e_frame_sizing_top_right;
               goto SizingSuccess;
            }
            rectangle = rectangleEvent;
            rectangle.left = rectangle.right - 5;
            rectangle.bottom = rectangle.top + 16;
            if(rectangle.contains(pointCursor))
            {
               etest = ::experience::e_frame_sizing_top_right;
               goto SizingSuccess;
            }
         }
         if(egrip & e_grip_bottom_right)
         {
            rectangle = rectangleEvent;
            rectangle.left = rectangle.right - 16;
            rectangle.top = rectangle.bottom - 5;
            if(rectangle.contains(pointCursor))
            {
               etest = ::experience::e_frame_sizing_bottom_right;
               goto SizingSuccess;
            }
            rectangle = rectangleEvent;
            rectangle.left = rectangle.right - 5;
            rectangle.top = rectangle.bottom - 16;
            if(rectangle.contains(pointCursor))
            {
               etest = ::experience::e_frame_sizing_bottom_right;
               goto SizingSuccess;
            }
         }
         if(egrip & e_grip_bottom_left)
         {
            rectangle = rectangleEvent;
            rectangle.right = rectangle.left + 16;
            rectangle.top = rectangle.bottom - 5;
            if(rectangle.contains(pointCursor))
            {
               etest = ::experience::e_frame_sizing_bottom_left;
               goto SizingSuccess;
            }
            rectangle = rectangleEvent;
            rectangle.right = rectangle.left + 5;
            rectangle.top = rectangle.bottom - 16;
            if(rectangle.contains(pointCursor))
            {
               etest = ::experience::e_frame_sizing_bottom_left;
               goto SizingSuccess;
            }
         }
         if(egrip & e_grip_top)
         {
            rectangle.top = rectangleEvent.top;
            rectangle.left = pointCenter.x - 8;
            rectangle.right = pointCenter.x + 8;
            rectangle.bottom = rectangleEvent.top + 5;
            if(rectangle.contains(pointCursor))
            {
               etest = ::experience::e_frame_sizing_top;
               goto SizingSuccess;
            }
         }
         if(egrip & e_grip_bottom)
         {
            rectangle.top = rectangleEvent.bottom - 5;
            rectangle.left = pointCenter.x - 8;
            rectangle.right = pointCenter.x + 8;
            rectangle.bottom = rectangleEvent.bottom;
            if(rectangle.contains(pointCursor))
            {
               etest = ::experience::e_frame_sizing_bottom;
               goto SizingSuccess;
            }
         }
         if(egrip & e_grip_left)
         {
            rectangle.top = pointCenter.y - 8;
            rectangle.left = rectangleEvent.left;
            rectangle.right = rectangleEvent.left + 5;
            rectangle.bottom = pointCenter.y + 8;
            if(rectangle.contains(pointCursor))
            {
               etest = ::experience::e_frame_sizing_left;
               goto SizingSuccess;
            }
         }
         if(egrip & e_grip_right)
         {
            rectangle.top = pointCenter.y - 8;
            rectangle.left = rectangleEvent.right - 5;
            rectangle.right = rectangleEvent.right;
            rectangle.bottom = pointCenter.y + 8;
            if(rectangle.contains(pointCursor))
            {
               etest = ::experience::e_frame_sizing_right;
               goto SizingSuccess;
            }
         }
         goto SizingNone;
SizingSuccess:
         return etest;
SizingNone:;
      }
      return ::experience::e_frame_client;
   }




   void frame_002::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClientParam, enum_border eside)
   {

      //auto psession = get_session();

      auto rectangleClient(rectangleClientParam);

      auto pframewindow = m_pframewindow;

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
      ::rectangle_i32 rectangleA(rectangleClient);

      if(m_pframewindow->m_estyle == ::user::StyleTranslucidWarmGray
            || m_pframewindow->m_estyle == ::user::StyleTranslucidLightBlue
            || m_pframewindow->m_estyle == ::user::StyleTranslucidLightGreen)
      {
            
         ::rectangle_i32 rectangle;
            
         GetBorderRect(rectangleClient, rectangle, eside);

         pgraphics->fill_rectangle(rectangle, ::color::color(crMoveableBorder, 127));

      }
      else if(m_pframewindow->m_estyle == ::user::StyleLightBlue)
      {
            
         rectangleA.deflate(1, 1, 1, 1);
            
         Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorder, 0);

         rectangleA.deflate(1, 1, 1, 1);
            
         Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorderHilight, crMoveableBorderShadow);

         rectangleA.deflate(1, 1, 1, 1);
            
         Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorder, crMoveableBorder);

         rectangleA.deflate(1, 1, 1, 1);
            
         Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorder, crMoveableBorder);

         ::rectangle_i32 rectangle;
            
         GetBorderRect(rectangleClient, rectangle, eside);

         pgraphics->fill_rectangle(rectangle, ::color::color(crMoveableBorder, 0.5));
            
      }
      else
      {

         ::rectangle_i32 rectangle;

         rectangleClient.deflate(1, 1);

         GetBorderRect(rectangleClient, rectangle, eside);

         pgraphics->fill_rectangle(rectangle,::color::color(crMoveableBorder, 200));

         GetBorderRect(rectangleClient, rectangle, eside);

         ::rectangle_i32 rectangleClientB = rectangleA;

         rectangleClientB.bottom--;
         rectangleClientB.right--;

         rectangleA.top++;
         rectangleA.bottom--;
         rectangleA.left++;
         rectangleA.right--;
         if(edock == e_dock_none)
         {
            Draw3dRectSide(pgraphics, rectangleA, eside, opaque(m_colorDkShadow), opaque(m_colorDkShadow));
         }

         rectangleA.top++;
         rectangleA.bottom--;
         rectangleA.left++;
         rectangleA.right--;
         Draw3dRectSide(pgraphics, rectangleA, eside, opaque(m_colorDkShadow), opaque(m_colorDkShadow));

         rectangleA.top++;
         rectangleA.bottom--;
         rectangleA.left++;
         rectangleA.right--;
         if(edock == e_dock_none)
         {
            Draw3dRectSide(pgraphics, rectangleA, eside, opaque(m_colorDkShadow), opaque(m_colorDkShadow));
         }

      }

   }
   

   void frame_002::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
   {

      auto pframewindow = m_pframewindow;

      if(pframewindow == nullptr)
         return;

      if(!pframewindow->is_frame_experience_enabled())
         return;

      bool bZoomed = pframewindow->layout().is_zoomed() != 0;

      //    CVMSApp * pApp = (CVMSApp *) System;
      //::aura::savings & savings = psession->m_paurasession->savings();

      //auto rectangleClient = pframewindow->get_client_rect();

      string str;

      ::rectangle_i32 rectangleNClient;

      pframewindow->get_window_rect(rectangleNClient);

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


   void frame_002::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient)
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
         draw_border_side(pgraphics, rectangleClient, e_border_top);
      }
      if(eborder & e_border_right)
      {
         draw_border_side(pgraphics, rectangleClient, e_border_right);
      }
      if(eborder & e_border_bottom)
      {
         draw_border_side(pgraphics, rectangleClient, e_border_bottom);
      }
      if(eborder & e_border_left)
      {
         draw_border_side(pgraphics, rectangleClient, e_border_left);
      }

   }
   

   void frame_002::GetBorderRect(
   const ::rectangle_i32 & rectangleClient,
   RECTANGLE_I32 * lprect,
   enum_border eside)
   {
      ::rectangle_i32 rectangleBig(rectangleClient);
      ::rectangle_i32 rectangleSmall;
      get_window_client_rect(rectangleSmall);
      ::rectangle_i32 rectangle;
      if(eside == e_border_top)
      {
         rectangle.left = rectangleBig.left;
         rectangle.right = rectangleBig.right;
         rectangle.top = rectangleBig.top;
         rectangle.bottom = rectangleSmall.top;
      }
      else if(eside == e_border_left)
      {
         rectangle.left = rectangleBig.left;
         rectangle.right = rectangleSmall.left;
         rectangle.top = rectangleSmall.top;
         rectangle.bottom = rectangleSmall.bottom;
      }
      else if(eside == e_border_right)
      {
         rectangle.left = rectangleSmall.right;
         rectangle.right = rectangleBig.right;
         rectangle.top = rectangleSmall.top;
         rectangle.bottom = rectangleSmall.bottom;
      }
      else if(eside == e_border_bottom)
      {
         rectangle.left = rectangleBig.left;
         rectangle.right = rectangleBig.right;
         rectangle.top = rectangleSmall.bottom;
         rectangle.bottom = rectangleBig.bottom;
      }
      *lprect = rectangle;
   }


   void frame_002::_on_style_change(::draw2d::graphics_pointer & pgraphics)
   {

      on_style_change_001_and_002(pgraphics);

   }


#define BEVEL_SMALL 2
#define BEVEL_LARGE 5
#define GRIP_SMALL 8
#define GRIP_LARGE 30

   void frame_002::DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClientParam, enum_grip egrip)
   {
      //            const i32 size1 = 14;
      //      const i32 size2 = 15;

      ::rectangle_i32 rectangleClient(rectangleClientParam);
      //            ::rectangle_i32 rectangleClientB(rectangleClient);
      ::rectangle_i32 rectangleA;
      ::point_i32 pointA;
      ::point_i32 pointB;
      ::point_i32 pointC;
      ::rectangle_i32 rectangle(rectangleClient);



      switch(egrip)
      {
      case e_grip_top_left:
      {

         rectangleClient.bottom--;
         rectangleClient.right--;

         rectangleA = rectangleClient;

         pgraphics->set(m_ppenHilight1);

         pointA = rectangleA.top_left();
         pointB = pointA;
         pointB.x += 16;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);


         pointA = rectangleA.top_left();
         pointB = pointA;
         pointB.y += 16;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pgraphics->set(m_ppenFace1);

         pointA = rectangleA.top_left();
         pointA.x++;
         pointA.y++;
         pointB = pointA;
         pointB.x += 15;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pointA = rectangleA.top_left();
         pointA.x += 2;
         pointA.y += 2;
         pointB = pointA;
         pointB.x += 14;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);


         pointA = rectangleA.top_left();
         pointA.x++;
         pointA.y++;
         pointB = pointA;
         pointB.y += 15;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pointA = rectangleA.top_left();
         pointA.x += 2;
         pointA.y += 2;
         pointB = pointA;
         pointB.y += 14;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pgraphics->set(m_ppenShadow1);

         pointA = rectangleA.top_left();
         pointA.x += 3;
         pointA.y += 3;
         pointB = pointA;
         pointB.x += 13;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);


         pointA = rectangleA.top_left();
         pointA.x += 3;
         pointA.y += 3;
         pointB = pointA;
         pointB.y += 13;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pgraphics->set(m_ppenDkShadow1);

         pointA = rectangleA.top_left();
         pointA.x += 4;
         pointA.y += 4;
         pointB = pointA;
         pointB.y += 12;
         pointC = pointB;
         pointC.x -= 3;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);
         pgraphics->line_to(pointC);

         pointA = rectangleA.top_left();
         pointA.x += 4;
         pointA.y += 4;
         pointB = pointA;
         pointB.x += 12;
         pointC = pointB;
         pointC.y -= 3;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);
         pgraphics->line_to(pointC);
      }
      break;
      case e_grip_top_right:
      {

         rectangleClient.bottom--;
         rectangleClient.right--;

         rectangleA = rectangleClient;

         pgraphics->set(m_ppenHilight1);

         pointA = rectangleA.top_right();
         pointB = pointA;
         pointB.x -= 16;
         pointC = pointB;
         pointC.y += 4;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);
         pgraphics->line_to(pointC);

         pointB = rectangleA.top_right();
         pointB.x -= 4;
         pointB.y += 4;
         pointC = pointB;
         pointC.y += 12;
         pgraphics->set_current_point(pointB);
         pgraphics->line_to(pointC);

         pgraphics->set(m_ppenFace1);

         pointA = rectangleA.top_right();
         pointA.x--;
         pointA.y++;
         pointB = pointA;
         pointB.x -= 14;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pointA = rectangleA.top_right();
         pointA.x -= 2;
         pointA.y += 2;
         pointB = pointA;
         pointB.x -= 13;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pointA = rectangleA.top_right();
         pointA.x -= 2;
         pointA.y += 2;
         pointB = pointA;
         pointB.y += 13;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pointA = rectangleA.top_right();
         pointA.x -= 3;
         pointA.y += 3;
         pointB = pointA;
         pointB.y += 12;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pgraphics->set(m_ppenShadow1);

         pointA = rectangleA.top_right();
         pointA.x -= 3;
         pointA.y += 3;
         pointB = pointA;
         pointB.x -= 12;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pointA = rectangleA.top_right();
         pointA.x--;
         pointA.y++;
         pointB = pointA;
         pointB.y += 14;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pgraphics->set(m_ppenDkShadow1);

         pointB = rectangleA.top_right();
         pointB.x -= 4;
         pointB.y += 4;
         pointC = pointB;
         pointC.x -= 12;
         pgraphics->set_current_point(pointB);
         pgraphics->line_to(pointC);


         pointA = rectangleA.top_right();
         pointB = pointA;
         pointB.y += 16;
         pointC = pointB;
         pointC.x -= 4;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);
         pgraphics->line_to(pointC);

      }
      break;
      case e_grip_bottom_left:
      {
         pgraphics->set(m_ppenHilight1);

         rectangleClient.bottom--;
         rectangleClient.right--;

         rectangleA = rectangleClient;


         pointA = rectangleA.bottom_left();
         pointB = rectangleA.bottom_left();
         pointB.y -= 16;
         pointC = pointB;
         pointC.x += 4;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB); // vertical left hilite
         pgraphics->line_to(pointC); // horizontal top hilite


         pointB = rectangleA.bottom_left();
         pointB.y -= 4;
         pointB.x += 4;
         pointC = pointB;
         pointC.x += 12;
         pgraphics->set_current_point(pointB);
         pgraphics->line_to(pointC); // horizontal bottom hillite

         pgraphics->set(m_ppenFace1);

         pointA = rectangleA.bottom_left();
         pointA.y--;
         pointA.x++;
         pointB = pointA;
         pointB.y -= 14;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pointA = rectangleA.bottom_left();
         pointA.y -= 2;
         pointA.x += 2;
         pointB = pointA;
         pointB.y -= 13;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pointA = rectangleA.bottom_left();
         pointA.y -= 2;
         pointA.x += 2;
         pointB = pointA;
         pointB.x += 13;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pointA = rectangleA.bottom_left();
         pointA.y -= 3;
         pointA.x += 3;
         pointB = pointA;
         pointB.x += 12;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pgraphics->set(m_ppenShadow1);

         pointA = rectangleA.bottom_left();
         pointA.y -= 3;
         pointA.x += 3;
         pointB = pointA;
         pointB.y -= 12;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pointA = rectangleA.bottom_left();
         pointA.y--;
         pointA.x++;
         pointB = pointA;
         pointB.x += 14;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pgraphics->set(m_ppenDkShadow1);

         pointB = rectangleA.bottom_left();
         pointB.y -= 4;
         pointB.x += 4;
         pointC = pointB;
         pointC.y -= 12;
         pgraphics->set_current_point(pointB);
         pgraphics->line_to(pointC);

         pointA = rectangleA.bottom_left();
         pointB = pointA;
         pointB.x += 16;
         pointC = pointB;
         pointC.y -= 4;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);
         pgraphics->line_to(pointC);

      }
      break;
      case e_grip_bottom_right:
      {
         rectangleClient.bottom--;
         rectangleClient.right--;

         rectangleA = rectangleClient;


         pgraphics->set(m_ppenDkShadow1);

         pointA = rectangleA.bottom_right();
         pointB = pointA;
         pointB.x -= 16;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pointA = rectangleA.bottom_right();
         pointB = pointA;
         pointB.y -= 16;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pgraphics->set(m_ppenShadow1);

         pointA = rectangleA.bottom_right();
         pointA.y--;
         pointA.x--;
         pointB = pointA;
         pointB.x -= 15;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pointA = rectangleA.bottom_right();
         pointA.y--;
         pointA.x--;
         pointB = pointA;
         pointB.y -= 15;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);


         pgraphics->set(m_ppenFace1);

         pointA = rectangleA.bottom_right();
         pointA.y -= 3;
         pointA.x -= 3;
         pointB = pointA;
         pointB.x -= 13;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pointA = rectangleA.bottom_right();
         pointA.y -= 2;
         pointA.x -= 2;
         pointB = pointA;
         pointB.x -= 14;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pointA = rectangleA.bottom_right();
         pointA.y -= 3;
         pointA.x -= 3;
         pointB = pointA;
         pointB.y -= 13;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);

         pointA = rectangleA.bottom_right();
         pointA.y -= 2;
         pointA.x -= 2;
         pointB = pointA;
         pointB.y -= 14;
         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);


         pgraphics->set(m_ppenHilight1);

         pointA = rectangleA.bottom_right();
         pointA.x -= 4;
         pointA.y -= 4;
         pointB = pointA;
         pointB.x -= 12;
         pointC = pointB;
         pointC.y += 4;

         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);
         pgraphics->line_to(pointC);

         pointA = rectangleA.bottom_right();
         pointA.x -= 4;
         pointA.y -= 4;
         pointB = pointA;
         pointB.y -= 12;
         pointC = pointB;
         pointC.x += 4;

         pgraphics->set_current_point(pointA);
         pgraphics->line_to(pointB);
         pgraphics->line_to(pointC);

      }
      break;
      case e_grip_top:
      {
         ::point_i32 pointCenter = rectangle.center();

         ::rectangle_i32 rectangleB;

         rectangleB.top = rectangleClient.top;
         rectangleB.left = pointCenter.x - GRIP_CENTER_LARGE_CX / 2;
         rectangleB.right = pointCenter.x + GRIP_CENTER_LARGE_CX / 2;
         rectangleB.bottom = rectangleB.top + GRIP_CENTER_SMALL_CY;

         DrawRectGrip(pgraphics, rectangleB);
      }
      break;
      case e_grip_bottom:
      {
         ::point_i32 pointCenter = rectangle.center();

         ::rectangle_i32 rectangleB;

         rectangleB.bottom = rectangleClient.bottom;
         rectangleB.left = pointCenter.x - GRIP_CENTER_LARGE_CX / 2;
         rectangleB.right = pointCenter.x + GRIP_CENTER_LARGE_CX / 2;
         rectangleB.top = rectangleB.bottom - GRIP_CENTER_SMALL_CY;

         DrawRectGrip(pgraphics, rectangleB);
      }
      break;
      case e_grip_left:
      {
         ::point_i32 pointCenter = rectangle.center();

         ::rectangle_i32 rectangleB;

         rectangleB.top = pointCenter.y - GRIP_CENTER_LARGE_CY / 2;
         rectangleB.left = rectangleClient.left;
         rectangleB.right = rectangleClient.left + GRIP_CENTER_SMALL_CX;
         rectangleB.bottom = pointCenter.y + GRIP_CENTER_LARGE_CY / 2;

         DrawRectGrip(pgraphics, rectangleB);
      }
      break;
      case e_grip_right:
      {
         ::point_i32 pointCenter = rectangle.center();

         ::rectangle_i32 rectangleB;

         rectangleB.top = pointCenter.y - GRIP_CENTER_LARGE_CY / 2;
         rectangleB.right = rectangleClient.right;
         rectangleB.left = rectangleClient.right - GRIP_CENTER_SMALL_CX;
         rectangleB.bottom = pointCenter.y + GRIP_CENTER_LARGE_CY / 2;

         DrawRectGrip(pgraphics, rectangleB);
      }
      break;
      default:
         break;
      }

   }
   

   void frame_002::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectangleParam)
   {

      //auto psession = get_session();

      ::rectangle_i32 rectangle(rectangleParam);

      auto pframewindow = m_pframewindow;

      auto pstyle = pframewindow->get_style(pgraphics);

      auto crButtonHilite = pframewindow->get_color(pstyle, ::e_element_button_hilite);

      auto crButtonDarkShadow = pframewindow->get_color(pstyle, ::e_element_button_dark_shadow);

      auto crButtonFace = pframewindow->get_color(pstyle, ::e_element_button_background);

      auto crButtonShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

      pgraphics->draw_inset_3d_rectangle(rectangle, crButtonHilite, crButtonDarkShadow);

      rectangle.top++;
      rectangle.bottom--;
      rectangle.left++;
      rectangle.right--;

      pgraphics->draw_inset_3d_rectangle(rectangle, crButtonFace, crButtonShadow);

      rectangle.top++;
      rectangle.bottom--;
      rectangle.left++;
      rectangle.right--;

      pgraphics->fill_rectangle(rectangle, crButtonFace);

   }
   

   void frame_002::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient)
   {

      auto psizenager = m_pframewindow->size_manager();

      enum_grip egrip = psizenager->GetGripMask();

      if(egrip & e_grip_top)
      {
         DrawGrip(pgraphics, rectangleClient, e_grip_top);
      }

      if(egrip & e_grip_top_right)
      {
         DrawGrip(pgraphics, rectangleClient, e_grip_top_right);
      }

      if(egrip & e_grip_right)
      {
         DrawGrip(pgraphics, rectangleClient, e_grip_right);
      }

      if(egrip & e_grip_bottom_right)
      {
         DrawGrip(pgraphics, rectangleClient, e_grip_bottom_right);
      }

      if(egrip & e_grip_bottom)
      {
         DrawGrip(pgraphics, rectangleClient, e_grip_bottom);
      }

      if(egrip & e_grip_bottom_left)
      {
         DrawGrip(pgraphics, rectangleClient, e_grip_bottom_left);
      }

      if(egrip & e_grip_left)
      {
         DrawGrip(pgraphics, rectangleClient, e_grip_left);
      }

      if(egrip & e_grip_top_left)
      {
         DrawGrip(pgraphics, rectangleClient, e_grip_top_left);
      }

   }


   status < ::color::color > frame_002::get_border_main_body_color()
   {

      return m_colorMoveableBorder;

   }

   
} // namespace experience_nanogui



