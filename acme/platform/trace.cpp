#include "framework.h"
#include "acme/operating_system.h"
#include <stdio.h>
//#ifndef WINDOWS
//#include "acme/operating_system/cross/windows/_windows.h"
//#endif
#include "trace.h"


thread_local __pointer(logger) t_plogger;


void logger::t_construct(class ::system * psystem)
{

   psystem->__construct(t_plogger);

}


void logger::t_release()
{

   ::release(t_plogger);

}



trace::trace()
{

   //m_pobject = pobject;

}


trace::~trace()
{

}



trace_category::trace_category()
{

   m_etracelevelMinimum    = e_trace_level_information;
   m_etracecategory        = e_trace_category_general;
   m_bEnabled              = true;

}


trace_category::~trace_category()
{

}




#define DEFINE_MESSAGE(wm)  { wm, #wm }


struct MAP_WM_MESSAGE
{


   ::u32              nMsg;
   const char *      pszMsg;



};




static const MAP_WM_MESSAGE allMessagesArray[] =
{
   DEFINE_MESSAGE(e_message_create),
   DEFINE_MESSAGE(e_message_destroy),
   DEFINE_MESSAGE(e_message_move),
   DEFINE_MESSAGE(e_message_size),
   DEFINE_MESSAGE(e_message_activate),
   DEFINE_MESSAGE(e_message_set_focus),
   DEFINE_MESSAGE(e_message_kill_focus),
   DEFINE_MESSAGE(e_message_enable),
   DEFINE_MESSAGE(e_message_paint),
   DEFINE_MESSAGE(e_message_close),
   DEFINE_MESSAGE(e_message_quit),
   DEFINE_MESSAGE(e_message_erase_background),
   DEFINE_MESSAGE(e_message_show_window),
   DEFINE_MESSAGE(e_message_set_cursor),
   DEFINE_MESSAGE(e_message_mouse_activate),
   DEFINE_MESSAGE(e_message_measure_item),
   DEFINE_MESSAGE(e_message_non_client_create),
   DEFINE_MESSAGE(e_message_non_client_destroy),
   DEFINE_MESSAGE(e_message_non_client_calcsize),
   DEFINE_MESSAGE(e_message_non_client_hittest),
   DEFINE_MESSAGE(e_message_non_client_paint),
   DEFINE_MESSAGE(e_message_non_client_activate),
   DEFINE_MESSAGE(e_message_non_client_mouse_move),
   DEFINE_MESSAGE(e_message_non_client_left_button_down),
   DEFINE_MESSAGE(e_message_non_client_left_button_up),
   DEFINE_MESSAGE(e_message_key_down),
   DEFINE_MESSAGE(e_message_key_up),
   DEFINE_MESSAGE(e_message_char),
   DEFINE_MESSAGE(e_message_dead_char),
   DEFINE_MESSAGE(e_message_sys_key_down),
   DEFINE_MESSAGE(e_message_sys_key_up),
   DEFINE_MESSAGE(e_message_sys_char),
   DEFINE_MESSAGE(e_message_sys_dead_char),
   DEFINE_MESSAGE(e_message_key_last),
   DEFINE_MESSAGE(e_message_command),
   DEFINE_MESSAGE(e_message_timer),
   DEFINE_MESSAGE(e_message_hscroll),
   DEFINE_MESSAGE(e_message_vscroll),
   DEFINE_MESSAGE(e_message_initialize_menu_popup),
   DEFINE_MESSAGE(e_message_mouse_wheel),
   DEFINE_MESSAGE(e_message_mouse_move),
   DEFINE_MESSAGE(e_message_left_button_down),
   DEFINE_MESSAGE(e_message_left_button_up),
   DEFINE_MESSAGE(e_message_left_button_double_click),
   DEFINE_MESSAGE(e_message_right_button_down),
   DEFINE_MESSAGE(e_message_right_button_up),
   DEFINE_MESSAGE(e_message_right_button_double_click),
   DEFINE_MESSAGE(e_message_middle_button_down),
   DEFINE_MESSAGE(e_message_middle_button_up),
   DEFINE_MESSAGE(e_message_middle_button_double_click),
   DEFINE_MESSAGE(e_message_paint),
   DEFINE_MESSAGE(e_message_vscroll),
   DEFINE_MESSAGE(e_message_hscroll),
   DEFINE_MESSAGE(e_message_window_position_changed),
   DEFINE_MESSAGE(e_message_window_position_changing),
   // ca2 API specific messages
   DEFINE_MESSAGE(e_message_size_parent),
   DEFINE_MESSAGE(e_message_set_message_string),
   DEFINE_MESSAGE(e_message_idle_update_command_user_interface),
   DEFINE_MESSAGE(e_message_command_help),
   DEFINE_MESSAGE(e_message_help_hit_test),
   DEFINE_MESSAGE(e_message_exit_help_mode),
   DEFINE_MESSAGE(e_message_context_menu),
   DEFINE_MESSAGE(e_message_display_change),
#ifdef WINDOWS_DESKTOP
   DEFINE_MESSAGE(WM_SIZECLIPBOARD),
   DEFINE_MESSAGE(WM_ASKCBFORMATNAME),
   DEFINE_MESSAGE(WM_CHANGECBCHAIN),
   DEFINE_MESSAGE(WM_QUERYNEWPALETTE),
   DEFINE_MESSAGE(WM_PALETTEISCHANGING),
   DEFINE_MESSAGE(WM_PALETTECHANGED),
   DEFINE_MESSAGE(WM_PARENTNOTIFY),
   DEFINE_MESSAGE(WM_MDICREATE),
   DEFINE_MESSAGE(WM_MDIDESTROY),
   DEFINE_MESSAGE(WM_MDIACTIVATE),
   DEFINE_MESSAGE(WM_MDIRESTORE),
   DEFINE_MESSAGE(WM_MDINEXT),
   DEFINE_MESSAGE(WM_MDIMAXIMIZE),
   DEFINE_MESSAGE(WM_MDITILE),
   DEFINE_MESSAGE(WM_MDICASCADE),
   DEFINE_MESSAGE(WM_MDIICONARRANGE),
   DEFINE_MESSAGE(WM_MDIGETACTIVE),
   DEFINE_MESSAGE(WM_MDISETMENU),
   DEFINE_MESSAGE(WM_CUT),
   DEFINE_MESSAGE(WM_COPYDATA),
   DEFINE_MESSAGE(WM_COPY),
   DEFINE_MESSAGE(WM_PASTE),
   DEFINE_MESSAGE(WM_CLEAR),
   DEFINE_MESSAGE(WM_UNDO),
   DEFINE_MESSAGE(WM_RENDERFORMAT),
   DEFINE_MESSAGE(WM_RENDERALLFORMATS),
   DEFINE_MESSAGE(WM_DESTROYCLIPBOARD),
   DEFINE_MESSAGE(WM_DRAWCLIPBOARD),
      /*   DEFINE_MESSAGE(WM_DDE_INITIATE),
   DEFINE_MESSAGE(WM_DDE_TERMINATE),
   DEFINE_MESSAGE(WM_DDE_ADVISE),
   DEFINE_MESSAGE(WM_DDE_UNADVISE),
   DEFINE_MESSAGE(WM_DDE_ACK),
   DEFINE_MESSAGE(WM_DDE_DATA),
   DEFINE_MESSAGE(WM_DDE_REQUEST),
   DEFINE_MESSAGE(WM_DDE_POKE),
   DEFINE_MESSAGE(WM_DDE_EXECUTE),*/
   DEFINE_MESSAGE(WM_DROPFILES),
   DEFINE_MESSAGE(WM_POWER),
      DEFINE_MESSAGE(WM_ENTERMENULOOP),
      DEFINE_MESSAGE(WM_HELP),
   DEFINE_MESSAGE(WM_NOTIFY),
   DEFINE_MESSAGE(WM_TCARD),
   DEFINE_MESSAGE(WM_MDIREFRESHMENU),
   DEFINE_MESSAGE(WM_MOVING),
   DEFINE_MESSAGE(WM_STYLECHANGED),
   DEFINE_MESSAGE(WM_STYLECHANGING),
   DEFINE_MESSAGE(WM_SIZING),
   DEFINE_MESSAGE(WM_SETHOTKEY),
   DEFINE_MESSAGE(WM_PRINT),
   DEFINE_MESSAGE(WM_PRINTCLIENT),
   DEFINE_MESSAGE(WM_POWERBROADCAST),
   DEFINE_MESSAGE(WM_HOTKEY),
   DEFINE_MESSAGE(WM_GETICON),
   DEFINE_MESSAGE(WM_EXITMENULOOP),
   DEFINE_MESSAGE(WM_STYLECHANGED),
   DEFINE_MESSAGE(WM_STYLECHANGING),
   DEFINE_MESSAGE(WM_GETICON),
   DEFINE_MESSAGE(WM_SETICON),
   DEFINE_MESSAGE(WM_SIZING),
   DEFINE_MESSAGE(WM_MOVING),
   DEFINE_MESSAGE(e_message_capture_changed),
   DEFINE_MESSAGE(WM_DEVICECHANGE),
   DEFINE_MESSAGE(WM_SETREDRAW),
   DEFINE_MESSAGE(WM_SETTEXT),
   DEFINE_MESSAGE(WM_GETTEXT),
   DEFINE_MESSAGE(WM_GETTEXTLENGTH),
   DEFINE_MESSAGE(WM_QUERYENDSESSION),
   DEFINE_MESSAGE(WM_QUERYOPEN),
   DEFINE_MESSAGE(WM_SYSCOLORCHANGE),
   DEFINE_MESSAGE(WM_ENDSESSION),
   DEFINE_MESSAGE(WM_CTLCOLORMSGBOX),
   DEFINE_MESSAGE(WM_CTLCOLOREDIT),
   DEFINE_MESSAGE(WM_CTLCOLORLISTBOX),
   DEFINE_MESSAGE(WM_CTLCOLORBTN),
   DEFINE_MESSAGE(WM_CTLCOLORDLG),
   DEFINE_MESSAGE(WM_CTLCOLORSCROLLBAR),
   DEFINE_MESSAGE(WM_CTLCOLORSTATIC),
   DEFINE_MESSAGE(WM_WININICHANGE),
   DEFINE_MESSAGE(WM_SETTINGCHANGE),
   DEFINE_MESSAGE(WM_DEVMODECHANGE),
   DEFINE_MESSAGE(WM_ACTIVATEAPP),
   DEFINE_MESSAGE(WM_FONTCHANGE),
   DEFINE_MESSAGE(WM_TIMECHANGE),
   DEFINE_MESSAGE(WM_CANCELMODE),
   DEFINE_MESSAGE(WM_CHILDACTIVATE),
   DEFINE_MESSAGE(WM_QUEUESYNC),
   DEFINE_MESSAGE(WM_GETMINMAXINFO),
   DEFINE_MESSAGE(WM_ICONERASEBKGND),
   DEFINE_MESSAGE(WM_NEXTDLGCTL),
   DEFINE_MESSAGE(WM_SPOOLERSTATUS),
   DEFINE_MESSAGE(WM_DRAWITEM),
   DEFINE_MESSAGE(WM_DELETEITEM),
   DEFINE_MESSAGE(WM_VKEYTOITEM),
   DEFINE_MESSAGE(WM_CHARTOITEM),
   DEFINE_MESSAGE(WM_SETFONT),
   DEFINE_MESSAGE(WM_GETFONT),
   DEFINE_MESSAGE(WM_QUERYDRAGICON),
   DEFINE_MESSAGE(WM_COMPAREITEM),
   DEFINE_MESSAGE(WM_COMPACTING),
   DEFINE_MESSAGE(WM_GETDLGCODE),
   DEFINE_MESSAGE(WM_NCLBUTTONDBLCLK),
   DEFINE_MESSAGE(WM_NCRBUTTONDOWN),
   DEFINE_MESSAGE(WM_NCRBUTTONUP),
   DEFINE_MESSAGE(WM_NCRBUTTONDBLCLK),
   DEFINE_MESSAGE(WM_NCMBUTTONDOWN),
   DEFINE_MESSAGE(WM_NCMBUTTONUP),
   DEFINE_MESSAGE(WM_NCMBUTTONDBLCLK),
   DEFINE_MESSAGE(WM_INITDIALOG),
   DEFINE_MESSAGE(WM_SYSCOMMAND),
   DEFINE_MESSAGE(WM_INITMENU),
   DEFINE_MESSAGE(WM_MENUSELECT),
   DEFINE_MESSAGE(WM_MENUCHAR),
   DEFINE_MESSAGE(WM_ENTERIDLE),
#endif
   {0,nullptr,}    // end of message list
};


CLASS_DECL_ACME const char *  get_windows_message_name(::u32 nMsg)
{

   MAP_WM_MESSAGE * pmessage = (MAP_WM_MESSAGE *) allMessagesArray;

   while(pmessage->nMsg != 0)
   {

      if(pmessage->nMsg == nMsg)
         return pmessage->pszMsg;


      pmessage++;

   }

   return nullptr;

}


tracer& tracer::operator << (const exception& exception)
{

   m_str += exception.m_strMessage  + " (" + __string(exception.m_estatus) + ")";

   return *this;

}


tracer& tracer::operator << (const e_status& estatus)
{

   m_str += __string(estatus);

   return *this;

}


tracer& tracer::operator << (const enum_status& estatus)
{

   m_str += __string(estatus);

   return *this;

}


tracer & tracer::operator << (const string & str)
{

   m_str += str;

   return *this;

}


tracer & tracer::operator << (const char * psz)
{

   m_str += string(psz);

   return *this;

}


tracer & tracer::operator << (enum_flush)
{

   flush();

   return *this;

}


//void tracer::print(const ::string & str)
//{
//
//   m_str += str;
//
//}


tracer & tracer::operator << (const integral_byte & memsize)
{

   if (memsize < 1_kb)
   {

      return format_output("%d bytes", memsize);

   }
   else if (memsize < 1_mb)
   {

      return format_output("%0.2f kb", (double)memsize / (double)(1_kb));

   }
   else if (memsize < 1_gb)
   {

      return format_output("%0.2f MB", (double)memsize / (double)(1_mb));

   }
   else
   {

      return format_output("%0.2f GB", (double)memsize / (double)(1_gb));

   }

}


void tracer::flush()
{

   auto plogger = ::is_set(m_plogger) ? m_plogger : t_plogger.m_p;

   if(::is_null(plogger))
   {

      ::logger::t_construct(m_psystem);

      plogger = t_plogger.m_p;

   }

   if (::is_set(plogger))
   {

      plogger->print(m_etracelevel, m_etracecategory, m_pszFunction, m_pszFile, m_iLine, m_str);

   }

}

