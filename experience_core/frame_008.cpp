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


         namespace aura
         {


            frame_008::frame_008()
            {

               m_bHollow = false;

               m_strStyle = "TranslucidWarmLiteGray";

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



            e_hittest frame_008::_001HitTest(const ::point & pointCursor)
            {
               e_hittest etest = hittest_client;
               {
                  //      m_pframewindow->_001ScreenToClient(point);
                  ::rect rectEvent;
                  m_pframewindow->get_window_rect(rectEvent);
                  ::rect rect;
                  ::point pointCenter = rectEvent.center();
                  e_grip egrip = m_pframewindow->size_manager()->GetGripMask();

                  ::point pointHitTest = pointCursor;

                  //if(rectEvent.left < 0)
                  // pointHitTest.x -= rectEvent.left;
                  //if(rectEvent.top < 0)
                  // pointHitTest.y -= rectEvent.top;

                  if((egrip & grip_top_left) == grip_top_left)
                  {
                     rect = rectEvent;
                     rect.right = rect.left + 16;
                     rect.bottom = rect.top + 5;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_top_left;
                        goto SizingSuccess;
                     }
                     rect = rectEvent;
                     rect.right = rect.left + 5;
                     rect.bottom = rect.top + 16;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_top_left;
                        goto SizingSuccess;
                     }
                  }
                  if((egrip & grip_top_right) == grip_top_right)
                  {
                     rect = rectEvent;
                     rect.left = rect.right - 16;
                     rect.bottom = rect.top + 5;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_top_right;
                        goto SizingSuccess;
                     }
                     rect = rectEvent;
                     rect.left = rect.right - 5;
                     rect.bottom = rect.top + 16;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_top_right;
                        goto SizingSuccess;
                     }
                  }
                  if((egrip & grip_bottom_right) == grip_bottom_right)
                  {
                     rect = rectEvent;
                     rect.left = rect.right - 16;
                     rect.top = rect.bottom - 5;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_bottom_right;
                        goto SizingSuccess;
                     }
                     rect = rectEvent;
                     rect.left = rect.right - 5;
                     rect.top = rect.bottom - 16;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_bottom_right;
                        goto SizingSuccess;
                     }
                  }
                  if((egrip & grip_bottom_left) == grip_bottom_left)
                  {
                     rect = rectEvent;
                     rect.right = rect.left + 16;
                     rect.top = rect.bottom - 5;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_bottom_left;
                        goto SizingSuccess;
                     }
                     rect = rectEvent;
                     rect.right = rect.left + 5;
                     rect.top = rect.bottom - 16;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_bottom_left;
                        goto SizingSuccess;
                     }
                  }
                  if((egrip & grip_top) == grip_top)
                  {
                     rect.top = rectEvent.top;
                     rect.left = pointCenter.x - 8;
                     rect.right = pointCenter.x + 8;
                     rect.bottom = rectEvent.top + 5;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_top;
                        goto SizingSuccess;
                     }
                  }
                  if((egrip & grip_bottom) == grip_bottom)
                  {
                     rect.top = rectEvent.bottom - 5;
                     rect.left = pointCenter.x - 8;
                     rect.right = pointCenter.x + 8;
                     rect.bottom = rectEvent.bottom;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_bottom;
                        goto SizingSuccess;
                     }
                  }
                  if((egrip & grip_left) == grip_left)
                  {
                     rect.top = pointCenter.y - 8;
                     rect.left = rectEvent.left;
                     rect.right = rectEvent.left + 5;
                     rect.bottom = pointCenter.y + 8;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_left;
                        goto SizingSuccess;
                     }
                  }
                  if((egrip & grip_right) == grip_right)
                  {
                     rect.top = pointCenter.y - 8;
                     rect.left = rectEvent.right - 5;
                     rect.right = rectEvent.right;
                     rect.bottom = pointCenter.y + 8;
                     if(rect.contains(pointHitTest))
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






            void frame_008::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient, e_border eside)
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

               if(pframewindow->is_active())
               {
                  crMoveableBorder = m_crMoveableBorder;
                  crMoveableBorderHilight = m_crMoveableBorderHilight;
                  crMoveableBorderShadow = m_crMoveableBorderShadow;
               }
               else
               {

                  auto pstyle = pframewindow->get_style(pgraphics);

                  crMoveableBorder = pframewindow->get_color(pstyle, ::user::element_button_background);

                  crMoveableBorderHilight = pframewindow->get_color(pstyle, ::user::element_button_hilite);

                  crMoveableBorderShadow = pframewindow->get_color(pstyle, ::user::element_button_shadow);

               }

               e_dock edock = m_pframewindow->dock_manager()->get_dock_mask();
               ::rect rectA(rectClient);

               if(m_bHollow)
               {

                  ::rect rect;
                  GetBorderRect(rectA, rect, eside);

                  pgraphics->fill_rect(rect, A_RGB(255, crMoveableBorder));//m_crMoveableBorderDkShadow);

                  // RGB(255, 170, 136) RedOrange
               }
               else if(m_estyle == StyleLightBlue || m_estyle == StyleRedOrange)
               {
                  rectA.deflate(1,1,1,1);
                  Draw3dRectSide(pgraphics,rectA,eside,crMoveableBorder,0);//m_crMoveableBorderDkShadow);

                  if(!m_bHollow)
                  {

                     rectA.deflate(1,1,1,1);
                     Draw3dRectSide(pgraphics,rectA,eside,crMoveableBorderHilight,crMoveableBorderShadow);

                     rectA.deflate(1,1,1,1);
                     Draw3dRectSide(pgraphics,rectA,eside,crMoveableBorder,crMoveableBorder);

                     rectA.deflate(1,1,1,1);
                     Draw3dRectSide(pgraphics,rectA,eside,crMoveableBorder,crMoveableBorder);

                     ::rect rect;
                     GetBorderRect(rectClient,rect,eside);
                     class imaging & imaging = System.imaging();
                     imaging.color_blend(pgraphics,
                                         rect,
                                         crMoveableBorder,
                                         127);

                  }

               }
               else if(m_estyle == StyleTranslucidWarmGray
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
               else
               {
                  ::rect rect;
                  GetBorderRect(rectClient, rect, eside);
                  class imaging & imaging = System.imaging();
                  imaging.color_blend(pgraphics,
                                      rect,
                                      crMoveableBorder,
                                      127);

                  ::rect rectClientB = rectA;

                  rectClientB.bottom--;
                  rectClientB.right--;

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  if(edock == dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectA, eside, m_crDkShadow, m_crDkShadow);
                  }

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  Draw3dRectSide(pgraphics, rectA, eside, m_crDkShadow, m_crDkShadow);

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  if(edock == dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectA, eside, m_crDkShadow, m_crDkShadow);
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

               //            pgraphics->SetBkMode(iOriginalBkMode);
               //          pgraphics->set_text_color(crOriginalTextColor);

            }


            void frame_008::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient)
            {

               // glxxx
               //return;

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



               if(m_bHollow && eborder == border_all)
               {



                  ::rect rectA(rectClient);

                  rectA.bottom--;
                  rectA.right--;

                  pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

                  pgraphics->set(m_penHollow0);
                  pgraphics->draw_rect(rectA);

                  //Draw3dRectSide(pgraphics,rectA,eside,ARGB(8,50,100,200),ARGB(8,50,100,200));
                  rectA.deflate(1,1,1,1);

                  pgraphics->set(m_penHollow1);
                  pgraphics->draw_rect(rectA);

                  //Draw3dRectSide(pgraphics,rectA,eside,ARGB(11,50,100,200),ARGB(11,50,100,200));
                  rectA.deflate(1,1,1,1);

                  pgraphics->set(m_penHollow2);
                  pgraphics->draw_rect(rectA);

                  //Draw3dRectSide(pgraphics,rectA,eside,ARGB(23,50,100,200),ARGB(23,50,100,200));
                  rectA.deflate(1,1,1,1);

                  pgraphics->set(m_penHollow3);
                  pgraphics->draw_rect(rectA);

                  //Draw3dRectSide(pgraphics,rectA,eside,ARGB(49,50,100,200),ARGB(49,50,100,200));
                  rectA.deflate(1,1,1,1);

                  pgraphics->set(m_penHollow4);
                  pgraphics->draw_rect(rectA);

                  //Draw3dRectSide(pgraphics,rectA,eside,ARGB(49 +23,50,100,200),ARGB(49+23,50,100,200));
                  rectA.deflate(1,1,1,1);

                  pgraphics->set(m_penHollow5);
                  pgraphics->draw_rect(rectA);

                  //Draw3dRectSide(pgraphics,rectA,eside,m_crMoveableBorderDkShadow,m_crMoveableBorderDkShadow);

               }
               else
               {

                  if(eborder & border_top)
                  {
                     draw_border_side(pgraphics,rectClient,border_top);
                  }
                  if(eborder & border_right)
                  {
                     draw_border_side(pgraphics,rectClient,border_right);
                  }
                  if(eborder & border_bottom)
                  {
                     draw_border_side(pgraphics,rectClient,border_bottom);
                  }
                  if(eborder & border_left)
                  {
                     draw_border_side(pgraphics,rectClient,border_left);
                  }

               }

            }


            void frame_008::GetBorderRect(const ::rect & rectClient, LPRECT32 lprect, e_border eside)
            {
               ::rect rectBig(rectClient);

               rectBig.deflate(m_rectMarginDock);
               ::rect rectSmall(rectBig);
               rectSmall.deflate(1);

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
                  rect.bottom++;
               }
               else if(eside == border_right)
               {
                  rect.left = rectSmall.right;
                  rect.right = rectBig.right;
                  rect.top = rectSmall.top;
                  rect.bottom = rectSmall.bottom;
                  rect.bottom++;
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


            void frame_008::on_style_change()
            {

               on_style_change_001_and_002();

               ::color color = m_crMoveableBorderDkShadow;

               color.m_iA = 8;
               m_penHollow0->create_solid(1.0,color);

               color.m_iA = 11;
               m_penHollow1->create_solid(1.0,color);

               color.m_iA = 23;
               m_penHollow2->create_solid(1.0,color);

               color.m_iA = 49;
               m_penHollow3->create_solid(1.0,color);

               color.m_iA = 72;
               m_penHollow4->create_solid(1.0, color);

               color.m_iA = 255;
               m_penHollow5->create_solid(1.0,color);


            }

#define BEVEL_SMALL 2
#define BEVEL_LARGE 5
#define GRIP_SMALL 8
#define GRIP_LARGE 30


            void frame_008::DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClientParam, e_grip egrip)
            {

               // glxxx
               //return;


               const i32 size = 16;

               auto rectClient(rectClientParam);
               //            ::rect rectClientB(rectClient);
               ::rect rectA;
               ::point pointA;
               ::point pointB;
               ::point pointC;
               //            ::rect rect(rectClient);
               switch(egrip)
               {
               case grip_top_left:
               {

                  rectA = rectClient;

                  rectA.right = 4;
                  rectA.bottom = size;

                  pgraphics->fill_rect(rectA, ARGB(255, 0x60, 0x65, 0x55));

                  rectA.right = size;
                  rectA.bottom = 4;

                  pgraphics->fill_rect(rectA, ARGB(255, 0x60, 0x65, 0x55));

               }
               break;
               case grip_top_right:
               {
                  rectA = rectClient;

                  rectA.left = rectA.right - 4;
                  rectA.bottom = size;

                  pgraphics->fill_rect(rectA, ARGB(255, 0x60, 0x65, 0x55));

                  rectA.left = rectA.right - size;
                  rectA.bottom = 4;

                  pgraphics->fill_rect(rectA, ARGB(255, 0x60, 0x65, 0x55));
               }
               break;
               case grip_bottom_left:
               {
                  rectA = rectClient;

                  rectA.right = 4;
                  rectA.top = rectA.bottom - size;

                  pgraphics->fill_rect(rectA, ARGB(255, 0x60, 0x65, 0x55));

                  rectA.right = size;
                  rectA.top = rectA.bottom - 4;

                  pgraphics->fill_rect(rectA, ARGB(255, 0x60, 0x65, 0x55));
               }
               break;
               case grip_bottom_right:
               {
                  rectA = rectClient;

                  rectA.left = rectA.right - 4;
                  rectA.top = rectA.bottom - size;

                  pgraphics->fill_rect(rectA, ARGB(255, 0x60, 0x65, 0x55));

                  rectA.left = rectA.right - size;
                  rectA.top = rectA.bottom - 4;

                  pgraphics->fill_rect(rectA, ARGB(255, 0x60, 0x65, 0x55));
               }
               break;
               case grip_top:
               {
                  rectA = rectClient;

                  rectA.left = rectA.left + rectA.width() / 2 - size / 2;
                  rectA.right = rectA.left + size;
                  rectA.bottom = 4;

                  pgraphics->fill_rect(rectA, ARGB(255, 0x60, 0x65, 0x55));

               }
               break;
               case grip_bottom:
               {
                  rectA = rectClient;

                  rectA.left = rectA.left + rectA.width() / 2 - size / 2;
                  rectA.right = rectA.left + size;
                  rectA.top = rectA.bottom - 4;

                  pgraphics->fill_rect(rectA, ARGB(255, 0x60, 0x65, 0x55));
               }
               break;
               case grip_left:
               {
                  rectA = rectClient;

                  rectA.right = 4;
                  rectA.top = rectA.top + rectA.height() / 2 - size / 2;
                  rectA.bottom = rectA.top + size;

                  pgraphics->fill_rect(rectA, ARGB(255, 0x60, 0x65, 0x55));
               }
               break;
               case grip_right:
               {
                  rectA = rectClient;

                  rectA.left = rectA.right - 4;
                  rectA.top = rectA.top + rectA.height() / 2 - size / 2;
                  rectA.bottom = rectA.top + size;

                  pgraphics->fill_rect(rectA, ARGB(255, 0x60, 0x65, 0x55));
               }
               break;
               default:
                  break;
               }


            }


            void frame_008::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const ::rect & rectParam)
            {

               auto psession = Session;

               ::rect rect(rectParam);

               auto pframewindow = m_pframewindow;

               auto pstyle = pframewindow->get_style(pgraphics);

               auto crButtonHilite = pframewindow->get_color(pstyle, ::user::element_button_hilite);

               auto crButtonDarkShadow = pframewindow->get_color(pstyle, ::user::element_button_dark_shadow);

               auto crButtonFace = pframewindow->get_color(pstyle, ::user::element_button_background);

               auto crButtonShadow = pframewindow->get_color(pstyle, ::user::element_button_shadow);

               pgraphics->draw_3drect(rect, crButtonFace, crButtonDarkShadow);

               rect.top++;
               rect.bottom--;
               rect.left++;
               rect.right--;

               pgraphics->draw_3drect(rect, crButtonHilite, crButtonShadow);

               rect.top++;
               rect.bottom--;
               rect.left++;
               rect.right--;

               pgraphics->fill_rect(rect, crButtonFace);

            }


            void frame_008::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient)
            {

               auto psizenager = m_pframewindow->size_manager();

               e_grip egrip = psizenager->GetGripMask();

               if(egrip & grip_top)
               {
                  DrawGrip(pgraphics, rectClient, grip_top);
               }
               if((egrip & grip_top_right) == grip_top_right)
               {
                  DrawGrip(pgraphics, rectClient, grip_top_right);
               }
               if(egrip & grip_right)
               {
                  DrawGrip(pgraphics, rectClient, grip_right);
               }
               if((egrip & grip_bottom_right) == grip_bottom_right)
               {
                  DrawGrip(pgraphics, rectClient, grip_bottom_right);
               }
               if(egrip & grip_bottom)
               {
                  DrawGrip(pgraphics, rectClient, grip_bottom);
               }
               if((egrip & grip_bottom_left) == grip_bottom_left)
               {
                  DrawGrip(pgraphics, rectClient, grip_bottom_left);
               }
               if(egrip & grip_left)
               {
                  DrawGrip(pgraphics, rectClient, grip_left);
               }
               if((egrip & grip_top_left) == grip_top_left)
               {
                  DrawGrip(pgraphics, rectClient, grip_top_left);
               }

            }




   } // namespace aura


} // namespace experience



