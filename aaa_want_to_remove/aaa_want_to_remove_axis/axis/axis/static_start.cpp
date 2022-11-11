#include "framework.h"
#include "aura/app_core.h"
#include "sqlite3.h"


aura_level auralevelAxis(::aura_level::level_axis, &defer_axis_init);

namespace axis
{


   namespace static_start
   {


      CLASS_DECL_AXIS void init()
      {

         xxdebug_box("axis.dll axis_static_start (0)", "box", e_message_box_ok);


#if defined(LINUX)

//         set_defer_process_x_message(&axis_defer_process_x_message);

//         set_TranslateMessage(&axis_TranslateMessage);
//
//         set_DispatchMessage(&axis_DispatchMessage);
//
//         oswindow_data::s_pdataptra = memory_new oswindow_dataptra;
//
//         oswindow_data::s_pmutex = memory_new ::pointer < ::mutex >;
//
//         osdisplay_data::s_pdataptra = memory_new osdisplay_dataptra;
//
//         osdisplay_data::s_pmutex = memory_new ::pointer < ::mutex >;

#endif // defined(LINUX)



      }














































      CLASS_DECL_AXIS void term()
      {

//#if defined(LINUX)
//
//         delete osdisplay_data::s_pmutex;
//
//         osdisplay_data::s_pmutex = nullptr;
//
//         delete osdisplay_data::s_pdataptra;
//
//         osdisplay_data::s_pdataptra = nullptr;
//
//         delete oswindow_data::s_pmutex;
//
//         oswindow_data::s_pmutex = nullptr;
//
//         delete oswindow_data::s_pdataptra;
//
//         oswindow_data::s_pdataptra = nullptr;
//
//#endif // defined(LINUX)




      }



   } // namespace static_start


} // namespace axis




//void sqlite_init()
//{
//
//   sqlite3_config(SQLITE_CONFIG_MULTITHREAD);
//
//
//}

