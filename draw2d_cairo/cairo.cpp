#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif
//#include "aura/platform/static_start.h"


static ::mutex * s_pmutex = nullptr;

extern string_map < i32_map < FT_Face > > * g_pmapFontFace;

extern string_to_int * g_pmapFontError ;

extern string_to_int * g_pmapFontError2 ;

extern string_map < cairo_font_face_t * > * g_pmapCairoFontFace;

//extern CLASS_DECL_AURA array < matter * > * g_paAura;

#ifdef LINUX

extern ::mutex * g_pmutexFc;

extern string_to_string *      g_pmapFontPath;

#endif

::mutex * cairo_mutex()
{

   return s_pmutex;

}



void init_cairo_mutex()
{

   s_pmutex = new ::mutex();

#ifdef LINUX

   g_pmutexFc = new ::mutex();

   g_pmapFontPath = new string_to_string();

#endif

   g_pmapFontFace = new string_map < i32_map < FT_Face> > ();

   g_pmapCairoFontFace = new string_map < cairo_font_face_t * > ();

   g_pmapFontError = new string_to_int ();

   g_pmapFontError2 = new string_to_int ();

}


void term_cairo_mutex()
{

   ::acme::del(g_pmapFontError2);

   ::acme::del(g_pmapFontError);

   ::acme::del(g_pmapCairoFontFace);

   ::acme::del(g_pmapFontFace);

#ifdef LINUX

   ::acme::del(g_pmapFontPath);

   ::acme::del(g_pmutexFc);

#endif

   ::acme::del(s_pmutex);

}


//#ifdef WINDOWS
//
//
//#ifdef _UWP
//[Platform::MTAThread]
//#endif
//BOOL WINAPI DllMain(HINSTANCE hInstance,::u32 dwReason,LPVOID lpReserved)
//{
//
//   xxdebug_box("draw2d_cairo.dll DllMain (0)","box",e_message_box_ok);
//
//   __UNREFERENCED_PARAMETER(hInstance);
//   __UNREFERENCED_PARAMETER(lpReserved);
//
//
//   //openssl_DllMain(hInstance, dwReason, lpReserved);
//
//
//   if(dwReason == DLL_PROCESS_ATTACH)
//   {
//
//      output_debug_string(L"draw2d_cairo.dll initializing!\n");
//
//      xxdebug_box("draw2d_cairo.dll DllMain","box",e_message_box_ok);
//
//   }
//   else if(dwReason == DLL_PROCESS_DETACH)
//   {
//
//      HMODULE hmodule;
//
//      try
//      {
//
//         if(::GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,"ca.dll",&hmodule) != false)
//         {
//
//            try
//            {
//
//               ::FreeLibrary(hmodule);
//
//            }
//            catch(...)
//            {
//
//            }
//
//         }
//
//      }
//      catch(...)
//      {
//      }
//
//
//      output_debug_string(L"draw2d_cairo.dll terminating!\n");
//
//
//   }
//
//   return 1;   // ok
//
//}
//
//
//#endif
