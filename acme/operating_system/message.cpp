// Created by camilo on 2022-11-02 05:09 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/constant/message.h"
#include "acme/primitive/primitive/tuple.h"
#ifdef WINDOWS_DESKTOP
#include "acme/_operating_system.h"
#endif


#define __message_entry(wm)  { wm, #wm }


static const i32_sz g_iszaMessageName[] =
{
   __message_entry(e_message_create),
   __message_entry(e_message_destroy),
   __message_entry(e_message_move),
   __message_entry(e_message_size),
   __message_entry(e_message_activate),
   __message_entry(e_message_set_focus),
   __message_entry(e_message_kill_focus),
   __message_entry(e_message_enable),
   __message_entry(e_message_paint),
   __message_entry(MESSAGE_CLOSE),
   __message_entry(e_message_quit),
   __message_entry(e_message_erase_background),
   __message_entry(e_message_show_window),
   __message_entry(e_message_set_cursor),
   __message_entry(e_message_mouse_activate),
   __message_entry(e_message_measure_item),
   __message_entry(e_message_non_client_create),
   __message_entry(e_message_non_client_destroy),
   __message_entry(e_message_non_client_calc_size),
   __message_entry(e_message_non_client_hit_test),
   __message_entry(e_message_non_client_paint),
   __message_entry(e_message_non_client_activate),
   __message_entry(e_message_non_client_mouse_move),
   __message_entry(e_message_non_client_left_button_down),
   __message_entry(e_message_non_client_left_button_up),
   __message_entry(e_message_key_down),
   __message_entry(e_message_key_up),
   __message_entry(e_message_char),
   __message_entry(e_message_dead_char),
   __message_entry(e_message_sys_key_down),
   __message_entry(e_message_sys_key_up),
   __message_entry(e_message_sys_char),
   __message_entry(e_message_sys_dead_char),
   __message_entry(e_message_key_last),
   __message_entry(e_message_command),
   __message_entry(e_message_timer),
   __message_entry(e_message_hscroll),
   __message_entry(e_message_vscroll),
   __message_entry(e_message_initialize_menu_popup),
   __message_entry(e_message_mouse_wheel),
   __message_entry(e_message_mouse_move),
   __message_entry(e_message_left_button_down),
   __message_entry(e_message_left_button_up),
   __message_entry(e_message_left_button_double_click),
   __message_entry(e_message_right_button_down),
   __message_entry(e_message_right_button_up),
   __message_entry(e_message_right_button_double_click),
   __message_entry(e_message_middle_button_down),
   __message_entry(e_message_middle_button_up),
   __message_entry(e_message_middle_button_double_click),
   __message_entry(e_message_paint),
   __message_entry(e_message_vscroll),
   __message_entry(e_message_hscroll),
   __message_entry(e_message_window_position_changed),
   __message_entry(e_message_window_position_changing),
   // ca2 API specific messages
   __message_entry(e_message_size_parent),
   __message_entry(e_message_set_message_string),
   __message_entry(e_message_idle_update_command_user_interface),
   __message_entry(e_message_command_help),
   __message_entry(e_message_help_hit_test),
   __message_entry(e_message_exit_help_mode),
   __message_entry(e_message_context_menu),
   __message_entry(e_message_display_change),
#ifdef WINDOWS_DESKTOP
   __message_entry(WM_SIZECLIPBOARD),
   __message_entry(WM_ASKCBFORMATNAME),
   __message_entry(WM_CHANGECBCHAIN),
   __message_entry(WM_QUERYNEWPALETTE),
   __message_entry(WM_PALETTEISCHANGING),
   __message_entry(WM_PALETTECHANGED),
   __message_entry(WM_PARENTNOTIFY),
   __message_entry(WM_MDICREATE),
   __message_entry(WM_MDIDESTROY),
   __message_entry(WM_MDIACTIVATE),
   __message_entry(WM_MDIRESTORE),
   __message_entry(WM_MDINEXT),
   __message_entry(WM_MDIMAXIMIZE),
   __message_entry(WM_MDITILE),
   __message_entry(WM_MDICASCADE),
   __message_entry(WM_MDIICONARRANGE),
   __message_entry(WM_MDIGETACTIVE),
   __message_entry(WM_MDISETMENU),
   __message_entry(WM_CUT),
   __message_entry(WM_COPYDATA),
   __message_entry(WM_COPY),
   __message_entry(WM_PASTE),
   __message_entry(WM_CLEAR),
   __message_entry(WM_UNDO),
   __message_entry(WM_RENDERFORMAT),
   __message_entry(WM_RENDERALLFORMATS),
   __message_entry(WM_DESTROYCLIPBOARD),
   __message_entry(WM_DRAWCLIPBOARD),
   /*   __message_entry(WM_DDE_INITIATE),
__message_entry(WM_DDE_TERMINATE),
__message_entry(WM_DDE_ADVISE),
__message_entry(WM_DDE_UNADVISE),
__message_entry(WM_DDE_ACK),
__message_entry(WM_DDE_DATA),
__message_entry(WM_DDE_REQUEST),
__message_entry(WM_DDE_POKE),
__message_entry(WM_DDE_EXECUTE),*/
__message_entry(WM_DROPFILES),
__message_entry(WM_POWER),
   __message_entry(WM_ENTERMENULOOP),
   __message_entry(WM_HELP),
__message_entry(WM_NOTIFY),
__message_entry(WM_TCARD),
__message_entry(WM_MDIREFRESHMENU),
__message_entry(WM_MOVING),
__message_entry(WM_STYLECHANGED),
__message_entry(WM_STYLECHANGING),
__message_entry(WM_SIZING),
__message_entry(WM_SETHOTKEY),
__message_entry(WM_PRINT),
__message_entry(WM_PRINTCLIENT),
__message_entry(WM_POWERBROADCAST),
__message_entry(WM_HOTKEY),
__message_entry(WM_GETICON),
__message_entry(WM_EXITMENULOOP),
__message_entry(WM_STYLECHANGED),
__message_entry(WM_STYLECHANGING),
__message_entry(WM_GETICON),
__message_entry(WM_SETICON),
__message_entry(WM_SIZING),
__message_entry(WM_MOVING),
__message_entry(e_message_capture_changed),
__message_entry(WM_DEVICECHANGE),
__message_entry(WM_SETREDRAW),
__message_entry(WM_SETTEXT),
__message_entry(WM_GETTEXT),
__message_entry(WM_GETTEXTLENGTH),
__message_entry(WM_QUERYENDSESSION),
__message_entry(WM_QUERYOPEN),
__message_entry(WM_SYSCOLORCHANGE),
__message_entry(WM_ENDSESSION),
__message_entry(WM_CTLCOLORMSGBOX),
__message_entry(WM_CTLCOLOREDIT),
__message_entry(WM_CTLCOLORLISTBOX),
__message_entry(WM_CTLCOLORBTN),
__message_entry(WM_CTLCOLORDLG),
__message_entry(WM_CTLCOLORSCROLLBAR),
__message_entry(WM_CTLCOLORSTATIC),
__message_entry(WM_WININICHANGE),
__message_entry(WM_SETTINGCHANGE),
__message_entry(WM_DEVMODECHANGE),
__message_entry(WM_ACTIVATEAPP),
__message_entry(WM_FONTCHANGE),
__message_entry(WM_TIMECHANGE),
__message_entry(WM_CANCELMODE),
__message_entry(WM_CHILDACTIVATE),
__message_entry(WM_QUEUESYNC),
__message_entry(WM_GETMINMAXINFO),
__message_entry(WM_ICONERASEBKGND),
__message_entry(WM_NEXTDLGCTL),
__message_entry(WM_SPOOLERSTATUS),
__message_entry(WM_DRAWITEM),
__message_entry(WM_DELETEITEM),
__message_entry(WM_VKEYTOITEM),
__message_entry(WM_CHARTOITEM),
__message_entry(WM_SETFONT),
__message_entry(WM_GETFONT),
__message_entry(WM_QUERYDRAGICON),
__message_entry(WM_COMPAREITEM),
__message_entry(WM_COMPACTING),
__message_entry(WM_GETDLGCODE),
__message_entry(WM_NCLBUTTONDBLCLK),
__message_entry(WM_NCRBUTTONDOWN),
__message_entry(WM_NCRBUTTONUP),
__message_entry(WM_NCRBUTTONDBLCLK),
__message_entry(WM_NCMBUTTONDOWN),
__message_entry(WM_NCMBUTTONUP),
__message_entry(WM_NCMBUTTONDBLCLK),
__message_entry(WM_INITDIALOG),
__message_entry(WM_SYSCOMMAND),
__message_entry(WM_INITMENU),
__message_entry(WM_MENUSELECT),
__message_entry(WM_MENUCHAR),
__message_entry(WM_ENTERIDLE),
#endif
   {-1,nullptr,}    // end of message list
};


namespace operating_system
{


   CLASS_DECL_ACME const char * get_message_text(enum_message emessage)
   {

      auto iFind = (::i32)emessage;

      auto pmessagename =
         tuple_array_find(
            g_iszaMessageName,
            [iFind](auto ptuple) { return ptuple->m_i == iFind; }, // find_condition
            [](auto ptuple) { return ptuple->m_i >= 0; } // continue condition
      );

      if (!pmessagename)
      {

         return nullptr;

      }

      return pmessagename->m_psz;

   }


} // namespace operating_system



