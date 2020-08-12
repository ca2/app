#include "framework.h"

#include <X11/Xlib.h>


CLASS_DECL_AXIS i32 ca2_main();

//CLASS_DECL_AXIS extern fixed_alloc_array * g_pfixedallocaWstring;

//CLASS_DECL_AXIS fixed_alloc_array * new_wstring_manager();

void CLASS_DECL_AXIS __cdecl _ca2_purecall()
{
    __throw(::exception::exception());
}


void __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers);


int xlib_error_handler(Display * d, XErrorEvent * e)
{

   if(e->request_code == 12) //
   {

      if(e->error_code == BadValue)
      {
      }

   }
   char sz[1024];
   XGetErrorText(d, e->error_code, sz, sizeof(sz));
   fputs(sz, stderr);

   abort();

}


void __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);
}
