#include "framework.h"


#define GRIP_CORNER_LARGE_CX 16
#define GRIP_CORNER_SMALL_CX 5
#define GRIP_CORNER_LARGE_CY 16
#define GRIP_CORNER_SMALL_CY 5


#define GRIP_CENTER_LARGE_CX 36
#define GRIP_CENTER_SMALL_CX 7
#define GRIP_CENTER_LARGE_CY 36
#define GRIP_CENTER_SMALL_CY 7


namespace user
{


   namespace experience
   {


      namespace frame
      {


         namespace experience_core
         {


            frame_008::frame_008(::object * pobject) :
               object(pobject),
               frame(pobject)
            {

               m_bHollow = false;

               set_style(StyleTranslucidWarmLiteGray);

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


            e_hittest frame_008::_001HitTest(point ptCursor)
            {
               e_hittest etest = hittest_client;
               {
                  //      m_pframewindow->GetEventWindow()->ScreenToClient(point);
                  ::rect rectEvent;
                  m_pframewindow->GetWindowRect(rectEvent);
                  ::rect rect;
                  point ptCenter = rectEvent.center();
                  e_grip egrip = m_pframewindow->size_manager()->GetGripMask();

                  ::point pointHitTest = ptCursor;

                  if(rectEvent.left < 0)
                     pointHitTest.x -= rectEvent.left;
                  if(rectEvent.top < 0)
                     pointHitTest.y -= rectEvent.top;

                  if(egrip & grip_top_left)
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
                  if(egrip & grip_top_right)
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
                  if(egrip & grip_bottom_right)
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
                  if(egrip & grip_bottom_left)
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
                  if(egrip & grip_top)
                  {
                     rect.top = rectEvent.top;
                     rect.left = ptCenter.x - 8;
                     rect.right = ptCenter.x + 8;
                     rect.bottom = rectEvent.top + 5;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_top;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_bottom)
                  {
                     rect.top = rectEvent.bottom - 5;
                     rect.left = ptCenter.x - 8;
                     rect.right = ptCenter.x + 8;
                     rect.bottom = rectEvent.bottom;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_bottom;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_left)
                  {
                     rect.top = ptCenter.y - 8;
                     rect.left = rectEvent.left;
                     rect.right = rectEvent.left + 5;
                     rect.bottom = ptCenter.y + 8;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_right)
                  {
                     rect.top = ptCenter.y - 8;
                     rect.left = rectEvent.right - 5;
                     rect.right = rectEvent.right;
                     rect.bottom = ptCenter.y + 8;
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






            void frame_008::draw_border_side(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient, e_border eside)
            {

               auto pframewindow = m_pframewindow;

               if(pappearance == nullptr)
                  return;

               COLORREF    crMoveableBorder;
               COLORREF    crMoveableBorderHilight;
               COLORREF    crMoveableBorderShadow;

               if(pappearance->m_fActive)
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

               e_dock edock = m_pframewindow->dock_manager()->GetDockState();
               ::rect rectA(lpcrectClient);

               if(m_bHollow)
               {

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
                     GetBorderRect(lpcrectClient,rect,eside);
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
                  GetBorderRect(lpcrectClient, rect, eside);
                  class imaging & imaging = System.imaging();
                  imaging.color_blend(pgraphics,
                                      rect,
                                      crMoveableBorder,
                                      127);
               }
               else
               {
                  ::rect rect;
                  GetBorderRect(lpcrectClient, rect, eside);
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

               if(pwndDraw == nullptr)
                  return;

               auto pframewindow = m_pframewindow;

               if(!pappearance->is_enabled())
                  return;

               auto pinteraction  = m_pframewindow->m_pframewindow->ui();

               bool bZoomed = pinteraction->window_is_zoomed() != 0;

               //    CVMSApp * pApp = (CVMSApp *) &System;
               //::aura::savings & savings = Session.savings();


               ::rect rectClient;
               pwndDraw->GetClientRect(rectClient);

               string str;


               ::rect rectNClient;

               pwndDraw->GetWindowRect(rectNClient);

               rectNClient -= rectNClient.top_left();

               ////////////////////
               //
               // Routine:
               // draw frame border
               //
               ////////////////////


               if(!pframewindow->window_is_full_screen())
               {
                  DrawBorder(pgraphics, rectNClient);
               }



               ///////////////////////
               //
               // Routine:
               // draw resize grip set
               //
               ///////////////////////

               if(!bZoomed && !pframewindow->window_is_full_screen())
               {
                  DrawGripSet(pgraphics, rectNClient);
               }

               //            pgraphics->SetBkMode(iOriginalBkMode);
               //          pgraphics->set_text_color(crOriginalTextColor);

            }


            void frame_008::DrawBorder(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient)
            {

               auto pmovemanager = m_pframewindow->move_manager();

               e_border eborder = pmovemanager->GetBorderMask();

               if(m_pframewindow->window_is_zoomed())
               {
                  eborder = (e_border)
                            (eborder &
                             ~(border_right
                               | border_bottom
                               | border_left));
               }



               if(m_bHollow)
               {



                  ::rect rectA(lpcrectClient);

                  rectA.bottom--;
                  rectA.right--;

                  pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

                  pgraphics->SelectObject(m_penHollow0);
                  pgraphics->DrawRect(rectA.left,rectA.top,rectA.right,rectA.bottom);

                  //Draw3dRectSide(pgraphics,rectA,eside,ARGB(8,50,100,200),ARGB(8,50,100,200));
                  rectA.deflate(1,1,1,1);

                  pgraphics->SelectObject(m_penHollow1);
                  pgraphics->DrawRect(rectA.left,rectA.top,rectA.right,rectA.bottom);

                  //Draw3dRectSide(pgraphics,rectA,eside,ARGB(11,50,100,200),ARGB(11,50,100,200));
                  rectA.deflate(1,1,1,1);

                  pgraphics->SelectObject(m_penHollow2);
                  pgraphics->DrawRect(rectA.left,rectA.top,rectA.right,rectA.bottom);

                  //Draw3dRectSide(pgraphics,rectA,eside,ARGB(23,50,100,200),ARGB(23,50,100,200));
                  rectA.deflate(1,1,1,1);

                  pgraphics->SelectObject(m_penHollow3);
                  pgraphics->DrawRect(rectA.left,rectA.top,rectA.right,rectA.bottom);

                  //Draw3dRectSide(pgraphics,rectA,eside,ARGB(49,50,100,200),ARGB(49,50,100,200));
                  rectA.deflate(1,1,1,1);

                  pgraphics->SelectObject(m_penHollow4);
                  pgraphics->DrawRect(rectA.left,rectA.top,rectA.right,rectA.bottom);

                  //Draw3dRectSide(pgraphics,rectA,eside,ARGB(49 +23,50,100,200),ARGB(49+23,50,100,200));
                  rectA.deflate(1,1,1,1);

                  pgraphics->SelectObject(m_penHollow5);
                  pgraphics->DrawRect(rectA.left,rectA.top,rectA.right,rectA.bottom);

                  //Draw3dRectSide(pgraphics,rectA,eside,m_crMoveableBorderDkShadow,m_crMoveableBorderDkShadow);

               }
               else
               {

                  if(eborder & border_top)
                  {
                     draw_border_side(pgraphics,lpcrectClient,border_top);
                  }
                  if(eborder & border_right)
                  {
                     draw_border_side(pgraphics,lpcrectClient,border_right);
                  }
                  if(eborder & border_bottom)
                  {
                     draw_border_side(pgraphics,lpcrectClient,border_bottom);
                  }
                  if(eborder & border_left)
                  {
                     draw_border_side(pgraphics,lpcrectClient,border_left);
                  }

               }

            }

            void frame_008::GetBorderRect(
            const RECT & lpcrectClient,
            LPRECT lprect,
            e_border eside)
            {
               ::rect rectBig(lpcrectClient);
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


            void frame_008::on_style_change()
            {

               on_style_change_001_and_002();

               m_penHollow0->create_solid(1.0,ARGB(8,50,100,200));
               m_penHollow1->create_solid(1.0,ARGB(11,50,100,200));
               m_penHollow2->create_solid(1.0,ARGB(23,50,100,200));
               m_penHollow3->create_solid(1.0,ARGB(49,50,100,200));
               m_penHollow4->create_solid(1.0,ARGB(49 + 23,50,100,200));
               m_penHollow5->create_solid(1.0,m_crMoveableBorderDkShadow);


            }

#define BEVEL_SMALL 2
#define BEVEL_LARGE 5
#define GRIP_SMALL 8
#define GRIP_LARGE 30

            void frame_008::DrawGrip(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient, e_grip egrip)
            {



               const i32 size = 16;

               ::rect rectClient(lpcrectClient);
               //            ::rect rectClientB(rectClient);
               ::rect rectA;
               point ptA;
               point ptB;
               point ptC;
               //            ::rect rect(rectClient);
               switch(egrip)
               {
               case grip_top_left:
               {

                  rectA = rectClient;

                  rectA.right = 4;
                  rectA.bottom = size;

                  pgraphics->FillSolidRect(rectA, ARGB(255, 0x60, 0x65, 0x55));

                  rectA.right = size;
                  rectA.bottom = 4;

                  pgraphics->FillSolidRect(rectA, ARGB(255, 0x60, 0x65, 0x55));

               }
               break;
               case grip_top_right:
               {
                  rectA = rectClient;

                  rectA.left = rectA.right - 4;
                  rectA.bottom = size;

                  pgraphics->FillSolidRect(rectA, ARGB(255, 0x60, 0x65, 0x55));

                  rectA.left = rectA.right - size;
                  rectA.bottom = 4;

                  pgraphics->FillSolidRect(rectA, ARGB(255, 0x60, 0x65, 0x55));
               }
               break;
               case grip_bottom_left:
               {
                  rectA = rectClient;

                  rectA.right = 4;
                  rectA.top = rectA.bottom - size;

                  pgraphics->FillSolidRect(rectA, ARGB(255, 0x60, 0x65, 0x55));

                  rectA.right = size;
                  rectA.top = rectA.bottom - 4;

                  pgraphics->FillSolidRect(rectA, ARGB(255, 0x60, 0x65, 0x55));
               }
               break;
               case grip_bottom_right:
               {
                  rectA = rectClient;

                  rectA.left = rectA.right - 4;
                  rectA.top = rectA.bottom - size;

                  pgraphics->FillSolidRect(rectA, ARGB(255, 0x60, 0x65, 0x55));

                  rectA.left = rectA.right - size;
                  rectA.top = rectA.bottom - 4;

                  pgraphics->FillSolidRect(rectA, ARGB(255, 0x60, 0x65, 0x55));
               }
               break;
               case grip_top:
               {
                  rectA = rectClient;

                  rectA.left = rectA.left + rectA.width() / 2 - size / 2;
                  rectA.right = rectA.left + size;
                  rectA.bottom = 4;

                  pgraphics->FillSolidRect(rectA, ARGB(255, 0x60, 0x65, 0x55));

               }
               break;
               case grip_bottom:
               {
                  rectA = rectClient;

                  rectA.left = rectA.left + rectA.width() / 2 - size / 2;
                  rectA.right = rectA.left + size;
                  rectA.top = rectA.bottom - 4;

                  pgraphics->FillSolidRect(rectA, ARGB(255, 0x60, 0x65, 0x55));
               }
               break;
               case grip_left:
               {
                  rectA = rectClient;

                  rectA.right = 4;
                  rectA.top = rectA.top + rectA.height() / 2 - size / 2;
                  rectA.bottom = rectA.top + size;

                  pgraphics->FillSolidRect(rectA, ARGB(255, 0x60, 0x65, 0x55));
               }
               break;
               case grip_right:
               {
                  rectA = rectClient;

                  rectA.left = rectA.right - 4;
                  rectA.top = rectA.top + rectA.height() / 2 - size / 2;
                  rectA.bottom = rectA.top + size;

                  pgraphics->FillSolidRect(rectA, ARGB(255, 0x60, 0x65, 0x55));
               }
               break;
               default:
                  break;
               }


            }

            void frame_008::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const RECT & rectParam)
            {



               ::rect rect(rectParam);

               pgraphics->Draw3dRect(rect, Session.get_default_color(COLOR_BTNFACE), Session.get_default_color(COLOR_3DDKSHADOW));

               rect.top++;
               rect.bottom--;
               rect.left++;
               rect.right--;

               pgraphics->Draw3dRect(rect, Session.get_default_color(COLOR_BTNHILIGHT), Session.get_default_color(COLOR_BTNSHADOW));

               rect.top++;
               rect.bottom--;
               rect.left++;
               rect.right--;

               pgraphics->FillSolidRect(rect, Session.get_default_color(COLOR_BTNFACE));

            }


            void frame_008::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient)
            {

               size_manager * psizenager = m_pframewindow->size_manager();

               e_grip egrip = psizenager->GetGripMask();

               if(egrip & grip_top)
               {
                  DrawGrip(pgraphics, lpcrectClient, grip_top);
               }
               if(egrip & grip_top_right)
               {
                  DrawGrip(pgraphics, lpcrectClient, grip_top_right);
               }
               if(egrip & grip_right)
               {
                  DrawGrip(pgraphics, lpcrectClient, grip_right);
               }
               if(egrip & grip_bottom_right)
               {
                  DrawGrip(pgraphics, lpcrectClient, grip_bottom_right);
               }
               if(egrip & grip_bottom)
               {
                  DrawGrip(pgraphics, lpcrectClient, grip_bottom);
               }
               if(egrip & grip_bottom_left)
               {
                  DrawGrip(pgraphics, lpcrectClient, grip_bottom_left);
               }
               if(egrip & grip_left)
               {
                  DrawGrip(pgraphics, lpcrectClient, grip_left);
               }
               if(egrip & grip_top_left)
               {
                  DrawGrip(pgraphics, lpcrectClient, grip_top_left);
               }

            }


         } // namespace experience_core


      } // namespace frame


   } // namespace experience


} // namespace user




















































