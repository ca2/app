#pragma once


#include "_c.h"
#include "acme/parallelization/types.h"


#include "acme/operating_system/window.h"


// #undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
// #include "acme/_operating_system.h"
// #include <windowsx.h>

//#include <Tlhelp32.h>


namespace windows
{


   CLASS_DECL_ACME int message_box(
      const ::operating_system::window & operatingsystemwindow,
      const ::scoped_string & scopedstrMessage,
      const ::scoped_string & scopedstrCaption,
      unsigned int uType);


} // namespace windows


// inline HWND as_hwnd(::acme::windowing::window * pacmewindowingwindow)
// {
//
//    return (HWND)oswindow;
//
// }
//
//
// inline oswindow as_oswindow(HWND hwnd)
// {
//
//    return (oswindow)hwnd;
//
// }


CLASS_DECL_ACME void attach_thread_input_to_main_thread(bool bAttach);


CLASS_DECL_ACME bool process_modules(string_array_base & stra, const ::process_identifier & processidentifier);


CLASS_DECL_ACME bool load_modules_diff(string_array_base & straOld, string_array_base & straNew, const ::scoped_string & scopedstrExceptDir);


//CLASS_DECL_ACME bool check_msys2_at_c_msys64(::particle* pparticle);


//namespace windows
//{
//
//
//   CLASS_DECL_ACME bool for_each_process_module(DWORD dwProcess, ::function < bool(const MODULEENTRY32 & moduleentry32) > & function);
//
//
//   CLASS_DECL_ACME bool for_each_process_identifier(::function < bool(::process_identifier processidentifier) > & function);
//
//
//} // namespace windows


#include "acme/operating_system/message.h"


// CLASS_DECL_ACME ::operating_system::window as_operating_system_window(HWND hwnd);
// CLASS_DECL_ACME HWND as_HWND(const ::operating_system::window & operatingsystemwindow);


/*
 * GetWindow() Constants
 */
#define WIN32_GW_HWNDFIRST        0
#define WIN32_GW_HWNDLAST         1
#define WIN32_GW_HWNDNEXT         2
#define WIN32_GW_HWNDPREV         3
#define WIN32_GW_OWNER            4
#define WIN32_GW_CHILD            5
#if(WINVER <= 0x0400)
#define WIN32_GW_MAX              5
#else
#define WIN32_GW_ENABLEDPOPUP     6
#define WIN32_GW_MAX              6
#endif


namespace windows
{

   CLASS_DECL_ACME ::string get_window_text_timeout(const ::operating_system::window & operatingsystemwindow, const class time & timeSendMessageMax = 1_s);
   
   CLASS_DECL_ACME const ::operating_system::window & child_at(const ::operating_system::window & operatingsystemwindow, iptr i);

   CLASS_DECL_ACME hinstance hinstance_from_function(void *pFunc);

   CLASS_DECL_ACME bool get_window_rect(const ::operating_system::window & operatingsystemwindow, ::int_rectangle & rectangle);

   CLASS_DECL_ACME ::int_rectangle get_window_rect(const ::operating_system::window & operatingsystemwindow);

   CLASS_DECL_ACME ::operating_system::window get_window(const ::operating_system::window & operatingsystemwindowCommand, int iGetWindowCommand);

   CLASS_DECL_ACME ::iptr get_window_long(const ::operating_system::window & operatingsystemwindow, int iGetWindowLong);

   CLASS_DECL_ACME ::itask get_window_thread_id(const ::operating_system::window & operatingsystemwindow);

   CLASS_DECL_ACME ::itask get_window_thread_process_id(const ::operating_system::window & operatingsystemwindow, ::process_identifier & processidentifier);

   CLASS_DECL_ACME ::process_identifier get_window_process_id(const ::operating_system::window & operatingsystemwindow);

   CLASS_DECL_ACME ::operating_system::window get_foreground_window();

   CLASS_DECL_ACME ::comparable_array_base<::operating_system::window> findWindowsByClass(const ::string_array_base & straClassNames);

   // Find first of windows that name contain the string.
   // It is not case sensitive.
   CLASS_DECL_ACME ::operating_system::window findFirstWindowByName(const ::scoped_string & scopedstrWindowName);


} // namespace windows



