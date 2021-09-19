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


            }


            frame_008::~frame_008()
            {

            }


            string frame_008::get_default_user_style() const
            {

               return "TranslucidWarmLiteGray";

            }


            e_hittest frame_008::_001HitTest(const ::point_i32 & pointCursor)
            {
               e_hittest etest = hittest_client;
               {
                  //      m_pframewindow->GetEventWindow()->screen_to_client(point);
                  ::rectangle_i32 rectEvent;
                  m_pframewindow->get_window_rect(rectEvent);
                  ::rectangle_i32 rectangle;
                  //::point_i32 pointCenter = rectEvent.center();
                  enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();

                  ::point_i32 pointHitTest = pointCursor;

                  if(rectEvent.left < 0)
                     pointHitTest.x -= rectEvent.left;
                  if(rectEvent.top < 0)
                     pointHitTest.y -= rectEvent.top;

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

                  //auto psession = get_session();

                  auto pstyle = pframewindow->get_style(pgraphics);

                  crMoveableBorder = pframewindow->get_color(pstyle, ::e_element_button_background);

                  crMoveableBorderHilight = pframewindow->get_color(pstyle, ::e_element_button_hilite);

                  crMoveableBorderShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

               }

               enum_dock edock = m_pframewindow->dock_manager()->get_dock_mask();
               ::rectangle_i32 rectA(rectangleClient);

               auto estyle = pframewindow->m_estyle;

               if(m_bHollow)
               {


               }
               else if(estyle == ::user::StyleLightBlue || estyle == ::user::StyleRedOrange)
               {

                  Draw3dRectSide(pgraphics, rectA, eside, color::black, color::black);

               }
               else if(estyle == ::user::StyleTranslucidWarmGray
                       || estyle == ::user::StyleTranslucidLightBlue
                       || estyle == ::user::StyleTranslucidLightGreen)
               {
                  ::rectangle_i32 rectangle;
                  GetBorderRect(rectangleClient, rectangle, eside);

                  //class imaging & imaging = psystem->imaging();
                  //imaging.color_blend(
                     pgraphics->fill_rectangle(
                                      rectangle,
                                      ::color::color(crMoveableBorder,
                                      0.5));
               }
               else
               {
                  ::rectangle_i32 rectangle;
                  GetBorderRect(rectangleClient, rectangle, eside);

                  //class imaging & imaging = psystem->imaging();
                  //imaging.color_blend(pgraphics,

                  pgraphics->fill_rectangle(
                                      rectangle,
                                      ::color::color(crMoveableBorder,
                                      127));

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

               if(!pframewindow->is_frame_experience_enabled())
                  return;

               ::rectangle_i32 rectangleClient;
               pframewindow->get_client_rect(rectangleClient);

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

               millis tickBorder;

               tickBorder.Now();

               if(!pframewindow->layout().is_full_screen())
               {
                  DrawBorder(pgraphics, rectNClient);
               }

               //printf("border draw frame_008 %dms", tickBorder.elapsed().m_i);

            }


            void frame_008::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient)

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

               auto rectMargin = get_margin_rect();

               auto pframewindow = m_pframewindow;

               auto estyle = pframewindow->m_estyle;

               if(m_bHollow)
               {
                  //return;
                  ::rectangle_i32 rectA(rectangleClient);


                  pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

                  pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);

                  auto iMaxBorder = rectMargin.max_dimension();

                  if (iMaxBorder > 0)
                  {

                     ::rectangle_i32 rectDeflate(
                        rectMargin.left / iMaxBorder,
                        rectMargin.top / iMaxBorder,
                        rectMargin.right / iMaxBorder,
                        rectMargin.bottom / iMaxBorder);

                     for (index i = 0; i < iMaxBorder; i++)
                     {

                        pgraphics->draw_inset_rectangle(rectA, argb(0, 0, 0, 0), eborder);

                        rectA.deflate(rectDeflate);

                     }

                     pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

                     pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

                     if (m_pframewindow->is_active_window())
                     {

                        ::rectangle_i32 rectA(rectangleClient);

                        for (index i = 0; i < iMaxBorder; i++)
                        {

                           ::draw2d::pen_pointer pen(e_create);

                           pen->create_solid(1.0, argb((byte) ((i+1) * 5), 0, 0, 0));
//                           pen->create_solid(1.0, argb(255, 0, 0, 0));

                           pgraphics->draw_round_rect(rectA, pen, (int)(10 - i), eborder);

                           rectA.deflate(rectDeflate);

                        }

                        //rectA.deflate(9, 9, 9, 9);

                        pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

                        pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);


                        if (estyle == ::user::StyleRedOrange)
                        {

                           pgraphics->draw_inset_rectangle(rectA, argb(255, 255, 170, 136), eborder);

                        }
                        else if (estyle == ::user::StyleLightGreen)
                        {

                           pgraphics->draw_inset_rectangle(rectA, argb(255, 128, 230, 150), eborder);

                        }
                        else
                        {

                           pgraphics->draw_inset_rectangle(rectA, argb(255, 0x07, 0x6D, 0x91), eborder);

                        }

                     }
                     else
                     {

                        //rectA.deflate(9, 9, 9, 9);
                        pgraphics->draw_inset_rectangle(rectA, argb(255, 128, 128, 128));

                     }

                  }


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

            void frame_008::GetBorderRect(
            const ::rectangle_i32 & rectangleClient,

            RECTANGLE_I32 * prectangle,

            enum_border eside)
            {
               ::rectangle_i32 rectBig(rectangleClient);

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
               *prectangle = rectangle;

            }


            void frame_008::_on_style_change(::draw2d::graphics_pointer & pgraphics)
            {

               m_penHollow1.create(this);
               m_penHollow2.create(this);
               m_penHollow3.create(this);
               m_penHollow4.create(this);
               m_penHollow5.create(this);


               on_style_change_001_and_002(pgraphics);
               
               auto pframewindow = m_pframewindow;

               auto estyle = pframewindow->m_estyle;

               if (estyle == ::user::StyleDarkRed)
               {
                  //m_penHollow1->create_solid(1.0, argb(20, 0, 0, 0));
                  //m_penHollow2->create_solid(1.0, argb(60, 20, 20, 20));
                  //m_penHollow3->create_solid(1.0, argb(100, 40, 40, 40));
                  //m_penHollow4->create_solid(1.0, argb(140, 60, 60, 60));
                  //m_penHollow5->create_solid(1.0, argb(255, 90, 220, 100));
                  m_colorCaptionTextBk = argb(255, 200, 200, 200);
                  m_colorActiveCaptionTextBk = argb(255, 165, 32, 32);
               }
               else if (estyle == ::user::StyleLightGreen)
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

               if (m_pcontrolbox.is_set())
               {

                  m_pcontrolbox->m_brushButtonBackSel = m_pcontrolbox->m_brushButtonBack;
                  m_pcontrolbox->m_penButtonBackSel = m_pcontrolbox->m_penButtonBack;
                  m_pcontrolbox->m_colorButtonForeSel = m_pcontrolbox->m_colorButtonFore;

               }

            }


            //color32_t frame_008::get_border_main_body_color()
            //{

            //   if (m_estyle == StyleRedOrange)
            //   {

            //      return argb(255, 255, 170, 136);

            //   }
            //   else
            //   {

            //      return argb(255, 50, 100, 200);

            //   }

            //}


            //bool frame_008::get_color(color32_t & color32, ::user::e_color ecolor, ::user::style_context * pstyle)
            //{

            //   return frame::get_color(color32, ecolor, pstyle);

            //}


         } // namespace tranquillum

   } // namespace experience



