#include "framework.h"
#include "acme/parallelization/mutex.h"
#include "acme/primitive/collection/int_map.h"
#include "acme/primitive/collection/string_map.h"
#include "acme/primitive/primitive/factory.h"
#include "acme/primitive/geometry2d/matrix.h"


//
//


//
//
//
//void init_cairo_mutex()
//{
//
//   ::platform::get()->__raw_construct(s_pmutex);
//
//#ifdef LINUX
//
//   ::platform::get()->__raw_construct(g_pmutexFc);
//
//   g_pmapFontPath = __new< string_to_string >();
//
//#endif
//
//   g_pmapFontFace = __new< string_map < i32_map < FT_Face> >  >();
//
//   g_pmapCairoFontFace = __new< string_map < cairo_font_face_t * >  >();
//
//   g_pmapFontError = __new< string_to_int  >();
//
//   g_pmapFontError2 = __new< string_to_int  >();
//
//}
//
//
//void term_cairo_mutex()
//{
//
//   ::acme::del(g_pmapFontError2);
//
//   ::acme::del(g_pmapFontError);
//
//   ::acme::del(g_pmapCairoFontFace);
//
//   ::acme::del(g_pmapFontFace);
//
//#ifdef LINUX
//
//   ::acme::del(g_pmapFontPath);
//
//   ::release(g_pmutexFc);
//
//#endif
//
//   ::release(s_pmutex);
//
//}


//#ifdef WINDOWS
//
//
//#ifdef UNIVERSAL_WINDOWS
//[Platform::MTAThread]
//#endif
//BOOL WINAPI DllMain(HINSTANCE hInstance,::u32 dwReason,LPVOID lpReserved)
//{
//
//   xxdebug_box("draw2d_cairo.dll DllMain (0)","box",e_message_box_ok);
//
//   UNREFERENCED_PARAMETER(hInstance);
//   UNREFERENCED_PARAMETER(lpReserved);
//
//
//   //openssl_DllMain(hInstance, dwReason, lpReserved);
//
//
//   if(dwReason == DLL_PROCESS_ATTACH)
//   {
//
//      information(L"draw2d_cairo.dll initializing!\n");
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
//      information(L"draw2d_cairo.dll terminating!\n");
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


void copy(::geometry2d::matrix * pmatrix, const cairo_matrix_t * pcairomatrix)
{

   pmatrix->a1 = pcairomatrix->xx;
   pmatrix->a2 = pcairomatrix->yx;
   pmatrix->b1 = pcairomatrix->xy;
   pmatrix->b2 = pcairomatrix->yy;
   pmatrix->c1 = pcairomatrix->x0;
   pmatrix->c2 = pcairomatrix->y0;

}


void copy(cairo_matrix_t* pcairomatrix,  const ::geometry2d::matrix* pmatrix)
{

   pcairomatrix->xx = pmatrix->a1;
   pcairomatrix->yx = pmatrix->a2;
   pcairomatrix->xy = pmatrix->b1;
   pcairomatrix->yy = pmatrix->b2;
   pcairomatrix->x0 = pmatrix->c1;
   pcairomatrix->y0 = pmatrix->c2;

}



