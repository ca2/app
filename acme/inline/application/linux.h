#pragma once


#include "acme/operating_system.h"




//#ifdef LINUX
//
//extern ::i8 _binary__matter_zip_start[];
//extern ::i8 _binary__matter_zip_end[];

//#endif

//#ifndef __APP_ID
//
//
//#define __APP_ID ""
//
//
//#endif

template < typename APPLICATION >
class app_runner
{
public:


   class ::main *                m_pmain;
   ::pointer<APPLICATION>       m_papplication;


   app_runner(::i32 argc, char_pointer argv[], char_pointer envp[], char_pointer res_start, char_pointer res_end)
   {

      m_pmain = memory_new class ::main;

      m_pmain->m_argc = argc;

      m_pmain->m_argv = argv;

      m_pmain->m_envp = envp;

      //m_pmain->m_strAppId = __APP_ID;

      m_pmain->m_bConsole = false;

      m_pmain->m_pchar_binary__matter_zip_start = res_start;

      m_pmain->m_pchar_binary__matter_zip_end = res_end;

      m_papplication = allocateø APPLICATION();

   }


   ::i32 main()
   {

      __main(*m_pmain);

      ::i32 iExitCode = m_pmain->m_iExitCode;

      return iExitCode;

   }


   ~app_runner()
   {

      m_papplication.release();

      ::acme::del(m_pmain);

   }


};


//#define __start(argc, argv, envp) ____start _____start; class ::main main(argc, argv, envp)
//#define __run() __main(main)
//#define __end return main.m_iExitCode

//APPLICATION_CLASS g_app;


::i32 main(::i32 argc, char_pointer argv[], char_pointer envp[])
{

   auto papp = allocateø APPLICATION_CLASS();

   papp->set_args(argc, argv, envp);

#if defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)

   papp->m_pchar_binary__matter_zip_start = embed_resource::get_start();

   papp->m_pchar_binary__matter_zip_end = embed_resource::get_end();

#endif

   ::i32 iExitCode = papp->main_loop();

   return iExitCode;

}


#endif


//app_runner < APPLICATION_CLASS > apprunner(argc, argv, envp, _binary__matter_zip_start, _binary__matter_zip_end);


//#ifdef CLASS_DECL_APEX
//
//
//#include "openssl/applink.c"
//
//
//#endif



