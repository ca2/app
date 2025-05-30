#include "framework.h"
//#include "dde.h"


/////////////////////////////////////////////////////////////////////////////
// Build data tables by including data file three times
//
//struct CLASS_DECL_APEX __MAP_MESSAGE
//{
//   unsigned int    nMsg;
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
 //         ::information(::ca2::trace::category_AppMsg, 0, "Warning: Unable to unpack WM_DDE_EXECUTE lParam %08lX.\n",
 //          pMsg->lParam);
 return;
 }
 ASSERT(hCommands != nullptr);

 const char * lpszCommands = (const char *)::GlobalLock(hCommands);
 ENSURE_THROW(lpszCommands != nullptr, ::windows_definition::ThrowMemoryException() );
 //      ::information(::ca2::trace::category_AppMsg, 0, "%s: Execute '%s'.\n", lpszPrefix, lpszCommands);
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
 //         ::information(::ca2::trace::category_AppMsg, 0, "Warning: Unable to unpack WM_DDE_ADVISE lParam %08lX.\n",
 //            pMsg->lParam);
 return;
 }
 aItem = (ATOM)nItem;
 ASSERT(aItem != nullptr);
 ASSERT(hAdvise != nullptr);

 DDEADVISE* lpAdvise = (DDEADVISE*)::GlobalLock(hAdvise);
 ENSURE_THROW(lpAdvise != nullptr, ::windows_definition::ThrowMemoryException() );
 char szItem[80];
 szItem[0] = '\0';

 if (aItem != 0)
 ::GlobalGetAtomName(aItem, szItem, _countof(szItem));

 char szFormat[80];
 szFormat[0] = '\0';
 if (((unsigned int)0xC000 <= (unsigned int)lpAdvise->cfFormat) &&
 ((unsigned int)lpAdvise->cfFormat <= (unsigned int)0xFFFF))
 {
 ::GetClipboardFormatName(lpAdvise->cfFormat,
 szFormat, _countof(szFormat));

 // User defined clipboard formats have a range of 0xC000->0xFFFF
 // ::apexacmesystem() clipboard formats have other ranges, but no printable
 // format names.
 }

 ::windows_definition::Trace(
 "%s: Advise item='%s', Format='%s', Ack=%d, Defer Update= %d\n",
 lpszPrefix, szItem, szFormat, lpAdvise->fAckReq,
 lpAdvise->fDeferUpd);
 ::GlobalUnlock(hAdvise);
 }
 }
 */
/////////////////////////////////////////////////////////////////////////////
//
//void __trace_message(const char * lpszPrefix, ::message::message * pmessage)
//{
//   //   ENSURE_ARG(::windows_definition::IsValidString(lpszPrefix));
//   ENSURE_ARG(pmessage != nullptr);
//   ::pointer<::user::message>pusermessage(pmessage);
//
//   if (pusermessage->m_emessage == e_message_mouse_move || pusermessage->m_emessage == e_message_non_client_mouse_move ||
//       pusermessage->m_emessage == e_message_non_client_hittest || pusermessage->m_emessage == e_message_set_cursor ||
//       pusermessage->id() == WM_CTLCOLORBTN ||
//       pusermessage->id() == WM_CTLCOLORDLG ||
//       pusermessage->id() == WM_CTLCOLOREDIT ||
//       pusermessage->id() == WM_CTLCOLORLISTBOX ||
//       pusermessage->id() == WM_CTLCOLORMSGBOX ||
//       pusermessage->id() == WM_CTLCOLORSCROLLBAR ||
//       pusermessage->id() == WM_CTLCOLORSTATIC ||
//       pusermessage->id() == WM_ENTERIDLE || pusermessage->id() == WM_CANCELMODE ||
//       pusermessage->id() == 0x0118)    // WM_SYSTIMER (caret blink)
//   {
//      // don't report very frequently sent messages
//      return;
//   }
//
//   const char * lpszMsgName = nullptr;
//   char szBuf[80];
//
//   // find message name
//   if (pusermessage->id() >= 0xC000)
//   {
//      // Window message registered with 'RegisterWindowMessage'
//      //  (actually a USER atom)
//      //      if (::GetClipboardFormatNameA(pusermessage->id(), szBuf, _countof(szBuf)))
//      //       lpszMsgName = szBuf;
//   }
//   else if (pusermessage->id() >= WM_USER)
//   {
//      // User message
//      sprintf(szBuf, "WM_USER+0x%04X", pusermessage->id() - WM_USER);
//      lpszMsgName = szBuf;
//   }
//   else
//   {
//      // a system windows message
//      const __MAP_MESSAGE* pMapMsg = allMessages;
//      for (/*null*/ ; pMapMsg->lpszMsg != nullptr; pMapMsg++)
//      {
//         if (pMapMsg->nMsg == pusermessage->id())
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
//      //information(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = %s (%p, %p)\n",
//      // lpszPrefix, pusermessage->m_hwnd, lpszMsgName,
//      //pusermessage->m_wparam, pusermessage->m_lparam);
//#else
//      //  ::information(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = %s (0x%08X, 0x%08X)\n",
//      //         lpszPrefix, pusermessage->m_hwnd, lpszMsgName,
//      //       pusermessage->m_wparam, pusermessage->m_lparam);
//#endif
//   }
//   else
//   {
//#ifdef _WIN64
//      //      ::information(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = 0x%04X (%p, %p)\n",
//      //       lpszPrefix, pusermessage->m_hwnd, lpszMsgName,
//      //     pusermessage->m_wparam, pusermessage->m_lparam);
//#else
//      //      ::information(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = 0x%04X (0x%08X, 0x%08X)\n",
//      //       lpszPrefix, pusermessage->m_hwnd, lpszMsgName,
//      //     pusermessage->m_wparam, pusermessage->m_lparam);
//#endif
//   }
//
//   /*   if (pusermessage->id() >= WM_DDE_FIRST && pusermessage->id() <= WM_DDE_LAST)
//    TraceDDE(lpszPrefix, pMsg);  */
//}
//
//
//
//void __trace_message(const char * lpszPrefix, MESSAGE * lpmsg)
//{
//   //ENSURE_ARG(::windows_definition::IsValidString(lpszPrefix));
//   ENSURE_ARG(lpmsg != nullptr);
//
//   if (lpmsg->message == e_message_mouse_move || lpmsg->message == e_message_non_client_mouse_move ||
//       lpmsg->message == e_message_non_client_hittest || lpmsg->message == e_message_set_cursor ||
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
//      //      information(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = %hs (%p, %p)\n",
//      //       lpszPrefix, pMsg->hwnd, lpszMsgName,
//      //     pMsg->wParam, pMsg->lParam);
//#else
//      //      ::information(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = %hs (0x%08X, 0x%08X)\n",
//      //       lpszPrefix, lpmsg->hwnd, lpszMsgName,
//      //     lpmsg->wParam, lpmsg->lParam);
//#endif
//   }
//   else
//   {
//#ifdef WIN64
//      //::information(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = 0x%04X (%p, %p)\n",
//      // lpszPrefix, pMsg->hwnd, lpszMsgName,
//      //pMsg->wParam, pMsg->lParam);
//#else
//      //::information(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = 0x%04X (0x%08X, 0x%08X)\n",
//      // lpszPrefix, lpmsg->hwnd, lpszMsgName,
//      //lpmsg->wParam, lpmsg->lParam);
//#endif
//   }
//
//   /*   if (lpmsg->message >= WM_DDE_FIRST && lpmsg->message <= WM_DDE_LAST)
//    TraceDDE(lpszPrefix, pMsg);*/
//}
//
//
