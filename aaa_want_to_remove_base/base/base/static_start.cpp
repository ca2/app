#include "framework.h"
#include "aura/app_core.h"

extern "C"
CLASS_DECL_BASE int_bool defer_base_init();

aura_level auralevelBase(::aura_level::level_base, &defer_base_init);

#if defined(APPLEOS)

#include "axis/os/macos/macos_window_impl.h"

//extern oswindow_dataptra * g_poswindowdataptra;

#elif defined(APPLE_IOS)

#include "axis/os/ios/ios_window_impl.h"

//extern oswindow_dataptra * g_poswindowdataptra;

#elif defined(ANDROID)

//#include "base/os/android/android_windowing.h"

//oswindow_dataptra * oswindow_data::s_pdataptra = nullptr;

//::mutex * oswindow_data::s_pmutex = nullptr;


#endif


#ifdef APPLEOS

extern oswindow_dataptra * g_poswindowdataptra;

#endif

#undef new



struct lconv * g_plconv = nullptr;

namespace base
{


   namespace static_start
   {


      CLASS_DECL_BASE void init()
      {


         xxdebug_box("axis.dll base_static_start (0)", "box", MB_OK);



#ifdef ANDROID


         g_plconv = new lconv;

         g_plconv->decimal_point = strdup(".");

         //oswindow_data::s_pdataptra = new oswindow_dataptra;

         //oswindow_data::s_pmutex = new ::mutex;

#endif

//#if defined(APPLEOS)
//
//         g_poswindowdataptra = new oswindow_dataptra;
//
//         g_poswindowdataptra->defer_create_mutex();
//
//#endif // defined(APPLEOS)


      }














































      CLASS_DECL_BASE void term()
      {


#if defined(APPLEOS)

         delete g_poswindowdataptra;

         g_poswindowdataptra = nullptr;

#endif // defined(APPLEOS)




      }


   } // namespace static_start


} // namespace base







