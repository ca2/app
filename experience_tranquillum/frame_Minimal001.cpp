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


      


         namespace tranquillum
         {


            frame_Minimal001::frame_Minimal001()
            {

               set_style(StyleLightBlue);

               m_rectMarginNormal.set(0,0,0,0);


            }


            frame_Minimal001::~frame_Minimal001()
            {

            }


            e_hittest frame_Minimal001::_001HitTest(const ::point & pointCursor)
            {
               e_hittest etest = hittest_client;
               {
                  //      m_pframewindow->GetEventWindow()->_001ScreenToClient(point);
                  ::rect rectEvent;
                  m_pframewindow->get_window_rect(rectEvent);
                  ::rect rect;
                  ::point pointCenter = rectEvent.center();
                  e_grip egrip = m_pframewindow->size_manager()->GetGripMask();

                  if(egrip & grip_top_left)
                  {
                     rect = rectEvent;
                     rect.right = rect.left + 16;
                     rect.bottom = rect.top + 5;
                     if(rect.contains(pointCursor))
                     {
                        etest = hittest_sizing_top_left;
                        goto SizingSuccess;
                     }
                     rect = rectEvent;
                     rect.right = rect.left + 5;
                     rect.bottom = rect.top + 16;
                     if(rect.contains(pointCursor))
                     {
                        etest = hittest_sizing_top_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_top_right)
                  {
                     rect = rectEvent;
                     rect.left = rect.right - 16;
                     rect.bottom = rect.top + 5;
                     if(rect.contains(pointCursor))
                     {
                        etest = hittest_sizing_top_right;
                        goto SizingSuccess;
                     }
                     rect = rectEvent;
                     rect.left = rect.right - 5;
                     rect.bottom = rect.top + 16;
                     if(rect.contains(pointCursor))
                     {
                        etest = hittest_sizing_top_right;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_bottom_right)
                  {
                     rect = rectEvent;
                     rect.left = rect.right - 16;
                     rect.top = rect.bottom - 5;
                     if(rect.contains(pointCursor))
                     {
                        etest = hittest_sizing_bottom_right;
                        goto SizingSuccess;
                     }
                     rect = rectEvent;
                     rect.left = rect.right - 5;
                     rect.top = rect.bottom - 16;
                     if(rect.contains(pointCursor))
                     {
                        etest = hittest_sizing_bottom_right;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_bottom_left)
                  {
                     rect = rectEvent;
                     rect.right = rect.left + 16;
                     rect.top = rect.bottom - 5;
                     if(rect.contains(pointCursor))
                     {
                        etest = hittest_sizing_bottom_left;
                        goto SizingSuccess;
                     }
                     rect = rectEvent;
                     rect.right = rect.left + 5;
                     rect.top = rect.bottom - 16;
                     if(rect.contains(pointCursor))
                     {
                        etest = hittest_sizing_bottom_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_top)
                  {
                     rect.top = rectEvent.top;
                     rect.left = pointCenter.x - 8;
                     rect.right = pointCenter.x + 8;
                     rect.bottom = rectEvent.top + 5;
                     if(rect.contains(pointCursor))
                     {
                        etest = hittest_sizing_top;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_bottom)
                  {
                     rect.top = rectEvent.bottom - 5;
                     rect.left = pointCenter.x - 8;
                     rect.right = pointCenter.x + 8;
                     rect.bottom = rectEvent.bottom;
                     if(rect.contains(pointCursor))
                     {
                        etest = hittest_sizing_bottom;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_left)
                  {
                     rect.top = pointCenter.y - 8;
                     rect.left = rectEvent.left;
                     rect.right = rectEvent.left + 5;
                     rect.bottom = pointCenter.y + 8;
                     if(rect.contains(pointCursor))
                     {
                        etest = hittest_sizing_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_right)
                  {
                     rect.top = pointCenter.y - 8;
                     rect.left = rectEvent.right - 5;
                     rect.right = rectEvent.right;
                     rect.bottom = pointCenter.y + 8;
                     if(rect.contains(pointCursor))
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





            void frame_Minimal001::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient, e_border eside)
            {

               if (eside != border_top)
               {

                  return;

               }

               auto psession = Session;

               auto pframewindow = m_pframewindow;

               color32_t    crMoveableBorder;

               color32_t    crMoveableBorderHilight;

               color32_t    crMoveableBorderShadow;

               if(pframewindow->is_active())
               {

                  crMoveableBorder = m_crMoveableBorder;

                  crMoveableBorderHilight = m_crMoveableBorderHilight;

                  crMoveableBorderShadow = m_crMoveableBorderShadow;

               }
               else
               {
                  auto psession = Session;

                  auto pstyle = pframewindow->get_style(pgraphics);

                  crMoveableBorder = pframewindow->get_color(pstyle, ::user::element_button_background);

                  crMoveableBorderHilight = pframewindow->get_color(pstyle, ::user::element_button_hilite);

                  crMoveableBorderShadow = pframewindow->get_color(pstyle, ::user::element_button_shadow);

}

//               e_dock edock = m_pframewindow->dock_manager()->GetDockState();

               //::rect rectA(rectClient);


               if(is_translucid_style(m_estyle))
               {

                  ::rect rect;

                  GetBorderRect(rectClient, rect, eside);


                  class imaging & imaging = System.imaging();

                  imaging.color_blend(pgraphics, rect, crMoveableBorder, 127);

               }
               /*else if(m_estyle == StyleLightBlue)
               {

                  ::rect rect;

                  GetBorderRect(rectClient, rect, eside);


                  class imaging & imaging = System.imaging();

                  imaging.color_blend(pgraphics, rect, crMoveableBorder, 127);



                  rectA.deflate(2, 2, 2, 2);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorderHilight, crMoveableBorderShadow);

                  rectA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorder, crMoveableBorder);

                  rectA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorder, crMoveableBorder);


               }*/
               else
               {

                  auto rectClient = m_pframewindow->get_client_rect();


                  rectClient.deflate(2, 2, 2, 2);

                  ::rect rect;

                  GetBorderRect(rectClient, rect, eside);

                  class imaging & imaging = System.imaging();

                  imaging.color_blend(pgraphics, rect, crMoveableBorder, 127);

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

               ::rect rectWindow;

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


            void frame_Minimal001::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient)

            {

               auto pmovemanager = m_pframewindow->move_manager();

               e_border eborder = pmovemanager->GetBorderMask();

               if(m_pframewindow->layout().is_zoomed())
               {
                  eborder = (e_border)
                            (eborder &
                             ~(border_right
                               | border_bottom
                               | border_left));
               }

               if(eborder & border_top)
               {

                  draw_border_side(pgraphics, rectClient, border_top);


               }

               if(eborder & border_right)
               {

                  draw_border_side(pgraphics, rectClient, border_right);


               }

               if(eborder & border_bottom)
               {

                  draw_border_side(pgraphics, rectClient, border_bottom);


               }

               if(eborder & border_left)
               {

                  draw_border_side(pgraphics, rectClient, border_left);


               }

            }

            void frame_Minimal001::GetBorderRect(const ::rect & rectClient, RECT32 * prect, e_border eside)

            {

               ::rect rectBig(rectClient);


               ::rect rectSmall;

               get_window_client_rect(rectSmall);

               ::rect rect;

               if(eside == border_top)
               {
                  rect.left = rectBig.left;
                  rect.right = rectBig.right;
                  rect.top = rectBig.top;
                  rect.bottom = rectSmall.top;
               }
               else if(eside == border_left)
               {
                  rect.left = rectBig.left;
                  rect.right = rectSmall.left;
                  rect.top = rectSmall.top;
                  rect.bottom = rectSmall.bottom;
               }
               else if(eside == border_right)
               {
                  rect.left = rectSmall.right;
                  rect.right = rectBig.right;
                  rect.top = rectSmall.top;
                  rect.bottom = rectSmall.bottom;
               }
               else if(eside == border_bottom)
               {
                  rect.left = rectBig.left;
                  rect.right = rectBig.right;
                  rect.top = rectSmall.bottom;
                  rect.bottom = rectBig.bottom;
               }
               *prect = rect;

            }


            void frame_Minimal001::on_style_change()
            {

               on_style_change_001_and_002();

            }


            void frame_Minimal001::DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient, e_grip egrip)

            {

               return;



//               ::rect rectC(rectClient);

//
//               ::rect rectClient(rectClient);

//
//               rectClient.right--;
//
//               rectClient.bottom--;
//
//               ::rect rectClientB(rectClient);
//
//               ::rect rectA;
//
//               ::point pointA;
//
//               ::point pointB;
//
//               ::point pointC;
//
//               ::rect rect(rectClient);
//
//               switch(egrip)
//               {
//               case grip_top_left:
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
//                                  // Most external rectangle
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
//                                  // Midle Rectangle
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
//               case grip_top_right:
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
//                                   // Most external rectangle
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
//                                   // Most internal rectangle
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
//                                   // Midle Rectangle
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
//               case grip_bottom_left:
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
//                                     // Most external rectangle 0
//
//                                     rectA = rectClient;
//
//                                     pointA = rectA.bottom_left();
//                                     pointA.y -= 15;
//                                     pointB = rectA.bottom_left();
//                                     pgraphics->move_to(pointB);
//                                     pgraphics->line_to(pointA);
//
//                                     // Most internal rectangle 4
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
//                                     // Midle Rectangle 2
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
//               case grip_bottom_right:
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
//                                      // Most internal rectangle
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
//                                      // Midle Rectangle
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
//               case grip_top:
//               {
//                                    ::point pointCenter = rect.center();
//
//                                    int iMod;
//                                    if(rect.width() % 2 == 1)
//                                       iMod = 1;
//                                    else
//                                       iMod = 0;
//
//                                    ::rect rectB;
//
//                                    rectB.top = rectC.top;
//                                    rectB.left = pointCenter.x - GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                    rectB.right = pointCenter.x + GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                    rectB.bottom = rectC.top + GRIP_CENTER_SMALL_CY;
//
//                                    DrawRectGrip(pgraphics, rectB);
//               }
//                  break;
//               case grip_bottom:
//               {
//                                       ::point pointCenter = rect.center();
//
//                                       ::rect rectB;
//
//                                       int iMod;
//                                       if(rect.width() % 2 == 1)
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
//               case grip_left:
//               {
//                                     ::point pointCenter = rect.center();
//
//                                     int iMod;
//                                     if(rect.height() % 2 == 1)
//                                        iMod = 1;
//                                     else
//                                        iMod = 0;
//
//
//                                     ::rect rectB;
//
//                                     rectB.top = pointCenter.y - GRIP_CENTER_LARGE_CY / 2 + iMod;
//                                     rectB.left = rectC.left;
//                                     rectB.right = rectC.left + GRIP_CENTER_SMALL_CX;
//                                     rectB.bottom = pointCenter.y + GRIP_CENTER_LARGE_CY / 2 + iMod;
//
//                                     DrawRectGrip(pgraphics, rectB);
//               }
//                  break;
//               case grip_right:
//               {
//                                      ::point pointCenter = rect.center();
//
//                                      int iMod;
//                                      if(rect.height() % 2 == 1)
//                                         iMod = 1;
//                                      else
//                                         iMod = 0;
//
//
//                                      ::rect rectB;
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
//
//
//            }
//
//            void frame_Minimal001::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const rect & rectParam)
//            {
//
//
//
//               ::rect rect(rectParam);
//
//               //rect.right++;
//
//               //rect.bottom++;
//
//               pgraphics->Draw3dRect(rect, crButtonFace | 0xff000000, crButtonDarkShadow | 0xff000000);
//
//               rect.deflate(1, 1);
//
//               pgraphics->Draw3dRect(rect, crButtonHilite | 0xff000000, crButtonShadow | 0xff000000);
//
//               rect.deflate(1, 1);
//
//               //rect.right--;
//
//               //rect.bottom--;
//
//               pgraphics->FillSolidRect(rect, crButtonFace | 0xff000000);

            }

            void frame_Minimal001::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient)

            {

               size_manager * psizenager = m_pframewindow->size_manager();

               e_grip egrip = psizenager->GetGripMask();

               if(egrip & grip_top)
               {
                  DrawGrip(pgraphics, rectClient, grip_top);

               }
               if(egrip & grip_top_right)
               {
                  DrawGrip(pgraphics, rectClient, grip_top_right);

               }
               if(egrip & grip_right)
               {
                  DrawGrip(pgraphics, rectClient, grip_right);

               }
               if(egrip & grip_bottom_right)
               {
                  DrawGrip(pgraphics, rectClient, grip_bottom_right);

               }
               if(egrip & grip_bottom)
               {
                  DrawGrip(pgraphics, rectClient, grip_bottom);

               }
               if(egrip & grip_bottom_left)
               {
                  DrawGrip(pgraphics, rectClient, grip_bottom_left);

               }
               if(egrip & grip_left)
               {
                  DrawGrip(pgraphics, rectClient, grip_left);

               }
               if(egrip & grip_top_left)
               {
                  DrawGrip(pgraphics, rectClient, grip_top_left);

               }

            }




         } // namespace tranquillum

   } // namespace experience



