#include "framework.h"


namespace plugin
{

   run_start_installer::run_start_installer(::elemental * pobject, plugin * pplugin) :
      m_pplugin(pplugin)
   {
      UNREFERENCED_PARAMETER(pobject);
   }

   void run_start_installer::run_start_install(const char * pszStart)
   {
      m_pplugin->run_start_install(pszStart);
   }

} // namespace plugin


