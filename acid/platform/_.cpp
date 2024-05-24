#include "framework.h"
#include "acid/constant/id.h"

////#include "acid/exception/exception.h"
#include "acid/_operating_system.h"


#ifdef WINDOWS_DESKTOP

#pragma comment(lib, "Dxva2.lib")

#endif


CLASS_DECL_ACID int_bool defer_ace_init();

CLASS_DECL_ACID int_bool defer_ace_term();


namespace acid
{



   bool extract_sub_string(string& rString, const ::scoped_string & scopedstrFullString, i32 iSubString, char chSep)
   {

      auto pszFullString = scopedstrFullString.begin();

      if (pszFullString == nullptr)
      {

         return false;

      }

      while (iSubString--)
      {
         pszFullString = ansi_chr(pszFullString, chSep);

         if (pszFullString == nullptr)

         {
            rString.empty();        // return is_empty string as well
            return false;
         }
         pszFullString++;       // point_i32 past the separator

      }

      const char* pchEnd = ansi_chr(pszFullString, chSep);


      strsize nLen = (pchEnd == nullptr) ? ansi_len(pszFullString) : (i32)(pchEnd - pszFullString);


      ASSERT(nLen >= 0);

      ::safe_memory_copy2(rString.get_buffer(nLen), nLen, pszFullString, nLen);

      rString.release_buffer();   // Need to call ReleaseBuffer after method get_buffer

      return true;

   }


} // namespace acid






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
//int_bool defer_ace_init()
//{
//
//   g_iAuraRefCount++;
//
//   if (g_iAuraRefCount > 1)
//      return true;
//
//   if (!ace_init())
//      return false;
//
//   return true;
//
//}

//extern "C"
//CLASS_DECL_ACID int_bool defer_ace_term()
//{
//
//   g_iAuraRefCount--;
//
//   if (g_iAuraRefCount >= 1)
//      return true;
//
//   ::ace_term();
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



//::acid::system* create_ace_system()
//{
//
//   return g_pfn_create_system();
//
//}



CLASS_DECL_ACID int g_bAura = 0;






CLASS_DECL_ACID u32 g_tickStartTime = 0;



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
//   ::parallelization::finish(::get_app());
//
//#endif
//
//}


CLASS_DECL_ACID int get_ace_init()
{

   return g_iAuraRefCount;

}



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
   strExtra.formatf(pszFormat, argList);
   va_end(argList);

   string strModule;

   if (pszModuleName != nullptr && *pszModuleName != '\0')
   {

      strModule.formatf("%s: ", pszModuleName);

   }

   string strType = get_debug_report_type_text(iType);

   ::acid::get()->platform()->informationf(strType + ": file: " + string(psz) + " line:" + as_string(iLine) + strModule + strExtra);

   return 1;

}


int __cdecl debug_report(int iType, wchar_t const* pszFile, int iLine, wchar_t const* pszModuleName, wchar_t const* pszFormat, ...)
{


   string strExtra;
   va_list argList;
   va_start(argList, pszFormat);
   string strFormat;
   strFormat = pszFormat;
   strFormat.replace_with("%S", "%s");
   strExtra.formatf(strFormat.c_str(), argList);
   va_end(argList);

   string strModule;

   string strType = get_debug_report_type_text(iType);

   if (pszModuleName != nullptr && *pszModuleName != '\0')
   {

      strModule.formatf("%S: ", pszModuleName);

   }

   ::acid::get()->platform()->informationf(strType + ": file: " + string(pszFile) + " line:" + as_string(iLine) + strModule + strExtra);

   return 1;

}


CLASS_DECL_ACID int is_ptr_null(const void* p, size_t s)
{

   return (((size_t)p) < s);

}

//
//void c_post_system_event(::u64 u, void* pparam)
//{
//
//   lparam lparam = (LPARAM)pparam;
//
//
//   system()->post_message(e_message_event2, (WPARAM)u, lparam);
//
//
//}


extern "C"
{

   typedef void FN_VOID();

   typedef FN_VOID* PFN_VOID;


} // extern "C"


void safe_free(void * pfree)
{

   if(pfree == nullptr)
   {

      return;

   }

   ::free(pfree);

}



void this_type_init(const ::scoped_string & scopedstr)
{


}


void this_type_term(const ::scoped_string & scopedstr)
{
   
   
}



