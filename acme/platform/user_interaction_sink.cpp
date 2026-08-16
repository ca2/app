//
// Created by camilo on 2026-04-07 06:22 <3ThomasBorregaardSørensen!!
//
#include "platform.h"
#include "user_interaction_sink.h"
#include "application.h"
#include "system.h"
#include "acme/user/user/interaction.h"

#define return_if_setø(a) if(a.is_set()) return a

user_interaction_sink::user_interaction_sink()
{

   initialize(::system()->m_papplication);

}


user_interaction_sink::user_interaction_sink(const ::operating_system::window & operatingsystemwindow):
m_operatingsystemwindow(operatingsystemwindow)
{

   initialize(::system()->m_papplication);

}

 ::operating_system::window user_interaction_sink::best_effort_operating_system_window() const
{


   ::operating_system::window operatingsystemwindow;

   operatingsystemwindow = m_operatingsystemwindow;

   return_if_setø(operatingsystemwindow);

   auto papplication = m_papplication;

   if(papplication)
   {
      
      auto pacmeuserinteractionMain = papplication->main_acme_user_interaction();

      if (pacmeuserinteractionMain)
      {

         operatingsystemwindow = pacmeuserinteractionMain->operating_system_window();

      }

   }

   return_if_setø(operatingsystemwindow);

   return nullptr;

}
