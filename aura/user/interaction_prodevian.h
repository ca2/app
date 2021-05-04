#pragma once


namespace user
{


   class CLASS_DECL_AURA prodevian :
      virtual public ::thread
   {
   public:


      synchronization_array                                m_synchronizationa;

      manual_reset_event                        m_evUpdateScreen;

      __pointer(::user::interaction)            m_puserinteraction;
      __pointer(::user::interaction_impl)       m_pimpl;

      __composite(::user::thread)               m_puserthread;
      nano_timer                                m_nanotimer;

      i64                                       m_nanosNow;

      i64                                       m_nanosPostRedrawProdevian;
      i64                                       m_nanosPostRedrawNominal;

      //i64                                       m_iFrameId;
      i64                                       m_nanosLastFrame;
      //i64                                       m_iLastFrameId;
      i64                                       m_nanosNextFrame;
      i64                                       m_nanosNextScreenUpdate;
      //::count                                   m_cLost;
      u64_array                                 m_iaFrame;

      millis                                    m_millisBeforeUpdateScreen;
      millis                                    m_millisAfterUpdateScreen;
      millis                                    m_millisDuringUpdateScreen;
      millis                                    m_millisOufOfUpdateScreen;


      millis                                    m_millisBeforeDrawing;
      millis                                    m_millisAfterDrawing;
      millis                                    m_millisDuringDrawing;
      millis                                    m_millisOutOfDrawing;

      millis                                    m_millisLastScreenUpdate;
      ::routine                        m_routineUpdateScreen;
      ::routine                        m_routineWindowShow;
      


      bool                                      m_bRedraw;
      bool                                      m_bUpdateBuffer; // internal offscreen buffer
      bool                                      m_bUpdateScreen; // screen buffer
      bool                                      m_bUpdateWindow; // window frame


      bool                                      m_bExclusiveMode;
      bool                                      m_bVisualUpdated;

      bool                                      m_bUpdatingScreen;


      bool                                      m_bUpdateBufferUpdateWindowPending;



      prodevian();
      virtual ~prodevian();


#ifdef DEBUG
      virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override;
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override;
      virtual i64 release(OBJ_REF_DBG_PARAMS) override;
#endif


      virtual ::e_status initialize_prodevian(interaction_impl * pimpl);


      bool prodevian_reset(::user::interaction * pinteraction);
      bool prodevian_iteration();
      bool prodevian_update_buffer(bool bRedraw);
      bool prodevian_update_screen();
      void update_buffer(bool & bUpdateBuffer, bool & bUpdateScreen, bool & bUpdateWindow, bool bForce = false);
      bool update_screen();

      

      void defer_prodevian_step();

      // Fps for when prodevian is active or there is any active prodevian object
      void set_prodevian_fps(double dProdevianFps);

      // Fps for when prodevian is not active and there is no active prodevian object
      void set_nominal_fps(double dNominalFps);

      void set_fps(double dFps);

      //virtual bool pump_message() override;

      virtual void term_thread() override;

      virtual ::e_status finalize() override;

      virtual ::e_status run() override;

      //virtual ::e_status do_task() override;


   };



} // namespace user




