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


      


         namespace lite

         {


            frame_Minimal001::frame_Minimal001(::particle * pparticle) :
               object(pparticle),
               frame(pparticle)
            {

               set_style(StyleLightBlue);

               m_rectangleMarginNormal.set(0,0,0,0);


            }


            frame_Minimal001::~frame_Minimal001()
            {

            }


            e_hittest frame_Minimal001::_001HitTest(::int_point pointCursor)
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





            void frame_Minimal001::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle &lpcrectClient, enum_border eside)
            {

               if(eside != e_border_top)
                  return;

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

//               enum_dock edock = m_pframewindow->dock_manager()->GetDockState();

               ::int_rectangle rectangleA(lpcrectClient);

               if(is_translucid_style(m_estyle))
               {

                  ::int_rectangle rectangle;

                  GetBorderRectangle(lpcrectClient, rectangle, eside);



                  pgraphics->color_blend( rectangle, crMoveableBorder, 127);

               }
               /*else if(m_estyle == StyleLightBlue)
               {

                  ::int_rectangle rectangle;

                  GetBorderRectangle(lpcrectClient, rectangle, eside);



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

                  ::int_rectangle rectangleX(lpcrectClient);

                  rectangleX.deflate(2, 2, 2, 2);

                  ::int_rectangle rectangle;

                  GetBorderRectangle(rectangleX, &rectangle, eside);



                  pgraphics->color_blend( rectangle, crMoveableBorder, 127);

               }

            }


            void frame_Minimal001::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
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

               ::int_rectangle rectangleWindow;

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


            void frame_Minimal001::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle &lpcrectClient)
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

            void frame_Minimal001::GetBorderRectangle(const ::int_rectangle &lpcrectClient, ::int_rectangle * lprect, enum_border eside)
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


            void frame_Minimal001::on_style_change()
            {

               on_style_change_001_and_002(pgraphics);

            }


            void frame_Minimal001::DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle &lpcrectClient, enum_grip egrip)
            {

               return;

               

//               ::int_rectangle rectangleC(lpcrectClient);
//
//               ::int_rectangle rectangleX(lpcrectClient);
//
//               rectangleX.right()--;
//
//               rectangleX.bottom()--;
//
//               ::int_rectangle rectangleXB(rectangleX);
//
//               ::int_rectangle rectangleA;
//
//               int_point ptA;
//
//               int_point ptB;
//
//               int_point ptC;
//
//               ::int_rectangle rectangle(rectangleX);
//
//               switch(egrip)
//               {
//               case e_grip_top_left:
//               {
//                                  pgraphics->SelectObject(m_ppenHilight1);
//
//                                  rectangleA = rectangleX;
//
//                                  rectangleA.top()++;
//                                  rectangleA.left()++;
//                                  rectangleA.bottom()--;
//                                  rectangleA.right()--;
//
//                                  ptA = rectangleA.top_left();
//                                  ptA.y() += 14;
//                                  ptB = rectangleA.top_left();
//                                  ptC = rectangleA.top_left();
//                                  ptC.x() += 15;
//
//                                  pgraphics->MoveTo(ptA);
//                                  pgraphics->LineTo(ptB);
//                                  pgraphics->LineTo(ptC);
//
//                                  pgraphics->SelectObject(m_ppenFace1);
//
//                                  // Most external int_rectangle
//
//                                  rectangleA = rectangleX;
//
//                                  ptA = rectangleA.top_left();
//                                  ptA.y() += 15;
//                                  ptB = rectangleA.top_left();
//                                  ptC = rectangleA.top_left();
//                                  ptC.x() += 16;
//                                  pgraphics->MoveTo(ptA);
//                                  pgraphics->LineTo(ptB);
//                                  pgraphics->LineTo(ptC);
//
//                                  // Midle Rectangle
//
//                                  rectangleA = rectangleX;
//
//                                  rectangleA.top() += 2;
//                                  rectangleA.left() += 2;
//                                  rectangleA.bottom() -= 2;
//                                  rectangleA.right() -= 2;
//
//                                  ptA = rectangleA.top_left();
//                                  ptA.y() += 13;
//                                  ptB = rectangleA.top_left();
//                                  ptC = rectangleA.top_left();
//                                  ptC.x() += 14;
//                                  pgraphics->MoveTo(ptA);
//                                  pgraphics->LineTo(ptB);
//                                  pgraphics->LineTo(ptC);
//
//                                  pgraphics->SelectObject(m_ppenShadow1);
//
//                                  rectangleA = rectangleX;
//
//                                  rectangleA.top()++;
//                                  rectangleA.left()++;
//                                  rectangleA.bottom()--;
//                                  rectangleA.right()--;
//
//                                  rectangleA.top() += 2;
//                                  rectangleA.left() += 2;
//                                  rectangleA.bottom() -= 2;
//                                  rectangleA.right() -= 2;
//
//
//                                  ptA = rectangleA.top_left();
//                                  ptA.y() += 12;
//                                  ptB = rectangleA.top_left();
//                                  ptC = rectangleA.top_left();
//                                  ptC.x() += 13;
//                                  pgraphics->MoveTo(ptA);
//                                  pgraphics->LineTo(ptB);
//                                  pgraphics->LineTo(ptC);
//
//                                  pgraphics->SelectObject(m_ppenDkShadow1);
//
//                                  rectangleA = rectangleX;
//
//                                  rectangleA.top() += 4;
//                                  rectangleA.left() += 4;
//                                  rectangleA.bottom() -= 4;
//                                  rectangleA.right() -= 4;
//
//                                  ptA = rectangleA.top_left();
//                                  ptA.y() += 11;
//                                  ptB = rectangleA.top_left();
//                                  ptC = rectangleA.top_left();
//                                  ptC.x() += 12;
//                                  pgraphics->MoveTo(ptA);
//                                  pgraphics->LineTo(ptB);
//                                  pgraphics->LineTo(ptC);
//
//                                  pgraphics->SelectObject(m_ppenShadow1);
//
//                                  // Details
//
//                                  ptA.x() = rectangleXB.left() + 14;
//                                  ptA.y() = rectangleXB.top() + 1;
//                                  ptB.x() = rectangleXB.left() + 14;
//                                  ptB.y() = rectangleXB.top() + 3;
//                                  pgraphics->MoveTo(ptA);
//                                  pgraphics->LineTo(ptB);
//
//
//                                  // Details
//
//                                  ptA.x() = rectangleXB.left() + 1;
//                                  ptA.y() = rectangleXB.top() + 14;
//                                  ptB.x() = rectangleXB.left() + 3;
//                                  ptB.y() = rectangleXB.top() + 14;
//                                  pgraphics->MoveTo(ptA);
//                                  pgraphics->LineTo(ptB);
//
//                                  pgraphics->SelectObject(m_ppenDkShadow1);
//
//                                  // Details
//
//                                  ptA.x() = rectangleXB.left() + 15;
//                                  ptA.y() = rectangleXB.top() + 1;
//                                  ptB.x() = rectangleXB.left() + 15;
//                                  ptB.y() = rectangleXB.top() + 5;
//                                  pgraphics->MoveTo(ptA);
//                                  pgraphics->LineTo(ptB);
//
//                                  // Details
//
//                                  ptA.x() = rectangleXB.left() + 1;
//                                  ptA.y() = rectangleXB.top() + 15;
//                                  ptB.x() = rectangleXB.left() + 5;
//                                  ptB.y() = rectangleXB.top() + 15;
//                                  pgraphics->MoveTo(ptA);
//                                  pgraphics->LineTo(ptB);
//               }
//                  break;
//               case e_grip_top_right:
//               {
//                                   pgraphics->SelectObject(m_ppenHilight1);
//
//                                   rectangleA = rectangleX;
//
//                                   rectangleA.top()++;
//                                   rectangleA.left()++;
//                                   rectangleA.bottom()--;
//                                   rectangleA.right()--;
//
//                                   ptA = rectangleA.top_right();
//                                   ptA.x() -= 15;
//                                   ptB = rectangleA.top_right();
//                                   pgraphics->MoveTo(ptA);
//                                   pgraphics->LineTo(ptB);
//
//                                   rectangleA.top() += 2;
//                                   rectangleA.left() += 2;
//                                   rectangleA.bottom() -= 2;
//                                   rectangleA.right() -= 2;
//
//                                   ptB = rectangleA.top_right();
//                                   ptC = rectangleA.top_right();
//                                   ptC.y() += 13;
//                                   pgraphics->MoveTo(ptB);
//                                   pgraphics->LineTo(ptC);
//
//                                   pgraphics->SelectObject(m_ppenFace1);
//
//                                   // Most external int_rectangle
//
//                                   rectangleA = rectangleX;
//
//                                   ptA = rectangleA.top_right();
//                                   ptA.x() -= 16;
//                                   ptB = rectangleA.top_right();
//                                   pgraphics->MoveTo(ptA);
//                                   pgraphics->LineTo(ptB);
//
//
//                                   // Most internal int_rectangle
//
//                                   rectangleA.top() += 4;
//                                   rectangleA.left() += 4;
//                                   rectangleA.bottom() -= 4;
//                                   rectangleA.right() -= 4;
//
//                                   ptB = rectangleA.top_right();
//                                   ptC = rectangleA.top_right();
//                                   ptC.y() += 12;
//                                   pgraphics->MoveTo(ptB);
//                                   pgraphics->LineTo(ptC);
//
//                                   // Midle Rectangle
//
//                                   rectangleA = rectangleX;
//
//                                   rectangleA.top() += 2;
//                                   rectangleA.left() += 2;
//                                   rectangleA.bottom() -= 2;
//                                   rectangleA.right() -= 2;
//
//                                   ptA = rectangleA.top_right();
//                                   ptA.x() -= 13;
//                                   ptB = rectangleA.top_right();
//                                   ptC = rectangleA.top_right();
//                                   ptC.y() += 14;
//                                   pgraphics->MoveTo(ptA);
//                                   pgraphics->LineTo(ptB);
//                                   pgraphics->LineTo(ptC);
//
//                                   pgraphics->SelectObject(m_ppenShadow1);
//
//                                   rectangleA = rectangleX;
//
//                                   rectangleA.top()++;
//                                   rectangleA.left()++;
//                                   rectangleA.bottom()--;
//                                   rectangleA.right()--;
//
//                                   ptB = rectangleA.top_right();
//                                   ptC = rectangleA.top_right();
//                                   ptC.y() += 15;
//                                   pgraphics->MoveTo(ptB);
//                                   pgraphics->LineTo(ptC);
//
//                                   rectangleA.top() += 2;
//                                   rectangleA.left() += 2;
//                                   rectangleA.bottom() -= 2;
//                                   rectangleA.right() -= 2;
//
//                                   ptA = rectangleA.top_right();
//                                   ptA.x() -= 12;
//                                   ptB = rectangleA.top_right();
//                                   pgraphics->MoveTo(ptA);
//                                   pgraphics->LineTo(ptB);
//
//                                   pgraphics->SelectObject(m_ppenDkShadow1);
//
//                                   rectangleA = rectangleX;
//
//                                   ptB = rectangleA.top_right();
//                                   ptC = rectangleA.top_right();
//                                   ptC.y() += 16;
//                                   pgraphics->MoveTo(ptB);
//                                   pgraphics->LineTo(ptC);
//
//                                   rectangleA.top() += 4;
//                                   rectangleA.left() += 4;
//                                   rectangleA.bottom() -= 4;
//                                   rectangleA.right() -= 4;
//
//                                   ptA = rectangleA.top_right();
//                                   ptA.x() -= 11;
//                                   ptB = rectangleA.top_right();
//                                   pgraphics->MoveTo(ptA);
//                                   pgraphics->LineTo(ptB);
//
//                                   pgraphics->SelectObject(m_ppenHilight1);
//
//                                   ptA.x() = rectangleXB.right() - 14;
//                                   ptA.y() = rectangleXB.top() + 1;
//                                   ptB.x() = rectangleXB.right() - 14;
//                                   ptB.y() = rectangleXB.top() + 4;
//                                   pgraphics->MoveTo(ptA);
//                                   pgraphics->LineTo(ptB);
//
//                                   pgraphics->SelectObject(m_ppenFace1);
//
//                                   // Details
//
//                                   ptA.x() = rectangleXB.right() - 15;
//                                   ptA.y() = rectangleXB.top();
//                                   ptB.x() = rectangleXB.right() - 15;
//                                   ptB.y() = rectangleXB.top() + 5;
//                                   pgraphics->MoveTo(ptA);
//                                   pgraphics->LineTo(ptB);
//
//                                   pgraphics->SelectObject(m_ppenShadow1);
//
//                                   // Details
//
//                                   ptA.x() = rectangleXB.right() - 3;
//                                   ptA.y() = rectangleXB.top() + 14;
//                                   ptB.x() = rectangleXB.right() - 1;
//                                   ptB.y() = rectangleXB.top() + 14;
//                                   pgraphics->MoveTo(ptA);
//                                   pgraphics->LineTo(ptB);
//
//                                   pgraphics->SelectObject(m_ppenDkShadow1);
//
//                                   // Details
//
//                                   ptA.x() = rectangleXB.right() - 4;
//                                   ptA.y() = rectangleXB.top() + 15;
//                                   ptB.x() = rectangleXB.right();
//                                   ptB.y() = rectangleXB.top() + 15;
//                                   pgraphics->MoveTo(ptB);
//                                   pgraphics->LineTo(ptA);
//               }
//                  break;
//               case e_grip_bottom_left:
//               {
//
//                                     pgraphics->SelectObject(m_ppenHilight1);
//
//                                     rectangleA = rectangleX;
//
//                                     rectangleA.left()++;
//                                     rectangleA.bottom()--;
//
//                                     // left 1
//                                     ptA = rectangleA.bottom_left();
//                                     ptA.y() -= 16;
//                                     ptB = rectangleA.bottom_left();
//                                     pgraphics->MoveTo(ptB);
//                                     pgraphics->LineTo(ptA);
//
//                                     rectangleA = rectangleX;
//
//                                     rectangleA.left() += 3;
//                                     rectangleA.bottom() -= 3;
//
//                                     // bottom 2
//                                     ptB = rectangleA.bottom_left();
//                                     ptC = rectangleA.bottom_left();
//                                     ptC.x() += 12;
//                                     pgraphics->MoveTo(ptC);
//                                     pgraphics->LineTo(ptB);
//
//                                     pgraphics->SelectObject(m_ppenFace1);
//
//                                     // Most external int_rectangle 0
//
//                                     rectangleA = rectangleX;
//
//                                     ptA = rectangleA.bottom_left();
//                                     ptA.y() -= 15;
//                                     ptB = rectangleA.bottom_left();
//                                     pgraphics->MoveTo(ptB);
//                                     pgraphics->LineTo(ptA);
//
//                                     // Most internal int_rectangle 4
//
//                                     rectangleA.top() += 4;
//                                     rectangleA.left() += 4;
//                                     rectangleA.bottom() -= 4;
//                                     rectangleA.right() -= 4;
//
//                                     ptB = rectangleA.bottom_left();
//                                     ptC = rectangleA.bottom_left();
//                                     ptC.x() += 12;
//                                     pgraphics->MoveTo(ptB);
//                                     pgraphics->LineTo(ptC);
//
//                                     // Midle Rectangle 2
//
//                                     rectangleA = rectangleX;
//
//                                     rectangleA.top() += 2;
//                                     rectangleA.left() += 2;
//                                     rectangleA.bottom() -= 2;
//                                     rectangleA.right() -= 2;
//
//                                     ptA = rectangleA.bottom_left();
//                                     ptA.y() -= 13;
//                                     ptB = rectangleA.bottom_left();
//                                     ptC = rectangleA.bottom_left();
//                                     ptC.x() += 14;
//                                     pgraphics->MoveTo(ptA);
//                                     pgraphics->LineTo(ptB);
//                                     pgraphics->LineTo(ptC);
//
//                                     pgraphics->SelectObject(m_ppenShadow1);
//
//                                     rectangleA = rectangleX;
//
//                                     rectangleA.left() += 2;
//                                     rectangleA.bottom()--;
//
//                                     ptB = rectangleA.bottom_left();
//                                     ptC = rectangleA.bottom_left();
//                                     ptC.x() += 14;
//                                     pgraphics->MoveTo(ptB);
//                                     pgraphics->LineTo(ptC);
//
//                                     rectangleA = rectangleX;
//
//                                     rectangleA.left() += 3;
//                                     rectangleA.bottom() -= 2;
//
//                                     ptA = rectangleA.bottom_left();
//                                     ptA.y() -= 12;
//                                     ptB = rectangleA.bottom_left();
//                                     pgraphics->MoveTo(ptA);
//                                     pgraphics->LineTo(ptB);
//
//                                     pgraphics->SelectObject(m_ppenDkShadow1);
//
//                                     rectangleA = rectangleX;
//
//                                     ptB = rectangleA.bottom_left();
//                                     ptB.x()++;
//                                     ptC = rectangleA.bottom_left();
//                                     ptC.x() += 16;
//                                     pgraphics->MoveTo(ptB);
//                                     pgraphics->LineTo(ptC);
//
//                                     rectangleA.left() += 4;
//                                     rectangleA.bottom() -= 3;
//
//                                     ptA = rectangleA.bottom_left();
//                                     ptA.y() -= 11;
//                                     ptB = rectangleA.bottom_left();
//                                     pgraphics->MoveTo(ptA);
//                                     pgraphics->LineTo(ptB);
//
//                                     // Details - top most
//
//                                     pgraphics->SelectObject(m_ppenHilight1);
//
//                                     ptA.x() = rectangleXB.left() + 1;
//                                     ptA.y() = rectangleXB.bottom() - 15;
//                                     ptB.x() = rectangleXB.left() + 4;
//                                     ptB.y() = rectangleXB.bottom() - 15;
//                                     pgraphics->MoveTo(ptA);
//                                     pgraphics->LineTo(ptB);
//
//                                     // Details - top most
//
//                                     pgraphics->SelectObject(m_ppenFace1);
//
//                                     ptA.x() = rectangleXB.left();
//                                     ptA.y() = rectangleXB.bottom() - 15;
//                                     ptB.x() = rectangleXB.left() + 5;
//                                     ptB.y() = rectangleXB.bottom() - 15;
//                                     pgraphics->MoveTo(ptA);
//                                     pgraphics->LineTo(ptB);
//
//                                     pgraphics->SelectObject(m_ppenShadow1);
//
//                                     // Details - right most
//
//                                     ptA.x() = rectangleXB.left() + 14;
//                                     ptA.y() = rectangleXB.bottom() - 4;
//                                     ptB.x() = rectangleXB.left() + 14;
//                                     ptB.y() = rectangleXB.bottom() - 1;
//                                     pgraphics->MoveTo(ptB);
//                                     pgraphics->LineTo(ptA);
//
//                                     pgraphics->SelectObject(m_ppenDkShadow1);
//
//                                     // Details - right most
//
//                                     ptA.x() = rectangleXB.left() + 15;
//                                     ptA.y() = rectangleXB.bottom() - 4;
//                                     ptB.x() = rectangleXB.left() + 15;
//                                     ptB.y() = rectangleXB.bottom();
//                                     pgraphics->MoveTo(ptB);
//                                     pgraphics->LineTo(ptA);
//               }
//                  break;
//               case e_grip_bottom_right:
//               {
//                                      pgraphics->SelectObject(m_ppenHilight1);
//
//                                      rectangleA = rectangleX;
//
//                                      rectangleA.top()++;
//                                      rectangleA.left()++;
//                                      rectangleA.bottom()--;
//                                      rectangleA.right()--;
//
//                                      rectangleA.top() += 2;
//                                      rectangleA.left() += 2;
//                                      rectangleA.bottom() -= 2;
//                                      rectangleA.right() -= 2;
//
//                                      ptA = rectangleA.bottom_right();
//                                      ptA.y() -= 12;
//                                      ptB = rectangleA.bottom_right();
//                                      ptC = rectangleA.bottom_right();
//                                      ptC.x() -= 13;
//                                      pgraphics->MoveTo(ptA);
//                                      pgraphics->LineTo(ptB);
//                                      pgraphics->LineTo(ptC);
//
//                                      pgraphics->SelectObject(m_ppenFace1);
//
//                                      rectangleA = rectangleX;
//
//                                      // Most internal int_rectangle
//
//                                      rectangleA.top() += 4;
//                                      rectangleA.left() += 4;
//                                      rectangleA.bottom() -= 4;
//                                      rectangleA.right() -= 4;
//
//                                      ptA = rectangleA.bottom_right();
//                                      ptA.y() -= 11;
//                                      ptB = rectangleA.bottom_right();
//                                      ptC = rectangleA.bottom_right();
//                                      ptC.x() -= 12;
//                                      pgraphics->MoveTo(ptA);
//                                      pgraphics->LineTo(ptB);
//                                      pgraphics->LineTo(ptC);
//
//                                      // Midle Rectangle
//
//                                      rectangleA = rectangleX;
//
//                                      rectangleA.top() += 2;
//                                      rectangleA.left() += 2;
//                                      rectangleA.bottom() -= 2;
//                                      rectangleA.right() -= 2;
//
//                                      ptA = rectangleA.bottom_right();
//                                      ptA.y() -= 13;
//                                      ptB = rectangleA.bottom_right();
//                                      ptC = rectangleA.bottom_right();
//                                      ptC.x() -= 14;
//                                      pgraphics->MoveTo(ptA);
//                                      pgraphics->LineTo(ptB);
//                                      pgraphics->LineTo(ptC);
//                                      pgraphics->SelectObject(m_ppenShadow1);
//
//                                      rectangleA = rectangleX;
//
//                                      rectangleA.top()++;
//                                      rectangleA.left()++;
//                                      rectangleA.bottom()--;
//                                      rectangleA.right()--;
//
//                                      ptA = rectangleA.bottom_right();
//                                      ptA.y() -= 14;
//                                      ptB = rectangleA.bottom_right();
//                                      ptC = rectangleA.bottom_right();
//                                      ptC.x() -= 15;
//                                      pgraphics->MoveTo(ptA);
//                                      pgraphics->LineTo(ptB);
//                                      pgraphics->LineTo(ptC);
//
//                                      pgraphics->SelectObject(m_ppenDkShadow1);
//
//                                      rectangleA = rectangleX;
//
//                                      ptA = rectangleA.bottom_right();
//                                      ptA.y() -= 15;
//                                      ptB = rectangleA.bottom_right();
//                                      ptC = rectangleA.bottom_right();
//                                      ptC.x() -= 15;
//                                      pgraphics->MoveTo(ptA);
//                                      pgraphics->LineTo(ptB);
//                                      pgraphics->LineTo(ptC);
//
//                                      pgraphics->SelectObject(m_ppenHilight1);
//
//                                      ptA.x() = rectangleXB.right() - 3;
//                                      ptA.y() = rectangleXB.bottom() - 14;
//                                      ptB.x() = rectangleXB.right() - 1;
//                                      ptB.y() = rectangleXB.bottom() - 14;
//                                      pgraphics->MoveTo(ptB);
//                                      pgraphics->LineTo(ptA);
//
//                                      ptA.x() = rectangleXB.right() - 14;
//                                      ptA.y() = rectangleXB.bottom() - 3;
//                                      ptB.x() = rectangleXB.right() - 14;
//                                      ptB.y() = rectangleXB.bottom() - 1;
//                                      pgraphics->MoveTo(ptB);
//                                      pgraphics->LineTo(ptA);
//
//                                      pgraphics->SelectObject(m_ppenFace1);
//
//                                      // Details
//
//                                      ptA.x() = rectangleXB.right() - 5;
//                                      ptA.y() = rectangleXB.bottom() - 15;
//                                      ptB.x() = rectangleXB.right();
//                                      ptB.y() = rectangleXB.bottom() - 15;
//                                      pgraphics->MoveTo(ptB);
//                                      pgraphics->LineTo(ptA);
//
//                                      ptA.x() = rectangleXB.right() - 15;
//                                      ptA.y() = rectangleXB.bottom() - 5;
//                                      ptB.x() = rectangleXB.right() - 15;
//                                      ptB.y() = rectangleXB.bottom();
//                                      pgraphics->MoveTo(ptB);
//                                      pgraphics->LineTo(ptA);
//               }
//                  break;
//               case e_grip_top:
//               {
//                                    int_point ptCenter = rectangle.center();
//
//                                    int iMod;
//                                    if(rectangle.width() % 2 == 1)
//                                       iMod = 1;
//                                    else
//                                       iMod = 0;
//
//                                    ::int_rectangle rectangleB;
//
//                                    rectangleB.top() = rectangleC.top();
//                                    rectangleB.left() = ptCenter.x() - GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                    rectangleB.right() = ptCenter.x() + GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                    rectangleB.bottom() = rectangleC.top() + GRIP_CENTER_SMALL_CY;
//
//                                    DrawRectGrip(pgraphics, rectangleB);
//               }
//                  break;
//               case e_grip_bottom:
//               {
//                                       int_point ptCenter = rectangle.center();
//
//                                       ::int_rectangle rectangleB;
//
//                                       int iMod;
//                                       if(rectangle.width() % 2 == 1)
//                                          iMod = 1;
//                                       else
//                                          iMod = 0;
//
//                                       rectangleB.bottom() = rectangleC.bottom();
//                                       rectangleB.left() = ptCenter.x() - GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                       rectangleB.right() = ptCenter.x() + GRIP_CENTER_LARGE_CX / 2 + iMod;
//                                       rectangleB.top() = rectangleC.bottom() - GRIP_CENTER_SMALL_CY;
//
//                                       DrawRectGrip(pgraphics, rectangleB);
//               }
//                  break;
//               case e_grip_left:
//               {
//                                     int_point ptCenter = rectangle.center();
//
//                                     int iMod;
//                                     if(rectangle.height() % 2 == 1)
//                                        iMod = 1;
//                                     else
//                                        iMod = 0;
//
//
//                                     ::int_rectangle rectangleB;
//
//                                     rectangleB.top() = ptCenter.y() - GRIP_CENTER_LARGE_CY / 2 + iMod;
//                                     rectangleB.left() = rectangleC.left();
//                                     rectangleB.right() = rectangleC.left() + GRIP_CENTER_SMALL_CX;
//                                     rectangleB.bottom() = ptCenter.y() + GRIP_CENTER_LARGE_CY / 2 + iMod;
//
//                                     DrawRectGrip(pgraphics, rectangleB);
//               }
//                  break;
//               case e_grip_right:
//               {
//                                      int_point ptCenter = rectangle.center();
//
//                                      int iMod;
//                                      if(rectangle.height() % 2 == 1)
//                                         iMod = 1;
//                                      else
//                                         iMod = 0;
//
//
//                                      ::int_rectangle rectangleB;
//
//                                      rectangleB.top() = ptCenter.y() - GRIP_CENTER_LARGE_CY / 2 + iMod;
//                                      rectangleB.right() = rectangleC.right();
//                                      rectangleB.left() = rectangleC.right() - GRIP_CENTER_SMALL_CX;
//                                      rectangleB.bottom() = ptCenter.y() + GRIP_CENTER_LARGE_CY / 2 + iMod;
//
//                                      DrawRectGrip(pgraphics, rectangleB);
//               }
//                  break;
//               default:
//                  break;
//               }
//
//
//            }
//
//            void frame_Minimal001::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const ::int_rectangle &rectangleParam)
//            {
//
//               
//
//               ::int_rectangle rectangle(rectangleParam);
//
//               //rectangle.right()++;
//
//               //rectangle.bottom()++;
//
//               pgraphics->Draw3dRect(rectangle, crButtonFace | 0xff000000, crButtonDarkShadow | 0xff000000);
//
//               rectangle.deflate(1, 1);
//
//               pgraphics->Draw3dRect(rectangle, crButtonHilite | 0xff000000, crButtonShadow | 0xff000000);
//
//               rectangle.deflate(1, 1);
//
//               //rectangle.right()--;
//
//               //rectangle.bottom()--;
//
//               pgraphics->FillSolidRect(rectangle, crButtonFace | 0xff000000);

            }

            void frame_Minimal001::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle &lpcrectClient)
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

































