#include "framework.h"
#include "acid/constant/id.h"


#include "acid/_operating_system.h"
//#include "_winrt.h"
//#include "acid/node/universal_windows/_uwp.h"
//#include "acid/operating_system/windows_common/draw2d_direct2d_global.h"


CLASS_DECL_ACID int g_iMouse = -1;


CLASS_DECL_ACID int_bool GetCursorPos(::point_i32 * lppoint);




int g_iMouseX = 0;
int g_iMouseY = 0;



CLASS_DECL_ACID void defer_dock_application(int_bool bDock)
{

   __UNREFERENCED_PARAMETER(bDock);

}




namespace user
{


   string _os_get_user_theme()
   {

      return "";

   }



   ::logic::boolean      g_bLastDarkModeApp;


} // namespace user


