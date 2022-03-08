//#include "apex/operating_system.h"
//
//
//CLASS_DECL_ACME void set_main_user_thread();
//
//
//i32 WINAPI _tWinMain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, TCHAR * pCmdLine, int nCmdShow)
//{
//
//
//   main_arguments mainarguments;
//
//   mainarguments.m_argc = __argc;
//
//   mainarguments.m_argv = __argv;
//
//   mainarguments.m_wargv = __wargv;
//
//   mainarguments.m_envp = *__p__environ();
//
//   mainarguments.m_wenvp = *__p__wenviron();
//
//   mainarguments.m_hinstanceThis = hinstanceThis;
//
//   mainarguments.m_hinstancePrev = hinstancePrev;
//
//   mainarguments.m_pszCommandLine = pCmdLine;
//
//   mainarguments.m_nCmdShow = nCmdShow;
//
//   mainarguments.m_bConsole = false;
//
////   set_main_user_thread();
////
////   string strAppId;
////
////#ifdef _APP_ID
////
////   strAppId = _APP_ID;
////
////#else
////
////   strAppId = executable_get_app_id(hinstance);
////
////#endif;
////
////   auto psystem = platform_create_system(strAppId);
////
////   if (!psystem)
////   {
////
////      return -1;
////
////   }
////
////   psystem->m_bConsole = false;
////
////   application_common(psystem);
////
////   string strCommandLine(pCmdLine);
////
////   psystem->system_construct(hinstance, hPrevInstance, strCommandLine, nCmdShow);
////
////   psystem->set_current_handles();
////
//////   auto estatus = psystem->system_main();
//////
//////   if (!estatus)
//////   {
//////    
//////      ::i32 iErrorStatus = estatus.error_status();
//////
//////      return iErrorStatus;
//////
//////   }
////
////   auto estatus = psystem->init_system();
////   
////   if(!estatus)
////   {
////      
////      return estatus.error_status();
////      
////   }
////
////   auto pnode = psystem->node();
////
////   estatus = pnode->implement();
////
////   auto estatusEnd = psystem->end();
////
//   auto estatus = __main(mainarguments);
//
//   //return iExitCode;
//
//   ::i32 iErrorStatus = estatus.error_status();
//
//   return iErrorStatus;
//
//}
//

//#include "openssl/applink.c"



