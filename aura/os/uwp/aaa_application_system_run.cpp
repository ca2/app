#include "framework.h"
#include "aura/node/uwp/_uwp.h"
#include "aura/node/uwp/directx_application.h"


namespace aura
{


   ::e_status system::os_application_system_run()
   {

      auto source = ::uwp::new_directx_application_source(this, m_strCommandLine);

      ::Windows::ApplicationModel::Core::CoreApplication::Run(source);

      return ::success;

   }


} // namespace aura




