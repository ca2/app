// Created by camilo on 2022-03-11 10:54 PM <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/operating_system.h"
#include "acme/platform/application.h"
#include "acme/platform/system_setup.h"


int WINAPI WinMain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, CHAR* pCmdLine, int nCmdShow)
{

   auto papp = ::app_factory::new_app();

   papp->m_argc = __argc;

   papp->m_argv = __argv;

   papp->m_wargv = __wargv;

   papp->m_envp = *__p__environ();

   papp->m_wenvp = *__p__wenviron();

   papp->m_hinstanceThis = hinstanceThis;

   papp->m_hinstancePrev = hinstancePrev;

   papp->m_strCommandLine = ::GetCommandLineW();

   papp->m_nCmdShow = nCmdShow;

   papp->m_bConsole = false;

   int iExitCode = papp->main_loop();

   return iExitCode;

}



