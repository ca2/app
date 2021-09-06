#include "framework.h"
#include "aura/node/universal_windows/directx.h"
#include "aura/node/universal_windows/directx_interaction.h"
#include "aura/node/universal_windows/directx_impact.h"
#include "aura/node/universal_windows/directx_framework_view.h"


CLASS_DECL_CORE ::e_status os_application_system_run(::aura::system * psystem)
{

   //auto estatus = psystem->begin_synch();

   //if (!estatus)
   //{

   //   return estatus;

   //}

   auto source = ::universal_windows::new_directx_application_source(get_context_system(), psystem->m_strCommandLine);

   ::winrt::Windows::ApplicationModel::Core::CoreApplication::Run(source);

   return ::success;

}



