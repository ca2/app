// Created by camilo on 2023-10-09 ~12:00 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/user/user/interaction.h"


namespace user
{


   class CLASS_DECL_CORE popup :
      virtual public ::user::interaction
   {
   public:


      ::int_size     m_sizeMinimum;
      bool           m_bHideOnLostFocus;
      class ::time   m_timeLostFocus;


      popup();
      ~popup() override;


      void install_message_routing(::channel * pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_kill_focus);


      virtual void show_popup(const ::int_point & point);
      virtual void hide_popup();


   };


} // namespace user


