#pragma once


#include "acme/parallelization/manual_reset_happening.h"
#include "acme/parallelization/synchronization_array.h"
#include "acme/platform/nanosecond_timer.h"
#include "acme/prototype/time/frequency.h"
#include "apex/parallelization/thread.h"


namespace user
{


   class CLASS_DECL_AURA graphics_thread :
      virtual public ::thread
   {
   public:


      synchronization_array                     m_synchronizationa;
      manual_reset_happening m_happeningFrame;
      ::pointer < manual_reset_happening >        m_phappeningUpdateScreen;

      ::pointer<::user::interaction>                  m_puserinteraction;
      //::pointer<::windowing::window>      m_pimpl;

      //::pointer<::user::thread>                   m_puserthread;
      nanosecond_timer                            m_nanosecondtimer;

      class ::time                                m_timeStart;
      class ::time                                m_timeThisFrame;

      ///manual_reset_happening                           m_happeningReady;

      bool                                        m_bGraphicsThreadEnabled;

      class ::time                                m_timePostRedrawProdevian;
      class ::time                                m_timePostRedrawNominal;

      //long long                                       m_iFrameId;
      //class ::time                                m_timeStart;
      class ::time                                m_timeLastFrame;
      //long long                                       m_iLastFrameId;
      class ::time                                m_timeNextFrame;
      class ::time                                m_timeNextScreenUpdate;
      //::collection::count                                   m_cLost;
      ::array < class ::time >                    m_timeaFrame;

      class ::time                                m_timeBeforeUpdateScreen;
      class ::time                                m_timeAfterUpdateScreen;
      class ::time                                m_timeDuringUpdateScreen;
      class ::time                                m_timeOufOfUpdateScreen;


      class ::time                                m_timeBeforeDrawing;
      class ::time                                m_timeAfterDrawing;
      class ::time                                m_timeDuringDrawing;
      class ::time                                m_timeOutOfDrawing;

      class ::time                                m_timeLastScreenUpdate;
      //::procedure                                 m_procedureUpdateScreen;
      //::procedure                                 m_procedureWindowShow;
      

      //bool                                      m_bRedraw;


      //bool                                      m_bExclusiveMode;
      //bool                                      m_bVisualUpdated;

      bool                                      m_bUpdatingScreen;


      //bool                                      m_bUpdateBufferUpdateWindowPending;

      bool                                      m_bFps;
      int m_iRedrawMessageCount;


      graphics_thread();
      ~graphics_thread() override;


#ifdef _DEBUG
      virtual long long increment_reference_count() override;
      virtual long long decrement_reference_count() override;
      virtual long long release() override;
#endif


      void install_message_routing(::channel * pchannel) override;


      virtual void defer_create_graphics_thread();


      virtual void initialize_graphics_thread(::user::interaction * puserinteraction);


      bool graphics_thread_reset(::user::interaction * pinteraction);
      bool graphics_thread_iteration();
      void on_graphics_thread_iteration_end();
      //bool graphics_thread_do_layout();
      //bool graphics_thread_update_buffer();
      bool graphics_thread_update_screen();
      void graphics_thread_redraw();
      //void update_buffer(bool & bUpdateBuffer, bool & bUpdateScreen, bool & bUpdateWindow, bool bForce = false);
      //void do_layout();
      //void update_buffer();
      //bool exclusive_mode_update_screen();
      void post_redraw();

      /// returns false if got quit message
      virtual bool wait_for_redraw_message();
      /// returns false if got quit message
      virtual bool clear_message_queue();
      /// returns false if got quit message
      virtual bool defer_process_redraw_message();

      virtual bool wait_to_present();
      
      virtual void profiling_on_before_update_screen();
      virtual void profiling_on_after_update_screen();

      DECLARE_MESSAGE_HANDLER(on_message_redraw);
      

      void defer_graphics_thread_step();

      // Fps for when graphics_thread is active or there is any active graphics_thread object
      void set_fps_interest_frames_per_second(::frequency frequencyProdevianFramesPerSecond);

      // Fps for when graphics_thread is not active and there is no active graphics_thread object
      void set_nominal_frames_per_second(::frequency frequencyNominalFramesPerSecond);

      void set_per_second(::frequency frequencyFramesPerSecond);

      //virtual bool pump_message() override;

      virtual void term_task() override;

      virtual void destroy() override;

      virtual void run() override;

      //virtual void do_task() override;


   };



} // namespace user




