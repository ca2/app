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





         namespace tranquillum

         {


            frame_008::frame_008()
            {

               m_bHollow = false;

               set_style(StyleTranslucidWarmLiteGray);

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
                  //      m_pframewindow->GetEventWindow()->_001ScreenToClient(point);
                  ::rect rectEvent;
                  m_pframewindow->get_window_rect(rectEvent);
                  ::rect rect;
                  //::point pointCenter = rectEvent.center();
                  enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();

                  ::point pointHitTest = pointCursor;

                  if(rectEvent.left < 0)
                     pointHitTest.x -= rectEvent.left;
                  if(rectEvent.top < 0)
                     pointHitTest.y -= rectEvent.top;

                  if(egrip & e_grip_top_left)
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
                  if(egrip & e_grip_top_right)
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
                  if(egrip & e_grip_bottom_right)
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
                  if(egrip & e_grip_bottom_left)
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
                  if(egrip & e_grip_top)
                  {
                     rect.top = rectEvent.top;
                     rect.left = rectEvent.left;
                     rect.right = rectEvent.right;
                     rect.bottom = rectEvent.top + 5;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_top;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_bottom)
                  {
                     rect.top = rectEvent.bottom - 5;
                     rect.left = rectEvent.left;
                     rect.right = rectEvent.right;
                     rect.bottom = rectEvent.bottom;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_bottom;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_left)
                  {
                     rect.top = rectEvent.top;
                     rect.left = rectEvent.left;
                     rect.right = rectEvent.left + 5;
                     rect.bottom = rectEvent.bottom;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_right)
                  {
                     rect.top = rectEvent.top;
                     rect.left = rectEvent.right - 5;
                     rect.right = rectEvent.right;
                     rect.bottom = rectEvent.bottom;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_right;
                        goto SizingSuccess;
                     }
                  }
                  goto SizingNone;
SizingSuccess:
                  return etest;
SizingNone:
                  ;
               }
               return hittest_client;
            }






            void frame_008::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient, enum_border eside)

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

                  auto psession = Session;

                  auto pstyle = pframewindow->get_style(pgraphics);

                  crMoveableBorder = pframewindow->get_color(pstyle, ::user::e_element_button_background);

                  crMoveableBorderHilight = pframewindow->get_color(pstyle, ::user::e_element_button_hilite);

                  crMoveableBorderShadow = pframewindow->get_color(pstyle, ::user::e_element_button_shadow);

               }

               enum_dock edock = m_pframewindow->dock_manager()->get_dock_mask();
               ::rect rectA(rectClient);


               if(m_bHollow)
               {


               }
               else if(m_estyle == StyleLightBlue || m_estyle == StyleRedOrange)
               {
                  //rectA.deflate(1,1,1,1);
                  Draw3dRectSide(pgraphics,rectA,eside, crMoveableBorderHilight,0);//m_crMoveableBorderDkShadow);

                  //if(!m_bHollow)
                  //{

                  //   rectA.deflate(1,1,1,1);
                  //   Draw3dRectSide(pgraphics,rectA,eside,crMoveableBorderHilight,crMoveableBorderShadow);

                  //   rectA.deflate(1,1,1,1);
                  //   Draw3dRectSide(pgraphics,rectA,eside,crMoveableBorder,crMoveableBorder);

                  //   rectA.deflate(1,1,1,1);
                  //   Draw3dRectSide(pgraphics,rectA,eside,crMoveableBorder,crMoveableBorder);

                  //   ::rect rect;
                  //   GetBorderRect(rectClient,rect,eside);

                  //   class imaging & imaging = System.imaging();
                  //   imaging.color_blend(pgraphics,
                  //      rect,
                  //      crMoveableBorder,
                  //      127);

                  //}

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
                  if(edock == e_dock_none)
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
                  if(edock == e_dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectA, eside, m_crDkShadow, m_crDkShadow);
                  }
               }

            }

            void frame_008::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
            {

               auto pframewindow = m_pframewindow;

               if(pframewindow == nullptr)
                  return;

               if(!pframewindow->is_frame_experience_enabled())
                  return;

               ::rect rectClient;
               pframewindow->get_client_rect(rectClient);

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

               millis tickBorder;

               tickBorder.Now();

               if(!pframewindow->layout().is_full_screen())
               {
                  DrawBorder(pgraphics, rectNClient);
               }

               //printf("border draw frame_008 %dms", tickBorder.elapsed().m_i);

            }


            void frame_008::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient)

            {

               auto pmovemanager = m_pframewindow->move_manager();


               auto eborder = pmovemanager->GetBorderMask();

               //if(m_pframewindow->layout().is_zoomed())
               //{
               //   eborder = (enum_border)
               //             (eborder &
               //              ~(e_border_right
               //                | e_border_bottom
               //                | e_border_left));
               //}

               auto prectMargin = get_margin_rect();


               if(m_bHollow)
               {
                  //return;
                  ::rect rectA(rectClient);


                  pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

                  pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);

                  auto iMaxBorder = prectMargin->max_border();

                  if (iMaxBorder > 0)
                  {

                     ::rect rectDeflate(
                        prectMargin->left / iMaxBorder,
                        prectMargin->top / iMaxBorder,
                        prectMargin->right / iMaxBorder,
                        prectMargin->bottom / iMaxBorder);

                     for (index i = 0; i < iMaxBorder; i++)
                     {

                        pgraphics->draw_rect(rectA, ARGB(0, 0, 0, 0), eborder);

                        rectA.deflate(rectDeflate);

                     }

                     pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

                     pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

                     if (m_pframewindow->is_active())
                     {

                        ::rect rectA(rectClient);

                        for (index i = 0; i < iMaxBorder; i++)
                        {

                           ::draw2d::pen_pointer pen(e_create);

                           pen->create_solid(1.0, ARGB((i+1) * 5, 0, 0, 0));
//                           pen->create_solid(1.0, ARGB(255, 0, 0, 0));

                           pgraphics->draw_round_rect(rectA, pen, (int)(10 - i), eborder);

                           rectA.deflate(rectDeflate);

                        }

                        //rectA.deflate(9, 9, 9, 9);

                        pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

                        pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);


                        if (m_estyle == StyleRedOrange)
                        {

                           pgraphics->draw_rect(rectA, ARGB(255, 255, 170, 136), eborder);

                        }
                        else if (m_estyle == StyleLightGreen)
                        {

                           pgraphics->draw_rect(rectA, ARGB(255, 128, 230, 150), eborder);

                        }
                        else
                        {

                           pgraphics->draw_rect(rectA, ARGB(255, 0x07, 0x6D, 0x91), eborder);

                        }

                     }
                     else
                     {

                        //rectA.deflate(9, 9, 9, 9);
                        pgraphics->draw_rect(rectA, ARGB(255, 128, 128, 128));

                     }

                  }


               }
               else
               {

                  if(eborder & e_border_top)
                  {
                     draw_border_side(pgraphics,rectClient,e_border_top);

                  }
                  if(eborder & e_border_right)
                  {
                     draw_border_side(pgraphics,rectClient,e_border_right);

                  }
                  if(eborder & e_border_bottom)
                  {
                     draw_border_side(pgraphics,rectClient,e_border_bottom);

                  }
                  if(eborder & e_border_left)
                  {
                     draw_border_side(pgraphics,rectClient,e_border_left);

                  }

               }

            }

            void frame_008::GetBorderRect(
            const ::rect & rectClient,

            RECT32 * prect,

            enum_border eside)
            {
               ::rect rectBig(rectClient);

               ::rect rectSmall;
               get_window_client_rect(rectSmall);
               ::rect rect;
               if(eside == e_border_top)
               {
                  rect.left = rectBig.left;
                  rect.right = rectBig.right;
                  rect.top = rectBig.top;
                  rect.bottom = rectSmall.top;
               }
               else if(eside == e_border_left)
               {
                  rect.left = rectBig.left;
                  rect.right = rectSmall.left;
                  rect.top = rectSmall.top;
                  rect.bottom = rectSmall.bottom;
               }
               else if(eside == e_border_right)
               {
                  rect.left = rectSmall.right;
                  rect.right = rectBig.right;
                  rect.top = rectSmall.top;
                  rect.bottom = rectSmall.bottom;
               }
               else if(eside == e_border_bottom)
               {
                  rect.left = rectBig.left;
                  rect.right = rectBig.right;
                  rect.top = rectSmall.bottom;
                  rect.bottom = rectBig.bottom;
               }
               *prect = rect;

            }


            void frame_008::on_style_change()
            {

               on_style_change_001_and_002();
               m_rectMarginNormal.set(10, 10, 10, 10);

               if (m_estyle == StyleDarkRed)
               {
                  //m_penHollow1->create_solid(1.0, ARGB(20, 0, 0, 0));
                  //m_penHollow2->create_solid(1.0, ARGB(60, 20, 20, 20));
                  //m_penHollow3->create_solid(1.0, ARGB(100, 40, 40, 40));
                  //m_penHollow4->create_solid(1.0, ARGB(140, 60, 60, 60));
                  //m_penHollow5->create_solid(1.0, ARGB(255, 90, 220, 100));
                  m_crCaptionTextBk = ARGB(255, 200, 200, 200);
                  m_crActiveCaptionTextBk = ARGB(255, 165, 32, 32);
               }
               else if (m_estyle == StyleLightGreen)
               {
                  //m_penHollow1->create_solid(1.0, ARGB(20, 0, 0, 0));
                  //m_penHollow2->create_solid(1.0, ARGB(60, 20, 20, 20));
                  //m_penHollow3->create_solid(1.0, ARGB(100, 40, 40, 40));
                  //m_penHollow4->create_solid(1.0, ARGB(140, 60, 60, 60));
                  //m_penHollow5->create_solid(1.0, ARGB(255, 90, 220, 100));
                  m_crCaptionTextBk = ARGB(255, 200, 200, 200);
                  m_crActiveCaptionTextBk = ARGB(255, 140, 200, 160);
               }
               else
               {
                  m_crCaptionTextBk = ARGB(255, 200, 200, 200);
                  m_crActiveCaptionTextBk = ARGB(255, 0x07, 0x6D, 0x91);
                  //m_penHollow1->create_solid(1.0, ARGB(20, 50, 100, 200));
                  //m_penHollow2->create_solid(1.0, ARGB(60, 50, 100, 200));
                  //m_penHollow3->create_solid(1.0, ARGB(100, 50, 100, 200));
                  //m_penHollow4->create_solid(1.0, ARGB(140, 50, 100, 200));
                  //m_penHollow5->create_solid(1.0, ARGB(255, 50, 100, 200));
               }

               if (m_pcontrolbox.is_set())
               {

                  m_pcontrolbox->m_brushButtonBackSel = m_pcontrolbox->m_brushButtonBack;
                  m_pcontrolbox->m_penButtonBackSel = m_pcontrolbox->m_penButtonBack;
                  m_pcontrolbox->m_crButtonForeSel = m_pcontrolbox->m_crButtonFore;

               }

            }


            color32_t frame_008::get_border_main_body_color()
            {

               if (m_estyle == StyleRedOrange)
               {

                  return ARGB(255, 255, 170, 136);

               }
               else
               {

                  return ARGB(255, 50, 100, 200);

               }

            }


            //bool frame_008::get_color(color32_t & cr, ::user::e_color ecolor, ::user::style_context * pstyle)
            //{

            //   return frame::get_color(cr, ecolor, pstyle);

            //}


         } // namespace tranquillum

   } // namespace experience



