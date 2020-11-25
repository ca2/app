#pragma once


namespace user
{


   class CLASS_DECL_AURA prodevian :
      virtual public ::thread
   {
   public:


      bool                                      m_bExclusiveMode;

      sync_array                                m_synca;

      manual_reset_event                        m_evUpdateScreen;


      __pointer(::user::interaction)            m_puserinteraction;
      __pointer(::user::interaction_impl)       m_pimpl;

      __composite(::user::thread)               m_puserthread;
      nano_timer                                m_nanotimer;

      i64                                       m_nanosNow;

      i64                                       m_nanosFrame;
      i64                                       m_nanosPostRedraw;

      i64                                       m_iFrameId;
      i64                                       m_nanosLastFrame;
      i64                                       m_iLastFrameId;
      i64                                       m_nanosNextFrame;
      i64                                       m_nanosNextScreenUpdate;
      ::count                                   m_cLost;
      u64_array                                 m_iaFrame;
      bool                                      m_bVisualUpdated;

      millis                                    m_millisBeforeUpdateScreen;
      millis                                    m_millisAfterUpdateScreen;
      millis                                    m_millisDuringUpdateScreen;
      millis                                    m_millisOufOfUpdateScreen;


      millis                                    m_millisBeforeDrawing;
      millis                                    m_millisAfterDrawing;
      millis                                    m_millisDuringDrawing;
      millis                                    m_millisOutOfDrawing;

      bool                                      m_bUpdatingScreen;
      millis                                    m_millisLastScreenUpdate;
      ::promise::routine                        m_routineUpdateScreen;
      ::promise::routine                        m_routineWindowShow;


      prodevian();
      virtual ~prodevian();


#ifdef DEBUG
      virtual i64 add_ref(OBJ_REF_DBG_PARAMS);
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS);
      virtual i64 release(OBJ_REF_DBG_PARAMS);
#endif


      virtual ::estatus initialize_prodevian(interaction_impl * pimpl);


      bool prodevian_reset(::user::interaction * pinteraction);
      bool prodevian_iteration();
      void update_buffer(bool & bUpdateBuffer, bool & bUpdateScreen, bool bForce = false);
      bool update_screen();

      void defer_prodevian_step();

      void set_config_fps(double dConfig);

      //virtual bool pump_message() override;

      virtual void term_thread() override;

      virtual void finalize() override;

      virtual ::estatus     run() override;



   };



} // namespace user




