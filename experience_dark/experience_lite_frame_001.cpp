#include "platform.h"

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


            frame_001::frame_001(::particle * pparticle) :
               object(pparticle),
               frame(pparticle)
            {

               set_style(StyleLightBlue);

            }


            frame_001::~frame_001()
            {

            }


            e_hittest frame_001::_001HitTest(::i32_point pointCursor)
            {
               e_hittest etest = ::experience::e_frame_client;
               {
                  //      m_pframewindow->GetEventWindow()->screen_to_client()(point);
                  ::i32_rectangle rectangleEvent;
                  m_pframewindow->window_rectangle(rectangleEvent);
                  ::i32_rectangle rectangle;
                  i32_point ptCenter = rectangleEvent.center();
                  auto egrip = m_pframewindow->size_manager()->GetGripMask();

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
                     rectangle.left = ptCenter.x - 8;
                     rectangle.right = ptCenter.x + 8;
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
                     rectangle.left = ptCenter.x - 8;
                     rectangle.right = ptCenter.x + 8;
                     rectangle.bottom = rectangleEvent.bottom;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = ::experience::e_frame_sizing_bottom;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_left)
                  {
                     rectangle.top = ptCenter.y - 8;
                     rectangle.left = rectangleEvent.left;
                     rectangle.right = rectangleEvent.left + 5;
                     rectangle.bottom = ptCenter.y + 8;
                     if(rectangle.contains(pointCursor))
                     {
                        etest = ::experience::e_frame_sizing_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_right)
                  {
                     rectangle.top = ptCenter.y - 8;
                     rectangle.left = rectangleEvent.right - 5;
                     rectangle.right = rectangleEvent.right;
                     rectangle.bottom = ptCenter.y + 8;
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





            void frame_001::draw_border_side(::draw2d::graphics_pointer & pdraw2dgraphics, const ::i32_rectangle &lpcrectClient, enum_border eside)
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
                  

                  auto pstyle = pframewindow->get_style(pdraw2dgraphics);

                  crMoveableBorder = pframewindow->get_color(pstyle, ::e_element_button_background);

                  crMoveableBorderHilight = pframewindow->get_color(pstyle, ::e_element_button_hilite);

                  crMoveableBorderShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

}



//               auto edock = m_pframewindow->dock_manager()->GetDockState();

               ::i32_rectangle rectangleA(lpcrectClient);

               if(is_translucid_style(m_estyle))
               {

                  ::i32_rectangle rectangle;

                  GetBorderRectangle(lpcrectClient, rectangle, eside);



                  pdraw2dgraphics->color_blend( rectangle, crMoveableBorder, 127);

               }
               /*else if(m_estyle == StyleLightBlue)
               {

                  ::i32_rectangle rectangle;

                  GetBorderRectangle(lpcrectClient, rectangle, eside);



                  pdraw2dgraphics->color_blend( rectangle, crMoveableBorder, 127);



                  rectangleA.deflate(2, 2, 2, 2);
                  Draw3dRectSide(pdraw2dgraphics, rectangleA, eside, crMoveableBorderHilight, crMoveableBorderShadow);

                  rectangleA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pdraw2dgraphics, rectangleA, eside, crMoveableBorder, crMoveableBorder);

                  rectangleA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pdraw2dgraphics, rectangleA, eside, crMoveableBorder, crMoveableBorder);


               }*/
               else
               {

                  ::i32_rectangle rectangleX(lpcrectClient);

                  rectangleX.deflate(2, 2, 2, 2);

                  ::i32_rectangle rectangle;

                  GetBorderRectangle(rectangleX, &rectangle, eside);



                  pdraw2dgraphics->color_blend( rectangle, crMoveableBorder, 127);

               }

            }


            void frame_001::on_draw_frame(::draw2d::graphics_pointer & pdraw2dgraphics)
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

               ::i32_rectangle rectangleWindow;

               pframewindow->window_rectangle(rectangleWindow);

               rectangleWindow -= rectangleWindow.top_left();

               if(!pframewindow->layout().is_full_screen())
               {

                  DrawBorder(pdraw2dgraphics, rectangleWindow);

               }

               if(!bZoomed && !pframewindow->layout().is_full_screen())
               {

                  DrawGripSet(pdraw2dgraphics, rectangleWindow);

               }

            }


            void frame_001::DrawBorder(::draw2d::graphics_pointer & pdraw2dgraphics, const ::i32_rectangle &lpcrectClient)
            {



               auto pmovemanager = m_pframewindow->move_manager();

               auto eborder = pmovemanager->GetBorderMask();

               if(m_pframewindow->layout().is_zoomed())
               {
                  eborder = 
                            (eborder &
                             ~(e_border_right
                               | e_border_bottom
                               | e_border_left));
               }

               if(eborder & e_border_top)
               {

                  draw_border_side(pdraw2dgraphics, lpcrectClient, e_border_top);

               }

               if(eborder & e_border_right)
               {

                  draw_border_side(pdraw2dgraphics, lpcrectClient, e_border_right);

               }

               if(eborder & e_border_bottom)
               {

                  draw_border_side(pdraw2dgraphics, lpcrectClient, e_border_bottom);

               }

               if(eborder & e_border_left)
               {

                  draw_border_side(pdraw2dgraphics, lpcrectClient, e_border_left);

               }

            }

            void frame_001::GetBorderRectangle(const ::i32_rectangle &lpcrectClient, ::i32_rectangle * lprect, enum_border eside)
            {

               ::i32_rectangle rectangleBig(lpcrectClient);

               ::i32_rectangle rectangleSmall;

               get_window_client_rectangle(&rectangleSmall);

               ::i32_rectangle rectangle;

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


            void frame_001::on_style_change()
            {

               on_style_change_001_and_002(pdraw2dgraphics);

            }


            void frame_001::DrawGrip(::draw2d::graphics_pointer & pdraw2dgraphics, const ::i32_rectangle &lpcrectClient, enum_grip egrip)
            {

               ::i32_rectangle rectangleC(lpcrectClient);

               ::i32_rectangle rectangleX(lpcrectClient);

               rectangleX.right--;

               rectangleX.bottom--;

               ::i32_rectangle rectangleXB(rectangleX);

               ::i32_rectangle rectangleA;

               i32_point ptA;

               i32_point ptB;

               i32_point ptC;

               ::i32_rectangle rectangle(rectangleX);



               switch(egrip)
               {
               case e_grip_top_left:
               {
                  pdraw2dgraphics->SelectObject(m_ppenHilight1);

                  rectangleA = rectangleX;

                  rectangleA.top++;
                  rectangleA.left++;
                  rectangleA.bottom--;
                  rectangleA.right--;

                  ptA = rectangleA.top_left();
                  ptA.y += 14;
                  ptB = rectangleA.top_left();
                  ptC = rectangleA.top_left();
                  ptC.x += 15;

                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  pdraw2dgraphics->SelectObject(m_ppenFace1);

                  // Most external i32_rectangle

                  rectangleA = rectangleX;

                  ptA = rectangleA.top_left();
                  ptA.y += 15;
                  ptB = rectangleA.top_left();
                  ptC = rectangleA.top_left();
                  ptC.x += 16;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  // Midle Rectangle

                  rectangleA = rectangleX;

                  rectangleA.top += 2;
                  rectangleA.left += 2;
                  rectangleA.bottom -= 2;
                  rectangleA.right -= 2;

                  ptA = rectangleA.top_left();
                  ptA.y += 13;
                  ptB = rectangleA.top_left();
                  ptC = rectangleA.top_left();
                  ptC.x += 14;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  pdraw2dgraphics->SelectObject(m_ppenShadow1);

                  rectangleA = rectangleX;

                  rectangleA.top++;
                  rectangleA.left++;
                  rectangleA.bottom--;
                  rectangleA.right--;

                  rectangleA.top += 2;
                  rectangleA.left += 2;
                  rectangleA.bottom -= 2;
                  rectangleA.right -= 2;


                  ptA = rectangleA.top_left();
                  ptA.y += 12;
                  ptB = rectangleA.top_left();
                  ptC = rectangleA.top_left();
                  ptC.x += 13;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  pdraw2dgraphics->SelectObject(m_ppenDkShadow1);

                  rectangleA = rectangleX;

                  rectangleA.top += 4;
                  rectangleA.left += 4;
                  rectangleA.bottom -= 4;
                  rectangleA.right -= 4;

                  ptA = rectangleA.top_left();
                  ptA.y += 11;
                  ptB = rectangleA.top_left();
                  ptC = rectangleA.top_left();
                  ptC.x += 12;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  pdraw2dgraphics->SelectObject(m_ppenShadow1);

                  // Details

                  ptA.x = rectangleXB.left + 14;
                  ptA.y = rectangleXB.top + 1;
                  ptB.x = rectangleXB.left + 14;
                  ptB.y = rectangleXB.top + 3;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);


                  // Details

                  ptA.x = rectangleXB.left + 1;
                  ptA.y = rectangleXB.top + 14;
                  ptB.x = rectangleXB.left + 3;
                  ptB.y = rectangleXB.top + 14;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);

                  pdraw2dgraphics->SelectObject(m_ppenDkShadow1);

                  // Details

                  ptA.x = rectangleXB.left + 15;
                  ptA.y = rectangleXB.top + 1;
                  ptB.x = rectangleXB.left + 15;
                  ptB.y = rectangleXB.top + 5;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);

                  // Details

                  ptA.x = rectangleXB.left + 1;
                  ptA.y = rectangleXB.top + 15;
                  ptB.x = rectangleXB.left + 5;
                  ptB.y = rectangleXB.top + 15;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);
               }
               break;
               case e_grip_top_right:
               {
                  pdraw2dgraphics->SelectObject(m_ppenHilight1);

                  rectangleA = rectangleX;

                  rectangleA.top++;
                  rectangleA.left++;
                  rectangleA.bottom--;
                  rectangleA.right--;

                  ptA = rectangleA.top_right();
                  ptA.x -= 15;
                  ptB = rectangleA.top_right();
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);

                  rectangleA.top += 2;
                  rectangleA.left += 2;
                  rectangleA.bottom -= 2;
                  rectangleA.right -= 2;

                  ptB = rectangleA.top_right();
                  ptC = rectangleA.top_right();
                  ptC.y += 13;
                  pdraw2dgraphics->set_current_point(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  pdraw2dgraphics->SelectObject(m_ppenFace1);

                  // Most external i32_rectangle

                  rectangleA = rectangleX;

                  ptA = rectangleA.top_right();
                  ptA.x -= 16;
                  ptB = rectangleA.top_right();
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);


                  // Most internal i32_rectangle

                  rectangleA.top += 4;
                  rectangleA.left += 4;
                  rectangleA.bottom -= 4;
                  rectangleA.right -= 4;

                  ptB = rectangleA.top_right();
                  ptC = rectangleA.top_right();
                  ptC.y += 12;
                  pdraw2dgraphics->set_current_point(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  // Midle Rectangle

                  rectangleA = rectangleX;

                  rectangleA.top += 2;
                  rectangleA.left += 2;
                  rectangleA.bottom -= 2;
                  rectangleA.right -= 2;

                  ptA = rectangleA.top_right();
                  ptA.x -= 13;
                  ptB = rectangleA.top_right();
                  ptC = rectangleA.top_right();
                  ptC.y += 14;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  pdraw2dgraphics->SelectObject(m_ppenShadow1);

                  rectangleA = rectangleX;

                  rectangleA.top++;
                  rectangleA.left++;
                  rectangleA.bottom--;
                  rectangleA.right--;

                  ptB = rectangleA.top_right();
                  ptC = rectangleA.top_right();
                  ptC.y += 15;
                  pdraw2dgraphics->set_current_point(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  rectangleA.top += 2;
                  rectangleA.left += 2;
                  rectangleA.bottom -= 2;
                  rectangleA.right -= 2;

                  ptA = rectangleA.top_right();
                  ptA.x -= 12;
                  ptB = rectangleA.top_right();
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);

                  pdraw2dgraphics->SelectObject(m_ppenDkShadow1);

                  rectangleA = rectangleX;

                  ptB = rectangleA.top_right();
                  ptC = rectangleA.top_right();
                  ptC.y += 16;
                  pdraw2dgraphics->set_current_point(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  rectangleA.top += 4;
                  rectangleA.left += 4;
                  rectangleA.bottom -= 4;
                  rectangleA.right -= 4;

                  ptA = rectangleA.top_right();
                  ptA.x -= 11;
                  ptB = rectangleA.top_right();
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);

                  pdraw2dgraphics->SelectObject(m_ppenHilight1);

                  ptA.x = rectangleXB.right - 14;
                  ptA.y = rectangleXB.top + 1;
                  ptB.x = rectangleXB.right - 14;
                  ptB.y = rectangleXB.top + 4;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);

                  pdraw2dgraphics->SelectObject(m_ppenFace1);

                  // Details

                  ptA.x = rectangleXB.right - 15;
                  ptA.y = rectangleXB.top;
                  ptB.x = rectangleXB.right - 15;
                  ptB.y = rectangleXB.top + 5;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);

                  pdraw2dgraphics->SelectObject(m_ppenShadow1);

                  // Details

                  ptA.x = rectangleXB.right - 3;
                  ptA.y = rectangleXB.top + 14;
                  ptB.x = rectangleXB.right - 1;
                  ptB.y = rectangleXB.top + 14;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);

                  pdraw2dgraphics->SelectObject(m_ppenDkShadow1);

                  // Details

                  ptA.x = rectangleXB.right - 4;
                  ptA.y = rectangleXB.top + 15;
                  ptB.x = rectangleXB.right;
                  ptB.y = rectangleXB.top + 15;
                  pdraw2dgraphics->set_current_point(ptB);
                  pdraw2dgraphics->line_to(ptA);
               }
               break;
               case e_grip_bottom_left:
               {

                  pdraw2dgraphics->SelectObject(m_ppenHilight1);

                  rectangleA = rectangleX;

                  rectangleA.left++;
                  rectangleA.bottom--;

                  // left 1
                  ptA = rectangleA.bottom_left();
                  ptA.y -= 16;
                  ptB = rectangleA.bottom_left();
                  pdraw2dgraphics->set_current_point(ptB);
                  pdraw2dgraphics->line_to(ptA);

                  rectangleA = rectangleX;

                  rectangleA.left += 3;
                  rectangleA.bottom -= 3;

                  // bottom 2
                  ptB = rectangleA.bottom_left();
                  ptC = rectangleA.bottom_left();
                  ptC.x += 12;
                  pdraw2dgraphics->set_current_point(ptC);
                  pdraw2dgraphics->line_to(ptB);

                  pdraw2dgraphics->SelectObject(m_ppenFace1);

                  // Most external i32_rectangle 0

                  rectangleA = rectangleX;

                  ptA = rectangleA.bottom_left();
                  ptA.y -= 15;
                  ptB = rectangleA.bottom_left();
                  pdraw2dgraphics->set_current_point(ptB);
                  pdraw2dgraphics->line_to(ptA);

                  // Most internal i32_rectangle 4

                  rectangleA.top += 4;
                  rectangleA.left += 4;
                  rectangleA.bottom -= 4;
                  rectangleA.right -= 4;

                  ptB = rectangleA.bottom_left();
                  ptC = rectangleA.bottom_left();
                  ptC.x += 12;
                  pdraw2dgraphics->set_current_point(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  // Midle Rectangle 2

                  rectangleA = rectangleX;

                  rectangleA.top += 2;
                  rectangleA.left += 2;
                  rectangleA.bottom -= 2;
                  rectangleA.right -= 2;

                  ptA = rectangleA.bottom_left();
                  ptA.y -= 13;
                  ptB = rectangleA.bottom_left();
                  ptC = rectangleA.bottom_left();
                  ptC.x += 14;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  pdraw2dgraphics->SelectObject(m_ppenShadow1);

                  rectangleA = rectangleX;

                  rectangleA.left += 2;
                  rectangleA.bottom--;

                  ptB = rectangleA.bottom_left();
                  ptC = rectangleA.bottom_left();
                  ptC.x += 14;
                  pdraw2dgraphics->set_current_point(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  rectangleA = rectangleX;

                  rectangleA.left += 3;
                  rectangleA.bottom -= 2;

                  ptA = rectangleA.bottom_left();
                  ptA.y -= 12;
                  ptB = rectangleA.bottom_left();
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);

                  pdraw2dgraphics->SelectObject(m_ppenDkShadow1);

                  rectangleA = rectangleX;

                  ptB = rectangleA.bottom_left();
                  ptB.x++;
                  ptC = rectangleA.bottom_left();
                  ptC.x += 16;
                  pdraw2dgraphics->set_current_point(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  rectangleA.left += 4;
                  rectangleA.bottom -= 3;

                  ptA = rectangleA.bottom_left();
                  ptA.y -= 11;
                  ptB = rectangleA.bottom_left();
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);

                  // Details - top most

                  pdraw2dgraphics->SelectObject(m_ppenHilight1);

                  ptA.x = rectangleXB.left + 1;
                  ptA.y = rectangleXB.bottom - 15;
                  ptB.x = rectangleXB.left + 4;
                  ptB.y = rectangleXB.bottom - 15;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);

                  // Details - top most

                  pdraw2dgraphics->SelectObject(m_ppenFace1);

                  ptA.x = rectangleXB.left;
                  ptA.y = rectangleXB.bottom - 15;
                  ptB.x = rectangleXB.left + 5;
                  ptB.y = rectangleXB.bottom - 15;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);

                  pdraw2dgraphics->SelectObject(m_ppenShadow1);

                  // Details - right most

                  ptA.x = rectangleXB.left + 14;
                  ptA.y = rectangleXB.bottom - 4;
                  ptB.x = rectangleXB.left + 14;
                  ptB.y = rectangleXB.bottom - 1;
                  pdraw2dgraphics->set_current_point(ptB);
                  pdraw2dgraphics->line_to(ptA);

                  pdraw2dgraphics->SelectObject(m_ppenDkShadow1);

                  // Details - right most

                  ptA.x = rectangleXB.left + 15;
                  ptA.y = rectangleXB.bottom - 4;
                  ptB.x = rectangleXB.left + 15;
                  ptB.y = rectangleXB.bottom;
                  pdraw2dgraphics->set_current_point(ptB);
                  pdraw2dgraphics->line_to(ptA);
               }
               break;
               case e_grip_bottom_right:
               {
                  pdraw2dgraphics->SelectObject(m_ppenHilight1);

                  rectangleA = rectangleX;

                  rectangleA.top++;
                  rectangleA.left++;
                  rectangleA.bottom--;
                  rectangleA.right--;

                  rectangleA.top += 2;
                  rectangleA.left += 2;
                  rectangleA.bottom -= 2;
                  rectangleA.right -= 2;

                  ptA = rectangleA.bottom_right();
                  ptA.y -= 12;
                  ptB = rectangleA.bottom_right();
                  ptC = rectangleA.bottom_right();
                  ptC.x -= 13;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  pdraw2dgraphics->SelectObject(m_ppenFace1);

                  rectangleA = rectangleX;

                  // Most internal i32_rectangle

                  rectangleA.top += 4;
                  rectangleA.left += 4;
                  rectangleA.bottom -= 4;
                  rectangleA.right -= 4;

                  ptA = rectangleA.bottom_right();
                  ptA.y -= 11;
                  ptB = rectangleA.bottom_right();
                  ptC = rectangleA.bottom_right();
                  ptC.x -= 12;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  // Midle Rectangle

                  rectangleA = rectangleX;

                  rectangleA.top += 2;
                  rectangleA.left += 2;
                  rectangleA.bottom -= 2;
                  rectangleA.right -= 2;

                  ptA = rectangleA.bottom_right();
                  ptA.y -= 13;
                  ptB = rectangleA.bottom_right();
                  ptC = rectangleA.bottom_right();
                  ptC.x -= 14;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);
                  pdraw2dgraphics->line_to(ptC);
                  pdraw2dgraphics->SelectObject(m_ppenShadow1);

                  rectangleA = rectangleX;

                  rectangleA.top++;
                  rectangleA.left++;
                  rectangleA.bottom--;
                  rectangleA.right--;

                  ptA = rectangleA.bottom_right();
                  ptA.y -= 14;
                  ptB = rectangleA.bottom_right();
                  ptC = rectangleA.bottom_right();
                  ptC.x -= 15;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  pdraw2dgraphics->SelectObject(m_ppenDkShadow1);

                  rectangleA = rectangleX;

                  ptA = rectangleA.bottom_right();
                  ptA.y -= 15;
                  ptB = rectangleA.bottom_right();
                  ptC = rectangleA.bottom_right();
                  ptC.x -= 15;
                  pdraw2dgraphics->set_current_point(ptA);
                  pdraw2dgraphics->line_to(ptB);
                  pdraw2dgraphics->line_to(ptC);

                  pdraw2dgraphics->SelectObject(m_ppenHilight1);

                  ptA.x = rectangleXB.right - 3;
                  ptA.y = rectangleXB.bottom - 14;
                  ptB.x = rectangleXB.right - 1;
                  ptB.y = rectangleXB.bottom - 14;
                  pdraw2dgraphics->set_current_point(ptB);
                  pdraw2dgraphics->line_to(ptA);

                  ptA.x = rectangleXB.right - 14;
                  ptA.y = rectangleXB.bottom - 3;
                  ptB.x = rectangleXB.right - 14;
                  ptB.y = rectangleXB.bottom - 1;
                  pdraw2dgraphics->set_current_point(ptB);
                  pdraw2dgraphics->line_to(ptA);

                  pdraw2dgraphics->SelectObject(m_ppenFace1);

                  // Details

                  ptA.x = rectangleXB.right - 5;
                  ptA.y = rectangleXB.bottom - 15;
                  ptB.x = rectangleXB.right;
                  ptB.y = rectangleXB.bottom - 15;
                  pdraw2dgraphics->set_current_point(ptB);
                  pdraw2dgraphics->line_to(ptA);

                  ptA.x = rectangleXB.right - 15;
                  ptA.y = rectangleXB.bottom - 5;
                  ptB.x = rectangleXB.right - 15;
                  ptB.y = rectangleXB.bottom;
                  pdraw2dgraphics->set_current_point(ptB);
                  pdraw2dgraphics->line_to(ptA);
               }
               break;
               case e_grip_top:
               {
                  i32_point ptCenter = rectangle.center();

                  ::i32 iMod;
                  if(rectangle.width() % 2 == 1)
                     iMod = 1;
                  else
                     iMod = 0;

                  ::i32_rectangle rectangleB;

                  rectangleB.top = rectangleC.top;
                  rectangleB.left = ptCenter.x - GRIP_CENTER_LARGE_CX / 2 + iMod;
                  rectangleB.right = ptCenter.x + GRIP_CENTER_LARGE_CX / 2 + iMod;
                  rectangleB.bottom = rectangleC.top + GRIP_CENTER_SMALL_CY;

                  DrawRectGrip(pdraw2dgraphics, rectangleB);
               }
               break;
               case e_grip_bottom:
               {
                  i32_point ptCenter = rectangle.center();

                  ::i32_rectangle rectangleB;

                  ::i32 iMod;
                  if(rectangle.width() % 2 == 1)
                     iMod = 1;
                  else
                     iMod = 0;

                  rectangleB.bottom = rectangleC.bottom;
                  rectangleB.left = ptCenter.x - GRIP_CENTER_LARGE_CX / 2 + iMod;
                  rectangleB.right = ptCenter.x + GRIP_CENTER_LARGE_CX / 2 + iMod;
                  rectangleB.top = rectangleC.bottom - GRIP_CENTER_SMALL_CY;

                  DrawRectGrip(pdraw2dgraphics, rectangleB);
               }
               break;
               case e_grip_left:
               {
                  i32_point ptCenter = rectangle.center();

                  ::i32 iMod;
                  if(rectangle.height() % 2 == 1)
                     iMod = 1;
                  else
                     iMod = 0;


                  ::i32_rectangle rectangleB;

                  rectangleB.top = ptCenter.y - GRIP_CENTER_LARGE_CY / 2 + iMod;
                  rectangleB.left = rectangleC.left;
                  rectangleB.right = rectangleC.left + GRIP_CENTER_SMALL_CX;
                  rectangleB.bottom = ptCenter.y + GRIP_CENTER_LARGE_CY / 2 + iMod;

                  DrawRectGrip(pdraw2dgraphics, rectangleB);
               }
               break;
               case e_grip_right:
               {
                  i32_point ptCenter = rectangle.center();

                  ::i32 iMod;
                  if(rectangle.height() % 2 == 1)
                     iMod = 1;
                  else
                     iMod = 0;


                  ::i32_rectangle rectangleB;

                  rectangleB.top = ptCenter.y - GRIP_CENTER_LARGE_CY / 2 + iMod;
                  rectangleB.right = rectangleC.right;
                  rectangleB.left = rectangleC.right - GRIP_CENTER_SMALL_CX;
                  rectangleB.bottom = ptCenter.y + GRIP_CENTER_LARGE_CY / 2 + iMod;

                  DrawRectGrip(pdraw2dgraphics, rectangleB);
               }
               break;
               default:
                  break;
               }


            }

            void frame_001::DrawRectGrip(::draw2d::graphics_pointer & pdraw2dgraphics,const ::i32_rectangle &rectangleParam)
            {



               ::i32_rectangle rectangle(rectangleParam);

               //rectangle.right++;

               //rectangle.bottom++;

               pdraw2dgraphics->draw_inset_3d_rectangle(rectangle, crButtonFace | 0xff000000, crButtonDarkShadow | 0xff000000);

               rectangle.deflate(1, 1);

               pdraw2dgraphics->draw_inset_3d_rectangle(rectangle, crButtonHilite | 0xff000000, crButtonShadow | 0xff000000);

               rectangle.deflate(1, 1);

               pdraw2dgraphics->fill_rectangle(rectangle, crButtonFace | 0xff000000);

            }

            void frame_001::DrawGripSet(::draw2d::graphics_pointer & pdraw2dgraphics, const ::i32_rectangle &lpcrectClient)
            {
               size_manager * psizenager = m_pframewindow->size_manager();

               auto egrip = psizenager->GetGripMask();

               if(egrip & e_grip_top)
               {
                  DrawGrip(pdraw2dgraphics, lpcrectClient, e_grip_top);
               }
               if(egrip & e_grip_top_right)
               {
                  DrawGrip(pdraw2dgraphics, lpcrectClient, e_grip_top_right);
               }
               if(egrip & e_grip_right)
               {
                  DrawGrip(pdraw2dgraphics, lpcrectClient, e_grip_right);
               }
               if(egrip & e_grip_bottom_right)
               {
                  DrawGrip(pdraw2dgraphics, lpcrectClient, e_grip_bottom_right);
               }
               if(egrip & e_grip_bottom)
               {
                  DrawGrip(pdraw2dgraphics, lpcrectClient, e_grip_bottom);
               }
               if(egrip & e_grip_bottom_left)
               {
                  DrawGrip(pdraw2dgraphics, lpcrectClient, e_grip_bottom_left);
               }
               if(egrip & e_grip_left)
               {
                  DrawGrip(pdraw2dgraphics, lpcrectClient, e_grip_left);
               }
               if(egrip & e_grip_top_left)
               {
                  DrawGrip(pdraw2dgraphics, lpcrectClient, e_grip_top_left);
               }

            }


         } // namespace lite



      


   } // namespace experience


















































