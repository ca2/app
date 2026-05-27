//
// Created by camilo on 2023-10-10 21:56 <3ThomasBorregaardSorensen!!.
//
#include "framework.h"
#include "user_key.h"


::string as_string(::user::enum_key ekey)
{

   ::string str;

   switch(ekey)
   {
      case ::user::e_key_back:       str = "user::e_key_back"; break;
      case ::user::e_key_return:       str = "user::e_key_return"; break;
      case ::user::e_key_down:       str = "user::e_key_down"; break;
      case ::user::e_key_left:       str = "user::e_key_left"; break;
      case ::user::e_key_right:       str = "user::e_key_right"; break;
      case ::user::e_key_up:       str = "user::e_key_up"; break;
      case ::user::e_key_home:     str = "user::e_key_home"; break;
      case ::user::e_key_end:     str = "user::e_key_end"; break;
      case ::user::e_key_page_down:     str = "user::e_key_page_down"; break;
      case ::user::e_key_page_up:     str = "user::e_key_page_up"; break;
      default:
         str.formatf("%d", (::i32)ekey);

   }

   return str;

}


::i32 e_user_key_to_vkcode(::user::enum_key euserkey)
{

   if(euserkey >= ::user::e_key_0 && euserkey <= ::user::e_key_9)
   {

      return 0x30 + (::i32)(euserkey - ::user::e_key_0);

   }

   if(euserkey >= ::user::e_key_a && euserkey <= ::user::e_key_z)
   {

      return 0x41 + (::i32)(euserkey - ::user::e_key_a);

   }

   if(euserkey >= ::user::e_key_numpad_0 && euserkey <= ::user::e_key_numpad_9)
   {

      return 0x60 + (::i32)(euserkey - ::user::e_key_numpad_0);

   }

   if(euserkey >= ::user::e_key_f1 && euserkey <= ::user::e_key_f24)
   {

      return 0x70 + (::i32)(euserkey - ::user::e_key_f1);

   }

   switch(euserkey)
   {
      case ::user::e_key_left_button:          return 0x01; // VK_LBUTTON
      case ::user::e_key_right_button:         return 0x02; // VK_RBUTTON
      case ::user::e_key_cancel:               return 0x03; // VK_CANCEL
      case ::user::e_key_middle_button:        return 0x04; // VK_MBUTTON
      case ::user::e_key_back:                 return 0x08; // VK_BACK
      case ::user::e_key_tab:                  return 0x09; // VK_TAB
      case ::user::e_key_clear:                return 0x0c; // VK_CLEAR
      case ::user::e_key_return:               return 0x0d; // VK_RETURN
      case ::user::e_key_shift:                return 0x10; // VK_SHIFT
      case ::user::e_key_control:              return 0x11; // VK_CONTROL
      case ::user::e_key_alt:                  return 0x12; // VK_MENU
      case ::user::e_key_pause:                return 0x13; // VK_PAUSE
      case ::user::e_key_capslock:             return 0x14; // VK_CAPITAL
      case ::user::e_key_hangul:               return 0x15; // VK_HANGUL
      case ::user::e_key_escape:               return 0x1b; // VK_ESCAPE
      case ::user::e_key_mode:                 return 0x1f; // VK_MODECHANGE
      case ::user::e_key_space:                return 0x20; // VK_SPACE
      case ::user::e_key_page_up:              return 0x21; // VK_PRIOR
      case ::user::e_key_page_down:            return 0x22; // VK_NEXT
      case ::user::e_key_end:                  return 0x23; // VK_END
      case ::user::e_key_home:                 return 0x24; // VK_HOME
      case ::user::e_key_left:                 return 0x25; // VK_LEFT
      case ::user::e_key_up:                   return 0x26; // VK_UP
      case ::user::e_key_right:                return 0x27; // VK_RIGHT
      case ::user::e_key_down:                 return 0x28; // VK_DOWN
      case ::user::e_key_select:               return 0x29; // VK_SELECT
      case ::user::e_key_sysreq:               return 0x2c; // VK_SNAPSHOT
      case ::user::e_key_print_screen:         return 0x2c; // VK_SNAPSHOT
      case ::user::e_key_snapshot:             return 0x2c; // VK_SNAPSHOT
      case ::user::e_key_insert:               return 0x2d; // VK_INSERT
      case ::user::e_key_delete:               return 0x2e; // VK_DELETE
      case ::user::e_key_help:                 return 0x2f; // VK_HELP
      case ::user::e_key_left_gui:             return 0x5b; // VK_LWIN
      case ::user::e_key_left_command:         return 0x5b; // VK_LWIN
      case ::user::e_key_system_left_command:  return 0x5b; // VK_LWIN
      case ::user::e_key_right_gui:            return 0x5c; // VK_RWIN
      case ::user::e_key_right_command:        return 0x5c; // VK_RWIN
      case ::user::e_key_system_right_command: return 0x5c; // VK_RWIN
      case ::user::e_key_command:              return 0x5b; // VK_LWIN
      case ::user::e_key_system_command:       return 0x5b; // VK_LWIN
      case ::user::e_key_application:          return 0x5d; // VK_APPS
      case ::user::e_key_power:                return 0x5e; // VK_POWER
      case ::user::e_key_sleep:                return 0x5f; // VK_SLEEP
      case ::user::e_key_numpad_multiply:      return 0x6a; // VK_MULTIPLY
      case ::user::e_key_numpad_plus:          return 0x6b; // VK_ADD
      case ::user::e_key_separator:            return 0x6c; // VK_SEPARATOR
      case ::user::e_key_numpad_minus:         return 0x6d; // VK_SUBTRACT
      case ::user::e_key_numpad_period:        return 0x6e; // VK_DECIMAL
      case ::user::e_key_decimal:              return 0x6e; // VK_DECIMAL
      case ::user::e_key_numpad_divide:        return 0x6f; // VK_DIVIDE
      case ::user::e_key_numlock_clear:        return 0x90; // VK_NUMLOCK
      case ::user::e_key_numlock:              return 0x90; // VK_NUMLOCK
      case ::user::e_key_scroll_lock:          return 0x91; // VK_SCROLL
      case ::user::e_key_numpad_equal:         return 0x92; // VK_OEM_NEC_EQUAL
      case ::user::e_key_left_shift:           return 0xa0; // VK_LSHIFT
      case ::user::e_key_right_shift:          return 0xa1; // VK_RSHIFT
      case ::user::e_key_left_control:         return 0xa2; // VK_LCONTROL
      case ::user::e_key_right_control:        return 0xa3; // VK_RCONTROL
      case ::user::e_key_left_alt:             return 0xa4; // VK_LMENU
      case ::user::e_key_right_alt:            return 0xa5; // VK_RMENU
      case ::user::e_key_ac_back:              return 0xa6; // VK_BROWSER_BACK
      case ::user::e_key_ac_forward:           return 0xa7; // VK_BROWSER_FORWARD
      case ::user::e_key_ac_refresh:           return 0xa8; // VK_BROWSER_REFRESH
      case ::user::e_key_stop:                 return 0xa9; // VK_BROWSER_STOP
      case ::user::e_key_ac_search:            return 0xaa; // VK_BROWSER_SEARCH
      case ::user::e_key_ac_bookmarks:         return 0xab; // VK_BROWSER_FAVORITES
      case ::user::e_key_ac_home:              return 0xac; // VK_BROWSER_HOME
      case ::user::e_key_mute:                 return 0xad; // VK_VOLUME_MUTE
      case ::user::e_key_volume_down:          return 0xae; // VK_VOLUME_DOWN
      case ::user::e_key_volume_up:            return 0xaf; // VK_VOLUME_UP
      case ::user::e_key_audionext:            return 0xb0; // VK_MEDIA_NEXT_TRACK
      case ::user::e_key_audioprev:            return 0xb1; // VK_MEDIA_PREV_TRACK
      case ::user::e_key_audiostop:            return 0xb2; // VK_MEDIA_STOP
      case ::user::e_key_audioplay:            return 0xb3; // VK_MEDIA_PLAY_PAUSE
      case ::user::e_key_mail:                 return 0xb4; // VK_LAUNCH_MAIL
      case ::user::e_key_media_select:         return 0xb5; // VK_LAUNCH_MEDIA_SELECT
      case ::user::e_key_app1:                 return 0xb6; // VK_LAUNCH_APP1
      case ::user::e_key_app2:                 return 0xb7; // VK_LAUNCH_APP2
      case ::user::e_key_semicolon:            return 0xba; // VK_OEM_1
      case ::user::e_key_plus:                 return 0xbb; // VK_OEM_PLUS
      case ::user::e_key_plus_oem:             return 0xbb; // VK_OEM_PLUS
      case ::user::e_key_equal:                return 0xbb; // VK_OEM_PLUS
      case ::user::e_key_comma:                return 0xbc; // VK_OEM_COMMA
      case ::user::e_key_minus:                return 0xbd; // VK_OEM_MINUS
      case ::user::e_key_minus_oem:            return 0xbd; // VK_OEM_MINUS
      case ::user::e_key_hyphen:               return 0xbd; // VK_OEM_MINUS
      case ::user::e_key_dot:                  return 0xbe; // VK_OEM_PERIOD
      case ::user::e_key_period:               return 0xbe; // VK_OEM_PERIOD
      case ::user::e_key_slash:                return 0xbf; // VK_OEM_2
      case ::user::e_key_til:                  return 0xc0; // VK_OEM_3
      case ::user::e_key_grave:                return 0xc0; // VK_OEM_3
      case ::user::e_key_open_bracket:         return 0xdb; // VK_OEM_4
      case ::user::e_key_left_bracket:         return 0xdb; // VK_OEM_4
      case ::user::e_key_backslash:            return 0xdc; // VK_OEM_5
      case ::user::e_key_close_bracket:        return 0xdd; // VK_OEM_6
      case ::user::e_key_right_bracket:        return 0xdd; // VK_OEM_6
      case ::user::e_key_apostrophe:           return 0xde; // VK_OEM_7
      case ::user::e_key_non_us_back_slash:    return 0xe2; // VK_OEM_102
      case ::user::e_key_copy:                 return 0xf2; // VK_OEM_COPY
      case ::user::e_key_execute:              return 0x2b; // VK_EXECUTE
      case ::user::e_key_none:
      case ::user::e_key_refer_to_text_member:
      default:
         return 0;
   }

}
