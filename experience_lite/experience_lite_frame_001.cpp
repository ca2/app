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


            e_hittest frame_001::_001HitTest(::point pointCursor)
            {
               e_hittest etest = hittest_client;
               {
                  //      m_pframewindow->GetEventWindow()->_001ScreenToClient(point);
                  ::rect rectEvent;
                  m_pframewindow->get_window_rect(rectEvent);
                  ::rect rect;
                  point ptCenter = rectEvent.center();
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
                     rect.left = ptCenter.x - 8;
                     rect.right = ptCenter.x + 8;
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
                     rect.left = ptCenter.x - 8;
                     rect.right = ptCenter.x + 8;
                     rect.bottom = rectEvent.bottom;
                     if(rect.contains(pointCursor))
                     {
                        etest = hittest_sizing_bottom;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_left)
                  {
                     rect.top = ptCenter.y - 8;
                     rect.left = rectEvent.left;
                     rect.right = rectEvent.left + 5;
                     rect.bottom = ptCenter.y + 8;
                     if(rect.contains(pointCursor))
                     {
                        etest = hittest_sizing_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_right)
                  {
                     rect.top = ptCenter.y - 8;
                     rect.left = rectEvent.right - 5;
                     rect.right = rectEvent.right;
                     rect.bottom = ptCenter.y + 8;
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





            void frame_001::draw_border_side(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient, e_border eside)
            {

               auto pframewindow = m_pframewindow;

               COLORREF    crMoveableBorder;

               COLORREF    crMoveableBorderHilight;

               COLORREF    crMoveableBorderShadow;

               if(pframewindow->m_fActive)
               {

                  crMoveableBorder = m_crMoveableBorder;

                  crMoveableBorderHilight = m_crMoveableBorderHilight;

                  crMoveableBorderShadow = m_crMoveableBorderShadow;

               }
               else
               {

                  crMoveableBorder = Session.get_default_color(COLOR_BTNFACE);

                  crMoveableBorderHilight = Session.get_default_color(COLOR_BTNHILIGHT);

                  crMoveableBorderShadow = Session.get_default_color(COLOR_BTNSHADOW);

               }



//               e_dock edock = m_pframewindow->dock_manager()->GetDockState();

               ::rect rectA(lpcrectClient);

               if(is_translucid_style(m_estyle))
               {

                  ::rect rect;

                  GetBorderRect(lpcrectClient, rect, eside);

                  class imaging & imaging = System.imaging();

                  imaging.color_blend(pgraphics, rect, crMoveableBorder, 127);

               }
               /*else if(m_estyle == StyleLightBlue)
               {

                  ::rect rect;

                  GetBorderRect(lpcrectClient, rect, eside);

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

                  ::rect rectClient(lpcrectClient);

                  rectClient.deflate(2, 2, 2, 2);

                  ::rect rect;

                  GetBorderRect(rectClient, rect, eside);

                  class imaging & imaging = System.imaging();

                  imaging.color_blend(pgraphics, rect, crMoveableBorder, 127);

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

               bool bZoomed = pframewindow->window_is_zoomed() != 0;

               string str;

               ::rect rectWindow;

               pframewindow->get_window_rect(rectWindow);

               rectWindow -= rectWindow.top_left();

               if(!pframewindow->window_is_full_screen())
               {

                  DrawBorder(pgraphics, rectWindow);

               }

               if(!bZoomed && !pframewindow->window_is_full_screen())
               {

                  DrawGripSet(pgraphics, rectWindow);

               }

            }


            void frame_001::DrawBorder(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient)
            {



               auto pmovemanager = m_pframewindow->move_manager();

               e_border eborder = pmovemanager->GetBorderMask();

               if(m_pframewindow->window_is_zoomed())
               {
                  eborder = (e_border)
                            (eborder &
                             ~(border_right
                               | border_bottom
                               | border_left));
               }

               if(eborder & border_top)
               {

                  draw_border_side(pgraphics, lpcrectClient, border_top);

               }

               if(eborder & border_right)
               {

                  draw_border_side(pgraphics, lpcrectClient, border_right);

               }

               if(eborder & border_bottom)
               {

                  draw_border_side(pgraphics, lpcrectClient, border_bottom);

               }

               if(eborder & border_left)
               {

                  draw_border_side(pgraphics, lpcrectClient, border_left);

               }

            }

            void frame_001::GetBorderRect(const RECT & lpcrectClient, LPRECT lprect, e_border eside)
            {

               ::rect rectBig(lpcrectClient);

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
               *lprect = rect;
            }


            void frame_001::on_style_change()
            {

               on_style_change_001_and_002();

            }


            void frame_001::DrawGrip(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient, e_grip egrip)
            {

               ::rect rectC(lpcrectClient);

               ::rect rectClient(lpcrectClient);

               rectClient.right--;

               rectClient.bottom--;

               ::rect rectClientB(rectClient);

               ::rect rectA;

               point ptA;

               point ptB;

               point ptC;

               ::rect rect(rectClient);



               switch(egrip)
               {
               case grip_top_left:
               {
                  pgraphics->SelectObject(m_penHilight1);

                  rectA = rectClient;

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

                  // Most external rectangle

                  rectA = rectClient;

                  ptA = rectA.top_left();
                  ptA.y += 15;
                  ptB = rectA.top_left();
                  ptC = rectA.top_left();
                  ptC.x += 16;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  // Midle Rectangle

                  rectA = rectClient;

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

                  rectA = rectClient;

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

                  rectA = rectClient;

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
               case grip_top_right:
               {
                  pgraphics->SelectObject(m_penHilight1);

                  rectA = rectClient;

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

                  // Most external rectangle

                  rectA = rectClient;

                  ptA = rectA.top_right();
                  ptA.x -= 16;
                  ptB = rectA.top_right();
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);


                  // Most internal rectangle

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

                  rectA = rectClient;

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

                  rectA = rectClient;

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

                  rectA = rectClient;

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
               case grip_bottom_left:
               {

                  pgraphics->SelectObject(m_penHilight1);

                  rectA = rectClient;

                  rectA.left++;
                  rectA.bottom--;

                  // left 1
                  ptA = rectA.bottom_left();
                  ptA.y -= 16;
                  ptB = rectA.bottom_left();
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptA);

                  rectA = rectClient;

                  rectA.left += 3;
                  rectA.bottom -= 3;

                  // bottom 2
                  ptB = rectA.bottom_left();
                  ptC = rectA.bottom_left();
                  ptC.x += 12;
                  pgraphics->move_to(ptC);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penFace1);

                  // Most external rectangle 0

                  rectA = rectClient;

                  ptA = rectA.bottom_left();
                  ptA.y -= 15;
                  ptB = rectA.bottom_left();
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptA);

                  // Most internal rectangle 4

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

                  rectA = rectClient;

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

                  rectA = rectClient;

                  rectA.left += 2;
                  rectA.bottom--;

                  ptB = rectA.bottom_left();
                  ptC = rectA.bottom_left();
                  ptC.x += 14;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptC);

                  rectA = rectClient;

                  rectA.left += 3;
                  rectA.bottom -= 2;

                  ptA = rectA.bottom_left();
                  ptA.y -= 12;
                  ptB = rectA.bottom_left();
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penDkShadow1);

                  rectA = rectClient;

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
               case grip_bottom_right:
               {
                  pgraphics->SelectObject(m_penHilight1);

                  rectA = rectClient;

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

                  rectA = rectClient;

                  // Most internal rectangle

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

                  rectA = rectClient;

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

                  rectA = rectClient;

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

                  rectA = rectClient;

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
               case grip_top:
               {
                  point ptCenter = rect.center();

                  int iMod;
                  if(rect.width() % 2 == 1)
                     iMod = 1;
                  else
                     iMod = 0;

                  ::rect rectB;

                  rectB.top = rectC.top;
                  rectB.left = ptCenter.x - GRIP_CENTER_LARGE_CX / 2 + iMod;
                  rectB.right = ptCenter.x + GRIP_CENTER_LARGE_CX / 2 + iMod;
                  rectB.bottom = rectC.top + GRIP_CENTER_SMALL_CY;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               case grip_bottom:
               {
                  point ptCenter = rect.center();

                  ::rect rectB;

                  int iMod;
                  if(rect.width() % 2 == 1)
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
               case grip_left:
               {
                  point ptCenter = rect.center();

                  int iMod;
                  if(rect.height() % 2 == 1)
                     iMod = 1;
                  else
                     iMod = 0;


                  ::rect rectB;

                  rectB.top = ptCenter.y - GRIP_CENTER_LARGE_CY / 2 + iMod;
                  rectB.left = rectC.left;
                  rectB.right = rectC.left + GRIP_CENTER_SMALL_CX;
                  rectB.bottom = ptCenter.y + GRIP_CENTER_LARGE_CY / 2 + iMod;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               case grip_right:
               {
                  point ptCenter = rect.center();

                  int iMod;
                  if(rect.height() % 2 == 1)
                     iMod = 1;
                  else
                     iMod = 0;


                  ::rect rectB;

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

            void frame_001::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const RECT & rectParam)
            {



               ::rect rect(rectParam);

               //rect.right++;

               //rect.bottom++;

               pgraphics->draw3d_rect(rect, Session.get_default_color(COLOR_BTNFACE) | 0xff000000, Session.get_default_color(COLOR_3DDKSHADOW) | 0xff000000);

               rect.deflate(1, 1);

               pgraphics->draw3d_rect(rect, Session.get_default_color(COLOR_BTNHILIGHT) | 0xff000000, Session.get_default_color(COLOR_BTNSHADOW) | 0xff000000);

               rect.deflate(1, 1);

               pgraphics->fill_rect(rect, Session.get_default_color(COLOR_BTNFACE) | 0xff000000);

            }

            void frame_001::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient)
            {
               size_manager * psizenager = m_pframewindow->size_manager();

               e_grip egrip = psizenager->GetGripMask();

               if(egrip & grip_top)
               {
                  DrawGrip(pgraphics, lpcrectClient, grip_top);
               }
               if(egrip & grip_top_right)
               {
                  DrawGrip(pgraphics, lpcrectClient, grip_top_right);
               }
               if(egrip & grip_right)
               {
                  DrawGrip(pgraphics, lpcrectClient, grip_right);
               }
               if(egrip & grip_bottom_right)
               {
                  DrawGrip(pgraphics, lpcrectClient, grip_bottom_right);
               }
               if(egrip & grip_bottom)
               {
                  DrawGrip(pgraphics, lpcrectClient, grip_bottom);
               }
               if(egrip & grip_bottom_left)
               {
                  DrawGrip(pgraphics, lpcrectClient, grip_bottom_left);
               }
               if(egrip & grip_left)
               {
                  DrawGrip(pgraphics, lpcrectClient, grip_left);
               }
               if(egrip & grip_top_left)
               {
                  DrawGrip(pgraphics, lpcrectClient, grip_top_left);
               }

            }


         } // namespace lite



      


   } // namespace experience


















































