#include "framework.h"
#include "aura/app_core.h"


aura_level auralevelCore(::aura_level::level_core, &defer_core_init);


//#ifdef ANDROID
//
//
//struct lconv* g_plconv = nullptr;
//
//
//#endif


namespace aura
{



   namespace static_start
   {


      CLASS_DECL_AURA void init()
      {

         xxdebug_box("aura.dll base_static_start (0)", "box", MB_OK);

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










































































      CLASS_DECL_AURA void term()
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


} // namespace base





