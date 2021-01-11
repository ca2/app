// Created by CamiloSTTBS 2020-12-25 14:01 BRT <3ThomasBS_, Mummi and bilbo!!
#include "framework.h"
#include "aura/node/uwp/_uwp.h"
#include "aura/os/windows_common/draw2d_direct2d_global.h"


namespace aura
{

   
   ::e_status system::message_box(const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox, const promise::process & process)
   {

      return os_message_box(pszMessage, pszTitle, emessagebox, process);

   }

   ::e_status system::message_box_timeout(const char * pszMessage, const char * pszTitle, const ::duration & durationTimeout, const ::e_message_box & emessagebox, const promise::process & process)
   {

      return os_message_box(pszMessage, pszTitle, emessagebox, process);

   }


   ::e_status system::os_application_system_run()
   {

      //auto estatus = begin_synch();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto source = ::uwp::new_directx_application_source(this, m_strCommandLine);

      ::Windows::ApplicationModel::Core::CoreApplication::Run(source);

      return ::success;

   }


} // namespace aura




