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


            frame_008::frame_008(::particle * pparticle) :
               object(pparticle),
               frame(pparticle)
            {

               m_bHollow = false;

               set_style(StyleTranslucidWarmLiteGray);

               m_ppenHollow1.create(this);
               m_ppenHollow2.create(this);
               m_ppenHollow3.create(this);
               m_ppenHollow4.create(this);
               m_ppenHollow5.create(this);

            }


            frame_008::~frame_008()
            {

            }


            e_hittest frame_008::_001HitTest(::point_i32 pointCursor)
            {
               e_hittest etest = ::experience::e_frame_client;
               {
                  //      m_pframewindow->GetEventWindow()->screen_to_client()(point);
                  ::rectangle_i32 rectangleEvent;
                  m_pframewindow->window_rectangle(rectangleEvent);
                  ::rectangle_i32 rectangle;
                  //point_i32 ptCenter = rectangleEvent.center();
                  enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();

                  ::point_i32 pointHitTest = pointCursor;

//                  if(rectangleEvent.left < 0)
//                     pointHitTest.x -= rectangleEvent.left;
//                  if(rectangleEvent.top < 0)
//                     pointHitTest.y -= rectangleEvent.top;

                  if(egrip & e_grip_top_left)
                  {
                     rectangle = rectangleEvent;
                     rectangle.right = rectangle.left + 16;
                     rectangle.bottom = rectangle.top + 5;
                     if(rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_top_left;
                        goto SizingSuccess;
                     }
                     rectangle = rectangleEvent;
                     rectangle.right = rectangle.left + 5;
                     rectangle.bottom = rectangle.top + 16;
                     if(rectangle.contains(pointHitTest))
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
                     if(rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_top_right;
                        goto SizingSuccess;
                     }
                     rectangle = rectangleEvent;
                     rectangle.left = rectangle.right - 5;
                     rectangle.bottom = rectangle.top + 16;
                     if(rectangle.contains(pointHitTest))
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
                     if(rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_bottom_right;
                        goto SizingSuccess;
                     }
                     rectangle = rectangleEvent;
                     rectangle.left = rectangle.right - 5;
                     rectangle.top = rectangle.bottom - 16;
                     if(rectangle.contains(pointHitTest))
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
                     if(rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_bottom_left;
                        goto SizingSuccess;
                     }
                     rectangle = rectangleEvent;
                     rectangle.right = rectangle.left + 5;
                     rectangle.top = rectangle.bottom - 16;
                     if(rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_bottom_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_top)
                  {
                     rectangle.top = rectangleEvent.top;
                     rectangle.left = rectangleEvent.left;
                     rectangle.right = rectangleEvent.right;
                     rectangle.bottom = rectangleEvent.top + 5;
                     if(rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_top;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_bottom)
                  {
                     rectangle.top = rectangleEvent.bottom - 5;
                     rectangle.left = rectangleEvent.left;
                     rectangle.right = rectangleEvent.right;
                     rectangle.bottom = rectangleEvent.bottom;
                     if(rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_bottom;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_left)
                  {
                     rectangle.top = rectangleEvent.top;
                     rectangle.left = rectangleEvent.left;
                     rectangle.right = rectangleEvent.left + 5;
                     rectangle.bottom = rectangleEvent.bottom;
                     if(rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & e_grip_right)
                  {
                     rectangle.top = rectangleEvent.top;
                     rectangle.left = rectangleEvent.right - 5;
                     rectangle.right = rectangleEvent.right;
                     rectangle.bottom = rectangleEvent.bottom;
                     if(rectangle.contains(pointHitTest))
                     {
                        etest = ::experience::e_frame_sizing_right;
                        goto SizingSuccess;
                     }
                  }
                  goto SizingNone;
SizingSuccess:
                  return etest;
SizingNone:
                  ;
               }
               return ::experience::e_frame_client;
            }






            void frame_008::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 &lpcrectClient, enum_border eside)
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
               ::rectangle_i32 rectangleA(lpcrectClient);

               if(m_bHollow)
               {


               }
               else if(m_estyle == StyleLightBlue || m_estyle == StyleRedOrange)
               {
                  //rectangleA.deflate(1,1,1,1);
                  Draw3dRectSide(pgraphics,rectangleA,eside, crMoveableBorderHilight,0);//m_colorMoveableBorderDkShadow);

                  //if(!m_bHollow)
                  //{

                  //   rectangleA.deflate(1,1,1,1);
                  //   Draw3dRectSide(pgraphics,rectangleA,eside,crMoveableBorderHilight,crMoveableBorderShadow);

                  //   rectangleA.deflate(1,1,1,1);
                  //   Draw3dRectSide(pgraphics,rectangleA,eside,crMoveableBorder,crMoveableBorder);

                  //   rectangleA.deflate(1,1,1,1);
                  //   Draw3dRectSide(pgraphics,rectangleA,eside,crMoveableBorder,crMoveableBorder);

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

                  ::rectangle_i32 rectangleClientB = rectangleA;

                  rectangleClientB.bottom--;
                  rectangleClientB.right--;

                  rectangleA.top++;
                  rectangleA.bottom--;
                  rectangleA.left++;
                  rectangleA.right--;
                  if(edock == e_dock_none)
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
                  if(edock == e_dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectangleA, eside, m_colorDkShadow, m_colorDkShadow);
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
               auto rectangleClient = pframewindow->client_rectangle();

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


               if(!pframewindow->layout().is_full_screen())
               {
                  DrawBorder(pgraphics, rectangleNClient);
               }



            }


            void frame_008::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 &lpcrectClient)
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
                  ::rectangle_i32 rectangleA(lpcrectClient);

                  pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

                  pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

                  for (index i = 0; i < 9; i++)
                  {

                     pgraphics->draw_inset_3d_rectangle(rectangleA, argb(0, 0, 0, 0), argb(0, 0, 0, 0));

                     rectangleA.deflate(1, 1, 1, 1);

                  }

                  if (m_pframewindow->GetWndDraw()->is_active())
                  {

                     ::rectangle_i32 rectangleA(lpcrectClient);

                     pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

                     pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

                     for (index i = 0; i < 9; i++)
                     {

                        auto ppen = __create < ::draw2d::pen > ();

                        ppen->create_solid(1.0, argb((i+1) * 5, 0, 0, 0));

                        pgraphics->draw_round_rect(rectangleA, pen, (int) (10 - i));

                        rectangleA.deflate(1, 1, 1, 1);

                     }

                     //rectangleA.deflate(9, 9, 9, 9);

                     pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

                     pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);


                     if (m_estyle == StyleRedOrange)
                     {

                        pgraphics->draw_inset_3d_rectangle(rectangleA, argb(255, 255, 170, 136), argb(255, 255, 170, 136));

                     }
                     else if (m_estyle == StyleLightGreen)
                     {

                        pgraphics->draw_inset_3d_rectangle(rectangleA, argb(255, 128, 230, 150), argb(255, 128, 230, 150));

                     }
                     else
                     {

                        pgraphics->draw_inset_3d_rectangle(rectangleA, argb(255, 0x07, 0x6D, 0x91), argb(255, 0x07, 0x6D, 0x91));

                     }

                  }
                  else
                  {

                     //rectangleA.deflate(9, 9, 9, 9);
                     pgraphics->draw_inset_3d_rectangle(rectangleA, argb(255, 128, 128, 128), argb(255, 128, 128, 128));
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
            const ::rectangle_i32 &lpcrectClient,
            RECTANGLE_I32 * lprect,
            enum_border eside)
            {
               ::rectangle_i32 rectangleBig(lpcrectClient);
               ::rectangle_i32 rectangleSmall;
               get_window_client_rect(rectangleSmall);
               ::rectangle_i32 rectangle;
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


            void frame_008::on_style_change()
            {

               on_style_change_001_and_002(pgraphics);
               m_rectangleMarginNormal.set(10, 10, 10, 10);

               if (m_estyle == StyleDarkRed)
               {
                  //m_ppenHollow1->create_solid(1.0, argb(20, 0, 0, 0));
                  //m_ppenHollow2->create_solid(1.0, argb(60, 20, 20, 20));
                  //m_ppenHollow3->create_solid(1.0, argb(100, 40, 40, 40));
                  //m_ppenHollow4->create_solid(1.0, argb(140, 60, 60, 60));
                  //m_ppenHollow5->create_solid(1.0, argb(255, 90, 220, 100));
                  m_colorCaptionTextBk = argb(255, 200, 200, 200);
                  m_colorActiveCaptionTextBk = argb(255, 165, 32, 32);
                  create_color(::user::color_button_background, argb(255, 165, 32, 32));
                  create_color(::user::color_button_background_hover, argb(255, 195, 64, 64));
                  create_color(::user::color_button_background_press, argb(255, 208, 72, 72));

               }
               else if (m_estyle == StyleLightGreen)
               {
                  //m_ppenHollow1->create_solid(1.0, argb(20, 0, 0, 0));
                  //m_ppenHollow2->create_solid(1.0, argb(60, 20, 20, 20));
                  //m_ppenHollow3->create_solid(1.0, argb(100, 40, 40, 40));
                  //m_ppenHollow4->create_solid(1.0, argb(140, 60, 60, 60));
                  //m_ppenHollow5->create_solid(1.0, argb(255, 90, 220, 100));
                  m_colorCaptionTextBk = argb(255, 200, 200, 200);
                  m_colorActiveCaptionTextBk = argb(255, 140, 200, 160);
               }
               else
               {
                  m_colorCaptionTextBk = argb(255, 200, 200, 200);
                  m_colorActiveCaptionTextBk = argb(255, 0x07, 0x6D, 0x91);
                  //m_ppenHollow1->create_solid(1.0, argb(20, 50, 100, 200));
                  //m_ppenHollow2->create_solid(1.0, argb(60, 50, 100, 200));
                  //m_ppenHollow3->create_solid(1.0, argb(100, 50, 100, 200));
                  //m_ppenHollow4->create_solid(1.0, argb(140, 50, 100, 200));
                  //m_ppenHollow5->create_solid(1.0, argb(255, 50, 100, 200));
               }

               if (m_spcontrolbox.is_set())
               {

                  m_spcontrolbox->m_pbrushButtonBackSel = m_spcontrolbox->m_pbrushButtonBack;
                  m_spcontrolbox->m_ppenButtonBackSel = m_spcontrolbox->m_ppenButtonBack;
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
               //   else if (ecolor == ::user::color_impact_background)
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























































