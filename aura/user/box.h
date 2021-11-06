#pragma once


namespace user
{


   class CLASS_DECL_AURA box :
      virtual public interaction
   {
   public:


      string                        m_strDisplay;
      ::database::key               m_databasekey;
      struct window_rectangle       m_windowrectangle;
      struct window_rectangle       m_windowrectangleStore;



      box();
      virtual ~box();

      
      virtual ::e_status initialize(::object * pobject) override;


      void install_message_routing(::channel * pchannel) override;

      
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);


      virtual::e_display window_stored_display() const override;
      virtual::e_display window_previous_display() const override;


      virtual void on_visual_applied() override;

      virtual void window_show_change_visibility() override;


      virtual void sketch_prepare_window_restore(edisplay edisplay) override;


      virtual string get_display_tag() override;

      
      virtual string calc_display();
      virtual bool does_display_match();
      virtual void defer_update_display() override;


      virtual bool should_save_window_rect() override;
      virtual bool WindowDataSaveWindowRect() override;
      virtual bool WindowDataLoadWindowRect(bool bForceRestore = false, bool bInitialFramePosition = false) override;

      virtual string window_data_key_modifier();

      virtual bool LoadWindowRect_(const ::database::key & key, bool bForceRestore = false, bool bInitialFramePosition = false);
      virtual bool SaveWindowRect_(const ::database::key & key);


      virtual void on_simple_command(::message::simple_command * psimplecommand) override;
      virtual void on_command(::message::command * pcommand) override;


      virtual bool on_set_parent(::user::primitive * puiParent) override;
      virtual bool on_before_set_parent(::user::primitive * pinterface) override;


      virtual bool parent_is_local_data();


   };


} // namespace user



