#include "framework.h"
#include "aura/node/uwp/_uwp.h"


CLASS_DECL_AURA ::estatus os_application_system_run(::apex::system * psystem)
{

   auto source = ::uwp::new_directx_application_source(System.m_paurasystem, psystem->m_strCommandLine);

   ::Windows::ApplicationModel::Core::CoreApplication::Run(source);

   return ::success;

}



