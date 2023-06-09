#include "framework.h"
#include "interaction_prodevian.h"
#include "interaction_thread.h"
#include "interaction_impl.h"
#include "interaction.h"
#include "acme/constant/message.h"
////#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/message_queue.h"
//#include "acme/primitive/time/floating/operator.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/windowing/window.h"


#if defined(WINDOWS_DESKTOP)
CLASS_DECL_ACME void attach_thread_input_to_main_thread(bool bAttach);
#endif


#if !defined(WINDOWS)
#define PM_NOREMOVE 0
#define PM_REMOVE 1
#endif


#define TIME_REPORTING 0


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


//#ifdef LINUX
//
//
//#include "aura/operating_system/ansi/_ansi.h"
//
//
//#endif


namespace user
{


#if TIME_REPORTING
   
   
   ::time g_timeBetweenUpdateBufferAndUpdateScreen;


#endif


   prodevian::prodevian()
   {

      //m_bUpdateBufferUpdateWindowPending = false;

      m_bRedraw = false;

      m_bAuraMessageQueue = true;

      m_bUpdatingScreen = false;

#ifdef UNIVERSAL_WINDOWS
      m_bExclusiveMode = true;
#else
      m_bExclusiveMode = false;
#endif

      //m_bVisualUpdated = true;

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

      defer_create_synchronization();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_procedureUpdateScreen = [this, pimpl]()
         {

            if (!has_flag(e_flag_destroying) && !has_finishing_flag())
            {

               update_screen();

            }

            m_bUpdatingScreen = false;

            {

               _synchronous_lock synchronouslock(pimpl->synchronization());

               if(pimpl->m_rectangleaNeedRedraw.has_element())
               {

                  auto iRequestsRemaining = pimpl->m_rectangleaNeedRedraw.size();

                  INFORMATION(iRequestsRemaining << " redraw requests remaining after updating the screen.");

                  m_puserinteraction->post_redraw();

               }

            }

         };

      m_procedureWindowShow = [this]()
         {

            if (m_pimpl)
            {

               m_puserinteraction->window_show();

            }

         };

      m_puserinteraction = pimpl->m_puserinteraction;

      m_pimpl = pimpl;

      set_per_second(60);

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

//      if (strType.case_insensitive_contains("list_box"))
//      {
//
//         output_debug_string("list_box");
//
//      }

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

         if (m_puserinteraction->has_destroying_flag())
         {

           m_puserinteraction->post_message(e_message_destroy_window);

         }

      }

      //return m_estatus;

   }


   bool prodevian::prodevian_reset(::user::interaction * pinteraction)
   {

      m_puserinteraction = pinteraction;

      m_timeNow.Now();

      //m_iFrameId = m_timeNow / m_timeFrame;

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

      m_procedureUpdateScreen.m_pbase.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

      if (m_procedureWindowShow)
      {

         m_procedureWindowShow->destroy();

      }

      m_procedureWindowShow.m_pbase.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

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

         if (strType.case_insensitive_contains("filemanager"))
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

         if (!m_puserinteraction->m_pinteractionimpl->m_bOfflineRender)
         {

            if (m_puserinteraction->const_layout().window().display() == e_display_iconic)
            {

               bHasProdevian = false;

            }
            else if (m_puserinteraction->const_layout().window().display() == e_display_notify_icon)
            {

               bHasProdevian = false;

            }
            else if (!::is_visible(m_puserinteraction->const_layout().window().display()))
            {

               bHasProdevian = false;

            }


         }
         

         //synchronous_lock synchronouslock(m_pimpl->synchronization());

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

//            if (strType.case_insensitive_contains("list_box"))
//            {
//
//               output_debug_string("list_box");
//
//            }

            //printf("prodevian get_message(%d)\n", m_message.message);

            int iSkipped = 0;

            while (peek_message(&m_message, NULL, 0, 0))
            {

               if (m_message.m_atom == e_message_redraw || m_message.m_atom == e_message_kick_idle)
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

            INFORMATION("Skipped e_message_redraw count "+ as_string(iSkipped) + "\n");

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

         if(m_pimpl->m_bPendingRedraw && m_pimpl->m_timeLastRedraw.elapsed() < 100_ms)
         {

            return true;

         }

      }

      // e_message_redraw

      if(strType.case_insensitive_contains("filemanager"))
      {

         //INFORMATION("filemanager");

      }

      i64 i1 = ::integral_nanosecond();

      bRedraw = m_message.wParam & 1;

      m_message.wParam &= ~1;

      //if (m_puserinteraction->m_bUpdateBufferPending)
      //{

         prodevian_update_buffer(bRedraw);

      //}

      //m_puserinteraction->m_bUpdateBufferPending = false;

      m_timeNow.Now();

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

         if (m_pimpl->m_bUpdateWindow || m_puserinteraction->m_bUpdateVisual)
         {

            m_puserinteraction->m_bUpdateVisual = false;

            if (m_puserinteraction->m_ewindowflag & e_window_flag_postpone_visual_update)
            {

               bStartWindowVisual = true;

            }

         }

      }

      bool bWait = ((m_pimpl->m_bUpdateWindow || m_pimpl->m_bUpdateScreen) && !bStartWindowVisual) || bRedraw;

      if (bWait)
      {

         auto elapsed = m_timeNow - m_timeLastFrame;

         if (bHasProdevian)
         {

            bWait = elapsed < m_timePostRedrawProdevian.half();

         }
         else
         {

            bWait = elapsed < m_timePostRedrawNominal.half();

         }

      }

      if (bWait)
      {

         // Either:
         // - It has prodevian mode (FPS drawing);
         // - Or it is going to wait because a frame was already drawn an instant ago due on-request-drawing (cool down).

         auto timeFrame = bHasProdevian ? m_timePostRedrawProdevian : m_timePostRedrawNominal ;

         //i64 i2 = get_nanos();

         // calculates the next/memory_new frame atom
         //m_iFrameId = (m_timeNow + timeFrame - 1) / (timeFrame);

         //m_timeNextFrame = m_iFrameId * timeFrame;

         m_timeNextFrame = m_timeNow + timeFrame;

         //m_cLost = (::count) (m_iFrameId - m_iLastFrameId - 1);

         //m_iLastFrameId = m_iFrameId;

         m_timeNextScreenUpdate = m_timeNextFrame;

         auto nanosElapsedSinceLastFrame = m_timeNow - m_timeLastFrame;

         if (nanosElapsedSinceLastFrame > timeFrame)
         {

            // todo display average from last 10 or so frame drawing time and not for every each single offending sample
            // output_debug_string("("+as_string(nanosElapsedSinceLastFrame/1'000'000)+"ms)Frames are taking long to draw. Wait a bit more to free CPU. Is there much load?!?!\n");

            m_timeNextScreenUpdate += timeFrame;

            //m_iLastFrameId++;

         }

         {

            auto timeStartWait = ::time::now();

            auto timeToWaitForNextFrame = m_timeNextScreenUpdate - timeStartWait;

            if (timeToWaitForNextFrame > 1_s)
            {

               //output_debug_string("what?!?!\n");

               timeToWaitForNextFrame = 500_ms;

            }

            if (timeToWaitForNextFrame >= 2_ms)
            {

               //auto timeStart = ::time::now();

               //printf("msToWaitForNextFrame >= 2\n");

               if (timeToWaitForNextFrame < timeFrame)
               {

                  if (timeToWaitForNextFrame >= 50_ms)
                  {

                     //printf("msToWaitForNextFrame >= 50ms (%dms)\n", (::i32) (msToWaitForNextFrame - 1));

                     m_synchronizationa.wait(timeToWaitForNextFrame - 1_ms);

                     //printf("Actually waited %dms\n", (::i32) ::time.elapsed().m_i);

                  }
                  else
                  {

                     //printf("msToWaitForNextFrame < 50\n");

                     if(timeToWaitForNextFrame > 300_ms)
                     {

                        m_evUpdateScreen._wait(timeToWaitForNextFrame);

                     }
                     else
                     {

                        ::preempt(timeToWaitForNextFrame);

                     }

                  }

               }

               //auto elapsed = time.elapsed();

               //printf("msToWaitForNextFrame Waited %d\n", elapsed.m_i);

            }

            auto timeEndWait = ::time::now();

            if (timeEndWait - timeStartWait > 100_ms)
            {

               output_debug_string("Waited more than 100ms to go display drawn frame at screen?!?!\n");

            }

            //{

            //   i64 nanosDeltaPostRedraw = (i64)m_timeNextScreenUpdate - (timeFrame - m_timePostRedraw)  - (i64)get_nanos();

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

            m_puserinteraction->window_show();

            //m_pimpl->window_show();

         }

         //#endif
         ////END IFDEF LINUX

      }

      // if (m_bVisualUpdated)
      // {

      //    m_bVisualUpdated = false;

      //    if (::is_set(m_pimpl->m_puserthread))
      //    {

      //       m_pimpl->m_puserthread->m_evApplyVisual.wait(15_s);

      //    }

      // }

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

      auto e1 = g_timeBetweenUpdateBufferAndUpdateScreen.elapsed();
      
      ::time timeUpdateScreenPost;
      
      timeUpdateScreenPost.Now();

      output_debug_string("timeBetweenUpdateBufferAndUpdateScreen "+as_string(e1.floating_millisecond().m_d) +"ms\n");

#endif

      //if (m_bUpdateScreen && (bWindowsApplyVisual || !bStartWindowVisual))
      {



         prodevian_update_screen();

      }
      //else
      //{

      //   INFORMATION("no update screen");

      //}

#if TIME_REPORTING

      auto e2 = timeUpdateScreenPost.elapsed();

      output_debug_string("timeUpdateScreenPost " + as_string(e2.floating_millisecond().m_d) + "ms\n");

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

            m_puserinteraction->window_show();

            //m_pimpl->m_pwindow->window_show();
            //m_puserinteraction->post_procedure(m_procedureWindowShow);

         }
         // ENDIF WINDOWS
      }

      {

         synchronous_lock sl(synchronization());

         auto timeNow = ::time::now();

         for (index i = 0; i < m_timeaFrame.get_size();)
         {

            auto timeFrame = m_timeaFrame[i];

            auto timeDiff = timeNow - timeFrame;

            if (timeDiff > 1_s)
            {

               m_timeaFrame.erase_at(i);

            } else
            {

               break;

            }

         }

      }

      if(!m_pimpl)
      {

         return false;

      }

      m_pimpl->m_frequencyOutputFramesPerSecond = (double)(m_timeaFrame.get_size());

      return true;

   }


   bool prodevian::prodevian_update_buffer(bool bRedraw)
   {

      m_bRedraw = bRedraw;

      m_pimpl->m_bUpdateBuffer = false;

      m_pimpl->m_bUpdateScreen = false;

      m_pimpl->m_bUpdateWindow = false;

      //update_buffer(m_bUpdateBuffer, m_bUpdateScreen, m_bUpdateWindow, bRedraw);

      update_buffer();

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

         m_timeLastScreenUpdate.Now();

         m_bUpdatingScreen = true;

         m_pimpl->m_pwindow->update_screen();

         //if (!m_bUpdatingScreen || m_timeLastScreenUpdate.elapsed() > 200_ms)
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



   //void prodevian::update_buffer(bool & bUpdateBuffer, bool & bUpdateScreen, bool & bUpdateWindow, bool bForce)
   void prodevian::update_buffer()
   {

      try
      {

         synchronous_lock synchronouslock(m_puserinteraction->synchronization());

         if(!m_puserinteraction)
         {

            return;

         }

         //bUpdateBuffer = false;

         //bUpdateWindow = false;

         i64 i1 = ::integral_nanosecond();

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


         if (!m_pimpl)
         {

            return;

         }

         synchronouslock.unlock();

         m_timeBeforeDrawing.Now();

         m_timeOutOfDrawing = m_timeBeforeDrawing - m_timeAfterDrawing;

         i64 i2 = ::integral_nanosecond();

#if TIME_REPORTING

         static ::time timeLast;

         output_debug_string("time outside updatebuffer " +as_string(timeLast.elapsed().floating_millisecond().m_d) + "ms\n");

#endif

         m_pimpl->do_graphics();

#if TIME_REPORTING

         timeLast.Now();

         g_timeBetweenUpdateBufferAndUpdateScreen.Now();

#endif


         m_timeAfterDrawing.Now();

         m_timeDuringDrawing = m_timeAfterDrawing - m_timeBeforeDrawing;

         if (m_puserinteraction)
         {

            m_puserinteraction->on_after_graphical_update();

         }

         if (m_puserinteraction)
         {

            m_puserinteraction->m_bNeedRedraw = false;

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

         if(strType.case_insensitive_contains("list_box"))
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

//         if (is_different(m_puserinteraction->m_ewindowflag & e_window_flag_on_show_window_visible,
//            m_puserinteraction->is_this_visible())
//            || is_different(m_puserinteraction->m_ewindowflag & e_window_flag_on_show_window_screen_visible,
//               m_puserinteraction->is_window_screen_visible()))
//         {
//
//            m_puserinteraction->m_ewindowflag.set(e_window_flag_on_show_window_visible, m_puserinteraction->is_this_visible());
//
//            m_puserinteraction->m_ewindowflag.set(e_window_flag_on_show_window_screen_visible, m_puserinteraction->is_window_screen_visible());
//
//            m_puserinteraction->_on_show_window();
//
//         }

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
    
      m_timeBeforeUpdateScreen.Now();

      m_timeOufOfUpdateScreen = m_timeBeforeUpdateScreen - m_timeAfterUpdateScreen;

   }


   void prodevian::profiling_on_after_update_screen()
   {

      synchronous_lock sl(synchronization());
      
      m_timeLastFrame.Now();

      m_timeaFrame.add(m_timeLastFrame);

      m_timeAfterUpdateScreen.Now();

      m_timeDuringUpdateScreen = m_timeAfterUpdateScreen - m_timeBeforeUpdateScreen;

      if (m_timeDuringUpdateScreen > 60_ms)
      {

         //output_debug_string("It took about " + as_string(m_timeDuringUpdateScreen) + " to update screen\n");

         //output_debug_string("It took about " + as_string(m_timeOufOfUpdateScreen) + " out of screen update\n");

      }

      m_timeDuringUpdateScreen = m_timeAfterUpdateScreen - m_timeBeforeUpdateScreen;

      if (m_timeOufOfUpdateScreen > 60_ms)
      {

         //output_debug_string("It took about " + as_string(m_timeDuringUpdateScreen) + " to update screen\n");

         //output_debug_string("It took about " + as_string(m_timeOufOfUpdateScreen) + " out of screen update\n");

      }
      
   }

   
   void prodevian::defer_prodevian_step()
   {

      if (m_timeLastFrame.elapsed() > (m_timePostRedrawNominal * 3 / 4))
      {

         post_message(e_message_redraw);

      }

   }


   void prodevian::set_prodevian_frames_per_second(::frequency frequencyProdevianFramesPerSecond)
   {

      m_timePostRedrawProdevian = 1.0 / frequencyProdevianFramesPerSecond;

   }


   void prodevian::set_nominal_frames_per_second(::frequency frequencyNominalFramesPerSecond)
   {

      m_timePostRedrawNominal = 1.0 / frequencyNominalFramesPerSecond;

   }


   void prodevian::set_per_second(::frequency frequencyFramesPerSecond)
   {

      set_prodevian_frames_per_second(frequencyFramesPerSecond);

      set_nominal_frames_per_second(frequencyFramesPerSecond);

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


