#include "framework.h"
#include "aura/node/universal_windows/_uwp.h"
#include "aura/node/universal_windows/directx_application.h"


namespace aura
{


   void system::os_application_system_run()
   {

      auto source = ::universal_windows::new_directx_application_source(this, m_strCommandLine);

      ::winrt::Windows::ApplicationModel::Core::CoreApplication::Run(source);

      return ::success;

   }


} // namespace aura




