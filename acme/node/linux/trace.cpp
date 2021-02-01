#include "framework.h"
#include "_linux.h"

#define DEFINE_MESSAGE(wm)  { wm, #wm }



/*
static void TraceDDE(const char * pszPrefix, const MESSAGE* pMsg)

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

      const char * pszCommands = (const char *)::GlobalLock(hCommands);

      ENSURE_THROW(pszCommands != nullptr, ::AfxThrowMemoryException() );

//      ::output_debug_string(::ca2::trace::category_AppMsg, 0, "%s: Execute '%s'.\n", pszPrefix, pszCommands);

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

      DDEADVISE* pAdvise = (DDEADVISE*)::GlobalLock(hAdvise);

      ENSURE_THROW(pAdvise != nullptr, ::AfxThrowMemoryException() );

      char szItem[80];
      szItem[0] = '\0';

      if (aItem != 0)
         ::GlobalGetAtomName(aItem, szItem, _countof(szItem));

      char szFormat[80];
      szFormat[0] = '\0';
      if (((::u32)0xC000 <= (::u32)pAdvise->cfFormat) &&

            ((::u32)pAdvise->cfFormat <= (::u32)0xFFFF))

      {
         ::GetClipboardFormatName(pAdvise->cfFormat,

            szFormat, _countof(szFormat));

         // User defined clipboard formats have a range of 0xC000->0xFFFF
         // System clipboard formats have other ranges, but no printable
         // format names.
      }

      AfxTrace(
         "%s: Advise item='%s', Format='%s', Ack=%d, Defer Update= %d\n",
          pszPrefix, szItem, szFormat, lpAdvise->fAckReq,

         pAdvise->fDeferUpd);

      ::GlobalUnlock(hAdvise);
   }
}
*/
/////////////////////////////////////////////////////////////////////////////

//void __trace_message(const char * pszPrefix, ::message::message * pmessage)

//{
////   ENSURE_ARG(AfxIsValidString(pszPrefix));

//   ENSURE_ARG(pmessage != nullptr);
//   __pointer(::message::base) pbase(pmessage);
//
//   if (pbase->m_id == e_message_mouse_move || pbase->m_id == e_message_non_client_mouse_move ||
//      pbase->m_id == e_message_nchittest || pbase->m_id == e_message_set_cursor ||
//      pbase->m_id == WM_CTLCOLORBTN ||
//      pbase->m_id == WM_CTLCOLORDLG ||
//      pbase->m_id == WM_CTLCOLOREDIT ||
//      pbase->m_id == WM_CTLCOLORLISTBOX ||
//      pbase->m_id == WM_CTLCOLORMSGBOX ||
//      pbase->m_id == WM_CTLCOLORSCROLLBAR ||
//      pbase->m_id == WM_CTLCOLORSTATIC ||
//      pbase->m_id == WM_ENTERIDLE || pbase->m_id == WM_CANCELMODE ||
//      pbase->m_id == 0x0118)    // WM_SYSTIMER (caret blink)
//   {
//      // don't report very frequently sent messages
//      return;
//   }
//
//   const char * pszMsgName = nullptr;

//   char szBuf[80];
//
//   // find message name
//   if (pbase->m_id >= 0xC000)
//   {
//      // Window message registered with 'RegisterWindowMessage'
//      //  (actually a USER atom)
////      if (::GetClipboardFormatNameA(pbase->m_id, szBuf, _countof(szBuf)))
//  //       pszMsgName = szBuf;

//   }
//   else if (pbase->m_id >= WM_USER)
//   {
//      // User message
//      sprintf(szBuf, "WM_USER+0x%04X", pbase->m_id - WM_USER);
//      pszMsgName = szBuf;

//   }
//   else
//   {
//      // a system windows message
//      const __MAP_MESSAGE* pMapMsg = allMessages;
//      for (/*null*/ ; pMapMsg->pszMsg != nullptr; pMapMsg++)

//      {
//         if (pMapMsg->nMsg == pbase->m_id)
//         {
//            pszMsgName = pMapMsg->pszMsg;

//            break;
//         }
//      }
//   }
//
//   if (pszMsgName != nullptr)

//   {
//#ifdef OS64BIT
//      //TRACE(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%point_i32, msg = %s (%point_i32, %point_i32)\n",
//        // pszPrefix, pbase->m_hwnd, pszMsgName,

//         //pbase->m_wparam, pbase->m_lparam);
//#else
//    //  ::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = %s (0x%08X, 0x%08X)\n",
////         pszPrefix, pbase->m_hwnd, pszMsgName,

//  //       pbase->m_wparam, pbase->m_lparam);
//#endif
//   }
//   else
//   {
//#ifdef OS64BIT
////      ::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%point_i32, msg = 0x%04X (%point_i32, %point_i32)\n",
//  //       pszPrefix, pbase->m_hwnd, pszMsgName,

//    //     pbase->m_wparam, pbase->m_lparam);
//#else
////      ::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = 0x%04X (0x%08X, 0x%08X)\n",
//  //       pszPrefix, pbase->m_hwnd, pszMsgName,

//    //     pbase->m_wparam, pbase->m_lparam);
//#endif
//   }
//
///*   if (pbase->m_id >= WM_DDE_FIRST && pbase->m_id <= WM_DDE_LAST)
//      TraceDDE(pszPrefix, pMsg);  */

//}
//
//
//
//void __trace_message(const char * pszPrefix, MESSAGE * lpmsg)

//{
//   //ENSURE_ARG(AfxIsValidString(pszPrefix));

//   ENSURE_ARG(pmsg != nullptr);

//
//   if (pmsg->message == e_message_mouse_move || lpmsg->message == e_message_non_client_mouse_move ||

//      pmsg->message == e_message_nchittest || lpmsg->message == e_message_set_cursor ||

//      pmsg->message == WM_CTLCOLORBTN ||

//      pmsg->message == WM_CTLCOLORDLG ||

//      pmsg->message == WM_CTLCOLOREDIT ||

//      pmsg->message == WM_CTLCOLORLISTBOX ||

//      pmsg->message == WM_CTLCOLORMSGBOX ||

//      pmsg->message == WM_CTLCOLORSCROLLBAR ||

//      pmsg->message == WM_CTLCOLORSTATIC ||

//      pmsg->message == WM_ENTERIDLE || lpmsg->message == WM_CANCELMODE ||

//      pmsg->message == 0x0118)    // WM_SYSTIMER (caret blink)

//   {
//      // don't report very frequently sent messages
//      return;
//   }
//
//   const char * pszMsgName = nullptr;

//   char szBuf[80];
//
//   // find message name
//   if (pmsg->message >= 0xC000)

//   {
//      // Window message registered with 'RegisterWindowMessage'
//      //  (actually a USER atom)
////      if (::GetClipboardFormatNameA(pmsg->message, szBuf, _countof(szBuf)))

//  //       pszMsgName = szBuf;

//   }
//   else if (pmsg->message >= WM_USER)

//   {
//      // User message
//      u32 uiValue = pmsg->message - WM_USER;

//      snprintf(szBuf, sizeof(szBuf), "WM_USER+0x%04X", uiValue);
//      pszMsgName = szBuf;

//   }
//   else
//   {
//      // a system windows message
//      const __MAP_MESSAGE* pMapMsg = allMessages;
//      for (/*null*/ ; pMapMsg->pszMsg != nullptr; pMapMsg++)

//      {
//         if (pMapMsg->nMsg == pmsg->message)

//         {
//            pszMsgName = pMapMsg->pszMsg;

//            break;
//         }
//      }
//   }
//
//   if (pszMsgName != nullptr)

//   {
//#ifdef WIN64
////      TRACE(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%point_i32, msg = %hs (%point_i32, %point_i32)\n",
//  //       pszPrefix, pMsg->hwnd, pszMsgName,

//    //     pMsg->wParam, pMsg->lParam);
//#else
////      ::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = %hs (0x%08X, 0x%08X)\n",
//  //       pszPrefix, lpmsg->hwnd, pszMsgName,

//    //     pmsg->wParam, lpmsg->lParam);

//#endif
//   }
//   else
//   {
//#ifdef WIN64
//      //::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%point_i32, msg = 0x%04X (%point_i32, %point_i32)\n",
//        // pszPrefix, pMsg->hwnd, pszMsgName,

//         //pMsg->wParam, pMsg->lParam);
//#else
//      //::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = 0x%04X (0x%08X, 0x%08X)\n",
//        // pszPrefix, lpmsg->hwnd, pszMsgName,

//         //pmsg->wParam, lpmsg->lParam);

//#endif
//   }
//
///*   if (pmsg->message >= WM_DDE_FIRST && lpmsg->message <= WM_DDE_LAST)

//      TraceDDE(pszPrefix, pMsg);*/

//}
//
//
