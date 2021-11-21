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


::e_status main::system_construct(const main& main)
{

   *((PLAIN_MAIN*)this) = (const PLAIN_MAIN&)main;

   m_strCommandLine = main.m_strCommandLine;

   m_strAppId = main.m_strAppId;

   m_pfnImplement = main.m_pfnImplement;

   return ::success;

}


CLASS_DECL_ACME void set_main_thread();


::e_status __main(main& main)
{

   set_main_thread();

   ::e_status estatus = error_failed;

   ::e_status estatusEnd = error_failed;

   auto psystem = platform_create_system(main.m_strAppId);

   estatus = psystem->system_construct(main);

   if (!estatus)
   {

      return estatus;

   }

   estatus = psystem->call_init_system();

   if (!estatus)
   {

      return estatus;

   }

   {

      auto pnode = psystem->node();

      estatus = pnode->implement();

      estatusEnd = psystem->end();

   }

   return estatus;

}



