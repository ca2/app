//
// Created by camilo on 30/10/2021 ~ 00:00 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#ifdef LINUX
#include "acme/operating_system/ansi/binreloc.h"
#endif
#include "acme/platform/acme.h"
#include "acme/platform/set_app_id.h"


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


void main::system_construct(const main& main)
{

   *((PLAIN_MAIN*)this) = (const PLAIN_MAIN&)main;

   m_strCommandLine = main.m_strCommandLine;

   m_strAppId = main.m_strAppId;

   m_pfnImplement = main.m_pfnImplement;

#if defined(LINUX) || defined(ANDROID) || defined(FREEBSD)

   if(!m_pchar_binary__matter_zip_start && !m_pchar_binary__matter_zip_end
   && main.m_pchar_binary__matter_zip_start && main.m_pchar_binary__matter_zip_end)
   {

      m_pchar_binary__matter_zip_start = main.m_pchar_binary__matter_zip_start;

      m_pchar_binary__matter_zip_end = main.m_pchar_binary__matter_zip_end;

   }

#endif
   
   if(!m_pappStartup && main.m_pappStartup)
   {
    
      m_pappStartup = main.m_pappStartup;
      
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


void __main(main& main)
{

   set_main_user_thread();

   ::e_status estatus = error_failed;

   ::e_status estatusEnd = error_failed;

   string strAppId;

   if (!main.m_bConsole)
   {

      strAppId = main.m_strAppId;

   }

   auto pfactoryitem = ::factory::get_factory()->get_factory_item<class::system>();

   __pointer(class ::system) psystem = pfactoryitem->create_element();

   psystem->system_construct(main);

   psystem->create_os_node();

   auto pnode = psystem->node();

   pnode->implement(pnode, psystem);

   if(main.m_iExitCode == 0 && psystem->m_iExitCode != 0)
   {

      main.m_iExitCode = psystem->m_iExitCode;

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



