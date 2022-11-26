#pragma once


#include "acme/parallelization/manual_reset_event.h"
#include "acme/parallelization/synchronization_array.h"
#include "acme/platform/nanosecond_timer.h"
#include "apex/parallelization/thread.h"


namespace user
{


   class CLASS_DECL_AURA prodevian :
      virtual public ::thread
   {
   public:


      synchronization_array                     m_synchronizationa;

      manual_reset_event                        m_evUpdateScreen;

      ::pointer<::user::interaction>           m_puserinteraction;
      ::pointer<::user::interaction_impl>      m_pimpl;

      ::pointer<::user::thread>              m_puserthread;
      nanosecond_timer                          m_nanosecondtimer;

      class ::time                                m_timeNow;

      class ::time                                m_timePostRedrawProdevian;
      class ::time                                m_timePostRedrawNominal;

      //i64                                       m_iFrameId;
      class ::time                                m_timeLastFrame;
      //i64                                       m_iLastFrameId;
      class ::time                                m_timeNextFrame;
      class ::time                                m_timeNextScreenUpdate;
      //::count                                   m_cLost;
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
      ::procedure                                 m_procedureUpdateScreen;
      ::procedure                                 m_procedureWindowShow;
      

      bool                                      m_bRedraw;
      bool                                      m_bUpdateBuffer; // internal offscreen buffer
      bool                                      m_bUpdateScreen; // screen buffer
      bool                                      m_bUpdateWindow; // window frame


      bool                                      m_bExclusiveMode;
      bool                                      m_bVisualUpdated;

      bool                                      m_bUpdatingScreen;


      //bool                                      m_bUpdateBufferUpdateWindowPending;



      prodevian();
      ~prodevian() override;


#ifdef _DEBUG
      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif


      virtual void defer_create_prodevian();



      virtual void initialize_prodevian(interaction_impl * pimpl);


      bool prodevian_reset(::user::interaction * pinteraction);
      bool prodevian_iteration();
      bool prodevian_update_buffer(bool bRedraw);
      bool prodevian_update_screen();
      void update_buffer(bool & bUpdateBuffer, bool & bUpdateScreen, bool & bUpdateWindow, bool bForce = false);
      bool update_screen();

      
      virtual void profiling_on_before_update_screen();
      virtual void profiling_on_after_update_screen();
      

      void defer_prodevian_step();

      // Fps for when prodevian is active or there is any active prodevian object
      void set_prodevian_fps(double dProdevianFps);

      // Fps for when prodevian is not active and there is no active prodevian object
      void set_nominal_fps(double dNominalFps);

      void set_fps(double dFps);

      //virtual bool pump_message() override;

      virtual void term_task() override;

      virtual void destroy() override;

      virtual void run() override;

      //virtual void do_task() override;


   };



} // namespace user




