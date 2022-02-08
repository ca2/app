#include "framework.h"
#include "aura/message.h"


namespace message
{

   class ::channel * CreateSignal()
   {
      return new class ::channel();
   }



//
//
//   CLASS_DECL_AURA bool is_idle_message(::message::message * pmessage)
//   {
//
//      __pointer(::user::message) pusermessage(pmessage);
//
//      // Return false if the message just dispatched should _not_
//      // cause on_idle to be run.  Messages which do not usually
//      // affect the state of the ::account::user interface and happen very
//      // often are checked for.
//
//      if(pusermessage == nullptr)
//         return false;
//
//      // redundant e_message_mouse_move and e_message_non_client_mouse_move
//      if(pusermessage->is_message() && (pusermessage->m_atom == e_message_mouse_move || pusermessage->m_atom == e_message_non_client_mouse_move))
//      {
//         return true;
//      }
//
//      // e_message_paint and WM_SYSTIMER (caret blink)
//      return pusermessage->m_atom != e_message_paint && pusermessage->m_atom != 0x0118;
//
//   }
//
//
//
//   CLASS_DECL_AURA bool is_idle_message(MESSAGE * pmsg)
//
//   {
//
//      // Return false if the message just dispatched should _not_
//      // cause on_idle to be run.  Messages which do not usually
//      // affect the state of the ::account::user interface and happen very
//      // often are checked for.
//
//      if(pmsg == nullptr)
//
//         return false;
//
//      // redundant e_message_mouse_move and e_message_non_client_mouse_move
//      if(pmsg->message == e_message_mouse_move || pmsg->message == e_message_non_client_mouse_move)
//
//      {
//         return true;
//      }
//
//      // e_message_paint and WM_SYSTIMER (caret blink)
//      return pmsg->message != e_message_paint && pmsg->message != 0x0118;
//
//
//   }


} // namespace message


namespace message
{


//   e_prototype get_message_prototype(enum_message emessage, ::u32 uCode)
//   {
//      switch (emessage)
//      {
//      case e_message_size:
//         return PrototypeSize;
//      case e_message_hscroll:
//      case e_message_vscroll:
//         return PrototypeScroll;
//      case e_message_create:
//      case e_message_non_client_create:
//         return PrototypeCreate;
//      case e_message_move:
//         return PrototypeMove;
//      case e_message_activate:
//         return PrototypeActivate;
//      case e_message_mouse_activate:
//         return PrototypeMouseActivate;
//      case e_message_measure_item:
//         return PrototypeMeasureItem;
//#ifdef WINDOWS
//      case WM_NOTIFY:
//         return PrototypeNotify;
//#endif
//      case e_message_command:
//         return PrototypeCommand;
//      case e_message_mouse_move:
//      case e_message_left_button_down:
//      case e_message_left_button_up:
//      case e_message_left_button_double_click:
//      case e_message_right_button_down:
//      case e_message_right_button_up:
//      case e_message_right_button_double_click:
//      case e_message_middle_button_down:
//      case e_message_middle_button_up:
//      case e_message_middle_button_double_click:
//      case e_message_non_client_mouse_move:
//      case e_message_non_client_left_button_down:
//      case e_message_non_client_left_button_up:
//         return PrototypeMouse;
//#ifdef WINDOWS
//      case e_message_mouse_wheel:
//         return PrototypeMouseWheel;
//#endif
//      case e_message_non_client_activate:
//         return PrototypeNcActivate;
//      case e_message_timer:
//         return PrototypeTimer;
//      case e_message_key_down:
//      case e_message_key_up:
//      case e_message_char:
//      case e_message_dead_char:
//      case e_message_sys_key_down:
//      case e_message_sys_key_up:
//      case e_message_sys_char:
//      case e_message_sys_dead_char:
//#if(_WIN32_WINNT >= 0x0501)
//      case e_message_uni_char:
//#endif
//         return PrototypeKey;
//      case e_message_non_client_hittest:
//         return PrototypeNcHitTest;
//      case e_message_set_cursor:
//         return PrototypeSetCursor;
//      case e_message_erase_background:
//         return PrototypeEraseBkgnd;
//      case e_message_show_window:
//         return PrototypeShowWindow;
//      case e_message_initialize_menu_popup:
//         return PrototypeInitMenuPopup;
//      case e_message_enable:
//         return PrototypeEnable;
//         /*#ifdef WINDOWS
//         case WM_CTLCOLOR:
//         if(pba)
//         return PrototypeCtlColor;
//         case WM_CTLCOLOR + WM_REFLECT_AXIS:
//         return PrototypeCtlColorReflect;
//         #endif*/
//      case e_message_kill_focus:
//         return PrototypeKillFocus;
//      case e_message_set_focus:
//         return PrototypeSetFocus;
//      case e_message_window_position_changing:
//      case e_message_window_position_changed:
//         return PrototypeWindowPos;
//      case e_message_non_client_calcsize:
//         return PrototypeNcCalcSize;
//      case e_message_simple_command:
//         return PrototypeSimpleCommand;
//      case e_message_paint:
//         return PrototypeNone;
//      default:
//         return PrototypeNone;
//      }
//   }


} // namespace message

