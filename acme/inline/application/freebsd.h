#pragma once


#include "acme/operating_system.h"


extern char _binary__matter_zip_start[];
extern char _binary__matter_zip_end[];


#ifndef __APP_ID


#define __APP_ID ""


#endif


const_char_pointer  g_psz_br_init_symbol_app = __APP_ID;


int main(int argc, char * argv[], char * envp[])
{

   class ::main main;

   main.m_argc = argc;

   main.m_argv = argv;

   main.m_envp = envp;

   main.m_strAppId = __APP_ID;

   main.m_bConsole = false;

   main.m_pchar_binary__matter_zip_start = _binary__matter_zip_start;

   main.m_pchar_binary__matter_zip_end = _binary__matter_zip_end;

   br_init_set_symbol(g_psz_br_init_symbol_app);

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



