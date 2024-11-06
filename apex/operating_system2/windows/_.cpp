#include "framework.h"
#include "apex/operating_system.h"
#include <VersionHelpers.h>

// #ifndef USE_OS_IMAGE_LOADER

// #include "FreeImage/FreeImage.h"

// #endif


#include "gdiplus.h"
#include <ddeml.h>



void __term_threading();
void __term_windowing();

CLASS_DECL_ACME bool is_verbose();


::apex::system* app_common_prelude(int& iError, ::create*& pmaininitdata, app_core& appcore, HINSTANCE hinstance = nullptr, HINSTANCE hinstancePrev = nullptr, const ::scoped_string & scopedstrCmdLine = nullptr, int nShowCmd = e_display_normal);
int app_common_term(int iError, ::apex::system* psystem, app_core& appcore);



CLASS_DECL_APEX int __cdecl _memory_type(const void* p);


bool __node_apex_pre_term()
{

   return true;

}


bool __node_apex_pos_term()
{

   if (is_verbose())
   {

      information(L"apex terminating!\n");

   }

   return true;

}
