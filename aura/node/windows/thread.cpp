#include "framework.h"


void CLASS_DECL_AURA __init_thread()
{

   //if(t_hHookOldMsgFilter == nullptr)
   //{

   //   t_hHookOldMsgFilter = ::SetWindowsHookEx(WH_MSGFILTER,__message_filter_hook,nullptr,::GetCurrentThreadId());

   //}

}


void CLASS_DECL_AURA __term_thread()
{


}


//namespace windows
//{
//

//thread::thread(::layered * pobjectContext):
//   ::object(pobject),
//   ::thread_impl(pobject)
//{

//      m_evFinish.SetEvent();
//      m_pThreadParams = nullptr;
//      m_pfnThreadProc = nullptr;

//      CommonConstruct();

//}

//void thread::construct(__THREADPROC pfnThreadProc,LPVOID pParam)
//{
//   m_evFinish.SetEvent();
//   m_pfnThreadProc = pfnThreadProc;
//   m_pThreadParams = pParam;

//   CommonConstruct();
//}


__STATIC bool CLASS_DECL_AURA IsHelpKey(LPMSG pMsg)

// return TRUE only for non-repeat F1 keydowns.
{
   return pMsg->message == WM_KEYDOWN &&

          pMsg->wParam == VK_F1 &&

          !(HIWORD(pMsg->lParam) & KF_REPEAT) &&

          GetKeyState(VK_SHIFT) >= 0 &&
          GetKeyState(VK_CONTROL) >= 0 &&
          GetKeyState(VK_MENU) >= 0;
}

__STATIC inline bool IsEnterKey(LPMSG pMsg)

{
   return pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN;

}

__STATIC inline bool IsButtonUp(LPMSG pMsg)

{
   return pMsg->message == WM_LBUTTONUP;

}



void __term_threading()
{

   //if(t_hHookOldMsgFilter != nullptr)
   //{
   //   ::UnhookWindowsHookEx(t_hHookOldMsgFilter);
   //   t_hHookOldMsgFilter = nullptr;
   //}

}



bool __node_init_thread(::thread * pthread)
{

   try
   {

      pthread->::exception::translator::attach();

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

         pthread->::exception::translator::detach();

      }

      bOk1 = true;

   }
   catch(...)
   {

   }

   return bOk1;

}







