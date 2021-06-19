#include "framework.h"

#define GRIP_CORNER_LARGE_CX 16
#define GRIP_CORNER_SMALL_CX 5
#define GRIP_CORNER_LARGE_CY 16
#define GRIP_CORNER_SMALL_CY 5

#define GRIP_CENTER_LARGE_CX 18
#define GRIP_CENTER_SMALL_CX 5
#define GRIP_CENTER_LARGE_CY 18
#define GRIP_CENTER_SMALL_CY 5





   namespace experience
   {


      


         namespace lite

         {


            frame_001::frame_001(::object * pobject) :
               object(pobject),
               frame(pobject)
            {

               set_style(StyleLightBlue);

            }


            frame_001::~frame_001()
            {

            }


            e_hittest frame_001::_001HitTest(::point_i32 pointCursor)
            {
               e_hittest etest = hittest_client;
               {
                  //      m_pframewindow->GetEventWindow()->_001ScreenToClient(point);
                  ::rectangle_i32 rectEvent;
                  m_pframewindow->get_window_rect(rectEvent);
                  ::rectangle_i32 rectangle;
                  point_i32 ptCenter = rectEvent.center();
                  enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();

                  if(egrip & e_grip_top_left)
                  {
                     rectangle = rectEvent;
                     rectangle.right = rectangle.left + 16;
                     rectangle.bottom = rectangle.top + 5;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = hittest_sizing_top_left;
                        goto SizingSuccess;
                     }
                     rectangle = rectEvent;
                     rectangle.right = rectangle.left + 5;
                     rectangle.bottom = rectangle.top + 16;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = hittest_sizing_top_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_top_right)
                  {
                     rectangle = rectEvent;
                     rectangle.left = rectangle.right - 16;
                     rectangle.bottom = rectangle.top + 5;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = hittest_sizing_top_right;
                        goto SizingSuccess;
                     }
                     rectangle = rectEvent;
                     rectangle.left = rectangle.right - 5;
                     rectangle.bottom = rectangle.top + 16;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = hittest_sizing_top_right;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_bottom_right)
                  {
                     rectangle = rectEvent;
                     rectangle.left = rectangle.right - 16;
                     rectangle.top = rectangle.bottom - 5;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = hittest_sizing_bottom_right;
                        goto SizingSuccess;
                     }
                     rectangle = rectEvent;
                     rectangle.left = rectangle.right - 5;
                     rectangle.top = rectangle.bottom - 16;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = hittest_sizing_bottom_right;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_bottom_left)
                  {
                     rectangle = rectEvent;
                     rectangle.right = rectangle.left + 16;
                     rectangle.top = rectangle.bottom - 5;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = hittest_sizing_bottom_left;
                        goto SizingSuccess;
                     }
                     rectangle = rectEvent;
                     rectangle.right = rectangle.left + 5;
                     rectangle.top = rectangle.bottom - 16;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = hittest_sizing_bottom_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_top)
                  {
                     rectangle.top = rectEvent.top;
                     rectangle.left = ptCenter.x - 8;
                     rectangle.right = ptCenter.x + 8;
                     rectangle.bottom = rectEvent.top + 5;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = hittest_sizing_top;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_bottom)
                  {
                     rectangle.top = rectEvent.bottom - 5;
                     rectangle.left = ptCenter.x - 8;
                     rectangle.right = ptCenter.x + 8;
                     rectangle.bottom = rectEvent.bottom;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = hittest_sizing_bottom;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_left)
                  {
                     rectangle.top = ptCenter.y - 8;
                     rectangle.left = rectEvent.left;
                     rectangle.right = rectEvent.left + 5;
                     rectangle.bottom = ptCenter.y + 8;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = hittest_sizing_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_right)
                  {
                     rectangle.top = ptCenter.y - 8;
                     rectangle.left = rectEvent.right - 5;
                     rectangle.right = rectEvent.right;
                     rectangle.bottom = ptCenter.y + 8;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = hittest_sizing_right;
                        goto SizingSuccess;
                     }
                  }
                  goto SizingNone;
SizingSuccess:
                  return etest;
SizingNone:;
               }
               return hittest_client;
            }





            void frame_001::draw_border_side(::draw2d::graphics_pointer & pgraphics, const RECTANGLE_I32 & lpcrectClient, enum_border eside)
            {

               auto pframewindow = m_pframewindow;

               color32_t    crMoveableBorder;

               color32_t    crMoveableBorderHilight;

               color32_t    crMoveableBorderShadow;

               if(pframewindow->m_fActive)
               {

                  crMoveableBorder = m_colorMoveableBorder;

                  crMoveableBorderHilight = m_colorMoveableBorderHilight;

                  crMoveableBorderShadow = m_colorMoveableBorderShadow;

               }
               else
               {
                  auto psession = get_session();

                  auto pstyle = pframewindow->get_style(pgraphics);

                  crMoveableBorder = pframewindow->get_color(pstyle, ::user::e_element_button_background);

                  crMoveableBorderHilight = pframewindow->get_color(pstyle, ::user::e_element_button_hilite);

                  crMoveableBorderShadow = pframewindow->get_color(pstyle, ::user::e_element_button_shadow);

}



//               enum_dock edock = m_pframewindow->dock_manager()->GetDockState();

               ::rectangle_i32 rectA(lpcrectClient);

               if(is_translucid_style(m_estyle))
               {

                  ::rectangle_i32 rectangle;

                  GetBorderRect(lpcrectClient, rectangle, eside);



                  pgraphics->color_blend( rectangle, crMoveableBorder, 127);

               }
               /*else if(m_estyle == StyleLightBlue)
               {

                  ::rectangle_i32 rectangle;

                  GetBorderRect(lpcrectClient, rectangle, eside);



                  pgraphics->color_blend( rectangle, crMoveableBorder, 127);



                  rectA.deflate(2, 2, 2, 2);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorderHilight, crMoveableBorderShadow);

                  rectA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorder, crMoveableBorder);

                  rectA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorder, crMoveableBorder);


               }*/
               else
               {

                  ::rectangle_i32 rectangleClient(lpcrectClient);

                  rectangleClient.deflate(2, 2, 2, 2);

                  ::rectangle_i32 rectangle;

                  GetBorderRect(rectangleClient, rectangle, eside);



                  pgraphics->color_blend( rectangle, crMoveableBorder, 127);

               }

            }


            void frame_001::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
            {

               auto pframewindow = m_pframewindow;

               if(pframewindow == nullptr)
                  return;

               auto pframewindow = m_pframewindow;

               if(!pframewindow->is_frame_experience_enabled())
                  return;

               auto pframewindow = m_pframewindow;

               bool bZoomed = pframewindow->layout().is_zoomed() != 0;

               string str;

               ::rectangle_i32 rectWindow;

               pframewindow->get_window_rect(rectWindow);

               rectWindow -= rectWindow.top_left();

               if(!pframewindow->layout().is_full_screen())
               {

                  DrawBorder(pgraphics, rectWindow);

               }

               if(!bZoomed && !pframewindow->layout().is_full_screen())
               {

                  DrawGripSet(pgraphics, rectWindow);

               }

            }


            void frame_001::DrawBorder(::draw2d::graphics_pointer & pgraphics, const RECTANGLE_I32 & lpcrectClient)
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

                  draw_border_side(pgraphics, lpcrectClient, e_border_top);

               }

               if(eborder & e_border_right)
               {

                  draw_border_side(pgraphics, lpcrectClient, e_border_right);

               }

               if(eborder & e_border_bottom)
               {

                  draw_border_side(pgraphics, lpcrectClient, e_border_bottom);

               }

               if(eborder & e_border_left)
               {

                  draw_border_side(pgraphics, lpcrectClient, e_border_left);

               }

            }

            void frame_001::GetBorderRect(const RECTANGLE_I32 & lpcrectClient, RECTANGLE_I32 * lprect, enum_border eside)
            {

               ::rectangle_i32 rectBig(lpcrectClient);

               ::rectangle_i32 rectSmall;

               get_window_client_rect(rectSmall);

               ::rectangle_i32 rectangle;

               if(eside == e_border_top)
               {
                  rectangle.left = rectBig.left;
                  rectangle.right = rectBig.right;
                  rectangle.top = rectBig.top;
                  rectangle.bottom = rectSmall.top;
               }
               else if(eside == e_border_left)
               {
                  rectangle.left = rectBig.left;
                  rectangle.right = rectSmall.left;
                  rectangle.top = rectSmall.top;
                  rectangle.bottom = rectSmall.bottom;
               }
               else if(eside == e_border_right)
               {
                  rectangle.left = rectSmall.right;
                  rectangle.right = rectBig.right;
                  rectangle.top = rectSmall.top;
                  rectangle.bottom = rectSmall.bottom;
               }
               else if(eside == e_border_bottom)
               {
                  rectangle.left = rectBig.left;
                  rectangle.right = rectBig.right;
                  rectangle.top = rectSmall.bottom;
                  rectangle.bottom = rectBig.bottom;
               }
               *lprect = rectangle;
            }


            void frame_001::on_style_change()
            {

               on_style_change_001_and_002(pgraphics);

            }


            void frame_001::DrawGrip(::draw2d::graphics_pointer & pgraphics, const RECTANGLE_I32 & lpcrectClient, enum_grip egrip)
            {

               ::rectangle_i32 rectC(lpcrectClient);

               ::rectangle_i32 rectangleClient(lpcrectClient);

               rectangleClient.right--;

               rectangleClient.bottom--;

               ::rectangle_i32 rectClientB(rectangleClient);

               ::rectangle_i32 rectA;

               point_i32 ptA;

               point_i32 ptB;

               point_i32 ptC;

               ::rectangle_i32 rectangle(rectangleClient);



               switch(egrip)
               {
               case e_grip_top_left:
               {
                  pgraphics->SelectObject(m_penHilight1);

                  rectA = rectangleClient;

                  rectA.top++;
                  rectA.left++;
                  rectA.bottom--;
                  rectA.right--;

                  ptA = rectA.top_left();
                  ptA.y += 14;
                  ptB = rectA.top_left();
                  ptC = rectA.top_left();
                  ptC.x += 15;

                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  pgraphics->SelectObject(m_penFace1);

                  // Most external rectangle_i32

                  rectA = rectangleClient;

                  ptA = rectA.top_left();
                  ptA.y += 15;
                  ptB = rectA.top_left();
                  ptC = rectA.top_left();
                  ptC.x += 16;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  // Midle Rectangle

                  rectA = rectangleClient;

                  rectA.top += 2;
                  rectA.left += 2;
                  rectA.bottom -= 2;
                  rectA.right -= 2;

                  ptA = rectA.top_left();
                  ptA.y += 13;
                  ptB = rectA.top_left();
                  ptC = rectA.top_left();
                  ptC.x += 14;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  pgraphics->SelectObject(m_penShadow1);

                  rectA = rectangleClient;

                  rectA.top++;
                  rectA.left++;
                  rectA.bottom--;
                  rectA.right--;

                  rectA.top += 2;
                  rectA.left += 2;
                  rectA.bottom -= 2;
                  rectA.right -= 2;


                  ptA = rectA.top_left();
                  ptA.y += 12;
                  ptB = rectA.top_left();
                  ptC = rectA.top_left();
                  ptC.x += 13;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  pgraphics->SelectObject(m_penDkShadow1);

                  rectA = rectangleClient;

                  rectA.top += 4;
                  rectA.left += 4;
                  rectA.bottom -= 4;
                  rectA.right -= 4;

                  ptA = rectA.top_left();
                  ptA.y += 11;
                  ptB = rectA.top_left();
                  ptC = rectA.top_left();
                  ptC.x += 12;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  pgraphics->SelectObject(m_penShadow1);

                  // Details

                  ptA.x = rectClientB.left + 14;
                  ptA.y = rectClientB.top + 1;
                  ptB.x = rectClientB.left + 14;
                  ptB.y = rectClientB.top + 3;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);


                  // Details

                  ptA.x = rectClientB.left + 1;
                  ptA.y = rectClientB.top + 14;
                  ptB.x = rectClientB.left + 3;
                  ptB.y = rectClientB.top + 14;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penDkShadow1);

                  // Details

                  ptA.x = rectClientB.left + 15;
                  ptA.y = rectClientB.top + 1;
                  ptB.x = rectClientB.left + 15;
                  ptB.y = rectClientB.top + 5;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  // Details

                  ptA.x = rectClientB.left + 1;
                  ptA.y = rectClientB.top + 15;
                  ptB.x = rectClientB.left + 5;
                  ptB.y = rectClientB.top + 15;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
               }
               break;
               case e_grip_top_right:
               {
                  pgraphics->SelectObject(m_penHilight1);

                  rectA = rectangleClient;

                  rectA.top++;
                  rectA.left++;
                  rectA.bottom--;
                  rectA.right--;

                  ptA = rectA.top_right();
                  ptA.x -= 15;
                  ptB = rectA.top_right();
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  rectA.top += 2;
                  rectA.left += 2;
                  rectA.bottom -= 2;
                  rectA.right -= 2;

                  ptB = rectA.top_right();
                  ptC = rectA.top_right();
                  ptC.y += 13;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptC);

                  pgraphics->SelectObject(m_penFace1);

                  // Most external rectangle_i32

                  rectA = rectangleClient;

                  ptA = rectA.top_right();
                  ptA.x -= 16;
                  ptB = rectA.top_right();
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);


                  // Most internal rectangle_i32

                  rectA.top += 4;
                  rectA.left += 4;
                  rectA.bottom -= 4;
                  rectA.right -= 4;

                  ptB = rectA.top_right();
                  ptC = rectA.top_right();
                  ptC.y += 12;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptC);

                  // Midle Rectangle

                  rectA = rectangleClient;

                  rectA.top += 2;
                  rectA.left += 2;
                  rectA.bottom -= 2;
                  rectA.right -= 2;

                  ptA = rectA.top_right();
                  ptA.x -= 13;
                  ptB = rectA.top_right();
                  ptC = rectA.top_right();
                  ptC.y += 14;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  pgraphics->SelectObject(m_penShadow1);

                  rectA = rectangleClient;

                  rectA.top++;
                  rectA.left++;
                  rectA.bottom--;
                  rectA.right--;

                  ptB = rectA.top_right();
                  ptC = rectA.top_right();
                  ptC.y += 15;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptC);

                  rectA.top += 2;
                  rectA.left += 2;
                  rectA.bottom -= 2;
                  rectA.right -= 2;

                  ptA = rectA.top_right();
                  ptA.x -= 12;
                  ptB = rectA.top_right();
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penDkShadow1);

                  rectA = rectangleClient;

                  ptB = rectA.top_right();
                  ptC = rectA.top_right();
                  ptC.y += 16;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptC);

                  rectA.top += 4;
                  rectA.left += 4;
                  rectA.bottom -= 4;
                  rectA.right -= 4;

                  ptA = rectA.top_right();
                  ptA.x -= 11;
                  ptB = rectA.top_right();
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penHilight1);

                  ptA.x = rectClientB.right - 14;
                  ptA.y = rectClientB.top + 1;
                  ptB.x = rectClientB.right - 14;
                  ptB.y = rectClientB.top + 4;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penFace1);

                  // Details

                  ptA.x = rectClientB.right - 15;
                  ptA.y = rectClientB.top;
                  ptB.x = rectClientB.right - 15;
                  ptB.y = rectClientB.top + 5;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penShadow1);

                  // Details

                  ptA.x = rectClientB.right - 3;
                  ptA.y = rectClientB.top + 14;
                  ptB.x = rectClientB.right - 1;
                  ptB.y = rectClientB.top + 14;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penDkShadow1);

                  // Details

                  ptA.x = rectClientB.right - 4;
                  ptA.y = rectClientB.top + 15;
                  ptB.x = rectClientB.right;
                  ptB.y = rectClientB.top + 15;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptA);
               }
               break;
               case e_grip_bottom_left:
               {

                  pgraphics->SelectObject(m_penHilight1);

                  rectA = rectangleClient;

                  rectA.left++;
                  rectA.bottom--;

                  // left 1
                  ptA = rectA.bottom_left();
                  ptA.y -= 16;
                  ptB = rectA.bottom_left();
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptA);

                  rectA = rectangleClient;

                  rectA.left += 3;
                  rectA.bottom -= 3;

                  // bottom 2
                  ptB = rectA.bottom_left();
                  ptC = rectA.bottom_left();
                  ptC.x += 12;
                  pgraphics->move_to(ptC);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penFace1);

                  // Most external rectangle_i32 0

                  rectA = rectangleClient;

                  ptA = rectA.bottom_left();
                  ptA.y -= 15;
                  ptB = rectA.bottom_left();
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptA);

                  // Most internal rectangle_i32 4

                  rectA.top += 4;
                  rectA.left += 4;
                  rectA.bottom -= 4;
                  rectA.right -= 4;

                  ptB = rectA.bottom_left();
                  ptC = rectA.bottom_left();
                  ptC.x += 12;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptC);

                  // Midle Rectangle 2

                  rectA = rectangleClient;

                  rectA.top += 2;
                  rectA.left += 2;
                  rectA.bottom -= 2;
                  rectA.right -= 2;

                  ptA = rectA.bottom_left();
                  ptA.y -= 13;
                  ptB = rectA.bottom_left();
                  ptC = rectA.bottom_left();
                  ptC.x += 14;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  pgraphics->SelectObject(m_penShadow1);

                  rectA = rectangleClient;

                  rectA.left += 2;
                  rectA.bottom--;

                  ptB = rectA.bottom_left();
                  ptC = rectA.bottom_left();
                  ptC.x += 14;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptC);

                  rectA = rectangleClient;

                  rectA.left += 3;
                  rectA.bottom -= 2;

                  ptA = rectA.bottom_left();
                  ptA.y -= 12;
                  ptB = rectA.bottom_left();
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penDkShadow1);

                  rectA = rectangleClient;

                  ptB = rectA.bottom_left();
                  ptB.x++;
                  ptC = rectA.bottom_left();
                  ptC.x += 16;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptC);

                  rectA.left += 4;
                  rectA.bottom -= 3;

                  ptA = rectA.bottom_left();
                  ptA.y -= 11;
                  ptB = rectA.bottom_left();
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  // Details - top most

                  pgraphics->SelectObject(m_penHilight1);

                  ptA.x = rectClientB.left + 1;
                  ptA.y = rectClientB.bottom - 15;
                  ptB.x = rectClientB.left + 4;
                  ptB.y = rectClientB.bottom - 15;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  // Details - top most

                  pgraphics->SelectObject(m_penFace1);

                  ptA.x = rectClientB.left;
                  ptA.y = rectClientB.bottom - 15;
                  ptB.x = rectClientB.left + 5;
                  ptB.y = rectClientB.bottom - 15;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penShadow1);

                  // Details - right most

                  ptA.x = rectClientB.left + 14;
                  ptA.y = rectClientB.bottom - 4;
                  ptB.x = rectClientB.left + 14;
                  ptB.y = rectClientB.bottom - 1;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptA);

                  pgraphics->SelectObject(m_penDkShadow1);

                  // Details - right most

                  ptA.x = rectClientB.left + 15;
                  ptA.y = rectClientB.bottom - 4;
                  ptB.x = rectClientB.left + 15;
                  ptB.y = rectClientB.bottom;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptA);
               }
               break;
               case e_grip_bottom_right:
               {
                  pgraphics->SelectObject(m_penHilight1);

                  rectA = rectangleClient;

                  rectA.top++;
                  rectA.left++;
                  rectA.bottom--;
                  rectA.right--;

                  rectA.top += 2;
                  rectA.left += 2;
                  rectA.bottom -= 2;
                  rectA.right -= 2;

                  ptA = rectA.bottom_right();
                  ptA.y -= 12;
                  ptB = rectA.bottom_right();
                  ptC = rectA.bottom_right();
                  ptC.x -= 13;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  pgraphics->SelectObject(m_penFace1);

                  rectA = rectangleClient;

                  // Most internal rectangle_i32

                  rectA.top += 4;
                  rectA.left += 4;
                  rectA.bottom -= 4;
                  rectA.right -= 4;

                  ptA = rectA.bottom_right();
                  ptA.y -= 11;
                  ptB = rectA.bottom_right();
                  ptC = rectA.bottom_right();
                  ptC.x -= 12;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  // Midle Rectangle

                  rectA = rectangleClient;

                  rectA.top += 2;
                  rectA.left += 2;
                  rectA.bottom -= 2;
                  rectA.right -= 2;

                  ptA = rectA.bottom_right();
                  ptA.y -= 13;
                  ptB = rectA.bottom_right();
                  ptC = rectA.bottom_right();
                  ptC.x -= 14;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);
                  pgraphics->SelectObject(m_penShadow1);

                  rectA = rectangleClient;

                  rectA.top++;
                  rectA.left++;
                  rectA.bottom--;
                  rectA.right--;

                  ptA = rectA.bottom_right();
                  ptA.y -= 14;
                  ptB = rectA.bottom_right();
                  ptC = rectA.bottom_right();
                  ptC.x -= 15;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  pgraphics->SelectObject(m_penDkShadow1);

                  rectA = rectangleClient;

                  ptA = rectA.bottom_right();
                  ptA.y -= 15;
                  ptB = rectA.bottom_right();
                  ptC = rectA.bottom_right();
                  ptC.x -= 15;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  pgraphics->SelectObject(m_penHilight1);

                  ptA.x = rectClientB.right - 3;
                  ptA.y = rectClientB.bottom - 14;
                  ptB.x = rectClientB.right - 1;
                  ptB.y = rectClientB.bottom - 14;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptA);

                  ptA.x = rectClientB.right - 14;
                  ptA.y = rectClientB.bottom - 3;
                  ptB.x = rectClientB.right - 14;
                  ptB.y = rectClientB.bottom - 1;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptA);

                  pgraphics->SelectObject(m_penFace1);

                  // Details

                  ptA.x = rectClientB.right - 5;
                  ptA.y = rectClientB.bottom - 15;
                  ptB.x = rectClientB.right;
                  ptB.y = rectClientB.bottom - 15;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptA);

                  ptA.x = rectClientB.right - 15;
                  ptA.y = rectClientB.bottom - 5;
                  ptB.x = rectClientB.right - 15;
                  ptB.y = rectClientB.bottom;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptA);
               }
               break;
               case e_grip_top:
               {
                  point_i32 ptCenter = rectangle.center();

                  int iMod;
                  if(rectangle.width() % 2 == 1)
                     iMod = 1;
                  else
                     iMod = 0;

                  ::rectangle_i32 rectB;

                  rectB.top = rectC.top;
                  rectB.left = ptCenter.x - GRIP_CENTER_LARGE_CX / 2 + iMod;
                  rectB.right = ptCenter.x + GRIP_CENTER_LARGE_CX / 2 + iMod;
                  rectB.bottom = rectC.top + GRIP_CENTER_SMALL_CY;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               case e_grip_bottom:
               {
                  point_i32 ptCenter = rectangle.center();

                  ::rectangle_i32 rectB;

                  int iMod;
                  if(rectangle.width() % 2 == 1)
                     iMod = 1;
                  else
                     iMod = 0;

                  rectB.bottom = rectC.bottom;
                  rectB.left = ptCenter.x - GRIP_CENTER_LARGE_CX / 2 + iMod;
                  rectB.right = ptCenter.x + GRIP_CENTER_LARGE_CX / 2 + iMod;
                  rectB.top = rectC.bottom - GRIP_CENTER_SMALL_CY;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               case e_grip_left:
               {
                  point_i32 ptCenter = rectangle.center();

                  int iMod;
                  if(rectangle.height() % 2 == 1)
                     iMod = 1;
                  else
                     iMod = 0;


                  ::rectangle_i32 rectB;

                  rectB.top = ptCenter.y - GRIP_CENTER_LARGE_CY / 2 + iMod;
                  rectB.left = rectC.left;
                  rectB.right = rectC.left + GRIP_CENTER_SMALL_CX;
                  rectB.bottom = ptCenter.y + GRIP_CENTER_LARGE_CY / 2 + iMod;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               case e_grip_right:
               {
                  point_i32 ptCenter = rectangle.center();

                  int iMod;
                  if(rectangle.height() % 2 == 1)
                     iMod = 1;
                  else
                     iMod = 0;


                  ::rectangle_i32 rectB;

                  rectB.top = ptCenter.y - GRIP_CENTER_LARGE_CY / 2 + iMod;
                  rectB.right = rectC.right;
                  rectB.left = rectC.right - GRIP_CENTER_SMALL_CX;
                  rectB.bottom = ptCenter.y + GRIP_CENTER_LARGE_CY / 2 + iMod;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               default:
                  break;
               }


            }

            void frame_001::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const RECTANGLE_I32 & rectParam)
            {



               ::rectangle_i32 rectangle(rectParam);

               //rectangle.right++;

               //rectangle.bottom++;

               pgraphics->draw3d_rect(rectangle, crButtonFace | 0xff000000, crButtonDarkShadow | 0xff000000);

               rectangle.deflate(1, 1);

               pgraphics->draw3d_rect(rectangle, crButtonHilite | 0xff000000, crButtonShadow | 0xff000000);

               rectangle.deflate(1, 1);

               pgraphics->fill_rectangle(rectangle, crButtonFace | 0xff000000);

            }

            void frame_001::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const RECTANGLE_I32 & lpcrectClient)
            {
               size_manager * psizenager = m_pframewindow->size_manager();

               enum_grip egrip = psizenager->GetGripMask();

               if(egrip & e_grip_top)
               {
                  DrawGrip(pgraphics, lpcrectClient, e_grip_top);
               }
               if(egrip & e_grip_top_right)
               {
                  DrawGrip(pgraphics, lpcrectClient, e_grip_top_right);
               }
               if(egrip & e_grip_right)
               {
                  DrawGrip(pgraphics, lpcrectClient, e_grip_right);
               }
               if(egrip & e_grip_bottom_right)
               {
                  DrawGrip(pgraphics, lpcrectClient, e_grip_bottom_right);
               }
               if(egrip & e_grip_bottom)
               {
                  DrawGrip(pgraphics, lpcrectClient, e_grip_bottom);
               }
               if(egrip & e_grip_bottom_left)
               {
                  DrawGrip(pgraphics, lpcrectClient, e_grip_bottom_left);
               }
               if(egrip & e_grip_left)
               {
                  DrawGrip(pgraphics, lpcrectClient, e_grip_left);
               }
               if(egrip & e_grip_top_left)
               {
                  DrawGrip(pgraphics, lpcrectClient, e_grip_top_left);
               }

            }


         } // namespace lite



      


   } // namespace experience


















































