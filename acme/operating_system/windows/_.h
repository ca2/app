#pragma once


#include "_c.h"

#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#include <windowsx.h>

//#include <Tlhelp32.h>


inline HWND as_hwnd(oswindow oswindow)
{

   return (HWND)oswindow;

}


inline oswindow as_oswindow(HWND hwnd)
{

   return (oswindow)hwnd;

}


CLASS_DECL_ACME void attach_thread_input_to_main_thread(bool bAttach);


CLASS_DECL_ACME bool process_modules(string_array & stra, unsigned int processID);


CLASS_DECL_ACME bool load_modules_diff(string_array & straOld, string_array & straNew, const ::scoped_string & scopedstrExceptDir);


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


inline void copy(MESSAGE & message, const MSG & msg)
{

   message.m_oswindow = (oswindow)(msg.hwnd);
   message.m_emessage = (enum_message)msg.message;
   message.m_wparam = msg.wParam;
   message.m_lparam = msg.lParam;
   message.m_point.x() = msg.pt.x;
   message.m_point.y() = msg.pt.y;
   message.m_time = msg.time;


}


inline void copy(MSG & msg, const MESSAGE & message)
{

   msg.hwnd = (HWND)(message.m_oswindow);
   msg.message = (UINT)message.m_emessage;
   msg.wParam = message.m_wparam;
   msg.lParam = message.m_lparam;
   msg.pt.x = message.m_point.x();
   msg.pt.y = message.m_point.y();
   msg.time = (DWORD)message.m_time;

}


namespace windows
{

 
   CLASS_DECL_ACME ::string get_window_text_timeout(HWND hwnd, const class time & timeSendMessageMax = 1_s);
   CLASS_DECL_ACME HWND child_at(HWND hwnd, iptr i);


} // namespace windows


inline int width(RECT & r) { return r.right - r.left; }

inline int height(RECT & r) { return r.bottom - r.top; }


inline ::int_point lparam_as_point(LPARAM lparam)
{

   return ::int_point(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));

}
