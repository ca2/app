#include "framework.h"
//#include "universal_windows.h"
//#include <process.h>    // for _beginthreadex and _endthreadex
//#include <ddeml.h>  // for MSGF_DDEMGR

namespace universal_windows
{
   class thread;
} // namespace universal_windows

bool CLASS_DECL_APEX __internal_pump_message();
LRESULT CLASS_DECL_APEX __internal_process_wnd_proc_exception(::exception*, const MSG* pMsg);
bool __internal_pre_translate_message(MSG* pMsg);
bool __internal_is_idle_message(MSG* pMsg);
//__STATIC void CLASS_DECL_APEX __pre_init_dialog(__pointer(::user::interaction) pWnd, RECTANGLE_I32 * lpRectOld, u32* pdwStyleOld);
//__STATIC void CLASS_DECL_APEX __post_init_dialog(__pointer(::user::interaction) pWnd, const RECTANGLE_I32& rectangleOld, u32 dwStyleOld);


//__declspec(thread) HHOOK t_hHookOldMsgFilter = nullptr;
//
//
//LRESULT CALLBACK __message_filter_hook(i32 code,WPARAM wParam,LPARAM lParam);


void CLASS_DECL_APEX __init_thread()
{

   //if(t_hHookOldMsgFilter == nullptr)
   //{

   //   t_hHookOldMsgFilter = ::SetWindowsHookEx(WH_MSGFILTER,__message_filter_hook,nullptr,::GetCurrentThreadId());

   //}

}


void CLASS_DECL_APEX __term_thread()
{


}


bool __node_init_thread(::thread * pthread)
{

   try
   {

      pthread->::exception_translator::attach();

   }
   catch(...)
   {

      return false;

   }

   return true;

}



bool __node_term_thread(::thread * pthread)
{

   bool bOk1 = false;

   try
   {

      if(pthread != nullptr)
      {

         pthread->::exception_translator::detach();

      }

      bOk1 = true;

   }
   catch(...)
   {

   }

   return bOk1;

}
