#include "framework.h"
#include "aura/node/uwp/directx.h"
#include "aura/node/uwp/directx_interaction.h"
#include "aura/node/uwp/directx_impact.h"
#include "aura/node/uwp/directx_framework_view.h"


CLASS_DECL_CORE ::estatus os_application_system_run(::aura::system * psystem)
{

   //auto estatus = psystem->begin_synch();

   //if (!estatus)
   //{

   //   return estatus;

   //}

   auto source = ::uwp::new_directx_application_source(get_context_system(), psystem->m_strCommandLine);

   ::Windows::ApplicationModel::Core::CoreApplication::Run(source);

   return ::success;

}



