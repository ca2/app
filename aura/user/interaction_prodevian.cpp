#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "aura/message.h"
#include "interaction_prodevian.h"
#include "interaction_thread.h"
#include "acme/parallelization/mq.h"


#ifdef LINUX
#include "aura/os/ansios/_ansios.h"
#endif


namespace user
{


   prodevian::prodevian()
   {

      m_bAuraMessageQueue = true;

      m_bUpdatingScreen = false;

      m_bExclusiveMode = false;

      m_bVisualUpdated = true;

      m_bSimpleMessageLoop = false;

   }


   prodevian::~prodevian()
   {

   }


#ifdef DEBUG


   i64 prodevian::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::thread::add_ref(OBJ_REF_DBG_ARGS);

   }


   i64 prodevian::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::thread::dec_ref(OBJ_REF_DBG_ARGS);

   }


   i64 prodevian::release(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::thread::release(OBJ_REF_DBG_ARGS);

   }


#endif


   ::estatus prodevian::initialize_prodevian(interaction_impl * pimpl)
   {

      auto estatus = initialize(pimpl);

      if (!estatus)
      {

         return estatus;

      }

      m_routineUpdateScreen = __routine([this]()
         {

            if (!m_bitFinishing && !m_bitSetFinish)
            {

               update_screen();

            }

            m_bUpdatingScreen = false;

         });

      m_routineWindowShow = __routine([this]()
         {

            if (m_pimpl)
            {

               m_pimpl->window_show();

            }

         });

      m_puserinteraction = pimpl->m_puserinteraction;

      m_pimpl = pimpl;

      set_config_fps(20);

      string strType;

      strType = ::str::demangle(m_puserinteraction->type_name());

      if (strType.contains("playlist"))
      {

         INFO("frame playlist");

      }

      return estatus;

   }




   ::estatus prodevian::run()
   {

      //m_pimpl->m_puserinteraction->task_add(this);

      m_synca.add(&m_evUpdateScreen);

   #ifdef WINDOWS_DESKTOP

      attach_thread_input_to_main_thread(true);

   #endif

      if (m_bAuraMessageQueue)
      {

         m_synca.add(&get_mq()->m_eventNewMessage);

      }

      ::set_thread_name("prodevian," + ::str::demangle(m_puserinteraction->type_name()));

      while (thread_get_run())
      {

         pump_runnable();

         if (!m_puserinteraction)
         {

            break;

         }

         if (!m_pimpl)
         {

            break;

         }

         if (!prodevian_iteration())
         {

            break;

         }

         if (!m_puserinteraction)
         {

            break;

         }

         if (!m_pimpl)
         {

            break;

         }

      }

      return m_estatus;

   }


bool prodevian::prodevian_reset(::user::interaction * pinteraction)
{

   m_puserinteraction = pinteraction;

   m_nanosNow = get_nanos();

   m_iFrameId = m_nanosNow / m_nanosFrame;

   m_iLastFrameId = m_iFrameId;

   return true;

}


void prodevian::term_thread()
{

   if (m_pimpl)
   {

      if (m_pimpl->m_pprodevian == this)
      {

         m_pimpl->__release(m_pimpl->m_pprodevian);

      }

   }

   m_nanotimer.close_timer();

   ::thread::term_thread();

   m_pimpl.release();

   m_puserinteraction.release();

   if (m_routineUpdateScreen)
   {

      m_routineUpdateScreen->finalize();

   }

   m_routineUpdateScreen.release(OBJ_REF_DBG_THIS);

   if (m_routineWindowShow)
   {

      m_routineWindowShow->finalize();

   }

   m_routineWindowShow.release(OBJ_REF_DBG_THIS);

}


void prodevian::finalize()
{

   m_evUpdateScreen.SetEvent();

   m_puserinteraction.release(OBJ_REF_DBG_THIS);

   m_pimpl.release(OBJ_REF_DBG_THIS);

   m_synca.clear();
   
   ::thread::finalize();

}


#undef EXTRA_PRODEVIAN_ITERATION_LOG


bool prodevian::prodevian_iteration()
{

   bool bHasProdevian = false;

   bool bRedraw = false;

   string strType;

   try
   {

      sync_lock sl(m_puserinteraction->mutex());

      strType = ::str::demangle(m_puserinteraction->type_name());

      if (strType.contains_ci("filemanager"))
      {

         //INFO("filemanager frame... ");

      }

      if(!m_puserinteraction)
      {

         return false;

      }

      if (m_puserinteraction->m_ewindowflag & window_flag_embedded_prodevian)
      {

         bHasProdevian = false;

      }
      else if (m_puserinteraction->m_pimpl2.is_null())
      {

         bHasProdevian = false;

      }
      else
      {

         bHasProdevian = m_puserinteraction->has_prodevian();

         //sync_lock sl(m_pimpl->mutex());

      }

   }
   catch(...)
   {

   }

   if (!(m_puserinteraction->m_ewindowflag & window_flag_embedded_prodevian))
   {

      if (m_puserinteraction->m_pimpl2.is_null() || !bHasProdevian)
      {

         m_puserinteraction->m_ewindowflag -= window_flag_redraw_in_queue;

         if (!get_message(&m_message, NULL, 0, 0))
         {

            return false;

         }

         //printf("prodevian get_message(%d)\n", m_message.message);

         int iSkipped = 0;

         while (peek_message(&m_message, NULL, 0, 0, PM_NOREMOVE))
         {

            if (m_message.message == e_message_redraw ||
               m_message.message == WM_KICKIDLE)
            {

               iSkipped++;

               peek_message(&m_message, NULL, 0, 0, PM_REMOVE);

            }
            else
            {

               break;

            }

         }

#ifdef EXTRA_PRODEVIAN_ITERATION_LOG

         INFO("Skipped e_message_redraw count "+ ::str::from(iSkipped) + "\n");

#endif

         if (m_message.message == e_message_null)
         {

            return true;

         }
         else if (m_message.message != e_message_redraw)
         {

            return true;

         }
         else if (!this->thread_get_run())
         {

            return false;

         }

         bRedraw = true;

      }
      else
      {

         while (peek_message(&m_message, NULL, 0, 0, PM_REMOVE))
         {

            if (m_message.message == e_message_null)
            {

               return true;

            }
            else if (m_message.message != e_message_redraw)
            {

               return true;

            }

            bRedraw = true;

         }

         if (!this->thread_get_run())
         {

            return false;

         }

      }

   }

   if(!m_puserinteraction)
   {

      return false;

   }

   if(m_puserinteraction->m_ewindowflag & window_flag_postpone_visual_update)
   {

      if(m_pimpl->m_bPendingRedraw && m_pimpl->m_millisLastRedraw.elapsed() < 100_ms)
      {

         return true;

      }

   }

   // e_message_redraw

   if(strType.contains_ci("filemanager"))
   {

      //INFO("filemanager");

   }

   i64 i1 = get_nanos();

   bRedraw = m_message.wParam & 1;

   m_message.wParam &= ~1;

   bool bUpdateBuffer = false;

   bool bUpdateWindow = false;

   update_buffer(bUpdateBuffer, bUpdateWindow, bRedraw);

   m_nanosNow = get_nanos();

   if (!this->thread_get_run())
   {

      return false;

   }

   bool bUpdateScreen = bUpdateBuffer;

   if (m_puserinteraction && m_puserinteraction->GetExStyle() & WS_EX_LAYERED)
   {

      bUpdateScreen |= bUpdateWindow;

   }

   bool bStartWindowVisual = false;

   if (m_puserinteraction)
   {

      if (bUpdateWindow || m_puserinteraction->m_bUpdateVisual)
      {

         m_puserinteraction->m_bUpdateVisual = false;

         if (m_puserinteraction->m_ewindowflag & window_flag_postpone_visual_update)
         {

            bStartWindowVisual = true;

         }

      }

   }

   bool bWait = (bUpdateScreen && !bStartWindowVisual) || bRedraw;

   if (bHasProdevian || (bWait && ((m_nanosNow - m_nanosLastFrame) < m_nanosPostRedraw / 2)))
   {

      // Either:
      // - It has prodevian mode (FPS drawing);
      // - Or it is going to wait because a frame was already drawn an instant ago due on-request-drawing (cool down).

      i64 nanosFrame = bRedraw ? m_nanosPostRedraw : m_nanosFrame;

      i64 i2 = get_nanos();

      // calculates the next/new frame id
      m_iFrameId = (m_nanosNow + nanosFrame - 1) / (nanosFrame);

      m_nanosNextFrame = m_iFrameId * nanosFrame;

      m_cLost = (::count) (m_iFrameId - m_iLastFrameId - 1);

      m_iLastFrameId = m_iFrameId;

      m_nanosNextScreenUpdate = m_nanosNextFrame;

      auto nanosElapsedSinceLastFrame = m_nanosNow - m_nanosLastFrame;

      if (nanosElapsedSinceLastFrame > nanosFrame)
      {

         // todo display average from last 10 or so frame drawing time and not for every each single offending sample
         // output_debug_string("("+__str(nanosElapsedSinceLastFrame/1'000'000)+"ms)Frames are taking long to draw. Wait a bit more to free CPU. Is there much load?!?!\n");

         m_nanosNextScreenUpdate += nanosFrame;

         m_iLastFrameId++;

      }

      {

         auto nanosStartWait = (i64)get_nanos();

         i64 nanosToWaitForNextFrame = (i64)m_nanosNextScreenUpdate - (i64)get_nanos();

         i32 msToWaitForNextFrame = (::i32)(nanosToWaitForNextFrame / 1'000'000);

         if (nanosToWaitForNextFrame > 1'000'000'000)
         {

            //output_debug_string("what?!?!\n");

            nanosToWaitForNextFrame = 500'000'000;

         }

         if (msToWaitForNextFrame >= 2)
         {

            ::millis tickWait;

            tickWait.Now();

            //printf("msToWaitForNextFrame >= 2\n");

            if (msToWaitForNextFrame >= 50)
            {

               //printf("msToWaitForNextFrame >= 50ms (%dms)\n", (::i32) (msToWaitForNextFrame - 1));

               ::millis millis;

               millis.Now();

               m_synca.wait(false, ::millis(msToWaitForNextFrame - 1));

               //printf("Actually waited %dms\n", (::i32) millis.elapsed().m_i);

            }
            else
            {

               //printf("msToWaitForNextFrame < 50\n");

               m_evUpdateScreen.wait(millis(msToWaitForNextFrame));

            }

            auto elapsed = tickWait.elapsed();

            //printf("msToWaitForNextFrame Waited %d\n", elapsed.m_i);

         }

         auto nanosEndWait = (i64)get_nanos();

         if (nanosEndWait - nanosStartWait > 100'000'000)
         {

            output_debug_string("Waited more than 100ms to go display drawn frame at screen?!?!\n");

         }

         //{

         //   i64 nanosDeltaPostRedraw = (i64)m_nanosNextScreenUpdate - (nanosFrame - m_nanosPostRedraw)  - (i64)get_nanos();

         //   i32 msDeltaPostRedraw = (::i32)(nanosDeltaPostRedraw / 1'000'000);

         //   if (msDeltaPostRedraw >= 1)
         //   {

         //      sleep(msDeltaPostRedraw);

         //   }


         //}

         m_evUpdateScreen.ResetEvent();

      }

   }

   if (!this->thread_get_run())
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

   if (!(m_puserinteraction->m_ewindowflag & window_flag_postpone_visual_update))
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

         m_pimpl->m_puserthread->m_evApplyVisual.wait(seconds(15));

      }

   }

   if (!this->thread_get_run())
   {

      return false;

   }

   bool bWindowsApplyVisual = true;

   if (bUpdateScreen && (bWindowsApplyVisual || !bStartWindowVisual))
   {

      if (m_bExclusiveMode)
      {

         update_screen();

      }
      else
      {

         //if (!m_bUpdatingScreen || m_millisLastScreenUpdate.elapsed() > 200_ms)
         {

            m_millisLastScreenUpdate.Now();

            m_bUpdatingScreen = true;

            if(m_puserinteraction)
            {

               m_puserinteraction->post_routine(m_routineUpdateScreen);

            }

         }

      }

   }
   
   if (!m_puserinteraction)
   {

      return false;

   }

   if ((m_puserinteraction->m_ewindowflag & window_flag_postpone_visual_update))
   {
      // IFDEF WINDOWS
      if (bStartWindowVisual)
      {

         m_puserinteraction->post_routine(m_routineWindowShow);

      }
      // ENDIF WINDOWS
   }

   u64 uNow = get_nanos();

   for (index i = 0; i < m_iaFrame.get_size();)
   {

      u64 uFrame = m_iaFrame[i];

      u64 uDiff = uNow - uFrame;

      if (uDiff > 1'000'000'000LL)
      {

         m_iaFrame.remove_at(i);

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

   m_pimpl->m_dOutputFps = (double)(m_iaFrame.get_size());

   return true;

}


   void prodevian::update_buffer(bool & bUpdateBuffer, bool & bUpdateWindow, bool bForce)
   {

      try
      {

         sync_lock sl(m_puserinteraction->mutex());

         if(!m_puserinteraction)
         {

            return;

         }

         bUpdateBuffer = false;

         bUpdateWindow = false;

         i64 i1 = get_nanos();

         bool bTransparentDraw;

      #ifdef WINDOWS_DESKTOP

         if (m_puserinteraction->GetExStyle() & WS_EX_LAYERED)
         {

            bTransparentDraw = true;

         }
         else
         {

            bTransparentDraw = false;

         }

      #else

         bTransparentDraw = true;

      #endif

         if (!::thread_get_run())
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

         if (!m_puserinteraction->m_bLockWindowUpdate)
         {

            sl.unlock();

            ::draw2d::graphics_pointer pgraphicsNull;

            //m_puserinteraction->update_modified();

            m_puserinteraction->sketch_to_design(pgraphicsNull, bUpdateBuffer, bUpdateWindow);

            sl.lock();

            if(!m_puserinteraction)
            {

               return;

            }

            if (!this->thread_get_run())
            {

               return;

            }

            if(!m_puserinteraction)
            {

               return;

            }

            bool bIsThisScreenVisible = m_puserinteraction->layout().design().is_screen_visible();

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

         if (m_puserinteraction->m_bitFinishing
            || m_puserinteraction->m_bitSetFinish
            || m_pimpl->m_bitFinishing
            || m_pimpl->m_bitSetFinish)
         {

            bDraw = false;

         }

         if (bDraw && m_pimpl)
         {

            sl.unlock();

            m_millisBeforeDrawing.Now();

            m_millisOutOfDrawing = m_millisBeforeDrawing - m_millisAfterDrawing;

            i64 i2 = get_nanos();

            m_pimpl->_001UpdateBuffer();

            bUpdateBuffer = true;

            m_millisAfterDrawing.Now();

            m_millisDuringDrawing = m_millisAfterDrawing - m_millisBeforeDrawing;

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

      try
      {

         m_millisBeforeUpdateScreen.Now();

         m_millisOufOfUpdateScreen = m_millisBeforeUpdateScreen - m_millisAfterUpdateScreen;

         if (!m_pimpl)
         {

            return false;

         }

         m_pimpl->prodevian_update_screen();

         if (!m_puserinteraction)
         {

            return false;

         }

         if (is_different(m_puserinteraction->m_ewindowflag & window_flag_on_show_window_visible,
            m_puserinteraction->is_this_visible())
            || is_different(m_puserinteraction->m_ewindowflag & window_flag_on_show_window_screen_visible,
               m_puserinteraction->is_window_screen_visible()))
         {

            m_puserinteraction->m_ewindowflag.set(window_flag_on_show_window_visible, m_puserinteraction->is_this_visible());

            m_puserinteraction->m_ewindowflag.set(window_flag_on_show_window_screen_visible, m_puserinteraction->is_window_screen_visible());

            m_puserinteraction->_on_show_window();

         }

         m_nanosLastFrame = get_nanos();

         m_iaFrame.add(m_nanosLastFrame);

         m_millisAfterUpdateScreen.Now();

         m_millisDuringUpdateScreen = m_millisAfterUpdateScreen - m_millisBeforeUpdateScreen;

         if (m_millisDuringUpdateScreen > 60)
         {

            //output_debug_string("It took about " + __str(m_millisDuringUpdateScreen) + " to update screen\n");

            //output_debug_string("It took about " + __str(m_millisOufOfUpdateScreen) + " out of screen update\n");

         }

         m_millisDuringUpdateScreen = m_millisAfterUpdateScreen - m_millisBeforeUpdateScreen;

         if (m_millisOufOfUpdateScreen > 60)
         {

            //output_debug_string("It took about " + __str(m_millisDuringUpdateScreen) + " to update screen\n");

            //output_debug_string("It took about " + __str(m_millisOufOfUpdateScreen) + " out of screen update\n");

         }

      }
      catch(...)
      {

         return false;

      }

      return true;

   }


   void prodevian::defer_prodevian_step()
   {

      if ((get_nanos() - m_nanosLastFrame) > (m_nanosFrame * 3 / 4))
      {

         post_message(e_message_redraw);

      }

   }



   void prodevian::set_config_fps(double dConfigFps)
   {

      m_nanosPostRedraw = (u64)(1'000'000'000.0 / 60.0);

      m_nanosFrame = (u64)(1'000'000'000.0 / m_pimpl->m_dConfigFps);

      m_nanosPostRedraw = min(m_nanosPostRedraw, m_nanosFrame);

   }


   void interaction::prodevian_post_routine(const ::promise::routine & routine)
   {

      if (is_graphical())
      {

         m_pimpl2->m_pprodevian->post_task(routine);

      }

   }


} // namespace user




prodevian::~prodevian()
{

   m_pinteraction->remove_prodevian(this);

}
