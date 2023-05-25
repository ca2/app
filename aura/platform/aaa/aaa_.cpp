#include "framework.h"
//#include "aura/message.h"
#include <stdio.h>


#ifdef WINDOWS_DESKTOP

#pragma comment(lib, "Dxva2.lib")

#endif

//extern string_map < ::pointer<::acme::library >> g_pmapLibrary;

//extern ::pointer < ::mutex >* ::auraacmesystem()->m_pmutexLibrary;


//extern "C"
CLASS_DECL_AURA int_bool defer_aura_init();

//extern "C"
CLASS_DECL_AURA int_bool defer_aura_term();


namespace aura
{



   bool extract_sub_string(string& rString, const ::string & pszFullString, i32 iSubString, char chSep)
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
            rString.empty();        // return is_empty string as well
            return false;
         }
         pszFullString++;       // point past the separator

      }

      const char* pchEnd = strchr(pszFullString, chSep);


      strsize nLen = (pchEnd == nullptr) ? strlen(pszFullString) : (i32)(pchEnd - pszFullString);


      ASSERT(nLen >= 0);

      ::aura::memcpy_s(rString.get_buffer(nLen), nLen * sizeof(char), pszFullString, nLen * sizeof(char));

      rString.release_buffer();   // Need to call ReleaseBuffer after calling get_buffer

      return true;

   }


} // namespace aura






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
   __UNREFERENCED_PARAMETER(i);
}





int g_iAuraRefCount = 0;


//extern "C"
//int_bool defer_aura_init()
//{
//
//   g_iAuraRefCount++;
//
//   if (g_iAuraRefCount > 1)
//      return true;
//
//   if (!aura_init())
//      return false;
//
//   return true;
//
//}

//extern "C"
//CLASS_DECL_AURA int_bool defer_aura_term()
//{
//
//   g_iAuraRefCount--;
//
//   if (g_iAuraRefCount >= 1)
//      return true;
//
//   ::aura_term();
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



//::aura::system* create_aura_system()
//{
//
//   return g_pfn_create_system();
//
//}



CLASS_DECL_AURA int g_bAura = 0;






CLASS_DECL_AURA u32 g_tickStartTime = 0;





//extern "C"
CLASS_DECL_AURA void debug_print(const ::string & pszFormat, ...)
{

   if (is_ptr_null(pszFormat, 1024))
   {

      return;

   }

   va_list argList;

   va_start(argList, pszFormat);

   char sz[4096];

   vsnprintf(sz, sizeof(sz), pszFormat, argList);

   ::output_debug_string(sz);

   va_end(argList);

}


void __post_quit_message(i32 nExitCode)
{

#ifdef WINDOWS_DESKTOP

   ::PostQuitMessage(nExitCode);

#else

   ::parallelization::set_finish(::get_app());

#endif

}


//string_map < ::pointer<::acme::library >> g_pmapLibrary = nullptr;
//string_map < PFN_NEW_AURA_LIBRARY >* g_pmapNewAuraLibrary = nullptr;


//::pointer < ::mutex >* ::auraacmesystem()->m_pmutexLibrary = nullptr;


CLASS_DECL_AURA string_map < PFN_NEW_AURA_LIBRARY >& __get_new_aura_library()
{

   return ::auraacmesystem()->m_mapNewAuraLibrary;

}


CLASS_DECL_AURA string_map < ::pointer<::acme::library >> __library()
{

   return ::auraacmesystem()->m_mapLibrary;

}



CLASS_DECL_AURA PFN_NEW_AURA_LIBRARY get_get_new_aura_library(const ::string & psz)
{

   synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

   auto ppair = ::auraacmesystem()->m_mapNewAuraLibrary.plookup(psz);

   if (::is_null(ppair))
   {

      return nullptr;

   }

   return ppair->element2();

}


CLASS_DECL_AURA::acme::library& get_library(const ::string & psz)
{

   synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

   return *::auraacmesystem()->m_mapLibrary[psz];

}


CLASS_DECL_AURA void register_get_new_aura_library(const ::string & psz, PFN_NEW_AURA_LIBRARY pfnNewAuraLibrary)
{

   synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

   __get_new_aura_library()[psz] = pfnNewAuraLibrary;

}


CLASS_DECL_AURA void register_library(const ::string & psz, ::acme::library* plibrary)
{

   synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

   __library()[psz] = plibrary;

}


CLASS_DECL_AURA int get_aura_init()
{

   return g_iAuraRefCount;

}


extern "C"
CLASS_DECL_AURA::aura::system * aura_create_aura_system()
{

   return memory_new ::aura::system();

}


////extern "C"
//CLASS_DECL_AURA int_bool defer_aura_init()
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
//   if (!aura_init())
//   {
//
//      return false;
//
//   }
//
//   s_paurastrpool = memory_new aura_str_pool();
//
//   ::user::init_windowing();
//
//   g_bAura = 1;
//
//   return true;
//
//}


//extern "C"
//CLASS_DECL_AURA int_bool defer_aura_term()
//{
//
//   g_iAuraRefCount--;
//
//   if (g_iAuraRefCount >= 1)
//   {
//
//      return true;
//
//   }
//
//   ::user::term_windowing();
//
//   g_bAura = 0;
//
//   ::acme::del(s_paurastrpool);
//
//   aura_term();
//
//   return true;
//
//}







// ::map < void*, void*, ::aura::application*, ::aura::application* >* g_pmapAura = nullptr;


// void set_aura(void* p, ::aura::application* papp)
// {

//    g_pmapAura->set_at(p, papp);

// }


// ::aura::application* get_aura(void* p)
// {

//    return g_pmapAura->operator [](p);

// }


//CLASS_DECL_AURA LPFN_CREATE_SYSTEM g_pfn_create_system;

//CLASS_DECL_AURA const char* g_pszCooperativeLevel;

//CLASS_DECL_AURA int g_iDerivedApplication = 0;


string get_debug_report_type_text(int iType)
{

   string strType;

   if (iType == _CRT_ASSERT)
   {

      strType = "ASSERT";

   }
   else
   {

      throw ::exception(error_bad_argument);

   }

   return strType;

}


int __cdecl debug_report(int iType, char const* psz, int iLine, char const* pszModuleName, char const* pszFormat, ...)
{

   string strExtra;
   va_list argList;
   va_start(argList, pszFormat);
   strExtra.format(pszFormat, argList);
   va_end(argList);

   string strModule;

   if (pszModuleName != nullptr && *pszModuleName != '\0')
   {

      strModule.format("%s: ", pszModuleName);

   }

   string strType = get_debug_report_type_text(iType);

   output_debug_string(strType + ": file: " + string(psz) + " line:" + as_string(iLine) + strModule + strExtra);

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
   strExtra.format(strFormat, argList);
   va_end(argList);

   string strModule;

   string strType = get_debug_report_type_text(iType);

   if (pszModuleName != nullptr && *pszModuleName != '\0')
   {

      strModule.format("%S: ", pszModuleName);

   }


   output_debug_string(strType + ": file: " + string(pszFile) + " line:" + as_string(iLine) + strModule + strExtra);

   return 1;


}



CLASS_DECL_AURA int is_ptr_null(const void* p, size_t s)
{

   return (((size_t)p) < s);

}


void c_post_system_event(::u64 u, void* pparam)
{

   LPARAM lparam = (LPARAM)pparam;


   ::auraacmesystem()->post_message(e_message_event2, (WPARAM)u, lparam);


}


extern "C"
{

   typedef void FN_VOID();

   typedef FN_VOID* PFN_VOID;

} // extern "C"




CLASS_DECL_AURA void load_factory_library(string strLibrary)
{


   synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

   ::pointer<::acme::library> plibrary = ::auraacmesystem()->m_mapLibrary[strLibrary];

   if (!plibrary)
   {

      plibrary = memory_new ::acme::library();

   }

   if (!plibrary->is_opened())
   {

      plibrary->open(strLibrary);

   }

   auto pcreatefactory = plibrary->get < PFN_VOID >(strLibrary + "_create_factory");

   if (!pcreatefactory)
   {

      return ::error_failed;

   }

   (*pcreatefactory)();

   return ::success;

}
