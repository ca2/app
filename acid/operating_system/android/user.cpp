// Created by camilo 2020-12-18 05:33 BRT <TBS!!, Mummi and bilbo!!
// streaming contribution: strager, Kebabskal and togglebit
// chatting contribution Immortalmonsterhybrid.

#include "framework.h"
//#include "atom.h"
#include "acid/operating_system/android/_android.h"

//
//namespace user
//{
//
//
////   string _os_get_user_theme()
////   {
////
////      return "";
////
////   }
//
//
//   void _os_process_user_theme(string strTheme)
//   {
//
//      __UNREFERENCED_PARAMETER(strTheme);
//
//   }
//
//
//
//   CLASS_DECL_ACID bool _os_calc_system_dark_mode()
//   {
//
//      return false;
//
//   }
//
//
//   CLASS_DECL_ACID bool _os_calc_app_dark_mode()
//   {
//
//      return false;
//
//   }
//
//
//
//   ::logic::boolean      g_bLastDarkModeApp;
//
//   ::logic::boolean      g_bLastDarkModeSystem;
//
//
//   void os_calc_dark_mode()
//   {
//
//      bool bDarkModeApp = _os_calc_app_dark_mode();
//
//      bool bDarkModeSystem = _os_calc_system_dark_mode();
//
//      if (g_bLastDarkModeApp != bDarkModeApp
//         || g_bLastDarkModeSystem != bDarkModeSystem)
//      {
//
//         ::user::set_app_dark_mode(bDarkModeApp);
//
//         ::user::set_system_dark_mode(bDarkModeSystem);
//
//         g_bLastDarkModeApp = bDarkModeApp;
//
//         g_bLastDarkModeSystem = bDarkModeSystem;
//
//         ::aceacesystem()->signal(id_os_dark_mode);
//
//      }
//
//   }
//
//
//} // namespace user
//
//
////CLASS_DECL_ACID HMONITOR GetUiMonitorHandle(HWND hwnd)
////{
////
////   return MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);
////
////}
//
//
////CLASS_DECL_ACID HMONITOR GetPrimaryMonitorHandle()
////{
////
////   const ::point_i32 pointZero = { 0,0 };
////
////   return MonitorFromPoint(pointZero, MONITOR_DEFAULTTOPRIMARY);
////
////}
//
//
////CLASS_DECL_ACID bool GetPrimaryMonitorRect(::rectangle_i32 * lprect)
////{
////
////   MONITORINFO mi;
////
////   zero(mi);
////
////   mi.cbSize = sizeof(MONITORINFO);
////
////   if (GetMonitorInfo(GetPrimaryMonitorHandle(), &mi))
////   {
////
////      *lprect = mi.rcMonitor;
////
////   }
////   else
////   {
////
////      if (!::GetWindowRect(::get_desktop_window(), lprect))
////      {
////
////         return false;
////
////      }
////
////   }
////
////   return true;
////
////}
////
//
//
//int _os_message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox)
//{
//
//   int iMessageBox = emessagebox.m_eenum & 0x7f;
//
//   wstring wstrText(pszMessage);
//
//   wstring wstrTitle(pszTitle);
//
//   ///int iResult = ::MessageBox(nullptr, wstrText, wstrTitle, iMessageBox);
//
//   int iResult = 0;
//
//   return iResult;
//
//}
//
//
//
//
//
//
//
//
