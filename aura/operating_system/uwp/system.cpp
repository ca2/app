// Created by CamiloSTTBS 2020-12-25 14:01 BRT <3ThomasBS_, Mummi and bilbo!!
#include "framework.h"
#include "aura/node/universal_windows/_uwp.h"
#include "aura/os/windows_common/draw2d_direct2d_global.h"


namespace aura
{

   
   void system::message_box(const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox, const future & process)
   {

      return message_box_synchronous(pszMessage, pszTitle, emessagebox, process);

   }

   void system::message_box_timeout(const ::string & pszMessage, const ::string & pszTitle, const ::duration & durationTimeout, const ::e_message_box & emessagebox, const future & process)
   {

      return message_box_synchronous(pszMessage, pszTitle, emessagebox, process);

   }


   void system::os_application_system_run()
   {

      //auto estatus = begin_synch();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto source = ::universal_windows::new_directx_application_source(this, m_strCommandLine);

      ::winrt::Windows::ApplicationModel::Core::CoreApplication::Run(source);

      return ::success;

   }


} // namespace aura




