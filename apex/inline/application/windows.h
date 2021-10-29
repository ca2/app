#include "apex/operating_system.h"


i32 WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, TCHAR * pCmdLine, int nCmdShow)
{

#ifdef CUBE

   main_hold mainhold;

#endif

   set_main_thread();

   string strAppId;

#ifdef _APP_ID

   strAppId = _APP_ID;

#else

   strAppId = executable_get_app_id(hinstance);

#endif;

   auto psystem = platform_create_system(strAppId);

   if (!psystem)
   {

      return -1;

   }

   psystem->m_bConsole = false;

   application_common(psystem);

   string strCommandLine(pCmdLine);

   psystem->system_construct(hinstance, hPrevInstance, strCommandLine, nCmdShow);

   psystem->set_current_handles();

//   auto estatus = psystem->system_main();
//
//   if (!estatus)
//   {
//    
//      ::i32 iErrorStatus = estatus.error_status();
//
//      return iErrorStatus;
//
//   }

   auto estatus = psystem->init_system();
   
   if(!estatus)
   {
      
      return estatus.error_status();
      
   }

   auto pnode = psystem->node();

   estatus = pnode->implement();

   auto estatusEnd = psystem->end();

   ::i32 iErrorStatus = estatus.error_status();

   return iErrorStatus;

}


#include "openssl/applink.c"



