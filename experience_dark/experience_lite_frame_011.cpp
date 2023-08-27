#include "framework.h"


#define GRIP_CORNER_LARGE_CX 16
#define GRIP_CORNER_SMALL_CX 5
#define GRIP_CORNER_LARGE_CY 16
#define GRIP_CORNER_SMALL_CY 5


#define GRIP_CENTER_LARGE_CX 36
#define GRIP_CENTER_SMALL_CX 7
#define GRIP_CENTER_LARGE_CY 36
#define GRIP_CENTER_SMALL_CY 7





   namespace experience
   {


      


         namespace lite

         {


            frame_011::frame_011(::particle * pparticle) :
               object(pparticle),
               frame(pparticle)
            {

               set_style(StyleTranslucidWarmLiteGray);

            }


            frame_011::~frame_011()
            {

            }


            e_hittest frame_011::_001HitTest(::point_i32 pointCursor)
            {
               e_hittest etest = ::experience::e_frame_client;
               {
                  //      m_pframewindow->GetEventWindow()->screen_to_client()(point);
                  ::rectangle_i32 rectangleEvent;
                  m_pframewindow->window_rectangle(rectangleEvent);
                  ::rectangle_i32 rectangle;
                  point_i32 ptCenter = rectangleEvent.center();
                  enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();

                  ::point_i32 pointHitTest = pointCursor;

                  if (rectangleEvent.left < 0)
                     pointHitTest.x() -= rectangleEvent.left;
                  if (rectangleEvent.top < 0)
                     pointHitTest.y() -= rectangleEvent.top;

                  if (egrip & e_grip_top_left)
                  {
                     rectangle = rectangleEvent;
                     rectangle.right = rectangle.left + 16;
                     rectangle.bottom = rectangle.top + 5;
                     if (rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_top_left;
                        goto SizingSuccess;
                     }
                     rectangle = rectangleEvent;
                     rectangle.right = rectangle.left + 5;
                     rectangle.bottom = rectangle.top + 16;
                     if (rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_top_left;
                        goto SizingSuccess;
                     }
                  }
                  if (egrip & e_grip_top_right)
                  {
                     rectangle = rectangleEvent;
                     rectangle.left = rectangle.right - 16;
                     rectangle.bottom = rectangle.top + 5;
                     if (rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_top_right;
                        goto SizingSuccess;
                     }
                     rectangle = rectangleEvent;
                     rectangle.left = rectangle.right - 5;
                     rectangle.bottom = rectangle.top + 16;
                     if (rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_top_right;
                        goto SizingSuccess;
                     }
                  }
                  if (egrip & e_grip_bottom_right)
                  {
                     rectangle = rectangleEvent;
                     rectangle.left = rectangle.right - 16;
                     rectangle.top = rectangle.bottom - 5;
                     if (rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_bottom_right;
                        goto SizingSuccess;
                     }
                     rectangle = rectangleEvent;
                     rectangle.left = rectangle.right - 5;
                     rectangle.top = rectangle.bottom - 16;
                     if (rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_bottom_right;
                        goto SizingSuccess;
                     }
                  }
                  if (egrip & e_grip_bottom_left)
                  {
                     rectangle = rectangleEvent;
                     rectangle.right = rectangle.left + 16;
                     rectangle.top = rectangle.bottom - 5;
                     if (rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_bottom_left;
                        goto SizingSuccess;
                     }
                     rectangle = rectangleEvent;
                     rectangle.right = rectangle.left + 5;
                     rectangle.top = rectangle.bottom - 16;
                     if (rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_bottom_left;
                        goto SizingSuccess;
                     }
                  }
                  if (egrip & e_grip_top)
                  {
                     rectangle.top = rectangleEvent.top;
                     rectangle.left = ptCenter.x() - 8;
                     rectangle.right = ptCenter.x() + 8;
                     rectangle.bottom = rectangleEvent.top + 5;
                     if (rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_top;
                        goto SizingSuccess;
                     }
                  }
                  if (egrip & e_grip_bottom)
                  {
                     rectangle.top = rectangleEvent.bottom - 5;
                     rectangle.left = ptCenter.x() - 8;
                     rectangle.right = ptCenter.x() + 8;
                     rectangle.bottom = rectangleEvent.bottom;
                     if (rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_bottom;
                        goto SizingSuccess;
                     }
                  }
                  if (egrip & e_grip_left)
                  {
                     rectangle.top = ptCenter.y() - 8;
                     rectangle.left = rectangleEvent.left;
                     rectangle.right = rectangleEvent.left + 5;
                     rectangle.bottom = ptCenter.y() + 8;
                     if (rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_left;
                        goto SizingSuccess;
                     }
                  }
                  if (egrip & e_grip_right)
                  {
                     rectangle.top = ptCenter.y() - 8;
                     rectangle.left = rectangleEvent.right - 5;
                     rectangle.right = rectangleEvent.right;
                     rectangle.bottom = ptCenter.y() + 8;
                     if (rectangle.contains(pointHitTest))
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






            void frame_011::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 &lpcrectClient, enum_border eside)
            {



               auto pframewindow = m_pframewindow;

               if (pframewindow == nullptr)
                  return;

               color32_t    crMoveableBorder;
               color32_t    crMoveableBorderHilight;
               color32_t    crMoveableBorderShadow;

               if (pframewindow->m_fActive)
               {
                  crMoveableBorder = m_colorMoveableBorder;
                  crMoveableBorderHilight = m_colorMoveableBorderHilight;
                  crMoveableBorderShadow = m_colorMoveableBorderShadow;
               }
               else
               {

                  auto psession = get_session();

                  auto pstyle = pframewindow->get_style(pgraphics);

                  crMoveableBorder = pframewindow->get_color(pstyle, ::e_element_button_background);

                  crMoveableBorderHilight = pframewindow->get_color(pstyle, ::e_element_button_hilite);

                  crMoveableBorderShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

}

               enum_dock edock = m_pframewindow->dock_manager()->GetDockState();
               ::rectangle_i32 rectangleA(lpcrectClient);

               if (m_estyle == StyleTranslucidWarmGray
                     || m_estyle == StyleTranslucidLightBlue
                     || m_estyle == StyleTranslucidLightGreen)
               {
                  ::rectangle_i32 rectangle;
                  GetBorderRectangle(lpcrectClient, rectangle, eside);

                  pgraphics->color_blend(
                                      rectangle,
                                      crMoveableBorder,
                                      127);
               }
               else if (m_estyle == StyleLightBlue)
               {
                  rectangleA.deflate(1, 1, 1, 1);
                  //Draw3dRectSide(pgraphics,rectangleA,eside,crMoveableBorder,0);//m_colorMoveableBorderDkShadow);

                  rectangleA.deflate(1, 1, 1, 1);
                  //Draw3dRectSide(pgraphics,rectangleA,eside,crMoveableBorderHilight,crMoveableBorderShadow);

                  rectangleA.deflate(1, 1, 1, 1);
                  //Draw3dRectSide(pgraphics,rectangleA,eside,crMoveableBorder,crMoveableBorder);

                  rectangleA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectangleA, eside, crMoveableBorder, crMoveableBorder);

                  //::rectangle_i32 rectangle;
                  //GetBorderRectangle(lpcrectClient,rectangle,eside);
                  //class imaging & imaging = psystem->imaging();
                  //imaging.color_blend(pgraphics,
                  //   rectangle,
                  //   crMoveableBorder,
                  //   127);
               }
               else
               {
                  ::rectangle_i32 rectangle;
                  GetBorderRectangle(lpcrectClient, rectangle, eside);

                  pgraphics->color_blend(
                                      rectangle,
                                      crMoveableBorder,
                                      127);

                  ::rectangle_i32 rectangleXB = rectangleA;

                  rectangleXB.bottom--;
                  rectangleXB.right--;

                  rectangleA.top++;
                  rectangleA.bottom--;
                  rectangleA.left++;
                  rectangleA.right--;
                  if (edock == e_dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectangleA, eside, m_colorDkShadow, m_colorDkShadow);
                  }

                  rectangleA.top++;
                  rectangleA.bottom--;
                  rectangleA.left++;
                  rectangleA.right--;
                  Draw3dRectSide(pgraphics, rectangleA, eside, m_colorDkShadow, m_colorDkShadow);

                  rectangleA.top++;
                  rectangleA.bottom--;
                  rectangleA.left++;
                  rectangleA.right--;
                  if (edock == e_dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectangleA, eside, m_colorDkShadow, m_colorDkShadow);
                  }
               }

            }

            void frame_011::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
            {

               auto pframewindow = m_pframewindow;

               if (pframewindow == nullptr)
                  return;

               auto pframewindow = m_pframewindow;

               if (!pframewindow->is_frame_experience_enabled())
                  return;

               auto pframewindow = m_pframewindow;

               bool bZoomed = pframewindow->layout().is_zoomed() != 0;

               //    CVMSApp * pApp = (CVMSApp *) System;
               //::aura::savings & savings = psession->savings();

               auto rectangleX = pframewindow->rectangle();

               string str;


               ::rectangle_i32 rectangleNClient;

               pframewindow->window_rectangle(rectangleNClient);

               rectangleNClient -= rectangleNClient.top_left();

               ////////////////////
               //
               // Routine:
               // draw frame border
               //
               ////////////////////


               if (!pframewindow->layout().is_full_screen())
               {
                  DrawBorder(pgraphics, rectangleNClient);
               }



               ///////////////////////
               //
               // Routine:
               // draw resize grip set
               //
               ///////////////////////

               if (!bZoomed && !pframewindow->layout().is_full_screen())
               {
                  DrawGripSet(pgraphics, rectangleNClient);
               }

               //            pgraphics->SetBkMode(iOriginalBkMode);
               //          pgraphics->set_text_color(crOriginalTextColor);

            }


            void frame_011::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 &lpcrectClient)
            {

               auto pmovemanager = m_pframewindow->move_manager();

               enum_border eborder = pmovemanager->GetBorderMask();

               if (m_pframewindow->layout().is_zoomed())
               {
                  eborder = (enum_border)
                            (eborder &
                             ~(e_border_right
                               | e_border_bottom
                               | e_border_left));
               }

               if (eborder & e_border_top)
               {
                  draw_border_side(pgraphics, lpcrectClient, e_border_top);
               }
               if (eborder & e_border_right)
               {
                  draw_border_side(pgraphics, lpcrectClient, e_border_right);
               }
               if (eborder & e_border_bottom)
               {
                  draw_border_side(pgraphics, lpcrectClient, e_border_bottom);
               }
               if (eborder & e_border_left)
               {
                  draw_border_side(pgraphics, lpcrectClient, e_border_left);
               }

            }

            void frame_011::GetBorderRectangle(
            const ::rectangle_i32 &lpcrectClient,
            ::rectangle_i32 * lprect,
            enum_border eside)
            {
               ::rectangle_i32 rectangleBig(lpcrectClient);
               ::rectangle_i32 rectangleSmall;
               get_window_client_rectangle(&rectangleSmall);
               ::rectangle_i32 rectangle;
               if (eside == e_border_top)
               {
                  rectangle.left = rectangleBig.left;
                  rectangle.right = rectangleBig.right;
                  rectangle.top = rectangleBig.top;
                  rectangle.bottom = rectangleSmall.top;
               }
               else if (eside == e_border_left)
               {
                  rectangle.left = rectangleBig.left;
                  rectangle.right = rectangleSmall.left;
                  rectangle.top = rectangleSmall.top;
                  rectangle.bottom = rectangleSmall.bottom;
               }
               else if (eside == e_border_right)
               {
                  rectangle.left = rectangleSmall.right;
                  rectangle.right = rectangleBig.right;
                  rectangle.top = rectangleSmall.top;
                  rectangle.bottom = rectangleSmall.bottom;
               }
               else if (eside == e_border_bottom)
               {
                  rectangle.left = rectangleBig.left;
                  rectangle.right = rectangleBig.right;
                  rectangle.top = rectangleSmall.bottom;
                  rectangle.bottom = rectangleBig.bottom;
               }
               *lprect = rectangle;
            }


            void frame_011::_on_style_change(::draw2d::graphics_pointer & pgraphics)
            {

               on_style_change_001_and_002(pgraphics);

            }

#define BEVEL_SMALL 2
#define BEVEL_LARGE 5
#define GRIP_SMALL 8
#define GRIP_LARGE 30

            void frame_011::DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 &lpcrectClient, enum_grip egrip)
            {



               const i32 size = 16;

               ::rectangle_i32 rectangleX(lpcrectClient);
               //            ::rectangle_i32 rectangleXB(rectangleX);
               ::rectangle_i32 rectangleA;
               point_i32 ptA;
               point_i32 ptB;
               point_i32 ptC;
               //            ::rectangle_i32 rectangle(rectangleX);
               switch (egrip)
               {
               case e_grip_top_left:
               {

                  rectangleA = rectangleX;

                  rectangleA.right = 4;
                  rectangleA.bottom = size;

                  pgraphics->fill_rectangle(rectangleA, rgb(0x60, 0x65, 0x55));

                  rectangleA.right = size;
                  rectangleA.bottom = 4;

                  pgraphics->fill_rectangle(rectangleA, rgb(0x60, 0x65, 0x55));

               }
               break;
               case e_grip_top_right:
               {
                  rectangleA = rectangleX;

                  rectangleA.left = rectangleA.right - 4;
                  rectangleA.bottom = size;

                  pgraphics->fill_rectangle(rectangleA, rgb(0x60, 0x65, 0x55));

                  rectangleA.left = rectangleA.right - size;
                  rectangleA.bottom = 4;

                  pgraphics->fill_rectangle(rectangleA, rgb(0x60, 0x65, 0x55));
               }
               break;
               case e_grip_bottom_left:
               {
                  rectangleA = rectangleX;

                  rectangleA.right = 4;
                  rectangleA.top = rectangleA.bottom - size;

                  pgraphics->fill_rectangle(rectangleA, rgb(0x60, 0x65, 0x55));

                  rectangleA.right = size;
                  rectangleA.top = rectangleA.bottom - 4;

                  pgraphics->fill_rectangle(rectangleA, rgb(0x60, 0x65, 0x55));
               }
               break;
               case e_grip_bottom_right:
               {
                  rectangleA = rectangleX;

                  rectangleA.left = rectangleA.right - 4;
                  rectangleA.top = rectangleA.bottom - size;

                  pgraphics->fill_rectangle(rectangleA, rgb(0x60, 0x65, 0x55));

                  rectangleA.left = rectangleA.right - size;
                  rectangleA.top = rectangleA.bottom - 4;

                  pgraphics->fill_rectangle(rectangleA, rgb(0x60, 0x65, 0x55));
               }
               break;
               case e_grip_top:
               {
                  rectangleA = rectangleX;

                  rectangleA.left = rectangleA.left + rectangleA.width() / 2 - size / 2;
                  rectangleA.right = rectangleA.left + size;
                  rectangleA.bottom = 4;

                  pgraphics->fill_rectangle(rectangleA, rgb(0x60, 0x65, 0x55));

               }
               break;
               case e_grip_bottom:
               {
                  rectangleA = rectangleX;

                  rectangleA.left = rectangleA.left + rectangleA.width() / 2 - size / 2;
                  rectangleA.right = rectangleA.left + size;
                  rectangleA.top = rectangleA.bottom - 4;

                  pgraphics->fill_rectangle(rectangleA, rgb(0x60, 0x65, 0x55));
               }
               break;
               case e_grip_left:
               {
                  rectangleA = rectangleX;

                  rectangleA.right = 4;
                  rectangleA.top = rectangleA.top + rectangleA.height() / 2 - size / 2;
                  rectangleA.bottom = rectangleA.top + size;

                  pgraphics->fill_rectangle(rectangleA, rgb(0x60, 0x65, 0x55));
               }
               break;
               case e_grip_right:
               {
                  rectangleA = rectangleX;

                  rectangleA.left = rectangleA.right - 4;
                  rectangleA.top = rectangleA.top + rectangleA.height() / 2 - size / 2;
                  rectangleA.bottom = rectangleA.top + size;

                  pgraphics->fill_rectangle(rectangleA, rgb(0x60, 0x65, 0x55));
               }
               break;
               default:
                  break;
               }


            }

            void frame_011::DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleParam)
            {



               ::rectangle_i32 rectangle(rectangleParam);

               pgraphics->draw_inset_3d_rectangle(rectangle, crButtonFace, crButtonDarkShadow);

               rectangle.top++;
               rectangle.bottom--;
               rectangle.left++;
               rectangle.right--;

               pgraphics->draw_inset_3d_rectangle(rectangle, crButtonHilite, crButtonShadow);

               rectangle.top++;
               rectangle.bottom--;
               rectangle.left++;
               rectangle.right--;

               pgraphics->fill_rectangle(rectangle, crButtonFace);

            }


            void frame_011::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 &lpcrectClient)
            {

               size_manager * psizenager = m_pframewindow->size_manager();

               enum_grip egrip = psizenager->GetGripMask();

               if (egrip & e_grip_top)
               {
                  DrawGrip(pgraphics, lpcrectClient, e_grip_top);
               }
               if (egrip & e_grip_top_right)
               {
                  DrawGrip(pgraphics, lpcrectClient, e_grip_top_right);
               }
               if (egrip & e_grip_right)
               {
                  DrawGrip(pgraphics, lpcrectClient, e_grip_right);
               }
               if (egrip & e_grip_bottom_right)
               {
                  DrawGrip(pgraphics, lpcrectClient, e_grip_bottom_right);
               }
               if (egrip & e_grip_bottom)
               {
                  DrawGrip(pgraphics, lpcrectClient, e_grip_bottom);
               }
               if (egrip & e_grip_bottom_left)
               {
                  DrawGrip(pgraphics, lpcrectClient, e_grip_bottom_left);
               }
               if (egrip & e_grip_left)
               {
                  DrawGrip(pgraphics, lpcrectClient, e_grip_left);
               }
               if (egrip & e_grip_top_left)
               {
                  DrawGrip(pgraphics, lpcrectClient, e_grip_top_left);
               }

            }


         } // namespace lite



      


   } // namespace experience























































