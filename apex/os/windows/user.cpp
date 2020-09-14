#include "framework.h"
#include "apex/node/windows/_windows.h"


CLASS_DECL_APEX oswindow get_desktop_window();



CLASS_DECL_APEX HMONITOR GetUiMonitorHandle(HWND hwnd)
{

   return MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);

}


CLASS_DECL_APEX HMONITOR GetPrimaryMonitorHandle()
{

   const POINT pointZero = { 0,0 };

   return MonitorFromPoint(pointZero, MONITOR_DEFAULTTOPRIMARY);

}


CLASS_DECL_APEX bool GetPrimaryMonitorRect(LPRECT lprect)
{

   MONITORINFO mi;

   xxf_zero(mi);

   mi.cbSize = sizeof(MONITORINFO);

   if (GetMonitorInfo(GetPrimaryMonitorHandle(), &mi))
   {

      *lprect = mi.rcMonitor;

   }
   else
   {

      if (!::GetWindowRect(::get_desktop_window(), lprect))
      {

         return false;

      }

   }

   return true;

}




