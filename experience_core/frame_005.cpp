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


         namespace core
         {


            frame_005::frame_005() :
               m_brushGrip(e_create),
               m_brushTextCaption(e_create)
            {

               //m_strStyle = "LightGreen";

               m_brushGrip->create_solid(argb(0xff, 0x60, 0x65, 0x55));

            }


            frame_005::~frame_005()
            {

            }


            string frame_005::get_default_user_style() const
            {

               return "LightGreen";

            }

            
            void frame_005::on_initialize_experience_frame()
            {

               frame::on_initialize_experience_frame();

               auto psession = Session;

               auto pframewindow = m_pframewindow;

               auto pgraphics = pframewindow->create_memory_graphics();

               auto pstyle = pframewindow->get_style(pgraphics);

               auto colorCaptionText = pframewindow->get_color(pstyle, ::user::e_element_window_title);

               m_brushTextCaption->create_solid(colorCaptionText);

            }


            e_hittest frame_005::_001HitTest(const ::point_i32 & pointCursor)
            {
               e_hittest etest = hittest_client;
               {
                  //      m_pframewindow->_001ScreenToClient(point);
                  ::rectangle_i32 rectEvent;
                  m_pframewindow->get_window_rect(rectEvent);
                  ::rectangle_i32 rectangle;
                  ::point_i32 pointCenter = rectEvent.center();
                  enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();

                  ::point_i32 pointHitTest = pointCursor;

//                  if(rectEvent.left < 0)
//                     pointHitTest.x -= rectEvent.left;
//                  if(rectEvent.top < 0)
//                     pointHitTest.y -= rectEvent.top;

                  if(egrip & e_grip_top_left)
                  {
                     rectangle = rectEvent;
                     rectangle.right = rectangle.left + 16;
                     rectangle.bottom = rectangle.top + 5;
                     if(rectangle.contains(pointHitTest))
                     {
                        etest = hittest_sizing_top_left;
                        goto SizingSuccess;
                     }
                     rectangle = rectEvent;
                     rectangle.right = rectangle.left + 5;
                     rectangle.bottom = rectangle.top + 16;
                     if(rectangle.contains(pointHitTest))
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
                     if(rectangle.contains(pointHitTest))
                     {
                        etest = hittest_sizing_top_right;
                        goto SizingSuccess;
                     }
                     rectangle = rectEvent;
                     rectangle.left = rectangle.right - 5;
                     rectangle.bottom = rectangle.top + 16;
                     if(rectangle.contains(pointHitTest))
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
                     if(rectangle.contains(pointHitTest))
                     {
                        etest = hittest_sizing_bottom_right;
                        goto SizingSuccess;
                     }
                     rectangle = rectEvent;
                     rectangle.left = rectangle.right - 5;
                     rectangle.top = rectangle.bottom - 16;
                     if(rectangle.contains(pointHitTest))
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
                     if(rectangle.contains(pointHitTest))
                     {
                        etest = hittest_sizing_bottom_left;
                        goto SizingSuccess;
                     }
                     rectangle = rectEvent;
                     rectangle.right = rectangle.left + 5;
                     rectangle.top = rectangle.bottom - 16;
                     if(rectangle.contains(pointHitTest))
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
                     if(rectangle.contains(pointHitTest))
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
                     if(rectangle.contains(pointHitTest))
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
                     if(rectangle.contains(pointHitTest))
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
                     if(rectangle.contains(pointHitTest))
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




            void frame_005::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient,
                  enum_border eside)
            {

               auto pframewindow = m_pframewindow;

               if (pframewindow == nullptr)
               {

                  return;

               }

               auto psession = Session;

               color32_t    crMoveableBorder;
               color32_t    crMoveableBorderHilight;
               color32_t    crMoveableBorderShadow;

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

               enum_dock edock = m_pframewindow->dock_manager()->get_dock_mask();
               ::rectangle_i32 rectA(rectClient);

               if(m_pframewindow->m_estyle == ::user::StyleTranslucidWarmGray
                     || m_pframewindow->m_estyle == ::user::StyleTranslucidLightBlue
                     || m_pframewindow->m_estyle == ::user::StyleTranslucidLightGreen)
               {

                  ::rectangle_i32 rectangle;

                  GetBorderRect(rectClient, rectangle, eside);

                  ColorGlass(pgraphics, rectangle, crMoveableBorder, 127);

               }
               else if(m_pframewindow->m_estyle == ::user::StyleLightBlue)
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
                  GetBorderRect(rectClient, rectangle, eside);
                  class imaging & imaging = System.imaging();
                  imaging.color_blend(pgraphics,
                                      rectangle,
                                      crMoveableBorder,
                                      127);
               }
               else
               {
                  ::rectangle_i32 rectangle;
                  GetBorderRect(rectClient, rectangle, eside);

                  ColorGlass(pgraphics, rectangle, crMoveableBorder, 230);

                  //auto:rectangle_i32 rectClientB = rectA;

                  //rectClientB.bottom--;
                  //rectClientB.right--;

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  if(edock == e_dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectA, eside, m_colorDkShadow, m_colorDkShadow);
                  }

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  Draw3dRectSide(pgraphics, rectA, eside, m_colorDkShadow, m_colorDkShadow);

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  if(edock == e_dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectA, eside, m_colorDkShadow, m_colorDkShadow);
                  }
               }

            }

            void frame_005::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
            {

               auto pframewindow = m_pframewindow;

               if(pframewindow == nullptr)
                  return;

               if(pframewindow == nullptr)
                  return;

               if(!pframewindow->is_frame_experience_enabled())
                  return;

               bool bZoomed = pframewindow->layout().is_zoomed();

               //    CVMSApp * pApp = (CVMSApp *) &System;
               //::aura::savings & savings = psession->savings();

               //auto rectClient = pframewindow->get_client_rect();

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


            void frame_005::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient)
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

            void frame_005::GetBorderRect(
            const ::rectangle_i32 & rectClient,
            RECTANGLE_I32 * lprect,
            enum_border eside)
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


            void frame_005::Draw3dRectSide(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectParam,enum_border eborder,color32_t crTopLeft,color32_t crBottomRight)
            {

               auto psession = Session;

               ::rectangle_i32 rectangle(rectParam);
               i32 x = rectangle.left;
               i32 y = rectangle.top;
               i32 cx = rectangle.width();
               i32 cy = rectangle.height();

               ::rectangle_i32 rectDraw;

               if(eborder & e_border_top)
               {

                  rectDraw = ::rect_dim(x, y, cx, 1);

                  if(psession->savings().is_trying_to_save(::e_resource_processing))
                  {

                     pgraphics->fill_rectangle(rectDraw, crTopLeft);

                  }
                  else
                  {
                     ColorGlass(pgraphics, rectDraw, crTopLeft, 127);

                  }

               }

               if(eborder & e_border_left)
               {

                  rectDraw = ::rect_dim(x, y + 1, 1, cy - 2);

                  if(psession->savings().is_trying_to_save(::e_resource_processing))
                  {

                     pgraphics->fill_rectangle(rectDraw, crTopLeft);

                  }
                  else
                  {

                     ColorGlass(pgraphics, rectDraw, crTopLeft, 127);

                  }

               }

               if(eborder & e_border_right)
               {

                  rectDraw = ::rect_dim(x + cx - 1, y + 1, 1, cy - 2);

                  if(psession->savings().is_trying_to_save(::e_resource_processing))
                  {

                     pgraphics->fill_rectangle(rectDraw, crBottomRight);

                  }
                  else
                  {

                     ColorGlass(pgraphics, rectDraw, crBottomRight, 127);

                  }

               }

               if(eborder & e_border_bottom)
               {

                  rectDraw = ::rect_dim(x, y + cy - 1, cx, 1);

                  if(psession->savings().is_trying_to_save(::e_resource_processing))
                  {

                     pgraphics->fill_rectangle(rectDraw, crBottomRight);

                  }
                  else
                  {
                     ColorGlass(pgraphics, rectDraw, crBottomRight, 127);
                  }

               }

            }


            void frame_005::on_style_change()
            {

               on_style_change_001_and_002();


            }

#define BEVEL_SMALL 2
#define BEVEL_LARGE 5
#define GRIP_SMALL 8
#define GRIP_LARGE 30

            void frame_005::DrawGrip(
            ::draw2d::graphics_pointer & pgraphics,
            const ::rectangle_i32 & rectClientParam,
            enum_grip egrip)
            {



               const i32 size = 16;

               auto rectClient(rectClientParam);
               //            ::rectangle_i32 rectClientB(rectClient);
               ::rectangle_i32 rectA;
               ::point_i32 pointA;
               ::point_i32 pointB;
               ::point_i32 pointC;
               //            ::rectangle_i32 rectangle(rectClient);
               switch(egrip)
               {
               case e_grip_top_left:
               {

                  rectA = rectClient;

                  rectA.right = 4;
                  rectA.bottom = size;

                  pgraphics->fill_rectangle(rectA, m_brushGrip);

                  rectA.right = size;
                  rectA.bottom = 4;

                  pgraphics->fill_rectangle(rectA, m_brushGrip);

               }
               break;
               case e_grip_top_right:
               {
                  rectA = rectClient;

                  rectA.left = rectA.right - 4;
                  rectA.bottom = size;

                  pgraphics->fill_rectangle(rectA, m_brushGrip);

                  rectA.left = rectA.right - size;
                  rectA.bottom = 4;

                  pgraphics->fill_rectangle(rectA, m_brushGrip);
               }
               break;
               case e_grip_bottom_left:
               {
                  rectA = rectClient;

                  rectA.right = 4;
                  rectA.top = rectA.bottom - size;

                  pgraphics->fill_rectangle(rectA, m_brushGrip);

                  rectA.right = size;
                  rectA.top = rectA.bottom - 4;

                  pgraphics->fill_rectangle(rectA, m_brushGrip);
               }
               break;
               case e_grip_bottom_right:
               {
                  rectA = rectClient;

                  rectA.left = rectA.right - 4;
                  rectA.top = rectA.bottom - size;

                  pgraphics->fill_rectangle(rectA, m_brushGrip);

                  rectA.left = rectA.right - size;
                  rectA.top = rectA.bottom - 4;

                  pgraphics->fill_rectangle(rectA, m_brushGrip);
               }
               break;
               case e_grip_top:
               {
                  rectA = rectClient;

                  rectA.left = rectA.left + rectA.width() / 2 - size / 2;
                  rectA.right = rectA.left + size;
                  rectA.bottom = 4;

                  pgraphics->fill_rectangle(rectA, m_brushGrip);

               }
               break;
               case e_grip_bottom:
               {
                  rectA = rectClient;

                  rectA.left = rectA.left + rectA.width() / 2 - size / 2;
                  rectA.right = rectA.left + size;
                  rectA.top = rectA.bottom - 4;

                  pgraphics->fill_rectangle(rectA, m_brushGrip);
               }
               break;
               case e_grip_left:
               {
                  rectA = rectClient;

                  rectA.right = 4;
                  rectA.top = rectA.top + rectA.height() / 2 - size / 2;
                  rectA.bottom = rectA.top + size;

                  pgraphics->fill_rectangle(rectA, m_brushGrip);
               }
               break;
               case e_grip_right:
               {
                  rectA = rectClient;

                  rectA.left = rectA.right - 4;
                  rectA.top = rectA.top + rectA.height() / 2 - size / 2;
                  rectA.bottom = rectA.top + size;

                  pgraphics->fill_rectangle(rectA, m_brushGrip);
               }
               break;
               default:
                  break;
               }


            }


            void frame_005::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectParam)
            {

               ::rectangle_i32 rectangle(rectParam);

               auto psession = Session;

               auto pframewindow = m_pframewindow;

               auto pstyle = pframewindow->get_style(pgraphics);

               auto crMoveableBorder = pframewindow->get_color(pstyle, ::user::e_element_button_background);

               auto crMoveableBorderHilight = pframewindow->get_color(pstyle, ::user::e_element_button_hilite);

               auto crMoveableBorderDkShadow = pframewindow->get_color(pstyle, ::user::e_element_button_dark_shadow);

               auto crMoveableBorderShadow = pframewindow->get_color(pstyle, ::user::e_element_button_shadow);

               pgraphics->draw_3drect(rectangle, crMoveableBorder, crMoveableBorderDkShadow);

               rectangle.top++;
               rectangle.bottom--;
               rectangle.left++;
               rectangle.right--;

               pgraphics->draw_3drect(rectangle,crMoveableBorderHilight, crMoveableBorderShadow);

               rectangle.top++;
               rectangle.bottom--;
               rectangle.left++;
               rectangle.right--;

               pgraphics->fill_rectangle(rectangle, crMoveableBorder);

            }


            void frame_005::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient)
            {

               auto psizemanager = m_pframewindow->size_manager();

               if (psizemanager == nullptr)
               {
                
                  return;

               }

               enum_grip egrip = psizemanager->GetGripMask();

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



