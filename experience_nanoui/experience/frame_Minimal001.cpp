#include "framework.h"
#include "frame_Minimal001.h"
#include "aura/graphics/draw2d/graphics.h"
#include "base/user/experience/frame_window.h"
#include "base/user/experience/move_manager.h"
#include "base/user/experience/size_manager.h"


#define GRIP_CORNER_LARGE_CX 16
#define GRIP_CORNER_SMALL_CX 5
#define GRIP_CORNER_LARGE_CY 16
#define GRIP_CORNER_SMALL_CY 5

#undef GRIP_CENTER_LARGE_CX
#undef GRIP_CENTER_SMALL_CX
#undef GRIP_CENTER_LARGE_CY
#undef GRIP_CENTER_SMALL_CY


#define GRIP_CENTER_LARGE_CX 18
#define GRIP_CENTER_SMALL_CX 5
#define GRIP_CENTER_LARGE_CY 18
#define GRIP_CENTER_SMALL_CY 5



namespace experience_nanoui
{


   frame_Minimal001::frame_Minimal001()
   {

      //set_style(StyleLightBlue);

      m_rectangleMarginNormal.set(0,0,0,0);


   }


   frame_Minimal001::~frame_Minimal001()
   {

   }


   string frame_Minimal001::get_default_user_style() const
   {

      return "LightBlue";

   }



   ::experience::enum_frame frame_Minimal001::experience_frame_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
   {
      ::experience::enum_frame etest = ::experience::e_frame_client;
      {
         //      m_pframewindow->screen_to_client()(point);
         ::rectangle_i32 rectangleEvent;
         m_pframewindow->window_rectangle(rectangleEvent);
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





   void frame_Minimal001::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClientParam, enum_border eside)
   {
               
      auto rectangleClient(rectangleClientParam);

      if (eside != e_border_top)
      {

         return;

      }

      //auto psession = get_session();

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

//               enum_dock edock = m_pframewindow->dock_manager()->GetDockState();

      //::rectangle_i32 rectangleA(rectangleClient);

      if(pframewindow->is_translucid_user_style(m_pframewindow->m_estyle))
      {

         ::rectangle_i32 rectangle;

         GetBorderRect(rectangleClient, rectangle, eside);

         //auto psystem = acmesystem()->m_paurasystem;

         pgraphics->fill_rectangle(rectangle, ::color::color(crMoveableBorder, 127));

      }
      /*else if(m_pframewindow->m_estyle == StyleLightBlue)
      {

         ::rectangle_i32 rectangle;

         GetBorderRect(rectangleClient, rectangle, eside);



         pgraphics->color_blend( rectangle, crMoveableBorder, 127);



         rectangleA.deflate(2, 2, 2, 2);
         Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorderHilight, crMoveableBorderShadow);

         rectangleA.deflate(1, 1, 1, 1);
         Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorder, crMoveableBorder);

         rectangleA.deflate(1, 1, 1, 1);
         Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorder, crMoveableBorder);


      }*/
      else
      {

         ::rectangle_i32 rectangleClient(rectangleClientParam);

         rectangleClient.deflate(2, 2, 2, 2);

         ::rectangle_i32 rectangle;

         GetBorderRect(rectangleClient, rectangle, eside);

         pgraphics->fill_rectangle( rectangle, ::color::color(crMoveableBorder, 127));

      }

   }


   void frame_Minimal001::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
   {

      auto pframewindow = m_pframewindow;

      if(pframewindow == nullptr)
         return;

      if(!pframewindow->is_frame_experience_enabled())
         return;

      bool bZoomed = pframewindow->layout().is_zoomed() != 0;

      string str;

      ::rectangle_i32 rectangleWindow;

      pframewindow->window_rectangle(rectangleWindow);

      rectangleWindow -= rectangleWindow.top_left();

      if(!pframewindow->layout().is_full_screen())
      {

         DrawBorder(pgraphics, rectangleWindow);

      }

      if(!bZoomed && !pframewindow->layout().is_full_screen())
      {

         DrawGripSet(pgraphics, rectangleWindow);

      }

   }


   void frame_Minimal001::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient)
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

   void frame_Minimal001::GetBorderRect(const ::rectangle_i32 & rectangleClient, RECTANGLE_I32 * lprect, enum_border eside)
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


   void frame_Minimal001::_on_style_change(::draw2d::graphics_pointer & pgraphics)
   {

      on_style_change_001_and_002(pgraphics);

   }


   void frame_Minimal001::DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient, enum_grip egrip)
   {

      return;

//               ::rectangle_i32 rectangleC(rectangleClient);
//
//               ::rectangle_i32 rectangleClient(rectangleClient);
//
//               rectangleClient.right--;
//
//               rectangleClient.bottom--;
//
//               ::rectangle_i32 rectangleClientB(rectangleClient);
//
//               ::rectangle_i32 rectangleA;
//
//               ::point_i32 pointA;
//
//               ::point_i32 pointB;
//
//               ::point_i32 pointC;
//
//               ::rectangle_i32 rectangle(rectangleClient);
//
//               switch(egrip)
//               {
//               case e_grip_top_left:
//               {
//                                  pgraphics->set(m_ppenHilight1);
//
//                                  rectangleA = rectangleClient;
//
//                                  rectangleA.top++;
//                                  rectangleA.left++;
//                                  rectangleA.bottom--;
//                                  rectangleA.right--;
//
//                                  pointA = rectangleA.top_left();
//                                  pointA.y += 14;
//                                  pointB = rectangleA.top_left();
//                                  pointC = rectangleA.top_left();
//                                  pointC.x += 15;
//
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//                                  pgraphics->line_to(pointC);
//
//                                  pgraphics->set(m_ppenFace1);
//
//                                  // Most external rectangle_i32
//
//                                  rectangleA = rectangleClient;
//
//                                  pointA = rectangleA.top_left();
//                                  pointA.y += 15;
//                                  pointB = rectangleA.top_left();
//                                  pointC = rectangleA.top_left();
//                                  pointC.x += 16;
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//                                  pgraphics->line_to(pointC);
//
//                                  // Midle rectangle_i32
//
//                                  rectangleA = rectangleClient;
//
//                                  rectangleA.top += 2;
//                                  rectangleA.left += 2;
//                                  rectangleA.bottom -= 2;
//                                  rectangleA.right -= 2;
//
//                                  pointA = rectangleA.top_left();
//                                  pointA.y += 13;
//                                  pointB = rectangleA.top_left();
//                                  pointC = rectangleA.top_left();
//                                  pointC.x += 14;
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//                                  pgraphics->line_to(pointC);
//
//                                  pgraphics->set(m_ppenShadow1);
//
//                                  rectangleA = rectangleClient;
//
//                                  rectangleA.top++;
//                                  rectangleA.left++;
//                                  rectangleA.bottom--;
//                                  rectangleA.right--;
//
//                                  rectangleA.top += 2;
//                                  rectangleA.left += 2;
//                                  rectangleA.bottom -= 2;
//                                  rectangleA.right -= 2;
//
//
//                                  pointA = rectangleA.top_left();
//                                  pointA.y += 12;
//                                  pointB = rectangleA.top_left();
//                                  pointC = rectangleA.top_left();
//                                  pointC.x += 13;
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//                                  pgraphics->line_to(pointC);
//
//                                  pgraphics->set(m_ppenDkShadow1);
//
//                                  rectangleA = rectangleClient;
//
//                                  rectangleA.top += 4;
//                                  rectangleA.left += 4;
//                                  rectangleA.bottom -= 4;
//                                  rectangleA.right -= 4;
//
//                                  pointA = rectangleA.top_left();
//                                  pointA.y += 11;
//                                  pointB = rectangleA.top_left();
//                                  pointC = rectangleA.top_left();
//                                  pointC.x += 12;
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//                                  pgraphics->line_to(pointC);
//
//                                  pgraphics->set(m_ppenShadow1);
//
//                                  // Details
//
//                                  pointA.x = rectangleClientB.left + 14;
//                                  pointA.y = rectangleClientB.top + 1;
//                                  pointB.x = rectangleClientB.left + 14;
//                                  pointB.y = rectangleClientB.top + 3;
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//
//
//                                  // Details
//
//                                  pointA.x = rectangleClientB.left + 1;
//                                  pointA.y = rectangleClientB.top + 14;
//                                  pointB.x = rectangleClientB.left + 3;
//                                  pointB.y = rectangleClientB.top + 14;
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//
//                                  pgraphics->set(m_ppenDkShadow1);
//
//                                  // Details
//
//                                  pointA.x = rectangleClientB.left + 15;
//                                  pointA.y = rectangleClientB.top + 1;
//                                  pointB.x = rectangleClientB.left + 15;
//                                  pointB.y = rectangleClientB.top + 5;
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//
//                                  // Details
//
//                                  pointA.x = rectangleClientB.left + 1;
//                                  pointA.y = rectangleClientB.top + 15;
//                                  pointB.x = rectangleClientB.left + 5;
//                                  pointB.y = rectangleClientB.top + 15;
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//               }
//                  break;
//               case e_grip_top_right:
//               {
//                                   pgraphics->set(m_ppenHilight1);
//
//                                   rectangleA = rectangleClient;
//
//                                   rectangleA.top++;
//                                   rectangleA.left++;
//                                   rectangleA.bottom--;
//                                   rectangleA.right--;
//
//                                   pointA = rectangleA.top_right();
//                                   pointA.x -= 15;
//                                   pointB = rectangleA.top_right();
//                                   pgraphics->set_current_point(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   rectangleA.top += 2;
//                                   rectangleA.left += 2;
//                                   rectangleA.bottom -= 2;
//                                   rectangleA.right -= 2;
//
//                                   pointB = rectangleA.top_right();
//                                   pointC = rectangleA.top_right();
//                                   pointC.y += 13;
//                                   pgraphics->set_current_point(pointB);
//                                   pgraphics->line_to(pointC);
//
//                                   pgraphics->set(m_ppenFace1);
//
//                                   // Most external rectangle_i32
//
//                                   rectangleA = rectangleClient;
//
//                                   pointA = rectangleA.top_right();
//                                   pointA.x -= 16;
//                                   pointB = rectangleA.top_right();
//                                   pgraphics->set_current_point(pointA);
//                                   pgraphics->line_to(pointB);
//
//
//                                   // Most internal rectangle_i32
//
//                                   rectangleA.top += 4;
//                                   rectangleA.left += 4;
//                                   rectangleA.bottom -= 4;
//                                   rectangleA.right -= 4;
//
//                                   pointB = rectangleA.top_right();
//                                   pointC = rectangleA.top_right();
//                                   pointC.y += 12;
//                                   pgraphics->set_current_point(pointB);
//                                   pgraphics->line_to(pointC);
//
//                                   // Midle rectangle_i32
//
//                                   rectangleA = rectangleClient;
//
//                                   rectangleA.top += 2;
//                                   rectangleA.left += 2;
//                                   rectangleA.bottom -= 2;
//                                   rectangleA.right -= 2;
//
//                                   pointA = rectangleA.top_right();
//                                   pointA.x -= 13;
//                                   pointB = rectangleA.top_right();
//                                   pointC = rectangleA.top_right();
//                                   pointC.y += 14;
//                                   pgraphics->set_current_point(pointA);
//                                   pgraphics->line_to(pointB);
//                                   pgraphics->line_to(pointC);
//
//                                   pgraphics->set(m_ppenShadow1);
//
//                                   rectangleA = rectangleClient;
//
//                                   rectangleA.top++;
//                                   rectangleA.left++;
//                                   rectangleA.bottom--;
//                                   rectangleA.right--;
//
//                                   pointB = rectangleA.top_right();
//                                   pointC = rectangleA.top_right();
//                                   pointC.y += 15;
//                                   pgraphics->set_current_point(pointB);
//                                   pgraphics->line_to(pointC);
//
//                                   rectangleA.top += 2;
//                                   rectangleA.left += 2;
//                                   rectangleA.bottom -= 2;
//                                   rectangleA.right -= 2;
//
//                                   pointA = rectangleA.top_right();
//                                   pointA.x -= 12;
//                                   pointB = rectangleA.top_right();
//                                   pgraphics->set_current_point(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   pgraphics->set(m_ppenDkShadow1);
//
//                                   rectangleA = rectangleClient;
//
//                                   pointB = rectangleA.top_right();
//                                   pointC = rectangleA.top_right();
//                                   pointC.y += 16;
//                                   pgraphics->set_current_point(pointB);
//                                   pgraphics->line_to(pointC);
//
//                                   rectangleA.top += 4;
//                                   rectangleA.left += 4;
//                                   rectangleA.bottom -= 4;
//                                   rectangleA.right -= 4;
//
//                                   pointA = rectangleA.top_right();
//                                   pointA.x -= 11;
//                                   pointB = rectangleA.top_right();
//                                   pgraphics->set_current_point(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   pgraphics->set(m_ppenHilight1);
//
//                                   pointA.x = rectangleClientB.right - 14;
//                                   pointA.y = rectangleClientB.top + 1;
//                                   pointB.x = rectangleClientB.right - 14;
//                                   pointB.y = rectangleClientB.top + 4;
//                                   pgraphics->set_current_point(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   pgraphics->set(m_ppenFace1);
//
//                                   // Details
//
//                                   pointA.x = rectangleClientB.right - 15;
//                                   pointA.y = rectangleClientB.top;
//                                   pointB.x = rectangleClientB.right - 15;
//                                   pointB.y = rectangleClientB.top + 5;
//                                   pgraphics->set_current_point(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   pgraphics->set(m_ppenShadow1);
//
//                                   // Details
//
//                                   pointA.x = rectangleClientB.right - 3;
//                                   pointA.y = rectangleClientB.top + 14;
//                                   pointB.x = rectangleClientB.right - 1;
//                                   pointB.y = rectangleClientB.top + 14;
//                                   pgraphics->set_current_point(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   pgraphics->set(m_ppenDkShadow1);
//
//                                   // Details
//
//                                   pointA.x = rectangleClientB.right - 4;
//                                   pointA.y = rectangleClientB.top + 15;
//                                   pointB.x = rectangleClientB.right;
//                                   pointB.y = rectangleClientB.top + 15;
//                                   pgraphics->set_current_point(pointB);
//                                   pgraphics->line_to(pointA);
//               }
//                  break;
//               case e_grip_bottom_left:
//               {
//
//                                     pgraphics->set(m_ppenHilight1);
//
//                                     rectangleA = rectangleClient;
//
//                                     rectangleA.left++;
//                                     rectangleA.bottom--;
//
//                                     // left 1
//                                     pointA = rectangleA.bottom_left();
//                                     pointA.y -= 16;
//                                     pointB = rectangleA.bottom_left();
//                                     pgraphics->set_current_point(pointB);
//                                     pgraphics->line_to(pointA);
//
//                                     rectangleA = rectangleClient;
//
//                                     rectangleA.left += 3;
//                                     rectangleA.bottom -= 3;
//
//                                     // bottom 2
//                                     pointB = rectangleA.bottom_left();
//                                     pointC = rectangleA.bottom_left();
//                                     pointC.x += 12;
//                                     pgraphics->set_current_point(pointC);
//                                     pgraphics->line_to(pointB);
//
//                                     pgraphics->set(m_ppenFace1);
//
//                                     // Most external rectangle_i32 0
//
//                                     rectangleA = rectangleClient;
//
//                                     pointA = rectangleA.bottom_left();
//                                     pointA.y -= 15;
//                                     pointB = rectangleA.bottom_left();
//                                     pgraphics->set_current_point(pointB);
//                                     pgraphics->line_to(pointA);
//
//                                     // Most internal rectangle_i32 4
//
//                                     rectangleA.top += 4;
//                                     rectangleA.left += 4;
//                                     rectangleA.bottom -= 4;
//                                     rectangleA.right -= 4;
//
//                                     pointB = rectangleA.bottom_left();
//                                     pointC = rectangleA.bottom_left();
//                                     pointC.x += 12;
//                                     pgraphics->set_current_point(pointB);
//                                     pgraphics->line_to(pointC);
//
//                                     // Midle rectangle_i32 2
//
//                                     rectangleA = rectangleClient;
//
//                                     rectangleA.top += 2;
//                                     rectangleA.left += 2;
//                                     rectangleA.bottom -= 2;
//                                     rectangleA.right -= 2;
//
//                                     pointA = rectangleA.bottom_left();
//                                     pointA.y -= 13;
//                                     pointB = rectangleA.bottom_left();
//                                     pointC = rectangleA.bottom_left();
//                                     pointC.x += 14;
//                                     pgraphics->set_current_point(pointA);
//                                     pgraphics->line_to(pointB);
//                                     pgraphics->line_to(pointC);
//
//                                     pgraphics->set(m_ppenShadow1);
//
//                                     rectangleA = rectangleClient;
//
//                                     rectangleA.left += 2;
//                                     rectangleA.bottom--;
//
//                                     pointB = rectangleA.bottom_left();
//                                     pointC = rectangleA.bottom_left();
//                                     pointC.x += 14;
//                                     pgraphics->set_current_point(pointB);
//                                     pgraphics->line_to(pointC);
//
//                                     rectangleA = rectangleClient;
//
//                                     rectangleA.left += 3;
//                                     rectangleA.bottom -= 2;
//
//                                     pointA = rectangleA.bottom_left();
//                                     pointA.y -= 12;
//                                     pointB = rectangleA.bottom_left();
//                                     pgraphics->set_current_point(pointA);
//                                     pgraphics->line_to(pointB);
//
//                                     pgraphics->set(m_ppenDkShadow1);
//
//                                     rectangleA = rectangleClient;
//
//                                     pointB = rectangleA.bottom_left();
//                                     pointB.x++;
//                                     pointC = rectangleA.bottom_left();
//                                     pointC.x += 16;
//                                     pgraphics->set_current_point(pointB);
//                                     pgraphics->line_to(pointC);
//
//                                     rectangleA.left += 4;
//                                     rectangleA.bottom -= 3;
//
//                                     pointA = rectangleA.bottom_left();
//                                     pointA.y -= 11;
//                                     pointB = rectangleA.bottom_left();
//                                     pgraphics->set_current_point(pointA);
//                                     pgraphics->line_to(pointB);
//
//                                     // Details - top most
//
//                                     pgraphics->set(m_ppenHilight1);
//
//                                     pointA.x = rectangleClientB.left + 1;
//                                     pointA.y = rectangleClientB.bottom - 15;
//                                     pointB.x = rectangleClientB.left + 4;
//                                     pointB.y = rectangleClientB.bottom - 15;
//                                     pgraphics->set_current_point(pointA);
//                                     pgraphics->line_to(pointB);
//
//                                     // Details - top most
//
//                                     pgraphics->set(m_ppenFace1);
//
//                                     pointA.x = rectangleClientB.left;
//                                     pointA.y = rectangleClientB.bottom - 15;
//                                     pointB.x = rectangleClientB.left + 5;
//                                     pointB.y = rectangleClientB.bottom - 15;
//                                     pgraphics->set_current_point(pointA);
//                                     pgraphics->line_to(pointB);
//
//                                     pgraphics->set(m_ppenShadow1);
//
//                                     // Details - right most
//
//                                     pointA.x = rectangleClientB.left + 14;
//                                     pointA.y = rectangleClientB.bottom - 4;
//                                     pointB.x = rectangleClientB.left + 14;
//                                     pointB.y = rectangleClientB.bottom - 1;
//                                     pgraphics->set_current_point(pointB);
//                                     pgraphics->line_to(pointA);
//
//                                     pgraphics->set(m_ppenDkShadow1);
//
//                                     // Details - right most
//
//                                     pointA.x = rectangleClientB.left + 15;
//                                     pointA.y = rectangleClientB.bottom - 4;
//                                     pointB.x = rectangleClientB.left + 15;
//                                     pointB.y = rectangleClientB.bottom;
//                                     pgraphics->set_current_point(pointB);
//                                     pgraphics->line_to(pointA);
//               }
//                  break;
//               case e_grip_bottom_right:
//               {
//                                      pgraphics->set(m_ppenHilight1);
//
//                                      rectangleA = rectangleClient;
//
//                                      rectangleA.top++;
//                                      rectangleA.left++;
//                                      rectangleA.bottom--;
//                                      rectangleA.right--;
//
//                                      rectangleA.top += 2;
//                                      rectangleA.left += 2;
//                                      rectangleA.bottom -= 2;
//                                      rectangleA.right -= 2;
//
//                                      pointA = rectangleA.bottom_right();
//                                      pointA.y -= 12;
//                                      pointB = rectangleA.bottom_right();
//                                      pointC = rectangleA.bottom_right();
//                                      pointC.x -= 13;
//                                      pgraphics->set_current_point(pointA);
//                                      pgraphics->line_to(pointB);
//                                      pgraphics->line_to(pointC);
//
//                                      pgraphics->set(m_ppenFace1);
//
//                                      rectangleA = rectangleClient;
//
//                                      // Most internal rectangle_i32
//
//                                      rectangleA.top += 4;
//                                      rectangleA.left += 4;
//                                      rectangleA.bottom -= 4;
//                                      rectangleA.right -= 4;
//
//                                      pointA = rectangleA.bottom_right();
//                                      pointA.y -= 11;
//                                      pointB = rectangleA.bottom_right();
//                                      pointC = rectangleA.bottom_right();
//                                      pointC.x -= 12;
//                                      pgraphics->set_current_point(pointA);
//                                      pgraphics->line_to(pointB);
//                                      pgraphics->line_to(pointC);
//
//                                      // Midle rectangle_i32
//
//                                      rectangleA = rectangleClient;
//
//                                      rectangleA.top += 2;
//                                      rectangleA.left += 2;
//                                      rectangleA.bottom -= 2;
//                                      rectangleA.right -= 2;
//
//                                      pointA = rectangleA.bottom_right();
//                                      pointA.y -= 13;
//                                      pointB = rectangleA.bottom_right();
//                                      pointC = rectangleA.bottom_right();
//                                      pointC.x -= 14;
//                                      pgraphics->set_current_point(pointA);
//                                      pgraphics->line_to(pointB);
//                                      pgraphics->line_to(pointC);
//                                      pgraphics->set(m_ppenShadow1);
//
//                                      rectangleA = rectangleClient;
//
//                                      rectangleA.top++;
//                                      rectangleA.left++;
//                                      rectangleA.bottom--;
//                                      rectangleA.right--;
//
//                                      pointA = rectangleA.bottom_right();
//                                      pointA.y -= 14;
//                                      pointB = rectangleA.bottom_right();
//                                      pointC = rectangleA.bottom_right();
//                                      pointC.x -= 15;
//                                      pgraphics->set_current_point(pointA);
//                                      pgraphics->line_to(pointB);
//                                      pgraphics->line_to(pointC);
//
//                                      pgraphics->set(m_ppenDkShadow1);
//
//                                      rectangleA = rectangleClient;
//
//                                      pointA = rectangleA.bottom_right();
//                                      pointA.y -= 15;
//                                      pointB = rectangleA.bottom_right();
//                                      pointC = rectangleA.bottom_right();
//                                      pointC.x -= 15;
//                                      pgraphics->set_current_point(pointA);
//                                      pgraphics->line_to(pointB);
//                                      pgraphics->line_to(pointC);
//
//                                      pgraphics->set(m_ppenHilight1);
//
//                                      pointA.x = rectangleClientB.right - 3;
//                                      pointA.y = rectangleClientB.bottom - 14;
//                                      pointB.x = rectangleClientB.right - 1;
//                                      pointB.y = rectangleClientB.bottom - 14;
//                                      pgraphics->set_current_point(pointB);
//                                      pgraphics->line_to(pointA);
//
//                                      pointA.x = rectangleClientB.right - 14;
//                                      pointA.y = rectangleClientB.bottom - 3;
//                                      pointB.x = rectangleClientB.right - 14;
//                                      pointB.y = rectangleClientB.bottom - 1;
//                                      pgraphics->set_current_point(pointB);
//                                      pgraphics->line_to(pointA);
//
//                                      pgraphics->set(m_ppenFace1);
//
//                                      // Details
//
//                                      pointA.x = rectangleClientB.right - 5;
//                                      pointA.y = rectangleClientB.bottom - 15;
//                                      pointB.x = rectangleClientB.right;
//                                      pointB.y = rectangleClientB.bottom - 15;
//                                      pgraphics->set_current_point(pointB);
//                                      pgraphics->line_to(pointA);
//
//                                      pointA.x = rectangleClientB.right - 15;
//                                      pointA.y = rectangleClientB.bottom - 5;
//                                      pointB.x = rectangleClientB.right - 15;
//                                      pointB.y = rectangleClientB.bottom;
//                                      pgraphics->set_current_point(pointB);
//                                      pgraphics->line_to(pointA);
//               }
//                  break;
//               case e_grip_top:
//               {
//                                    ::point_i32 pointCenter = rectangle.center();
//
//                                    int iMod;
//                                    if(rectangle.width() % 2 == 1)
//                                       iMod = 1;
//                                    else
//                                       iMod = 0;
//
//                                    ::rectangle_i32 rectangleB;
//
//                                    rectangleB.top = rectangleC.top;
//                                    rectangleB.left = pointCenter.x - GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                    rectangleB.right = pointCenter.x + GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                    rectangleB.bottom = rectangleC.top + GRIP_CENTER_SMALL_CY;
//
//                                    DrawRectGrip(pgraphics, rectangleB);
//               }
//                  break;
//               case e_grip_bottom:
//               {
//                                       ::point_i32 pointCenter = rectangle.center();
//
//                                       ::rectangle_i32 rectangleB;
//
//                                       int iMod;
//                                       if(rectangle.width() % 2 == 1)
//                                          iMod = 1;
//                                       else
//                                          iMod = 0;
//
//                                       rectangleB.bottom = rectangleC.bottom;
//                                       rectangleB.left = pointCenter.x - GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                       rectangleB.right = pointCenter.x + GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                       rectangleB.top = rectangleC.bottom - GRIP_CENTER_SMALL_CY;
//
//                                       DrawRectGrip(pgraphics, rectangleB);
//               }
//                  break;
//               case e_grip_left:
//               {
//                                     ::point_i32 pointCenter = rectangle.center();
//
//                                     int iMod;
//                                     if(rectangle.height() % 2 == 1)
//                                        iMod = 1;
//                                     else
//                                        iMod = 0;
//
//
//                                     ::rectangle_i32 rectangleB;
//
//                                     rectangleB.top = pointCenter.y - GRIP_CENTER_LARGE_CY / 2 + iMod;
//                                     rectangleB.left = rectangleC.left;
//                                     rectangleB.right = rectangleC.left + GRIP_CENTER_SMALL_CX;
//                                     rectangleB.bottom = pointCenter.y + GRIP_CENTER_LARGE_CY / 2 + iMod;
//
//                                     DrawRectGrip(pgraphics, rectangleB);
//               }
//                  break;
//               case e_grip_right:
//               {
//                                      ::point_i32 pointCenter = rectangle.center();
//
//                                      int iMod;
//                                      if(rectangle.height() % 2 == 1)
//                                         iMod = 1;
//                                      else
//                                         iMod = 0;
//
//
//                                      ::rectangle_i32 rectangleB;
//
//                                      rectangleB.top = pointCenter.y - GRIP_CENTER_LARGE_CY / 2 + iMod;
//                                      rectangleB.right = rectangleC.right;
//                                      rectangleB.left = rectangleC.right - GRIP_CENTER_SMALL_CX;
//                                      rectangleB.bottom = pointCenter.y + GRIP_CENTER_LARGE_CY / 2 + iMod;
//
//                                      DrawRectGrip(pgraphics, rectangleB);
//               }
//                  break;
//               default:
//                  break;
//               }


   }

   void frame_Minimal001::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectangleParam)
   {



      ::rectangle_i32 rectangle(rectangleParam);

      //rectangle.right++;

      //rectangle.bottom++;

      //auto psession = get_session();

      auto pframewindow = m_pframewindow;

      auto pstyle = pframewindow->get_style(pgraphics);

      auto crButtonHilite = pframewindow->get_color(pstyle, ::e_element_button_hilite);

      auto crButtonDarkShadow = pframewindow->get_color(pstyle, ::e_element_button_dark_shadow);

      auto crButtonFace = pframewindow->get_color(pstyle, ::e_element_button_background);

      auto crButtonShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

      pgraphics->draw_inset_3d_rectangle(rectangle, opaque(crButtonFace), opaque(crButtonDarkShadow));

      rectangle.deflate(1, 1);

      pgraphics->draw_inset_3d_rectangle(rectangle, opaque(crButtonHilite), opaque(crButtonShadow));

      rectangle.deflate(1, 1);

      //rectangle.right--;

      //rectangle.bottom--;

      pgraphics->fill_rectangle(rectangle, opaque(crButtonFace));

   }

   void frame_Minimal001::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient)
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

//
//   frame_Minimal001::frame_Minimal001()
//   {
//
//      set_style(StyleLightBlue);
//
//      m_rectangleMarginNormal.set(0,0,0,0);
//
//
//   }
//
//
//   frame_Minimal001::~frame_Minimal001()
//   {
//
//   }
//
//
//   string frame_Minimal001::get_default_user_style() const
//   {
//
//      return "LightBlue";
//
//   }
//
//
//
//   ::experience::enum_frame frame_Minimal001::experience_frame_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
//   {
//      ::experience::enum_frame etest = ::experience::e_frame_client;
//      {
//               m_pframewindow->screen_to_client()(point);
//         ::rectangle_i32 rectangleEvent;
//         m_pframewindow->window_rectangle(rectangleEvent);
//         ::rectangle_i32 rectangle;
//         ::point_i32 pointCenter = rectangleEvent.center();
//         enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();
//
//         if(egrip & e_grip_top_left)
//         {
//            rectangle = rectangleEvent;
//            rectangle.right = rectangle.left + 16;
//            rectangle.bottom = rectangle.top + 5;
//            if(rectangle.contains(pointCursor))
//            {
//               etest = ::experience::e_frame_sizing_top_left;
//               goto SizingSuccess;
//            }
//            rectangle = rectangleEvent;
//            rectangle.right = rectangle.left + 5;
//            rectangle.bottom = rectangle.top + 16;
//            if(rectangle.contains(pointCursor))
//            {
//               etest = ::experience::e_frame_sizing_top_left;
//               goto SizingSuccess;
//            }
//         }
//         if(egrip & e_grip_top_right)
//         {
//            rectangle = rectangleEvent;
//            rectangle.left = rectangle.right - 16;
//            rectangle.bottom = rectangle.top + 5;
//            if(rectangle.contains(pointCursor))
//            {
//               etest = ::experience::e_frame_sizing_top_right;
//               goto SizingSuccess;
//            }
//            rectangle = rectangleEvent;
//            rectangle.left = rectangle.right - 5;
//            rectangle.bottom = rectangle.top + 16;
//            if(rectangle.contains(pointCursor))
//            {
//               etest = ::experience::e_frame_sizing_top_right;
//               goto SizingSuccess;
//            }
//         }
//         if(egrip & e_grip_bottom_right)
//         {
//            rectangle = rectangleEvent;
//            rectangle.left = rectangle.right - 16;
//            rectangle.top = rectangle.bottom - 5;
//            if(rectangle.contains(pointCursor))
//            {
//               etest = ::experience::e_frame_sizing_bottom_right;
//               goto SizingSuccess;
//            }
//            rectangle = rectangleEvent;
//            rectangle.left = rectangle.right - 5;
//            rectangle.top = rectangle.bottom - 16;
//            if(rectangle.contains(pointCursor))
//            {
//               etest = ::experience::e_frame_sizing_bottom_right;
//               goto SizingSuccess;
//            }
//         }
//         if(egrip & e_grip_bottom_left)
//         {
//            rectangle = rectangleEvent;
//            rectangle.right = rectangle.left + 16;
//            rectangle.top = rectangle.bottom - 5;
//            if(rectangle.contains(pointCursor))
//            {
//               etest = ::experience::e_frame_sizing_bottom_left;
//               goto SizingSuccess;
//            }
//            rectangle = rectangleEvent;
//            rectangle.right = rectangle.left + 5;
//            rectangle.top = rectangle.bottom - 16;
//            if(rectangle.contains(pointCursor))
//            {
//               etest = ::experience::e_frame_sizing_bottom_left;
//               goto SizingSuccess;
//            }
//         }
//         if(egrip & e_grip_top)
//         {
//            rectangle.top = rectangleEvent.top;
//            rectangle.left = pointCenter.x - 8;
//            rectangle.right = pointCenter.x + 8;
//            rectangle.bottom = rectangleEvent.top + 5;
//            if(rectangle.contains(pointCursor))
//            {
//               etest = ::experience::e_frame_sizing_top;
//               goto SizingSuccess;
//            }
//         }
//         if(egrip & e_grip_bottom)
//         {
//            rectangle.top = rectangleEvent.bottom - 5;
//            rectangle.left = pointCenter.x - 8;
//            rectangle.right = pointCenter.x + 8;
//            rectangle.bottom = rectangleEvent.bottom;
//            if(rectangle.contains(pointCursor))
//            {
//               etest = ::experience::e_frame_sizing_bottom;
//               goto SizingSuccess;
//            }
//         }
//         if(egrip & e_grip_left)
//         {
//            rectangle.top = pointCenter.y - 8;
//            rectangle.left = rectangleEvent.left;
//            rectangle.right = rectangleEvent.left + 5;
//            rectangle.bottom = pointCenter.y + 8;
//            if(rectangle.contains(pointCursor))
//            {
//               etest = ::experience::e_frame_sizing_left;
//               goto SizingSuccess;
//            }
//         }
//         if(egrip & e_grip_right)
//         {
//            rectangle.top = pointCenter.y - 8;
//            rectangle.left = rectangleEvent.right - 5;
//            rectangle.right = rectangleEvent.right;
//            rectangle.bottom = pointCenter.y + 8;
//            if(rectangle.contains(pointCursor))
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
//
//
//
//
//
//   void frame_Minimal001::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClientParam, enum_border eside)
//   {
//               
//      auto rectangleClient(rectangleClientParam);
//
//      if (eside != e_border_top)
//      {
//
//         return;
//
//      }
//
//      auto psession = get_session();
//
//      auto pframewindow = m_pframewindow;
//
//      status < ::color::color > crMoveableBorder;
//      status < ::color::color > crMoveableBorderHilight;
//      status < ::color::color > crMoveableBorderShadow;
//
//      if(pframewindow->is_active_window())
//      {
//
//         crMoveableBorder = m_colorMoveableBorder;
//
//         crMoveableBorderHilight = m_colorMoveableBorderHilight;
//
//         crMoveableBorderShadow = m_colorMoveableBorderShadow;
//
//      }
//      else
//      {
//
//         auto pstyle = pframewindow->get_style(pgraphics);
//
//         crMoveableBorder = pframewindow->get_color(pstyle, ::e_element_button_background);
//
//         crMoveableBorderHilight = pframewindow->get_color(pstyle, ::e_element_button_hilite);
//
//         crMoveableBorderShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);
//
//      }
//
//               enum_dock edock = m_pframewindow->dock_manager()->GetDockState();
//
//      ::rectangle_i32 rectangleA(rectangleClient);
//
//      if(pframewindow->is_translucid_user_style(m_pframewindow->m_estyle))
//      {
//
//         ::rectangle_i32 rectangle;
//
//         GetBorderRect(rectangleClient, rectangle, eside);
//
//         auto psystem = acmesystem()->m_paurasystem;
//
//         pgraphics->fill_rectangle(rectangle, ::color::color(crMoveableBorder, 127));
//
//      }
//      /*else if(m_pframewindow->m_estyle == StyleLightBlue)
//      {
//
//         ::rectangle_i32 rectangle;
//
//         GetBorderRect(rectangleClient, rectangle, eside);
//
//
//
//         pgraphics->color_blend( rectangle, crMoveableBorder, 127);
//
//
//
//         rectangleA.deflate(2, 2, 2, 2);
//         Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorderHilight, crMoveableBorderShadow);
//
//         rectangleA.deflate(1, 1, 1, 1);
//         Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorder, crMoveableBorder);
//
//         rectangleA.deflate(1, 1, 1, 1);
//         Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorder, crMoveableBorder);
//
//
//      }*/
//      else
//      {
//
//         ::rectangle_i32 rectangleClient(rectangleClientParam);
//
//         rectangleClient.deflate(2, 2, 2, 2);
//
//         ::rectangle_i32 rectangle;
//
//         GetBorderRect(rectangleClient, rectangle, eside);
//
//         pgraphics->fill_rectangle( rectangle, ::color::color(crMoveableBorder, 127));
//
//      }
//
//   }
//
//
//   void frame_Minimal001::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      auto pframewindow = m_pframewindow;
//
//      if(pframewindow == nullptr)
//         return;
//
//      if(!pframewindow->is_frame_experience_enabled())
//         return;
//
//      bool bZoomed = pframewindow->layout().is_zoomed() != 0;
//
//      string str;
//
//      ::rectangle_i32 rectangleWindow;
//
//      pframewindow->window_rectangle(rectangleWindow);
//
//      rectangleWindow -= rectangleWindow.top_left();
//
//      if(!pframewindow->layout().is_full_screen())
//      {
//
//         DrawBorder(pgraphics, rectangleWindow);
//
//      }
//
//      if(!bZoomed && !pframewindow->layout().is_full_screen())
//      {
//
//         DrawGripSet(pgraphics, rectangleWindow);
//
//      }
//
//   }
//
//
//   void frame_Minimal001::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient)
//   {
//
//      auto pmovemanager = m_pframewindow->move_manager();
//
//      enum_border eborder = pmovemanager->GetBorderMask();
//
//      if(m_pframewindow->layout().is_zoomed())
//      {
//         eborder = (enum_border)
//                     (eborder &
//                     ~(e_border_right
//                        | e_border_bottom
//                        | e_border_left));
//      }
//
//      if(eborder & e_border_top)
//      {
//
//         draw_border_side(pgraphics, rectangleClient, e_border_top);
//
//      }
//
//      if(eborder & e_border_right)
//      {
//
//         draw_border_side(pgraphics, rectangleClient, e_border_right);
//
//      }
//
//      if(eborder & e_border_bottom)
//      {
//
//         draw_border_side(pgraphics, rectangleClient, e_border_bottom);
//
//      }
//
//      if(eborder & e_border_left)
//      {
//
//         draw_border_side(pgraphics, rectangleClient, e_border_left);
//
//      }
//
//   }
//
//   void frame_Minimal001::GetBorderRect(const ::rectangle_i32 & rectangleClient, RECTANGLE_I32 * lprect, enum_border eside)
//   {
//
//      ::rectangle_i32 rectangleBig(rectangleClient);
//
//      ::rectangle_i32 rectangleSmall;
//
//      get_window_client_rect(rectangleSmall);
//
//      ::rectangle_i32 rectangle;
//
//      if(eside == e_border_top)
//      {
//         rectangle.left = rectangleBig.left;
//         rectangle.right = rectangleBig.right;
//         rectangle.top = rectangleBig.top;
//         rectangle.bottom = rectangleSmall.top;
//      }
//      else if(eside == e_border_left)
//      {
//         rectangle.left = rectangleBig.left;
//         rectangle.right = rectangleSmall.left;
//         rectangle.top = rectangleSmall.top;
//         rectangle.bottom = rectangleSmall.bottom;
//      }
//      else if(eside == e_border_right)
//      {
//         rectangle.left = rectangleSmall.right;
//         rectangle.right = rectangleBig.right;
//         rectangle.top = rectangleSmall.top;
//         rectangle.bottom = rectangleSmall.bottom;
//      }
//      else if(eside == e_border_bottom)
//      {
//         rectangle.left = rectangleBig.left;
//         rectangle.right = rectangleBig.right;
//         rectangle.top = rectangleSmall.bottom;
//         rectangle.bottom = rectangleBig.bottom;
//      }
//      *lprect = rectangle;
//   }
//
//
//   void frame_Minimal001::_on_style_change(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      on_style_change_001_and_002(pgraphics);
//
//   }
//
//
//   void frame_Minimal001::DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient, enum_grip egrip)
//   {
//
//      return;
//
//               ::rectangle_i32 rectangleC(rectangleClient);
//
//               ::rectangle_i32 rectangleClient(rectangleClient);
//
//               rectangleClient.right--;
//
//               rectangleClient.bottom--;
//
//               ::rectangle_i32 rectangleClientB(rectangleClient);
//
//               ::rectangle_i32 rectangleA;
//
//               ::point_i32 pointA;
//
//               ::point_i32 pointB;
//
//               ::point_i32 pointC;
//
//               ::rectangle_i32 rectangle(rectangleClient);
//
//               switch(egrip)
//               {
//               case e_grip_top_left:
//               {
//                                  pgraphics->set(m_ppenHilight1);
//
//                                  rectangleA = rectangleClient;
//
//                                  rectangleA.top++;
//                                  rectangleA.left++;
//                                  rectangleA.bottom--;
//                                  rectangleA.right--;
//
//                                  pointA = rectangleA.top_left();
//                                  pointA.y += 14;
//                                  pointB = rectangleA.top_left();
//                                  pointC = rectangleA.top_left();
//                                  pointC.x += 15;
//
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//                                  pgraphics->line_to(pointC);
//
//                                  pgraphics->set(m_ppenFace1);
//
//                                   Most external rectangle_i32
//
//                                  rectangleA = rectangleClient;
//
//                                  pointA = rectangleA.top_left();
//                                  pointA.y += 15;
//                                  pointB = rectangleA.top_left();
//                                  pointC = rectangleA.top_left();
//                                  pointC.x += 16;
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//                                  pgraphics->line_to(pointC);
//
//                                   Midle rectangle_i32
//
//                                  rectangleA = rectangleClient;
//
//                                  rectangleA.top += 2;
//                                  rectangleA.left += 2;
//                                  rectangleA.bottom -= 2;
//                                  rectangleA.right -= 2;
//
//                                  pointA = rectangleA.top_left();
//                                  pointA.y += 13;
//                                  pointB = rectangleA.top_left();
//                                  pointC = rectangleA.top_left();
//                                  pointC.x += 14;
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//                                  pgraphics->line_to(pointC);
//
//                                  pgraphics->set(m_ppenShadow1);
//
//                                  rectangleA = rectangleClient;
//
//                                  rectangleA.top++;
//                                  rectangleA.left++;
//                                  rectangleA.bottom--;
//                                  rectangleA.right--;
//
//                                  rectangleA.top += 2;
//                                  rectangleA.left += 2;
//                                  rectangleA.bottom -= 2;
//                                  rectangleA.right -= 2;
//
//
//                                  pointA = rectangleA.top_left();
//                                  pointA.y += 12;
//                                  pointB = rectangleA.top_left();
//                                  pointC = rectangleA.top_left();
//                                  pointC.x += 13;
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//                                  pgraphics->line_to(pointC);
//
//                                  pgraphics->set(m_ppenDkShadow1);
//
//                                  rectangleA = rectangleClient;
//
//                                  rectangleA.top += 4;
//                                  rectangleA.left += 4;
//                                  rectangleA.bottom -= 4;
//                                  rectangleA.right -= 4;
//
//                                  pointA = rectangleA.top_left();
//                                  pointA.y += 11;
//                                  pointB = rectangleA.top_left();
//                                  pointC = rectangleA.top_left();
//                                  pointC.x += 12;
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//                                  pgraphics->line_to(pointC);
//
//                                  pgraphics->set(m_ppenShadow1);
//
//                                   Details
//
//                                  pointA.x = rectangleClientB.left + 14;
//                                  pointA.y = rectangleClientB.top + 1;
//                                  pointB.x = rectangleClientB.left + 14;
//                                  pointB.y = rectangleClientB.top + 3;
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//
//
//                                   Details
//
//                                  pointA.x = rectangleClientB.left + 1;
//                                  pointA.y = rectangleClientB.top + 14;
//                                  pointB.x = rectangleClientB.left + 3;
//                                  pointB.y = rectangleClientB.top + 14;
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//
//                                  pgraphics->set(m_ppenDkShadow1);
//
//                                   Details
//
//                                  pointA.x = rectangleClientB.left + 15;
//                                  pointA.y = rectangleClientB.top + 1;
//                                  pointB.x = rectangleClientB.left + 15;
//                                  pointB.y = rectangleClientB.top + 5;
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//
//                                   Details
//
//                                  pointA.x = rectangleClientB.left + 1;
//                                  pointA.y = rectangleClientB.top + 15;
//                                  pointB.x = rectangleClientB.left + 5;
//                                  pointB.y = rectangleClientB.top + 15;
//                                  pgraphics->set_current_point(pointA);
//                                  pgraphics->line_to(pointB);
//               }
//                  break;
//               case e_grip_top_right:
//               {
//                                   pgraphics->set(m_ppenHilight1);
//
//                                   rectangleA = rectangleClient;
//
//                                   rectangleA.top++;
//                                   rectangleA.left++;
//                                   rectangleA.bottom--;
//                                   rectangleA.right--;
//
//                                   pointA = rectangleA.top_right();
//                                   pointA.x -= 15;
//                                   pointB = rectangleA.top_right();
//                                   pgraphics->set_current_point(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   rectangleA.top += 2;
//                                   rectangleA.left += 2;
//                                   rectangleA.bottom -= 2;
//                                   rectangleA.right -= 2;
//
//                                   pointB = rectangleA.top_right();
//                                   pointC = rectangleA.top_right();
//                                   pointC.y += 13;
//                                   pgraphics->set_current_point(pointB);
//                                   pgraphics->line_to(pointC);
//
//                                   pgraphics->set(m_ppenFace1);
//
//                                    Most external rectangle_i32
//
//                                   rectangleA = rectangleClient;
//
//                                   pointA = rectangleA.top_right();
//                                   pointA.x -= 16;
//                                   pointB = rectangleA.top_right();
//                                   pgraphics->set_current_point(pointA);
//                                   pgraphics->line_to(pointB);
//
//
//                                    Most internal rectangle_i32
//
//                                   rectangleA.top += 4;
//                                   rectangleA.left += 4;
//                                   rectangleA.bottom -= 4;
//                                   rectangleA.right -= 4;
//
//                                   pointB = rectangleA.top_right();
//                                   pointC = rectangleA.top_right();
//                                   pointC.y += 12;
//                                   pgraphics->set_current_point(pointB);
//                                   pgraphics->line_to(pointC);
//
//                                    Midle rectangle_i32
//
//                                   rectangleA = rectangleClient;
//
//                                   rectangleA.top += 2;
//                                   rectangleA.left += 2;
//                                   rectangleA.bottom -= 2;
//                                   rectangleA.right -= 2;
//
//                                   pointA = rectangleA.top_right();
//                                   pointA.x -= 13;
//                                   pointB = rectangleA.top_right();
//                                   pointC = rectangleA.top_right();
//                                   pointC.y += 14;
//                                   pgraphics->set_current_point(pointA);
//                                   pgraphics->line_to(pointB);
//                                   pgraphics->line_to(pointC);
//
//                                   pgraphics->set(m_ppenShadow1);
//
//                                   rectangleA = rectangleClient;
//
//                                   rectangleA.top++;
//                                   rectangleA.left++;
//                                   rectangleA.bottom--;
//                                   rectangleA.right--;
//
//                                   pointB = rectangleA.top_right();
//                                   pointC = rectangleA.top_right();
//                                   pointC.y += 15;
//                                   pgraphics->set_current_point(pointB);
//                                   pgraphics->line_to(pointC);
//
//                                   rectangleA.top += 2;
//                                   rectangleA.left += 2;
//                                   rectangleA.bottom -= 2;
//                                   rectangleA.right -= 2;
//
//                                   pointA = rectangleA.top_right();
//                                   pointA.x -= 12;
//                                   pointB = rectangleA.top_right();
//                                   pgraphics->set_current_point(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   pgraphics->set(m_ppenDkShadow1);
//
//                                   rectangleA = rectangleClient;
//
//                                   pointB = rectangleA.top_right();
//                                   pointC = rectangleA.top_right();
//                                   pointC.y += 16;
//                                   pgraphics->set_current_point(pointB);
//                                   pgraphics->line_to(pointC);
//
//                                   rectangleA.top += 4;
//                                   rectangleA.left += 4;
//                                   rectangleA.bottom -= 4;
//                                   rectangleA.right -= 4;
//
//                                   pointA = rectangleA.top_right();
//                                   pointA.x -= 11;
//                                   pointB = rectangleA.top_right();
//                                   pgraphics->set_current_point(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   pgraphics->set(m_ppenHilight1);
//
//                                   pointA.x = rectangleClientB.right - 14;
//                                   pointA.y = rectangleClientB.top + 1;
//                                   pointB.x = rectangleClientB.right - 14;
//                                   pointB.y = rectangleClientB.top + 4;
//                                   pgraphics->set_current_point(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   pgraphics->set(m_ppenFace1);
//
//                                    Details
//
//                                   pointA.x = rectangleClientB.right - 15;
//                                   pointA.y = rectangleClientB.top;
//                                   pointB.x = rectangleClientB.right - 15;
//                                   pointB.y = rectangleClientB.top + 5;
//                                   pgraphics->set_current_point(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   pgraphics->set(m_ppenShadow1);
//
//                                    Details
//
//                                   pointA.x = rectangleClientB.right - 3;
//                                   pointA.y = rectangleClientB.top + 14;
//                                   pointB.x = rectangleClientB.right - 1;
//                                   pointB.y = rectangleClientB.top + 14;
//                                   pgraphics->set_current_point(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   pgraphics->set(m_ppenDkShadow1);
//
//                                    Details
//
//                                   pointA.x = rectangleClientB.right - 4;
//                                   pointA.y = rectangleClientB.top + 15;
//                                   pointB.x = rectangleClientB.right;
//                                   pointB.y = rectangleClientB.top + 15;
//                                   pgraphics->set_current_point(pointB);
//                                   pgraphics->line_to(pointA);
//               }
//                  break;
//               case e_grip_bottom_left:
//               {
//
//                                     pgraphics->set(m_ppenHilight1);
//
//                                     rectangleA = rectangleClient;
//
//                                     rectangleA.left++;
//                                     rectangleA.bottom--;
//
//                                      left 1
//                                     pointA = rectangleA.bottom_left();
//                                     pointA.y -= 16;
//                                     pointB = rectangleA.bottom_left();
//                                     pgraphics->set_current_point(pointB);
//                                     pgraphics->line_to(pointA);
//
//                                     rectangleA = rectangleClient;
//
//                                     rectangleA.left += 3;
//                                     rectangleA.bottom -= 3;
//
//                                      bottom 2
//                                     pointB = rectangleA.bottom_left();
//                                     pointC = rectangleA.bottom_left();
//                                     pointC.x += 12;
//                                     pgraphics->set_current_point(pointC);
//                                     pgraphics->line_to(pointB);
//
//                                     pgraphics->set(m_ppenFace1);
//
//                                      Most external rectangle_i32 0
//
//                                     rectangleA = rectangleClient;
//
//                                     pointA = rectangleA.bottom_left();
//                                     pointA.y -= 15;
//                                     pointB = rectangleA.bottom_left();
//                                     pgraphics->set_current_point(pointB);
//                                     pgraphics->line_to(pointA);
//
//                                      Most internal rectangle_i32 4
//
//                                     rectangleA.top += 4;
//                                     rectangleA.left += 4;
//                                     rectangleA.bottom -= 4;
//                                     rectangleA.right -= 4;
//
//                                     pointB = rectangleA.bottom_left();
//                                     pointC = rectangleA.bottom_left();
//                                     pointC.x += 12;
//                                     pgraphics->set_current_point(pointB);
//                                     pgraphics->line_to(pointC);
//
//                                      Midle rectangle_i32 2
//
//                                     rectangleA = rectangleClient;
//
//                                     rectangleA.top += 2;
//                                     rectangleA.left += 2;
//                                     rectangleA.bottom -= 2;
//                                     rectangleA.right -= 2;
//
//                                     pointA = rectangleA.bottom_left();
//                                     pointA.y -= 13;
//                                     pointB = rectangleA.bottom_left();
//                                     pointC = rectangleA.bottom_left();
//                                     pointC.x += 14;
//                                     pgraphics->set_current_point(pointA);
//                                     pgraphics->line_to(pointB);
//                                     pgraphics->line_to(pointC);
//
//                                     pgraphics->set(m_ppenShadow1);
//
//                                     rectangleA = rectangleClient;
//
//                                     rectangleA.left += 2;
//                                     rectangleA.bottom--;
//
//                                     pointB = rectangleA.bottom_left();
//                                     pointC = rectangleA.bottom_left();
//                                     pointC.x += 14;
//                                     pgraphics->set_current_point(pointB);
//                                     pgraphics->line_to(pointC);
//
//                                     rectangleA = rectangleClient;
//
//                                     rectangleA.left += 3;
//                                     rectangleA.bottom -= 2;
//
//                                     pointA = rectangleA.bottom_left();
//                                     pointA.y -= 12;
//                                     pointB = rectangleA.bottom_left();
//                                     pgraphics->set_current_point(pointA);
//                                     pgraphics->line_to(pointB);
//
//                                     pgraphics->set(m_ppenDkShadow1);
//
//                                     rectangleA = rectangleClient;
//
//                                     pointB = rectangleA.bottom_left();
//                                     pointB.x++;
//                                     pointC = rectangleA.bottom_left();
//                                     pointC.x += 16;
//                                     pgraphics->set_current_point(pointB);
//                                     pgraphics->line_to(pointC);
//
//                                     rectangleA.left += 4;
//                                     rectangleA.bottom -= 3;
//
//                                     pointA = rectangleA.bottom_left();
//                                     pointA.y -= 11;
//                                     pointB = rectangleA.bottom_left();
//                                     pgraphics->set_current_point(pointA);
//                                     pgraphics->line_to(pointB);
//
//                                      Details - top most
//
//                                     pgraphics->set(m_ppenHilight1);
//
//                                     pointA.x = rectangleClientB.left + 1;
//                                     pointA.y = rectangleClientB.bottom - 15;
//                                     pointB.x = rectangleClientB.left + 4;
//                                     pointB.y = rectangleClientB.bottom - 15;
//                                     pgraphics->set_current_point(pointA);
//                                     pgraphics->line_to(pointB);
//
//                                      Details - top most
//
//                                     pgraphics->set(m_ppenFace1);
//
//                                     pointA.x = rectangleClientB.left;
//                                     pointA.y = rectangleClientB.bottom - 15;
//                                     pointB.x = rectangleClientB.left + 5;
//                                     pointB.y = rectangleClientB.bottom - 15;
//                                     pgraphics->set_current_point(pointA);
//                                     pgraphics->line_to(pointB);
//
//                                     pgraphics->set(m_ppenShadow1);
//
//                                      Details - right most
//
//                                     pointA.x = rectangleClientB.left + 14;
//                                     pointA.y = rectangleClientB.bottom - 4;
//                                     pointB.x = rectangleClientB.left + 14;
//                                     pointB.y = rectangleClientB.bottom - 1;
//                                     pgraphics->set_current_point(pointB);
//                                     pgraphics->line_to(pointA);
//
//                                     pgraphics->set(m_ppenDkShadow1);
//
//                                      Details - right most
//
//                                     pointA.x = rectangleClientB.left + 15;
//                                     pointA.y = rectangleClientB.bottom - 4;
//                                     pointB.x = rectangleClientB.left + 15;
//                                     pointB.y = rectangleClientB.bottom;
//                                     pgraphics->set_current_point(pointB);
//                                     pgraphics->line_to(pointA);
//               }
//                  break;
//               case e_grip_bottom_right:
//               {
//                                      pgraphics->set(m_ppenHilight1);
//
//                                      rectangleA = rectangleClient;
//
//                                      rectangleA.top++;
//                                      rectangleA.left++;
//                                      rectangleA.bottom--;
//                                      rectangleA.right--;
//
//                                      rectangleA.top += 2;
//                                      rectangleA.left += 2;
//                                      rectangleA.bottom -= 2;
//                                      rectangleA.right -= 2;
//
//                                      pointA = rectangleA.bottom_right();
//                                      pointA.y -= 12;
//                                      pointB = rectangleA.bottom_right();
//                                      pointC = rectangleA.bottom_right();
//                                      pointC.x -= 13;
//                                      pgraphics->set_current_point(pointA);
//                                      pgraphics->line_to(pointB);
//                                      pgraphics->line_to(pointC);
//
//                                      pgraphics->set(m_ppenFace1);
//
//                                      rectangleA = rectangleClient;
//
//                                       Most internal rectangle_i32
//
//                                      rectangleA.top += 4;
//                                      rectangleA.left += 4;
//                                      rectangleA.bottom -= 4;
//                                      rectangleA.right -= 4;
//
//                                      pointA = rectangleA.bottom_right();
//                                      pointA.y -= 11;
//                                      pointB = rectangleA.bottom_right();
//                                      pointC = rectangleA.bottom_right();
//                                      pointC.x -= 12;
//                                      pgraphics->set_current_point(pointA);
//                                      pgraphics->line_to(pointB);
//                                      pgraphics->line_to(pointC);
//
//                                       Midle rectangle_i32
//
//                                      rectangleA = rectangleClient;
//
//                                      rectangleA.top += 2;
//                                      rectangleA.left += 2;
//                                      rectangleA.bottom -= 2;
//                                      rectangleA.right -= 2;
//
//                                      pointA = rectangleA.bottom_right();
//                                      pointA.y -= 13;
//                                      pointB = rectangleA.bottom_right();
//                                      pointC = rectangleA.bottom_right();
//                                      pointC.x -= 14;
//                                      pgraphics->set_current_point(pointA);
//                                      pgraphics->line_to(pointB);
//                                      pgraphics->line_to(pointC);
//                                      pgraphics->set(m_ppenShadow1);
//
//                                      rectangleA = rectangleClient;
//
//                                      rectangleA.top++;
//                                      rectangleA.left++;
//                                      rectangleA.bottom--;
//                                      rectangleA.right--;
//
//                                      pointA = rectangleA.bottom_right();
//                                      pointA.y -= 14;
//                                      pointB = rectangleA.bottom_right();
//                                      pointC = rectangleA.bottom_right();
//                                      pointC.x -= 15;
//                                      pgraphics->set_current_point(pointA);
//                                      pgraphics->line_to(pointB);
//                                      pgraphics->line_to(pointC);
//
//                                      pgraphics->set(m_ppenDkShadow1);
//
//                                      rectangleA = rectangleClient;
//
//                                      pointA = rectangleA.bottom_right();
//                                      pointA.y -= 15;
//                                      pointB = rectangleA.bottom_right();
//                                      pointC = rectangleA.bottom_right();
//                                      pointC.x -= 15;
//                                      pgraphics->set_current_point(pointA);
//                                      pgraphics->line_to(pointB);
//                                      pgraphics->line_to(pointC);
//
//                                      pgraphics->set(m_ppenHilight1);
//
//                                      pointA.x = rectangleClientB.right - 3;
//                                      pointA.y = rectangleClientB.bottom - 14;
//                                      pointB.x = rectangleClientB.right - 1;
//                                      pointB.y = rectangleClientB.bottom - 14;
//                                      pgraphics->set_current_point(pointB);
//                                      pgraphics->line_to(pointA);
//
//                                      pointA.x = rectangleClientB.right - 14;
//                                      pointA.y = rectangleClientB.bottom - 3;
//                                      pointB.x = rectangleClientB.right - 14;
//                                      pointB.y = rectangleClientB.bottom - 1;
//                                      pgraphics->set_current_point(pointB);
//                                      pgraphics->line_to(pointA);
//
//                                      pgraphics->set(m_ppenFace1);
//
//                                       Details
//
//                                      pointA.x = rectangleClientB.right - 5;
//                                      pointA.y = rectangleClientB.bottom - 15;
//                                      pointB.x = rectangleClientB.right;
//                                      pointB.y = rectangleClientB.bottom - 15;
//                                      pgraphics->set_current_point(pointB);
//                                      pgraphics->line_to(pointA);
//
//                                      pointA.x = rectangleClientB.right - 15;
//                                      pointA.y = rectangleClientB.bottom - 5;
//                                      pointB.x = rectangleClientB.right - 15;
//                                      pointB.y = rectangleClientB.bottom;
//                                      pgraphics->set_current_point(pointB);
//                                      pgraphics->line_to(pointA);
//               }
//                  break;
//               case e_grip_top:
//               {
//                                    ::point_i32 pointCenter = rectangle.center();
//
//                                    int iMod;
//                                    if(rectangle.width() % 2 == 1)
//                                       iMod = 1;
//                                    else
//                                       iMod = 0;
//
//                                    ::rectangle_i32 rectangleB;
//
//                                    rectangleB.top = rectangleC.top;
//                                    rectangleB.left = pointCenter.x - GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                    rectangleB.right = pointCenter.x + GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                    rectangleB.bottom = rectangleC.top + GRIP_CENTER_SMALL_CY;
//
//                                    DrawRectGrip(pgraphics, rectangleB);
//               }
//                  break;
//               case e_grip_bottom:
//               {
//                                       ::point_i32 pointCenter = rectangle.center();
//
//                                       ::rectangle_i32 rectangleB;
//
//                                       int iMod;
//                                       if(rectangle.width() % 2 == 1)
//                                          iMod = 1;
//                                       else
//                                          iMod = 0;
//
//                                       rectangleB.bottom = rectangleC.bottom;
//                                       rectangleB.left = pointCenter.x - GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                       rectangleB.right = pointCenter.x + GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                       rectangleB.top = rectangleC.bottom - GRIP_CENTER_SMALL_CY;
//
//                                       DrawRectGrip(pgraphics, rectangleB);
//               }
//                  break;
//               case e_grip_left:
//               {
//                                     ::point_i32 pointCenter = rectangle.center();
//
//                                     int iMod;
//                                     if(rectangle.height() % 2 == 1)
//                                        iMod = 1;
//                                     else
//                                        iMod = 0;
//
//
//                                     ::rectangle_i32 rectangleB;
//
//                                     rectangleB.top = pointCenter.y - GRIP_CENTER_LARGE_CY / 2 + iMod;
//                                     rectangleB.left = rectangleC.left;
//                                     rectangleB.right = rectangleC.left + GRIP_CENTER_SMALL_CX;
//                                     rectangleB.bottom = pointCenter.y + GRIP_CENTER_LARGE_CY / 2 + iMod;
//
//                                     DrawRectGrip(pgraphics, rectangleB);
//               }
//                  break;
//               case e_grip_right:
//               {
//                                      ::point_i32 pointCenter = rectangle.center();
//
//                                      int iMod;
//                                      if(rectangle.height() % 2 == 1)
//                                         iMod = 1;
//                                      else
//                                         iMod = 0;
//
//
//                                      ::rectangle_i32 rectangleB;
//
//                                      rectangleB.top = pointCenter.y - GRIP_CENTER_LARGE_CY / 2 + iMod;
//                                      rectangleB.right = rectangleC.right;
//                                      rectangleB.left = rectangleC.right - GRIP_CENTER_SMALL_CX;
//                                      rectangleB.bottom = pointCenter.y + GRIP_CENTER_LARGE_CY / 2 + iMod;
//
//                                      DrawRectGrip(pgraphics, rectangleB);
//               }
//                  break;
//               default:
//                  break;
//               }
//
//
//   }
//
//   void frame_Minimal001::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectangleParam)
//   {
//
//
//
//      ::rectangle_i32 rectangle(rectangleParam);
//
//      rectangle.right++;
//
//      rectangle.bottom++;
//
//      auto psession = get_session();
//
//      auto pframewindow = m_pframewindow;
//
//      auto pstyle = pframewindow->get_style(pgraphics);
//
//      auto crButtonHilite = pframewindow->get_color(pstyle, ::e_element_button_hilite);
//
//      auto crButtonDarkShadow = pframewindow->get_color(pstyle, ::e_element_button_dark_shadow);
//
//      auto crButtonFace = pframewindow->get_color(pstyle, ::e_element_button_background);
//
//      auto crButtonShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);
//
//      pgraphics->draw_inset_3d_rectangle(rectangle, opaque(crButtonFace), opaque(crButtonDarkShadow));
//
//      rectangle.deflate(1, 1);
//
//      pgraphics->draw_inset_3d_rectangle(rectangle, opaque(crButtonHilite), opaque(crButtonShadow));
//
//      rectangle.deflate(1, 1);
//
//      rectangle.right--;
//
//      rectangle.bottom--;
//
//      pgraphics->fill_rectangle(rectangle, opaque(crButtonFace));
//
//   }
//
//   void frame_Minimal001::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient)
//   {
//
//      auto psizenager = m_pframewindow->size_manager();
//
//      enum_grip egrip = psizenager->GetGripMask();
//
//      if(egrip & e_grip_top)
//      {
//         DrawGrip(pgraphics, rectangleClient, e_grip_top);
//      }
//      if(egrip & e_grip_top_right)
//      {
//         DrawGrip(pgraphics, rectangleClient, e_grip_top_right);
//      }
//      if(egrip & e_grip_right)
//      {
//         DrawGrip(pgraphics, rectangleClient, e_grip_right);
//      }
//      if(egrip & e_grip_bottom_right)
//      {
//         DrawGrip(pgraphics, rectangleClient, e_grip_bottom_right);
//      }
//      if(egrip & e_grip_bottom)
//      {
//         DrawGrip(pgraphics, rectangleClient, e_grip_bottom);
//      }
//      if(egrip & e_grip_bottom_left)
//      {
//         DrawGrip(pgraphics, rectangleClient, e_grip_bottom_left);
//      }
//      if(egrip & e_grip_left)
//      {
//         DrawGrip(pgraphics, rectangleClient, e_grip_left);
//      }
//      if(egrip & e_grip_top_left)
//      {
//         DrawGrip(pgraphics, rectangleClient, e_grip_top_left);
//      }
//
//   }


} // namespace experience_nanoui



