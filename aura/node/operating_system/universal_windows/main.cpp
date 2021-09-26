#include "framework.h"
//#include "universal_windows.h"
//#include "sal.h"


//CLASS_DECL_AURA int ca2_main();
//
//
////CLASS_DECL_BOOT extern fixed_alloc_array * g_pfixedallocaWstring;
//
////CLASS_DECL_BOOT fixed_alloc_array * new_wstring_manager();
//
//void CLASS_DECL_AURA __cdecl _ca2_purecall()
//{
//   __throw(::exception());
//}
//
//
//CLASS_DECL_AURA void __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers);
//
//
////::aura::application *     win_application_create(::aura::application * pappSystem, const ::string & pszId);
////::aura::application *     win_instantiate_application(::aura::application * pappSystem, const ::string & pszId);
////int                     win_application_procedure(::aura::application * pappSystem)
////::u32 c_cdecl          win_application_thread_proc(LPVOID);
///////////////////////////////////////////////////////////////////////////////
//// Standard WinMain implementation
////  Can be replaced as long as '::ca2::WinInit' is called first
//
//
////int CLASS_DECL_AURA win_main(::aura::system * psystem, ::Array < ::String ^ > ^ args)
////{
////
////   if (!main_initialize())
////      return -1;
////
////
////   _set_purecall_handler(_ca2_purecall);
////
////
////   int nReturnCode = 0;
////
////
////   auto pcommand  = __new(::universal_windows::command);
////
////   //    pcommand->m_hInstance               = nullptr;
////   //    pcommand->m_hPrevInstance           = nullptr;
////   //    pcommand->m_nCmdShow                = 0;
////
////   //pinitmaindata->m_hInstance             = hInstance;
////   //pinitmaindata->m_hPrevInstance         = hPrevInstance;
////   //pinitmaindata->m_strCommandLine        = ::str::international::unicode_to_utf8(::GetCommandLineW());
////   //pinitmaindata->m_nCmdShow              = nCmdShow;
////
////
////   psystem->startup_command(pcommand);
////
////   //MessageBox(nullptr, "box1", "box1", e_message_box_icon_information);
////
////   psystem->main();
////
////   try
////   {
////
////      main_finalize();
////
////   }
////   catch (...)
////   {
////   }
////
////   try
////   {
////      delete psystem;
////   }
////   catch (...)
////   {
////   }
////
////   psystem = nullptr;
////
////
////   try
////   {
////      //      delete __get_module_state()->m_pmapHWND;
////   }
////   catch (...)
////   {
////   }
////   /*   try
////   {
////   delete __get_module_state()->m_pmapHDC;
////   }
////   catch(...)
////   {
////   }*/
////   /*   try
////   {
////   delete __get_module_state()->m_pmapHGDIOBJ;
////   }
////   catch(...)
////   {
////   }*/
////   //      delete __get_module_state()->m_pmapHMENU;
////
////   //try
////   //{
////   //   __get_module_state()->m_pmapHWND     = nullptr;
////   //}
////   //catch(...)
////   //{
////   //}
////   /*   try
////   {
////   __get_module_state()->m_pmapHDC      = nullptr;
////   }
////   catch(...)
////   {
////   }*/
////   /*   try
////   {
////   __get_module_state()->m_pmapHGDIOBJ  = nullptr;
////   }
////   catch(...)
////   {
////   }*/
////
////
////   //   set_heap_mutex(nullptr);
////
////   return nReturnCode;
////
////
////}
//
//
////int CLASS_DECL_AURA ca2_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, const ::string & lpCmdLine, int nCmdShow)
////{
////   try
////   {
////
////      _set_purecall_handler(_ca2_purecall);
////
////      ::aura::system * psystem = new ::aura::system();
////
////
////      //sleep(30 * 1000);
////
////
////      ASSERT(hPrevInstance == nullptr);
////
////      int nReturnCode = 0;
////
////      ::universal_windows::main_init_data * pinitmaindata  = new ::universal_windows::main_init_data;
////
////      pinitmaindata->m_hInstance             = hInstance;
////      pinitmaindata->m_hPrevInstance         = hPrevInstance;
////      pinitmaindata->m_strCommandLine        = lpCmdLine;
////      pinitmaindata->m_nCmdShow              = nCmdShow;
////
////
////      psystem->init_main_data(pinitmaindata);
////
////
////      nReturnCode = psystem->main();
////
////
////      __win_term();
////
////
////      try
////      {
////         delete psystem;
////      }
////      catch(...)
////      {
////      }
////
////      psystem = nullptr;
////
////      try
////      {
//////         delete __get_module_state()->m_pmapHWND;
////      }
////      catch(...)
////      {
////      }
/////*      try
////      {
////         delete __get_module_state()->m_pmapHDC;
////      }
////      catch(...)
////      {
////      }*/
/////*      try
////      {
////         delete __get_module_state()->m_pmapHGDIOBJ;
////      }
////      catch(...)
////      {
////      }*/
//////      delete __get_module_state()->m_pmapHMENU;
////      try
////      {
////         __get_module_state()->m_pmapHWND     = nullptr;
////      }
////      catch(...)
////      {
////      }
/////*      try
////      {
////         __get_module_state()->m_pmapHDC      = nullptr;
////      }
////      catch(...)
////      {
////      }
////      try
////      {
////         __get_module_state()->m_pmapHGDIOBJ  = nullptr;
////      }
////      catch(...)
////      {
////      }*/
////
//////      set_heap_mutex(nullptr);
////
////
////      return nReturnCode;
////   }
////   catch(...)
////   {
////   }
////   return -1;
////}
////
////
//
//void CLASS_DECL_AURA __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers)
//{
//   __UNREFERENCED_PARAMETER(uiCode);
//   __UNREFERENCED_PARAMETER(ppointers);
//}
//
//
//string ca2_command_line()
//{
//
//   string strAppId = ::winrt::Windows::ApplicationModel::Package::Current->Id->Name;
//
//   if (strAppId.is_empty())
//   {
//
//      return "";
//
//   }
//
//   if (!::str::begins_eat_ci(strAppId, "com."))
//   {
//
//      ::str::begins_eat_ci(strAppId, "com.");
//
//   }
//
//   string_array stra;
//
//   stra.explode(".", strAppId);
//
//   stra.predicate_each([](auto & str)
//   {
//
//      str.replace("-", "_");
//
//   }, 1);
//
//   strAppId = stra.implode("/");
//
//   return "app.exe : app=" + strAppId + " client_only";
//
//}
//
//
//
//
//
//bool os_init_application()
//{
//
//   return true;
//
//}
#undef papplication

//void os_post_quit()
//{
//
//   ::winrt::Windows::UI::Xaml::papplication::Current->Exit();
//
//}

