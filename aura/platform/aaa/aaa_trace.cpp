#include "framework.h"
#include <stdio.h>


namespace aura
{


   namespace trace
   {


      trace::trace()
      {

         //m_pobject = pparticle;

      }


      trace::~trace()
      {

      }


      typedef void ( * PFN_trace_v)(const ::string &pszFileName, i32 nLine, u32 dwCategory, u32 nLevel, const ::string & pszFmt, va_list args);
      CLASS_DECL_AURA void raw_trace_v(const ::string &pszFileName, i32 nLine, u32 dwCategory, u32 nLevel, const ::string & pszFmt, va_list args);
      CLASS_DECL_AURA PFN_trace_v trace_v = &raw_trace_v;


      void trace::TraceV(const ::string &pszFileName, i32 nLine, e_trace_category ecategory, enum_trace_level elevel, const ::string & pszFormat, va_list args) const
      {
         UNREFERENCED_PARAMETER(pszFileName);
         UNREFERENCED_PARAMETER(nLine);
         /*      const category *pCategory;
         trace_module * pmodule = nullptr;
         static const i32 nCount = 1024;
         char szBuf[nCount] = {'\0'};
         i32 nLen = 0;*/

         auto pcategory = ((trace *) this)->enabled_get(ecategory, elevel);

         /*
         if (nLen >= 0 && nLen < nCount)
         {
         if(g_Allocator.GetProcess()->m_bFileNameAndLineNo)
         {
         i32 nTemp;
         C_RUNTIME_FORMATTED_ERRORCHECK_SPRINTF(nTemp = _snprintf_s(szBuf + nLen, nCount - nLen, nCount - nLen - 1, "%s(%d) : ", pszFileName, nLine));
         if( nTemp < 0 )
         nLen = nCount;
         else
         nLen += nTemp;
         }
         }
         if (nLen >= 0 && nLen < nCount)
         {
         if(pCategory && g_Allocator.GetProcess()->m_bFuncAndCategoryNames)
         {
         i32 nTemp;
         C_RUNTIME_FORMATTED_ERRORCHECK_SPRINTF(nTemp = _snprintf_s(szBuf + nLen, nCount - nLen, nCount - nLen - 1, "%S: ", pCategory->Name()));
         if( nTemp < 0 )
         nLen = nCount;
         else
         nLen += nTemp;
         }
         }
         */
         /*
         if (nLen >= 0 && nLen < nCount)
         {
         C_RUNTIME_ERRORCHECK_SPRINTF(_vsnprintf_s(szBuf + nLen, nCount - nLen, nCount - nLen - 1, pszFormat, ptr));
         }
         */

         string str;

         str.formatf(pszFormat, args);

         ::information(str);

         /*
         if(pmodule != nullptr)
         pmodule->DebugReport(_CRT_WARN, nullptr, 0, nullptr, pszFormat, ptr);
         else
         information(szBuf);
         */

      }


      category::category()
      {

         m_elevelMin    = e_trace_level_information;
         m_ecategory    = trace_category_general;
         m_bEnabled     = true;

      }

      category::~category()
      {

      }


      CLASS_DECL_AURA void raw_trace_v(const ::string &pszFileName, i32 nLine, u32 dwCategory, u32 nLevel, const ::string & pszFmt, va_list args)
      {

         UNREFERENCED_PARAMETER(pszFileName);
         UNREFERENCED_PARAMETER(nLine);
         UNREFERENCED_PARAMETER(dwCategory);
         UNREFERENCED_PARAMETER(nLevel);

         string str;

         str.formatf(pszFmt, args);

         ::information(str);

      }

      /*CLASS_DECL_AURA void system_log_trace_v(const ::string &pszFileName, i32 nLine, u32 dwCategory, u32 nLevel, const ::string & pszFmt, va_list args)
      {
      ::auraacmesystem()->log().trace_v(pszFileName, nLine, dwCategory, nLevel, pszFmt, args);
      }*/


   } // namespace trace

}  // namespace aura





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
   DEFINE_MESSAGE(e_message_reposition),
   DEFINE_MESSAGE(e_message_size),
   DEFINE_MESSAGE(e_message_activate),
   DEFINE_MESSAGE(e_message_set_focus),
   DEFINE_MESSAGE(e_message_kill_focus),
   DEFINE_MESSAGE(e_message_enable),
   DEFINE_MESSAGE(WM_SETREDRAW),
   DEFINE_MESSAGE(WM_SETTEXT),
   DEFINE_MESSAGE(WM_GETTEXT),
   DEFINE_MESSAGE(WM_GETTEXTLENGTH),
   DEFINE_MESSAGE(e_message_paint),
   DEFINE_MESSAGE(e_message_close),
   DEFINE_MESSAGE(WM_QUERYENDSESSION),
   DEFINE_MESSAGE(e_message_quit),
   DEFINE_MESSAGE(WM_QUERYOPEN),
   DEFINE_MESSAGE(e_message_erase_background),
   DEFINE_MESSAGE(WM_SYSCOLORCHANGE),
   DEFINE_MESSAGE(WM_ENDSESSION),
   DEFINE_MESSAGE(e_message_show_window),
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
   DEFINE_MESSAGE(e_message_set_cursor),
   DEFINE_MESSAGE(e_message_mouse_activate),
   DEFINE_MESSAGE(WM_CHILDACTIVATE),
   DEFINE_MESSAGE(WM_QUEUESYNC),
   DEFINE_MESSAGE(WM_GETMINMAXINFO),
   DEFINE_MESSAGE(WM_ICONERASEBKGND),
   DEFINE_MESSAGE(WM_NEXTDLGCTL),
   DEFINE_MESSAGE(WM_SPOOLERSTATUS),
   DEFINE_MESSAGE(WM_DRAWITEM),
   DEFINE_MESSAGE(e_message_measure_item),
   DEFINE_MESSAGE(WM_DELETEITEM),
   DEFINE_MESSAGE(WM_VKEYTOITEM),
   DEFINE_MESSAGE(WM_CHARTOITEM),
   DEFINE_MESSAGE(WM_SETFONT),
   DEFINE_MESSAGE(WM_GETFONT),
   DEFINE_MESSAGE(WM_QUERYDRAGICON),
   DEFINE_MESSAGE(WM_COMPAREITEM),
   DEFINE_MESSAGE(WM_COMPACTING),
   DEFINE_MESSAGE(e_message_non_client_create),
   DEFINE_MESSAGE(e_message_non_client_destroy),
   DEFINE_MESSAGE(e_message_non_client_calcsize),
   DEFINE_MESSAGE(e_message_non_client_hittest),
   DEFINE_MESSAGE(e_message_non_client_paint),
   DEFINE_MESSAGE(e_message_non_client_activate),
   DEFINE_MESSAGE(WM_GETDLGCODE),
   DEFINE_MESSAGE(e_message_non_client_mouse_move),
   DEFINE_MESSAGE(e_message_non_client_left_button_down),
   DEFINE_MESSAGE(e_message_non_client_left_button_up),
   DEFINE_MESSAGE(WM_NCLBUTTONDBLCLK),
   DEFINE_MESSAGE(WM_NCRBUTTONDOWN),
   DEFINE_MESSAGE(WM_NCRBUTTONUP),
   DEFINE_MESSAGE(WM_NCRBUTTONDBLCLK),
   DEFINE_MESSAGE(WM_NCMBUTTONDOWN),
   DEFINE_MESSAGE(WM_NCMBUTTONUP),
   DEFINE_MESSAGE(WM_NCMBUTTONDBLCLK),
   DEFINE_MESSAGE(e_message_key_down),
   DEFINE_MESSAGE(e_message_key_up),
   DEFINE_MESSAGE(e_message_char),
   DEFINE_MESSAGE(e_message_dead_char),
   DEFINE_MESSAGE(e_message_sys_key_down),
   DEFINE_MESSAGE(e_message_sys_key_up),
   DEFINE_MESSAGE(e_message_sys_char),
   DEFINE_MESSAGE(e_message_sys_dead_char),
   DEFINE_MESSAGE(e_message_key_last),
   DEFINE_MESSAGE(WM_INITDIALOG),
   DEFINE_MESSAGE(e_message_command),
   DEFINE_MESSAGE(WM_SYSCOMMAND),
   DEFINE_MESSAGE(e_message_timer),
   DEFINE_MESSAGE(e_message_hscroll),
   DEFINE_MESSAGE(e_message_vscroll),
   DEFINE_MESSAGE(WM_INITMENU),
   DEFINE_MESSAGE(e_message_initialize_menu_popup),
   DEFINE_MESSAGE(WM_MENUSELECT),
   DEFINE_MESSAGE(WM_MENUCHAR),
   DEFINE_MESSAGE(WM_ENTERIDLE),
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
   DEFINE_MESSAGE(e_message_paintCLIPBOARD),
   DEFINE_MESSAGE(e_message_vscrollCLIPBOARD),
   DEFINE_MESSAGE(WM_SIZECLIPBOARD),
   DEFINE_MESSAGE(WM_ASKCBFORMATNAME),
   DEFINE_MESSAGE(WM_CHANGECBCHAIN),
   DEFINE_MESSAGE(e_message_hscrollCLIPBOARD),
   DEFINE_MESSAGE(WM_QUERYNEWPALETTE),
   DEFINE_MESSAGE(WM_PALETTEISCHANGING),
   DEFINE_MESSAGE(WM_PALETTECHANGED),
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
   DEFINE_MESSAGE(e_message_window_position_changed),
   DEFINE_MESSAGE(e_message_window_position_changing),
   // ca2 API specific messages
   DEFINE_MESSAGE(e_message_size_parent),
   DEFINE_MESSAGE(WM_SETMESSAGESTRING),
   DEFINE_MESSAGE(WM_IDLEUPDATECMDUI),
   DEFINE_MESSAGE(WM_COMMANDHELP),
   DEFINE_MESSAGE(WM_HELPHITTEST),
   DEFINE_MESSAGE(WM_EXITHELPMODE),
   DEFINE_MESSAGE(WM_HELP),
   DEFINE_MESSAGE(WM_NOTIFY),
   DEFINE_MESSAGE(e_message_context_menu),
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
   DEFINE_MESSAGE(WM_ENTERMENULOOP),
   DEFINE_MESSAGE(e_message_display_change),
   DEFINE_MESSAGE(WM_STYLECHANGED),
   DEFINE_MESSAGE(WM_STYLECHANGING),
   DEFINE_MESSAGE(WM_GETICON),
   DEFINE_MESSAGE(WM_SETICON),
   DEFINE_MESSAGE(WM_SIZING),
   DEFINE_MESSAGE(WM_MOVING),
   DEFINE_MESSAGE(e_message_capture_changed),
   DEFINE_MESSAGE(WM_DEVICECHANGE),
   {0,nullptr,}    // end of message list
};


CLASS_DECL_AURA const char *  get_windows_message_name(::u32 nMsg)
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


#undef DEFINE_MESSAGE

#define SIMPLE_TRACE_FUNCTION_NAME 0
#define SIMPLE_TRACE_FILE_NAME 0


enum_trace_level g_etracelevel = e_trace_level_error;

enum_trace_level get_global_trace_level()
{

   return g_etracelevel;

}


void set_global_trace_level(enum_trace_level etracelevel)
{

   g_etracelevel = etracelevel;

}


CLASS_DECL_AURA void __simple_tracea(::particle * pparticle, enum_trace_level elevel, const ::string & pszFunction, const ::string &pszFileName, i32 iLine, const ::string & psz)
{

   if (elevel < get_global_trace_level())
   {

      return;

   }

   string strMessage;

   auto pszTopicText = topic_text(pparticle);

   if (::is_set(pszTopicText) && *pszTopicText != '\0')
   {

      string strTopic(pszTopicText);

      strTopic.case_insensitive_begins_eat("class ");

      strTopic.case_insensitive_begins_eat("struct ");

      strMessage.formatf("%c:%s> %s", e_trace_level_char(elevel), strTopic.c_str(), psz);

   }
   else
   {

      strMessage.formatf("%c> %s", e_trace_level_char(elevel), psz);

   }

   #if SIMPLE_TRACE_FUNCTION_NAME

   if (::is_set(pszFunction))
   {

      strMessage += "\nFunction: ";

      strMessage += pszFunction;

   }

   #endif

   #if SIMPLE_TRACE_FILE_NAME

   if (::is_set(pszFileName))
   {

      strMessage += "\nFile: ";

      strMessage += pszFileName;

      if (iLine >= 1)
      {

         strMessage += "(" + as_string(iLine) + ")";

      }

   }

   #endif

   strMessage += "\n";

   information(strMessage);

}


CLASS_DECL_AURA void __simple_tracev(::particle * pparticle, enum_trace_level elevel, const ::string & pszFunction, const ::string &pszFileName, i32 iLine, const ::string & pszFormat, va_list args)
{

   //if (s_pstringmanager == nullptr)
   //{

   //   vprintf(pszFormat, args);

   //   return;

   //}

   string strMessage;

   strMessage.formatf_arguments(pszFormat, args);

   __simple_tracea(pparticle, elevel, pszFunction, pszFileName, iLine, strMessage);

}



