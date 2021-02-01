#include "framework.h"
#include "apex/operating_system.h"


#define ___TEMP_CLASS_NAME_SIZE 4096


CLASS_DECL_APEX void defer_dock_application(int_bool bDock)
{

   UNREFERENCED_PARAMETER(bDock);

}



//CLASS_DECL_APEX int_bool os_init_windowing()
//{
//
//   return true;
//
//}


//CLASS_DECL_APEX void os_term_windowing()
//{
//
//}


//::user::interaction * get_system_window_interaction(::os_system_window * psystemwindow)
//{
//
//   return nullptr;
//
//}


CLASS_DECL_APEX i64 oswindow_id(HWND hwnd)
{

   return (i64)hwnd;

}


//CLASS_DECL_APEX int_bool is_window(oswindow oswindow)
//{
//
//   return ::IsWindow(oswindow);
//
//}


CLASS_DECL_APEX bool get_gui_thread_info(PGUITHREADINFO pinfo)
{

   HWND hwndForeground = ::GetForegroundWindow();

   if (hwndForeground == nullptr)
   {

      return false;

   }

   ::u32 dwThread = GetWindowThreadProcessId(hwndForeground, nullptr);

   __zero(pinfo);

   pinfo->cbSize = sizeof(GUITHREADINFO);

   if (!::GetGUIThreadInfo(dwThread, pinfo))
   {

      ::u32 dwLastError = ::GetLastError();

      return false;

   }

   return true;

}


CLASS_DECL_APEX oswindow get_focus()
{

   GUITHREADINFO info;

   if (!get_gui_thread_info(&info))
   {

      return nullptr;

   }

   return info.hwndFocus;

}


//CLASS_DECL_APEX oswindow set_focus(oswindow oswindow)
//{
//
//   return ::SetFocus(oswindow);
//
//}


CLASS_DECL_APEX oswindow get_active_window()
{

   //attach_thread_input_to_main_thread(true);

   auto oswindow = ::GetActiveWindow();

   //attach_thread_input_to_main_thread(false);

   return oswindow;

}


//CLASS_DECL_APEX oswindow set_active_window(oswindow oswindow)
//{
//
//   return ::SetActiveWindow(oswindow);
//
//}


CLASS_DECL_APEX oswindow get_capture()
{

   return ::GetCapture();

}


//CLASS_DECL_APEX oswindow set_capture(oswindow oswindow)
//{
//
//   return ::SetCapture(oswindow);
//
//}


CLASS_DECL_APEX int_bool release_capture()
{

   return ::ReleaseCapture();

}


//CLASS_DECL_APEX int_bool destroy_window(oswindow oswindow)
//{
//
//   return ::DestroyWindow(oswindow);
//
//}






// void update_session_cursor(class user::interaction_impl * puiimpl)
// {

//    __pointer(::windows::interaction_impl) pimpl = puiimpl;

//    if (pimpl.is_set())
//    {

//       return;

//    }

//    Sess(puiimpl->get_context_application()).get_cursor_pos(puiimpl->m_pointCursor);

// }

//CLASS_DECL_APEX int_bool show_window(oswindow oswindow, const ::e_display & edisplay, const ::e_activation & eactivation)
//{
//
//   int nCmdShow = windows_show_window(edisplay, eactivation);
//
//   return ::ShowWindow(oswindow, nCmdShow);
//
//}


///// from top to bottom
//CLASS_DECL_APEX __pointer(::user::oswindow_array) get_top_level_windows(bool bDesktop, bool bVisible)
//{
//
//   /// from top to bottom
//   top_level_enum toplevelenum(bDesktop, bVisible);
//
//   return toplevelenum.m_poswindowa;
//
//}


//top_level_enum::top_level_enum(bool bDesktop, bool bVisible) :
//   m_bVisible(bVisible)
//{
//
//   __construct_new(m_poswindowa);
//
//   if (bDesktop)
//   {
//
//      ::EnumDesktopWindows(nullptr, &::top_level_enum::EnumWindowsProc, (LPARAM)this);
//
//   }
//   else
//   {
//
//      ::EnumWindows(&::top_level_enum::EnumWindowsProc, (LPARAM)this);
//
//   }
//
//
//}
//
//
//top_level_enum::~top_level_enum()
//{
//
//
//}
//
//
//BOOL CALLBACK top_level_enum::EnumWindowsProc(oswindow oswindow, LPARAM lParam)
//{
//
//   top_level_enum * ptoplevelenum = (top_level_enum *) lParam;
//
//   if (ptoplevelenum->m_bVisible && !IsWindowVisible(oswindow))
//   {
//
//      return true;
//
//   }
//
//   ptoplevelenum->m_poswindowa->add(oswindow);
//
//   return true;
//
//}
//
//
//int_bool point_is_window_origin(POINT_I32 ptHitTest, oswindow oswindowExclude, int iMargin)
//{
//
//   auto poswindowa = get_top_level_windows();
//
//   if (poswindowa->is_empty())
//   {
//
//      return false;
//
//   }
//
//   ::rectangle_i32 rectWindow;
//
//   for(auto & oswindow : *poswindowa)
//   {
//
//      if(oswindow != oswindowExclude)
//      {
//
//         if (!IsWindowVisible(oswindow))
//         {
//
//            continue;
//
//         }
//
//         if (::GetWindowRect(oswindow, rectWindow))
//         {
//
//            ::rectangle_i32 rectHitTest;
//            
//            rectHitTest.set(rectWindow.origin(), ::size());
//
//            rectHitTest.inflate(iMargin + 1);
//
//            if (rectHitTest.contains(ptHitTest))
//            {
//
//               return true;
//
//            }
//
//            //return true;
//
//         }
//
//      }
//
//   }
//
//   return false;
//
//}



//
//void window_create_caret(oswindow oswindow, HBITMAP hbitmap)
//{
//
//   ASSERT(::IsWindow(oswindow));
//
//   ::CreateCaret(oswindow, hbitmap, 0, 0);
//
//}
//
//void window_create_solid_caret(oswindow oswindow, i32 nWidth, i32 nHeight)
//{
//
//   ASSERT(::IsWindow(oswindow));
//
//   ::CreateCaret(oswindow, (HBITMAP)nullptr, nWidth, nHeight);
//
//}
//
//void window_create_gray_caret(oswindow oswindow, i32 nWidth, i32 nHeight)
//{
//
//   ASSERT(::IsWindow(oswindow));
//
//   ::CreateCaret(oswindow, (HBITMAP)1, nWidth, nHeight);
//
//}
//

//CLASS_DECL_APEX string message_box_result_to_string(int iResult);
//
//
//CLASS_DECL_APEX ::e_status _os_message_box(oswindow oswindow, const char* pszMessage, const char* pszTitle, const ::e_message_box & emessagebox, ::future future)
//{
//
//   string strMessage(pszMessage);
//
//   strMessage.replace_ci("<br>", "\n");
//
//   string strTitle(pszTitle);
//
//   strTitle.replace_ci("<br>", "\n");
//
//   ::i32 iResult = ::MessageBoxW(oswindow, wstring(strMessage), wstring(strTitle), emessagebox);
//
//   string strResult = message_box_result_to_string(iResult);
//
//   future.receive_response(strResult);
//
//   return ::success;
//
//}
//

CLASS_DECL_ACME::e_status _os_message_box(oswindow oswindow, const char* pszMessage, const char* pszTitle, const ::e_message_box & emessagebox, const ::promise::process & process);


CLASS_DECL_APEX ::e_status apex_os_message_box(oswindow oswindow, const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox, const ::promise::process & process)
{

   if (System.is_dedicated_thread())
   {

      System.fork([=]()
         {

            _os_message_box(oswindow, pszMessage, pszTitle, emessagebox, process);

         });

      return ::success;

   }

   return _os_message_box(oswindow, pszMessage, pszTitle, emessagebox, process);

}


//
//
//void defer_term_ui()
//{
//
//
//}



