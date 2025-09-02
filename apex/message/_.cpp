#include "framework.h"
#include "acme/constant/user_message.h"
#include "acme/constant/user_message_prototype.h"
#include "acme/operating_system/message.h"
#include "apex/user/user/message.h"


//#include "acme/operating_system/cross/windows/_windows.h"


namespace message
{


//   class ::channel * CreateSignal()
//   {
//      return ___new class ::channel ();
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

      // redundant ::user::e_message_mouse_move and ::user::e_message_non_client_mouse_move
      if(pmessage->m_eusermessage == ::user::e_message_mouse_move || pmessage->m_eusermessage == ::user::e_message_non_client_mouse_move)
      {

         return true;

      }

      // ::user::e_message_paint and WM_SYSTIMER (caret blink)
      return pmessage->m_eusermessage != ::user::e_message_paint && pmessage->m_eusermessage != 0x0118;

   }



   CLASS_DECL_APEX bool is_idle_message(MESSAGE * pmsg)
   {

      // Return false if the message just dispatched should _not_
      // cause on_idle to be run.  Messages which do not usually
      // affect the state of the ::account::user interface and happen very
      // often are checked for.

      if(pmsg == nullptr)

         return false;

      // redundant ::user::e_message_mouse_move and ::user::e_message_non_client_mouse_move
      if(pmsg->m_eusermessage == ::user::e_message_mouse_move || pmsg->m_eusermessage == ::user::e_message_non_client_mouse_move)

      {
         return true;
      }

      // ::user::e_message_paint and WM_SYSTIMER (caret blink)
      return pmsg->m_eusermessage != ::user::e_message_paint && pmsg->m_eusermessage != 0x0118;

   }


//   unsigned int translate_to_os_message(const ::atom & atom)
//   {
//
////#ifdef WINDOWS
////
////      if (atom.m_etype == ::atom::e_type_message)
////      {
////
////         return (unsigned int) atom.m_emessage;
////
////      }
////
////#elif defined(LINUX) ||  defined(__APPLE__) || defined(__ANDROID__)
////      switch (emessage)
////      {
////      case ::user::e_message_create:
////         return ::user::e_message_create;
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


} // namespace message


namespace user
{

   ::user::enum_message_prototype get_message_prototype(::user::enum_message emessage, unsigned int /* uCode */)
   {

      switch (emessage)
      {
         case ::user::e_message_size:
            return ::user::e_message_prototype_size;
         case ::user::e_message_scroll_x:
         case ::user::e_message_scroll_y:
            return ::user::e_message_prototype_scroll;
         case ::user::e_message_create:
         case ::user::e_message_non_client_create:
            return ::user::e_message_prototype_create;
         case ::user::e_message_reposition:
            return ::user::e_message_prototype_move;
         case ::user::e_message_activate:
            return ::user::e_message_prototype_activate;
         case ::user::e_message_mouse_activate:
            return ::user::e_message_prototype_mouse_activate;
         case ::user::e_message_measure_item:
            return ::user::e_message_prototype_measure_item;
         case ::user::e_message_wm_notify:
            return ::user::e_message_prototype_notify;
         case ::user::e_message_command:
            return ::user::e_message_prototype_command;
            //{
            // switch (uicode)
            //{
            // case cn_update_::message::command:
            //    return ::user::e_message_prototype_updatecommanduserinterface;
            // default:
            // return ::user::e_message_prototype_command;
            //}
            //}
         case ::user::e_message_mouse_move:
         case ::user::e_message_left_button_down:
         case ::user::e_message_left_button_up:
         case ::user::e_message_left_button_double_click:
         case ::user::e_message_right_button_down:
         case ::user::e_message_right_button_up:
         case ::user::e_message_right_button_double_click:
         case ::user::e_message_middle_button_down:
         case ::user::e_message_middle_button_up:
         case ::user::e_message_middle_button_double_click:
         case ::user::e_message_non_client_mouse_move:
         case ::user::e_message_non_client_left_button_down:
         case ::user::e_message_non_client_left_button_up:
            return ::user::e_message_prototype_mouse;
         case ::user::e_message_mouse_wheel:
            return ::user::e_message_prototype_mouse_wheel;
         case ::user::e_message_non_client_activate:
            return ::user::e_message_prototype_non_client_activate;
         case ::user::e_message_timer:
            return ::user::e_message_prototype_timer;
         case ::user::e_message_key_down:
         case ::user::e_message_key_up:
         case ::user::e_message_char:
         case ::user::e_message_dead_char:
         case ::user::e_message_sys_key_down:
         case ::user::e_message_sys_key_up:
         case ::user::e_message_sys_char:
         case ::user::e_message_sys_dead_char:
         case ::user::e_message_uni_char:
            return ::user::e_message_prototype_key;
         case ::user::e_message_non_client_hit_test:
            return ::user::e_message_prototype_non_client_hit_test;
         case ::user::e_message_set_cursor:
            return ::user::e_message_prototype_set_cursor;
         case ::user::e_message_erase_background:
            return ::user::e_message_prototype_erase_background;
         case ::user::e_message_show_window:
            return ::user::e_message_prototype_show_window;
         case ::user::e_message_initialize_menu_popup:
            return ::user::e_message_prototype_init_menu_popup;
         case ::user::e_message_enable:
            return ::user::e_message_prototype_enable;
            /*#ifdef windows
            case wm_ctlcolor:
            if(pba)
            return ::user::e_message_prototype_ctlcolor;
            case wm_ctlcolor + wm_reflect_axis:
            return ::user::e_message_prototype_ctlcolorreflect;
            #endif*/
         case ::user::e_message_kill_focus:
            return ::user::e_message_prototype_kill_focus;
         case ::user::e_message_set_focus:
            return ::user::e_message_prototype_set_focus;
         case ::user::e_message_window_position_changing:
         case ::user::e_message_window_position_changed:
            return ::user::e_message_prototype_window_pos;
         case ::user::e_message_non_client_calc_size:
            return ::user::e_message_prototype_non_client_calc_size;
         case ::user::e_message_simple_command:
            return ::user::e_message_prototype_simple_command;
         case ::user::e_message_post_user:
            return ::user::e_message_prototype_object;
         case ::user::e_message_paint:
            return ::user::e_message_prototype_none;
         default:
            return ::user::e_message_prototype_none;
      }
   
   
   }


} // namespace user





