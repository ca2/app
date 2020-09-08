#include "framework.h"
#include "acme/app_core.h"


ace_level acelevelCore(::ace_level::level_core, &defer_core_init);


//#ifdef ANDROID
//
//
//struct lconv* g_plconv = nullptr;
//
//
//#endif


namespace acme
{



   namespace static_start
   {


      CLASS_DECL_ACME void init()
      {

         xxdebug_box("acme.dll base_static_start (0)", "box", MB_OK);

//#ifdef ANDROID
//
//
//         g_plconv = new lconv;
//
//         g_plconv->decimal_point = strdup(".");
//
//         //oswindow_data::s_pdataptra = new oswindow_dataptra;
//
//         //oswindow_data::s_pmutex = new ::mutex;
//
//#endif

//#if defined(APPLEOS)
//
//         g_poswindowdataptra = new oswindow_dataptra;
//
//         g_poswindowdataptra->defer_create_mutex();
//
//#endif // defined(APPLEOS)

      #ifdef LINUX


            ::user::initialize_edesktop();


         #endif


      }










































































      CLASS_DECL_ACME void term()
      {


//#if defined(APPLEOS)
//
//         delete g_poswindowdataptra;
//
//         g_poswindowdataptra = nullptr;
//
//#endif // defined(APPLEOS)






      }



   } // namespace static_start


} // namespace acme





