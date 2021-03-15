#include "framework.h"

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



   namespace experience
   {



         namespace core
         {


            frame_Minimal001::frame_Minimal001()
            {

               //set_style(StyleLightBlue);

               m_rectMarginNormal.set(0,0,0,0);


            }


            frame_Minimal001::~frame_Minimal001()
            {

            }


            string frame_Minimal001::get_default_user_style() const
            {

               return "LightBlue";

            }



            e_hittest frame_Minimal001::_001HitTest(const ::point_i32 & pointCursor)
            {
               e_hittest etest = hittest_client;
               {
                  //      m_pframewindow->_001ScreenToClient(point);
                  ::rectangle_i32 rectEvent;
                  m_pframewindow->get_window_rect(rectEvent);
                  ::rectangle_i32 rectangle;
                  ::point_i32 pointCenter = rectEvent.center();
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
                     rectangle.left = pointCenter.x - 8;
                     rectangle.right = pointCenter.x + 8;
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
                     rectangle.left = pointCenter.x - 8;
                     rectangle.right = pointCenter.x + 8;
                     rectangle.bottom = rectEvent.bottom;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = hittest_sizing_bottom;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_left)
                  {
                     rectangle.top = pointCenter.y - 8;
                     rectangle.left = rectEvent.left;
                     rectangle.right = rectEvent.left + 5;
                     rectangle.bottom = pointCenter.y + 8;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = hittest_sizing_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_right)
                  {
                     rectangle.top = pointCenter.y - 8;
                     rectangle.left = rectEvent.right - 5;
                     rectangle.right = rectEvent.right;
                     rectangle.bottom = pointCenter.y + 8;
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





            void frame_Minimal001::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClientParam, enum_border eside)
            {
               
               auto rectClient(rectClientParam);

               if (eside != e_border_top)
               {

                  return;

               }

               auto psession = get_session();

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

                  crMoveableBorder = pframewindow->get_color(pstyle, ::user::e_element_button_background);

                  crMoveableBorderHilight = pframewindow->get_color(pstyle, ::user::e_element_button_hilite);

                  crMoveableBorderShadow = pframewindow->get_color(pstyle, ::user::e_element_button_shadow);

               }

//               enum_dock edock = m_pframewindow->dock_manager()->GetDockState();

               //::rectangle_i32 rectA(rectClient);

               if(pframewindow->is_translucid_user_style(m_pframewindow->m_estyle))
               {

                  ::rectangle_i32 rectangle;

                  GetBorderRect(rectClient, rectangle, eside);

                  auto psystem = get_system();



                  pgraphics->color_blend( rectangle, crMoveableBorder, 127);

               }
               /*else if(m_pframewindow->m_estyle == StyleLightBlue)
               {

                  ::rectangle_i32 rectangle;

                  GetBorderRect(rectClient, rectangle, eside);



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

                  ::rectangle_i32 rectClient(rectClientParam);

                  rectClient.deflate(2, 2, 2, 2);

                  ::rectangle_i32 rectangle;

                  GetBorderRect(rectClient, rectangle, eside);



                  pgraphics->color_blend( rectangle, crMoveableBorder, 127);

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


            void frame_Minimal001::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient)
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

                  draw_border_side(pgraphics, rectClient, e_border_top);

               }

               if(eborder & e_border_right)
               {

                  draw_border_side(pgraphics, rectClient, e_border_right);

               }

               if(eborder & e_border_bottom)
               {

                  draw_border_side(pgraphics, rectClient, e_border_bottom);

               }

               if(eborder & e_border_left)
               {

                  draw_border_side(pgraphics, rectClient, e_border_left);

               }

            }

            void frame_Minimal001::GetBorderRect(const ::rectangle_i32 & rectClient, RECTANGLE_I32 * lprect, enum_border eside)
            {

               ::rectangle_i32 rectBig(rectClient);

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


            void frame_Minimal001::_on_style_change(::draw2d::graphics_pointer & pgraphics)
            {

               on_style_change_001_and_002(pgraphics);

            }


            void frame_Minimal001::DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient, enum_grip egrip)
            {

               return;

//               ::rectangle_i32 rectC(rectClient);
//
//               ::rectangle_i32 rectClient(rectClient);
//
//               rectClient.right--;
//
//               rectClient.bottom--;
//
//               ::rectangle_i32 rectClientB(rectClient);
//
//               ::rectangle_i32 rectA;
//
//               ::point_i32 pointA;
//
//               ::point_i32 pointB;
//
//               ::point_i32 pointC;
//
//               ::rectangle_i32 rectangle(rectClient);
//
//               switch(egrip)
//               {
//               case e_grip_top_left:
//               {
//                                  pgraphics->set(m_penHilight1);
//
//                                  rectA = rectClient;
//
//                                  rectA.top++;
//                                  rectA.left++;
//                                  rectA.bottom--;
//                                  rectA.right--;
//
//                                  pointA = rectA.top_left();
//                                  pointA.y += 14;
//                                  pointB = rectA.top_left();
//                                  pointC = rectA.top_left();
//                                  pointC.x += 15;
//
//                                  pgraphics->move_to(pointA);
//                                  pgraphics->line_to(pointB);
//                                  pgraphics->line_to(pointC);
//
//                                  pgraphics->set(m_penFace1);
//
//                                  // Most external rectangle_i32
//
//                                  rectA = rectClient;
//
//                                  pointA = rectA.top_left();
//                                  pointA.y += 15;
//                                  pointB = rectA.top_left();
//                                  pointC = rectA.top_left();
//                                  pointC.x += 16;
//                                  pgraphics->move_to(pointA);
//                                  pgraphics->line_to(pointB);
//                                  pgraphics->line_to(pointC);
//
//                                  // Midle rectangle_i32
//
//                                  rectA = rectClient;
//
//                                  rectA.top += 2;
//                                  rectA.left += 2;
//                                  rectA.bottom -= 2;
//                                  rectA.right -= 2;
//
//                                  pointA = rectA.top_left();
//                                  pointA.y += 13;
//                                  pointB = rectA.top_left();
//                                  pointC = rectA.top_left();
//                                  pointC.x += 14;
//                                  pgraphics->move_to(pointA);
//                                  pgraphics->line_to(pointB);
//                                  pgraphics->line_to(pointC);
//
//                                  pgraphics->set(m_penShadow1);
//
//                                  rectA = rectClient;
//
//                                  rectA.top++;
//                                  rectA.left++;
//                                  rectA.bottom--;
//                                  rectA.right--;
//
//                                  rectA.top += 2;
//                                  rectA.left += 2;
//                                  rectA.bottom -= 2;
//                                  rectA.right -= 2;
//
//
//                                  pointA = rectA.top_left();
//                                  pointA.y += 12;
//                                  pointB = rectA.top_left();
//                                  pointC = rectA.top_left();
//                                  pointC.x += 13;
//                                  pgraphics->move_to(pointA);
//                                  pgraphics->line_to(pointB);
//                                  pgraphics->line_to(pointC);
//
//                                  pgraphics->set(m_penDkShadow1);
//
//                                  rectA = rectClient;
//
//                                  rectA.top += 4;
//                                  rectA.left += 4;
//                                  rectA.bottom -= 4;
//                                  rectA.right -= 4;
//
//                                  pointA = rectA.top_left();
//                                  pointA.y += 11;
//                                  pointB = rectA.top_left();
//                                  pointC = rectA.top_left();
//                                  pointC.x += 12;
//                                  pgraphics->move_to(pointA);
//                                  pgraphics->line_to(pointB);
//                                  pgraphics->line_to(pointC);
//
//                                  pgraphics->set(m_penShadow1);
//
//                                  // Details
//
//                                  pointA.x = rectClientB.left + 14;
//                                  pointA.y = rectClientB.top + 1;
//                                  pointB.x = rectClientB.left + 14;
//                                  pointB.y = rectClientB.top + 3;
//                                  pgraphics->move_to(pointA);
//                                  pgraphics->line_to(pointB);
//
//
//                                  // Details
//
//                                  pointA.x = rectClientB.left + 1;
//                                  pointA.y = rectClientB.top + 14;
//                                  pointB.x = rectClientB.left + 3;
//                                  pointB.y = rectClientB.top + 14;
//                                  pgraphics->move_to(pointA);
//                                  pgraphics->line_to(pointB);
//
//                                  pgraphics->set(m_penDkShadow1);
//
//                                  // Details
//
//                                  pointA.x = rectClientB.left + 15;
//                                  pointA.y = rectClientB.top + 1;
//                                  pointB.x = rectClientB.left + 15;
//                                  pointB.y = rectClientB.top + 5;
//                                  pgraphics->move_to(pointA);
//                                  pgraphics->line_to(pointB);
//
//                                  // Details
//
//                                  pointA.x = rectClientB.left + 1;
//                                  pointA.y = rectClientB.top + 15;
//                                  pointB.x = rectClientB.left + 5;
//                                  pointB.y = rectClientB.top + 15;
//                                  pgraphics->move_to(pointA);
//                                  pgraphics->line_to(pointB);
//               }
//                  break;
//               case e_grip_top_right:
//               {
//                                   pgraphics->set(m_penHilight1);
//
//                                   rectA = rectClient;
//
//                                   rectA.top++;
//                                   rectA.left++;
//                                   rectA.bottom--;
//                                   rectA.right--;
//
//                                   pointA = rectA.top_right();
//                                   pointA.x -= 15;
//                                   pointB = rectA.top_right();
//                                   pgraphics->move_to(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   rectA.top += 2;
//                                   rectA.left += 2;
//                                   rectA.bottom -= 2;
//                                   rectA.right -= 2;
//
//                                   pointB = rectA.top_right();
//                                   pointC = rectA.top_right();
//                                   pointC.y += 13;
//                                   pgraphics->move_to(pointB);
//                                   pgraphics->line_to(pointC);
//
//                                   pgraphics->set(m_penFace1);
//
//                                   // Most external rectangle_i32
//
//                                   rectA = rectClient;
//
//                                   pointA = rectA.top_right();
//                                   pointA.x -= 16;
//                                   pointB = rectA.top_right();
//                                   pgraphics->move_to(pointA);
//                                   pgraphics->line_to(pointB);
//
//
//                                   // Most internal rectangle_i32
//
//                                   rectA.top += 4;
//                                   rectA.left += 4;
//                                   rectA.bottom -= 4;
//                                   rectA.right -= 4;
//
//                                   pointB = rectA.top_right();
//                                   pointC = rectA.top_right();
//                                   pointC.y += 12;
//                                   pgraphics->move_to(pointB);
//                                   pgraphics->line_to(pointC);
//
//                                   // Midle rectangle_i32
//
//                                   rectA = rectClient;
//
//                                   rectA.top += 2;
//                                   rectA.left += 2;
//                                   rectA.bottom -= 2;
//                                   rectA.right -= 2;
//
//                                   pointA = rectA.top_right();
//                                   pointA.x -= 13;
//                                   pointB = rectA.top_right();
//                                   pointC = rectA.top_right();
//                                   pointC.y += 14;
//                                   pgraphics->move_to(pointA);
//                                   pgraphics->line_to(pointB);
//                                   pgraphics->line_to(pointC);
//
//                                   pgraphics->set(m_penShadow1);
//
//                                   rectA = rectClient;
//
//                                   rectA.top++;
//                                   rectA.left++;
//                                   rectA.bottom--;
//                                   rectA.right--;
//
//                                   pointB = rectA.top_right();
//                                   pointC = rectA.top_right();
//                                   pointC.y += 15;
//                                   pgraphics->move_to(pointB);
//                                   pgraphics->line_to(pointC);
//
//                                   rectA.top += 2;
//                                   rectA.left += 2;
//                                   rectA.bottom -= 2;
//                                   rectA.right -= 2;
//
//                                   pointA = rectA.top_right();
//                                   pointA.x -= 12;
//                                   pointB = rectA.top_right();
//                                   pgraphics->move_to(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   pgraphics->set(m_penDkShadow1);
//
//                                   rectA = rectClient;
//
//                                   pointB = rectA.top_right();
//                                   pointC = rectA.top_right();
//                                   pointC.y += 16;
//                                   pgraphics->move_to(pointB);
//                                   pgraphics->line_to(pointC);
//
//                                   rectA.top += 4;
//                                   rectA.left += 4;
//                                   rectA.bottom -= 4;
//                                   rectA.right -= 4;
//
//                                   pointA = rectA.top_right();
//                                   pointA.x -= 11;
//                                   pointB = rectA.top_right();
//                                   pgraphics->move_to(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   pgraphics->set(m_penHilight1);
//
//                                   pointA.x = rectClientB.right - 14;
//                                   pointA.y = rectClientB.top + 1;
//                                   pointB.x = rectClientB.right - 14;
//                                   pointB.y = rectClientB.top + 4;
//                                   pgraphics->move_to(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   pgraphics->set(m_penFace1);
//
//                                   // Details
//
//                                   pointA.x = rectClientB.right - 15;
//                                   pointA.y = rectClientB.top;
//                                   pointB.x = rectClientB.right - 15;
//                                   pointB.y = rectClientB.top + 5;
//                                   pgraphics->move_to(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   pgraphics->set(m_penShadow1);
//
//                                   // Details
//
//                                   pointA.x = rectClientB.right - 3;
//                                   pointA.y = rectClientB.top + 14;
//                                   pointB.x = rectClientB.right - 1;
//                                   pointB.y = rectClientB.top + 14;
//                                   pgraphics->move_to(pointA);
//                                   pgraphics->line_to(pointB);
//
//                                   pgraphics->set(m_penDkShadow1);
//
//                                   // Details
//
//                                   pointA.x = rectClientB.right - 4;
//                                   pointA.y = rectClientB.top + 15;
//                                   pointB.x = rectClientB.right;
//                                   pointB.y = rectClientB.top + 15;
//                                   pgraphics->move_to(pointB);
//                                   pgraphics->line_to(pointA);
//               }
//                  break;
//               case e_grip_bottom_left:
//               {
//
//                                     pgraphics->set(m_penHilight1);
//
//                                     rectA = rectClient;
//
//                                     rectA.left++;
//                                     rectA.bottom--;
//
//                                     // left 1
//                                     pointA = rectA.bottom_left();
//                                     pointA.y -= 16;
//                                     pointB = rectA.bottom_left();
//                                     pgraphics->move_to(pointB);
//                                     pgraphics->line_to(pointA);
//
//                                     rectA = rectClient;
//
//                                     rectA.left += 3;
//                                     rectA.bottom -= 3;
//
//                                     // bottom 2
//                                     pointB = rectA.bottom_left();
//                                     pointC = rectA.bottom_left();
//                                     pointC.x += 12;
//                                     pgraphics->move_to(pointC);
//                                     pgraphics->line_to(pointB);
//
//                                     pgraphics->set(m_penFace1);
//
//                                     // Most external rectangle_i32 0
//
//                                     rectA = rectClient;
//
//                                     pointA = rectA.bottom_left();
//                                     pointA.y -= 15;
//                                     pointB = rectA.bottom_left();
//                                     pgraphics->move_to(pointB);
//                                     pgraphics->line_to(pointA);
//
//                                     // Most internal rectangle_i32 4
//
//                                     rectA.top += 4;
//                                     rectA.left += 4;
//                                     rectA.bottom -= 4;
//                                     rectA.right -= 4;
//
//                                     pointB = rectA.bottom_left();
//                                     pointC = rectA.bottom_left();
//                                     pointC.x += 12;
//                                     pgraphics->move_to(pointB);
//                                     pgraphics->line_to(pointC);
//
//                                     // Midle rectangle_i32 2
//
//                                     rectA = rectClient;
//
//                                     rectA.top += 2;
//                                     rectA.left += 2;
//                                     rectA.bottom -= 2;
//                                     rectA.right -= 2;
//
//                                     pointA = rectA.bottom_left();
//                                     pointA.y -= 13;
//                                     pointB = rectA.bottom_left();
//                                     pointC = rectA.bottom_left();
//                                     pointC.x += 14;
//                                     pgraphics->move_to(pointA);
//                                     pgraphics->line_to(pointB);
//                                     pgraphics->line_to(pointC);
//
//                                     pgraphics->set(m_penShadow1);
//
//                                     rectA = rectClient;
//
//                                     rectA.left += 2;
//                                     rectA.bottom--;
//
//                                     pointB = rectA.bottom_left();
//                                     pointC = rectA.bottom_left();
//                                     pointC.x += 14;
//                                     pgraphics->move_to(pointB);
//                                     pgraphics->line_to(pointC);
//
//                                     rectA = rectClient;
//
//                                     rectA.left += 3;
//                                     rectA.bottom -= 2;
//
//                                     pointA = rectA.bottom_left();
//                                     pointA.y -= 12;
//                                     pointB = rectA.bottom_left();
//                                     pgraphics->move_to(pointA);
//                                     pgraphics->line_to(pointB);
//
//                                     pgraphics->set(m_penDkShadow1);
//
//                                     rectA = rectClient;
//
//                                     pointB = rectA.bottom_left();
//                                     pointB.x++;
//                                     pointC = rectA.bottom_left();
//                                     pointC.x += 16;
//                                     pgraphics->move_to(pointB);
//                                     pgraphics->line_to(pointC);
//
//                                     rectA.left += 4;
//                                     rectA.bottom -= 3;
//
//                                     pointA = rectA.bottom_left();
//                                     pointA.y -= 11;
//                                     pointB = rectA.bottom_left();
//                                     pgraphics->move_to(pointA);
//                                     pgraphics->line_to(pointB);
//
//                                     // Details - top most
//
//                                     pgraphics->set(m_penHilight1);
//
//                                     pointA.x = rectClientB.left + 1;
//                                     pointA.y = rectClientB.bottom - 15;
//                                     pointB.x = rectClientB.left + 4;
//                                     pointB.y = rectClientB.bottom - 15;
//                                     pgraphics->move_to(pointA);
//                                     pgraphics->line_to(pointB);
//
//                                     // Details - top most
//
//                                     pgraphics->set(m_penFace1);
//
//                                     pointA.x = rectClientB.left;
//                                     pointA.y = rectClientB.bottom - 15;
//                                     pointB.x = rectClientB.left + 5;
//                                     pointB.y = rectClientB.bottom - 15;
//                                     pgraphics->move_to(pointA);
//                                     pgraphics->line_to(pointB);
//
//                                     pgraphics->set(m_penShadow1);
//
//                                     // Details - right most
//
//                                     pointA.x = rectClientB.left + 14;
//                                     pointA.y = rectClientB.bottom - 4;
//                                     pointB.x = rectClientB.left + 14;
//                                     pointB.y = rectClientB.bottom - 1;
//                                     pgraphics->move_to(pointB);
//                                     pgraphics->line_to(pointA);
//
//                                     pgraphics->set(m_penDkShadow1);
//
//                                     // Details - right most
//
//                                     pointA.x = rectClientB.left + 15;
//                                     pointA.y = rectClientB.bottom - 4;
//                                     pointB.x = rectClientB.left + 15;
//                                     pointB.y = rectClientB.bottom;
//                                     pgraphics->move_to(pointB);
//                                     pgraphics->line_to(pointA);
//               }
//                  break;
//               case e_grip_bottom_right:
//               {
//                                      pgraphics->set(m_penHilight1);
//
//                                      rectA = rectClient;
//
//                                      rectA.top++;
//                                      rectA.left++;
//                                      rectA.bottom--;
//                                      rectA.right--;
//
//                                      rectA.top += 2;
//                                      rectA.left += 2;
//                                      rectA.bottom -= 2;
//                                      rectA.right -= 2;
//
//                                      pointA = rectA.bottom_right();
//                                      pointA.y -= 12;
//                                      pointB = rectA.bottom_right();
//                                      pointC = rectA.bottom_right();
//                                      pointC.x -= 13;
//                                      pgraphics->move_to(pointA);
//                                      pgraphics->line_to(pointB);
//                                      pgraphics->line_to(pointC);
//
//                                      pgraphics->set(m_penFace1);
//
//                                      rectA = rectClient;
//
//                                      // Most internal rectangle_i32
//
//                                      rectA.top += 4;
//                                      rectA.left += 4;
//                                      rectA.bottom -= 4;
//                                      rectA.right -= 4;
//
//                                      pointA = rectA.bottom_right();
//                                      pointA.y -= 11;
//                                      pointB = rectA.bottom_right();
//                                      pointC = rectA.bottom_right();
//                                      pointC.x -= 12;
//                                      pgraphics->move_to(pointA);
//                                      pgraphics->line_to(pointB);
//                                      pgraphics->line_to(pointC);
//
//                                      // Midle rectangle_i32
//
//                                      rectA = rectClient;
//
//                                      rectA.top += 2;
//                                      rectA.left += 2;
//                                      rectA.bottom -= 2;
//                                      rectA.right -= 2;
//
//                                      pointA = rectA.bottom_right();
//                                      pointA.y -= 13;
//                                      pointB = rectA.bottom_right();
//                                      pointC = rectA.bottom_right();
//                                      pointC.x -= 14;
//                                      pgraphics->move_to(pointA);
//                                      pgraphics->line_to(pointB);
//                                      pgraphics->line_to(pointC);
//                                      pgraphics->set(m_penShadow1);
//
//                                      rectA = rectClient;
//
//                                      rectA.top++;
//                                      rectA.left++;
//                                      rectA.bottom--;
//                                      rectA.right--;
//
//                                      pointA = rectA.bottom_right();
//                                      pointA.y -= 14;
//                                      pointB = rectA.bottom_right();
//                                      pointC = rectA.bottom_right();
//                                      pointC.x -= 15;
//                                      pgraphics->move_to(pointA);
//                                      pgraphics->line_to(pointB);
//                                      pgraphics->line_to(pointC);
//
//                                      pgraphics->set(m_penDkShadow1);
//
//                                      rectA = rectClient;
//
//                                      pointA = rectA.bottom_right();
//                                      pointA.y -= 15;
//                                      pointB = rectA.bottom_right();
//                                      pointC = rectA.bottom_right();
//                                      pointC.x -= 15;
//                                      pgraphics->move_to(pointA);
//                                      pgraphics->line_to(pointB);
//                                      pgraphics->line_to(pointC);
//
//                                      pgraphics->set(m_penHilight1);
//
//                                      pointA.x = rectClientB.right - 3;
//                                      pointA.y = rectClientB.bottom - 14;
//                                      pointB.x = rectClientB.right - 1;
//                                      pointB.y = rectClientB.bottom - 14;
//                                      pgraphics->move_to(pointB);
//                                      pgraphics->line_to(pointA);
//
//                                      pointA.x = rectClientB.right - 14;
//                                      pointA.y = rectClientB.bottom - 3;
//                                      pointB.x = rectClientB.right - 14;
//                                      pointB.y = rectClientB.bottom - 1;
//                                      pgraphics->move_to(pointB);
//                                      pgraphics->line_to(pointA);
//
//                                      pgraphics->set(m_penFace1);
//
//                                      // Details
//
//                                      pointA.x = rectClientB.right - 5;
//                                      pointA.y = rectClientB.bottom - 15;
//                                      pointB.x = rectClientB.right;
//                                      pointB.y = rectClientB.bottom - 15;
//                                      pgraphics->move_to(pointB);
//                                      pgraphics->line_to(pointA);
//
//                                      pointA.x = rectClientB.right - 15;
//                                      pointA.y = rectClientB.bottom - 5;
//                                      pointB.x = rectClientB.right - 15;
//                                      pointB.y = rectClientB.bottom;
//                                      pgraphics->move_to(pointB);
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
//                                    ::rectangle_i32 rectB;
//
//                                    rectB.top = rectC.top;
//                                    rectB.left = pointCenter.x - GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                    rectB.right = pointCenter.x + GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                    rectB.bottom = rectC.top + GRIP_CENTER_SMALL_CY;
//
//                                    DrawRectGrip(pgraphics, rectB);
//               }
//                  break;
//               case e_grip_bottom:
//               {
//                                       ::point_i32 pointCenter = rectangle.center();
//
//                                       ::rectangle_i32 rectB;
//
//                                       int iMod;
//                                       if(rectangle.width() % 2 == 1)
//                                          iMod = 1;
//                                       else
//                                          iMod = 0;
//
//                                       rectB.bottom = rectC.bottom;
//                                       rectB.left = pointCenter.x - GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                       rectB.right = pointCenter.x + GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                       rectB.top = rectC.bottom - GRIP_CENTER_SMALL_CY;
//
//                                       DrawRectGrip(pgraphics, rectB);
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
//                                     ::rectangle_i32 rectB;
//
//                                     rectB.top = pointCenter.y - GRIP_CENTER_LARGE_CY / 2 + iMod;
//                                     rectB.left = rectC.left;
//                                     rectB.right = rectC.left + GRIP_CENTER_SMALL_CX;
//                                     rectB.bottom = pointCenter.y + GRIP_CENTER_LARGE_CY / 2 + iMod;
//
//                                     DrawRectGrip(pgraphics, rectB);
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
//                                      ::rectangle_i32 rectB;
//
//                                      rectB.top = pointCenter.y - GRIP_CENTER_LARGE_CY / 2 + iMod;
//                                      rectB.right = rectC.right;
//                                      rectB.left = rectC.right - GRIP_CENTER_SMALL_CX;
//                                      rectB.bottom = pointCenter.y + GRIP_CENTER_LARGE_CY / 2 + iMod;
//
//                                      DrawRectGrip(pgraphics, rectB);
//               }
//                  break;
//               default:
//                  break;
//               }


            }

            void frame_Minimal001::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectParam)
            {



               ::rectangle_i32 rectangle(rectParam);

               //rectangle.right++;

               //rectangle.bottom++;

               auto psession = get_session();

               auto pframewindow = m_pframewindow;

               auto pstyle = pframewindow->get_style(pgraphics);

               auto crButtonHilite = pframewindow->get_color(pstyle, ::user::e_element_button_hilite);

               auto crButtonDarkShadow = pframewindow->get_color(pstyle, ::user::e_element_button_dark_shadow);

               auto crButtonFace = pframewindow->get_color(pstyle, ::user::e_element_button_background);

               auto crButtonShadow = pframewindow->get_color(pstyle, ::user::e_element_button_shadow);

               pgraphics->draw_3drect(rectangle, opaque(crButtonFace), opaque(crButtonDarkShadow));

               rectangle.deflate(1, 1);

               pgraphics->draw_3drect(rectangle, opaque(crButtonHilite), opaque(crButtonShadow));

               rectangle.deflate(1, 1);

               //rectangle.right--;

               //rectangle.bottom--;

               pgraphics->fill_rectangle(rectangle, opaque(crButtonFace));

            }

            void frame_Minimal001::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient)
            {

               auto psizenager = m_pframewindow->size_manager();

               enum_grip egrip = psizenager->GetGripMask();

               if(egrip & e_grip_top)
               {
                  DrawGrip(pgraphics, rectClient, e_grip_top);
               }
               if(egrip & e_grip_top_right)
               {
                  DrawGrip(pgraphics, rectClient, e_grip_top_right);
               }
               if(egrip & e_grip_right)
               {
                  DrawGrip(pgraphics, rectClient, e_grip_right);
               }
               if(egrip & e_grip_bottom_right)
               {
                  DrawGrip(pgraphics, rectClient, e_grip_bottom_right);
               }
               if(egrip & e_grip_bottom)
               {
                  DrawGrip(pgraphics, rectClient, e_grip_bottom);
               }
               if(egrip & e_grip_bottom_left)
               {
                  DrawGrip(pgraphics, rectClient, e_grip_bottom_left);
               }
               if(egrip & e_grip_left)
               {
                  DrawGrip(pgraphics, rectClient, e_grip_left);
               }
               if(egrip & e_grip_top_left)
               {
                  DrawGrip(pgraphics, rectClient, e_grip_top_left);
               }

            }



   } // namespace core


} // namespace experience



