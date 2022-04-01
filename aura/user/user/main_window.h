#pragma once


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


      void on_create_user_interaction() override;


      ::index get_preferred_restore(RECTANGLE_I32 * prectanglePreferredRestore) override;


      virtual void create_main_window();

   };



} // namespace user



