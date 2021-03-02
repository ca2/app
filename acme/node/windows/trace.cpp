#include "framework.h"
#include "acme/operating_system.h"
#include <dde.h>


///////////////////////////////////////////////////////////////////////////////
//// Build data tables by including data file three times
//
//struct CLASS_DECL_ACME __MAP_MESSAGE
//{
//   ::u32    nMsg;
//   const char *  pszMsg;

//};
//
//#define DEFINE_MESSAGE(wm)  { wm, #wm }
//
//static const __MAP_MESSAGE allMessages[] =
//{
//   DEFINE_MESSAGE(e_message_create),
//   DEFINE_MESSAGE(e_message_destroy),
//   DEFINE_MESSAGE(e_message_move),
//   DEFINE_MESSAGE(e_message_size),
//   DEFINE_MESSAGE(e_message_activate),
//   DEFINE_MESSAGE(e_message_set_focus),
//   DEFINE_MESSAGE(e_message_kill_focus),
//   DEFINE_MESSAGE(e_message_enable),
//   DEFINE_MESSAGE(WM_SETREDRAW),
//   DEFINE_MESSAGE(WM_SETTEXT),
//   DEFINE_MESSAGE(WM_GETTEXT),
//   DEFINE_MESSAGE(WM_GETTEXTLENGTH),
//   DEFINE_MESSAGE(e_message_paint),
//   DEFINE_MESSAGE(e_message_close),
//   DEFINE_MESSAGE(WM_QUERYENDSESSION),
//   DEFINE_MESSAGE(WM_QUERYOPEN),
//   DEFINE_MESSAGE(e_message_erase_background),
//   DEFINE_MESSAGE(WM_SYSCOLORCHANGE),
//   DEFINE_MESSAGE(WM_ENDSESSION),
//   DEFINE_MESSAGE(e_message_show_window),
//   DEFINE_MESSAGE(WM_CTLCOLORMSGBOX),
//   DEFINE_MESSAGE(WM_CTLCOLOREDIT),
//   DEFINE_MESSAGE(WM_CTLCOLORLISTBOX),
//   DEFINE_MESSAGE(WM_CTLCOLORBTN),
//   DEFINE_MESSAGE(WM_CTLCOLORDLG),
//   DEFINE_MESSAGE(WM_CTLCOLORSCROLLBAR),
//   DEFINE_MESSAGE(WM_CTLCOLORSTATIC),
//   DEFINE_MESSAGE(WM_WININICHANGE),
//   DEFINE_MESSAGE(WM_SETTINGCHANGE),
//   DEFINE_MESSAGE(WM_DEVMODECHANGE),
//   DEFINE_MESSAGE(WM_ACTIVATEAPP),
//   DEFINE_MESSAGE(WM_FONTCHANGE),
//   DEFINE_MESSAGE(WM_TIMECHANGE),
//   DEFINE_MESSAGE(WM_CANCELMODE),
//   DEFINE_MESSAGE(e_message_set_cursor),
//   DEFINE_MESSAGE(e_message_mouse_activate),
//   DEFINE_MESSAGE(WM_CHILDACTIVATE),
//   DEFINE_MESSAGE(WM_QUEUESYNC),
//   DEFINE_MESSAGE(WM_GETMINMAXINFO),
//   DEFINE_MESSAGE(WM_ICONERASEBKGND),
//   DEFINE_MESSAGE(WM_NEXTDLGCTL),
//   DEFINE_MESSAGE(WM_SPOOLERSTATUS),
//   DEFINE_MESSAGE(WM_DRAWITEM),
//   DEFINE_MESSAGE(e_message_measure_item),
//   DEFINE_MESSAGE(WM_DELETEITEM),
//   DEFINE_MESSAGE(WM_VKEYTOITEM),
//   DEFINE_MESSAGE(WM_CHARTOITEM),
//   DEFINE_MESSAGE(WM_SETFONT),
//   DEFINE_MESSAGE(WM_GETFONT),
//   DEFINE_MESSAGE(WM_QUERYDRAGICON),
//   DEFINE_MESSAGE(WM_COMPAREITEM),
//   DEFINE_MESSAGE(WM_COMPACTING),
//   DEFINE_MESSAGE(e_message_nccreate),
//   DEFINE_MESSAGE(e_message_ncdestroy),
//   DEFINE_MESSAGE(e_message_nccalcsize),
//   DEFINE_MESSAGE(e_message_nchittest),
//   DEFINE_MESSAGE(e_message_ncpaint),
//   DEFINE_MESSAGE(e_message_ncactivate),
//   DEFINE_MESSAGE(WM_GETDLGCODE),
//   DEFINE_MESSAGE(e_message_non_client_mouse_move),
//   DEFINE_MESSAGE(e_message_non_client_left_button_down),
//   DEFINE_MESSAGE(e_message_non_client_left_button_up),
//   DEFINE_MESSAGE(WM_NCLBUTTONDBLCLK),
//   DEFINE_MESSAGE(WM_NCRBUTTONDOWN),
//   DEFINE_MESSAGE(WM_NCRBUTTONUP),
//   DEFINE_MESSAGE(WM_NCRBUTTONDBLCLK),
//   DEFINE_MESSAGE(WM_NCMBUTTONDOWN),
//   DEFINE_MESSAGE(WM_NCMBUTTONUP),
//   DEFINE_MESSAGE(WM_NCMBUTTONDBLCLK),
//   DEFINE_MESSAGE(e_message_key_down),
//   DEFINE_MESSAGE(e_message_key_up),
//   DEFINE_MESSAGE(e_message_char),
//   DEFINE_MESSAGE(e_message_dead_char),
//   DEFINE_MESSAGE(e_message_sys_key_down),
//   DEFINE_MESSAGE(e_message_sys_key_up),
//   DEFINE_MESSAGE(e_message_sys_char),
//   DEFINE_MESSAGE(e_message_sys_dead_char),
//   DEFINE_MESSAGE(e_message_key_last),
//   DEFINE_MESSAGE(WM_INITDIALOG),
//   DEFINE_MESSAGE(e_message_command),
//   DEFINE_MESSAGE(WM_SYSCOMMAND),
//   DEFINE_MESSAGE(e_message_timer),
//   DEFINE_MESSAGE(e_message_hscroll),
//   DEFINE_MESSAGE(e_message_vscroll),
//   DEFINE_MESSAGE(WM_INITMENU),
//   DEFINE_MESSAGE(e_message_initialize_menu_popup),
//   DEFINE_MESSAGE(WM_MENUSELECT),
//   DEFINE_MESSAGE(WM_MENUCHAR),
//   DEFINE_MESSAGE(WM_ENTERIDLE),
//   DEFINE_MESSAGE(e_message_mouse_wheel),
//   DEFINE_MESSAGE(e_message_mouse_move),
//   DEFINE_MESSAGE(e_message_left_button_down),
//   DEFINE_MESSAGE(e_message_left_button_up),
//   DEFINE_MESSAGE(e_message_left_button_double_click),
//   DEFINE_MESSAGE(e_message_right_button_down),
//   DEFINE_MESSAGE(e_message_right_button_up),
//   DEFINE_MESSAGE(e_message_right_button_double_click),
//   DEFINE_MESSAGE(e_message_middle_button_down),
//   DEFINE_MESSAGE(e_message_middle_button_up),
//   DEFINE_MESSAGE(e_message_middle_button_double_click),
//   DEFINE_MESSAGE(WM_PARENTNOTIFY),
//   DEFINE_MESSAGE(WM_MDICREATE),
//   DEFINE_MESSAGE(WM_MDIDESTROY),
//   DEFINE_MESSAGE(WM_MDIACTIVATE),
//   DEFINE_MESSAGE(WM_MDIRESTORE),
//   DEFINE_MESSAGE(WM_MDINEXT),
//   DEFINE_MESSAGE(WM_MDIMAXIMIZE),
//   DEFINE_MESSAGE(WM_MDITILE),
//   DEFINE_MESSAGE(WM_MDICASCADE),
//   DEFINE_MESSAGE(WM_MDIICONARRANGE),
//   DEFINE_MESSAGE(WM_MDIGETACTIVE),
//   DEFINE_MESSAGE(WM_MDISETMENU),
//   DEFINE_MESSAGE(WM_CUT),
//   DEFINE_MESSAGE(WM_COPYDATA),
//   DEFINE_MESSAGE(WM_COPY),
//   DEFINE_MESSAGE(WM_PASTE),
//   DEFINE_MESSAGE(WM_CLEAR),
//   DEFINE_MESSAGE(WM_UNDO),
//   DEFINE_MESSAGE(WM_RENDERFORMAT),
//   DEFINE_MESSAGE(WM_RENDERALLFORMATS),
//   DEFINE_MESSAGE(WM_DESTROYCLIPBOARD),
//   DEFINE_MESSAGE(WM_DRAWCLIPBOARD),
//   DEFINE_MESSAGE(e_message_paintCLIPBOARD),
//   DEFINE_MESSAGE(e_message_vscrollCLIPBOARD),
//   DEFINE_MESSAGE(WM_SIZECLIPBOARD),
//   DEFINE_MESSAGE(WM_ASKCBFORMATNAME),
//   DEFINE_MESSAGE(WM_CHANGECBCHAIN),
//   DEFINE_MESSAGE(e_message_hscrollCLIPBOARD),
//   DEFINE_MESSAGE(WM_QUERYNEWPALETTE),
//   DEFINE_MESSAGE(WM_PALETTEISCHANGING),
//   DEFINE_MESSAGE(WM_PALETTECHANGED),
//   DEFINE_MESSAGE(WM_DDE_INITIATE),
//   DEFINE_MESSAGE(WM_DDE_TERMINATE),
//   DEFINE_MESSAGE(WM_DDE_ADVISE),
//   DEFINE_MESSAGE(WM_DDE_UNADVISE),
//   DEFINE_MESSAGE(WM_DDE_ACK),
//   DEFINE_MESSAGE(WM_DDE_DATA),
//   DEFINE_MESSAGE(WM_DDE_REQUEST),
//   DEFINE_MESSAGE(WM_DDE_POKE),
//   DEFINE_MESSAGE(WM_DDE_EXECUTE),
//   DEFINE_MESSAGE(WM_DROPFILES),
//   DEFINE_MESSAGE(WM_POWER),
//   DEFINE_MESSAGE(e_message_window_position_changed),
//   DEFINE_MESSAGE(e_message_window_position_changing),
//// acme API specific messages
//   DEFINE_MESSAGE(e_message_size_parent),
//   DEFINE_MESSAGE(WM_SETMESSAGESTRING),
//   DEFINE_MESSAGE(WM_IDLEUPDATECMDUI),
//   DEFINE_MESSAGE(WM_INITIALUPDATE),
//   DEFINE_MESSAGE(WM_COMMANDHELP),
//   DEFINE_MESSAGE(WM_HELPHITTEST),
//   DEFINE_MESSAGE(WM_EXITHELPMODE),
//   DEFINE_MESSAGE(WM_HELP),
//   DEFINE_MESSAGE(WM_NOTIFY),
//   DEFINE_MESSAGE(e_message_context_menu),
//   DEFINE_MESSAGE(WM_TCARD),
//   DEFINE_MESSAGE(WM_MDIREFRESHMENU),
//   DEFINE_MESSAGE(WM_MOVING),
//   DEFINE_MESSAGE(WM_STYLECHANGED),
//   DEFINE_MESSAGE(WM_STYLECHANGING),
//   DEFINE_MESSAGE(WM_SIZING),
//   DEFINE_MESSAGE(WM_SETHOTKEY),
//   DEFINE_MESSAGE(WM_PRINT),
//   DEFINE_MESSAGE(WM_PRINTCLIENT),
//   DEFINE_MESSAGE(WM_POWERBROADCAST),
//   DEFINE_MESSAGE(WM_HOTKEY),
//   DEFINE_MESSAGE(WM_GETICON),
//   DEFINE_MESSAGE(WM_EXITMENULOOP),
//   DEFINE_MESSAGE(WM_ENTERMENULOOP),
//   DEFINE_MESSAGE(e_message_display_change),
//   DEFINE_MESSAGE(WM_STYLECHANGED),
//   DEFINE_MESSAGE(WM_STYLECHANGING),
//   DEFINE_MESSAGE(WM_GETICON),
//   DEFINE_MESSAGE(WM_SETICON),
//   DEFINE_MESSAGE(WM_SIZING),
//   DEFINE_MESSAGE(WM_MOVING),
//   DEFINE_MESSAGE(e_message_capture_changed),
//   DEFINE_MESSAGE(WM_DEVICECHANGE),
//   { 0, nullptr, }    // end of message list
//};
//
//#undef DEFINE_MESSAGE

/////////////////////////////////////////////////////////////////////////////
// DDE special case

void TraceDDE(const char * pszPrefix, const MSG* pMsg)

{
   ENSURE_ARG(pMsg != nullptr);
   if (pMsg->message == WM_DDE_EXECUTE)
   {
      uptr nDummy;
      HGLOBAL hCommands;
      if (!UnpackDDElParam(WM_DDE_EXECUTE, pMsg->lParam,
                           &nDummy, (uptr*)&hCommands))
      {
//         ::output_debug_string(trace_category_appmsg, 0, "Warning: Unable to unpack WM_DDE_EXECUTE lParam %08lX.\n",
         //          pMsg->lParam);
         return;
      }
      ASSERT(hCommands != nullptr);

      const char * pszCommands = (const char *)::GlobalLock(hCommands);

      ENSURE_THROW(pszCommands != nullptr, __throw(error_no_memory));

//      ::output_debug_string(trace_category_appmsg, 0, "%s: Execute '%s'.\n", pszPrefix, pszCommands);

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
//         ::output_debug_string(trace_category_appmsg, 0, "Warning: Unable to unpack WM_DDE_ADVISE lParam %08lX.\n",
//            pMsg->lParam);
         return;
      }
      aItem = (ATOM)nItem;
      ASSERT(aItem != 0);
      ASSERT(hAdvise != 0);

      DDEADVISE* pAdvise = (DDEADVISE*)::GlobalLock(hAdvise);

      ENSURE_THROW(pAdvise != nullptr, __throw(error_no_memory));

      wchar_t szItem[80];
      szItem[0] = '\0';

      if (aItem != 0)
         ::GlobalGetAtomNameW(aItem, szItem, _countof(szItem));

      wchar_t szFormat[80];
      szFormat[0] = '\0';
      if (((::u32)0xC000 <= (::u32)pAdvise->cfFormat) &&

            ((::u32)pAdvise->cfFormat <= (::u32)0xFFFF))

      {
         ::GetClipboardFormatNameW(pAdvise->cfFormat,

                                  szFormat, _countof(szFormat));

         // User defined clipboard formats have a range of 0xC000->0xFFFF
         // System clipboard formats have other ranges, but no printable
         // format names.
      }

      //TRACE(
      //   "%s: Advise item='%s', Format='%s', Ack=%d, Defer Update= %d\n",
      //   pszPrefix, szItem, szFormat, lpAdvise->fAckReq,

      //   pAdvise->fDeferUpd);

      ::GlobalUnlock(hAdvise);
   }
}

