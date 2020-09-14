#include "framework.h"
//#include "acme/message.h"
#include <stdio.h>


#ifdef WINDOWS_DESKTOP

#pragma comment(lib, "Dxva2.lib")

#endif

//extern string_map < __pointer(::acme::library) >* g_pmapLibrary;

//extern ::mutex* &::get_context_system()->m_mutexLibrary;


//extern "C"
CLASS_DECL_ACME int_bool defer_acme_init();

//extern "C"
CLASS_DECL_ACME int_bool defer_acme_term();


namespace acme
{



   bool extract_sub_string(string& rString, const char* pszFullString, i32 iSubString, char chSep)
   {

      if (pszFullString == nullptr)
      {

         return false;

      }

      while (iSubString--)
      {
         pszFullString = strchr(pszFullString, chSep);

         if (pszFullString == nullptr)

         {
            rString.Empty();        // return is_empty string as well
            return FALSE;
         }
         pszFullString++;       // point past the separator

      }

      const char* pchEnd = strchr(pszFullString, chSep);


      strsize nLen = (pchEnd == nullptr) ? strlen(pszFullString) : (i32)(pchEnd - pszFullString);


      ASSERT(nLen >= 0);

      ::acme::memcpy_s(rString.get_string_buffer(nLen), nLen * sizeof(char), pszFullString, nLen * sizeof(char));

      rString.release_string_buffer();   // Need to call ReleaseBuffer after calling get_string_buffer

      return TRUE;

   }


} // namespace acme






#ifdef WINDOWS

extern "C" const GUID LIBID_Lib = { 0x44EC0535,0x400F,0x11D0,{0x9D,0xCD,0x00,0xA0,0xC9,0x03,0x91,0xD3} };
extern "C" const CLSID CLSID_Registrar = { 0x44EC053A,0x400F,0x11D0,{0x9D,0xCD,0x00,0xA0,0xC9,0x03,0x91,0xD3} };
extern "C" const IID IID_IRegistrar = { 0x44EC053B,0x400F,0x11D0,{0x9D,0xCD,0x00,0xA0,0xC9,0x03,0x91,0xD3} };
extern "C" const IID IID_IAxWinHostWindow = { 0xb6ea2050,0x048a,0x11d1,{0x82,0xb9,0x00,0xc0,0x4f,0xb9,0x94,0x2e} };
extern "C" const IID IID_IAxWinAmbientDispatch = { 0xb6ea2051,0x048a,0x11d1,{0x82,0xb9,0x00,0xc0,0x4f,0xb9,0x94,0x2e} };
extern "C" const IID IID_IInternalConnection = { 0x72AD0770,0x6A9F,0x11d1,{0xBC,0xEC,0x00,0x60,0x08,0x8F,0x44,0x4E} };
extern "C" const IID IID_IDocHostUIHandlerDispatch = { 0x425B5AF0,0x65F1,0x11d1,{0x96,0x11,0x00,0x00,0xF8,0x1E,0x0D,0x0D} };
extern "C" const IID IID_IAxWinHostWindowLic = { 0x3935BDA8,0x4ED9,0x495c,{0x86,0x50,0xE0,0x1F,0xC1,0xE3,0x8A,0x4B} };
extern "C" const IID IID_IAxWinAmbientDispatchEx = { 0xB2D0778B,0xAC99,0x4c58,{0xA5,0xC8,0xE7,0x72,0x4E,0x53,0x16,0xB5} };


#endif


void gen_CrtErrorCheck(i32 i);


void gen_CrtErrorCheck(i32 i)
{
   UNREFERENCED_PARAMETER(i);
}





int g_iAuraRefCount = 0;


//extern "C"
//int_bool defer_acme_init()
//{
//
//   g_iAuraRefCount++;
//
//   if (g_iAuraRefCount > 1)
//      return true;
//
//   if (!acme_init())
//      return false;
//
//   return true;
//
//}

//extern "C"
//CLASS_DECL_ACME int_bool defer_acme_term()
//{
//
//   g_iAuraRefCount--;
//
//   if (g_iAuraRefCount >= 1)
//      return true;
//
//   ::acme_term();
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



//::acme::system* create_acme_system()
//{
//
//   return g_pfn_create_system();
//
//}



CLASS_DECL_ACME int g_bAura = 0;






CLASS_DECL_ACME u32 g_tickStartTime = 0;



//
//
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
//   ::multithreading::set_finish(::get_context_application());
//
//#endif
//
//}


//string_map < __pointer(::acme::library) >* g_pmapLibrary = nullptr;
//string_map < PFN_NEW_ACME_LIBRARY >* g_pmapNewAuraLibrary = nullptr;


//::mutex* &::get_context_system()->m_mutexLibrary = nullptr;


//CLASS_DECL_ACME string_map < PFN_NEW_ACME_LIBRARY >& __get_new_acme_library()
//{
//
//   return ::get_context_system()->m_mapNewAuraLibrary;
//
//}
//
//
//CLASS_DECL_ACME string_map < __pointer(::acme::library) >& __library()
//{
//
//   return ::get_context_system()->m_mapLibrary;
//
//}
//
//
//
//CLASS_DECL_ACME PFN_NEW_ACME_LIBRARY get_get_new_acme_library(const char* psz)
//{
//
//   sync_lock sl(&::get_context_system()->m_mutexLibrary);
//
//   auto ppair = ::get_context_system()->m_mapNewAuraLibrary.plookup(psz);
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
//
//CLASS_DECL_ACME::acme::library& get_library(const char* psz)
//{
//
//   sync_lock sl(&::get_context_system()->m_mutexLibrary);
//
//   return *::get_context_system()->m_mapLibrary[psz];
//
//}


//CLASS_DECL_ACME void register_get_new_acme_library(const char* psz, PFN_NEW_ACME_LIBRARY pfnNewAuraLibrary)
//{
//
//   sync_lock sl(&::get_context_system()->m_mutexLibrary);
//
//   __get_new_acme_library()[psz] = pfnNewAuraLibrary;
//
//}
//
//
//CLASS_DECL_ACME void register_library(const char* psz, ::acme::library* plibrary)
//{
//
//   sync_lock sl(&::get_context_system()->m_mutexLibrary);
//
//   __library()[psz] = plibrary;
//
//}


CLASS_DECL_ACME int get_acme_init()
{

   return g_iAuraRefCount;

}


//extern "C"
//CLASS_DECL_ACME::acme::system * acme_create_acme_system()
//{
//
//   return new ::acme::system();
//
//}


////extern "C"
//CLASS_DECL_ACME int_bool defer_acme_init()
//{
//
//   g_iAuraRefCount++;
//
//   if (g_iAuraRefCount > 1)
//   {
//
//      return true;
//
//   }
//
//   if (!acme_init())
//   {
//
//      return false;
//
//   }
//
//   s_pacmestrpool = new acme_str_pool();
//
//   ::user::init_windowing();
//
//   g_bAura = 1;
//
//   return true;
//
//}


//extern "C"
//CLASS_DECL_ACME int_bool defer_acme_term()
//{
//
//   g_iAuraRefCount--;
//
//   if (g_iAuraRefCount >= 1)
//   {
//
//      return TRUE;
//
//   }
//
//   ::user::term_windowing();
//
//   g_bAura = 0;
//
//   ::acme::del(s_pacmestrpool);
//
//   acme_term();
//
//   return TRUE;
//
//}







// ::map < void*, void*, ::acme::application*, ::acme::application* >* g_pmapAura = nullptr;


// void set_acme(void* p, ::acme::application* papp)
// {

//    g_pmapAura->set_at(p, papp);

// }


// ::acme::application* get_acme(void* p)
// {

//    return g_pmapAura->operator [](p);

// }


//CLASS_DECL_ACME LPFN_CREATE_SYSTEM g_pfn_create_system;

//CLASS_DECL_ACME const char* g_pszCooperativeLevel;

//CLASS_DECL_ACME int g_iDerivedApplication = 0;


string get_debug_report_type_text(int iType)
{

   string strType;

   if (iType == _CRT_ASSERT)
   {

      strType = "ASSERT";

   }
   else
   {

      __throw(invalid_argument_exception());

   }

   return strType;

}


int __cdecl debug_report(int iType, char const* psz, int iLine, char const* pszModuleName, char const* pszFormat, ...)
{

   string strExtra;
   va_list argList;
   va_start(argList, pszFormat);
   strExtra.Format(pszFormat, argList);
   va_end(argList);

   string strModule;

   if (pszModuleName != nullptr && *pszModuleName != '\0')
   {

      strModule.Format("%s: ", pszModuleName);

   }

   string strType = get_debug_report_type_text(iType);

   output_debug_string(strType + ": file: " + string(psz) + " line:" + __str(iLine) + strModule + strExtra);

   return 1;

}


int __cdecl debug_report(int iType, wchar_t const* pszFile, int iLine, wchar_t const* pszModuleName, wchar_t const* pszFormat, ...)
{


   string strExtra;
   va_list argList;
   va_start(argList, pszFormat);
   string strFormat;
   strFormat = pszFormat;
   strFormat.replace("%s", "%S");
   strExtra.Format(strFormat, argList);
   va_end(argList);

   string strModule;

   string strType = get_debug_report_type_text(iType);

   if (pszModuleName != nullptr && *pszModuleName != '\0')
   {

      strModule.Format("%S: ", pszModuleName);

   }


   output_debug_string(strType + ": file: " + string(pszFile) + " line:" + __str(iLine) + strModule + strExtra);

   return 1;


}


CLASS_DECL_ACME void writeln(const char* psz)
{

   output_debug_string(string(psz) + "\n");

}


CLASS_DECL_ACME int is_ptr_null(const void* p, size_t s)
{

   return (((size_t)p) < s);

}

//
//void c_post_system_event(::u64 u, void* pparam)
//{
//
//   LPARAM lparam = (LPARAM)pparam;
//
//
//   ::get_context_system()->post_message(message_event2, (WPARAM)u, lparam);
//
//
//}


extern "C"
{

   typedef void FN_VOID();

   typedef FN_VOID* PFN_VOID;

} // extern "C"



//
//CLASS_DECL_ACME ::estatus load_factory_library(string strLibrary)
//{
//
//
//   sync_lock sl(&::get_context_system()->m_mutexLibrary);
//
//   __pointer(::acme::library)& plibrary = ::get_context_system()->m_mapLibrary[strLibrary];
//
//   if (!plibrary)
//   {
//
//      plibrary = new ::acme::library();
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
