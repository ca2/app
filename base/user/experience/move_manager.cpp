#include "framework.h"
#include "move_manager.h"
#include "frame_window.h"
#include "frame.h"
#include "acme/constant/message.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "apex/parallelization/thread.h"
#include "aura/user/user/interaction_thread.h"
#include "aura/windowing/window.h"
#include "aura/windowing/windowing.h"
#include "aura/message/user.h"


namespace experience
{

   
   move_manager::move_manager()
   {

      m_iConsiderMove = 0;
      m_bMoving = false;
      //SetSWPFlags(0);
      m_eborderMask = e_border_all;

   }


   move_manager::~move_manager()
   {

   }


   void move_manager::initialize_move_manager(::experience::frame_window* pframewindow)
   {

      //auto estatus =
      
      ::object::initialize(pframewindow);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pframewindow = pframewindow;

      //return estatus;

   }


   bool move_manager::on_message_left_button_down(::message::mouse * pmouse)
   {

      if (!m_pframewindow->is_moving_enabled())
      {

         return false;

      }

      if(m_pframewindow->window()->defer_perform_entire_reposition_process(pmouse))
      {

         pmouse->m_lresult = 1;

         pmouse->m_bRet = true;

         return true;

      }

      m_bMoving = true;

      m_pframewindow->set_mouse_capture();

      m_stateBefore = m_pframewindow->const_layout().design();

      auto pointCursor = pmouse->m_pointAbsolute;

      ::int_rectangle rectangleWindow;

      m_pframewindow->window_rectangle(rectangleWindow);

      m_pointCursorOrigin = pointCursor;

      m_pointWindowOrigin = rectangleWindow.top_left();

      information() << "on_message_left_button_down m_pointWindowOrigin : " << m_pointWindowOrigin;

      m_pointMove = m_pointWindowOrigin;

      m_iConsiderMove = 0;

      m_pframewindow->window()->m_puserthread->m_emessageaGetLast.add(e_message_mouse_move);

      auto & edisplaySketch = m_pframewindow->layout().m_statea[::user::e_layout_sketch].m_edisplay;

      if (edisplaySketch & e_display_docking_mask)
      {

         edisplaySketch -= e_display_docking_mask;

         if (edisplaySketch == e_display_none)
         {

            edisplaySketch = e_display_normal;

         }

      }

      m_pframewindow->on_start_layout_experience(e_layout_experience_moving);

      pmouse->m_bRet = true;

      return true;

   }


   bool move_manager::on_message_parent_mouse_move(::message::mouse * pmouse)
   {

      if (!m_pframewindow->is_moving_enabled())
      {

         return false;

      }

      ASSERT(pmouse->m_emessage == e_message_parent_mouse_move);

      //auto pwindowing = m_pframewindow->windowing();

      //auto pcursor = pwindowing->get_cursor(e_cursor_arrow);

      //pmouse->m_pcursor = pcursor;

      //m_pframewindow->set_mouse_cursor(pcursor);

      if (!window_is_moving())
      {

         return false;

      }

//      if(m_pframewindow->window()->defer_perform_reposition())
//      {
//
//         return true;
//
//      }
//
      pmouse->payload("flush_similar_messages") = true;

      auto pframewindow = m_pframewindow;

      auto pointMove = m_pointWindowOrigin + (pmouse->m_pointAbsolute - m_pointCursorOrigin);

      if (pframewindow->get_parent() != nullptr)
      {

         pframewindow->screen_to_client()(pointMove);

      }

      if (pframewindow->get_int("ysnap") > 1)
      {

         pointMove.y() -= pointMove.y() % pframewindow->get_int("ysnap");

      }

      m_pointMove = pointMove;

      m_iConsiderMove++;

      {

         //::user::lock_sketch_to_design lockSketchToDesign(pframewindow);

         //auto edisplay = pframewindow->const_layout().sketch().display();

//         if (::is_docking_appearance(edisplay))
//         {
//
//            //pframewindow->m_pframe->defer_frame_placement_snapping();
//
//         }
//         else
         {

            pframewindow->set_position(pointMove);

         }

         pframewindow->set_need_redraw();

      }

      pframewindow->post_redraw();

      pmouse->m_bRet = true;

      return true;

   }


   bool move_manager::on_message_mouse_move(::message::mouse * pmouse)
   {

      if (!m_pframewindow->is_moving_enabled())
      {

         return false;

      }

      return false;

      //ASSERT(
      //   pmouse->m_emessage == e_message_mouse_move 
      //   || pmouse->m_emessage == e_message_non_client_mouse_move);

      //auto pwindowing = m_pframewindow->windowing();

      //auto pcursor = pwindowing->get_cursor(e_cursor_arrow);

      //m_pframewindow->user_mouse_set_cursor(pmouse, pcursor);

      //m_iConsiderMove++;

      //////m_pframewindow->set_mouse_cursor(pcursor);

      ////if (!window_is_moving())
      ////{

      ////   return false;

      ////}

      ////pmouse->payload("flush_similar_messages") = true;

      ////auto pframewindow = m_pframewindow;

      ////auto pointMove = m_pointWindowOrigin + (pmouse->m_point - m_pointCursorOrigin);

      ////if (pframewindow->get_parent() != nullptr)
      ////{

      ////   pframewindow->screen_to_client()(pointMove);

      ////}

      ////if (pframewindow->find_int("ysnap") > 1)
      ////{

      ////   pointMove.y() -= pointMove.y() % pframewindow->find_int("ysnap");

      ////}

      ////m_pointMove = pointMove;

      ////m_iConsiderMove++;

      ////{

      ////   //::user::lock_sketch_to_design lockSketchToDesign(pframewindow);

      ////   auto edisplay = pframewindow->const_layout().sketch().display();

      ////   if (::is_docking_appearance(edisplay))
      ////   {

      ////      pframewindow->m_pframe->defer_frame_placement_snapping();

      ////   }
      ////   else
      ////   {

      ////      pframewindow->set_position(pointMove);

      ////   }

      ////   pframewindow->set_need_redraw();

      ////}

      ////pframewindow->post_redraw();

      //pmouse->m_bRet = true;

      //return true;

   }


   bool move_manager::on_message_left_button_up(::message::mouse * pmouse)
   {

      if (!m_pframewindow->is_moving_enabled())
      {

         return false;

      }

      if (!window_is_moving())
      {

         return false;

      }

      //bool bApply = !is_docking_appearance(m_pframewindow->const_layout().sketch().display());

      window_stop_moving(pmouse);

      return true;

   }


   bool move_manager::window_stop_moving(::message::mouse * pmouse)
   {

      if (!m_bMoving)
      {

         return false;

      }

      m_bMoving = false;

      m_pframewindow->window()->m_puserthread->m_emessageaGetLast.erase(e_message_mouse_move);

      m_pframewindow->defer_release_mouse_capture();

      if (!consider_move())
      {

         information() << "Repositioning isn't considered intentional (too few mouse moves). Restoring previous state";

         {

//            ::user::lock_sketch_to_design lockSketchToDesign(m_pframewindow);

            m_pframewindow->set_layout_state(m_stateBefore, ::user::e_layout_sketch);

         }

         m_pframewindow->set_need_redraw();

      }
//      else if (bApply)
//      {
//
//         auto rectangleRequest = m_pframewindow->screen_rectangle();
//
//         //index iMatchingMonitor = m_pframewindow->good_move(rectangleRequest, nullptr);
//
//         //index iMatchingMonitor =
//         m_pframewindow->good_move(&rectangleRequest);
//
//         //if (iMatchingMonitor >= 0)
//         //{
//
//         //   if (!pmouse)
//         //   {
//
//         //      pmouse->m_point = -m_pointWindowOrigin + rectangleRequest.top_left() + m_pointCursorOrigin;
//
//         //   }
//
//         //}
//
//      }

      m_pframewindow->on_end_layout_experience(e_layout_experience_moving);

      return true;

   }


   bool move_manager::set_frame_window(frame_window * pframewindow)
   {

      m_pframewindow = pframewindow;

      return true;

   }


   bool move_manager::window_is_moving()
   {

      return m_bMoving;

   }


   void move_manager::cancel_moving()
   {
      
      m_bMoving = false;
      
      m_pframewindow->defer_release_mouse_capture();

   }


   bool move_manager::consider_move()
   {

      return m_iConsiderMove > 10;

   }


   e_border move_manager::GetBorderMask()
   {

      return m_eborderMask;

   }


   void move_manager::SetBorderMask(const e_border & emask)
   {

      m_eborderMask = emask;

   }


   bool move_manager::on_timer(unsigned int uEvent)
   {

      return false;

   }


} // namespace experience



