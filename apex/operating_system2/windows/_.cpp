#include "framework.h"
#include "apex/operating_system.h"
#include <VersionHelpers.h>

// #ifndef USE_OS_IMAGE_LOADER

// #include "FreeImage/FreeImage.h"

// #endif


#include "gdiplus.h"
#include <ddeml.h>
//#define memory_new ACME_NEW


void __term_threading();
void __term_windowing();

CLASS_DECL_ACME bool is_verbose();


::apex::system* app_common_prelude(int& iError, ::create*& pmaininitdata, app_core& appcore, HINSTANCE hinstance = nullptr, HINSTANCE hinstancePrev = nullptr, const scoped_string & strCmdLine = nullptr, int nShowCmd = e_display_restored);
int app_common_term(int iError, ::apex::system* psystem, app_core& appcore);



CLASS_DECL_APEX i32 __cdecl _memory_type(const void* p);



// typedef int
// (WINAPI* LPFN_ChangeWindowMessageFilter)(
//    const ::atom & atom,
//    ::u32 dwFlag);

//
//LPFN_ChangeWindowMessageFilter g_pfnChangeWindowMessageFilter = nullptr;
//
//typedef
//LSTATUS
//(APIENTRY* LPFN_RegGetValueW) (
//   HKEY hkey,
//   const ::wide_character * pSubKey,
//
//   const ::wide_character * pValue,
//
//   u32 dwFlags,
//   LPDWORD pdwType,
//   PVOID pvData,
//   LPDWORD pcbData
//   );
//
//LPFN_RegGetValueW g_pfnRegGetValueW = nullptr;
//
//
//// bool defer_co_initialize_ex(bool bMultiThread, bool bDisableOleDDE)
//// {
//
////    auto pthread = ::get_task();
//
////    if(!pthread)
////    {
//
////       return false;
//
////    }
//
////    HRESULT hr = pthread->m_hresultCoInitialize;
//
////    if(!pthread->m_bCoInitialize)
////    {
//
////       pthread->m_bCoInitialize = true;
//
////       if (bMultiThread)
////       {
//
////          hr = ::CoInitializeEx(nullptr, COINIT_MULTITHREADED);
//
////       }
////       else
////       {
//
////          hr = ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | (bDisableOleDDE ? COINIT_DISABLE_OLE1DDE : 0));
//
////       }
//
////       pthread->m_hresultCoInitialize = hr;
//
////    }
//
////    if(FAILED(hr))
////    {
//
////       ::output_debug_string("Failed to ::CoInitializeEx(nullptr, COINIT_MULTITHREADED) at __node_pre_init");
//
////       return false;
//
////    }
//
////    return true;
//
//// }




bool __node_apex_pre_term()
{



   return true;

}

bool __node_apex_pos_term()
{


   // #ifndef USE_OS_IMAGE_LOADER

   //    try
   //    {

   //       FreeImage_DeInitialise();

   //    }
   //    catch (...)
   //    {

   //    }

   // #endif // USE_OS_IMAGE_LOADER


   //if (g_pgdiplusStartupOutput != nullptr)
   //{

   //   g_pgdiplusStartupOutput->NotificationUnhook(g_gdiplusHookToken);


   //   ::Gdiplus::GdiplusShutdown(g_gdiplusToken);


   //   ::acme::del(g_pgdiplusStartupInput);
   //   ::acme::del(g_pgdiplusStartupOutput);
   //}

   if (is_verbose())
   {

      output_debug_string(L"apex terminating!\n");

   }

   //::CoUninitialize();


   //WSACleanup();


   return true;

}
