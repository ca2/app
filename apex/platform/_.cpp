#include "framework.h"
#include "apex/message.h"
#include <stdio.h>

//
//#ifdef WINDOWS_DESKTOP
//
//#pragma comment(lib, "Dxva2.lib")
//
//#endif

//extern string_map < __pointer(::acme::library) >* g_pmapLibrary;

//extern ::mutex * psystem->m_mutexLibrary;


//extern "C"
CLASS_DECL_APEX int_bool defer_apex_init();

//extern "C"
CLASS_DECL_APEX int_bool defer_apex_term();

//
//namespace apex
//{
//
//
//
//   bool extract_sub_string(string& rString, const char* pszFullString, i32 iSubString, char chSep)
//   {
//
//      if (pszFullString == nullptr)
//      {
//
//         return false;
//
//      }
//
//      while (iSubString--)
//      {
//         pszFullString = strchr(pszFullString, chSep);
//
//         if (pszFullString == nullptr)
//
//         {
//            rString.Empty();        // return is_empty string as well
//            return false;
//         }
//         pszFullString++;       // point_i32 past the separator
//
//      }
//
//      const char* pchEnd = strchr(pszFullString, chSep);
//
//
//      strsize nLen = (pchEnd == nullptr) ? strlen(pszFullString) : (i32)(pchEnd - pszFullString);
//
//
//      ASSERT(nLen >= 0);
//
//      ::acme::memcpy_s(rString.get_string_buffer(nLen), nLen * sizeof(char), pszFullString, nLen * sizeof(char));
//
//      rString.release_string_buffer();   // Need to call ReleaseBuffer after calling get_string_buffer
//
//      return true;
//
//   }
//
//
//} // namespace apex




//
//
//#ifdef WINDOWS
//
//extern "C" const GUID LIBID_Lib = { 0x44EC0535,0x400F,0x11D0,{0x9D,0xCD,0x00,0xA0,0xC9,0x03,0x91,0xD3} };
//extern "C" const CLSID CLSID_Registrar = { 0x44EC053A,0x400F,0x11D0,{0x9D,0xCD,0x00,0xA0,0xC9,0x03,0x91,0xD3} };
//extern "C" const IID IID_IRegistrar = { 0x44EC053B,0x400F,0x11D0,{0x9D,0xCD,0x00,0xA0,0xC9,0x03,0x91,0xD3} };
//extern "C" const IID IID_IAxWinHostWindow = { 0xb6ea2050,0x048a,0x11d1,{0x82,0xb9,0x00,0xc0,0x4f,0xb9,0x94,0x2e} };
//extern "C" const IID IID_IAxWinAmbientDispatch = { 0xb6ea2051,0x048a,0x11d1,{0x82,0xb9,0x00,0xc0,0x4f,0xb9,0x94,0x2e} };
//extern "C" const IID IID_IInternalConnection = { 0x72AD0770,0x6A9F,0x11d1,{0xBC,0xEC,0x00,0x60,0x08,0x8F,0x44,0x4E} };
//extern "C" const IID IID_IDocHostUIHandlerDispatch = { 0x425B5AF0,0x65F1,0x11d1,{0x96,0x11,0x00,0x00,0xF8,0x1E,0x0D,0x0D} };
//extern "C" const IID IID_IAxWinHostWindowLic = { 0x3935BDA8,0x4ED9,0x495c,{0x86,0x50,0xE0,0x1F,0xC1,0xE3,0x8A,0x4B} };
//extern "C" const IID IID_IAxWinAmbientDispatchEx = { 0xB2D0778B,0xAC99,0x4c58,{0xA5,0xC8,0xE7,0x72,0x4E,0x53,0x16,0xB5} };
//
//
//#endif

//
//void gen_CrtErrorCheck(i32 i);

//
//void gen_CrtErrorCheck(i32 i)
//{
//   __UNREFERENCED_PARAMETER(i);
//}
//
//



int g_iApexRefCount = 0;


//extern "C"
//int_bool defer_apex_init()
//{
//
//   g_iApexRefCount++;
//
//   if (g_iApexRefCount > 1)
//      return true;
//
//   if (!apex_init())
//      return false;
//
//   return true;
//
//}

//extern "C"
//CLASS_DECL_APEX int_bool defer_apex_term()
//{
//
//   g_iApexRefCount--;
//
//   if (g_iApexRefCount >= 1)
//      return true;
//
//   ::apex_term();
//
//   return true;
//
//}


//
//namespace user
//{
//
//
//
//} // namespace user



//::apex::system* create_apex_system()
//{
//
//   return g_pfn_create_system();
//
//}


//
//CLASS_DECL_APEX int g_bApex = 0;
//



//
//
//CLASS_DECL_APEX u32 g_tickStartTime = 0;
//







//void __post_quit_message(i32 nExitCode)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   ::PostQuitMessage(nExitCode);
//
//#else
//
//   ::parallelization::finish(::get_application());
//
//#endif
//
//}
//

//string_map < __pointer(::acme::library) >* g_pmapLibrary = nullptr;
//string_map < PFN_NEW_APEX_LIBRARY >* g_pmapNewApexLibrary = nullptr;


//::mutex * psystem->m_mutexLibrary = nullptr;

//
//CLASS_DECL_APEX string_map < PFN_NEW_APEX_LIBRARY >& __get_new_apex_library()
//{
//
//   return psystem->m_mapNewApexLibrary;
//
//}
//
//
//CLASS_DECL_APEX string_map < __composite(::acme::library) >& __library()
//{
//
//   return psystem->m_mapLibrary;
//
//}

//
//
//CLASS_DECL_APEX PFN_NEW_APEX_LIBRARY get_get_new_apex_library(const char* psz)
//{
//
//   synchronous_lock synchronouslock(&psystem->m_mutexLibrary);
//
//   auto ppair = psystem->m_mapNewApexLibrary.plookup(psz);
//
//   if (::is_null(ppair))
//   {
//
//      return nullptr;
//
//   }
//
//   return ppair->element2();
//
//}

//
//CLASS_DECL_APEX::acme::library& get_library(const char* psz)
//{
//
//   synchronous_lock synchronouslock(&psystem->m_mutexLibrary);
//
//   return *psystem->m_mapLibrary[psz];
//
//}

//
//CLASS_DECL_APEX void register_get_new_apex_library(const char* psz, PFN_NEW_APEX_LIBRARY pfnNewApexLibrary)
//{
//
//   synchronous_lock synchronouslock(&psystem->m_mutexLibrary);
//
//   __get_new_apex_library()[psz] = pfnNewApexLibrary;
//
//}

//
//CLASS_DECL_APEX void register_library(const char* psz, ::acme::library* plibrary)
//{
//
//   synchronous_lock synchronouslock(&psystem->m_mutexLibrary);
//
//   __own(psystem, m_mapLibrary[psz], plibrary);
//
//}


CLASS_DECL_APEX int get_apex_init()
{

   return g_iApexRefCount;

}

//
//extern "C"
//CLASS_DECL_APEX::apex::system * apex_create_apex_system()
//{
//
//   return new ::apex::system();
//
//}


////extern "C"
//CLASS_DECL_APEX int_bool defer_apex_init()
//{
//
//   g_iApexRefCount++;
//
//   if (g_iApexRefCount > 1)
//   {
//
//      return true;
//
//   }
//
//   if (!apex_init())
//   {
//
//      return false;
//
//   }
//
//   s_papexstrpool = new apex_str_pool();
//
//   ::user::init_windowing();
//
//   g_bApex = 1;
//
//   return true;
//
//}


//extern "C"
//CLASS_DECL_APEX int_bool defer_apex_term()
//{
//
//   g_iApexRefCount--;
//
//   if (g_iApexRefCount >= 1)
//   {
//
//      return true;
//
//   }
//
//   ::user::term_windowing();
//
//   g_bApex = 0;
//
//   ::acme::del(s_papexstrpool);
//
//   apex_term();
//
//   return true;
//
//}







// ::map < void*, void*, ::application*, ::application* >* g_pmapApex = nullptr;


// void set_apex(void* p, ::application* papp)
// {

//    g_pmapApex->set_at(p, papp);

// }


// ::application* get_apex(void* p)
// {

//    return g_pmapApex->operator [](p);

// }


//CLASS_DECL_APEX LPFN_CREATE_SYSTEM g_pfn_create_system;

//CLASS_DECL_APEX const char* g_pszCooperativeLevel;

//CLASS_DECL_APEX int g_iDerivedApplication = 0;


//string get_debug_report_type_text(int iType)
//{
//
//   string strType;
//
//   if (iType == _CRT_ASSERT)
//   {
//
//      strType = "ASSERT";
//
//   }
//   else
//   {
//
//      __throw(error_invalid_argument);
//
//   }
//
//   return strType;
//
//}
//
//
////int __cdecl debug_report(int iType, char const* psz, int iLine, char const* pszModuleName, char const* pszFormat, ...)
////{
////
////   string strExtra;
////   va_list argList;
////   va_start(argList, pszFormat);
////   strExtra.format(pszFormat, argList);
////   va_end(argList);
////
////   string strModule;
////
////   if (pszModuleName != nullptr && *pszModuleName != '\0')
////   {
////
////      strModule.format("%s: ", pszModuleName);
////
////   }
////
////   string strType = get_debug_report_type_text(iType);
////
////   output_debug_string(strType + ": file: " + string(psz) + " line:" + __string(iLine) + strModule + strExtra);
////
////   return 1;
////
////}
//
////
////int __cdecl debug_report(int iType, wchar_t const* pszFile, int iLine, wchar_t const* pszModuleName, wchar_t const* pszFormat, ...)
////{
////
////
////   string strExtra;
////   va_list argList;
////   va_start(argList, pszFormat);
////   string strFormat;
////   strFormat = pszFormat;
////   strFormat.replace("%s", "%S");
////   strExtra.format(strFormat, argList);
////   va_end(argList);
////
////   string strModule;
////
////   string strType = get_debug_report_type_text(iType);
////
////   if (pszModuleName != nullptr && *pszModuleName != '\0')
////   {
////
////      strModule.format("%S: ", pszModuleName);
////
////   }
////
////
////   output_debug_string(strType + ": file: " + string(pszFile) + " line:" + __string(iLine) + strModule + strExtra);
////
////   return 1;
////
////
////}
////
////
////
////
////CLASS_DECL_APEX int is_ptr_null(const void* p, size_t s)
////{
////
////   return (((size_t)p) < s);
////
////}
////
////
//void c_post_system_event(::u64 u, void* pparam)
//{
//
//   lparam lparam = (iptr)pparam;
//
//
//   psystem->post_message(e_message_event2, (iptr)u, lparam);
//
//
//}

//
//extern "C"
//{
//
//   typedef void FN_VOID();
//
//   typedef FN_VOID* PFN_VOID;
//
//} // extern "C"




//CLASS_DECL_APEX ::e_status load_factory_library(string strLibrary)
//{
//
//
//   synchronous_lock synchronouslock(&psystem->m_mutexLibrary);
//
//   auto & plibrary = psystem->m_mapLibrary[strLibrary];
//
//   if (!plibrary)
//   {
//
//      __own(psystem, m_mapLibrary[strLibrary], __new(::acme::library));
//
//   }
//
//   if (!plibrary->is_opened())
//   {
//
//      plibrary->open(strLibrary);
//
//   }
//
//   auto pcreatefactory = plibrary->get < PFN_VOID >(strLibrary + "_create_factory");
//
//   if (!pcreatefactory)
//   {
//
//      return ::error_failed;
//
//   }
//
//   (*pcreatefactory)();
//
//   return ::success;
//
//}



//CLASS_DECL_APEX ::context * get_context(::object * pobject)
//{
//
//  if (pobject == nullptr)
//  {
//
//     return get_context();
//
//  }
//
//  auto pobject = __object(pobject);
//
//  if (::is_null(pobject))
//  {
//
//     return get_context();
//
//  }
//
//  ::context * pcontext = pobject->get_context();
//
//  if (pcontext != nullptr)
//  {
//
//     return pcontext;
//
//  }
//
//  return get_context();
//
//}


//CLASS_DECL_APEX ::application * get_application(::object * pobject)
//{
//
//  if (pobject == nullptr)
//  {
//
//     return ::get_application();
//
//  }
//
//  auto pobject = __object(pobject);
//
//  if (::is_null(pobject))
//  {
//
//     return ::get_application();
//
//  }
//
//  ::application * papplication = pobject->get_application();
//
//  if (papplication != nullptr)
//  {
//
//     return papplication;
//
//  }
//
//  return ::get_application();
//
//}


//CLASS_DECL_APEX ::apex::session * get_session(::object * pobject)
//{
//
//  if (pobject == nullptr)
//  {
//
//     return ::get_session();
//
//  }
//
//  auto pobject = __object(pobject);
//
//  if (::is_null(pobject))
//  {
//
//     return ::get_session();
//
//  }
//
//  ::apex::session * psessionContext = pobject->get_session();
//
//  if (psessionContext != nullptr)
//  {
//
//     return psessionContext;
//
//  }
//
//  return ::get_session();
//
//}


//CLASS_DECL_APEX ::apex::system * ::apex::get_system(::object * pobject)
//{
//
//  if (pobject == nullptr)
//  {
//
//     return psystem;
//
//  }
//
//  auto pobject = __object(pobject);
//
//  if (::is_null(pobject))
//  {
//
//     return psystem;
//
//  }
//
//  ::apex::system * psystemContext = psystem;
//
//  if (psystemContext != nullptr)
//  {
//
//     return psystemContext;
//
//  }
//
//  return psystem;
//
//}



