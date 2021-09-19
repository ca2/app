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


color32_t SetAValue(byte a, color32_t color32)
{

   return argb(a, colorref_get_r_value(color32), colorref_get_g_value(color32), colorref_get_b_value(color32));

}





   namespace experience
   {


      


         namespace tranquillum

         {



            frame_002::frame_002()
            {

               //set_style(StyleLightGreen);




            }


            frame_002::~frame_002()
            {

            }


            e_hittest frame_002::_001HitTest(const ::point_i32 & pointCursor)
            {
               e_hittest etest = hittest_client;
               {
                  //      m_pframewindow->GetEventWindow()->screen_to_client(point);
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




            void frame_002::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClientParam, enum_border eside)
            {

               //auto psession = get_session();

               auto rectangleClient(rectClientParam);

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

                  //auto psession = get_session();

                  auto pstyle = pframewindow->get_style(pgraphics);

                  crMoveableBorder = pframewindow->get_color(pstyle, ::e_element_button_background);

                  crMoveableBorderHilight = pframewindow->get_color(pstyle, ::e_element_button_hilite);

                  crMoveableBorderShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

               }

               enum_dock edock = m_pframewindow->dock_manager()->get_dock_mask();
               ::rectangle_i32 rectA(rectClientParam);

               auto estyle = pframewindow->m_estyle;

               if(estyle == ::user::StyleTranslucidWarmGray
                     || estyle == ::user::StyleTranslucidLightBlue
                     || estyle == ::user::StyleTranslucidLightGreen)
               {
                  ::rectangle_i32 rectangle;
                  GetBorderRect(rectangleClient, rectangle, eside);


                  pgraphics->fill_rectangle(
                                      rectangle,
                                      crMoveableBorder &
                                      127_opacity);
               }
               else if(estyle == ::user::StyleLightBlue)
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
                  GetBorderRect(rectangleClient, rectangle, eside);

                  //class imaging & imaging = psystem->imaging();
                  //imaging.color_blend(
                     pgraphics->fill_rectangle(
                                      rectangle,
                                      crMoveableBorder &
                                      127_opacity);
               }
               else
               {
                  ::rectangle_i32 rectangle;
                  ::rectangle_i32 rectangleClient = rectClientParam;

                  rectangleClient.deflate(1, 1);
                  GetBorderRect(rectangleClient, rectangle, eside);
                  //class imaging & imaging = psystem->imaging();
                  //imaging.color_blend(
                  pgraphics->fill_rectangle(
                                      rectangle,
                                      crMoveableBorder &
                                      200_opacity);

                  GetBorderRect(rectangleClient, rectangle, eside);


                  ::rectangle_i32 rectClientB = rectA;

                  rectClientB.bottom--;
                  rectClientB.right--;

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  if(edock == e_dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectA, eside, opaque(m_colorDkShadow), opaque(m_colorDkShadow));
                  }

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  Draw3dRectSide(pgraphics, rectA, eside, opaque(m_colorDkShadow), opaque(m_colorDkShadow));

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  if(edock == e_dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectA, eside, opaque(m_colorDkShadow), opaque(m_colorDkShadow));
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


               ::rectangle_i32 rectangleClient;
               pframewindow->get_client_rect(rectangleClient);

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

            RECTANGLE_I32 * prectangle,

            enum_border eside)
            {
               ::rectangle_i32 rectBig(rectangleClient);

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
               *prectangle = rectangle;

            }


            void frame_002::_on_style_change(::draw2d::graphics_pointer & pgraphics)
            {

               on_style_change_001_and_002(pgraphics);

            }

#define BEVEL_SMALL 2
#define BEVEL_LARGE 5
#define GRIP_SMALL 8
#define GRIP_LARGE 30

            void frame_002::DrawGrip(
            ::draw2d::graphics_pointer & pgraphics,
            const ::rectangle_i32 & rectClientParam,

            enum_grip egrip)
            {
               //            const i32 size1 = 14;
               //      const i32 size2 = 15;

               ::rectangle_i32 rectangleClient(rectClientParam);

               //            ::rectangle_i32 rectClientB(rectangleClient);
               ::rectangle_i32 rectA;
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

                  rectA = rectangleClient;

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
               case e_grip_top_right:
               {

                  rectangleClient.bottom--;
                  rectangleClient.right--;

                  rectA = rectangleClient;

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
               case e_grip_bottom_left:
               {
                  pgraphics->set(m_penHilight1);

                  rectangleClient.bottom--;
                  rectangleClient.right--;

                  rectA = rectangleClient;


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
               case e_grip_bottom_right:
               {
                  rectangleClient.bottom--;
                  rectangleClient.right--;

                  rectA = rectangleClient;


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
               case e_grip_top:
               {
                  ::point_i32 pointCenter = rectangle.center();

                  ::rectangle_i32 rectB;

                  rectB.top = rectangleClient.top;
                  rectB.left = pointCenter.x - GRIP_CENTER_LARGE_CX / 2;
                  rectB.right = pointCenter.x + GRIP_CENTER_LARGE_CX / 2;
                  rectB.bottom = rectB.top + GRIP_CENTER_SMALL_CY;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               case e_grip_bottom:
               {
                  ::point_i32 pointCenter = rectangle.center();

                  ::rectangle_i32 rectB;

                  rectB.bottom = rectangleClient.bottom;
                  rectB.left = pointCenter.x - GRIP_CENTER_LARGE_CX / 2;
                  rectB.right = pointCenter.x + GRIP_CENTER_LARGE_CX / 2;
                  rectB.top = rectB.bottom - GRIP_CENTER_SMALL_CY;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               case e_grip_left:
               {
                  ::point_i32 pointCenter = rectangle.center();

                  ::rectangle_i32 rectB;

                  rectB.top = pointCenter.y - GRIP_CENTER_LARGE_CY / 2;
                  rectB.left = rectangleClient.left;
                  rectB.right = rectangleClient.left + GRIP_CENTER_SMALL_CX;
                  rectB.bottom = pointCenter.y + GRIP_CENTER_LARGE_CY / 2;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               case e_grip_right:
               {
                  ::point_i32 pointCenter = rectangle.center();

                  ::rectangle_i32 rectB;

                  rectB.top = pointCenter.y - GRIP_CENTER_LARGE_CY / 2;
                  rectB.right = rectangleClient.right;
                  rectB.left = rectangleClient.right - GRIP_CENTER_SMALL_CX;
                  rectB.bottom = pointCenter.y + GRIP_CENTER_LARGE_CY / 2;

                  DrawRectGrip(pgraphics, rectB);
               }
               break;
               default:
                  break;
               }


            }

            void frame_002::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const rectangle_i32 & rectParam)
            {

               //auto psession = get_session();

               auto pframewindow = m_pframewindow;

               auto pstyle = pframewindow->get_style(pgraphics);

               auto crButtonHilite = pframewindow->get_color(pstyle, ::e_element_button_hilite);

               auto crButtonDarkShadow = pframewindow->get_color(pstyle, ::e_element_button_dark_shadow);

               auto crButtonFace = pframewindow->get_color(pstyle, ::e_element_button_background);

               auto crButtonShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

               ::rectangle_i32 rectangle(rectParam);

               pgraphics->draw_inset_3drect(rectangle, crButtonHilite, crButtonDarkShadow);

               rectangle.top++;
               rectangle.bottom--;
               rectangle.left++;
               rectangle.right--;

               pgraphics->draw_inset_3drect(rectangle, crButtonFace, crButtonShadow);

               rectangle.top++;
               rectangle.bottom--;
               rectangle.left++;
               rectangle.right--;

               pgraphics->fill_rectangle(rectangle, crButtonFace);

            }

            void frame_002::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient)

            {

               size_manager * psizenager = m_pframewindow->size_manager();

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


         } // namespace tranquillum

   } // namespace experience



