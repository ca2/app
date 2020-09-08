#include "framework.h"
#include "apex/node/uwp/directx.h"
#include "apex/node/uwp/directx_interaction.h"
#include "apex/node/uwp/directx_impact.h"
#include "apex/node/uwp/directx_application.h"


CLASS_DECL_APEX ::estatus os_application_system_run(::apex::system * psystem)
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



