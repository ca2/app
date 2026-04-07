//
// Created by camilo on 2026-04-07 05:56 <3ThomasBorregaardSørensen!!
//
#pragma once

#include "acme/operating_system/window.h"

namespace a
{
   class CLASS_DECL_ACME user_interaction :
      virtual public ::particle
   {
   public:

      user_interaction

      ::operating_system::window m_operatingsystemwindow;

      virtual ::operating_system::window operating_system_window()
      {

         return m_operatingsystemwindow;

      }

   };
} // namespace a