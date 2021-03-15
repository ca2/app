#include "framework.h"
#include "acme/operating_system.h"


#if !BROAD_PRECOMPILED_HEADER
#include "acme/user/_user.h"
#endif
#include "windowing.h"
//#include "top_level_enum.h"


//#define ___TEMP_CLASS_NAME_SIZE 4096
//
//
//CLASS_DECL_ACME void defer_dock_application(int_bool bDock)
//{
//
//   UNREFERENCED_PARAMETER(bDock);
//
//}
//

//
//CLASS_DECL_ACME int_bool os_init_windowing()
//{
//
//   return true;
//
//}
//
//
//CLASS_DECL_ACME void os_term_windowing()
//{
//
//}


//::user::interaction * get_system_window_interaction(::os_system_window * psystemwindow)
//{
//
//   return nullptr;
//
//}

//
//CLASS_DECL_ACME i64 oswindow_id(HWND hwnd)
//{
//
//   return (i64)hwnd;
//
//}
//

CLASS_DECL_ACME int_bool is_window(HWND hwnd)
{

   return ::IsWindow(hwnd);

}

//
//CLASS_DECL_ACME bool get_gui_thread_info(PGUITHREADINFO pinfo)
//{
//
//   HWND hwndForeground = ::GetForegroundWindow();
//
//   if (hwndForeground == nullptr)
//   {
//
//      return false;
//
//   }
//
//   ::u32 dwThread = GetWindowThreadProcessId(hwndForeground, nullptr);
//
//   __zero(pinfo);
//
//   pinfo->cbSize = sizeof(GUITHREADINFO);
//
//   if (!::GetGUIThreadInfo(dwThread, pinfo))
//   {
//
//      ::u32 dwLastError = ::GetLastError();
//
//      return false;
//
//   }
//
//   return true;
//
//}
//
//
//CLASS_DECL_ACME hwnd get_focus()
//{
//
//   GUITHREADINFO info;
//
//   if (!get_gui_thread_info(&info))
//   {
//
//      return nullptr;
//
//   }
//
//   return info.hwndFocus;
//
//}
//
//
//CLASS_DECL_ACME hwnd set_focus(HWND hwnd)
//{
//
//   return ::SetFocus(hwnd);
//
//}
//
//
//CLASS_DECL_ACME hwnd get_active_window()
//{
//
//   //attach_thread_input_to_main_thread(true);
//
//   auto hwnd = ::GetActiveWindow();
//
//   //attach_thread_input_to_main_thread(false);
//
//   return hwnd;
//
//}
//
//
//CLASS_DECL_ACME hwnd set_active_window(HWND hwnd)
//{
//
//   return ::SetActiveWindow(hwnd);
//
//}
//
//
//CLASS_DECL_ACME hwnd get_capture()
//{
//
//   return ::GetCapture();
//
//}
//
//
//CLASS_DECL_ACME hwnd set_capture(HWND hwnd)
//{
//
//   return ::SetCapture(hwnd);
//
//}
//
//
//CLASS_DECL_ACME int_bool release_capture()
//{
//
//   return ::ReleaseCapture();
//
//}
//
//
//CLASS_DECL_ACME int_bool destroy_window(HWND hwnd)
//{
//
//   return ::DestroyWindow(hwnd);
//
//}
//
//
//CLASS_DECL_ACME hwnd get_desktop_window()
//{
//
//   return ::GetDesktopWindow();
//
//}
//
//
//CLASS_DECL_ACME hwnd get_window(HWND hwnd, int iWindow)
//{
//
//   return ::GetWindow(hwnd, iWindow);
//
//}
//
//
//
//// void update_session_cursor(class user::interaction_impl * puiimpl)
//// {
//
////    __pointer(::windows::interaction_impl) pimpl = puiimpl;
//
////    if (pimpl.is_set())
////    {
//
////       return;
//
////    }
//
////    Sess(puiimpl->get_application()).get_cursor_position(puiimpl->m_pointCursor);
//
//// }
//
//CLASS_DECL_ACME int_bool show_window(HWND hwnd, int iShowCmd)
//{
//
//   return ::ShowWindow(hwnd, iShowCmd);
//
//}
//
//
/////// from top to bottom
////CLASS_DECL_ACME __pointer(::user::oswindow_array) get_top_level_windows(bool bDesktop, bool bVisible)
////{
////
////   /// from top to bottom
////   top_level_enum toplevelenum(bDesktop, bVisible);
////
////   return toplevelenum.m_poswindowa;
////
////}
////
////
////top_level_enum::top_level_enum(bool bDesktop, bool bVisible) :
////   m_bVisible(bVisible)
////{
////
////   __construct_new(m_poswindowa);
////
////   if (bDesktop)
////   {
////
////      ::EnumDesktopWindows(nullptr, &::top_level_enum::EnumWindowsProc, (LPARAM)this);
////
////   }
////   else
////   {
////
////      ::EnumWindows(&::top_level_enum::EnumWindowsProc, (LPARAM)this);
////
////   }
////
////
////}
////
////
////top_level_enum::~top_level_enum()
////{
////
////
////}
////
////
////BOOL CALLBACK top_level_enum::EnumWindowsProc(HWND hwnd, LPARAM lParam)
////{
////
////   top_level_enum * ptoplevelenum = (top_level_enum *) lParam;
////
////   if (ptoplevelenum->m_bVisible && !IsWindowVisible(hwnd))
////   {
////
////      return true;
////
////   }
////
////   ptoplevelenum->m_poswindowa->add(hwnd);
////
////   return true;
////
////}
////
//
////int_bool point_is_window_origin(POINT_I32 ptHitTest, hwnd oswindowExclude, int iMargin)
////{
////
////   auto poswindowa = get_top_level_windows();
////
////   if (poswindowa->is_empty())
////   {
////
////      return false;
////
////   }
////
////   ::rectangle_i32 rectWindow;
////
////   for(auto & hwnd : *poswindowa)
////   {
////
////      if(hwnd != oswindowExclude)
////      {
////
////         if (!IsWindowVisible(hwnd))
////         {
////
////            continue;
////
////         }
////
////         if (::GetWindowRect(hwnd, rectWindow))
////         {
////
////            ::rectangle_i32 rectHitTest;
////            
////            rectHitTest.set(rectWindow.origin(), ::size());
////
////            rectHitTest.inflate(iMargin + 1);
////
////            if (rectHitTest.contains(ptHitTest))
////            {
////
////               return true;
////
////            }
////
////            //return true;
////
////         }
////
////      }
////
////   }
////
////   return false;
////
////}
////
//
////
////
////void window_create_caret(HWND hwnd, HBITMAP hbitmap)
////{
////
////   ASSERT(::IsWindow(hwnd));
////
////   ::CreateCaret(hwnd, hbitmap, 0, 0);
////
////}
////
////void window_create_solid_caret(HWND hwnd, i32 nWidth, i32 nHeight)
////{
////
////   ASSERT(::IsWindow(hwnd));
////
////   ::CreateCaret(hwnd, (HBITMAP)nullptr, nWidth, nHeight);
////
////}
////
////void window_create_gray_caret(HWND hwnd, i32 nWidth, i32 nHeight)
////{
////
////   ASSERT(::IsWindow(hwnd));
////
////   ::CreateCaret(hwnd, (HBITMAP)1, nWidth, nHeight);
////
////}
//
//
CLASS_DECL_ACME string message_box_result_to_string(enum_dialog_result edialogresult);
//
//


//CLASS_DECL_ACME ::e_status _os_message_box(::windowing::window * pwindow, const char* pszMessage, const char* pszTitle, const ::e_message_box & emessagebox, const ::future & process)
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
//   int iResult = ::MessageBoxW(__hwnd(oswindow), wstring(strMessage), wstring(strTitle), emessagebox);
//
//   enum_dialog_result edialogresult = (enum_dialog_result) iResult;
//
//   string strResult = message_box_result_to_string(edialogresult);
//
//   process(strResult);
//
//   return ::success;
//
//}
////
////
//CLASS_DECL_ACME ::e_status os_message_box(HWND hwnd, const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox, const ::future & process)
//{
//
//   //if (get_system()->is_dedicated_thread())
//   //{
//
//   //   get_system()->fork([=]()
//   //      {
//
//   //         _os_message_box(hwnd, pszMessage, pszTitle, emessagebox, callback);
//
//   //      });
//
//   //   return ::success;
//
//   //}
//
//   return _os_message_box(hwnd, pszMessage, pszTitle, emessagebox, process);
//
//}
//
//
//
//
//void defer_term_ui()
//{
//
//
//}
//
//
//


//CLASS_DECL_ACME bool windows_register_class(WNDCLASSEXW* puserinteractionclass)
//{
//
//   WNDCLASSEXW wndcls;
//
//   if (GetClassInfoExW(puserinteractionclass->hInstance, puserinteractionclass->lpszClassName, &wndcls))
//
//   {
//
//      return true;
//
//   }
//
//   puserinteractionclass->cbSize = sizeof(WNDCLASSEXW);
//
//   if (!::RegisterClassExW(puserinteractionclass))
//   {
//
//      ::u32 dw = GetLastError();
//
//      return false;
//
//   }
//
//   bool bRet = true;
//
//   return bRet;
//
//}





LRESULT CALLBACK WndProc(HWND hWnd, ::u32 message, WPARAM wParam, LPARAM lParam);
//
//WNDPROC g_pwindowprocedure = &WndProc;
//
//CLASS_DECL_ACME void os_set_window_procedure(WNDPROC puserinteractionproc)
//{
//
//   g_pwindowprocedure = puserinteractionproc;
//
//}
//
//
//CLASS_DECL_ACME WNDPROC get_window_procedure()
//{
//
//   return g_pwindowprocedure;
//
//}

//CLASS_DECL_WINDOWING_WIN32 WNDPROC windows_user_interaction_impl_get_window_procedure();
//
//
//CLASS_DECL_ACME bool windows_register_class(HINSTANCE hinstance)
//{
//
//   WNDCLASSEXW wcex = {};
//
//   wcex.cbSize = sizeof(WNDCLASSEXW);
//   wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
//   wcex.lpfnWndProc = windows_user_interaction_impl_get_window_procedure();
//   wcex.cbClsExtra = 0;
//   wcex.cbWndExtra = 40;
//   wcex.hInstance = hinstance;
//   wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
//   wcex.lpszClassName = L"windows_interaction_impl";
//
//   if (!RegisterClassExW(&wcex))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}


CLASS_DECL_ACME iptr get_window_long_ptr(HWND hwnd, int iIndex)
{

   return ::GetWindowLongPtrW(hwnd, iIndex);

}


CLASS_DECL_ACME iptr set_window_long_ptr(HWND hwnd, int iIndex, iptr i)
{

   return ::SetWindowLongPtrW(hwnd, iIndex, i);

}


namespace str
{


   string get_window_text_timeout(oswindow oswindow, millis tickTimeout)
   {

      string str;

      if (oswindow != nullptr)
      {

   #ifdef WINDOWS_DESKTOP

         DWORD_PTR lresult = 0;

         auto tickStart = ::millis::now();

         tickTimeout = maximum(tickTimeout, 10);

         if (!::SendMessageTimeoutW(__hwnd(oswindow), WM_GETTEXTLENGTH, 0, 0, SMTO_ABORTIFHUNG, __os(tickTimeout), &lresult))
            return "";

         tickTimeout -= tickStart.elapsed();

         wstring wstr;

         tickTimeout = minimum(tickTimeout, 10);

         if (!::SendMessageTimeoutW(__hwnd(oswindow), WM_GETTEXT, (LPARAM)wstr.get_string_buffer(lresult + 1), lresult + 1, SMTO_ABORTIFHUNG, __os(tickTimeout), &lresult))
            return "";

         str = wstr;

         //i32 nLen = ::GetWindowTextLength(oswindow);

         //::GetWindowText(oswindow, str.get_string_buffer(nLen), nLen+1);

         //str.ReleaseBuffer();

   #else

         __throw(todo);

   #endif

      }

      return str;

   }


} // namespace str