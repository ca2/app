#pragma once


#include "acme/operating_system.h"
void implement(class ::system* psystem);


i32 WINAPI _tWinMain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, TCHAR* pCmdLine, int nCmdShow)
{


   main_arguments mainarguments;

   mainarguments.m_argc = __argc;

   mainarguments.m_argv = __argv;

   mainarguments.m_wargv = __wargv;

   mainarguments.m_envp = *__p__environ();

   mainarguments.m_wenvp = *__p__wenviron();

   mainarguments.m_hinstanceThis = hinstanceThis;

   mainarguments.m_hinstancePrev = hinstancePrev;

   mainarguments.m_pszCommandLine = pCmdLine;

   mainarguments.m_nCmdShow = nCmdShow;

   mainarguments.m_bConsole = true;




   mainarguments.m_pfnImplement = &::implement;

   auto estatus = __main(mainarguments);

   int iStatus = estatus.error_status();

   return iStatus;
}


