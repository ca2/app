#include "framework.h"
//#include "metrowin.h"

/////////////////////////////////////////////////////////////////////////////
void __trace_message(const char * lpszPrefix,::message::message * pmessage)
{
   ENSURE_ARG(__is_valid_string(lpszPrefix));
   ENSURE_ARG(pmessage != nullptr);
   SCAST_PTR(::message::base,pbase,pmessage);

   if(pbase->m_id == WM_MOUSEMOVE || pbase->m_id == WM_NCMOUSEMOVE ||
         pbase->m_id == WM_NCHITTEST || pbase->m_id == WM_SETCURSOR ||
         pbase->m_id == WM_CTLCOLORBTN ||
         pbase->m_id == WM_CTLCOLORDLG ||
         pbase->m_id == WM_CTLCOLOREDIT ||
         pbase->m_id == WM_CTLCOLORLISTBOX ||
         pbase->m_id == WM_CTLCOLORMSGBOX ||
         pbase->m_id == WM_CTLCOLORSCROLLBAR ||
         pbase->m_id == WM_CTLCOLORSTATIC ||
         pbase->m_id == WM_ENTERIDLE || pbase->m_id == WM_CANCELMODE ||
         pbase->m_id == 0x0118)    // WM_SYSTIMER (caret blink)
   {
      // don't report very frequently sent messages
      return;
   }

   const char * lpszMsgName = nullptr;
   char szBuf[80];

   // find message name
   if(pbase->m_id >= 0xC000)
   {
      // Window message registered with 'RegisterWindowMessage'
      //  (actually a USER atom)
      /*
      if (::GetClipboardFormatNameA(pbase->m_id, szBuf, _countof(szBuf)))
      lpszMsgName = szBuf;*/
   }
   else if(pbase->m_id >= WM_USER)
   {
      // User message
      sprintf_s(szBuf,_countof(szBuf),"WM_USER+0x%04X", (UINT) (pbase->m_id.i64() - WM_USER));
      lpszMsgName = szBuf;
   }
   else
   {
      lpszMsgName = get_windows_message_name((UINT) pbase->m_id.i64());
   }

   if(lpszMsgName != nullptr)
   {
#ifdef _WIN64
      //TRACE(::aura::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = %s (%p, %p)\n",
      // lpszPrefix, pbase->m_hwnd, lpszMsgName,
      //pbase->m_wparam, pbase->m_lparam);
#else
      //  ::output_debug_string(::aura::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = %s (0x%08X, 0x%08X)\n",
      //         lpszPrefix, pbase->m_hwnd, lpszMsgName,
      //       pbase->m_wparam, pbase->m_lparam);
#endif
   }
   else
   {
#ifdef _WIN64
      //      ::output_debug_string(::aura::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = 0x%04X (%p, %p)\n",
      //       lpszPrefix, pbase->m_hwnd, lpszMsgName,
      //     pbase->m_wparam, pbase->m_lparam);
#else
      //      ::output_debug_string(::aura::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = 0x%04X (0x%08X, 0x%08X)\n",
      //       lpszPrefix, pbase->m_hwnd, lpszMsgName,
      //     pbase->m_wparam, pbase->m_lparam);
#endif
   }

   /*if (pbase->m_id >= WM_DDE_FIRST && pbase->m_id <= WM_DDE_LAST)
   TraceDDE(lpszPrefix, pMsg);*/
}


void __trace_message(const char * lpszPrefix,LPMESSAGE lpmsg)
{
   ENSURE_ARG(__is_valid_string(lpszPrefix));
   ENSURE_ARG(lpmsg != nullptr);

   if(lpmsg->message == WM_MOUSEMOVE || lpmsg->message == WM_NCMOUSEMOVE ||
         lpmsg->message == WM_NCHITTEST || lpmsg->message == WM_SETCURSOR ||
         lpmsg->message == WM_CTLCOLORBTN ||
         lpmsg->message == WM_CTLCOLORDLG ||
         lpmsg->message == WM_CTLCOLOREDIT ||
         lpmsg->message == WM_CTLCOLORLISTBOX ||
         lpmsg->message == WM_CTLCOLORMSGBOX ||
         lpmsg->message == WM_CTLCOLORSCROLLBAR ||
         lpmsg->message == WM_CTLCOLORSTATIC ||
         lpmsg->message == WM_ENTERIDLE || lpmsg->message == WM_CANCELMODE ||
         lpmsg->message == 0x0118)    // WM_SYSTIMER (caret blink)
   {
      // don't report very frequently sent messages
      return;
   }

   const char * lpszMsgName = nullptr;
   char szBuf[80];

   // find message name
   if(lpmsg->message >= 0xC000)
   {
      // Window message registered with 'RegisterWindowMessage'
      //  (actually a USER atom)
      //      if (::GetClipboardFormatNameA(lpmsg->message, szBuf, _countof(szBuf)))
      //       lpszMsgName = szBuf;
   }
   else if(lpmsg->message >= WM_USER)
   {
      // User message
      sprintf_s(szBuf,_countof(szBuf),"WM_USER+0x%04X",lpmsg->message - WM_USER);
      lpszMsgName = szBuf;
   }
   else
   {
      lpszMsgName = get_windows_message_name(lpmsg->message);
   }

   if(lpszMsgName != nullptr)
   {
#ifdef WIN64
      //      TRACE(::aura::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = %hs (%p, %p)\n",
      //       lpszPrefix, pMsg->hwnd, lpszMsgName,
      //     pMsg->wParam, pMsg->lParam);
#else
      //      ::output_debug_string(::aura::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = %hs (0x%08X, 0x%08X)\n",
      //       lpszPrefix, lpmsg->hwnd, lpszMsgName,
      //     lpmsg->wParam, lpmsg->lParam);
#endif
   }
   else
   {
#ifdef WIN64
      //::output_debug_string(::aura::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = 0x%04X (%p, %p)\n",
      // lpszPrefix, pMsg->hwnd, lpszMsgName,
      //pMsg->wParam, pMsg->lParam);
#else
      //::output_debug_string(::aura::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = 0x%04X (0x%08X, 0x%08X)\n",
      // lpszPrefix, lpmsg->hwnd, lpszMsgName,
      //lpmsg->wParam, lpmsg->lParam);
#endif
   }

   /*if (lpmsg->message >= WM_DDE_FIRST && lpmsg->message <= WM_DDE_LAST)
   TraceDDE(lpszPrefix, pMsg);*/
}
