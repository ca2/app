#include "framework.h"
#include "acme/constant/id.h"


#include "acme/_operating_system.h"
//#include "_winrt.h"
//#include "acme/node/universal_windows/_uwp.h"
//#include "acme/operating_system/windows_common/draw2d_direct2d_global.h"


CLASS_DECL_ACME int g_iMouse = -1;


CLASS_DECL_ACME int_bool GetCursorPos(::int_point * lppoint);




int g_iMouseX = 0;
int g_iMouseY = 0;



CLASS_DECL_ACME void defer_dock_application(int_bool bDock)
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


