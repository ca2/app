

void __trace_message(const char * lpszPrefix, LPMESSAGE lpmsg)
{
   //ENSURE_ARG(AfxIsValidString(lpszPrefix));
   ENSURE_ARG(lpmsg != nullptr);

   if (lpmsg->message == e_message_mouse_move || lpmsg->message == e_message_non_client_mouse_move ||
         lpmsg->message == e_message_non_client_hittest || lpmsg->message == e_message_set_cursor ||
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
   if (lpmsg->message >= 0xC000)
   {
      // Window message registered with 'RegisterWindowMessage'
      //  (actually a USER atom)
//      if (::GetClipboardFormatNameA(lpmsg->message, szBuf, _countof(szBuf)))
      //       lpszMsgName = szBuf;
   }
   else if (lpmsg->message >= WM_USER)
   {
      // User message
      u32 uiValue = lpmsg->message - WM_USER;
      snprintf(szBuf, sizeof(szBuf), "WM_USER+0x%04X", uiValue);
      lpszMsgName = szBuf;
   }
   else
   {
      // a system windows message
      lpszMsgName = get_windows_message_name(lpmsg->message);
   }

   if (lpszMsgName != nullptr)
   {
#ifdef WIN64
//      FORMATTED_TRACE(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = %hs (%p, %p)\n",
      //       lpszPrefix, pMsg->hwnd, lpszMsgName,
      //     pMsg->wParam, pMsg->lParam);
#else
//      ::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = %hs (0x%08X, 0x%08X)\n",
      //       lpszPrefix, lpmsg->hwnd, lpszMsgName,
      //     lpmsg->wParam, lpmsg->lParam);
#endif
   }
   else
   {
#ifdef WIN64
      //::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = 0x%04X (%p, %p)\n",
      // lpszPrefix, pMsg->hwnd, lpszMsgName,
      //pMsg->wParam, pMsg->lParam);
#else
      //::output_debug_string(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = 0x%04X (0x%08X, 0x%08X)\n",
      // lpszPrefix, lpmsg->hwnd, lpszMsgName,
      //lpmsg->wParam, lpmsg->lParam);
#endif
   }

   /*   if (lpmsg->message >= WM_DDE_FIRST && lpmsg->message <= WM_DDE_LAST)
         TraceDDE(lpszPrefix, pMsg);*/
}


