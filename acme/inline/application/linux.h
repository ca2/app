#pragma once


#include "acme/operating_system.h"


#ifndef __APP_ID


#define __APP_ID ""


#endif


int main(int argc, char * argv[], char * envp[])
{

   class ::main main;

   main.m_argc = argc;

   main.m_argv = argv;

   main.m_envp = envp;

   main.m_strAppId = __APP_ID;

   main.m_bConsole = false;

   auto estatus = __main(main);

   int iStatus = estatus.error_status();

   return iStatus;

}


//#ifdef CLASS_DECL_APEX
//
//
//#include "openssl/applink.c"
//
//
//#endif



