#pragma once


#include "acme/operating_system.h"


#ifndef __APP_ID


#define __APP_ID ""


#endif


i32 WINAPI _tWinMain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, TCHAR* pCmdLine, int nCmdShow)
{

   ::main main;

   main.m_argc = __argc;

   main.m_argv = __argv;

   main.m_wargv = __wargv;

   main.m_envp = *__p__environ();

   main.m_wenvp = *__p__wenviron();

   main.m_hinstanceThis = hinstanceThis;

   main.m_hinstancePrev = hinstancePrev;

   main.m_strCommandLine = pCmdLine;

   main.m_strAppId = __APP_ID;

   main.m_nCmdShow = nCmdShow;

   main.m_bConsole = false;

   __apps(main);

   __main(main);

   return main.m_iExitCode;

}


//#ifdef CLASS_DECL_APEX
//
//
//#include "openssl/applink.c"
//
//
//#endif



