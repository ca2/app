#pragma once


#include "app/aura/user/user/interaction.h"
#include "apex/database/key.h"


namespace user
{


   class CLASS_DECL_AURA box :
      virtual public interaction
   {
   public:


      string                        m_strDisplay;
      //::string                      m_strDataKey2;
      struct window_rectangle       m_windowrectangle;
      struct window_rectangle       m_windowrectangleStore;


      box();
      ~box() override;


      
      virtual void initialize(::particle * pparticle) override;


      void install_message_routing(::channel * pchannel) override;

      
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);





      
      //void display_normal() override;
      //void display_stored_state() override;
      
      
      void design_window_iconic() override;
      

      ::e_display window_stored_display() override;
      ::e_display window_previous_display() override;

      
      void set_window_previous_display(::e_display edisplayPrevious) override;


      void on_visual_applied() override;

      void window_show_change_visibility() override;


      void design_window_normal(::e_display edisplay) override;


      string get_display_tag() override;

      
      virtual string calculate_display();
      virtual bool does_display_match();
      void defer_update_display() override;


      bool should_save_window_rectangle() override;
      
      bool FancyWindowDataLoadWindowRectangle(bool bForceRestore = false, bool bInitialFramePosition = false) override;
      bool WindowDataLoadWindowRectangle() override;
      void WindowDataSaveWindowRectangle() override;

      virtual string window_data_key_modifier();

      virtual bool FancyLoadWindowRectangle(const ::scoped_string & strDataKey, bool bForceRestore = false, bool bInitialFramePosition = false);
      virtual bool LoadWindowRectangle(const ::scoped_string & strDataKey);
      virtual void SaveWindowRectangle(const ::scoped_string & strDataKey);


      ::size_i32 get_window_normal_stored_size() override;

      void display_normal(::e_display edisplay, ::e_activation eactivation) override;
      void display_full_screen(::index iMonitor, ::e_activation eactivation) override;

      void on_simple_command(::message::simple_command * psimplecommand) override;
      void on_command(::message::command * pcommand) override;


      virtual bool on_set_parent(::user::primitive * puiParent) override;
      virtual bool on_before_set_parent(::user::primitive * pinterface) override;


      //virtual bool parent_is_local_data();


      //void set_restored_rectangle(const ::rectangle_i32 & rectangleRestored) override;


   };


} // namespace user



