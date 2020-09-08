#include "framework.h"


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


COLORREF SetAValue(BYTE a, COLORREF cr)
{

   return ARGB(a, colorref_get_r_value(cr), colorref_get_g_value(cr), colorref_get_b_value(cr));

}

namespace experience
{


   namespace aura
   {


            frame_002::frame_002()
            {

               m_strStyle = "LightGreen";

               m_rectControlBoxMarginNormal.top = 0;


            }


            frame_002::~frame_002()
            {

            }


            e_hittest frame_002::_001HitTest(const ::point & pointCursor)
            {
               e_hittest etest = hittest_client;
               {
                  //      m_pframewindow->_001ScreenToClient(point);
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




            void frame_002::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClientParam, e_border eside)
            {


               auto rectClient(rectClientParam);


               auto pframewindow = m_pframewindow;

               COLORREF    crMoveableBorder;
               COLORREF    crMoveableBorderHilight;
               COLORREF    crMoveableBorderShadow;

               if(pframewindow->is_active())
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

               e_dock edock = m_pframewindow->dock_manager()->get_dock_mask();
               ::rect rectA(rectClient);

               if(m_estyle == StyleTranslucidWarmGray
                     || m_estyle == StyleTranslucidLightBlue
                     || m_estyle == StyleTranslucidLightGreen)
               {
                  ::rect rect;
                  GetBorderRect(rectClient, rect, eside);
                  class imaging & imaging = System.imaging();
                  imaging.color_blend(pgraphics,
                                      rect,
                                      crMoveableBorder,
                                      127);
               }
               else if(m_estyle == StyleLightBlue)
               {
                  rectA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorder, 0);//m_crMoveableBorderDkShadow);

                  rectA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorderHilight, crMoveableBorderShadow);

                  rectA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorder, crMoveableBorder);

                  rectA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorder, crMoveableBorder);

                  ::rect rect;
                  GetBorderRect(rectClient, rect, eside);
                  class imaging & imaging = System.imaging();
                  imaging.color_blend(pgraphics,
                                      rect,
                                      crMoveableBorder,
                                      127);
               }
               else
               {

                  ::rect rect;

                  rectClient.deflate(1, 1);

                  GetBorderRect(rectClient, rect, eside);

                  class imaging & imaging = System.imaging();

                  imaging.color_blend(pgraphics,
                                      rect,
                                      crMoveableBorder,
                                      200);

                  GetBorderRect(rectClient, rect, eside);

                  ::rect rectClientB = rectA;

                  rectClientB.bottom--;
                  rectClientB.right--;

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  if(edock == dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectA, eside, SetAValue(255, m_crDkShadow), SetAValue(255, m_crDkShadow));
                  }

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  Draw3dRectSide(pgraphics, rectA, eside, SetAValue(255, m_crDkShadow), SetAValue(255, m_crDkShadow));

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  if(edock == dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectA, eside, SetAValue(255, m_crDkShadow), SetAValue(255, m_crDkShadow));
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

               //    CVMSApp * pApp = (CVMSApp *) &System;
               //::aura::savings & savings = Session.savings();

               //auto rectClient = pframewindow->get_client_rect();

               string str;

               ::rect rectNClient;

               pframewindow->get_window_rect(rectNClient);

               rectNClient -= rectNClient.top_left();

               ////////////////////
               //
               // Routine:
               // draw frame border
               //
               ////////////////////


               if(!pframewindow->layout().is_full_screen())
               {
                  DrawBorder(pgraphics, rectNClient);
               }

               ///////////////////////
               //
               // Routine:
               // draw resize grip set
               //
               ///////////////////////

               if(!bZoomed && !pframewindow->layout().is_full_screen())
               {
                  DrawGripSet(pgraphics, rectNClient);
               }

               //          pgraphics->SetBkMode(iOriginalBkMode);
               //            pgraphics->set_text_color(crOriginalTextColor);

            }


            void frame_002::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient)
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

            void frame_002::GetBorderRect(
            const ::rect & rectClient,
            LPRECT lprect,
            e_border eside)
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
               *lprect = rect;
            }


            void frame_002::on_style_change()
            {

               on_style_change_001_and_002();

            }

#define BEVEL_SMALL 2
#define BEVEL_LARGE 5
#define GRIP_SMALL 8
#define GRIP_LARGE 30

            void frame_002::DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClientParam, e_grip egrip)
            {
               //            const i32 size1 = 14;
               //      const i32 size2 = 15;

               ::rect rectClient(rectClientParam);
               //            ::rect rectClientB(rectClient);
               ::rect rectA;
               ::point pointA;
               ::point pointB;
               ::point pointC;
               ::rect rect(rectClient);



               switch(egrip)
               {
               case grip_top_left:
               {

                  rectClient.bottom--;
                  rectClient.right--;

                  rectA = rectClient;

                  pgraphics->set(m_penHilight1);

                  pointA = rectA.top_left();
                  pointB = pointA;
                  pointB.x += 16;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);


                  pointA = rectA.top_left();
                  pointB = pointA;
                  pointB.y += 16;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pgraphics->set(m_penFace1);

                  pointA = rectA.top_left();
                  pointA.x++;
                  pointA.y++;
                  pointB = pointA;
                  pointB.x += 15;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pointA = rectA.top_left();
                  pointA.x += 2;
                  pointA.y += 2;
                  pointB = pointA;
                  pointB.x += 14;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);


                  pointA = rectA.top_left();
                  pointA.x++;
                  pointA.y++;
                  pointB = pointA;
                  pointB.y += 15;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pointA = rectA.top_left();
                  pointA.x += 2;
                  pointA.y += 2;
                  pointB = pointA;
                  pointB.y += 14;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pgraphics->set(m_penShadow1);

                  pointA = rectA.top_left();
                  pointA.x += 3;
                  pointA.y += 3;
                  pointB = pointA;
                  pointB.x += 13;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);


                  pointA = rectA.top_left();
                  pointA.x += 3;
                  pointA.y += 3;
                  pointB = pointA;
                  pointB.y += 13;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pgraphics->set(m_penDkShadow1);

                  pointA = rectA.top_left();
                  pointA.x += 4;
                  pointA.y += 4;
                  pointB = pointA;
                  pointB.y += 12;
                  pointC = pointB;
                  pointC.x -= 3;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);
                  pgraphics->line_to(pointC);

                  pointA = rectA.top_left();
                  pointA.x += 4;
                  pointA.y += 4;
                  pointB = pointA;
                  pointB.x += 12;
                  pointC = pointB;
                  pointC.y -= 3;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);
                  pgraphics->line_to(pointC);
               }
               break;
               case grip_top_right:
               {

                  rectClient.bottom--;
                  rectClient.right--;

                  rectA = rectClient;

                  pgraphics->set(m_penHilight1);

                  pointA = rectA.top_right();
                  pointB = pointA;
                  pointB.x -= 16;
                  pointC = pointB;
                  pointC.y += 4;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);
                  pgraphics->line_to(pointC);

                  pointB = rectA.top_right();
                  pointB.x -= 4;
                  pointB.y += 4;
                  pointC = pointB;
                  pointC.y += 12;
                  pgraphics->move_to(pointB);
                  pgraphics->line_to(pointC);

                  pgraphics->set(m_penFace1);

                  pointA = rectA.top_right();
                  pointA.x--;
                  pointA.y++;
                  pointB = pointA;
                  pointB.x -= 14;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pointA = rectA.top_right();
                  pointA.x -= 2;
                  pointA.y += 2;
                  pointB = pointA;
                  pointB.x -= 13;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pointA = rectA.top_right();
                  pointA.x -= 2;
                  pointA.y += 2;
                  pointB = pointA;
                  pointB.y += 13;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pointA = rectA.top_right();
                  pointA.x -= 3;
                  pointA.y += 3;
                  pointB = pointA;
                  pointB.y += 12;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pgraphics->set(m_penShadow1);

                  pointA = rectA.top_right();
                  pointA.x -= 3;
                  pointA.y += 3;
                  pointB = pointA;
                  pointB.x -= 12;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pointA = rectA.top_right();
                  pointA.x--;
                  pointA.y++;
                  pointB = pointA;
                  pointB.y += 14;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pgraphics->set(m_penDkShadow1);

                  pointB = rectA.top_right();
                  pointB.x -= 4;
                  pointB.y += 4;
                  pointC = pointB;
                  pointC.x -= 12;
                  pgraphics->move_to(pointB);
                  pgraphics->line_to(pointC);


                  pointA = rectA.top_right();
                  pointB = pointA;
                  pointB.y += 16;
                  pointC = pointB;
                  pointC.x -= 4;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);
                  pgraphics->line_to(pointC);

               }
               break;
               case grip_bottom_left:
               {
                  pgraphics->set(m_penHilight1);

                  rectClient.bottom--;
                  rectClient.right--;

                  rectA = rectClient;


                  pointA = rectA.bottom_left();
                  pointB = rectA.bottom_left();
                  pointB.y -= 16;
                  pointC = pointB;
                  pointC.x += 4;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB); // vertical left hilite
                  pgraphics->line_to(pointC); // horizontal top hilite


                  pointB = rectA.bottom_left();
                  pointB.y -= 4;
                  pointB.x += 4;
                  pointC = pointB;
                  pointC.x += 12;
                  pgraphics->move_to(pointB);
                  pgraphics->line_to(pointC); // horizontal bottom hillite

                  pgraphics->set(m_penFace1);

                  pointA = rectA.bottom_left();
                  pointA.y--;
                  pointA.x++;
                  pointB = pointA;
                  pointB.y -= 14;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pointA = rectA.bottom_left();
                  pointA.y -= 2;
                  pointA.x += 2;
                  pointB = pointA;
                  pointB.y -= 13;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pointA = rectA.bottom_left();
                  pointA.y -= 2;
                  pointA.x += 2;
                  pointB = pointA;
                  pointB.x += 13;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pointA = rectA.bottom_left();
                  pointA.y -= 3;
                  pointA.x += 3;
                  pointB = pointA;
                  pointB.x += 12;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pgraphics->set(m_penShadow1);

                  pointA = rectA.bottom_left();
                  pointA.y -= 3;
                  pointA.x += 3;
                  pointB = pointA;
                  pointB.y -= 12;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pointA = rectA.bottom_left();
                  pointA.y--;
                  pointA.x++;
                  pointB = pointA;
                  pointB.x += 14;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pgraphics->set(m_penDkShadow1);

                  pointB = rectA.bottom_left();
                  pointB.y -= 4;
                  pointB.x += 4;
                  pointC = pointB;
                  pointC.y -= 12;
                  pgraphics->move_to(pointB);
                  pgraphics->line_to(pointC);

                  pointA = rectA.bottom_left();
                  pointB = pointA;
                  pointB.x += 16;
                  pointC = pointB;
                  pointC.y -= 4;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);
                  pgraphics->line_to(pointC);

               }
               break;
               case grip_bottom_right:
               {
                  rectClient.bottom--;
                  rectClient.right--;

                  rectA = rectClient;


                  pgraphics->set(m_penDkShadow1);

                  pointA = rectA.bottom_right();
                  pointB = pointA;
                  pointB.x -= 16;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pointA = rectA.bottom_right();
                  pointB = pointA;
                  pointB.y -= 16;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pgraphics->set(m_penShadow1);

                  pointA = rectA.bottom_right();
                  pointA.y--;
                  pointA.x--;
                  pointB = pointA;
                  pointB.x -= 15;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pointA = rectA.bottom_right();
                  pointA.y--;
                  pointA.x--;
                  pointB = pointA;
                  pointB.y -= 15;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);


                  pgraphics->set(m_penFace1);

                  pointA = rectA.bottom_right();
                  pointA.y -= 3;
                  pointA.x -= 3;
                  pointB = pointA;
                  pointB.x -= 13;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pointA = rectA.bottom_right();
                  pointA.y -= 2;
                  pointA.x -= 2;
                  pointB = pointA;
                  pointB.x -= 14;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pointA = rectA.bottom_right();
                  pointA.y -= 3;
                  pointA.x -= 3;
                  pointB = pointA;
                  pointB.y -= 13;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);

                  pointA = rectA.bottom_right();
                  pointA.y -= 2;
                  pointA.x -= 2;
                  pointB = pointA;
                  pointB.y -= 14;
                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);


                  pgraphics->set(m_penHilight1);

                  pointA = rectA.bottom_right();
                  pointA.x -= 4;
                  pointA.y -= 4;
                  pointB = pointA;
                  pointB.x -= 12;
                  pointC = pointB;
                  pointC.y += 4;

                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);
                  pgraphics->line_to(pointC);

                  pointA = rectA.bottom_right();
                  pointA.x -= 4;
                  pointA.y -= 4;
                  pointB = pointA;
                  pointB.y -= 12;
                  pointC = pointB;
                  pointC.x += 4;

                  pgraphics->move_to(pointA);
                  pgraphics->line_to(pointB);
                  pgraphics->line_to(pointC);

               }
               break;
               case grip_top:
               {
                  ::point pointCenter = rect.center();

                  ::rect rectB;

                  rectB.top = rectClient.top;
                  rectB.left = pointCenter.x - GRIP_CENTER_LARGE_CX / 2;
                  rectB.right = pointCenter.x + GRIP_CENTER_LARGE_CX / 2;
                  rectB.bottom = rectB.top + GRIP_CENTER_SMALL_CY;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               case grip_bottom:
               {
                  ::point pointCenter = rect.center();

                  ::rect rectB;

                  rectB.bottom = rectClient.bottom;
                  rectB.left = pointCenter.x - GRIP_CENTER_LARGE_CX / 2;
                  rectB.right = pointCenter.x + GRIP_CENTER_LARGE_CX / 2;
                  rectB.top = rectB.bottom - GRIP_CENTER_SMALL_CY;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               case grip_left:
               {
                  ::point pointCenter = rect.center();

                  ::rect rectB;

                  rectB.top = pointCenter.y - GRIP_CENTER_LARGE_CY / 2;
                  rectB.left = rectClient.left;
                  rectB.right = rectClient.left + GRIP_CENTER_SMALL_CX;
                  rectB.bottom = pointCenter.y + GRIP_CENTER_LARGE_CY / 2;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               case grip_right:
               {
                  ::point pointCenter = rect.center();

                  ::rect rectB;

                  rectB.top = pointCenter.y - GRIP_CENTER_LARGE_CY / 2;
                  rectB.right = rectClient.right;
                  rectB.left = rectClient.right - GRIP_CENTER_SMALL_CX;
                  rectB.bottom = pointCenter.y + GRIP_CENTER_LARGE_CY / 2;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               default:
                  break;
               }


            }

            void frame_002::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const ::rect & rectParam)
            {



               ::rect rect(rectParam);

               pgraphics->draw_3drect(rect, Session.get_default_color(COLOR_BTNHILIGHT), Session.get_default_color(COLOR_3DDKSHADOW));

               rect.top++;
               rect.bottom--;
               rect.left++;
               rect.right--;

               pgraphics->draw_3drect(rect, Session.get_default_color(COLOR_BTNFACE), Session.get_default_color(COLOR_BTNSHADOW));

               rect.top++;
               rect.bottom--;
               rect.left++;
               rect.right--;

               pgraphics->fill_rect(rect, Session.get_default_color(COLOR_BTNFACE));

            }

            void frame_002::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient)
            {

               auto psizenager = m_pframewindow->size_manager();

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


            COLORREF frame_002::get_border_main_body_color()
            {

               return m_crMoveableBorder;

            }



   } // namespace aura


} // namespace experience



