#include "framework.h"
//#include "dde.h"


/////////////////////////////////////////////////////////////////////////////
// Build data tables by including data file three times
//
//struct CLASS_DECL_ACME __MAP_MESSAGE
//{
//   ::u32    nMsg;
//   const char *  lpszMsg;
//};

#define DEFINE_MESSAGE(wm)  { wm, #wm }



/*
 static void TraceDDE(const char * lpszPrefix, const MESSAGE* pMsg)
 {
 ENSURE_ARG(pMsg != nullptr);
 if (pMsg->message == WM_DDE_EXECUTE)
 {
 uptr nDummy;
 HGLOBAL hCommands;
 if (!UnpackDDElParam(WM_DDE_EXECUTE, pMsg->lParam,
 &nDummy, (uptr*)&hCommands))
 {
 //         ::output_debug_string(::ca2::trace::category_AppMsg, 0, "Warning: Unable to unpack WM_DDE_EXECUTE lParam %08lX.\n",
 //          pMsg->lParam);
 return;
 }
 ASSERT(hCommands != nullptr);

 const char * lpszCommands = (const char *)::GlobalLock(hCommands);
 ENSURE_THROW(lpszCommands != nullptr, ::AfxThrowMemoryException() );
 //      ::output_debug_string(::ca2::trace::category_AppMsg, 0, "%s: Execute '%s'.\n", lpszPrefix, lpszCommands);
 ::GlobalUnlock(hCommands);
 }
 else if (pMsg->message == WM_DDE_ADVISE)
 {
 uptr nItem;
 ATOM aItem;
 HGLOBAL hAdvise;
 if (!UnpackDDElParam(WM_DDE_ADVISE, pMsg->lParam,
 (uptr*)&hAdvise, &nItem))
 {
 //         ::output_debug_string(::ca2::trace::category_AppMsg, 0, "Warning: Unable to unpack WM_DDE_ADVISE lParam %08lX.\n",
 //            pMsg->lParam);
 return;
 }
 aItem = (ATOM)nItem;
 ASSERT(aItem != nullptr);
 ASSERT(hAdvise != nullptr);

 DDEADVISE* lpAdvise = (DDEADVISE*)::GlobalLock(hAdvise);
 ENSURE_THROW(lpAdvise != nullptr, ::AfxThrowMemoryException() );
 char szItem[80];
 szItem[0] = '\0';

 if (aItem != 0)
 ::GlobalGetAtomName(aItem, szItem, _countof(szItem));

 char szFormat[80];
 szFormat[0] = '\0';
 if (((::u32)0xC000 <= (::u32)lpAdvise->cfFormat) &&
 ((::u32)lpAdvise->cfFormat <= (::u32)0xFFFF))
 {
 ::GetClipboardFormatName(lpAdvise->cfFormat,
 szFormat, _countof(szFormat));

 // User defined clipboard formats have a range of 0xC000->0xFFFF
 // System clipboard formats have other ranges, but no printable
 // format names.
 }

 AfxTrace(
 "%s: Advise item='%s', Format='%s', Ack=%d, Defer Update= %d\n",
 lpszPrefix, szItem, szFormat, lpAdvise->fAckReq,
 lpAdvise->fDeferUpd);
 ::GlobalUnlock(hAdvise);
 }
 }
 */
/////////////////////////////////////////////////////////////////////////////

//void __trace_message(const char * lpszPrefix, ::message::message * pmessage)
//{
//   //   ENSURE_ARG(AfxIsValidString(lpszPrefix));
//   ENSURE_ARG(pmessage != nullptr);
//   SCAST_PTR(::message::base, pbase, pmessage);
//
//   if (pbase->m_id == e_message_mouse_move || pbase->m_id == e_message_non_client_mouse_move ||
//       pbase->m_id == e_message_nchittest || pbase->m_id == WM_SETCURSOR ||
//       pbase->m_id == WM_CTLCOLORBTN ||
//       pbase->m_id == WM_CTLCOLORDLG ||
//       pbase->m_id == WM_CTLCOLOREDIT ||
//       pbase->m_id == WM_CTLCOLORLISTBOX ||
//       pbase->m_id == WM_CTLCOLORMSGBOX ||
//       pbase->m_id == WM_CTLCOLORSCROLLBAR ||
//       pbase->m_id == WM_CTLCOLORSTATIC ||
//       pbase->m_id == WM_ENTERIDLE || pbase->m_id == WM_CANCELMODE ||
//       pbase->m_id == 0x0118)    // WM_SYSTIMER (caret blink)
//   {
//      // don't report very frequently sent messages
//      return;
//   }
//
//   const char * lpszMsgName = nullptr;
//   char szBuf[80];
//
//   // find message name
//   if (pbase->m_id >= 0xC000)
//   {
//      // Window message registered with 'RegisterWindowMessage'
//      //  (actually a USER atom)
//      //      if (::GetClipboardFormatNameA(pbase->m_id, szBuf, _countof(szBuf)))
//      //       lpszMsgName = szBuf;
//   }
//   else if (pbase->m_id >= WM_USER)
//   {
//      // User message
//      sprintf(szBuf, "WM_USER+0x%04X", pbase->m_id - WM_USER);
//      lpszMsgName = szBuf;
//   }
//   else
//   {
//      // a system windows message
//      const __MAP_MESSAGE* pMapMsg = allMessages;
//      for (/*null*/ ; pMapMsg->lpszMsg != nullptr; pMapMsg++)
//      {
//         if (pMapMsg->nMsg == pbase->m_id)
//         {
//            lpszMsgName = pMapMsg->lpszMsg;
//            break;
//         }
//      }
//   }
//
//   if (lpszMsgName != nullptr)
//   {
//#ifdef _WIN64
//      //TRACE(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = %s (%p, %p)\n",
//      // lpszPrefix, pbase->m_hwnd, lpszMsgName,
//      //pbase->m_wparam, pbase->m_lparam);
//#else
//      //  ::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = %s (0x%08X, 0x%08X)\n",
//      //         lpszPrefix, pbase->m_hwnd, lpszMsgName,
//      //       pbase->m_wparam, pbase->m_lparam);
//#endif
//   }
//   else
//   {
//#ifdef _WIN64
//      //      ::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = 0x%04X (%p, %p)\n",
//      //       lpszPrefix, pbase->m_hwnd, lpszMsgName,
//      //     pbase->m_wparam, pbase->m_lparam);
//#else
//      //      ::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = 0x%04X (0x%08X, 0x%08X)\n",
//      //       lpszPrefix, pbase->m_hwnd, lpszMsgName,
//      //     pbase->m_wparam, pbase->m_lparam);
//#endif
//   }
//
//   /*   if (pbase->m_id >= WM_DDE_FIRST && pbase->m_id <= WM_DDE_LAST)
//    TraceDDE(lpszPrefix, pMsg);  */
//}
//
//
//
//void __trace_message(const char * lpszPrefix, LPMESSAGE lpmsg)
//{
//   //ENSURE_ARG(AfxIsValidString(lpszPrefix));
//   ENSURE_ARG(lpmsg != nullptr);
//
//   if (lpmsg->message == e_message_mouse_move || lpmsg->message == e_message_non_client_mouse_move ||
//       lpmsg->message == e_message_nchittest || lpmsg->message == WM_SETCURSOR ||
//       lpmsg->message == WM_CTLCOLORBTN ||
//       lpmsg->message == WM_CTLCOLORDLG ||
//       lpmsg->message == WM_CTLCOLOREDIT ||
//       lpmsg->message == WM_CTLCOLORLISTBOX ||
//       lpmsg->message == WM_CTLCOLORMSGBOX ||
//       lpmsg->message == WM_CTLCOLORSCROLLBAR ||
//       lpmsg->message == WM_CTLCOLORSTATIC ||
//       lpmsg->message == WM_ENTERIDLE || lpmsg->message == WM_CANCELMODE ||
//       lpmsg->message == 0x0118)    // WM_SYSTIMER (caret blink)
//   {
//      // don't report very frequently sent messages
//      return;
//   }
//
//   const char * lpszMsgName = nullptr;
//   char szBuf[80];
//
//   // find message name
//   if (lpmsg->message >= 0xC000)
//   {
//      // Window message registered with 'RegisterWindowMessage'
//      //  (actually a USER atom)
//      //      if (::GetClipboardFormatNameA(lpmsg->message, szBuf, _countof(szBuf)))
//      //       lpszMsgName = szBuf;
//   }
//   else if (lpmsg->message >= WM_USER)
//   {
//      // User message
//      sprintf(szBuf, "WM_USER+0x%04X", lpmsg->message - WM_USER);
//      lpszMsgName = szBuf;
//   }
//   else
//   {
//      // a system windows message
//      const __MAP_MESSAGE* pMapMsg = allMessages;
//      for (/*null*/ ; pMapMsg->lpszMsg != nullptr; pMapMsg++)
//      {
//         if (pMapMsg->nMsg == lpmsg->message)
//         {
//            lpszMsgName = pMapMsg->lpszMsg;
//            break;
//         }
//      }
//   }
//
//   if (lpszMsgName != nullptr)
//   {
//#ifdef WIN64
//      //      TRACE(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = %hs (%p, %p)\n",
//      //       lpszPrefix, pMsg->hwnd, lpszMsgName,
//      //     pMsg->wParam, pMsg->lParam);
//#else
//      //      ::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = %hs (0x%08X, 0x%08X)\n",
//      //       lpszPrefix, lpmsg->hwnd, lpszMsgName,
//      //     lpmsg->wParam, lpmsg->lParam);
//#endif
//   }
//   else
//   {
//#ifdef WIN64
//      //::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = 0x%04X (%p, %p)\n",
//      // lpszPrefix, pMsg->hwnd, lpszMsgName,
//      //pMsg->wParam, pMsg->lParam);
//#else
//      //::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = 0x%04X (0x%08X, 0x%08X)\n",
//      // lpszPrefix, lpmsg->hwnd, lpszMsgName,
//      //lpmsg->wParam, lpmsg->lParam);
//#endif
//   }
//
//   /*   if (lpmsg->message >= WM_DDE_FIRST && lpmsg->message <= WM_DDE_LAST)
//    TraceDDE(lpszPrefix, pMsg);*/
//}


