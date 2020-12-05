#include "framework.h"
#include "acme/node/uwp/directx.h"
#include "acme/node/uwp/directx_interaction.h"
#include "acme/node/uwp/directx_impact.h"
#include "acme/node/uwp/directx_framework_view.h"

namespace acme
{


   ::estatus system::os_application_system_run()
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


} // namespace acme


