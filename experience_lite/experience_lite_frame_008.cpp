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


            frame_008::frame_008(::object * pobject) :
               object(pobject),
               frame(pobject)
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


            e_hittest frame_008::_001HitTest(::point_i32 pointCursor)
            {
               e_hittest etest = hittest_client;
               {
                  //      m_pframewindow->GetEventWindow()->screen_to_client(point);
                  ::rectangle_i32 rectEvent;
                  m_pframewindow->get_window_rect(rectEvent);
                  ::rectangle_i32 rectangle;
                  //point_i32 ptCenter = rectEvent.center();
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
                     rectangle.left = rectEvent.left;
                     rectangle.right = rectEvent.right;
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
                     rectangle.left = rectEvent.left;
                     rectangle.right = rectEvent.right;
                     rectangle.bottom = rectEvent.bottom;
                     if(rectangle.contains(pointHitTest))
                     {
                        etest = hittest_sizing_bottom;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_left)
                  {
                     rectangle.top = rectEvent.top;
                     rectangle.left = rectEvent.left;
                     rectangle.right = rectEvent.left + 5;
                     rectangle.bottom = rectEvent.bottom;
                     if(rectangle.contains(pointHitTest))
                     {
                        etest = hittest_sizing_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_right)
                  {
                     rectangle.top = rectEvent.top;
                     rectangle.left = rectEvent.right - 5;
                     rectangle.right = rectEvent.right;
                     rectangle.bottom = rectEvent.bottom;
                     if(rectangle.contains(pointHitTest))
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






            void frame_008::draw_border_side(::draw2d::graphics_pointer & pgraphics, const RECTANGLE_I32 & lpcrectClient, enum_border eside)
            {

               auto pframewindow = m_pframewindow;

               if(pframewindow == nullptr)
                  return;

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

                  auto psession = get_session();

                  auto pstyle = pframewindow->get_style(pgraphics);

                  crMoveableBorder = pframewindow->get_color(pstyle, ::e_element_button_background);

                  crMoveableBorderHilight = pframewindow->get_color(pstyle, ::e_element_button_hilite);

                  crMoveableBorderShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

}

               enum_dock edock = m_pframewindow->dock_manager()->GetDockState();
               ::rectangle_i32 rectA(lpcrectClient);

               if(m_bHollow)
               {


               }
               else if(m_estyle == StyleLightBlue || m_estyle == StyleRedOrange)
               {
                  //rectA.deflate(1,1,1,1);
                  Draw3dRectSide(pgraphics,rectA,eside, crMoveableBorderHilight,0);//m_colorMoveableBorderDkShadow);

                  //if(!m_bHollow)
                  //{

                  //   rectA.deflate(1,1,1,1);
                  //   Draw3dRectSide(pgraphics,rectA,eside,crMoveableBorderHilight,crMoveableBorderShadow);

                  //   rectA.deflate(1,1,1,1);
                  //   Draw3dRectSide(pgraphics,rectA,eside,crMoveableBorder,crMoveableBorder);

                  //   rectA.deflate(1,1,1,1);
                  //   Draw3dRectSide(pgraphics,rectA,eside,crMoveableBorder,crMoveableBorder);

                  //   ::rectangle_i32 rectangle;
                  //   GetBorderRect(lpcrectClient,rectangle,eside);
                  //   class imaging & imaging = psystem->imaging();
                  //   imaging.color_blend(pgraphics,
                  //      rectangle,
                  //      crMoveableBorder,
                  //      127);

                  //}

               }
               else if(m_estyle == StyleTranslucidWarmGray
                       || m_estyle == StyleTranslucidLightBlue
                       || m_estyle == StyleTranslucidLightGreen)
               {
                  ::rectangle_i32 rectangle;
                  GetBorderRect(lpcrectClient, rectangle, eside);

                  pgraphics->color_blend(
                                      rectangle,
                                      crMoveableBorder,
                                      127);
               }
               else
               {
                  ::rectangle_i32 rectangle;
                  GetBorderRect(lpcrectClient, rectangle, eside);

                  pgraphics->color_blend(
                                      rectangle,
                                      crMoveableBorder,
                                      127);

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

               if(pframewindow == nullptr)
                  return;

               auto pframewindow = m_pframewindow;

               if(!pframewindow->is_frame_experience_enabled())
                  return;

               auto pframewindow = m_pframewindow;

               //bool bZoomed = pframewindow->layout().is_zoomed() != 0;

               //    CVMSApp * pApp = (CVMSApp *) System;
               //::aura::savings & savings = psession->savings();
               auto rectangleClient = pframewindow->get_client_rect();

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



            }


            void frame_008::DrawBorder(::draw2d::graphics_pointer & pgraphics, const RECTANGLE_I32 & lpcrectClient)
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



               if(m_bHollow)
               {
                  //return;
                  ::rectangle_i32 rectA(lpcrectClient);

                  pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

                  pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);

                  for (index i = 0; i < 9; i++)
                  {

                     pgraphics->draw3d_rect(rectA, argb(0, 0, 0, 0), argb(0, 0, 0, 0));

                     rectA.deflate(1, 1, 1, 1);

                  }

                  if (m_pframewindow->GetWndDraw()->is_active())
                  {

                     ::rectangle_i32 rectA(lpcrectClient);

                     pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

                     pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

                     for (index i = 0; i < 9; i++)
                     {

                        ::draw2d::pen_pointer pen(e_create);

                        pen->create_solid(1.0, argb((i+1) * 5, 0, 0, 0));

                        pgraphics->draw_round_rect(rectA, pen, (int) (10 - i));

                        rectA.deflate(1, 1, 1, 1);

                     }

                     //rectA.deflate(9, 9, 9, 9);

                     pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

                     pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);


                     if (m_estyle == StyleRedOrange)
                     {

                        pgraphics->draw3d_rect(rectA, argb(255, 255, 170, 136), argb(255, 255, 170, 136));

                     }
                     else if (m_estyle == StyleLightGreen)
                     {

                        pgraphics->draw3d_rect(rectA, argb(255, 128, 230, 150), argb(255, 128, 230, 150));

                     }
                     else
                     {

                        pgraphics->draw3d_rect(rectA, argb(255, 0x07, 0x6D, 0x91), argb(255, 0x07, 0x6D, 0x91));

                     }

                  }
                  else
                  {

                     //rectA.deflate(9, 9, 9, 9);
                     pgraphics->draw3d_rect(rectA, argb(255, 128, 128, 128), argb(255, 128, 128, 128));
                  }


               }
               else
               {

                  if(eborder & e_border_top)
                  {
                     draw_border_side(pgraphics,lpcrectClient,e_border_top);
                  }
                  if(eborder & e_border_right)
                  {
                     draw_border_side(pgraphics,lpcrectClient,e_border_right);
                  }
                  if(eborder & e_border_bottom)
                  {
                     draw_border_side(pgraphics,lpcrectClient,e_border_bottom);
                  }
                  if(eborder & e_border_left)
                  {
                     draw_border_side(pgraphics,lpcrectClient,e_border_left);
                  }

               }

            }

            void frame_008::GetBorderRect(
            const RECTANGLE_I32 & lpcrectClient,
            RECTANGLE_I32 * lprect,
            enum_border eside)
            {
               ::rectangle_i32 rectBig(lpcrectClient);
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


            void frame_008::on_style_change()
            {

               on_style_change_001_and_002(pgraphics);
               m_rectMarginNormal.set(10, 10, 10, 10);

               if (m_estyle == StyleDarkRed)
               {
                  //m_penHollow1->create_solid(1.0, argb(20, 0, 0, 0));
                  //m_penHollow2->create_solid(1.0, argb(60, 20, 20, 20));
                  //m_penHollow3->create_solid(1.0, argb(100, 40, 40, 40));
                  //m_penHollow4->create_solid(1.0, argb(140, 60, 60, 60));
                  //m_penHollow5->create_solid(1.0, argb(255, 90, 220, 100));
                  m_colorCaptionTextBk = argb(255, 200, 200, 200);
                  m_colorActiveCaptionTextBk = argb(255, 165, 32, 32);
                  create_color(::user::color_button_background, argb(255, 165, 32, 32));
                  create_color(::user::color_button_background_hover, argb(255, 195, 64, 64));
                  create_color(::user::color_button_background_press, argb(255, 208, 72, 72));

               }
               else if (m_estyle == StyleLightGreen)
               {
                  //m_penHollow1->create_solid(1.0, argb(20, 0, 0, 0));
                  //m_penHollow2->create_solid(1.0, argb(60, 20, 20, 20));
                  //m_penHollow3->create_solid(1.0, argb(100, 40, 40, 40));
                  //m_penHollow4->create_solid(1.0, argb(140, 60, 60, 60));
                  //m_penHollow5->create_solid(1.0, argb(255, 90, 220, 100));
                  m_colorCaptionTextBk = argb(255, 200, 200, 200);
                  m_colorActiveCaptionTextBk = argb(255, 140, 200, 160);
               }
               else
               {
                  m_colorCaptionTextBk = argb(255, 200, 200, 200);
                  m_colorActiveCaptionTextBk = argb(255, 0x07, 0x6D, 0x91);
                  //m_penHollow1->create_solid(1.0, argb(20, 50, 100, 200));
                  //m_penHollow2->create_solid(1.0, argb(60, 50, 100, 200));
                  //m_penHollow3->create_solid(1.0, argb(100, 50, 100, 200));
                  //m_penHollow4->create_solid(1.0, argb(140, 50, 100, 200));
                  //m_penHollow5->create_solid(1.0, argb(255, 50, 100, 200));
               }

               if (m_spcontrolbox.is_set())
               {

                  m_spcontrolbox->m_brushButtonBackSel = m_spcontrolbox->m_brushButtonBack;
                  m_spcontrolbox->m_penButtonBackSel = m_spcontrolbox->m_penButtonBack;
                  m_spcontrolbox->m_colorButtonForeSel = m_spcontrolbox->m_colorButtonFore;

               }

            }


            color32_t frame_008::get_border_main_body_color()
            {

               if (m_estyle == StyleRedOrange)
               {

                  return argb(255, 255, 170, 136);

               }
               else
               {

                  return argb(255, 50, 100, 200);

               }

            }


            bool frame_008::get_color(color32_t & color32, ::user::e_color ecolor, ::user::style_context * pcontext)
            {

               //if (m_estyle == StyleLightGreen)
               //{

               //   if (ecolor == ::user::color_face_lite)
               //   {

               //      color32 = argb(80, 160, 160, 160);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_text)
               //   {

               //      color32 = argb(200, 80, 80, 80);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_text_hover)
               //   {

               //      color32 = argb(200, 80, 80, 80);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_text_highlight)
               //   {

               //      color32 = argb(200, 80, 80, 80);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_background_hover)
               //   {

               //      color32 = argb(20, 0, 0, 0);

               //      return true;

               //   }

               //   return ::experience::frame::get_color(color32, ecolor, pcontext );

               //}
               //else // if (m_estyle != StyleLightGreen)
               //{

               //   if (ecolor == ::user::color_background)
               //   {

               //      color32 = argb(255, 255, 255, 255);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_list_background)
               //   {

               //      color32 = argb(255, 255, 255, 255);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_edit_background)
               //   {

               //      color32 = argb(255, 255, 255, 255);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_tree_background)
               //   {

               //      color32 = argb(255, 255, 255, 255);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_view_background)
               //   {

               //      color32 = argb(255, 255, 255, 255);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_scrollbar_background)
               //   {

               //      color32 = argb(255, 255, 255, 255);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_tab_layout_background)
               //   {

               //      color32 = argb(255, 255, 255, 255);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_tab_client_background)
               //   {

               //      color32 = argb(255, 0xF3, 0XF5, 0xF5);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_split_layout_background)
               //   {

               //      color32 = argb(255, 255, 255, 255);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_background_selected)
               //   {

               //      color32 = argb(255, 155, 185, 255);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_list_header)
               //   {

               //      color32 = argb(255, 255, 255, 255);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_list_header_background)
               //   {

               //      color32 = argb(255, 0x58, 0x5C, 0x5D);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_list_item_background)
               //   {

               //      color32 = argb(30, 0, 0, 0);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_list_header_separator)
               //   {

               //      color32 = 0;

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_toolbar_background)
               //   {

               //      color32 = argb(255, 0xF3, 0XF5, 0xF5);

               //      return true;


               //   }
               //   else if (ecolor == ::user::color_button_background_disabled)
               //   {

               //      color32 = argb(255, 128, 128, 128);

               //      return true;


               //   }
               //   else if (ecolor == ::user::color_button_background_hover)
               //   {

               //      if (m_estyle == StyleDarkRed)
               //      {
               //         color32 = argb(255, 205, 72, 72);
               //      }
               //      else
               //      {
               //         color32 = argb(255, 0x55, 0x99, 0xC2);

               //      }

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_button_background)
               //   {

               //      if (m_estyle == StyleDarkRed)
               //      {
               //         color32 = argb(255, 165, 32, 32);
               //      }
               //      else
               //      {
               //         color32 = argb(255, 0x30, 0x75, 0xA0);
               //      }


               //      return true;
               //   }
               //   else if (ecolor == ::user::color_button_background_press)
               //   {

               //      color32 = argb(255, 0x07, 0x6D, 0x91);

               //      return true;
               //   }
               //   else if (ecolor == ::user::color_button_text_disabled)
               //   {

               //      color32 = argb(255, 0xD0, 0xD0, 0xD0);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_button_text_hover)
               //   {

               //      color32 = argb(255, 255, 255, 255);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_button_text)
               //   {

               //      color32 = argb(255, 255, 255, 255);

               //      return true;

               //   }
               //   else if (ecolor == ::user::color_button_text_press)
               //   {

               //      color32 = argb(255, 255, 255, 255);

               //      return true;

               //   }

               //}

               return frame::get_color(color32, ecolor, pcontext);

            }


         } // namespace lite



      


   } // namespace experience























































