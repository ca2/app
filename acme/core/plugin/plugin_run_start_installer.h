#pragma once


#include "acme/run_start_installer.h"


namespace plugin
{



   class run_start_installer :
      virtual public ::acme::run_start_installer
   {
   public:


      plugin * m_pplugin;


      run_start_installer(::generic * pobject, plugin * pplugin);


      virtual void run_start_install(const char * pszStart);

   };


} // namespace plugin


