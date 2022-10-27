#include "framework.h"

//#include "acme/message.h"
#include "interaction_prodevian.h"
#include "interaction_thread.h"
#include "acme/parallelization/message_queue.h"
//#include "acme/operating_system/_user.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/windowing/window.h"
#include "interaction_impl.h"
#include "interaction.h"

#if !defined(WINDOWS_DESKTOP)
#define PM_NOREMOVE 0
#define PM_REMOVE 1

#endif
#define TIME_REPORTING 0


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


#ifdef LINUX


#include "aura/operating_system/ansi/_ansi.h"


#endif


namespace user
{


#if TIME_REPORTING
   
   
   ::duration g_durationBetweenUpdateBufferAndUpdateScreen;


#endif


   prodevian::prodevian()
   {

      //m_bUpdateBufferUpdateWindowPending = false;

      m_bRedraw = false;
      m_bUpdateBuffer = false;
      m_bUpdateScreen = false;
      m_bUpdateWindow = false;

      m_bAuraMessageQueue = true;

      m_bUpdatingScreen = false;

#ifdef _UWP
      m_bExclusiveMode = true;
#else
      m_bExclusiveMode = false;
#endif

      m_bVisualUpdated = true;

      m_bSimpleMessageLoop = false;

   }


   prodevian::~prodevian()
   {

   }


#ifdef _DEBUG


   i64 prodevian::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::thread::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   i64 prodevian::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::thread::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   i64 prodevian::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::thread::release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


   void prodevian::defer_create_prodevian()
   {

      //__refer(m_pprodevian, m_pimpl->m_pprodevian);

      //if(m_pprodevian)
      {

         if (!(m_pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_embedded_prodevian))
         {


            branch();

            //if (!branch())
            //{

            //   //__release(m_pprodevian);

            //   return error_failed;

            //}

         }
         else
         {

            init_task();

         }

      }

      //return ::success;

   }


   void prodevian::initialize_prodevian(interaction_impl * pimpl)
   {

      //auto estatus = 
      
      initialize(pimpl);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_procedureUpdateScreen = [this]()
         {

            if (!has(e_flag_destroying) && !is_finishing())
            {

               update_screen();

            }

            m_bUpdatingScreen = false;

         };

      m_procedureWindowShow = [this]()
         {

            if (m_pimpl)
            {

               m_pimpl->window_show();

            }

         };

      m_puserinteraction = pimpl->m_puserinteraction;

      m_pimpl = pimpl;

      set_fps(60);

      string strType;

      strType = __type_name(m_puserinteraction);

      if (strType.contains("playlist"))
      {

         INFORMATION("frame playlist");

      }

      //return estatus;

   }

   
   //void prodevian::do_task()
   //{

   //   return ::thread::do_task();

   //}


   void prodevian::run()
   {

      //m_pimpl->m_puserinteraction->task_add(this);

      m_synchronizationa.add(&m_evUpdateScreen);

   #ifdef WINDOWS_DESKTOP

      attach_thread_input_to_main_thread(true);

   #endif

      if (m_bAuraMessageQueue)
      {

         m_synchronizationa.add(&get_message_queue()->m_eventNewMessage);

      }

      string strType = __type_name(m_puserinteraction);

      ::task_set_name("prodevian," + strType);

      if (strType.contains_ci("list_box"))
      {

         output_debug_string("list_box");

      }

      m_puserinteraction->add_task(this);

      //m_puserinteraction->m_pthreadUserInteraction->add_task(this);

      //add_task(m_puserinteraction);

      try
      {

         while (task_get_run())
         {

            pump_runnable();

            if (!prodevian_iteration())
            {

               break;

            }

         }

      }
      catch (::exception&)
      {


      }
      catch (...)
      {

      }

      if (m_puserinteraction)
      {

         if (m_puserinteraction->is_destroying())
         {

           m_puserinteraction->post_message(e_message_destroy_window);

         }

      }

      //return m_estatus;

   }


   bool prodevian::prodevian_reset(::user::interaction * pinteraction)
   {

      m_puserinteraction = pinteraction;

      m_durationNow.Now();

      //m_iFrameId = m_durationNow / m_durationFrame;

      //m_iLastFrameId = m_iFrameId;

      return true;

   }


   void prodevian::term_task()
   {

      if (m_pimpl)
      {

         if (m_pimpl->m_pprodevian == this)
         {

            m_pimpl->m_pprodevian.release();

         }

      }

      m_nanosecondtimer.close_timer();

      ::thread::term_task();

      m_pimpl.release();

      m_puserinteraction.release();

      if (m_procedureUpdateScreen)
      {

         m_procedureUpdateScreen->destroy();

      }

      m_procedureUpdateScreen.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

      if (m_procedureWindowShow)
      {

         m_procedureWindowShow->destroy();

      }

      m_procedureWindowShow.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   }


   void prodevian::destroy()
   {

      m_evUpdateScreen.SetEvent();

      m_puserinteraction.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

      m_pimpl.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

      m_synchronizationa.clear();

      //auto estatus = 
      
      ::thread::destroy();

      //return estatus;

   }


   #undef EXTRA_PRODEVIAN_ITERATION_LOG


   bool prodevian::prodevian_iteration()
   {

      bool bHasProdevian = false;

      bool bRedraw = false;

      string strType;

      strType = __type_name(m_puserinteraction);

      {

         synchronous_lock synchronouslock(m_puserinteraction->synchronization());

         if (strType.contains_ci("filemanager"))
         {

            //INFORMATION("filemanager frame... ");

         }

         if (!m_puserinteraction)
         {

            return false;

         }

         ASSERT(!(m_puserinteraction->m_ewindowflag & e_window_flag_embedded_prodevian));
         ASSERT(m_puserinteraction->m_pinteractionimpl.is_set());

         bHasProdevian = m_puserinteraction->has_prodevian();

         //synchronous_lock synchronouslock(m_pimpl->mutex());

         // if (bHasProdevian)
         // {

         //    output_debug_string("has_prodevian");

         // }
//
//         }

      }

      if (!(m_puserinteraction->m_ewindowflag & e_window_flag_embedded_prodevian))
      {

         if (m_puserinteraction->m_pinteractionimpl.is_null() || !bHasProdevian)
         {

            m_puserinteraction->m_ewindowflag -= e_window_flag_redraw_in_queue;

            get_message(&m_message, NULL, 0, 0);

            if(m_message.m_atom == e_message_quit)
            {

               CATEGORY_INFORMATION(prodevian, "Prodevian has quit!! " << strType);

               return false;

            }

            if (strType.contains_ci("list_box"))
            {

               output_debug_string("list_box");

            }

            //printf("prodevian get_message(%d)\n", m_message.message);

            int iSkipped = 0;

            while (peek_message(&m_message, NULL, 0, 0))
            {

               if (m_message.m_atom == e_message_redraw || m_message.m_atom == WM_KICKIDLE)
               {

                  iSkipped++;

                  peek_message(&m_message, NULL, 0, 0, true);

               }
               else
               {

                  break;

               }

            }

   #ifdef EXTRA_PRODEVIAN_ITERATION_LOG

            INFORMATION("Skipped e_message_redraw count "+ __string(iSkipped) + "\n");

   #endif

            if (m_message.m_atom == e_message_null)
            {

               return true;

            }
            else if (m_message.m_atom != e_message_redraw)
            {

               return true;

            }
            else if (!this->task_get_run())
            {

               return false;

            }

            bRedraw = true;

         }
         else if(!bHasProdevian)
         {

            while (peek_message(&m_message, NULL, 0, 0, true))
            {

               if (m_message.m_atom == e_message_null)
               {

                  return true;

               }
               else if (m_message.m_atom != e_message_redraw)
               {

                  return true;

               }

               bRedraw = true;

            }

            if (!this->task_get_run())
            {

               return false;

            }

         }

      }

      if(!m_puserinteraction)
      {

         return false;

      }

      if(m_puserinteraction->m_ewindowflag & e_window_flag_postpone_visual_update)
      {

         if(m_pimpl->m_bPendingRedraw && m_pimpl->m_durationLastRedraw.elapsed() < 100_ms)
         {

            return true;

         }

      }

      // e_message_redraw

      if(strType.contains_ci("filemanager"))
      {

         //INFORMATION("filemanager");

      }

      i64 i1 = get_integral_nanosecond().m_i;

      bRedraw = m_message.wParam & 1;

      m_message.wParam &= ~1;

      //if (m_bUpdateBufferUpdateWindowPending)
      //{

         prodevian_update_buffer(bRedraw);

      //}

      //m_bUpdateBufferUpdateWindowPending = false;

      m_durationNow.Now();

      if (!this->task_get_run())
      {

         return false;

      }

      //if (m_puserinteraction && m_puserinteraction->GetExStyle() & WS_EX_LAYERED)
      //{

      //   m_bUpdateWindow |= m_bUpdateBuffer;

      //}

      bool bStartWindowVisual = false;

      if (m_puserinteraction)
      {

         if (m_bUpdateWindow || m_puserinteraction->m_bUpdateVisual)
         {

            m_puserinteraction->m_bUpdateVisual = false;

            if (m_puserinteraction->m_ewindowflag & e_window_flag_postpone_visual_update)
            {

               bStartWindowVisual = true;

            }

         }

      }

      bool bWait = ((m_bUpdateWindow || m_bUpdateScreen) && !bStartWindowVisual) || bRedraw;

      if (bWait)
      {

         if (bHasProdevian)
         {

            bWait = (m_durationNow - m_durationLastFrame) < m_durationPostRedrawProdevian.half();

         }
         else
         {

            bWait = (m_durationNow - m_durationLastFrame) < m_durationPostRedrawNominal.half();

         }

      }

      if (bWait)
      {

         // Either:
         // - It has prodevian mode (FPS drawing);
         // - Or it is going to wait because a frame was already drawn an instant ago due on-request-drawing (cool down).

         auto durationFrame = bHasProdevian ? m_durationPostRedrawProdevian : m_durationPostRedrawNominal ;

         //i64 i2 = get_nanos();

         // calculates the next/memory_new frame atom
         //m_iFrameId = (m_durationNow + durationFrame - 1) / (durationFrame);

         //m_durationNextFrame = m_iFrameId * durationFrame;

         m_durationNextFrame = m_durationNow + durationFrame;

         //m_cLost = (::count) (m_iFrameId - m_iLastFrameId - 1);

         //m_iLastFrameId = m_iFrameId;

         m_durationNextScreenUpdate = m_durationNextFrame;

         auto nanosElapsedSinceLastFrame = m_durationNow - m_durationLastFrame;

         if (nanosElapsedSinceLastFrame > durationFrame)
         {

            // todo display average from last 10 or so frame drawing time and not for every each single offending sample
            // output_debug_string("("+__string(nanosElapsedSinceLastFrame/1'000'000)+"ms)Frames are taking long to draw. Wait a bit more to free CPU. Is there much load?!?!\n");

            m_durationNextScreenUpdate += durationFrame;

            //m_iLastFrameId++;

         }

         {

            auto durationStartWait = ::duration::now();

            auto durationToWaitForNextFrame = m_durationNextScreenUpdate - durationStartWait;

            if (durationToWaitForNextFrame > 1_s)
            {

               //output_debug_string("what?!?!\n");

               durationToWaitForNextFrame = 500_ms;

            }

            if (durationToWaitForNextFrame >= 2_ms)
            {

               ::duration tickWait;

               tickWait.Now();

               //printf("msToWaitForNextFrame >= 2\n");

               if (durationToWaitForNextFrame < durationFrame)
               {

                  if (durationToWaitForNextFrame >= 50_ms)
                  {

                     //printf("msToWaitForNextFrame >= 50ms (%dms)\n", (::i32) (msToWaitForNextFrame - 1));

                     ::duration duration;

                     duration.Now();

                     m_synchronizationa.wait(durationToWaitForNextFrame - 1_ms);

                     //printf("Actually waited %dms\n", (::i32) ::duration.elapsed().m_i);

                  }
                  else
                  {

                     //printf("msToWaitForNextFrame < 50\n");

                     if(durationToWaitForNextFrame > 300_ms)
                     {

                        m_evUpdateScreen._wait(durationToWaitForNextFrame);

                     }
                     else
                     {

                        ::preempt(durationToWaitForNextFrame);

                     }

                  }

               }

               auto elapsed = tickWait.elapsed();

               //printf("msToWaitForNextFrame Waited %d\n", elapsed.m_i);

            }

            auto durationEndWait = ::duration::now();

            if (durationEndWait - durationStartWait > 100_ms)
            {

               output_debug_string("Waited more than 100ms to go display drawn frame at screen?!?!\n");

            }

            //{

            //   i64 nanosDeltaPostRedraw = (i64)m_durationNextScreenUpdate - (durationFrame - m_durationPostRedraw)  - (i64)get_nanos();

            //   i32 msDeltaPostRedraw = (::i32)(nanosDeltaPostRedraw / 1'000'000);

            //   if (msDeltaPostRedraw >= 1)
            //   {

            //      sleep(msDeltaPostRedraw);

            //   }


            //}

            m_evUpdateScreen.ResetEvent();

         }

      }

      if (!this->task_get_run())
      {

         return false;

      }

      if(!m_pimpl)
      {

         return false;

      }

      if(!m_puserinteraction)
      {

         return false;

      }

      if (!(m_puserinteraction->m_ewindowflag & e_window_flag_postpone_visual_update))
      {

         //#ifdef LINUX

         if (bStartWindowVisual)
         {

            m_pimpl->window_show();

         }

         //#endif
         ////END IFDEF LINUX

      }

      if (m_bVisualUpdated)
      {

         m_bVisualUpdated = false;

         if (::is_set(m_pimpl->m_puserthread))
         {

            m_pimpl->m_puserthread->m_evApplyVisual.wait(15_s);

         }

      }

      if (!this->task_get_run())
      {

         return false;

      }

      bool bWindowsApplyVisual = true;

      auto & edisplayOutput = m_puserinteraction->const_layout().output().m_edisplay;

      auto & edisplayDesign = m_puserinteraction->const_layout().design().m_edisplay;

      if (edisplayOutput != edisplayDesign)
      {

         m_puserinteraction->post_message(e_message_show_window, ::is_screen_visible(edisplayDesign) ? 1 : 0);

      }


#if TIME_REPORTING

      auto e1 = g_durationBetweenUpdateBufferAndUpdateScreen.elapsed();
      
      ::duration durationUpdateScreenPost;
      
      durationUpdateScreenPost.Now();

      output_debug_string("durationBetweenUpdateBufferAndUpdateScreen "+__string(e1.floating_millisecond().m_d) +"ms\n");

#endif

      if (m_bUpdateScreen && (bWindowsApplyVisual || !bStartWindowVisual))
      {

         prodevian_update_screen();

      }

#if TIME_REPORTING

      auto e2 = durationUpdateScreenPost.elapsed();

      output_debug_string("durationUpdateScreenPost " + __string(e2.floating_millisecond().m_d) + "ms\n");

#endif

      m_puserinteraction->set_display(edisplayDesign, e_layout_output);

      if (!m_puserinteraction)
      {

         return false;

      }

      if ((m_puserinteraction->m_ewindowflag & e_window_flag_postpone_visual_update))
      {
         // IFDEF WINDOWS
         if (bStartWindowVisual)
         {


            m_pimpl->m_pwindow->window_show();
            //m_puserinteraction->post_procedure(m_procedureWindowShow);

         }
         // ENDIF WINDOWS
      }

      auto durationNow = ::duration::now();

      for (index i = 0; i < m_durationaFrame.get_size();)
      {

         auto durationFrame = m_durationaFrame[i];

         auto durationDiff = durationNow - durationFrame;

         if (durationDiff > 1_s)
         {

            m_durationaFrame.erase_at(i);

         }
         else
         {

            break;

         }

      }

      if(!m_pimpl)
      {

         return false;

      }

      m_pimpl->m_dOutputFps = (double)(m_durationaFrame.get_size());

      return true;

   }


   bool prodevian::prodevian_update_buffer(bool bRedraw)
   {

      m_bRedraw = bRedraw;

      m_bUpdateBuffer = false;

      m_bUpdateScreen = false;

      m_bUpdateWindow = false;

      update_buffer(m_bUpdateBuffer, m_bUpdateScreen, m_bUpdateWindow, bRedraw);

      //m_bUpdateBufferUpdateWindowPending = m_bUpdateWindow;

      return true;

   }


   bool prodevian::prodevian_update_screen()
   {

      if (m_bExclusiveMode)
      {

         update_screen();

      }
      else
      {

         m_durationLastScreenUpdate.Now();

         m_bUpdatingScreen = true;

         m_pimpl->m_pwindow->update_screen();

         //if (!m_bUpdatingScreen || m_durationLastScreenUpdate.elapsed() > 200_ms)
//         {
//
//            if (m_puserinteraction)
//            {
//
//               m_puserinteraction->post_procedure(m_procedureUpdateScreen);
//
//            }
//
//         }

      }

      return true;

   }



   void prodevian::update_buffer(bool & bUpdateBuffer, bool & bUpdateScreen, bool & bUpdateWindow, bool bForce)
   {

      try
      {

         synchronous_lock synchronouslock(m_puserinteraction->synchronization());

         if(!m_puserinteraction)
         {

            return;

         }

         bUpdateBuffer = false;

         bUpdateWindow = false;

         i64 i1 = get_integral_nanosecond().m_i;

      //   bool bTransparentDraw;

      //#ifdef WINDOWS_DESKTOP

      //   if (m_puserinteraction->GetExStyle() & WS_EX_LAYERED)
      //   {

      //      bTransparentDraw = true;

      //   }
      //   else
      //   {

      //      bTransparentDraw = false;

      //   }

      //#else

      //   bTransparentDraw = true;

      //#endif

         if (!::task_get_run())
         {

            return;

         }

         if (m_puserinteraction == nullptr)
         {

            return;

         }

         bool bDraw = false;

         m_bVisualUpdated = false;

         if(!m_puserinteraction)
         {

            return;

         }

         {


            synchronouslock.unlock();

            //if (!m_puserinteraction->is_sketch_to_design_locked())
            //{

               m_puserinteraction->sketch_to_design(bUpdateBuffer, bUpdateWindow);

            //}

            synchronouslock.lock();

            if(!m_puserinteraction)
            {

               return;

            }

            if (!this->task_get_run())
            {

               return;

            }

            if(!m_puserinteraction)
            {

               return;

            }

            bool bIsThisScreenVisible = m_puserinteraction->const_layout().design().is_screen_visible();

            if(!m_pimpl)
            {

               return;

            }

            bool bHasProdevian = m_pimpl->has_prodevian();

            if(!m_puserinteraction)
            {

               return;

            }

            bool bRedraw = m_puserinteraction->m_bNeedRedraw;

            if(!m_puserinteraction)
            {

               return;

            }

            bool bHasPendingGraphicalUpdate = m_puserinteraction->has_pending_graphical_update();

            if (bIsThisScreenVisible
               &&
               (bForce
               || bUpdateBuffer
               || bHasProdevian
               || bRedraw
               || bHasPendingGraphicalUpdate
               )
               )
            {

               bDraw = true;

            }

            if(!m_puserinteraction)
            {

               return;

            }

            if (m_puserinteraction->m_bOffScreenRender)
            {

               bDraw = true;

            }

            m_pimpl->update_graphics_resources();

            if (bDraw && m_pimpl->m_pgraphics.is_null())
            {

               bDraw = false;

            }

         }

         if (m_puserinteraction->has(e_flag_destroying)
            || m_puserinteraction->is_finishing()
            || m_pimpl->has(e_flag_destroying)
            || m_pimpl->is_finishing())
         {

            bDraw = false;

         }

         if (bDraw && m_pimpl)
         {

            synchronouslock.unlock();

            m_durationBeforeDrawing.Now();

            m_durationOutOfDrawing = m_durationBeforeDrawing - m_durationAfterDrawing;

            i64 i2 = get_integral_nanosecond().m_i;

#if TIME_REPORTING

            static ::duration durationLast;

            output_debug_string("time outside updatebuffer " +__string(durationLast.elapsed().floating_millisecond().m_d) + "ms\n");

#endif

            m_pimpl->_001UpdateBuffer();

#if TIME_REPORTING

            durationLast.Now();

            g_durationBetweenUpdateBufferAndUpdateScreen.Now();

#endif

            bUpdateBuffer = true;

            bUpdateScreen = true;

            m_durationAfterDrawing.Now();

            m_durationDuringDrawing = m_durationAfterDrawing - m_durationBeforeDrawing;

            if (m_puserinteraction)
            {

               m_puserinteraction->on_after_graphical_update();

            }

            if (m_puserinteraction)
            {

               m_puserinteraction->m_bNeedRedraw = false;

            }


            if (m_puserinteraction)
            {

               if (m_puserinteraction->is_visual_changed())
               {

                  m_puserinteraction->on_visual_applied();

               }

            }

         }

      }
      catch (...)
      {

      }

   }


   bool prodevian::update_screen()
   {

      //if (m_pimpl)
      //{

      //   if (m_pimpl->m_pgraphics)
      //   {

      //      auto pbitmapsource = m_pimpl->m_pgraphics.cast < ::graphics::bitmap_source_buffer >();

      //      if (pbitmapsource)
      //      {

      //         string strBitmapSource = m_puserinteraction->payload("bitmap-source");

      //         if (pbitmapsource->m_strBitmapSource != strBitmapSource)
      //         {

      //            pbitmapsource->enable_ipc_copy(strBitmapSource);

      //         }

      //      }


      //   }

      //}


      try
      {

         string strType = __type_name(m_puserinteraction);

         if(strType.contains_ci("list_box"))
         {

            output_debug_string("We're on the list_box update_screen");

         }
         
         profiling_on_before_update_screen();

         if (!m_pimpl)
         {

            return false;

         }

         m_pimpl->prodevian_update_screen();

         if (!m_puserinteraction)
         {

            return false;

         }

         if (is_different(m_puserinteraction->m_ewindowflag & e_window_flag_on_show_window_visible,
            m_puserinteraction->is_this_visible())
            || is_different(m_puserinteraction->m_ewindowflag & e_window_flag_on_show_window_screen_visible,
               m_puserinteraction->is_window_screen_visible()))
         {

            m_puserinteraction->m_ewindowflag.set(e_window_flag_on_show_window_visible, m_puserinteraction->is_this_visible());

            m_puserinteraction->m_ewindowflag.set(e_window_flag_on_show_window_screen_visible, m_puserinteraction->is_window_screen_visible());

            m_puserinteraction->_on_show_window();

         }
         
         profiling_on_after_update_screen();

      }
      catch(...)
      {

         return false;

      }

      return true;

   }


   void prodevian::profiling_on_before_update_screen()
   {
    
      m_durationBeforeUpdateScreen.Now();

      m_durationOufOfUpdateScreen = m_durationBeforeUpdateScreen - m_durationAfterUpdateScreen;

   }


   void prodevian::profiling_on_after_update_screen()
   {
      
      m_durationLastFrame.Now();

      m_durationaFrame.add(m_durationLastFrame);

      m_durationAfterUpdateScreen.Now();

      m_durationDuringUpdateScreen = m_durationAfterUpdateScreen - m_durationBeforeUpdateScreen;

      if (m_durationDuringUpdateScreen > 60_ms)
      {

         //output_debug_string("It took about " + __string(m_durationDuringUpdateScreen) + " to update screen\n");

         //output_debug_string("It took about " + __string(m_durationOufOfUpdateScreen) + " out of screen update\n");

      }

      m_durationDuringUpdateScreen = m_durationAfterUpdateScreen - m_durationBeforeUpdateScreen;

      if (m_durationOufOfUpdateScreen > 60_ms)
      {

         //output_debug_string("It took about " + __string(m_durationDuringUpdateScreen) + " to update screen\n");

         //output_debug_string("It took about " + __string(m_durationOufOfUpdateScreen) + " out of screen update\n");

      }
      
   }

   
   void prodevian::defer_prodevian_step()
   {

      if (m_durationLastFrame.elapsed() > (m_durationPostRedrawNominal * 3 / 4))
      {

         post_message(e_message_redraw);

      }

   }


   void prodevian::set_prodevian_fps(double dProdevianFps)
   {

      m_durationPostRedrawProdevian = 1.0_s / dProdevianFps;

   }


   void prodevian::set_nominal_fps(double dNominalFps)
   {

      m_durationPostRedrawNominal = 1._s / dNominalFps;

   }


   void prodevian::set_fps(double dFps)
   {

      set_prodevian_fps(dFps);

      set_nominal_fps(dFps);

   }


   void interaction::prodevian_post_procedure(const ::procedure & procedure)
   {

      if (!is_graphical())
      {

         throw ::exception(error_wrong_state);

      }

      m_pinteractionimpl->m_pprodevian->post_procedure(procedure);

   }


} // namespace user




prodevian::~prodevian()
{

   m_pinteraction->erase_prodevian(this);

}



//void attach_thread_input_to_main_thread(bool bAttach)
//{
//
//   MSG msg;
//
//   if (bAttach)
//   {
//
//      PeekMessage(&msg, nullptr, 0, 0xffffffff, false);
//
//   }
//
//   AttachThreadInput(::GetCurrentThreadId(), (DWORD)get_main_user_itask(), bAttach ? true : false);
//
//}
//


