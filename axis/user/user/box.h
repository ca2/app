#pragma once




namespace user
{



   class CLASS_DECL_AURA box :
      virtual public scroll
   {
   public:


      string               m_strDisplay;
      ::database::key      m_databasekey;

      box();
      virtual ~box();

      
      virtual ::estatus initialize(::object * pobjectContext) override;


      void install_message_routing(::channel * pchannel) override;

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnShowWindow);

      virtual void prodevian_prepare_window_restore(edisplay edisplay) override;

      virtual string calc_display();
      virtual bool does_display_match();
      virtual void defer_update_display();

      virtual bool should_save_window_rect() override;
      virtual bool WindowDataSaveWindowRect() override;
      virtual bool WindowDataLoadWindowRect(bool bForceRestore = false, bool bInitialFramePosition = false) override;

      virtual string window_data_key_modifier();

      virtual bool LoadWindowRect_(const ::database::key & key, bool bForceRestore = false, bool bInitialFramePosition = false);
      virtual bool SaveWindowRect_(const ::database::key & key);


      virtual void on_simple_command(::message::simple_command * psimplecommand) override;
      virtual void on_command(::user::command * pcommand) override;


      virtual bool on_set_parent(::user::interaction * puiParent) override;
      virtual bool on_before_set_parent(::user::interaction * pinterface) override;


      virtual bool parent_is_local_data();
      //virtual bool is_local_data() override;


   };


} // namespace user





