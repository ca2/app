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


            frame_008::frame_008()
            {

               m_bHollow = false;

               m_penHollow0.create(this);
               m_penHollow1.create(this);
               m_penHollow2.create(this);
               m_penHollow3.create(this);
               m_penHollow4.create(this);
               m_penHollow5.create(this);

            }


            frame_008::~frame_008()
            {

            }


            //string frame_008::get_default_user_style() const
            //{

            //   return "LightGreen";

            //}


            e_hittest frame_008::_001HitTest(const ::point_i32 & pointCursor)
            {
               e_hittest etest = hittest_client;
               {
                  //      m_pframewindow->screen_to_client(point);
                  ::rectangle_i32 rectEvent;
                  m_pframewindow->get_window_rect(rectEvent);
                  ::rectangle_i32 rectangle;
                  ::point_i32 pointCenter = rectEvent.center();
                  enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();

                  ::point_i32 pointHitTest = pointCursor;

                  //if(rectEvent.left < 0)
                  // pointHitTest.x -= rectEvent.left;
                  //if(rectEvent.top < 0)
                  // pointHitTest.y -= rectEvent.top;

                  if((egrip & e_grip_top_left) == e_grip_top_left)
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
                  if((egrip & e_grip_top_right) == e_grip_top_right)
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
                  if((egrip & e_grip_bottom_right) == e_grip_bottom_right)
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
                  if((egrip & e_grip_bottom_left) == e_grip_bottom_left)
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
                  if((egrip & e_grip_top) == e_grip_top)
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
                  if((egrip & e_grip_bottom) == e_grip_bottom)
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
                  if((egrip & e_grip_left) == e_grip_left)
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
                  if((egrip & e_grip_right) == e_grip_right)
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






            void frame_008::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient, enum_border eside)
            {

               auto pframewindow = m_pframewindow;

               if (pframewindow == nullptr)
               {

                  return;

               }

               //auto psession = get_session();

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

                  auto pstyle = pframewindow->get_style(pgraphics);

                  crMoveableBorder = pframewindow->get_color(pstyle, ::e_element_button_background);

                  crMoveableBorderHilight = pframewindow->get_color(pstyle, ::e_element_button_hilite);

                  crMoveableBorderShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

               }

               enum_dock edock = m_pframewindow->dock_manager()->get_dock_mask();
               ::rectangle_i32 rectA(rectangleClient);

               if(m_bHollow)
               {

                  ::rectangle_i32 rectangle;
                  GetBorderRect(rectA, rectangle, eside);

                  pgraphics->fill_rectangle(rectangle, opaque(crMoveableBorder));//m_colorMoveableBorderDkShadow);

                  // rgb(255, 170, 136) RedOrange
               }
               else if(m_pframewindow->m_estyle == ::user::StyleLightBlue || m_pframewindow->m_estyle == ::user::StyleRedOrange)
               {
                  rectA.deflate(1,1,1,1);
                  Draw3dRectSide(pgraphics,rectA,eside,crMoveableBorder,0);//m_colorMoveableBorderDkShadow);

                  if(!m_bHollow)
                  {

                     rectA.deflate(1,1,1,1);
                     
                     Draw3dRectSide(pgraphics,rectA,eside,crMoveableBorderHilight,crMoveableBorderShadow);

                     rectA.deflate(1,1,1,1);
                     
                     Draw3dRectSide(pgraphics,rectA,eside,crMoveableBorder,crMoveableBorder);

                     rectA.deflate(1,1,1,1);
                     
                     Draw3dRectSide(pgraphics,rectA,eside,crMoveableBorder,crMoveableBorder);

                     ::rectangle_i32 rectangle;
                     
                     GetBorderRect(rectangleClient,rectangle,eside);
                     
                     pgraphics->fill_rectangle(rectangle, ::color::color(crMoveableBorder,127));

                  }

               }
               else if(m_pframewindow->m_estyle == ::user::StyleTranslucidWarmGray
                       || m_pframewindow->m_estyle == ::user::StyleTranslucidLightBlue
                       || m_pframewindow->m_estyle == ::user::StyleTranslucidLightGreen)
               {
                  
                  ::rectangle_i32 rectangle;
                  
                  GetBorderRect(rectangleClient, rectangle, eside);
                  
                  pgraphics->fill_rectangle(rectangle, ::color::color(crMoveableBorder, 127));
                  
               }
               else
               {
                  
                  ::rectangle_i32 rectangle;
                  
                  GetBorderRect(rectangleClient, rectangle, eside);
                  
                  pgraphics->fill_rectangle(rectangle, ::color::color(crMoveableBorder,127));

                  ::rectangle_i32 rectClientB = rectA;

                  rectClientB.bottom--;
                  rectClientB.right--;

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

            void frame_008::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
            {

               auto pframewindow = m_pframewindow;

               if (pframewindow == nullptr)
               {

                  return;

               }

               if (!pframewindow->is_frame_experience_enabled())
               {

                  return;

               }

               bool bZoomed = pframewindow->layout().is_zoomed() != 0;

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

               //            pgraphics->SetBkMode(iOriginalBkMode);
               //          pgraphics->set_text_color(crOriginalTextColor);

            }


            void frame_008::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient)
            {

               // glxxx
               //return;

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



               if(m_bHollow && eborder == e_border_all)
               {



                  ::rectangle_i32 rectA(rectangleClient);

                  rectA.bottom--;
                  rectA.right--;

                  pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

                  pgraphics->set(m_penHollow0);
                  pgraphics->draw_rectangle(rectA);

                  //Draw3dRectSide(pgraphics,rectA,eside,argb(8,50,100,200),argb(8,50,100,200));
                  rectA.deflate(1,1,1,1);

                  pgraphics->set(m_penHollow1);
                  pgraphics->draw_rectangle(rectA);

                  //Draw3dRectSide(pgraphics,rectA,eside,argb(11,50,100,200),argb(11,50,100,200));
                  rectA.deflate(1,1,1,1);

                  pgraphics->set(m_penHollow2);
                  pgraphics->draw_rectangle(rectA);

                  //Draw3dRectSide(pgraphics,rectA,eside,argb(23,50,100,200),argb(23,50,100,200));
                  rectA.deflate(1,1,1,1);

                  pgraphics->set(m_penHollow3);
                  pgraphics->draw_rectangle(rectA);

                  //Draw3dRectSide(pgraphics,rectA,eside,argb(49,50,100,200),argb(49,50,100,200));
                  rectA.deflate(1,1,1,1);

                  pgraphics->set(m_penHollow4);
                  pgraphics->draw_rectangle(rectA);

                  //Draw3dRectSide(pgraphics,rectA,eside,argb(49 +23,50,100,200),argb(49+23,50,100,200));
                  rectA.deflate(1,1,1,1);

                  pgraphics->set(m_penHollow5);
                  pgraphics->draw_rectangle(rectA);

                  //Draw3dRectSide(pgraphics,rectA,eside,m_colorMoveableBorderDkShadow,m_colorMoveableBorderDkShadow);

               }
               else
               {

                  if(eborder & e_border_top)
                  {
                     draw_border_side(pgraphics,rectangleClient,e_border_top);
                  }
                  if(eborder & e_border_right)
                  {
                     draw_border_side(pgraphics,rectangleClient,e_border_right);
                  }
                  if(eborder & e_border_bottom)
                  {
                     draw_border_side(pgraphics,rectangleClient,e_border_bottom);
                  }
                  if(eborder & e_border_left)
                  {
                     draw_border_side(pgraphics,rectangleClient,e_border_left);
                  }

               }

            }


            void frame_008::GetBorderRect(const ::rectangle_i32 & rectangleClient, RECTANGLE_I32 * lprect, enum_border eside)
            {
               ::rectangle_i32 rectBig(rectangleClient);

               rectBig.deflate(m_rectMarginDock);
               ::rectangle_i32 rectSmall(rectBig);
               rectSmall.deflate(1);

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
                  rectangle.bottom++;
               }
               else if(eside == e_border_right)
               {
                  rectangle.left = rectSmall.right;
                  rectangle.right = rectBig.right;
                  rectangle.top = rectSmall.top;
                  rectangle.bottom = rectSmall.bottom;
                  rectangle.bottom++;
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


            void frame_008::_on_style_change(::draw2d::graphics_pointer & pgraphics)
            {

               on_style_change_001_and_002(pgraphics);

               ::color::color color = m_colorMoveableBorderDkShadow;

               color.alpha = 8;
               m_penHollow0->create_solid(1.0,color);

               color.alpha = 11;
               m_penHollow1->create_solid(1.0,color);

               color.alpha = 23;
               m_penHollow2->create_solid(1.0,color);

               color.alpha = 49;
               m_penHollow3->create_solid(1.0,color);

               color.alpha = 72;
               m_penHollow4->create_solid(1.0, color);

               color.alpha = 255;
               m_penHollow5->create_solid(1.0,color);


            }

#define BEVEL_SMALL 2
#define BEVEL_LARGE 5
#define GRIP_SMALL 8
#define GRIP_LARGE 30


            void frame_008::DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClientParam, enum_grip egrip)
            {

               // glxxx
               //return;


               const i32 size = 16;

               auto rectangleClient(rectClientParam);
               //            ::rectangle_i32 rectClientB(rectangleClient);
               ::rectangle_i32 rectA;
               ::point_i32 pointA;
               ::point_i32 pointB;
               ::point_i32 pointC;
               //            ::rectangle_i32 rectangle(rectangleClient);
               switch(egrip)
               {
               case e_grip_top_left:
               {

                  rectA = rectangleClient;

                  rectA.right = 4;
                  rectA.bottom = size;

                  pgraphics->fill_rectangle(rectA, argb(255, 0x60, 0x65, 0x55));

                  rectA.right = size;
                  rectA.bottom = 4;

                  pgraphics->fill_rectangle(rectA, argb(255, 0x60, 0x65, 0x55));

               }
               break;
               case e_grip_top_right:
               {
                  rectA = rectangleClient;

                  rectA.left = rectA.right - 4;
                  rectA.bottom = size;

                  pgraphics->fill_rectangle(rectA, argb(255, 0x60, 0x65, 0x55));

                  rectA.left = rectA.right - size;
                  rectA.bottom = 4;

                  pgraphics->fill_rectangle(rectA, argb(255, 0x60, 0x65, 0x55));
               }
               break;
               case e_grip_bottom_left:
               {
                  rectA = rectangleClient;

                  rectA.right = 4;
                  rectA.top = rectA.bottom - size;

                  pgraphics->fill_rectangle(rectA, argb(255, 0x60, 0x65, 0x55));

                  rectA.right = size;
                  rectA.top = rectA.bottom - 4;

                  pgraphics->fill_rectangle(rectA, argb(255, 0x60, 0x65, 0x55));
               }
               break;
               case e_grip_bottom_right:
               {
                  rectA = rectangleClient;

                  rectA.left = rectA.right - 4;
                  rectA.top = rectA.bottom - size;

                  pgraphics->fill_rectangle(rectA, argb(255, 0x60, 0x65, 0x55));

                  rectA.left = rectA.right - size;
                  rectA.top = rectA.bottom - 4;

                  pgraphics->fill_rectangle(rectA, argb(255, 0x60, 0x65, 0x55));
               }
               break;
               case e_grip_top:
               {
                  rectA = rectangleClient;

                  rectA.left = rectA.left + rectA.width() / 2 - size / 2;
                  rectA.right = rectA.left + size;
                  rectA.bottom = 4;

                  pgraphics->fill_rectangle(rectA, argb(255, 0x60, 0x65, 0x55));

               }
               break;
               case e_grip_bottom:
               {
                  rectA = rectangleClient;

                  rectA.left = rectA.left + rectA.width() / 2 - size / 2;
                  rectA.right = rectA.left + size;
                  rectA.top = rectA.bottom - 4;

                  pgraphics->fill_rectangle(rectA, argb(255, 0x60, 0x65, 0x55));
               }
               break;
               case e_grip_left:
               {
                  rectA = rectangleClient;

                  rectA.right = 4;
                  rectA.top = rectA.top + rectA.height() / 2 - size / 2;
                  rectA.bottom = rectA.top + size;

                  pgraphics->fill_rectangle(rectA, argb(255, 0x60, 0x65, 0x55));
               }
               break;
               case e_grip_right:
               {
                  rectA = rectangleClient;

                  rectA.left = rectA.right - 4;
                  rectA.top = rectA.top + rectA.height() / 2 - size / 2;
                  rectA.bottom = rectA.top + size;

                  pgraphics->fill_rectangle(rectA, argb(255, 0x60, 0x65, 0x55));
               }
               break;
               default:
                  break;
               }


            }


            void frame_008::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectParam)
            {

               //auto psession = get_session();

               ::rectangle_i32 rectangle(rectParam);

               auto pframewindow = m_pframewindow;

               auto pstyle = pframewindow->get_style(pgraphics);

               auto crButtonHilite = pframewindow->get_color(pstyle, ::e_element_button_hilite);

               auto crButtonDarkShadow = pframewindow->get_color(pstyle, ::e_element_button_dark_shadow);

               auto crButtonFace = pframewindow->get_color(pstyle, ::e_element_button_background);

               auto crButtonShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

               pgraphics->draw_inset_3drect(rectangle, crButtonFace, crButtonDarkShadow);

               rectangle.top++;
               rectangle.bottom--;
               rectangle.left++;
               rectangle.right--;

               pgraphics->draw_inset_3drect(rectangle, crButtonHilite, crButtonShadow);

               rectangle.top++;
               rectangle.bottom--;
               rectangle.left++;
               rectangle.right--;

               pgraphics->fill_rectangle(rectangle, crButtonFace);

            }


            void frame_008::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient)
            {

               auto psizenager = m_pframewindow->size_manager();

               enum_grip egrip = psizenager->GetGripMask();

               if(egrip & e_grip_top)
               {
                  DrawGrip(pgraphics, rectangleClient, e_grip_top);
               }
               if((egrip & e_grip_top_right) == e_grip_top_right)
               {
                  DrawGrip(pgraphics, rectangleClient, e_grip_top_right);
               }
               if(egrip & e_grip_right)
               {
                  DrawGrip(pgraphics, rectangleClient, e_grip_right);
               }
               if((egrip & e_grip_bottom_right) == e_grip_bottom_right)
               {
                  DrawGrip(pgraphics, rectangleClient, e_grip_bottom_right);
               }
               if(egrip & e_grip_bottom)
               {
                  DrawGrip(pgraphics, rectangleClient, e_grip_bottom);
               }
               if((egrip & e_grip_bottom_left) == e_grip_bottom_left)
               {
                  DrawGrip(pgraphics, rectangleClient, e_grip_bottom_left);
               }
               if(egrip & e_grip_left)
               {
                  DrawGrip(pgraphics, rectangleClient, e_grip_left);
               }
               if((egrip & e_grip_top_left) == e_grip_top_left)
               {
                  DrawGrip(pgraphics, rectangleClient, e_grip_top_left);
               }

            }




   } // namespace core


} // namespace experience



