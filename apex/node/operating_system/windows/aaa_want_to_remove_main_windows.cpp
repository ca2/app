#include "framework.h"
#include "apex/platform/app_core.h"
#include "application.h"
#include "apex/os/_application.h"


//CLASS_DECL_APEX i32 main_windows(HINSTANCE hinstance, HINSTANCE hPrevInstance, char * pCmdLine, int nCmdShow)
//{
//
//   int iStatus = -1;
//
//   class apex_apex apex_apex;
//
//   {
//
////
////      int iResult = 0;
////
////#ifdef GET_COMMAND_LINE
////
////      char* pszCommandLine = GET_COMMAND_LINE(argc, argv);
////
////#elif defined(MAIN_STRING)
////
////      char* pszCommandLine = strdup(MAIN_STRING);
////
////#elif defined (_WIN32)
////
////      char* pszCommandLine = _strdup("");
////
////#else
////
////      char* pszCommandLine = strdup("");
////
////#endif
//
////#ifdef LINUX
////
////      br_init_set_symbol(br_init_get_symbol());
////
////#endif
//
////#ifdef ACID_APP
////
////      PFN_NEW_APEX_APPLICATION pfnNewAuraApplication = &get_acid_app;
////
////#else
////
////      PFN_NEW_APEX_APPLICATION pfnNewAuraApplication = (PFN_NEW_APEX_APPLICATION) ::GetProcAddress(hinstance, "new_apex_application");;
////
////#endif
//
////#ifdef ACID_LIBRARY
////
////      PFN_NEW_APEX_LIBRARY pfnNewLibrary = &get_acid_library;
////
////#else
////
////      PFN_NEW_APEX_LIBRARY pfnNewLibrary = nullptr;
////
////#endif
//
//      //if (pfnNewAuraApplication)
//      //{
//
//      //   pfnNewAuraApplication = 
//
//      //}
//
//      //if (!papexmain)
//      //{
//
//        // message_box("Please!!\n\nImplement entry function with the macro \n\n__main\n{\n\n\t<\"Main Body\">\n\n}\n\n." + e_message_box_icon_error);
//
//         //return -1;
//
//      //}
//
//      ::apex_main_struct mainstruct = {};
//
//      mainstruct.m_bConsole = false;
//      mainstruct.m_bDraw2d = true;
//      mainstruct.m_bUser = true;
//      mainstruct.m_bUserEx = true;
//      mainstruct.m_bShowApplicationInformation = false;
//
//      auto psystem = __new(::apex::system());
//
//      psystem->system_construct(&mainstruct, hinstance, hPrevInstance, pCmdLine, nCmdShow);
//
//      //pmaindata->m_pappcore = __new(app_core(pmaindata));
//
//      if (!psystem->system_beg())
//      {
//
//         throw ::exception::exception("The application didn't started.");
//
//      }
//
//      bool bOk = psystem->system_ini();
//
//      if (!bOk)
//      {
//
//         throw ::exception::exception("The application didn't started. (2)");
//
//      }
//
//      psystem->system_start();
//
//      iStatus = psystem->system_run();
//
//      psystem->system_end();
//
//   }
//
//   return iStatus;
//
//}



