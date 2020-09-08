#include "framework.h"
#include "acme/node/windows/_windows.h"


namespace user
{


   CLASS_DECL_ACME bool is_system_dark_mode()
   {

      try
      {

         ::windows::registry::key key;

         key.open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize");

         DWORD dw;

         auto estatus = key._get("SystemUseLightTheme", dw);

         if (::failed(estatus))
         {

            estatus = key._get("AppsUseLightTheme", dw);

            if (::failed(estatus))
            {

               return false;

            }

         }

         return dw == 0;

      }
      catch (...)
      {

         return false;

      }

   }


   CLASS_DECL_ACME bool is_app_dark_mode()
   {

      try
      {

         ::windows::registry::key key;

         key.open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize");

         DWORD dw;

         auto estatus = key._get("AppsUseLightTheme", dw);

         if (::failed(estatus))
         {

            estatus = key._get("SystemUseLightTheme", dw);

            if (::failed(estatus))
            {

               return false;

            }

         }

         return dw == 0;

      }
      catch (...)
      {

         return false;

      }

   }


} // namespace user


CLASS_DECL_ACME HMONITOR GetUiMonitorHandle(HWND hwnd)
{

   return MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);

}


CLASS_DECL_ACME HMONITOR GetPrimaryMonitorHandle()
{

   const POINT pointZero = { 0,0 };

   return MonitorFromPoint(pointZero, MONITOR_DEFAULTTOPRIMARY);

}


CLASS_DECL_ACME bool GetPrimaryMonitorRect(LPRECT lprect)
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




