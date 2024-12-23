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


color32_t SetAValue(unsigned char a, color32_t color32)
{

   return argb(a, color32_byte_red(color32), color32_byte_green(color32), color32_byte_blue(color32));

}





   namespace experience
   {


      


         namespace lite

         {



            frame_002::frame_002(::particle * pparticle) :
               object(pparticle),
               frame(pparticle)
            {

               set_style(StyleLightGreen);




            }


            frame_002::~frame_002()
            {

            }


            e_hittest frame_002::_001HitTest(::int_point pointCursor)
            {
               e_hittest etest = ::experience::e_frame_client;
               {
                  //      m_pframewindow->GetEventWindow()->screen_to_client()(point);
                  ::int_rectangle rectangleEvent;
                  m_pframewindow->window_rectangle(rectangleEvent);
                  ::int_rectangle rectangle;
                  int_point ptCenter = rectangleEvent.center();
                  enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();

                  if(egrip & e_grip_top_left)
                  {
                     rectangle = rectangleEvent;
                     rectangle.right() = rectangle.left() + 16;
                     rectangle.bottom() = rectangle.top() + 5;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = ::experience::e_frame_sizing_top_left;
                        goto SizingSuccess;
                     }
                     rectangle = rectangleEvent;
                     rectangle.right() = rectangle.left() + 5;
                     rectangle.bottom() = rectangle.top() + 16;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = ::experience::e_frame_sizing_top_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_top_right)
                  {
                     rectangle = rectangleEvent;
                     rectangle.left() = rectangle.right() - 16;
                     rectangle.bottom() = rectangle.top() + 5;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = ::experience::e_frame_sizing_top_right;
                        goto SizingSuccess;
                     }
                     rectangle = rectangleEvent;
                     rectangle.left() = rectangle.right() - 5;
                     rectangle.bottom() = rectangle.top() + 16;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = ::experience::e_frame_sizing_top_right;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_bottom_right)
                  {
                     rectangle = rectangleEvent;
                     rectangle.left() = rectangle.right() - 16;
                     rectangle.top() = rectangle.bottom() - 5;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = ::experience::e_frame_sizing_bottom_right;
                        goto SizingSuccess;
                     }
                     rectangle = rectangleEvent;
                     rectangle.left() = rectangle.right() - 5;
                     rectangle.top() = rectangle.bottom() - 16;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = ::experience::e_frame_sizing_bottom_right;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_bottom_left)
                  {
                     rectangle = rectangleEvent;
                     rectangle.right() = rectangle.left() + 16;
                     rectangle.top() = rectangle.bottom() - 5;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = ::experience::e_frame_sizing_bottom_left;
                        goto SizingSuccess;
                     }
                     rectangle = rectangleEvent;
                     rectangle.right() = rectangle.left() + 5;
                     rectangle.top() = rectangle.bottom() - 16;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = ::experience::e_frame_sizing_bottom_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_top)
                  {
                     rectangle.top() = rectangleEvent.top();
                     rectangle.left() = ptCenter.x() - 8;
                     rectangle.right() = ptCenter.x() + 8;
                     rectangle.bottom() = rectangleEvent.top() + 5;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = ::experience::e_frame_sizing_top;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_bottom)
                  {
                     rectangle.top() = rectangleEvent.bottom() - 5;
                     rectangle.left() = ptCenter.x() - 8;
                     rectangle.right() = ptCenter.x() + 8;
                     rectangle.bottom() = rectangleEvent.bottom();
                     if(rectangle.contains(pointCursor))
                     {
                        etest = ::experience::e_frame_sizing_bottom;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_left)
                  {
                     rectangle.top() = ptCenter.y() - 8;
                     rectangle.left() = rectangleEvent.left();
                     rectangle.right() = rectangleEvent.left() + 5;
                     rectangle.bottom() = ptCenter.y() + 8;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = ::experience::e_frame_sizing_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_right)
                  {
                     rectangle.top() = ptCenter.y() - 8;
                     rectangle.left() = rectangleEvent.right() - 5;
                     rectangle.right() = rectangleEvent.right();
                     rectangle.bottom() = ptCenter.y() + 8;
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




            void frame_002::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle &lpcrectClient, enum_border eside)
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

                  

                  auto pstyle = pframewindow->get_style(pgraphics);

                  crMoveableBorder = pframewindow->get_color(pstyle, ::e_element_button_background);

                  crMoveableBorderHilight = pframewindow->get_color(pstyle, ::e_element_button_hilite);

                  crMoveableBorderShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

}

               enum_dock edock = m_pframewindow->dock_manager()->GetDockState();
               ::int_rectangle rectangleA(lpcrectClient);

               if(m_estyle == StyleTranslucidWarmGray
                     || m_estyle == StyleTranslucidLightBlue
                     || m_estyle == StyleTranslucidLightGreen)
               {
                  ::int_rectangle rectangle;
                  GetBorderRectangle(lpcrectClient, rectangle, eside);

                  pgraphics->color_blend(
                                      rectangle,
                                      crMoveableBorder,
                                      127);
               }
               else if(m_estyle == StyleLightBlue)
               {
                  rectangleA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorder, 0);//m_colorMoveableBorderDkShadow);

                  rectangleA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorderHilight, crMoveableBorderShadow);

                  rectangleA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorder, crMoveableBorder);

                  rectangleA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorder, crMoveableBorder);

                  ::int_rectangle rectangle;
                  GetBorderRectangle(lpcrectClient, rectangle, eside);

                  pgraphics->color_blend(
                                      rectangle,
                                      crMoveableBorder,
                                      127);
               }
               else
               {
                  ::int_rectangle rectangle;
                  ::int_rectangle rectangleX = lpcrectClient;
                  rectangleX.deflate(1, 1);
                  GetBorderRectangle(rectangleX, &rectangle, eside);

                  pgraphics->color_blend(
                                      rectangle,
                                      crMoveableBorder,
                                      200);

                  GetBorderRectangle(lpcrectClient, rectangle, eside);

                  ::int_rectangle rectangleXB = rectangleA;

                  rectangleXB.bottom()--;
                  rectangleXB.right()--;

                  rectangleA.top()++;
                  rectangleA.bottom()--;
                  rectangleA.left()++;
                  rectangleA.right()--;
                  if(edock == e_dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectangleA, eside, SetAValue(255, m_colorDkShadow), SetAValue(255, m_colorDkShadow));
                  }

                  rectangleA.top()++;
                  rectangleA.bottom()--;
                  rectangleA.left()++;
                  rectangleA.right()--;
                  Draw3dRectSide(pgraphics, rectangleA, eside, SetAValue(255, m_colorDkShadow), SetAValue(255, m_colorDkShadow));

                  rectangleA.top()++;
                  rectangleA.bottom()--;
                  rectangleA.left()++;
                  rectangleA.right()--;
                  if(edock == e_dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectangleA, eside, SetAValue(255, m_colorDkShadow), SetAValue(255, m_colorDkShadow));
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
               //::aura::savings & savings = session()->savings();

               auto rectangleX = pframewindow->rectangle();

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


            void frame_002::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle &lpcrectClient)
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

            void frame_002::GetBorderRectangle(
            const ::int_rectangle &lpcrectClient,
            ::int_rectangle * lprect,
            enum_border eside)
            {
               ::int_rectangle rectangleBig(lpcrectClient);
               ::int_rectangle rectangleSmall;
               get_window_client_rectangle(&rectangleSmall);
               ::int_rectangle rectangle;
               if(eside == e_border_top)
               {
                  rectangle.left() = rectangleBig.left();
                  rectangle.right() = rectangleBig.right();
                  rectangle.top() = rectangleBig.top();
                  rectangle.bottom() = rectangleSmall.top();
               }
               else if(eside == e_border_left)
               {
                  rectangle.left() = rectangleBig.left();
                  rectangle.right() = rectangleSmall.left();
                  rectangle.top() = rectangleSmall.top();
                  rectangle.bottom() = rectangleSmall.bottom();
               }
               else if(eside == e_border_right)
               {
                  rectangle.left() = rectangleSmall.right();
                  rectangle.right() = rectangleBig.right();
                  rectangle.top() = rectangleSmall.top();
                  rectangle.bottom() = rectangleSmall.bottom();
               }
               else if(eside == e_border_bottom)
               {
                  rectangle.left() = rectangleBig.left();
                  rectangle.right() = rectangleBig.right();
                  rectangle.top() = rectangleSmall.bottom();
                  rectangle.bottom() = rectangleBig.bottom();
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
            const ::int_rectangle &lpcrectClient,
            enum_grip egrip)
            {
               //            const int size1 = 14;
               //      const int size2 = 15;

               ::int_rectangle rectangleX(lpcrectClient);
               //            ::int_rectangle rectangleXB(rectangleX);
               ::int_rectangle rectangleA;
               int_point ptA;
               int_point ptB;
               int_point ptC;
               ::int_rectangle rectangle(rectangleX);



               switch(egrip)
               {
               case e_grip_top_left:
               {

                  rectangleX.bottom()--;
                  rectangleX.right()--;

                  rectangleA = rectangleX;

                  pgraphics->SelectObject(m_ppenHilight1);

                  ptA = rectangleA.top_left();
                  ptB = ptA;
                  ptB.x() += 16;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);


                  ptA = rectangleA.top_left();
                  ptB = ptA;
                  ptB.y() += 16;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_ppenFace1);

                  ptA = rectangleA.top_left();
                  ptA.x()++;
                  ptA.y()++;
                  ptB = ptA;
                  ptB.x() += 15;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectangleA.top_left();
                  ptA.x() += 2;
                  ptA.y() += 2;
                  ptB = ptA;
                  ptB.x() += 14;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);


                  ptA = rectangleA.top_left();
                  ptA.x()++;
                  ptA.y()++;
                  ptB = ptA;
                  ptB.y() += 15;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectangleA.top_left();
                  ptA.x() += 2;
                  ptA.y() += 2;
                  ptB = ptA;
                  ptB.y() += 14;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_ppenShadow1);

                  ptA = rectangleA.top_left();
                  ptA.x() += 3;
                  ptA.y() += 3;
                  ptB = ptA;
                  ptB.x() += 13;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);


                  ptA = rectangleA.top_left();
                  ptA.x() += 3;
                  ptA.y() += 3;
                  ptB = ptA;
                  ptB.y() += 13;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_ppenDkShadow1);

                  ptA = rectangleA.top_left();
                  ptA.x() += 4;
                  ptA.y() += 4;
                  ptB = ptA;
                  ptB.y() += 12;
                  ptC = ptB;
                  ptC.x() -= 3;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  ptA = rectangleA.top_left();
                  ptA.x() += 4;
                  ptA.y() += 4;
                  ptB = ptA;
                  ptB.x() += 12;
                  ptC = ptB;
                  ptC.y() -= 3;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);
               }
               break;
               case e_grip_top_right:
               {

                  rectangleX.bottom()--;
                  rectangleX.right()--;

                  rectangleA = rectangleX;

                  pgraphics->SelectObject(m_ppenHilight1);

                  ptA = rectangleA.top_right();
                  ptB = ptA;
                  ptB.x() -= 16;
                  ptC = ptB;
                  ptC.y() += 4;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  ptB = rectangleA.top_right();
                  ptB.x() -= 4;
                  ptB.y() += 4;
                  ptC = ptB;
                  ptC.y() += 12;
                  pgraphics->set_current_point(ptB);
                  pgraphics->line_to(ptC);

                  pgraphics->SelectObject(m_ppenFace1);

                  ptA = rectangleA.top_right();
                  ptA.x()--;
                  ptA.y()++;
                  ptB = ptA;
                  ptB.x() -= 14;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectangleA.top_right();
                  ptA.x() -= 2;
                  ptA.y() += 2;
                  ptB = ptA;
                  ptB.x() -= 13;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectangleA.top_right();
                  ptA.x() -= 2;
                  ptA.y() += 2;
                  ptB = ptA;
                  ptB.y() += 13;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectangleA.top_right();
                  ptA.x() -= 3;
                  ptA.y() += 3;
                  ptB = ptA;
                  ptB.y() += 12;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_ppenShadow1);

                  ptA = rectangleA.top_right();
                  ptA.x() -= 3;
                  ptA.y() += 3;
                  ptB = ptA;
                  ptB.x() -= 12;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectangleA.top_right();
                  ptA.x()--;
                  ptA.y()++;
                  ptB = ptA;
                  ptB.y() += 14;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_ppenDkShadow1);

                  ptB = rectangleA.top_right();
                  ptB.x() -= 4;
                  ptB.y() += 4;
                  ptC = ptB;
                  ptC.x() -= 12;
                  pgraphics->set_current_point(ptB);
                  pgraphics->line_to(ptC);


                  ptA = rectangleA.top_right();
                  ptB = ptA;
                  ptB.y() += 16;
                  ptC = ptB;
                  ptC.x() -= 4;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

               }
               break;
               case e_grip_bottom_left:
               {
                  pgraphics->SelectObject(m_ppenHilight1);

                  rectangleX.bottom()--;
                  rectangleX.right()--;

                  rectangleA = rectangleX;


                  ptA = rectangleA.bottom_left();
                  ptB = rectangleA.bottom_left();
                  ptB.y() -= 16;
                  ptC = ptB;
                  ptC.x() += 4;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB); // vertical left hilite
                  pgraphics->line_to(ptC); // horizontal top hilite


                  ptB = rectangleA.bottom_left();
                  ptB.y() -= 4;
                  ptB.x() += 4;
                  ptC = ptB;
                  ptC.x() += 12;
                  pgraphics->set_current_point(ptB);
                  pgraphics->line_to(ptC); // horizontal bottom hillite

                  pgraphics->SelectObject(m_ppenFace1);

                  ptA = rectangleA.bottom_left();
                  ptA.y()--;
                  ptA.x()++;
                  ptB = ptA;
                  ptB.y() -= 14;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectangleA.bottom_left();
                  ptA.y() -= 2;
                  ptA.x() += 2;
                  ptB = ptA;
                  ptB.y() -= 13;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectangleA.bottom_left();
                  ptA.y() -= 2;
                  ptA.x() += 2;
                  ptB = ptA;
                  ptB.x() += 13;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectangleA.bottom_left();
                  ptA.y() -= 3;
                  ptA.x() += 3;
                  ptB = ptA;
                  ptB.x() += 12;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_ppenShadow1);

                  ptA = rectangleA.bottom_left();
                  ptA.y() -= 3;
                  ptA.x() += 3;
                  ptB = ptA;
                  ptB.y() -= 12;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectangleA.bottom_left();
                  ptA.y()--;
                  ptA.x()++;
                  ptB = ptA;
                  ptB.x() += 14;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_ppenDkShadow1);

                  ptB = rectangleA.bottom_left();
                  ptB.y() -= 4;
                  ptB.x() += 4;
                  ptC = ptB;
                  ptC.y() -= 12;
                  pgraphics->set_current_point(ptB);
                  pgraphics->line_to(ptC);

                  ptA = rectangleA.bottom_left();
                  ptB = ptA;
                  ptB.x() += 16;
                  ptC = ptB;
                  ptC.y() -= 4;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

               }
               break;
               case e_grip_bottom_right:
               {
                  rectangleX.bottom()--;
                  rectangleX.right()--;

                  rectangleA = rectangleX;


                  pgraphics->SelectObject(m_ppenDkShadow1);

                  ptA = rectangleA.bottom_right();
                  ptB = ptA;
                  ptB.x() -= 16;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectangleA.bottom_right();
                  ptB = ptA;
                  ptB.y() -= 16;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  pgraphics->SelectObject(m_ppenShadow1);

                  ptA = rectangleA.bottom_right();
                  ptA.y()--;
                  ptA.x()--;
                  ptB = ptA;
                  ptB.x() -= 15;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectangleA.bottom_right();
                  ptA.y()--;
                  ptA.x()--;
                  ptB = ptA;
                  ptB.y() -= 15;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);


                  pgraphics->SelectObject(m_ppenFace1);

                  ptA = rectangleA.bottom_right();
                  ptA.y() -= 3;
                  ptA.x() -= 3;
                  ptB = ptA;
                  ptB.x() -= 13;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectangleA.bottom_right();
                  ptA.y() -= 2;
                  ptA.x() -= 2;
                  ptB = ptA;
                  ptB.x() -= 14;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectangleA.bottom_right();
                  ptA.y() -= 3;
                  ptA.x() -= 3;
                  ptB = ptA;
                  ptB.y() -= 13;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);

                  ptA = rectangleA.bottom_right();
                  ptA.y() -= 2;
                  ptA.x() -= 2;
                  ptB = ptA;
                  ptB.y() -= 14;
                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);


                  pgraphics->SelectObject(m_ppenHilight1);

                  ptA = rectangleA.bottom_right();
                  ptA.x() -= 4;
                  ptA.y() -= 4;
                  ptB = ptA;
                  ptB.x() -= 12;
                  ptC = ptB;
                  ptC.y() += 4;

                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

                  ptA = rectangleA.bottom_right();
                  ptA.x() -= 4;
                  ptA.y() -= 4;
                  ptB = ptA;
                  ptB.y() -= 12;
                  ptC = ptB;
                  ptC.x() += 4;

                  pgraphics->set_current_point(ptA);
                  pgraphics->line_to(ptB);
                  pgraphics->line_to(ptC);

               }
               break;
               case e_grip_top:
               {
                  int_point ptCenter = rectangle.center();

                  ::int_rectangle rectangleB;

                  rectangleB.top() = rectangleX.top();
                  rectangleB.left() = ptCenter.x() - GRIP_CENTER_LARGE_CX / 2;
                  rectangleB.right() = ptCenter.x() + GRIP_CENTER_LARGE_CX / 2;
                  rectangleB.bottom() = rectangleB.top() + GRIP_CENTER_SMALL_CY;

                  DrawRectGrip(pgraphics, rectangleB);
               }
               break;
               case e_grip_bottom:
               {
                  int_point ptCenter = rectangle.center();

                  ::int_rectangle rectangleB;

                  rectangleB.bottom() = rectangleX.bottom();
                  rectangleB.left() = ptCenter.x() - GRIP_CENTER_LARGE_CX / 2;
                  rectangleB.right() = ptCenter.x() + GRIP_CENTER_LARGE_CX / 2;
                  rectangleB.top() = rectangleB.bottom() - GRIP_CENTER_SMALL_CY;

                  DrawRectGrip(pgraphics, rectangleB);
               }
               break;
               case e_grip_left:
               {
                  int_point ptCenter = rectangle.center();

                  ::int_rectangle rectangleB;

                  rectangleB.top() = ptCenter.y() - GRIP_CENTER_LARGE_CY / 2;
                  rectangleB.left() = rectangleX.left();
                  rectangleB.right() = rectangleX.left() + GRIP_CENTER_SMALL_CX;
                  rectangleB.bottom() = ptCenter.y() + GRIP_CENTER_LARGE_CY / 2;

                  DrawRectGrip(pgraphics, rectangleB);
               }
               break;
               case e_grip_right:
               {
                  int_point ptCenter = rectangle.center();

                  ::int_rectangle rectangleB;

                  rectangleB.top() = ptCenter.y() - GRIP_CENTER_LARGE_CY / 2;
                  rectangleB.right() = rectangleX.right();
                  rectangleB.left() = rectangleX.right() - GRIP_CENTER_SMALL_CX;
                  rectangleB.bottom() = ptCenter.y() + GRIP_CENTER_LARGE_CY / 2;

                  DrawRectGrip(pgraphics, rectangleB);
               }
               break;
               default:
                  break;
               }


            }

            void frame_002::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const ::int_rectangle &rectangleParam)
            {



               ::int_rectangle rectangle(rectangleParam);

               pgraphics->draw_inset_3d_rectangle(rectangle, crButtonHilite, crButtonDarkShadow);

               rectangle.top()++;
               rectangle.bottom()--;
               rectangle.left()++;
               rectangle.right()--;

               pgraphics->draw_inset_3d_rectangle(rectangle, crButtonFace, crButtonShadow);

               rectangle.top()++;
               rectangle.bottom()--;
               rectangle.left()++;
               rectangle.right()--;

               pgraphics->fill_rectangle(rectangle, crButtonFace);

            }


            void frame_002::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle &lpcrectClient)
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








































