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


      virtual void install_message_routing(::channel* pchannel) override;


      virtual void on_create_user_interaction() override;


      virtual ::e_status create_main_window();

   };



} // namespace user



