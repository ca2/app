//
// Created by camilo on 30/10/2021 ~ 00:00 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#ifdef LINUX
#include "acme/operating_system/ansi/binreloc.h"
#endif
#include "acme/platform/acme.h"
#include "acme/platform/set_app_id.h"
#include "acme/platform/system_setup.h"
#include "_main_hold_base.h"


namespace acme
{

   
   void initialize();


} // namespace acme


PLAIN_MAIN::PLAIN_MAIN()
{

   ::acme::initialize();

}



main::main()
{

}


main::~main()
{


}





//const char * br_init_get_symbol();
//
//
//const char * g_pszAppId = nullptr;
//
//
//void executable_set_app_id(const char * pszAppId)
//{
//
//	g_pszAppId = pszAppId;
//
//}
//
//
//const char * executable_get_app_id()
//{
//
//
//   return g_pszAppId;
//
//}
//
//
//set_app_id::set_app_id(const char * pszAppId)
//{
//
//#ifdef LINUX
//
//   br_init_set_symbol(pszAppId);
//
//#endif
//
//   executable_set_app_id(pszAppId);
//
//}


void main::system_construct(const main * pmain)
{

   *((PLAIN_MAIN*)this) = *pmain;

   m_strCommandLine = pmain->m_strCommandLine;

   m_strAppId = pmain->m_strAppId;

   m_pfnImplement = pmain->m_pfnImplement;

#if defined(LINUX) || defined(ANDROID) || defined(FREEBSD)

   if(!m_pchar_binary__matter_zip_start && !m_pchar_binary__matter_zip_end
   && pmain->m_pchar_binary__matter_zip_start && pmain->m_pchar_binary__matter_zip_end)
   {

      m_pchar_binary__matter_zip_start = pmain->m_pchar_binary__matter_zip_start;

      m_pchar_binary__matter_zip_end = pmain->m_pchar_binary__matter_zip_end;

   }

#endif
   
   if(!m_pacmeapplicationStartup && pmain->m_pacmeapplicationStartup)
   {
    
      m_pacmeapplicationStartup = pmain->m_pacmeapplicationStartup;
      
   }

}


string main::_get_argv(int iArgument) const
{

   if (iArgument < 0 || iArgument >= _get_argc())
   {

      return "";

   }

   if (m_wargv && m_wargv[iArgument])
   {

      return m_wargv[iArgument];

   }
   else if (m_argv && m_argv[iArgument])
   {

      return m_argv[iArgument];

   }

   return "";

}


string main::get_executable() const
{

   return _get_argv(0);

}


string_array main::get_arguments()
{

   string_array stra;

   for (::index i = 0; i < m_argc; i++)
   {

      string strArgument;

      if (m_wargv && m_wargv[i])
      {

      strArgument = m_wargv[i];

      }
      else if (m_argv && m_argv[i])
      {

         strArgument = m_argv[i];

      }
      else
      {

         break;

      }

      stra.add(strArgument);

   }

   return ::move(stra);

}


string main::get_argument1(int iArgument) const
{

   return _get_argv(iArgument + 1);

}


CLASS_DECL_ACME void set_main_user_thread();


void __main()
{




}


void __main(::acme::application * pacmeapplication)
{

   #ifdef WINDOWS_DESKTOP
   //{

   //   auto papp = ::app_factory::new_app();

   pacmeapplication->m_argc = __argc;

   pacmeapplication->m_argv = __argv;

   pacmeapplication->m_wargv = __wargv;

   pacmeapplication->m_envp = *__p__environ();

   pacmeapplication->m_wenvp = *__p__wenviron();

      //pacmeapplication->m_hinstanceThis = hinstanceThis;

      //pacmeapplication->m_hinstancePrev = hinstancePrev;

   pacmeapplication->m_strCommandLine = ::GetCommandLineW();

      //pacmeapplication->m_nCmdShow = nCmdShow;

      //pacmeapplication->m_bConsole = false;

      //int iExitCode = pacmeapplication->main_loop();

      //return iExitCode;

#elif !defined(_UWP)

   pacmeapplication->set_args(argc, argv, envp);

#endif


   set_main_user_thread();

   ::e_status estatus = error_failed;

   ::e_status estatusEnd = error_failed;

   string strAppId;

   if (!pacmeapplication->m_bConsole)
   {

      strAppId = pacmeapplication->m_strAppId;

   }

   //main.m_bAudio = main_hold_base::is_audio_enabled();

   auto pfactoryitem = ::factory::get_factory()->get_factory_item<::acme::system>();

   __pointer(::acme::system) psystem = pfactoryitem->create_element();

   //psystem->m_pacmeapplicationStartup = pacmeapplication;

   psystem->system_construct(pacmeapplication);

   psystem->create_os_node();

   auto pnode = psystem->node();

   pnode->implement(pnode, psystem);

   if(pacmeapplication->m_iExitCode == 0 && psystem->m_iExitCode != 0)
   {

      pacmeapplication->m_iExitCode = psystem->m_iExitCode;

   }

   //}

   //auto psystem = platform_create_system(strAppId);

   /*estatus =*/

   //if (!estatus)
   //{

   //   return estatus;

   //}

   /*estatus = */ //psystem->__task_init();

   //if (!estatus)
   //{

   //   return estatus;

   //}


   //return estatus;

}


app_flag::app_flag(::main & main, const char * pszFlag)
{

   if(!::is_empty(pszFlag))
   {

      if(!strcmp(pszFlag, "no_audio"))
      {

         main.m_bAudio = false;

      }
      else if(!strcmp(pszFlag, "no_imaging"))
      {

         main.m_bImaging = false;

      }

   }

}



static char * g_pchar_binary__matter_zip_start = nullptr;


static char * g_pchar_binary__matter_zip_end = nullptr;


embed_resource::embed_resource(char * start, char * end)
{

   g_pchar_binary__matter_zip_start = start;

   g_pchar_binary__matter_zip_end = end;

}


char * embed_resource::get_start()
{

   return g_pchar_binary__matter_zip_start;

}


char * embed_resource::get_end()
{

   return g_pchar_binary__matter_zip_end;

}



