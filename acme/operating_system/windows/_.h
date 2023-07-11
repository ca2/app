#pragma once


#include "_c.h"


#include "acme/_operating_system.h"


//#include <Tlhelp32.h>


inline HWND __hwnd(oswindow oswindow)
{

   return (HWND)oswindow;

}


inline oswindow __oswindow(HWND hwnd)
{

   return (oswindow)hwnd;

}


CLASS_DECL_ACME void attach_thread_input_to_main_thread(bool bAttach);


CLASS_DECL_ACME bool process_modules(string_array & stra, u32 processID);


CLASS_DECL_ACME bool load_modules_diff(string_array & straOld, string_array & straNew, const ::scoped_string & scopedstrExceptDir);


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

   message.oswindow = (oswindow)(msg.hwnd);
   message.m_atom = (enum_message)msg.message;
   message.wParam = msg.wParam;
   message.lParam = msg.lParam;
   message.pt.x() = msg.pt.x;
   message.pt.y() = msg.pt.y;
   message.time = msg.time;


}


inline void copy(MSG & msg, const MESSAGE & message)
{

   msg.hwnd = (HWND)(message.oswindow);
   msg.message = (UINT)message.m_atom.as_i64();
   msg.wParam = message.wParam;
   msg.lParam = message.lParam;
   msg.pt.x = message.pt.x();
   msg.pt.y = message.pt.y();
   msg.time = (DWORD)message.time;


}


namespace windows
{

 
   CLASS_DECL_ACME ::string get_window_text_timeout(HWND hwnd, const class time & timeSendMessageMax = 1_s);
   CLASS_DECL_ACME HWND child_at(HWND hwnd, iptr i);


} // namespace windows






