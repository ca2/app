#include "framework.h"
#include "aura/platform/app_core.h"
#include "application.h"
#include "aura/os/_application.h"


//CLASS_DECL_AURA ::estatus aura_run_system_init(::aura::system* psystem)
//{
//
//   if (!psystem->system_beg())
//   {
//
//      throw ::exception::exception("The application didn't started.");
//
//   }
//
//   bool bOk = psystem->system_init();
//
//   if (!bOk)
//   {
//
//      throw ::exception::exception("The application didn't started. (2)");
//
//   }
//
//   auto estatus = psystem->system_start();
//
//   return estatus;
//
//}


//CLASS_DECL_AURA::estatus aura_run_system_term(::aura::system* psystem)
//{
//
//   try
//   {
//
//      psystem->system_end();
//
//   }
//   catch (...)
//   {
//
//   }
//
//   return ::success;
//
//}


//CLASS_DECL_AURA ::estatus aura_run_system_proc(::aura::system* psystem)
//{
//
//   ::estatus estatus = psystem->system_proc();
//
//   return estatus;
//
//}




//CLASS_DECL_AURA i32 aura_run_system(::aura::system * psystem)
//{
//
//   //int iStatus = -1;
//
//   //class aura_aura aura_aura;
//
//   //{
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
////      PFN_NEW_AURA_APPLICATION pfnNewAuraApplication = &get_acid_app;
////
////#else
////
////      PFN_NEW_AURA_APPLICATION pfnNewAuraApplication = (PFN_NEW_AURA_APPLICATION) ::GetProcAddress(hinstance, "new_aura_application");;
////
////#endif
//
////#ifdef ACID_LIBRARY
////
////      PFN_NEW_AURA_LIBRARY pfnNewLibrary = &get_acid_library;
////
////#else
////
////      PFN_NEW_AURA_LIBRARY pfnNewLibrary = nullptr;
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
//      //if (!pauramain)
//      //{
//
//        // message_box("Please!!\n\nImplement entry function with the macro \n\n__main\n{\n\n\t<\"Main Body\">\n\n}\n\n." + message_box_icon_error);
//
//         //return -1;
//
//      //}
//
////      ::aura_main_struct mainstruct = {};
////
////      mainstruct.m_bConsole = false;
////      mainstruct.m_bDraw2d = true;
////      mainstruct.m_bUser = true;
////      mainstruct.m_bUserEx = true;
////      mainstruct.m_bShowApplicationInformation = false;
////
////      auto psystem = __new(::aura::system());
////
////#ifdef _UWP
////
////      psystem->construct_system(stra);
////
////#else
////
////      psystem->construct_system(&mainstruct, hinstance, hPrevInstance, pCmdLine, nCmdShow);
////
////#endif
//
//      //pmaindata->m_pappcore = __new(app_core(pmaindata));
//
//   ::estatus estatus = psystem->system_prep();
//
//   if (estatus)
//   {
//
//      return estatus;
//
//   }
//
//   estatus = psystem->system_init();
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   if (psystem->m_pmainstruct && psystem->m_pmainstruct->m_bConsole)
//   {
//
//      return ::success;
//
//   }
//
//   //auto estatusReturn = aura_run_system_proc(psystem);
//
//   //estatus = aura_run_system_term(psystem);
//
//   //int iErrorStatus = estatusReturn.error_status();
//
//   //return iErrorStatus;
//
//}

