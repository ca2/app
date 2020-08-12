#include "framework.h"
#include "android.h"


void __trace_message(const char * lpszPrefix,::message::message * pmessage)
{
   //   ENSURE_ARG(AfxIsValidString(lpszPrefix));
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
      //      if (::GetClipboardFormatNameA(pbase->m_id, szBuf, _countof(szBuf)))
      //       lpszMsgName = szBuf;
   }
   else if(pbase->m_id >= WM_USER)
   {
      // User message
      sprintf(szBuf,"WM_USER+0x%04X", (unsigned int) (pbase->m_id.i64() - WM_USER));
      lpszMsgName = szBuf;
   }
   else
   {

      // a system windows message

      lpszMsgName = get_windows_message_name(pbase->m_id);

   }

   if(lpszMsgName != nullptr)
   {
#ifdef _WIN64
      //TRACE(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = %s (%p, %p)\n",
      // lpszPrefix, pbase->m_hwnd, lpszMsgName,
      //pbase->m_wparam, pbase->m_lparam);
#else
      //  ::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = %s (0x%08X, 0x%08X)\n",
      //         lpszPrefix, pbase->m_hwnd, lpszMsgName,
      //       pbase->m_wparam, pbase->m_lparam);
#endif
   }
   else
   {
#ifdef _WIN64
      //      ::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = 0x%04X (%p, %p)\n",
      //       lpszPrefix, pbase->m_hwnd, lpszMsgName,
      //     pbase->m_wparam, pbase->m_lparam);
#else
      //      ::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = 0x%04X (0x%08X, 0x%08X)\n",
      //       lpszPrefix, pbase->m_hwnd, lpszMsgName,
      //     pbase->m_wparam, pbase->m_lparam);
#endif
   }

   /*   if (pbase->m_id >= WM_DDE_FIRST && pbase->m_id <= WM_DDE_LAST)
   TraceDDE(lpszPrefix, pMsg);  */
}
