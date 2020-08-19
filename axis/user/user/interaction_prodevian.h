#pragma once


namespace user
{


   class CLASS_DECL_AURA prodevian :
      virtual public ::thread
   {
   public:


      bool                          m_bExclusiveMode;

      sync_array                   m_synca;

      manual_reset_event            m_evUpdateScreen;


      __pointer(::user::interaction)       m_puserinteraction;
      __pointer(::user::interaction_impl)  m_pimpl;

      __composite(::user::thread)   m_puserthread;
      nano_timer                    m_nanotimer;

      i64                           m_nanosNow;

      i64                           m_nanosFrame;
      i64                           m_nanosPostRedraw;

      i64                           m_iFrameId;
      i64                           m_nanosLastFrame;
      i64                           m_iLastFrameId;
      i64                           m_nanosNextFrame;
      i64                           m_nanosNextScreenUpdate;
      ::count                       m_cLost;
      u64_array                     m_iaFrame;
      bool                          m_bVisualUpdated;

      tick                          m_tickBeforeUpdateScreen;
      tick                          m_tickAfterUpdateScreen;
      tick                          m_tickDuringUpdateScreen;
      tick                          m_tickOufOfUpdateScreen;


      tick                          m_tickBeforeDrawing;
      tick                          m_tickAfterDrawing;
      tick                          m_tickDuringDrawing;
      tick                          m_tickOutOfDrawing;

      bool                          m_bUpdatingScreen;
      tick                          m_tickLastScreenUpdate;
      __pointer(generic_object)     m_ptaskX;


      prodevian();
      virtual ~prodevian();

      virtual ::estatus     initialize_prodevian(interaction_impl * pimpl);

      //virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override
      //{

      //   return ::thread::add_ref(OBJ_REF_DBG_ARGS);

      //}

      //virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override
      //{

      //   return ::thread::dec_ref(OBJ_REF_DBG_ARGS);

      //}


      bool prodevian_reset(::user::interaction * pinteraction);
      bool prodevian_iteration();
      void prodevian_update_buffer(bool & bUpdateBuffer, bool & bUpdateScreen, bool bForce = false);
      bool prodevian_update_screen();

      void defer_prodevian_step();

      void set_config_fps(double dConfig);

      //virtual bool pump_message() override;

      virtual void term_thread() override;

      virtual ::estatus     run() override;

      virtual void finalize() override
      {

         if (m_bRunThisThread)
         {

            m_evUpdateScreen.SetEvent();

         }

         ::thread::finalize();

      }


   };



} // namespace user




