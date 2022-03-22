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


      virtual void create_main_window();

   };



} // namespace user



