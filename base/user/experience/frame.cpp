#include "framework.h"
#include "frame.h"
#include "aura/graphics/draw2d/_component.h"
#include "base/platform/session.h"
#include "frame_window.h"
#include "control_box.h"
#include "size_manager.h"
#include "move_manager.h"
#include "dock_manager.h"
#include "aura/message/user.h"
#include "experience.h"
#include "aura/user/user/style.h"


namespace experience
{


   frame::frame()
   {

      m_bPendingStyleChange = false;

      m_bHollow = true;
      m_bFirstLayoutDone = false;

      m_rectangleCaptionTextPadding.left = 4;
      m_rectangleCaptionTextPadding.right = 4;
      m_rectangleCaptionTextPadding.top = 0;
      m_rectangleCaptionTextPadding.bottom = 0;


      m_rectangleMarginFullScreen.set(0, 0, 0, 0);
      m_rectangleMarginZoomed.set(0, 0, 0, 0);
      m_rectangleMarginNormal.set(5, 5, 5, 5);

      m_bControlBoxAlignRight = true;
      m_bInitialControlBoxPosition = true;

   }


   frame::~frame()
   {

   }


   ::base::application * frame::get_app() const 
   {
      
      return m_pcontext ? m_pcontext->m_pbaseapplication : nullptr; 
   
   }


   ::base::session * frame::get_session() const 
   {
      
      return m_pcontext ? m_pcontext->m_pbasesession : nullptr; 
   
   }


   ::base::system * frame::get_system() const 
   {
      
      return m_psystem ? m_psystem->m_pbasesystem : nullptr; 
   
   }


   ::base::user * frame::user() const 
   {
      
      return get_session() ? get_session()->user() : nullptr; 
   
   }


   int frame::adjust_client_height(int iHeight)
   {

      return iHeight + get_caption_height();

   }


   int frame::adjust_client_width(int iWidth)
   {

      return iWidth + 20;
      
   }


   void frame::OnMove(__pointer(::user::interaction) pframewindow)
   {

      __UNREFERENCED_PARAMETER(pframewindow);

   }


   void frame::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);

   }


   void frame::frame_on_attach()
   {

      //if (m_pframewindow)
      //{

      //   if (m_pframewindow->size_manager() != nullptr)
      //   {

      //      m_pframewindow->size_manager()->SetSWPFlags(0);

      //   }

      //}

   }


   void frame::frame_on_detach()
   {

   }


   bool frame::is_control_box_moveable()
   {

      return false;

   }


   size_i32 frame::GetMinSize()
   {

      return m_pframewindow->get_window_minimum_size();

   }


   void frame::OnNcCalcSize(RECTANGLE_I32 * prectangle)
   {

      if(m_pframewindow->m_bUseNc)
      {

         //calc_window_client_rect(prectangle,rectangle_i32(prectangle));


      }

   }


   void frame::OnActivate()
   {

   }


   //bool frame::_001OnCommand(WPARAM wparam, LPARAM lparam, LRESULT & lresult)
   //{

   //   __UNREFERENCED_PARAMETER(wparam);
   //   __UNREFERENCED_PARAMETER(lparam);

   //   __UNREFERENCED_PARAMETER(lresult);

   //   return false;

   //}


   void frame::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto pframewindow = m_pframewindow;

      synchronous_lock synchronouslock(pframewindow->mutex());

      ::rectangle_i32 rectangleClient;

      pframewindow->::user::interaction::get_client_rect(rectangleClient);

      if (rectangleClient.is_empty())
      {

         return;

      }

      if (m_pcontrolbox.is_set())
      {

         m_pcontrolbox->reset_layout(pgraphics);

      }

      m_iCaptionHeight = calc_caption_height(pgraphics);

      //::rectangle_i32 rectangleClient;

      title_bar_layout(pgraphics);

      update_window_client_rect();

      pframewindow->get_client_rect(rectangleClient);

      get_window_client_rect(rectangleClient);

      if (pframewindow != nullptr)
      {

         if (pframewindow->m_bSnapToBars)
         {

            ::rectangle_i32 rectangle(0, 0, 32767, 32767);

            pframewindow->RepositionBars(0, 0xffff, FIRST_PANE, pframewindow->reposQuery,
                                 &rectangle, &rectangle, false);
            rectangle.offset(rectangleClient.top_left());
            ::rectangle_i32 rectangleBorder;
            pframewindow->GetBorderRect(rectangleBorder);
            pframewindow->RepositionBars(0, 0xffff, FIRST_PANE, pframewindow->reposExtra,
                                 &rectangleBorder, &rectangle, true);
            pframewindow->SetBorderRect(rectangleBorder);
            //pframewindow->CalcWindowRect(&rectangle);
            OnNcCalcSize(&rectangle);
            //::rectangle_i32 rectangleSnap(0, 0, 0, 0);
            //CalcWndClient(rectangleSnap, rectangleSnap);
            //rectangle.deflate(rectangleSnap);
            pframewindow->set_size(rectangle.size());
            pframewindow->display();
//                  pframewindow->display();(zorder_none, 0, 0, rectangle.width(), rectangle.height(),
//                                     SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);

         }
         else
         {

            ::rectangle_i32 rectangleBorder;

            pframewindow->GetBorderRect(rectangleBorder);

            pframewindow->RepositionBars(0, 0xffff, FIRST_PANE, pframewindow->reposExtra, &rectangleBorder, &rectangleClient);

            pframewindow->SetBorderRect(rectangleBorder);

         }

      }

      if(get_control_box()->is_this_screen_visible())
      {

         get_control_box()->order(::e_zorder_top_most);

      }

      get_control_box()->set_need_layout();

   }


   void frame::on_reposition()
   {


   }


   status < ::color::color > frame::get_border_main_body_color()
   {

      return m_colorMoveableBorder;

   }


   bool frame::on_message_left_button_down(::message::mouse * pmouse)
   {

      if(!m_pframewindow->layout().is_zoomed() && !m_pframewindow->layout().is_full_screen())
      {

         if (m_pframewindow->size_manager()->on_message_left_button_down(pmouse))
         {

            return true;

         }

         if (m_pframewindow->move_manager()->on_message_left_button_down(pmouse))
         {

            return true;

         }

      }

      return false;

   }


   bool frame::on_message_left_button_up(::message::mouse * pmouse)
   {

      if(!m_pframewindow->layout().is_zoomed() && !m_pframewindow->layout().is_full_screen())
      {

//         if(m_pframewindow->dock_manager()->on_message_left_button_up(pmouse))
  //          return true;

         if(m_pframewindow->size_manager()->on_message_left_button_up(pmouse))
            return true;

         if(m_pframewindow->move_manager()->on_message_left_button_up(pmouse))
            return true;

      }

      return false;
   }


   bool frame::on_message_left_button_double_click(::message::mouse* pmouse)
   {

      auto ehittest = experience_frame_hit_test(pmouse->m_point);

      if (ehittest == ::experience::e_frame_client)
      {
         
         m_pframewindow->dock_manager()->cancel_docking();
         
         m_pframewindow->move_manager()->cancel_moving();
         
         m_pframewindow->size_manager()->cancel_sizing();
         
         if (m_pframewindow->layout().is_zoomed())
         {

            m_pframewindow->display(::e_display_restore);

         }
         else
         {

            m_pframewindow->display(::e_display_zoomed);

         }

         m_pframewindow->set_need_redraw();

         m_pframewindow->post_redraw();
         
         pmouse->m_bRet = true;

      }

      return false;
      
   }


   bool frame::on_message_mouse_move(::message::mouse * pmouse)
   {

      auto psession = get_session();

      psession->m_pointCursor = pmouse->m_point;

      if(!m_pframewindow->layout().is_zoomed() && !m_pframewindow->layout().is_full_screen())
      {

         if (!m_pframewindow->move_manager()->window_is_moving()
            && !m_pframewindow->size_manager()->window_is_sizing())
         {

            if (m_pframewindow->dock_manager()->window_is_docking())
            {

               __pointer(::message::mouse) pmouseHold = pmouse;

               //m_pframewindow->prodevian_predicate([this, pmouseHold->()
               //{

//                  m_pframewindow->dock_manager()->on_message_mouse_move(pmouseHold);

               //});

               return true;

            }
            else
            {

//               if (m_pframewindow->dock_manager()->on_message_mouse_move(pmouse))
//               {
//
//                  return true;
//
//               }

            }

         }

         if (!m_pframewindow->size_manager()->window_is_sizing())
         {

            if (m_pframewindow->move_manager()->window_is_moving())
            {

               __pointer(::message::mouse) pmouseHold = pmouse;

               //m_pframewindow->prodevian_predicate([this, pmouseHold->()
               //{

                  m_pframewindow->move_manager()->on_message_mouse_move(pmouseHold);

               //});

               return true;

            }
            else
            {

               if (m_pframewindow->move_manager()->on_message_mouse_move(pmouse))
               {

                  return true;

               }

            }

         }

         if (m_pframewindow->size_manager()->window_is_sizing())
         {

            __pointer(::message::mouse) pmouseHold = pmouse;

            //m_pframewindow->prodevian_predicate([this, pmouseHold->()
            //{

               m_pframewindow->size_manager()->on_message_mouse_move(pmouseHold);

            //});

            return true;

         }
         else
         {

            if (m_pframewindow->size_manager()->on_message_mouse_move(pmouse))
            {

               return true;

            }

         }

      }

      return false;

   }


//   bool frame::on_message_set_cursor(::message::set_cursor * psetcursor)
//   {
//
//      auto psession = get_session();
//
//      psession->m_pointCursor = psetcursor->m_point;
//
//      if (!m_pframewindow->layout().is_zoomed() && !m_pframewindow->layout().is_full_screen())
//      {
//
//         if (!m_pframewindow->move_manager()->window_is_moving()
//            && !m_pframewindow->size_manager()->window_is_sizing())
//         {
//
//            if (m_pframewindow->dock_manager()->window_is_docking())
//            {
//
//               __pointer(::message::set_cursor) psetcursorHold = psetcursor;
//
//               //m_pframewindow->prodevian_predicate([this, pmouseHold->()
//               //{
//
////                  m_pframewindow->dock_manager()->on_message_mouse_move(pmouseHold);
//
//               //});
//
//               return true;
//
//            }
//            else
//            {
//
//               //               if (m_pframewindow->dock_manager()->on_message_mouse_move(pmouse))
//               //               {
//               //
//               //                  return true;
//               //
//               //               }
//
//            }
//
//         }
//
//         if (!m_pframewindow->size_manager()->window_is_sizing())
//         {
//
//            if (m_pframewindow->move_manager()->window_is_moving())
//            {
//
//               __pointer(::message::set_cursor) psetcursorHold = psetcursor;
//
//               //m_pframewindow->prodevian_predicate([this, pmouseHold->()
//               //{
//
//               m_pframewindow->move_manager()->on_message_set_cursor(psetcursorHold);
//
//               //});
//
//               return true;
//
//            }
//            else
//            {
//
//               if (m_pframewindow->move_manager()->on_message_set_cursor(psetcursor))
//               {
//
//                  return true;
//
//               }
//
//            }
//
//         }
//
//         if (m_pframewindow->size_manager()->window_is_sizing())
//         {
//
//            __pointer(::message::set_cursor) psetcursorHold = psetcursor;
//
//            //m_pframewindow->prodevian_predicate([this, pmouseHold->()
//            //{
//
//            m_pframewindow->size_manager()->on_message_set_cursor(psetcursorHold);
//
//            //});
//
//            return true;
//
//         }
//         else
//         {
//
//            if (m_pframewindow->size_manager()->on_message_set_cursor(psetcursor))
//            {
//
//               return true;
//
//            }
//
//         }
//
//      }
//
//      return false;
//
//   }


   bool frame::_001OnNcLButtonDown(::message::mouse * pmouse)
   {

      if(!m_pframewindow->layout().is_zoomed() && !m_pframewindow->layout().is_full_screen())
      {

//         if(m_pframewindow->dock_manager()->on_message_left_button_down(pmouse))
//            return true;

         if(m_pframewindow->size_manager()->on_message_left_button_down(pmouse))
            return true;

         if(m_pframewindow->move_manager()->on_message_left_button_down(pmouse))
            return true;

      }

      return false;
   }

   bool frame::_001OnNcLButtonUp(::message::mouse * pmouse)
   {

      if(!m_pframewindow->layout().is_zoomed() && !m_pframewindow->layout().is_full_screen())
      {

//         if (m_pframewindow->dock_manager()->on_message_left_button_up(pmouse))
//         {
//
//            return true;
//
//         }

         if (m_pframewindow->size_manager()->on_message_left_button_up(pmouse))
         {

            return true;

         }

         if (m_pframewindow->move_manager()->on_message_left_button_up(pmouse))
         {

            return true;

         }

      }

      return false;

   }


   bool frame::_001OnNcMouseMove(::message::mouse * pmouse)
   {

      if(!m_pframewindow->layout().is_zoomed() && !m_pframewindow->layout().is_full_screen())
      {

         if(!m_pframewindow->move_manager()->window_is_moving()
               && !m_pframewindow->size_manager()->window_is_sizing()
            )
             //  && m_pframewindow->dock_manager()->on_message_mouse_move(pmouse))
            return true;

         if(!m_pframewindow->move_manager()->window_is_moving()
               && m_pframewindow->size_manager()->on_message_mouse_move(pmouse))
            return true;

         if(m_pframewindow->move_manager()->on_message_mouse_move(pmouse))
            return true;

      }

      return false;

   }


   bool frame::_001OnNcHitTest(const ::point_i32 & point, enum_hit_test & ehittest)
   {

      __UNREFERENCED_PARAMETER(point);

      ehittest = e_hit_test_client;

      return true;

   }


   bool frame::_001OnTimer(::u32 uEvent)
   {

      __UNREFERENCED_PARAMETER(uEvent);

      return false;

   }


   //bool frame::on_message_size(u32 nType,i32 cx,i32 cy)
   //{

   //   __UNREFERENCED_PARAMETER(cx);
   //   __UNREFERENCED_PARAMETER(cy);

   //   return false;

   //}


/*       bool frame::on_message_move(i32 x, i32 y)
   {

      __UNREFERENCED_PARAMETER(x);
      __UNREFERENCED_PARAMETER(y);

      return false;

   }*/


   i32 frame::get_caption_height()
   {

      return m_iCaptionHeight;

   }


   i32 frame::calc_caption_height(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangle = get_control_box()->get_button_margin(e_button_close);

      auto iButtonSize = get_control_box()->calc_button_size(pgraphics);

      auto iCaptionHeight = rectangle.top + iButtonSize + rectangle.bottom;

      return iCaptionHeight;

   }


   void frame::title_bar_layout(::draw2d::graphics_pointer & pgraphics)
   {

      bool bVisible = false;

      auto pframewindow = m_pframewindow;

      if(::is_null(pframewindow))
      {

         return;

      }

      try
      {

         if (m_pframewindow->layout().is_full_screen())
         {

            bVisible = false;

         }
         else if (m_pframewindow->layout().is_this_screen_visible())
         {

            bVisible = true;

         }
         else
         {

            bVisible = false;

         }

      }
      catch (...)
      {

      }

      ::rectangle_i32 rectangleClient;

      pframewindow->::user::interaction::get_client_rect(rectangleClient);

      if (rectangleClient.is_empty())
      {

         return;

      }

      rectangle_i32 rectangleMargin = get_margin_rect();

      rectangle_i32 rectangleCaptionTextPadding = get_caption_text_padding();

      i32 iControlBoxWidth = m_pcontrolbox->calc_control_box_width(pgraphics);

      i32 iCaptionTextHeight = calc_caption_height(pgraphics);


      i32 iCaptionHeight = iCaptionTextHeight;

      m_rectangleCaption.left = rectangleClient.left + rectangleMargin.left;
      m_rectangleCaption.top = rectangleClient.top + rectangleMargin.top;
      m_rectangleCaption.right = rectangleClient.right - rectangleMargin.right;
      m_rectangleCaption.bottom = m_rectangleCaption.top + iCaptionHeight;

      m_iTitleBottom = m_rectangleCaption.bottom;

      rectangleClient.deflate(rectangleMargin);

      auto eappearance = m_pframewindow->const_layout().design().appearance();

      if (!m_pframewindow->layout().is_full_screen() &&
         !(eappearance & ::e_appearance_transparent_frame))
      {

         rectangleClient.top = m_rectangleCaption.bottom - 1;

      }

      m_rectangleClient = rectangleClient;

      m_iControlBoxPosition = rectangleClient.right;

      if(m_iControlBoxPosition < rectangleClient.left)
      {

         m_iControlBoxPosition = rectangleClient.left;

      }
      else if(m_iControlBoxPosition > rectangleClient.right - iControlBoxWidth)
      {

         m_iControlBoxPosition = rectangleClient.right - iControlBoxWidth;

      }

      ::rectangle_i32 rectangleControlBox;

      rectangleControlBox.left = m_iControlBoxPosition;
      rectangleControlBox.right = rectangleControlBox.left + iControlBoxWidth;
      rectangleControlBox.top = m_rectangleCaption.top;
      rectangleControlBox.bottom = m_rectangleCaption.bottom;

      if (m_pframewindow->const_layout().is_this_screen_visible() && !is_iconic(m_pframewindow->const_layout().design().display()))
      {

         get_control_box()->place(rectangleControlBox);

      }

      m_rectangleWindow = rectangleClient;

      ::rectangle_i32 rectangleIcon;

      bool bIcon = get_element_rect(rectangleIcon, ::e_element_top_left_icon);

      m_pointWindowIcon.y = rectangleMargin.top + ((iCaptionHeight - rectangleIcon.height()) /2 );

      if (bIcon)
      {

         m_rectangleWindowText.left = rectangleIcon.right + rectangleCaptionTextPadding.left;

      }
      else
      {

         m_rectangleWindowText.left = m_rectangleCaption.left + rectangleCaptionTextPadding.left;

      }

      m_rectangleWindowText.top = m_rectangleCaption.top + rectangleCaptionTextPadding.top;
      m_rectangleWindowText.right = m_rectangleCaption.right - rectangleCaptionTextPadding.right;
      m_rectangleWindowText.bottom = m_iTitleBottom;

      if (bVisible)
      {

         get_control_box()->display();

      }
      else
      {

         get_control_box()->hide();

      }

   }


   void frame::on_initialize_experience_frame()
   {


   }


   void frame::on_initialize_appearance()
   {
      
      if(m_pframewindow->m_bWindowFrame)
      {

         if (!m_pcontrolbox)
         {

            __compose(m_pcontrolbox, m_pexperience->m_pfactory->create < ::experience::control_box >());

            m_pcontrolbox->initialize(this);

            m_pcontrolbox->m_pframewindow = m_pframewindow;

            auto pframewindow = m_pframewindow;

            m_pcontrolbox->create_child(pframewindow);

            m_pcontrolbox->update_control_box_buttons();

         }
            
      }

      on_style_change();

      on_initialize_experience_frame();

   }



   __pointer(control_box) frame::get_control_box()
   {

      return m_pcontrolbox;

   }


   //void frame::update_window_style()
   //{

   //}


   //void frame::update_window()
   //{

   //   update_window_style();

   //}


   string frame::get_default_user_style() const
   {

      return "LightBlue";

   }


   void frame::set_moveable_border_color(const ::color::color & colorParam)
   {

      m_colorMoveableBorder = colorParam;

      ::color::color color;

      color = colorParam;
      color.hls_rate(0.0, 0.5, 0.0);
      m_colorMoveableBorderHilight = color;
      m_colorMoveableBorderHilight.alpha = 255;

      color = colorParam;
      color.hls_rate(0.0, -0.3, 0.0);
      m_colorMoveableBorderShadow = color;
      m_colorMoveableBorderHilight.alpha = 255;

      color = colorParam;
      color.hls_rate(8.0, -0.8, 0.0);
      m_colorMoveableBorderDkShadow = color;
      m_colorMoveableBorderDkShadow.alpha = 255;

      m_colorCaptionTextBk = m_colorMoveableBorderShadow;

   }


   bool frame::get_window_client_rect(RECTANGLE_I32 * prectangle)
   {

      if (__type_name(this).contains_ci("file"))
      {


         output_debug_string("frame::get_window_client_rect file");

      }

      *prectangle = m_rectangleClient;

      return true;

   }


   bool frame::get_draw_client_rect(RECTANGLE_I32 * prectangle)
   {

      ::rectangle_i32 rectangle;

      if(!get_window_client_rect(rectangle))
      {

         return false;

      }

      rectangle.offset(-rectangle.top_left());

      *prectangle = rectangle;


      return true;

   }


   void frame::update_window_client_rect()
   {

      auto pframewindow  = m_pframewindow;

      ASSERT(pframewindow != nullptr);

      if (pframewindow == nullptr)
      {

         return;

      }

      ::rectangle_i32 rectangleClient;

      pframewindow->::user::interaction::get_client_rect(rectangleClient);

      //calc_window_client_rect(m_rectangleClient, rectangleClient);

   }


   void frame::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == id_user_style_change)
      {

         on_style_change();

      }

   }


   void frame::on_style_change()
   {



      m_bPendingStyleChange = true;

   }


   void frame::_on_style_change(::draw2d::graphics_pointer & pgraphics)
   {

      auto estyle = m_pframewindow->m_estyle;

      auto color = m_pframewindow->m_puserstyle->get_style_moveable_border_color(estyle);

      set_moveable_border_color(color);

   }

   
   rectangle_i32 frame::get_caption_text_padding()
   {

      return m_rectangleCaptionTextPadding;

   }


   rectangle_i32 frame::get_margin_rect()
   {

      if (m_pframewindow->layout().is_full_screen())
      {

         return m_rectangleMarginFullScreen;

      }
      else if (m_pframewindow->layout().is_zoomed())
      {

         return m_rectangleMarginZoomed;

      }
      else
      {

         return m_rectangleMarginDock;

      }

   }


   void frame::on_defer_display()
   {

      if (m_pframewindow->layout().is_this_screen_visible())
      {

         if (m_pframewindow->get_parent() == nullptr)
         {

            if (!(m_pframewindow->m_ewindowflag & e_window_flag_disable_window_placement_snapping)
               //&& !m_pframewindow->layout().is_moving()
               //&& !m_pframewindow->layout().is_sizing()
               && !m_pframewindow->layout().is_docking()
               //&& !::is_docking_appearance(m_pframewindow->layout().sketch().display())
               && m_pframewindow->const_layout().sketch().display() != e_display_zoomed
               && m_pframewindow->const_layout().sketch().display() != e_display_full_screen)
            {

               defer_frame_placement_snapping();

            }

         }

         sync_dock_grip_border();

      }

   }


   void frame::defer_frame_placement_snapping()
   {

      string strType;

      strType = __type_name(m_pframewindow);

      if (strType.contains("playlist"))
      {

         INFORMATION("frame playlist");

      }

      auto edisplay = m_pframewindow->const_layout().sketch().display();

      ::rectangle_i32 rectangle;

      ::rectangle_i32 rectangleRequest;

      bool bPreserveSize;

      rectangleRequest = m_pframewindow->screen_rect();

      bool bMoving = m_pframewindow->move_manager()->window_is_moving();

      bool bSizing = m_pframewindow->size_manager()->window_is_sizing();

      if (bMoving)
      {

         auto pointMove = m_pframewindow->move_manager()->m_pointMove;

         //auto sizeMinimum = m_pframewindow->get_window_minimum_size();

         //auto sizeMove = m_pframewindow->m_windowrectangle.m_rectangleRestored.size().maximum(sizeMinimum);

         //rectangleRequest.set(pointMove, sizeMove);

         rectangleRequest.move_to(pointMove);

         bPreserveSize = true;

      }
      else if(bSizing)
      {

         bPreserveSize = false;

      }
      else
      {

         // arbitrary placement,
         // storage placement,
         // initialization placement...
         // (not sizing and not moving...)

         bPreserveSize = true;

      }

      auto iWorkspace = m_pframewindow->get_best_zoneing(edisplay, &rectangle, rectangleRequest, bPreserveSize);

      if(edisplay != m_pframewindow->const_layout().sketch().display() ||
         (::is_docking_appearance(edisplay) && iWorkspace != m_pframewindow->m_windowrectangle.m_iWorkspace))
      {

         if (m_pframewindow->const_layout().m_durationLastSketchToDesign.elapsed() < 800_ms)
         {

            if (edisplay != m_pframewindow->const_layout().design().display())
            {

               edisplay = m_pframewindow->const_layout().design().display();

            }

         }

         if (is_docking_appearance(edisplay))
         {

             if (m_pframewindow->size_manager()->window_is_sizing())
             {

                 m_pframewindow->size_manager()->window_stop_sizing(false);

             }

         }

         if (edisplay == e_display_restored)
         {

            if (m_pframewindow->move_manager()->window_is_moving())
            {

               if (m_pframewindow->move_manager()->consider_move())
               {

                  m_pframewindow->set_position(m_pframewindow->move_manager()->m_pointMove);

               }

            }

            m_pframewindow->set_size(rectangle.size());

         }
         else
         {

            m_pframewindow->place(rectangle);

         }

         if (is_docking_appearance(edisplay))
         {

            m_pframewindow->m_windowrectangle.m_rectangleSnapped = rectangle;

         }

         m_pframewindow->m_windowrectangle.m_iWorkspace = iWorkspace;

         m_pframewindow->const_layout().sketch().display() = edisplay;

      }
      else if (is_docking_appearance(edisplay))
      {

         if (m_pframewindow->size_manager()->window_is_sizing())
         {

            m_pframewindow->m_windowrectangle.m_rectangleRestored = rectangle;

            m_pframewindow->m_windowrectangle.m_rectangleSnapped = rectangle;

            m_pframewindow->place(rectangle);

         }
         else if (m_pframewindow->move_manager()->window_is_moving())
         {

            m_pframewindow->m_windowrectangle.m_rectangleSnapped = rectangle;

            m_pframewindow->place(rectangle);

            m_pframewindow->set_reposition();

         }

      }

      auto sizeMin = m_pframewindow->get_window_minimum_size();

      auto size = m_pframewindow->const_layout().sketch().size();

      size.ensure_at_least(sizeMin);

      m_pframewindow->set_size(size);

   }


   void frame::sync_dock_grip_border()
   {

      edisplay edisplay = m_pframewindow->const_layout().sketch().display();

      auto rectangleMargin = m_rectangleMarginNormal;

      e_grip egrip;
      e_border eborder;
      e_dock edock;

      if (!m_pframewindow->is_this_screen_visible() || is_zoomed(edisplay) || is_full_screen(edisplay))
      {

         egrip = e_grip_none;
         eborder = e_border_none;
         edock = e_dock_none;

         rectangleMargin.Null();

      }
      else if (is_docking_appearance(edisplay))
      {

         if (!(edisplay & e_display_bottom))
         {

            egrip |= e_grip_bottom;
            eborder |= e_border_bottom;
            edock |= e_dock_bottom;

            if (!(edisplay & e_display_left))
            {

               egrip |= e_grip_bottom_left;

            }

         }

         if (!(edisplay & e_display_top))
         {

            egrip |= e_grip_top;
            eborder |= e_border_top;
            edock |= e_dock_top;

            if (!(edisplay & e_display_right))
            {

               egrip |= e_grip_top_right;

            }

         }

         if (!(edisplay & e_display_left))
         {

            egrip |= e_grip_left;
            eborder |= e_border_left;
            edock |= e_dock_left;

            if (!(edisplay & e_display_top))
            {

               egrip |= e_grip_top_left;

            }

         }

         if (!(edisplay & e_display_right))
         {

            egrip |= e_grip_right;
            eborder |= e_border_right;
            edock |= e_dock_right;

            if (!(edisplay & e_display_bottom))
            {

               egrip |= e_grip_bottom_right;

            }

         }

         if (edisplay & e_display_top)
         {

            rectangleMargin.top = 0;

         }

         if(edisplay & e_display_bottom)
         {

            rectangleMargin.bottom = 0;

         }

         if (edisplay & e_display_right)
         {

            rectangleMargin.right = 0;

         }

         if (edisplay & e_display_left)
         {

            rectangleMargin.left = 0;

         }

      }
      else
      {

         egrip = e_grip_all;
         eborder = e_border_all;
         edock = e_dock_all;

      }

      string strType = __type_name(m_pframewindow);

      if (strType.contains("filemanager"))
      {

         //INFORMATION("filemanager");

      }

      if (m_pframewindow->m_eupdown == ::user::interaction::e_updown_down)
      {

         egrip = e_grip_none;
         edock = e_dock_none;

      }

      m_pframewindow->m_psizemanager->SetGripMask(egrip);
      m_pframewindow->m_pmovemanager->SetBorderMask(eborder);
      m_pframewindow->set_dock_mask(edock);

      if (rectangleMargin != m_rectangleMarginDock)
      {

         m_rectangleMarginDock = rectangleMargin;

         m_pframewindow->set_need_layout();

      }

   }


   bool frame::get_element_rect(RECTANGLE_I32 * prectangle,::enum_element eelement)
   {

      return false;

   }


   void frame::get_parent_rect(RECTANGLE_I32 * prectangle)

   {

      if (m_pframewindow->layout().is_full_screen())
      {

         m_pframewindow->best_monitor(prectangle);


      }
      else if (m_pframewindow->layout().is_zoomed())
      {

         m_pframewindow->get_window_rect(prectangle);


      }
      else
      {

         m_pframewindow->get_window_rect(prectangle);


      }

   }


//   rectangle_i32 * frame::get_control_box_rect()
//   {
//
//      if(m_pframewindow->layout().is_full_screen())
//      {
//
//         return &m_rectangleControlBoxFullScreen;
//
//      }
//      else if(m_pframewindow->layout().is_zoomed())
//      {
//
//         return &m_rectangleControlBoxZoomed;
//
//      }
//      else
//      {
//
//         return &m_rectangleControlBoxNormal;
//
//      }
//
//   }


   ::experience::enum_frame frame::experience_frame_hit_test(const ::point_i32 & point)
   {

      __UNREFERENCED_PARAMETER(point);

      return e_frame_client;

   }


   void frame::GetFrameRect(rectangle_i32 * prectangle)
   {

      m_pframewindow->::user::interaction::get_client_rect(prectangle);

   }


   //void frame::nextstyle(::user::style_context * pcontext)
   //{

   //   m_pframewindow->nextstyle(pcontext);

   //}


} // namespace experience


