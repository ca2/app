#include "framework.h"
#include "acme/constant/message.h"
#include "acme/constant/message_prototype.h"
#include "acme/operating_system/message.h"
#include "apex/message/message.h"


//#include "acme/operating_system/cross/windows/_windows.h"


namespace message
{


//   class ::channel * CreateSignal()
//   {
//      return memory_new class ::channel();
//   }


   CLASS_DECL_APEX bool is_idle_message(::message::message * pmessage)
   {

      // Return false if the message just dispatched should _not_
      // cause on_idle to be run.  Messages which do not usually
      // affect the state of the ::account::user interface and happen very
      // often are checked for.

      if (pmessage == nullptr)
      {

         return false;

      }

      // redundant e_message_mouse_move and e_message_non_client_mouse_move
      if(pmessage->m_atom == e_message_mouse_move || pmessage->m_atom == e_message_non_client_mouse_move)
      {

         return true;

      }

      // e_message_paint and WM_SYSTIMER (caret blink)
      return pmessage->m_atom != e_message_paint && pmessage->m_atom != 0x0118;

   }



   CLASS_DECL_APEX bool is_idle_message(MESSAGE * pmsg)
   {

      // Return false if the message just dispatched should _not_
      // cause on_idle to be run.  Messages which do not usually
      // affect the state of the ::account::user interface and happen very
      // often are checked for.

      if(pmsg == nullptr)

         return false;

      // redundant e_message_mouse_move and e_message_non_client_mouse_move
      if(pmsg->m_atom == e_message_mouse_move || pmsg->m_atom == e_message_non_client_mouse_move)

      {
         return true;
      }

      // e_message_paint and WM_SYSTIMER (caret blink)
      return pmsg->m_atom != e_message_paint && pmsg->m_atom != 0x0118;

   }


//   ::u32 translate_to_os_message(const ::atom & atom)
//   {
//
////#ifdef WINDOWS
////
////      if (atom.m_etype == ::atom::e_type_message)
////      {
////
////         return (::u32) atom.m_emessage;
////
////      }
////
////#elif defined(LINUX) ||  defined(__APPLE__) || defined(ANDROID)
////      switch (emessage)
////      {
////      case e_message_create:
////         return e_message_create;
////      default:
////         return emessage;
////      };
////
////#else
////      switch (emessage)
////      {
////      default:
////         return emessage;
////      };
////#endif
//
//   }


   enum_prototype get_message_prototype(enum_message emessage, ::u32 /* uCode */ )
   {

      switch (emessage)
      {
      case e_message_size:
         return e_prototype_size;
      case e_message_hscroll:
      case e_message_vscroll:
         return e_prototype_scroll;
      case e_message_create:
      case e_message_non_client_create:
         return e_prototype_create;
      case e_message_move:
         return e_prototype_move;
      case e_message_activate:
         return e_prototype_activate;
      case e_message_mouse_activate:
         return e_prototype_mouse_activate;
      case e_message_measure_item:
         return e_prototype_measure_item;
      case e_message_wm_notify:
         return e_prototype_notify;
      case e_message_command:
         return e_prototype_command;
         //{
         //switch (uicode)
         //{
         //case cn_update_::message::command:
         //    return e_prototype_updatecommanduserinterface;
         //default:
         //return e_prototype_command;
         //}
         //}
      case e_message_mouse_move:
      case e_message_left_button_down:
      case e_message_left_button_up:
      case e_message_left_button_double_click:
      case e_message_right_button_down:
      case e_message_right_button_up:
      case e_message_right_button_double_click:
      case e_message_middle_button_down:
      case e_message_middle_button_up:
      case e_message_middle_button_double_click:
      case e_message_non_client_mouse_move:
      case e_message_non_client_left_button_down:
      case e_message_non_client_left_button_up:
         return e_prototype_mouse;
      case e_message_mouse_wheel:
         return e_prototype_mouse_wheel;
      case e_message_non_client_activate:
         return e_prototype_non_client_activate;
      case e_message_timer:
         return e_prototype_timer;
      case e_message_key_down:
      case e_message_key_up:
      case e_message_char:
      case e_message_dead_char:
      case e_message_sys_key_down:
      case e_message_sys_key_up:
      case e_message_sys_char:
      case e_message_sys_dead_char:
      case e_message_uni_char:
         return e_prototype_key;
      case e_message_non_client_hit_test:
         return e_prototype_non_client_hit_test;
      case e_message_set_cursor:
         return e_prototype_set_cursor;
      case e_message_erase_background:
         return e_prototype_erase_background;
      case e_message_show_window:
         return e_prototype_show_window;
      case e_message_initialize_menu_popup:
         return e_prototype_init_menu_popup;
      case e_message_enable:
         return e_prototype_enable;
         /*#ifdef windows
         case wm_ctlcolor:
         if(pba)
         return e_prototype_ctlcolor;
         case wm_ctlcolor + wm_reflect_axis:
         return e_prototype_ctlcolorreflect;
         #endif*/
      case e_message_kill_focus:
         return e_prototype_kill_focus;
      case e_message_set_focus:
         return e_prototype_set_focus;
      case e_message_window_position_changing:
      case e_message_window_position_changed:
         return e_prototype_window_pos;
      case e_message_non_client_calc_size:
         return e_prototype_non_client_calc_size;
      case e_message_simple_command:
         return e_prototype_simple_command;
      case e_message_post_user:
         return e_prototype_object;
      case e_message_paint:
         return e_prototype_none;
      default:
         return e_prototype_none;
      }
   }


} // namespace message



