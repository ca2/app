#include "framework.h"
#if defined(WINDOWS_DESKTOP)
CLASS_DECL_ACME void attach_thread_input_to_main_thread(bool bAttach);
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#endif
#include "aura/user/user/frame_interaction.h"
#include "interaction_graphics_thread.h"
#include "interaction_thread.h"
//#include "interaction_impl.h"
#include "interaction.h"
#include "acme/constant/message.h"
////#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/message_queue.h"
#include "acme/platform/node.h"
#include "acme/prototype/time/_text_stream.h"
#include "acme/prototype/datetime/_text_stream.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/windowing/window.h"


#define MORE_LOG
#undef MORE_LOG


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


   graphics_thread::graphics_thread()
   {

      //m_bUpdateBufferUpdateWindowPending = false;

      //m_bRedraw = false;


      m_iRedrawMessageCount = 0;

      m_bAuraMessageQueue = true;

      m_bUpdatingScreen = false;

      m_bGraphicsThreadEnabled = false;

      //m_happeningReady.reset_happening();

//#ifdef UNIVERSAL_WINDOWS
//      m_bExclusiveMode = true;
//#else
//      m_bExclusiveMode = false;
//#endif

      //m_bVisualUpdated = true;

      //m_bSimpleMessageLoop = false;

   }


   graphics_thread::~graphics_thread()
   {

   }


#ifdef _DEBUG


   long long graphics_thread::increment_reference_count()
   {

      return ::thread::increment_reference_count();

   }


   long long graphics_thread::decrement_reference_count()
   {

      return ::thread::decrement_reference_count();

   }


   long long graphics_thread::release()
   {

      return ::thread::release();

   }


#endif


   void graphics_thread::install_message_routing(::channel * pchannel)
   {

      ::thread::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_redraw, pchannel, this, &graphics_thread::on_message_redraw);

   }


   void graphics_thread::defer_create_graphics_thread()
   {

      //__refer(m_pgraphicsthread, m_puserinteraction->windowing_window()->m_pgraphicsthread);

      //if(m_pgraphicsthread)
      {

         if (!(m_puserinteraction->m_ewindowflag & e_window_flag_embedded_graphics_thread_if_child))
         {

            
            m_puserinteraction->user_thread()->_post([this]()
                                                     {
               
               branch();
               
            });
            
////            m_puserinteraction->m_pus

            //m_puserinteraction->add_task(this);

            //if (!branch())
            //{

            //   //__release(m_pgraphicsthread);

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


   void graphics_thread::initialize_graphics_thread(::user::interaction * puserinteraction)
   {

      //auto estatus = 
      
      initialize(puserinteraction);

      defer_create_synchronization();

      //if (!estatus)
      //{

      //   return estatus;

      //}

//      m_procedureUpdateScreen = [this, pimpl]()
//         {
//
//            if (!has_flag(e_flag_destroying) && !has_finishing_flag())
//            {
//
//               update_screen();
//
//            }
//
//            m_bUpdatingScreen = false;
//
//            {
//
//               _synchronous_lock synchronouslock(pimpl->synchronization());
//
//               if(pimpl->m_redrawitema.has_element())
//               {
//
//                  auto iRequestsRemaining = pimpl->m_redrawitema.size();
//
//                  information() << iRequestsRemaining << " redraw requests remaining after updating the screen.";
//
//                  m_puserinteraction->post_redraw();
//
//               }
//
//            }
//
//         };

//      m_procedureWindowShow = [this]()
//         {
//
//            if (m_puserinteraction->windowing_window())
//            {
//
//               m_puserinteraction->window_show();
//
//            }
//
//         };

      m_puserinteraction = puserinteraction;

      //m_puserinteraction->windowing_window() = pimpl;

      set_per_second(60);

      string strType;

      strType = ::type(m_puserinteraction).name();

      if (strType.contains("playlist"))
      {

         information() << "frame playlist";

      }

      //return estatus;

   }

   
   //void graphics_thread::do_task()
   //{

   //   return ::thread::do_task();

   //}


//   int graphics_thread::thread_index()
//   {
//
//      _synchronous_lock sl(this->synchronization());
//
//      auto iTask = ::current_itask();
//
//      auto iThreadIndex = m_iaThread.find_first(iTask);
//
//      if(iThreadIndex < 0)
//      {
//
//         iThreadIndex = m_iaThread.add(iTask);
//
//      }
//
//      return iThreadIndex;
//
//   }


   void graphics_thread::run()
   {

      string strType = ::type(m_puserinteraction).name();

      ::task_set_name("graphics_thread," + strType);

      //m_puserinteraction->windowing_window()->m_puserinteraction->task_add(this);

      //m_happeningReady.wait();

      __defer_raw_construct_new(m_phappeningUpdateScreen);

      m_synchronizationa.add(m_phappeningUpdateScreen);

   #ifdef WINDOWS_DESKTOP

      attach_thread_input_to_main_thread(true);

   #endif

      if (m_bAuraMessageQueue)
      {

         m_synchronizationa.add(get_message_queue()->m_phappeningNewMessage);

      }

//      if (strType.case_insensitive_contains("list_box"))
//      {
//
//         informationf("list_box");
//
//      }

      //m_puserinteraction->add_task(this);

      //m_puserinteraction->m_pthreadUserInteraction->add_task(this);

      //add_task(m_puserinteraction);

      ::parallelization::set_priority(::e_priority_highest);
#ifdef WINDOWS_DESKTOP
      auto i = GdiSetBatchLimit(20);
      auto i2 = GdiGetBatchLimit();
      printf("result %d", i);
      printf("result2 %d", i2);
#endif

      m_timeStart.Now();

      try
      {

         while (true)
         {

            
            if(has_finishing_flag())
            {
               if (!task_get_run())
               {
                  
                  information() << "graphics_thread::run !task_get_run()";
                  
                  break;
                  
               }
               
            }
            else
            {
               if (!task_get_run())
               {
                  
                  information() << "graphics_thread::run !task_get_run()";
                  
                  break;
                  
               }
               
            }

            if(!m_bGraphicsThreadEnabled)
            {

               preempt(100_ms);

               continue;

            }

            task_iteration();

            defer_process_redraw_message();

         }

      }
      catch (::exception&)
      {

         information() << "graphics_thread::run exception!!";

      }
      catch (...)
      {

         information() << "graphics_thread::run exception (...) !!";

      }

      //if (m_puserinteraction)
      //{

      //   if (m_puserinteraction->has_destroying_flag())
      //   {

      //     m_puserinteraction->post_message(e_message_destroy_window);

      //   }

      //}

      //return m_estatus;

   }


   void graphics_thread::on_message_redraw(::message::message * pmessage)
   {

      m_iRedrawMessageCount++;

   }


   bool graphics_thread::wait_for_redraw_message()
   {

      auto pwindow = m_puserinteraction->window();

      if (pwindow->m_redrawitema.has_element())
      {

         return true;

      }

      while(::task_get_run())
      {

         m_puserinteraction->m_ewindowflag -= e_window_flag_redraw_in_queue;

         get_message(&m_message, nullptr, 0, 0);

         if (m_message.m_emessage == e_message_quit)
         {

            ::string strType = type(m_puserinteraction).name();

            information()(e_trace_category_graphics_thread) << "Graphics Thread has quit!! " << strType;

            return false;

         }
         
         int iRedrawMessageCount = 0;
         
         if (m_message.m_emessage == e_message_redraw)
         {

            iRedrawMessageCount = 1;

         }

         //dispatch_message(&m_message);

         while (peek_message(&m_message, nullptr, 0, 0, true))
         {

            if (m_message.m_emessage == e_message_redraw)
            {

               iRedrawMessageCount++;

            }

         }

         if (iRedrawMessageCount > 0)
         {

            return true;

         }


#ifdef EXTRA_PRODEVIAN_ITERATION_LOG

         information() << "Skipped e_message_redraw count "+ as_string(iRedrawMessageCount) + "\n";

#endif

//         if (iRedrawMessageCount <= 0)
//         {
//
//            return true;
//
//         }

      }

      return false;

   }


   bool graphics_thread::clear_message_queue()
   {

      while (peek_message(&m_message, NULL, 0, 0, true))
      {

         if(m_message.m_emessage == e_message_quit)
         {

            return false;

         }

//               if (m_message.m_emessage == e_message_null)
//               {
//
//                  return true;
//
//               }
//               else if (m_message.m_emessage != e_message_redraw)
//               {
//
//                  return true;
//
//               }

      }

      return true;

   }


   bool graphics_thread::defer_process_redraw_message()
   {

      //m_bFps = false;

      {

         _synchronous_lock synchronouslock(m_puserinteraction->synchronization());

         ASSERT(!(m_puserinteraction->m_ewindowflag & e_window_flag_embedded_graphics_thread_if_child));

         m_bFps = m_puserinteraction->has_fps_output_purpose();

         if (!m_puserinteraction
            || !m_puserinteraction->windowing_window())
         {

            return false;

         }

//         if (!m_puserinteraction->windowing_window()->m_bOfflineRender)
//         {
//
////            if (m_puserinteraction->const_layout().window().display() == e_display_iconic)
////            {
////
////               m_bAutoRefresh = false;
////
////            }
////            else if (m_puserinteraction->const_layout().window().display() == e_display_notify_icon)
////            {
////
////               m_bAutoRefresh = false;
////
////            }
////            else if (!::is_visible(m_puserinteraction->const_layout().design().display()))
////            {
////
////               m_bAutoRefresh = false;
////
////            }
//
//         }

      }

      //if (!(m_puserinteraction->m_ewindowflag & e_window_flag_embedded_graphics_thread_if_child))
      //{

         //if (!m_bAutoRefresh)
//          if (m_puserinteraction->has_fps_output_purpose())
//          {
//
//             if(!clear_message_queue())
//             {
//
//                return false;
//
//             }
//
//          }
//          // else if(m_iRedrawMessageCount <= 0)
//          // {
//          //    return true;
//          // }
//
//             //if (!wait_for_redraw_message())
//             //{
//
//               // information() << "defer_process_redraw_message exit (1)";
//
//                //return true;
//
//             //}
//
//             //while (peek_message(&m_message, nullptr, e_message_redraw, e_message_redraw, true))
//             //{
//
//
//             //}
//
// //            while (peek_message(&m_message, NULL, 0, 0, true))
// //            {
// //
// ////               if (m_message.m_emessage == e_message_null)
// ////               {
// ////
// ////                  return true;
// ////
// ////               }
// ////               else if (m_message.m_emessage != e_message_redraw)
// ////               {
// ////
// ////                  return true;
// ////
// ////               }
// //
// //            }
//
//         // }
//
//       //}
//
//       m_iRedrawMessageCount = 0;

      if(m_puserinteraction->m_ewindowflag & e_window_flag_postpone_visual_update)
      {

         if(m_puserinteraction->windowing_window()->m_bPendingRedraw && m_puserinteraction->windowing_window()->m_timeLastRedraw.elapsed() < 100_ms)
         {

            information() << "defer_process_redraw_message exit (2)";

            return true;

         }

      }

      try
      {

         if (!graphics_thread_iteration())
         {

            return false;

         }

      }
      catch(...)
      {

         information() << "exception while running graphics_thread_iteration";

      }

      return true;

   }


   bool graphics_thread::graphics_thread_reset(::user::interaction * pinteraction)
   {

      m_puserinteraction = pinteraction;

      //m_timeNow.Now();

      //m_iFrameId = m_timeNow / m_timeFrame;

      //m_iLastFrameId = m_iFrameId;

      return true;

   }


   void graphics_thread::term_task()
   {

      auto puserinteraction = m_puserinteraction;

      if(puserinteraction)
      {

         auto pacmewindowingwindow = puserinteraction->m_pacmewindowingwindow.m_p;

         if (pacmewindowingwindow)
         {

            ::cast < ::windowing::window > pwindow = pacmewindowingwindow;

            if (pwindow)
            {

               if (pwindow->m_pgraphicsthread == this)
               {

                  pwindow->m_pgraphicsthread.release();
               
               }


            }


         }


      }

      m_nanosecondtimer.close_timer();

      ::thread::term_task();

      //m_puserinteraction->windowing_window().release();

      m_puserinteraction.release();

//      if (m_procedureUpdateScreen)
//      {
//
//         m_procedureUpdateScreen->destroy();
//
//      }
//
//      m_procedureUpdateScreen.m_pbase.release();

//      if (m_procedureWindowShow)
//      {
//
//         m_procedureWindowShow->destroy();
//
//      }
//
//      m_procedureWindowShow.m_pbase.release();

   }


   void graphics_thread::destroy()
   {

      m_phappeningUpdateScreen->set_happening();

      m_puserinteraction.release();

      //m_puserinteraction->windowing_window().release();

      m_synchronizationa.clear();

      //auto estatus = 
      
      ::thread::destroy();

      //return estatus;

   }


   #undef EXTRA_PRODEVIAN_ITERATION_LOG


   bool graphics_thread::wait_to_present()
   {


      //m_puserinteraction->m_bUpdateBufferPending = false;


      if (!this->task_get_run())
      {

         return false;

      }

      //if (m_puserinteraction && m_puserinteraction->GetExStyle() & WS_EX_LAYERED)
      //{

      //   m_bUpdateWindow |= m_bUpdateBuffer;

      //}

//      bool bStartWindowVisual = false;
//
//      if (m_puserinteraction)
//      {
//
//         if (m_puserinteraction->m_bUpdateWindow || m_puserinteraction->m_bUpdateVisual)
//         {
//
//            m_puserinteraction->m_bUpdateVisual = false;
//
//            if (m_puserinteraction->m_ewindowflag & e_window_flag_postpone_visual_update)
//            {
//
//               bStartWindowVisual = true;
//
//            }
//
//         }
//
//      }
//
//      //bool bWait = ((m_puserinteraction->m_bUpdateWindow || m_puserinteraction->m_bUpdateScreen) && !bStartWindowVisual) || m_bRedraw;
//
//      bool bWait = ((m_puserinteraction->m_bUpdateWindow || m_puserinteraction->m_bUpdateScreen) && !bStartWindowVisual);
//
//      if (bWait)
//      {



      bool bWait = false;

      //auto elapsed = m_timeNow - m_timeLastFrame;

//      if (m_bAutoRefresh)
//      {
//
//         bWait = elapsed < m_timePostRedrawProdevian.half();
//
//      }
//      else
//      {
//
//         bWait = elapsed < m_timePostRedrawNominal.half();
//
//      }
//
//      //}
//
//      if (bWait)
//      {

         // Either:
         // - It has graphics_thread mode (FPS drawing);
         // - Or it is going to wait because a frame was already drawn an instant ago due on-request-drawing (cool down).

         auto timeFrame = m_puserinteraction->has_fps_output_purpose()
            ? m_timePostRedrawProdevian : m_timePostRedrawNominal ;


         if (
            m_puserinteraction->m_pacmewindowingwindow
            && m_puserinteraction->has_fps_output_purpose())
         {

            auto elapsed = m_puserinteraction->window()->m_timeLastDrawGuard1.elapsed();

            if (elapsed > timeFrame
               && (
                  m_puserinteraction->const_layout().sketch().is_screen_visible()
                  || m_puserinteraction->const_layout().window().is_screen_visible()))
            {

               return true;

            }

         }
         //long long i2 = get_nanos();

         // calculates the next/aaa_memory_new frame atom
         //m_iFrameId = (m_timeNow + timeFrame - 1) / (timeFrame);

         //m_timeNextFrame = m_iFrameId * timeFrame;

         //class ::time timeNow;

         //timeNow.Now();

         auto timeNow = m_timeStart.elapsed();

         long long iFrame = (long long) floor(timeNow / timeFrame);

         m_timeThisFrame = timeFrame * iFrame;

         m_timeNextFrame = m_timeThisFrame + timeFrame;

         //m_cLost = (::collection::count) (m_iFrameId - m_iLastFrameId - 1);

         //m_iLastFrameId = m_iFrameId;

         //m_timeNextScreenUpdate = m_timeNextFrame;

         auto nanosElapsedInThisFrame = timeNow - m_timeThisFrame;

      //information() << "frame : " <<iFrame;
      //information() << "time frame : " <<timeFrame.floating_millisecond() << "ms";
      //information() << "elapsed in this frame : " <<nanosElapsedInThisFrame.floating_millisecond() << "ms";

      m_timeNextScreenUpdate = m_timeThisFrame + timeFrame * ceil(nanosElapsedInThisFrame/ timeFrame);

      if (nanosElapsedInThisFrame > timeFrame)
         {

            // todo display average from last 10 or so frame drawing time and not for every each single offending sample
            // informationf("("+as_string(nanosElapsedSinceLastFrame/1'000'000)+"ms)Frames are taking long to draw. Wait a bit more to free CPU. Is there much load?!?!\n");



            //information() << "next_frame time extended. frames taking long to draw";

            //m_iLastFrameId++;

         }

         {

            //auto timeStartWait = ::time::now();

            auto timeToWaitForNextFrame = m_timeNextScreenUpdate - timeNow;

            //information() << "timeToWaitForNextFrame:" <<timeToWaitForNextFrame.floating_millisecond()<<"ms";

            if (timeToWaitForNextFrame > 1_s)
            {

               //informationf("what?!?!\n");

               timeToWaitForNextFrame = 500_ms;

            }

            if (timeToWaitForNextFrame >= 1_ms)
            {

               //auto timeStart = ::time::now();

               //printf("msToWaitForNextFrame >= 2\n");

               if (timeToWaitForNextFrame < timeFrame)
               {

//                  if (timeToWaitForNextFrame >= 50_ms)
//                  {
//
//                     //printf("msToWaitForNextFrame >= 50ms (%dms)\n", (int) (msToWaitForNextFrame - 1));
//
//                     m_synchronizationa.wait(timeToWaitForNextFrame - 1_ms);
//
//                     //printf("Actually waited %dms\n", (int) ::time.elapsed().m_i);
//
//                  }
//                  else
                  {

                     //printf("msToWaitForNextFrame < 50\n");

//                     if(timeToWaitForNextFrame > 300_ms)
//                     {
//
//                        m_happeningUpdateScreen._wait(timeToWaitForNextFrame);
//
//                     }
//                     else
                     
                     
                     
                     

                     while(true)
                     {

                        if (task_wait(timeToWaitForNextFrame))
                        {

                           task_iteration();
                         
                           break;

                        }

                        if (m_iRedrawMessageCount > 0)
                        {

                           break;

                        }

                        if (m_puserinteraction->has_fps_output_purpose())
                        {

                           break;

                        }

                        if (!::task_get_run())
                        {

                           return false;

                        }

                        timeToWaitForNextFrame = 1_s;
                        
                        update_new_main_loop_happening();

                     }

                  }

               }

               //auto elapsed = time.elapsed();

               //printf("msToWaitForNextFrame Waited %d\n", elapsed.m_i);

            }

//            auto timeEndWait = ::time::now();
//
//            if (timeEndWait - timeStartWait > 100_ms)
//            {
//
//               informationf("Waited more than 100ms to go display drawn frame at screen?!?!\n");
//
//            }

            //{

            //   long long nanosDeltaPostRedraw = (long long)m_timeNextScreenUpdate - (timeFrame - m_timePostRedraw)  - (long long)get_nanos();

            //   int msDeltaPostRedraw = (int)(nanosDeltaPostRedraw / 1'000'000);

            //   if (msDeltaPostRedraw >= 1)
            //   {

            //      sleep(msDeltaPostRedraw);

            //   }


            //}

            m_phappeningUpdateScreen->reset_happening();

         }

//      }

      if (!this->task_get_run())
      {

         return false;

      }

      return true;

   }


   bool graphics_thread::graphics_thread_iteration()
   {

      //information() << "graphics_thread_iteration (A0)";

      if (!m_puserinteraction ||
         m_puserinteraction->has_finishing_flag()
         || m_puserinteraction->has_destroying_flag()
         || !m_puserinteraction->m_pacmewindowingwindow
         || m_puserinteraction->m_pacmewindowingwindow->has_finishing_flag()
         || m_puserinteraction->m_pacmewindowingwindow->has_destroying_flag())
      {

         return false;

      }

      if (::type(m_puserinteraction) == "user::list_box")
      {

         information() << "user::list_box graphics_thread_iteration user::list_box";

      }
#ifdef MORE_LOG
      else
      {

         debug() << "graphics_thread_iteration";

      }
#endif

      long long i1 = ::long_long_nanosecond();

      //m_timeLastFrame = m_timeThisFrame;

      //m_timeThisFrame = m_timeNextFrame;

      if(m_timeStart == 0_ms)
      {

         m_timeStart.Now();

      }

      m_puserinteraction->m_bUpdateBuffer = false;

      m_puserinteraction->m_bUpdateScreen = false;

      m_puserinteraction->m_bUpdateWindow = false;

      //m_puserinteraction->windowing_window()->_on

      auto pwindow = m_puserinteraction->windowing_window();

      if (!pwindow)
      {

         information() << "graphics_thread_iteration !pwindow";

         return false;

      }

      auto puserinteraction = m_puserinteraction;
      
      if (!(puserinteraction->m_ewindowflag & e_window_flag_window_created))
      {

         if (::type(puserinteraction) == "user::list_box")
         {

            information() << "user::list_box graphics_thread_iteration !e_window_flag_window_created";

         }

         information() << "graphics_thread_iteration !e_window_flag_window_created";
         // please, set_need_redraw and post_redraw after window creation...
         
         //set_need_redraw();

         //post_redraw();

         return true;

      }

      //information() << "graphics_thread_iteration (A1)";

      if (m_puserinteraction->has_graphical_output_purpose())
      {

         if (::type(m_puserinteraction.m_p) == "user::list_box")
         {

            information() << "user::list_box graphics_thread_iteration has_graphical_output_purpose";

         }

#ifdef MORE_LOG

         debug() << "graphics_thread_iteration has_graphical_output_purpose";

#endif

         if (!m_puserinteraction->has_fps_output_purpose())
         {

            if(!wait_to_present())
            {

               return false;

            }

            if (m_iRedrawMessageCount <= 0)
            {

               return true;

            }

         }

         m_iRedrawMessageCount = 0;

         //information() << "graphics_thread_iteration (A2)";

         //information() << "graphics_thread_iteration has_graphical_output_purpose";

         if(m_puserinteraction->has_flag(e_flag_destroying)
            || m_puserinteraction->has_finishing_flag()
            || pwindow->has_flag(e_flag_destroying)
            || pwindow->has_finishing_flag())
         {

            information() << "graphics_thread_iteration exit(A3)";

            return false;

         }

         //information() << "graphics_thread_iteration (A4)";
            
         if ((
            m_puserinteraction->const_layout().sketch().is_screen_visible()
            || m_puserinteraction->const_layout().window().is_screen_visible())
            || pwindow->has_offscreen_output_purpose())
         {

            pwindow->do_graphics();

            //m_puserinteraction->windowing_window()->do_graphics(e_graphics_draw);

            m_puserinteraction->on_after_graphical_update();

         }

         m_puserinteraction->m_bNeedRedraw = false;

         //graphics_thread_do_layout();

         //graphics_thread_update_buffer();

         //m_puserinteraction->m_bLockSketchToDesign = true;df

      }
      else
      {

#ifdef MORE_LOG

         information() << "graphics_thread_iteration !(Not)has_graphical_output_purpose";

#endif

      }

      if (has_finishing_flag())
      {

         return false;

      }

      if (m_puserinteraction->has_fps_output_purpose())
      {

         if(!wait_to_present())
         {

            return false;

         }

         if (has_finishing_flag())
         {

            return false;

         }

      }

      if(::is_set(puserinteraction))
      {

         if (puserinteraction->has_screen_output_purpose())
         {

            auto pwindow = puserinteraction->windowing_window();

            if (::is_set(pwindow))
            {


#ifdef MORE_LOG
                  
                  debug() << "graphics_thread_iteration has_screen_output_purpose before window_update_screen";

#endif

                  //information() << "pwindow->window_update_screen();";

                  pwindow->window_update_screen();

            }

         }

      }

      //m_puserinteraction->m_bLockSketchToDesign = false;

      return true;

   }


   void graphics_thread::on_graphics_thread_iteration_end()
   {

      {

         _synchronous_lock sl(synchronization());

         auto timeNow = ::time::now();

         for (::collection::index i = 0; i < m_timeaFrame.get_size();)
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

      m_puserinteraction->windowing_window()->m_frequencyOutputFramesPerSecond = (double)(m_timeaFrame.get_size());

   }


   //bool graphics_thread::graphics_thread_do_layout()
   //{

   //   //m_bRedraw = bRedraw;

   //   m_puserinteraction->m_bUpdateBuffer = false;

   //   m_puserinteraction->m_bUpdateScreen = false;

   //   m_puserinteraction->m_bUpdateWindow = false;

   //   //update_buffer(m_bUpdateBuffer, m_bUpdateScreen, m_bUpdateWindow, bRedraw);

   //   update_buffer();

   //   //m_bUpdateBufferUpdateWindowPending = m_bUpdateWindow;

   //   return true;

   //}



   //bool graphics_thread::graphics_thread_update_buffer()
   //{

   //   //m_bRedraw = bRedraw;

   //   //m_puserinteraction->m_bUpdateBuffer = false;

   //   //m_puserinteraction->m_bUpdateScreen = false;

   //   //m_puserinteraction->m_bUpdateWindow = false;

   //   //update_buffer(m_bUpdateBuffer, m_bUpdateScreen, m_bUpdateWindow, bRedraw);

   //   update_buffer();

   //   //m_bUpdateBufferUpdateWindowPending = m_bUpdateWindow;

   //   return true;

   //}


   bool graphics_thread::graphics_thread_update_screen()
   {

      information() << "graphics_thread_update_screen";

//      if (m_bExclusiveMode)
//      {
//
//         // UNIVERSAL_WINDOWS
//
//         exclusive_mode_update_screen();
//
//         return true;
//
//      }

      m_timeLastScreenUpdate.Now();

      m_bUpdatingScreen = true;

      profiling_on_before_update_screen();

      m_puserinteraction->windowing_window()->__update_graphics_buffer();

      profiling_on_after_update_screen();

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

      return true;

   }


   void graphics_thread::graphics_thread_redraw()
   {

      information() << "graphics_thread_redraw(1)";

      if (m_puserinteraction->m_ewindowflag & e_window_flag_embedded_graphics_thread_if_child)
      {

         information() << "graphics_thread_redraw(A)";

         m_message.m_wparam |= 1;

         graphics_thread_iteration();

      }
      else
      {

         information() << "graphics_thread_redraw(B)";

         bool bUpdateBuffer = 1;

         post_message(e_message_redraw, bUpdateBuffer ? 1 : 0);

      }

   }



//   //void graphics_thread::update_buffer(bool & bUpdateBuffer, bool & bUpdateScreen, bool & bUpdateWindow, bool bForce)
//   void graphics_thread::do_layout()
//   {
//
//      try
//      {
//
//         //         _synchronous_lock synchronouslock(m_puserinteraction->synchronization());
//         //
//         //         if(!m_puserinteraction)
//         //         {
//         //
//         //            return;
//         //
//         //         }
//         //
//         //         //bUpdateBuffer = false;
//         //
//         //         //bUpdateWindow = false;
//         //
//         //         long long i1 = ::long_long_nanosecond();
//         //
//         //      //   bool bTransparentDraw;
//         //
//         //      //#ifdef WINDOWS_DESKTOP
//         //
//         //      //   if (m_puserinteraction->GetExStyle() & WS_EX_LAYERED)
//         //      //   {
//         //
//         //      //      bTransparentDraw = true;
//         //
//         //      //   }
//         //      //   else
//         //      //   {
//         //
//         //      //      bTransparentDraw = false;
//         //
//         //      //   }
//         //
//         //      //#else
//         //
//         //      //   bTransparentDraw = true;
//         //
//         //      //#endif
//         //
//         //         if (!::task_get_run())
//         //         {
//         //
//         //            return;
//         //
//         //         }
//         //
//         //         if (m_puserinteraction == nullptr)
//         //         {
//         //
//         //            return;
//         //
//         //         }
//         //
//         //
//         //         if (!m_puserinteraction->windowing_window())
//         //         {
//         //
//         //            return;
//         //
//         //         }
//         //
//         //         synchronouslock.unlock();
//
//         m_timeBeforeDrawing.Now();
//
//         m_timeOutOfDrawing = m_timeBeforeDrawing - m_timeAfterDrawing;
//
//         long long i2 = ::long_long_nanosecond();
//
//#if TIME_REPORTING
//
//         static ::time timeLast;
//
//         informationf("time outside updatebuffer " + as_string(timeLast.elapsed().floating_millisecond().m_d) + "ms\n");
//
//#endif
//
//         m_puserinteraction->windowing_window()->do_graphics();
//
//#if TIME_REPORTING
//
//         timeLast.Now();
//
//         g_timeBetweenUpdateBufferAndUpdateScreen.Now();
//
//#endif
//
//         m_timeAfterDrawing.Now();
//
//         m_timeDuringDrawing = m_timeAfterDrawing - m_timeBeforeDrawing;
//
//         if (m_puserinteraction)
//         {
//
//            m_puserinteraction->on_after_graphical_update();
//
//            m_puserinteraction->m_bNeedRedraw = false;
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//   }
//
//   //void graphics_thread::update_buffer(bool & bUpdateBuffer, bool & bUpdateScreen, bool & bUpdateWindow, bool bForce)
//   void graphics_thread::update_buffer()
//   {
//
//      try
//      {
//
////         _synchronous_lock synchronouslock(m_puserinteraction->synchronization());
////
////         if(!m_puserinteraction)
////         {
////
////            return;
////
////         }
////
////         //bUpdateBuffer = false;
////
////         //bUpdateWindow = false;
////
////         long long i1 = ::long_long_nanosecond();
////
////      //   bool bTransparentDraw;
////
////      //#ifdef WINDOWS_DESKTOP
////
////      //   if (m_puserinteraction->GetExStyle() & WS_EX_LAYERED)
////      //   {
////
////      //      bTransparentDraw = true;
////
////      //   }
////      //   else
////      //   {
////
////      //      bTransparentDraw = false;
////
////      //   }
////
////      //#else
////
////      //   bTransparentDraw = true;
////
////      //#endif
////
////         if (!::task_get_run())
////         {
////
////            return;
////
////         }
////
////         if (m_puserinteraction == nullptr)
////         {
////
////            return;
////
////         }
////
////
////         if (!m_puserinteraction->windowing_window())
////         {
////
////            return;
////
////         }
////
////         synchronouslock.unlock();
//
//         m_timeBeforeDrawing.Now();
//
//         m_timeOutOfDrawing = m_timeBeforeDrawing - m_timeAfterDrawing;
//
//         long long i2 = ::long_long_nanosecond();
//
//#if TIME_REPORTING
//
//         static ::time timeLast;
//
//         informationf("time outside updatebuffer " +as_string(timeLast.elapsed().floating_millisecond().m_d) + "ms\n");
//
//#endif
//
//         m_puserinteraction->windowing_window()->do_graphics();
//
//#if TIME_REPORTING
//
//         timeLast.Now();
//
//         g_timeBetweenUpdateBufferAndUpdateScreen.Now();
//
//#endif
//
//         m_timeAfterDrawing.Now();
//
//         m_timeDuringDrawing = m_timeAfterDrawing - m_timeBeforeDrawing;
//
//         if (m_puserinteraction)
//         {
//
//            m_puserinteraction->on_after_graphical_update();
//
//            m_puserinteraction->m_bNeedRedraw = false;
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//   }


   void graphics_thread::post_redraw()
   {

      if (m_bFps)
      {

         //warning() << "graphics thread is going to ignore post redraw as it should be doing Fps drawing";

         return;

      }

      //information() << node()->get_callstack();

      //information() << "graphics_thread::post_redraw";

      try
      {

         post_message(e_message_redraw);

      }
      catch (...)
      {


      }

   }


//   bool graphics_thread::exclusive_mode_update_screen()
//   {
//
//      //if (m_puserinteraction->windowing_window())
//      //{
//
//      //   if (m_puserinteraction->windowing_window()->m_pgraphics)
//      //   {
//
//      //      auto pbitmapsource = m_puserinteraction->windowing_window()->m_pgraphics.cast < ::graphics::bitmap_source_buffer >();
//
//      //      if (pbitmapsource)
//      //      {
//
//      //         string strBitmapSource = m_puserinteraction->payload("bitmap-source");
//
//      //         if (pbitmapsource->m_strBitmapSource != strBitmapSource)
//      //         {
//
//      //            pbitmapsource->enable_ipc_copy(strBitmapSource);
//
//      //         }
//
//      //      }
//
//
//      //   }
//
//      //}
//
//
//      try
//      {
//
//         string strType = ::type(m_puserinteraction).name();
//
//         if(strType.case_insensitive_contains("list_box"))
//         {
//
//            informationf("We're on the list_box update_screen");
//
//         }
//
//         profiling_on_before_update_screen();
//
//         if (!m_puserinteraction->windowing_window())
//         {
//
//            return false;
//
//         }
//
//         m_puserinteraction->windowing_window()->graphics_thread_update_screen();
//
//         if (!m_puserinteraction)
//         {
//
//            return false;
//
//         }
//
////         if (is_different(m_puserinteraction->m_ewindowflag & e_window_flag_on_show_window_visible,
////            m_puserinteraction->is_this_visible())
////            || is_different(m_puserinteraction->m_ewindowflag & e_window_flag_on_show_window_screen_visible,
////               m_puserinteraction->is_window_screen_visible()))
////         {
////
////            m_puserinteraction->m_ewindowflag.set(e_window_flag_on_show_window_visible, m_puserinteraction->is_this_visible());
////
////            m_puserinteraction->m_ewindowflag.set(e_window_flag_on_show_window_screen_visible, m_puserinteraction->is_window_screen_visible());
////
////            m_puserinteraction->_on_show_window();
////
////         }
//
//         profiling_on_after_update_screen();
//
//      }
//      catch(...)
//      {
//
//         return false;
//
//      }
//
//      return true;
//
//   }


   void graphics_thread::profiling_on_before_update_screen()
   {
    
      m_timeBeforeUpdateScreen.Now();

      m_timeOufOfUpdateScreen = m_timeBeforeUpdateScreen - m_timeAfterUpdateScreen;

   }


   void graphics_thread::profiling_on_after_update_screen()
   {

      _synchronous_lock sl(synchronization());
      
      //m_timeLastFrame.Now();

      //m_timeLastFrame = m_timeNow;

      m_timeaFrame.add(m_timeLastFrame);

      m_timeAfterUpdateScreen.Now();

      m_timeDuringUpdateScreen = m_timeAfterUpdateScreen - m_timeBeforeUpdateScreen;

      if (m_timeDuringUpdateScreen > 60_ms)
      {

         //informationf("It took about " + as_string(m_timeDuringUpdateScreen) + " to update screen\n");

         //informationf("It took about " + as_string(m_timeOufOfUpdateScreen) + " out of screen update\n");

      }

      m_timeDuringUpdateScreen = m_timeAfterUpdateScreen - m_timeBeforeUpdateScreen;

      if (m_timeOufOfUpdateScreen > 60_ms)
      {

         //informationf("It took about " + as_string(m_timeDuringUpdateScreen) + " to update screen\n");

         //informationf("It took about " + as_string(m_timeOufOfUpdateScreen) + " out of screen update\n");

      }
      
   }

   
   void graphics_thread::defer_graphics_thread_step()
   {

      if (m_timeLastFrame.elapsed() > (m_timePostRedrawNominal * 3 / 4))
      {

         post_message(e_message_redraw);

      }

   }


   void graphics_thread::set_fps_interest_frames_per_second(::frequency frequencyProdevianFramesPerSecond)
   {

      m_timePostRedrawProdevian = 1.0 / frequencyProdevianFramesPerSecond;

   }


   void graphics_thread::set_nominal_frames_per_second(::frequency frequencyNominalFramesPerSecond)
   {

      m_timePostRedrawNominal = 1.0 / frequencyNominalFramesPerSecond;

   }


   void graphics_thread::set_per_second(::frequency frequencyFramesPerSecond)
   {

      set_fps_interest_frames_per_second(frequencyFramesPerSecond);

      set_nominal_frames_per_second(frequencyFramesPerSecond);

   }


//   void interaction::graphics_thread_post_procedure(const ::procedure & procedure)
//   {
//
//      if (!is_graphical())
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      windowing_window()->m_pgraphicsthread->post_procedure(procedure);
//
//   }


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
//   AttachThreadInput(::GetCurrentThreadId(), (DWORD)main_user_itask(), bAttach ? true : false);
//
//}
//


