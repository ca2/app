#include "framework.h"
#include "_netbsd.h"


#define DEFINE_MESSAGE(wm)  { wm, #wm }



/*
static void TraceDDE(const ::scoped_string & scopedstrPrefix, const MESSAGE* pMsg)

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

      const ::scoped_string & scopedstrCommands = (const_char_pointer )::GlobalLock(hCommands);

      ENSURE_THROW(scopedstrCommands != nullptr, ::windows_definition::ThrowMemoryException() );

//      ::information(::ca2::trace::category_AppMsg, 0, "%s: Execute '%s'.\n", pszPrefix, pszCommands);

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

      DDEADVISE* pAdvise = (DDEADVISE*)::GlobalLock(hAdvise);

      ENSURE_THROW(pAdvise != nullptr, ::windows_definition::ThrowMemoryException() );

      char szItem[80];
      szItem[0] = '\0';

      if (aItem != 0)
         ::GlobalGetAtomName(aItem, szItem, _countof(szItem));

      char szFormat[80];
      szFormat[0] = '\0';
      if (((unsigned int)0xC000 <= (unsigned int)pAdvise->cfFormat) &&

            ((unsigned int)pAdvise->cfFormat <= (unsigned int)0xFFFF))

      {
         ::GetClipboardFormatName(pAdvise->cfFormat,

            szFormat, _countof(szFormat));

         // User defined clipboard formats have a range of 0xC000->0xFFFF
         // ::acmeacmesystem() clipboard formats have other ranges, but no printable
         // format names.
      }

      ::windows_definition::Trace(
         "%s: Advise item='%s', Format='%s', Ack=%d, Defer Update= %d\n",
          pszPrefix, szItem, szFormat, lpAdvise->fAckReq,

         pAdvise->fDeferUpd);

      ::GlobalUnlock(hAdvise);
   }
}
*/
/////////////////////////////////////////////////////////////////////////////

//void __trace_message(const ::scoped_string & scopedstrPrefix, ::message::message * pmessage)

//{
////   ENSURE_ARG(::windows_definition::IsValidString(scopedstrPrefix));

//   ENSURE_ARG(pmessage != nullptr);
//   ::pointer<::user::message>pusermessage(pmessage);
//
//   if (pusermessage->m_emessage == e_message_mouse_move || pusermessage->m_emessage == e_message_non_client_mouse_move ||
//      pusermessage->m_emessage == e_message_non_client_hit_test || pusermessage->m_emessage == e_message_set_cursor ||
//      pusermessage->id() == WM_CTLCOLORBTN ||
//      pusermessage->id() == WM_CTLCOLORDLG ||
//      pusermessage->id() == WM_CTLCOLOREDIT ||
//      pusermessage->id() == WM_CTLCOLORLISTBOX ||
//      pusermessage->id() == WM_CTLCOLORMSGBOX ||
//      pusermessage->id() == WM_CTLCOLORSCROLLBAR ||
//      pusermessage->id() == WM_CTLCOLORSTATIC ||
//      pusermessage->id() == WM_ENTERIDLE || pusermessage->id() == WM_CANCELMODE ||
//      pusermessage->id() == 0x0118)    // WM_SYSTIMER (caret blink)
//   {
//      // don't report very frequently sent messages
//      return;
//   }
//
//   const ::scoped_string & scopedstrMsgName = nullptr;

//   char szBuf[80];
//
//   // find message name
//   if (pusermessage->id() >= 0xC000)
//   {
//      // Window message registered with 'RegisterWindowMessage'
//      //  (actually a USER atom)
////      if (::GetClipboardFormatNameA(pusermessage->id(), szBuf, _countof(szBuf)))
//  //       pszMsgName = szBuf;

//   }
//   else if (pusermessage->id() >= WM_USER)
//   {
//      // User message
//      sprintf(szBuf, "WM_USER+0x%04X", pusermessage->id() - WM_USER);
//      pszMsgName = szBuf;

//   }
//   else
//   {
//      // a system windows message
//      const __MAP_MESSAGE* pMapMsg = allMessages;
//      for (/*null*/ ; pMapMsg->pszMsg != nullptr; pMapMsg++)

//      {
//         if (pMapMsg->nMsg == pusermessage->id())
//         {
//            pszMsgName = pMapMsg->pszMsg;

//            break;
//         }
//      }
//   }
//
//   if (scopedstrMsgName != nullptr)

//   {
//#ifdef OS64BIT
//      //information(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%point, msg = %s (%point, %int_point)\n",
//        // pszPrefix, pusermessage->m_hwnd, pszMsgName,

//         //pusermessage->m_wparam, pusermessage->m_lparam);
//#else
//    //  ::information(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = %s (0x%08X, 0x%08X)\n",
////         pszPrefix, pusermessage->m_hwnd, pszMsgName,

//  //       pusermessage->m_wparam, pusermessage->m_lparam);
//#endif
//   }
//   else
//   {
//#ifdef OS64BIT
////      ::information(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%point, msg = 0x%04X (%point, %int_point)\n",
//  //       pszPrefix, pusermessage->m_hwnd, pszMsgName,

//    //     pusermessage->m_wparam, pusermessage->m_lparam);
//#else
////      ::information(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = 0x%04X (0x%08X, 0x%08X)\n",
//  //       pszPrefix, pusermessage->m_hwnd, pszMsgName,

//    //     pusermessage->m_wparam, pusermessage->m_lparam);
//#endif
//   }
//
///*   if (pusermessage->id() >= WM_DDE_FIRST && pusermessage->id() <= WM_DDE_LAST)
//      TraceDDE(scopedstrPrefix, pMsg);  */

//}
//
//
//
//void __trace_message(const ::scoped_string & scopedstrPrefix, MESSAGE * lpmsg)

//{
//   //ENSURE_ARG(::windows_definition::IsValidString(scopedstrPrefix));

//   ENSURE_ARG(pmsg != nullptr);

//
//   if (pmsg->message == e_message_mouse_move || lpmsg->message == e_message_non_client_mouse_move ||

//      pmsg->message == e_message_non_client_hit_test || lpmsg->message == e_message_set_cursor ||

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
//   const ::scoped_string & scopedstrMsgName = nullptr;

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
//      unsigned int uiValue = pmsg->message - WM_USER;

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
//   if (scopedstrMsgName != nullptr)

//   {
//#ifdef WIN64
////      information(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%point, msg = %hs (%point, %int_point)\n",
//  //       pszPrefix, pMsg->hwnd, pszMsgName,

//    //     pMsg->wParam, pMsg->lParam);
//#else
////      ::information(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = %hs (0x%08X, 0x%08X)\n",
//  //       pszPrefix, lpmsg->hwnd, pszMsgName,

//    //     pmsg->wParam, lpmsg->lParam);

//#endif
//   }
//   else
//   {
//#ifdef WIN64
//      //::information(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%point, msg = 0x%04X (%point, %int_point)\n",
//        // pszPrefix, pMsg->hwnd, pszMsgName,

//         //pMsg->wParam, pMsg->lParam);
//#else
//      //::information(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = 0x%04X (0x%08X, 0x%08X)\n",
//        // pszPrefix, lpmsg->hwnd, pszMsgName,

//         //pmsg->wParam, lpmsg->lParam);

//#endif
//   }
//
///*   if (pmsg->message >= WM_DDE_FIRST && lpmsg->message <= WM_DDE_LAST)

//      TraceDDE(scopedstrPrefix, pMsg);*/

//}
//
//
