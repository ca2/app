#include "framework.h"
#include <stdio.h>


/////////////////////////////////////////////////////////////////////////////

void __trace_message(const char * pszPrefix,::message::message * pmessage)

{
   ENSURE_ARG(__is_valid_string(pszPrefix));

   ENSURE_ARG(pmessage != nullptr);
   SCAST_PTR(::message::base,pbase,pmessage);

   UINT uiMessage;

   uiMessage = (UINT) pbase->m_id.i64();

   if(uiMessage == WM_MOUSEMOVE || uiMessage == WM_NCMOUSEMOVE ||
         uiMessage == WM_NCHITTEST || uiMessage == WM_SETCURSOR ||
         uiMessage == WM_CTLCOLORBTN ||
         uiMessage == WM_CTLCOLORDLG ||
         uiMessage == WM_CTLCOLOREDIT ||
         uiMessage == WM_CTLCOLORLISTBOX ||
         uiMessage == WM_CTLCOLORMSGBOX ||
         uiMessage == WM_CTLCOLORSCROLLBAR ||
         uiMessage == WM_CTLCOLORSTATIC ||
         uiMessage == WM_ENTERIDLE || uiMessage == WM_CANCELMODE ||
         uiMessage == 0x0118)    // WM_SYSTIMER (caret blink)
   {
      // don't report very frequently sent messages
      return;
   }

   const char * pszMsgName = nullptr;

   char szBuf[80];

   // find message name
   if(uiMessage >= 0xC000)
   {
      // Window message registered with 'RegisterWindowMessage'
      //  (actually a USER atom)
      if(::GetClipboardFormatNameA(uiMessage,szBuf,_countof(szBuf)))
         pszMsgName = szBuf;

   }
   else if(uiMessage >= WM_USER)
   {
      // User message
      sprintf_s(szBuf,_countof(szBuf),"WM_USER+0x%04X",uiMessage - WM_USER);
      pszMsgName = szBuf;

   }
   else
   {
      pszMsgName = get_windows_message_name(uiMessage);

   }

   if(pszMsgName != nullptr)

   {
#ifdef _WIN64
      //TRACE(::aura::trace::category_WinMsg, 4, "%s: oswindow=%point, msg = %s (%point, %point)\n",
      // pszPrefix, pbase->m_oswindow, pszMsgName,

      //pbase->m_wparam, pbase->m_lparam);
#else
      //  ::output_debug_string(::aura::trace::category_WinMsg, 4, "%s: oswindow=0x%08X, msg = %s (0x%08X, 0x%08X)\n",
      //         pszPrefix, pbase->m_oswindow, pszMsgName,

      //       pbase->m_wparam, pbase->m_lparam);
#endif
   }
   else
   {
#ifdef _WIN64
      //      ::output_debug_string(::aura::trace::category_WinMsg, 4, "%s: oswindow=%point, msg = 0x%04X (%point, %point)\n",
      //       pszPrefix, pbase->m_oswindow, pszMsgName,

      //     pbase->m_wparam, pbase->m_lparam);
#else
      //      ::output_debug_string(::aura::trace::category_WinMsg, 4, "%s: oswindow=0x%08X, msg = 0x%04X (0x%08X, 0x%08X)\n",
      //       pszPrefix, pbase->m_oswindow, pszMsgName,

      //     pbase->m_wparam, pbase->m_lparam);
#endif
   }

   /*if (uiMessage >= WM_DDE_FIRST && uiMessage <= WM_DDE_LAST)
   TraceDDE(pszPrefix, pMsg);*/

}


void __trace_message(const char * pszPrefix,LPMSG pmsg)

{
   ENSURE_ARG(__is_valid_string(pszPrefix));

   ENSURE_ARG(pmsg != nullptr);


   if(pmsg->message == WM_MOUSEMOVE || pmsg->message == WM_NCMOUSEMOVE ||

         pmsg->message == WM_NCHITTEST || pmsg->message == WM_SETCURSOR ||

         pmsg->message == WM_CTLCOLORBTN ||

         pmsg->message == WM_CTLCOLORDLG ||

         pmsg->message == WM_CTLCOLOREDIT ||

         pmsg->message == WM_CTLCOLORLISTBOX ||

         pmsg->message == WM_CTLCOLORMSGBOX ||

         pmsg->message == WM_CTLCOLORSCROLLBAR ||

         pmsg->message == WM_CTLCOLORSTATIC ||

         pmsg->message == WM_ENTERIDLE || pmsg->message == WM_CANCELMODE ||

         pmsg->message == 0x0118)    // WM_SYSTIMER (caret blink)

   {
      // don't report very frequently sent messages
      return;
   }

   const char * pszMsgName = nullptr;

   char szBuf[80];

   // find message name
   if(pmsg->message >= 0xC000)

   {
      // Window message registered with 'RegisterWindowMessage'
      //  (actually a USER atom)
      if(::GetClipboardFormatNameA(pmsg->message,szBuf,_countof(szBuf)))

         pszMsgName = szBuf;

   }
   else if(pmsg->message >= WM_USER)

   {
      // User message
      sprintf_s(szBuf,_countof(szBuf),"WM_USER+0x%04X",pmsg->message - WM_USER);

      pszMsgName = szBuf;

   }
   else
   {
      pszMsgName = get_windows_message_name(pmsg->message);

   }

   if(pszMsgName != nullptr)

   {
#ifdef WIN64
      //      TRACE(::aura::trace::category_WinMsg, 4, "%s: oswindow=%point, msg = %hs (%point, %point)\n",
      //       pszPrefix, pMsg->oswindow, pszMsgName,

      //     pMsg->wParam, pMsg->lParam);
#else
      //      ::output_debug_string(::aura::trace::category_WinMsg, 4, "%s: oswindow=0x%08X, msg = %hs (0x%08X, 0x%08X)\n",
      //       pszPrefix, pmsg->oswindow, pszMsgName,

      //     pmsg->wParam, pmsg->lParam);

#endif
   }
   else
   {
#ifdef WIN64
      //::output_debug_string(::aura::trace::category_WinMsg, 4, "%s: oswindow=%point, msg = 0x%04X (%point, %point)\n",
      // pszPrefix, pMsg->oswindow, pszMsgName,

      //pMsg->wParam, pMsg->lParam);
#else
      //::output_debug_string(::aura::trace::category_WinMsg, 4, "%s: oswindow=0x%08X, msg = 0x%04X (0x%08X, 0x%08X)\n",
      // pszPrefix, pmsg->oswindow, pszMsgName,

      //pmsg->wParam, pmsg->lParam);

#endif
   }

   /*if (pmsg->message >= WM_DDE_FIRST && pmsg->message <= WM_DDE_LAST)

   TraceDDE(pszPrefix, pMsg);*/

}
