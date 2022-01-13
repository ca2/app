//
// Created by camilo on 30/10/2021 ~ 00:00 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#ifdef LINUX
#include "acme/node/operating_system/ansi/binreloc.h"
#endif
#include "acme/platform/set_app_id.h"



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

   //return ::success;

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


string main::get_argument1(int iArgument) const
{

   return _get_argv(iArgument + 1);

}


CLASS_DECL_ACME void set_main_thread();


void __main(main& main)
{

   set_main_thread();

   ::e_status3 estatus = error_failed;

   ::e_status3 estatusEnd = error_failed;

   auto psystem = platform_create_system(main.m_strAppId);

   /*estatus =*/ psystem->system_construct(main);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   /*estatus = */ psystem->call_init_system();

   //if (!estatus)
   //{

   //   return estatus;

   //}

   {

      auto pnode = psystem->node();

      /*estatus =*/ pnode->implement(pnode, psystem);

   }

   //return estatus;

}



