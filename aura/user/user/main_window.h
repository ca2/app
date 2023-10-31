#pragma once


#include "frame.h"


namespace user
{


   class CLASS_DECL_AURA main_window :
      virtual public ::user::frame
   {
   public:


      ::rectangle_f64                                   m_rectangleInitialRateOrSize;


      main_window();
      ~main_window() override;


      void install_message_routing(::channel* pchannel) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);


      //void on_create_user_interaction() override;
      
      
      void input_client_rectangle(::rectangle_i32 & rectangle, enum_layout elayout = e_layout_sketch) override;


      void initial_frame_placement() override;


      ::index get_preferred_restore(::rectangle_i32 & rectanglePreferredRestore) override;


      virtual void create_main_window_asynchronously();


      bool should_redraw_on_mouse_activate() override;


      bool should_redraw_on_mouse_hover() override;



   };



} // namespace user



