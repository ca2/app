// Created by camilo on 2021-04-02 01:58 BRT <3TBS_!!
#pragma once
#include "acme/primitive/collection/strdup_array.h"

//void stage();
class ::system* acme_system_init();
void acme_system_term();



CLASS_DECL_ACME void process_set_args(int argc, platform_char** argv);

int main(int argc, platform_char** argv)
{

   ::e_status estatus = ::success;

   //process_set_args(argc, argv);

   string strAppId;

#ifdef _APP_ID

   strAppId = _APP_ID;

#else

   strAppId = executable_get_app_id(nullptr);

#endif;

   auto psystem = platform_create_system(strAppId);

   if (!psystem)
   {

      return -1;

   }

   psystem->m_bConsole = false;

   application_common(psystem);

   //string strCommandLine(pCmdLine);
   {

      //wcsdup_array wcsdupa;

      //auto envp = psystem->node()->_get_envp(wcsdupa);

      platform_char** envp = nullptr;

      psystem->system_construct(argc, argv, envp);

      //psystem->system_construct(hinstance, hPrevInstance, strCommandLine, nCmdShow);

      psystem->set_current_handles();

      estatus = psystem->init_system();

      if (!estatus)
      {

         return estatus;

      }

      estatus = psystem->m_papexsystem->__thread_init();

      if (!estatus)
      {

         return estatus;

      }

      implement(psystem);

      estatus = psystem->m_estatus;

   }

//   {
//
//#ifdef WINDOWS
//
//      wcsdup_array wcsdupa;
//
//      auto envp = psystem->node()->_get_envp(wcsdupa);
//
//#endif
//      estatus = implement(argc, argv, envp);
//
//   }

   auto iErrorStatus = estatus.error_status();

   return iErrorStatus;

}


