#pragma once


#include "frame_interaction.h"


namespace user
{


   class CLASS_DECL_AURA main_window :
      virtual public ::user::frame_interaction
   {
   public:


      ::double_rectangle                                   m_rectangleInitialRateOrSize;


      main_window();
      ~main_window() override;


      void install_message_routing(::channel* pchannel) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);


      //void on_create_user_interaction() override;
      
      
      void input_client_rectangle(::int_rectangle & rectangle, enum_layout elayout = e_layout_sketch) override;


      void initial_frame_placement() override;


      ::collection::index get_preferred_restore(::int_rectangle & rectanglePreferredRestore) override;


      //virtual void create_main_window_asynchronously();

      virtual void create_main_window(::request * prequest);


      bool should_redraw_on_mouse_activate() override;


      bool should_redraw_on_mouse_hover() override;

      bool is_child_interaction() override;


   };



} // namespace user



