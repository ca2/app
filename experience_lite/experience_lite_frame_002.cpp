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


color32_t SetAValue(byte a, color32_t cr)
{

   return argb(a, colorref_get_r_value(cr), colorref_get_g_value(cr), colorref_get_b_value(cr));

}





   namespace experience
   {


      


         namespace lite

         {



            frame_002::frame_002(::object * pobject) :
               object(pobject),
               frame(pobject)
            {

               set_style(StyleLightGreen);




            }


            frame_002::~frame_002()
            {

            }


            e_hittest frame_002::_001HitTest(::point_i32 pointCursor)
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




            void frame_002::draw_border_side(::draw2d::graphics_pointer & pgraphics, const RECTANGLE_I32 & lpcrectClient, enum_border eside)
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

               enum_dock edock = m_pframewindow->dock_manager()->GetDockState();
               ::rectangle_i32 rectA(lpcrectClient);

               if(m_estyle == StyleTranslucidWarmGray
                     || m_estyle == StyleTranslucidLightBlue
                     || m_estyle == StyleTranslucidLightGreen)
               {
                  ::rectangle_i32 rectangle;
                  GetBorderRect(lpcrectClient, rectangle, eside);

                  pgraphics->color_blend(
                                      rectangle,
                                      crMoveableBorder,
                                      127);
               }
               else if(m_estyle == StyleLightBlue)
               {
                  rectA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorder, 0);//m_colorMoveableBorderDkShadow);

                  rectA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorderHilight, crMoveableBorderShadow);

                  rectA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorder, crMoveableBorder);

                  rectA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorder, crMoveableBorder);

                  ::rectangle_i32 rectangle;
                  GetBorderRect(lpcrectClient, rectangle, eside);

                  pgraphics->color_blend(
                                      rectangle,
                                      crMoveableBorder,
                                      127);
               }
               else
               {
                  ::rectangle_i32 rectangle;
                  ::rectangle_i32 rectClient = lpcrectClient;
                  rectClient.deflate(1, 1);
                  GetBorderRect(rectClient, rectangle, eside);

                  pgraphics->color_blend(
                                      rectangle,
                                      crMoveableBorder,
                                      200);

                  GetBorderRect(lpcrectClient, rectangle, eside);

                  ::rectangle_i32 rectClientB = rectA;

                  rectClientB.bottom--;
                  rectClientB.right--;

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  if(edock == e_dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectA, eside, SetAValue(255, m_colorDkShadow), SetAValue(255, m_colorDkShadow));
                  }

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  Draw3dRectSide(pgraphics, rectA, eside, SetAValue(255, m_colorDkShadow), SetAValue(255, m_colorDkShadow));

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  if(edock == e_dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectA, eside, SetAValue(255, m_colorDkShadow), SetAValue(255, m_colorDkShadow));
                  }

               }

            }

            void frame_002::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
            {

               auto pframewindow = m_pframewindow;

               if(pframewindow == nullptr)
                  return;

               auto pframewindow = m_pframewindow;

               if(!pframewindow->is_frame_experience_enabled())
                  return;

               auto pframewindow = m_pframewindow;

               bool bZoomed = pframewindow->layout().is_zoomed() != 0;

               //    CVMSApp * pApp = (CVMSApp *) System;
               //::aura::savings & savings = psession->savings();

               auto rectClient = pframewindow->get_client_rect();

               string str;


               ::rectangle_i32 rectNClient;

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


            void frame_002::DrawBorder(::draw2d::graphics_pointer & pgraphics, const RECTANGLE_I32 & lpcrectClient)
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

            void frame_002::GetBorderRect(
            const RECTANGLE_I32 & lpcrectClient,
            RECTANGLE_I32 * lprect,
            enum_border eside)
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


            void frame_002::on_style_change()
            {

               on_style_change_001_and_002(pgraphics);

            }

#define BEVEL_SMALL 2
#define BEVEL_LARGE 5
#define GRIP_SMALL 8
#define GRIP_LARGE 30

            void frame_002::DrawGrip(
            ::draw2d::graphics_pointer & pgraphics,
            const RECTANGLE_I32 & lpcrectClient,
            enum_grip egrip)
            {
               //            const i32 size1 = 14;
               //      const i32 size2 = 15;

               ::rectangle_i32 rectClient(lpcrectClient);
               //            ::rectangle_i32 rectClientB(rectClient);
               ::rectangle_i32 rectA;
               point_i32 ptA;
               point_i32 ptB;
               point_i32 ptC;
               ::rectangle_i32 rectangle(rectClient);



               switch(egrip)
               {
               case e_grip_top_left:
               {

                  rectClient.bottom--;
                  rectClient.right--;

                  rectA = rectClient;

                  pgraphics->SelectObject(m_penHilight1);

                  ptA = rectA.top_left();
                  ptB = ptA;
                  ptB.x += 16;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);


                  ptA = rectA.top_left();
                  ptB = ptA;
                  ptB.y += 16;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penFace1);

                  ptA = rectA.top_left();
                  ptA.x++;
                  ptA.y++;
                  ptB = ptA;
                  ptB.x += 15;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectA.top_left();
                  ptA.x += 2;
                  ptA.y += 2;
                  ptB = ptA;
                  ptB.x += 14;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);


                  ptA = rectA.top_left();
                  ptA.x++;
                  ptA.y++;
                  ptB = ptA;
                  ptB.y += 15;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectA.top_left();
                  ptA.x += 2;
                  ptA.y += 2;
                  ptB = ptA;
                  ptB.y += 14;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penShadow1);

                  ptA = rectA.top_left();
                  ptA.x += 3;
                  ptA.y += 3;
                  ptB = ptA;
                  ptB.x += 13;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);


                  ptA = rectA.top_left();
                  ptA.x += 3;
                  ptA.y += 3;
                  ptB = ptA;
                  ptB.y += 13;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penDkShadow1);

                  ptA = rectA.top_left();
                  ptA.x += 4;
                  ptA.y += 4;
                  ptB = ptA;
                  ptB.y += 12;
                  ptC = ptB;
                  ptC.x -= 3;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  ptA = rectA.top_left();
                  ptA.x += 4;
                  ptA.y += 4;
                  ptB = ptA;
                  ptB.x += 12;
                  ptC = ptB;
                  ptC.y -= 3;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);
               }
               break;
               case e_grip_top_right:
               {

                  rectClient.bottom--;
                  rectClient.right--;

                  rectA = rectClient;

                  pgraphics->SelectObject(m_penHilight1);

                  ptA = rectA.top_right();
                  ptB = ptA;
                  ptB.x -= 16;
                  ptC = ptB;
                  ptC.y += 4;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  ptB = rectA.top_right();
                  ptB.x -= 4;
                  ptB.y += 4;
                  ptC = ptB;
                  ptC.y += 12;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptC);

                  pgraphics->SelectObject(m_penFace1);

                  ptA = rectA.top_right();
                  ptA.x--;
                  ptA.y++;
                  ptB = ptA;
                  ptB.x -= 14;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectA.top_right();
                  ptA.x -= 2;
                  ptA.y += 2;
                  ptB = ptA;
                  ptB.x -= 13;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectA.top_right();
                  ptA.x -= 2;
                  ptA.y += 2;
                  ptB = ptA;
                  ptB.y += 13;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectA.top_right();
                  ptA.x -= 3;
                  ptA.y += 3;
                  ptB = ptA;
                  ptB.y += 12;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penShadow1);

                  ptA = rectA.top_right();
                  ptA.x -= 3;
                  ptA.y += 3;
                  ptB = ptA;
                  ptB.x -= 12;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectA.top_right();
                  ptA.x--;
                  ptA.y++;
                  ptB = ptA;
                  ptB.y += 14;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penDkShadow1);

                  ptB = rectA.top_right();
                  ptB.x -= 4;
                  ptB.y += 4;
                  ptC = ptB;
                  ptC.x -= 12;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptC);


                  ptA = rectA.top_right();
                  ptB = ptA;
                  ptB.y += 16;
                  ptC = ptB;
                  ptC.x -= 4;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

               }
               break;
               case e_grip_bottom_left:
               {
                  pgraphics->SelectObject(m_penHilight1);

                  rectClient.bottom--;
                  rectClient.right--;

                  rectA = rectClient;


                  ptA = rectA.bottom_left();
                  ptB = rectA.bottom_left();
                  ptB.y -= 16;
                  ptC = ptB;
                  ptC.x += 4;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB); // vertical left hilite
                  pgraphics->line_to(ptC); // horizontal top hilite


                  ptB = rectA.bottom_left();
                  ptB.y -= 4;
                  ptB.x += 4;
                  ptC = ptB;
                  ptC.x += 12;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptC); // horizontal bottom hillite

                  pgraphics->SelectObject(m_penFace1);

                  ptA = rectA.bottom_left();
                  ptA.y--;
                  ptA.x++;
                  ptB = ptA;
                  ptB.y -= 14;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectA.bottom_left();
                  ptA.y -= 2;
                  ptA.x += 2;
                  ptB = ptA;
                  ptB.y -= 13;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectA.bottom_left();
                  ptA.y -= 2;
                  ptA.x += 2;
                  ptB = ptA;
                  ptB.x += 13;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectA.bottom_left();
                  ptA.y -= 3;
                  ptA.x += 3;
                  ptB = ptA;
                  ptB.x += 12;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penShadow1);

                  ptA = rectA.bottom_left();
                  ptA.y -= 3;
                  ptA.x += 3;
                  ptB = ptA;
                  ptB.y -= 12;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectA.bottom_left();
                  ptA.y--;
                  ptA.x++;
                  ptB = ptA;
                  ptB.x += 14;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penDkShadow1);

                  ptB = rectA.bottom_left();
                  ptB.y -= 4;
                  ptB.x += 4;
                  ptC = ptB;
                  ptC.y -= 12;
                  pgraphics->move_to(ptB);
                  pgraphics->line_to(ptC);

                  ptA = rectA.bottom_left();
                  ptB = ptA;
                  ptB.x += 16;
                  ptC = ptB;
                  ptC.y -= 4;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

               }
               break;
               case e_grip_bottom_right:
               {
                  rectClient.bottom--;
                  rectClient.right--;

                  rectA = rectClient;


                  pgraphics->SelectObject(m_penDkShadow1);

                  ptA = rectA.bottom_right();
                  ptB = ptA;
                  ptB.x -= 16;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectA.bottom_right();
                  ptB = ptA;
                  ptB.y -= 16;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_penShadow1);

                  ptA = rectA.bottom_right();
                  ptA.y--;
                  ptA.x--;
                  ptB = ptA;
                  ptB.x -= 15;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectA.bottom_right();
                  ptA.y--;
                  ptA.x--;
                  ptB = ptA;
                  ptB.y -= 15;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);


                  pgraphics->SelectObject(m_penFace1);

                  ptA = rectA.bottom_right();
                  ptA.y -= 3;
                  ptA.x -= 3;
                  ptB = ptA;
                  ptB.x -= 13;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectA.bottom_right();
                  ptA.y -= 2;
                  ptA.x -= 2;
                  ptB = ptA;
                  ptB.x -= 14;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectA.bottom_right();
                  ptA.y -= 3;
                  ptA.x -= 3;
                  ptB = ptA;
                  ptB.y -= 13;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectA.bottom_right();
                  ptA.y -= 2;
                  ptA.x -= 2;
                  ptB = ptA;
                  ptB.y -= 14;
                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);


                  pgraphics->SelectObject(m_penHilight1);

                  ptA = rectA.bottom_right();
                  ptA.x -= 4;
                  ptA.y -= 4;
                  ptB = ptA;
                  ptB.x -= 12;
                  ptC = ptB;
                  ptC.y += 4;

                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  ptA = rectA.bottom_right();
                  ptA.x -= 4;
                  ptA.y -= 4;
                  ptB = ptA;
                  ptB.y -= 12;
                  ptC = ptB;
                  ptC.x += 4;

                  pgraphics->move_to(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

               }
               break;
               case e_grip_top:
               {
                  point_i32 ptCenter = rectangle.center();

                  ::rectangle_i32 rectB;

                  rectB.top = rectClient.top;
                  rectB.left = ptCenter.x - GRIP_CENTER_LARGE_CX / 2;
                  rectB.right = ptCenter.x + GRIP_CENTER_LARGE_CX / 2;
                  rectB.bottom = rectB.top + GRIP_CENTER_SMALL_CY;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               case e_grip_bottom:
               {
                  point_i32 ptCenter = rectangle.center();

                  ::rectangle_i32 rectB;

                  rectB.bottom = rectClient.bottom;
                  rectB.left = ptCenter.x - GRIP_CENTER_LARGE_CX / 2;
                  rectB.right = ptCenter.x + GRIP_CENTER_LARGE_CX / 2;
                  rectB.top = rectB.bottom - GRIP_CENTER_SMALL_CY;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               case e_grip_left:
               {
                  point_i32 ptCenter = rectangle.center();

                  ::rectangle_i32 rectB;

                  rectB.top = ptCenter.y - GRIP_CENTER_LARGE_CY / 2;
                  rectB.left = rectClient.left;
                  rectB.right = rectClient.left + GRIP_CENTER_SMALL_CX;
                  rectB.bottom = ptCenter.y + GRIP_CENTER_LARGE_CY / 2;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               case e_grip_right:
               {
                  point_i32 ptCenter = rectangle.center();

                  ::rectangle_i32 rectB;

                  rectB.top = ptCenter.y - GRIP_CENTER_LARGE_CY / 2;
                  rectB.right = rectClient.right;
                  rectB.left = rectClient.right - GRIP_CENTER_SMALL_CX;
                  rectB.bottom = ptCenter.y + GRIP_CENTER_LARGE_CY / 2;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               default:
                  break;
               }


            }

            void frame_002::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const RECTANGLE_I32 & rectParam)
            {



               ::rectangle_i32 rectangle(rectParam);

               pgraphics->draw3d_rect(rectangle, crButtonHilite, crButtonDarkShadow);

               rectangle.top++;
               rectangle.bottom--;
               rectangle.left++;
               rectangle.right--;

               pgraphics->draw3d_rect(rectangle, crButtonFace, crButtonShadow);

               rectangle.top++;
               rectangle.bottom--;
               rectangle.left++;
               rectangle.right--;

               pgraphics->fill_rectangle(rectangle, crButtonFace);

            }


            void frame_002::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const RECTANGLE_I32 & lpcrectClient)
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


            color32_t frame_002::get_border_main_body_color()
            {

               return m_colorMoveableBorder;

            }


         } // namespace lite



      


   } // namespace experience








































