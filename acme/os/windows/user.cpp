#include "framework.h"
#include "id.h"
#include "acme/node/windows/_windows.h"


namespace user
{


   CLASS_DECL_ACME bool _os_calc_system_dark_mode()
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


   CLASS_DECL_ACME bool _os_calc_app_dark_mode()
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



   ::set g_bLastDarkModeApp;

   ::set g_bLastDarkModeSystem;


   void os_calc_dark_mode()
   {

      bool bDarkModeApp = _os_calc_app_dark_mode();

      bool bDarkModeSystem = _os_calc_system_dark_mode();

      if (g_bLastDarkModeApp != bDarkModeApp
         || g_bLastDarkModeSystem != bDarkModeSystem)
      {

         ::user::set_app_dark_mode(bDarkModeApp);

         ::user::set_system_dark_mode(bDarkModeSystem);

         g_bLastDarkModeApp = bDarkModeApp;

         g_bLastDarkModeSystem = bDarkModeSystem;

         system_set_modified(id_dark_mode);

      }

   }


} // namespace user


//CLASS_DECL_ACME HMONITOR GetUiMonitorHandle(HWND hwnd)
//{
//
//   return MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);
//
//}


//CLASS_DECL_ACME HMONITOR GetPrimaryMonitorHandle()
//{
//
//   const POINT pointZero = { 0,0 };
//
//   return MonitorFromPoint(pointZero, MONITOR_DEFAULTTOPRIMARY);
//
//}


//CLASS_DECL_ACME bool GetPrimaryMonitorRect(LPRECT lprect)
//{
//
//   MONITORINFO mi;
//
//   xxf_zero(mi);
//
//   mi.cbSize = sizeof(MONITORINFO);
//
//   if (GetMonitorInfo(GetPrimaryMonitorHandle(), &mi))
//   {
//
//      *lprect = mi.rcMonitor;
//
//   }
//   else
//   {
//
//      if (!::GetWindowRect(::get_desktop_window(), lprect))
//      {
//
//         return false;
//
//      }
//
//   }
//
//   return true;
//
//}
//


int _os_message_box(const char* pszMessage, const char* pszTitle, ::emessagebox emessagebox)
{

   int iMessageBox = emessagebox.m_eenum & 0x7f;

   wstring wstrText(pszMessage);

   wstring wstrTitle(pszTitle);

   int iResult = ::MessageBox(nullptr, wstrText, wstrTitle, iMessageBox);

   return iResult;

}






