//
// Created by camilo on 2026-04-07 05:56 <3ThomasBorregaardSørensen!!
//
#pragma once

#include "application.h"
#include "acme/operating_system/window.h"
#include "acme/user/user/interaction.h"


class CLASS_DECL_ACME user_interaction_sink :
   virtual public ::particle
{
public:



   ::operating_system::window m_operatingsystemwindow;


   user_interaction_sink(const ::operating_system::window & operatingsystemwindow);

   virtual ::operating_system::window best_effort_operating_system_window();

};
