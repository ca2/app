//
// Created by camilo on 2023-10-10 21:56 <3ThomasBorregaardSorensen!!.
//
#include "framework.h"
#include "user_key.h"
#include <array>

#if defined(WINDOWS_DESKTOP)

#ifndef VK_POWER
#define VK_POWER 0x5E
#endif

static std::array<unsigned char, ::user::e_key_count> create_vk_table()
{
   std::array<unsigned char, ::user::e_key_count> a;

      a[::user::e_key_none] = 0;
      a[::user::e_key_refer_to_text_member] = 0;

      a[::user::e_key_0] = '0';
      a[::user::e_key_1] = '1';
      a[::user::e_key_2] = '2';
      a[::user::e_key_3] = '3';
      a[::user::e_key_4] = '4';
      a[::user::e_key_5] = '5';
      a[::user::e_key_6] = '6';
      a[::user::e_key_7] = '7';
      a[::user::e_key_8] = '8';
      a[::user::e_key_9] = '9';

      a[::user::e_key_a] = 'A';
      a[::user::e_key_b] = 'B';
      a[::user::e_key_c] = 'C';
      a[::user::e_key_d] = 'D';
      a[::user::e_key_e] = 'E';
      a[::user::e_key_f] = 'F';
      a[::user::e_key_g] = 'G';
      a[::user::e_key_h] = 'H';
      a[::user::e_key_i] = 'I';
      a[::user::e_key_j] = 'J';
      a[::user::e_key_k] = 'K';
      a[::user::e_key_l] = 'L';
      a[::user::e_key_m] = 'M';
      a[::user::e_key_n] = 'N';
      a[::user::e_key_o] = 'O';
      a[::user::e_key_p] = 'P';
      a[::user::e_key_q] = 'Q';
      a[::user::e_key_r] = 'R';
      a[::user::e_key_s] = 'S';
      a[::user::e_key_t] = 'T';
      a[::user::e_key_u] = 'U';
      a[::user::e_key_v] = 'V';
      a[::user::e_key_w] = 'W';
      a[::user::e_key_x] = 'X';
      a[::user::e_key_y] = 'Y';
      a[::user::e_key_z] = 'Z';

      a[::user::e_key_left_button] = VK_LBUTTON;
      a[::user::e_key_right_button] = VK_RBUTTON;
      a[::user::e_key_middle_button] = VK_MBUTTON;

      a[::user::e_key_cancel] = VK_CANCEL;
      a[::user::e_key_back] = VK_BACK;
      a[::user::e_key_tab] = VK_TAB;
      a[::user::e_key_clear] = VK_CLEAR;
      a[::user::e_key_return] = VK_RETURN;

      a[::user::e_key_shift] = VK_SHIFT;
      a[::user::e_key_left_shift] = VK_LSHIFT;
      a[::user::e_key_right_shift] = VK_RSHIFT;

      a[::user::e_key_control] = VK_CONTROL;
      a[::user::e_key_left_control] = VK_LCONTROL;
      a[::user::e_key_right_control] = VK_RCONTROL;

      a[::user::e_key_alt] = VK_MENU;
      a[::user::e_key_left_alt] = VK_LMENU;
      a[::user::e_key_right_alt] = VK_RMENU;

      a[::user::e_key_pause] = VK_PAUSE;
      a[::user::e_key_capslock] = VK_CAPITAL;
      a[::user::e_key_hangul] = VK_HANGUL;

      a[::user::e_key_escape] = VK_ESCAPE;
      a[::user::e_key_space] = VK_SPACE;

      a[::user::e_key_page_up] = VK_PRIOR;
      a[::user::e_key_page_down] = VK_NEXT;
      a[::user::e_key_end] = VK_END;
      a[::user::e_key_home] = VK_HOME;

      a[::user::e_key_left] = VK_LEFT;
      a[::user::e_key_up] = VK_UP;
      a[::user::e_key_right] = VK_RIGHT;
      a[::user::e_key_down] = VK_DOWN;

      a[::user::e_key_select] = VK_SELECT;
      a[::user::e_key_execute] = VK_EXECUTE;

      a[::user::e_key_print_screen] = VK_SNAPSHOT;
      a[::user::e_key_snapshot] = VK_SNAPSHOT;
      a[::user::e_key_sysreq] = VK_SNAPSHOT;

      a[::user::e_key_insert] = VK_INSERT;
      a[::user::e_key_delete] = VK_DELETE;
      a[::user::e_key_help] = VK_HELP;

      a[::user::e_key_left_gui] = VK_LWIN;
      a[::user::e_key_left_command] = VK_LWIN;
      a[::user::e_key_system_left_command] = VK_LWIN;

      a[::user::e_key_right_gui] = VK_RWIN;
      a[::user::e_key_right_command] = VK_RWIN;
      a[::user::e_key_system_right_command] = VK_RWIN;

      a[::user::e_key_command] = VK_LWIN;
      a[::user::e_key_system_command] = VK_LWIN;

      a[::user::e_key_application] = VK_APPS;
      a[::user::e_key_power] = VK_POWER;
      a[::user::e_key_sleep] = VK_SLEEP;

      a[::user::e_key_numpad_0] = VK_NUMPAD0;
      a[::user::e_key_numpad_1] = VK_NUMPAD1;
      a[::user::e_key_numpad_2] = VK_NUMPAD2;
      a[::user::e_key_numpad_3] = VK_NUMPAD3;
      a[::user::e_key_numpad_4] = VK_NUMPAD4;
      a[::user::e_key_numpad_5] = VK_NUMPAD5;
      a[::user::e_key_numpad_6] = VK_NUMPAD6;
      a[::user::e_key_numpad_7] = VK_NUMPAD7;
      a[::user::e_key_numpad_8] = VK_NUMPAD8;
      a[::user::e_key_numpad_9] = VK_NUMPAD9;

      a[::user::e_key_numpad_multiply] = VK_MULTIPLY;
      a[::user::e_key_numpad_plus] = VK_ADD;
      a[::user::e_key_separator] = VK_SEPARATOR;
      a[::user::e_key_numpad_minus] = VK_SUBTRACT;
      a[::user::e_key_numpad_period] = VK_DECIMAL;
      a[::user::e_key_decimal] = VK_DECIMAL;
      a[::user::e_key_numpad_divide] = VK_DIVIDE;

      a[::user::e_key_f1] = VK_F1;
      a[::user::e_key_f2] = VK_F2;
      a[::user::e_key_f3] = VK_F3;
      a[::user::e_key_f4] = VK_F4;
      a[::user::e_key_f5] = VK_F5;
      a[::user::e_key_f6] = VK_F6;
      a[::user::e_key_f7] = VK_F7;
      a[::user::e_key_f8] = VK_F8;
      a[::user::e_key_f9] = VK_F9;
      a[::user::e_key_f10] = VK_F10;
      a[::user::e_key_f11] = VK_F11;
      a[::user::e_key_f12] = VK_F12;
      a[::user::e_key_f13] = VK_F13;
      a[::user::e_key_f14] = VK_F14;
      a[::user::e_key_f15] = VK_F15;
      a[::user::e_key_f16] = VK_F16;
      a[::user::e_key_f17] = VK_F17;
      a[::user::e_key_f18] = VK_F18;
      a[::user::e_key_f19] = VK_F19;
      a[::user::e_key_f20] = VK_F20;
      a[::user::e_key_f21] = VK_F21;
      a[::user::e_key_f22] = VK_F22;
      a[::user::e_key_f23] = VK_F23;
      a[::user::e_key_f24] = VK_F24;

      a[::user::e_key_numlock_clear] = VK_NUMLOCK;
      a[::user::e_key_numlock] = VK_NUMLOCK;
      a[::user::e_key_scroll_lock] = VK_SCROLL;

      a[::user::e_key_semicolon] = VK_OEM_1;
      a[::user::e_key_plus] = VK_OEM_PLUS;
      a[::user::e_key_plus_oem] = VK_OEM_PLUS;
      a[::user::e_key_equal] = VK_OEM_PLUS;
      a[::user::e_key_comma] = VK_OEM_COMMA;
      a[::user::e_key_minus] = VK_OEM_MINUS;
      a[::user::e_key_minus_oem] = VK_OEM_MINUS;
      a[::user::e_key_hyphen] = VK_OEM_MINUS;
      a[::user::e_key_dot] = VK_OEM_PERIOD;
      a[::user::e_key_period] = VK_OEM_PERIOD;
      a[::user::e_key_slash] = VK_OEM_2;
      a[::user::e_key_til] = VK_OEM_3;
      a[::user::e_key_grave] = VK_OEM_3;
      a[::user::e_key_open_bracket] = VK_OEM_4;
      a[::user::e_key_left_bracket] = VK_OEM_4;
      a[::user::e_key_backslash] = VK_OEM_5;
      a[::user::e_key_close_bracket] = VK_OEM_6;
      a[::user::e_key_right_bracket] = VK_OEM_6;
      a[::user::e_key_apostrophe] = VK_OEM_7;
      a[::user::e_key_non_us_back_slash] = VK_OEM_102;

      a[::user::e_key_ac_back] = VK_BROWSER_BACK;
      a[::user::e_key_ac_forward] = VK_BROWSER_FORWARD;
      a[::user::e_key_ac_refresh] = VK_BROWSER_REFRESH;
      a[::user::e_key_stop] = VK_BROWSER_STOP;
      a[::user::e_key_ac_search] = VK_BROWSER_SEARCH;
      a[::user::e_key_ac_bookmarks] = VK_BROWSER_FAVORITES;
      a[::user::e_key_ac_home] = VK_BROWSER_HOME;

      a[::user::e_key_mute] = VK_VOLUME_MUTE;
      a[::user::e_key_volume_down] = VK_VOLUME_DOWN;
      a[::user::e_key_volume_up] = VK_VOLUME_UP;

      a[::user::e_key_audionext] = VK_MEDIA_NEXT_TRACK;
      a[::user::e_key_audioprev] = VK_MEDIA_PREV_TRACK;
      a[::user::e_key_audiostop] = VK_MEDIA_STOP;
      a[::user::e_key_audioplay] = VK_MEDIA_PLAY_PAUSE;

      a[::user::e_key_mail] = VK_LAUNCH_MAIL;
      a[::user::e_key_media_select] = VK_LAUNCH_MEDIA_SELECT;
      a[::user::e_key_app1] = VK_LAUNCH_APP1;
      a[::user::e_key_app2] = VK_LAUNCH_APP2;

      a[::user::e_key_copy] = VK_OEM_COPY;

   return a;
}



static const auto g_vkcode_from_user_key = create_vk_table();

static std::array<::user::e_key, 256> create_rear_vk_table()
{

   std::array<::user::e_key, 256> a;

   for (::user::e_key ekey = ::user::e_key_none; ekey < ::user::e_key_count; ekey++)
   {

      a[g_vkcode_from_user_key[ekey.m_eenum]] = ekey;

   }

   return a;

}


static const auto g_user_key_from_vkcode = create_rear_vk_table();

::string as_string(const ::user::e_key & ekey)
{

   ::string str;

   switch(ekey.m_eenum)
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


CLASS_DECL_ACME::user::e_key vk_code_to_e_user_key(int iVkCode)
{

   return g_user_key_from_vkcode[iVkCode];

}

CLASS_DECL_ACME ::i32 e_user_key_to_vkcode(const ::user::e_key & euserkey)
{

   return g_vkcode_from_user_key[euserkey.m_eenum];

   //if(euserkey >= ::user::e_key_0 && euserkey <= ::user::e_key_9)
   //{

   //   return 0x30 + (::i32)(euserkey - ::user::e_key_0);

   //}

   //if(euserkey >= ::user::e_key_a && euserkey <= ::user::e_key_z)
   //{

   //   return 0x41 + (::i32)(euserkey - ::user::e_key_a);

   //}

   //if(euserkey >= ::user::e_key_numpad_0 && euserkey <= ::user::e_key_numpad_9)
   //{

   //   return 0x60 + (::i32)(euserkey - ::user::e_key_numpad_0);

   //}

   //if(euserkey >= ::user::e_key_f1 && euserkey <= ::user::e_key_f24)
   //{

   //   return 0x70 + (::i32)(euserkey - ::user::e_key_f1);

   //}

   //switch(euserkey.m_eenum)
   //{
   //   case ::user::e_key_left_button:          return 0x01; // VK_LBUTTON
   //   case ::user::e_key_right_button:         return 0x02; // VK_RBUTTON
   //   case ::user::e_key_cancel:               return 0x03; // VK_CANCEL
   //   case ::user::e_key_middle_button:        return 0x04; // VK_MBUTTON
   //   case ::user::e_key_back:                 return 0x08; // VK_BACK
   //   case ::user::e_key_tab:                  return 0x09; // VK_TAB
   //   case ::user::e_key_clear:                return 0x0c; // VK_CLEAR
   //   case ::user::e_key_return:               return 0x0d; // VK_RETURN
   //   case ::user::e_key_shift:                return 0x10; // VK_SHIFT
   //   case ::user::e_key_control:              return 0x11; // VK_CONTROL
   //   case ::user::e_key_alt:                  return 0x12; // VK_MENU
   //   case ::user::e_key_pause:                return 0x13; // VK_PAUSE
   //   case ::user::e_key_capslock:             return 0x14; // VK_CAPITAL
   //   case ::user::e_key_hangul:               return 0x15; // VK_HANGUL
   //   case ::user::e_key_escape:               return 0x1b; // VK_ESCAPE
   //   case ::user::e_key_mode:                 return 0x1f; // VK_MODECHANGE
   //   case ::user::e_key_space:                return 0x20; // VK_SPACE
   //   case ::user::e_key_page_up:              return 0x21; // VK_PRIOR
   //   case ::user::e_key_page_down:            return 0x22; // VK_NEXT
   //   case ::user::e_key_end:                  return 0x23; // VK_END
   //   case ::user::e_key_home:                 return 0x24; // VK_HOME
   //   case ::user::e_key_left:                 return 0x25; // VK_LEFT
   //   case ::user::e_key_up:                   return 0x26; // VK_UP
   //   case ::user::e_key_right:                return 0x27; // VK_RIGHT
   //   case ::user::e_key_down:                 return 0x28; // VK_DOWN
   //   case ::user::e_key_select:               return 0x29; // VK_SELECT
   //   case ::user::e_key_sysreq:               return 0x2c; // VK_SNAPSHOT
   //   case ::user::e_key_print_screen:         return 0x2c; // VK_SNAPSHOT
   //   case ::user::e_key_snapshot:             return 0x2c; // VK_SNAPSHOT
   //   case ::user::e_key_insert:               return 0x2d; // VK_INSERT
   //   case ::user::e_key_delete:               return 0x2e; // VK_DELETE
   //   case ::user::e_key_help:                 return 0x2f; // VK_HELP
   //   case ::user::e_key_left_gui:             return 0x5b; // VK_LWIN
   //   case ::user::e_key_left_command:         return 0x5b; // VK_LWIN
   //   case ::user::e_key_system_left_command:  return 0x5b; // VK_LWIN
   //   case ::user::e_key_right_gui:            return 0x5c; // VK_RWIN
   //   case ::user::e_key_right_command:        return 0x5c; // VK_RWIN
   //   case ::user::e_key_system_right_command: return 0x5c; // VK_RWIN
   //   case ::user::e_key_command:              return 0x5b; // VK_LWIN
   //   case ::user::e_key_system_command:       return 0x5b; // VK_LWIN
   //   case ::user::e_key_application:          return 0x5d; // VK_APPS
   //   case ::user::e_key_power:                return 0x5e; // VK_POWER
   //   case ::user::e_key_sleep:                return 0x5f; // VK_SLEEP
   //   case ::user::e_key_numpad_multiply:      return 0x6a; // VK_MULTIPLY
   //   case ::user::e_key_numpad_plus:          return 0x6b; // VK_ADD
   //   case ::user::e_key_separator:            return 0x6c; // VK_SEPARATOR
   //   case ::user::e_key_numpad_minus:         return 0x6d; // VK_SUBTRACT
   //   case ::user::e_key_numpad_period:        return 0x6e; // VK_DECIMAL
   //   case ::user::e_key_decimal:              return 0x6e; // VK_DECIMAL
   //   case ::user::e_key_numpad_divide:        return 0x6f; // VK_DIVIDE
   //   case ::user::e_key_numlock_clear:        return 0x90; // VK_NUMLOCK
   //   case ::user::e_key_numlock:              return 0x90; // VK_NUMLOCK
   //   case ::user::e_key_scroll_lock:          return 0x91; // VK_SCROLL
   //   case ::user::e_key_numpad_equal:         return 0x92; // VK_OEM_NEC_EQUAL
   //   case ::user::e_key_left_shift:           return 0xa0; // VK_LSHIFT
   //   case ::user::e_key_right_shift:          return 0xa1; // VK_RSHIFT
   //   case ::user::e_key_left_control:         return 0xa2; // VK_LCONTROL
   //   case ::user::e_key_right_control:        return 0xa3; // VK_RCONTROL
   //   case ::user::e_key_left_alt:             return 0xa4; // VK_LMENU
   //   case ::user::e_key_right_alt:            return 0xa5; // VK_RMENU
   //   case ::user::e_key_ac_back:              return 0xa6; // VK_BROWSER_BACK
   //   case ::user::e_key_ac_forward:           return 0xa7; // VK_BROWSER_FORWARD
   //   case ::user::e_key_ac_refresh:           return 0xa8; // VK_BROWSER_REFRESH
   //   case ::user::e_key_stop:                 return 0xa9; // VK_BROWSER_STOP
   //   case ::user::e_key_ac_search:            return 0xaa; // VK_BROWSER_SEARCH
   //   case ::user::e_key_ac_bookmarks:         return 0xab; // VK_BROWSER_FAVORITES
   //   case ::user::e_key_ac_home:              return 0xac; // VK_BROWSER_HOME
   //   case ::user::e_key_mute:                 return 0xad; // VK_VOLUME_MUTE
   //   case ::user::e_key_volume_down:          return 0xae; // VK_VOLUME_DOWN
   //   case ::user::e_key_volume_up:            return 0xaf; // VK_VOLUME_UP
   //   case ::user::e_key_audionext:            return 0xb0; // VK_MEDIA_NEXT_TRACK
   //   case ::user::e_key_audioprev:            return 0xb1; // VK_MEDIA_PREV_TRACK
   //   case ::user::e_key_audiostop:            return 0xb2; // VK_MEDIA_STOP
   //   case ::user::e_key_audioplay:            return 0xb3; // VK_MEDIA_PLAY_PAUSE
   //   case ::user::e_key_mail:                 return 0xb4; // VK_LAUNCH_MAIL
   //   case ::user::e_key_media_select:         return 0xb5; // VK_LAUNCH_MEDIA_SELECT
   //   case ::user::e_key_app1:                 return 0xb6; // VK_LAUNCH_APP1
   //   case ::user::e_key_app2:                 return 0xb7; // VK_LAUNCH_APP2
   //   case ::user::e_key_semicolon:            return 0xba; // VK_OEM_1
   //   case ::user::e_key_plus:                 return 0xbb; // VK_OEM_PLUS
   //   case ::user::e_key_plus_oem:             return 0xbb; // VK_OEM_PLUS
   //   case ::user::e_key_equal:                return 0xbb; // VK_OEM_PLUS
   //   case ::user::e_key_comma:                return 0xbc; // VK_OEM_COMMA
   //   case ::user::e_key_minus:                return 0xbd; // VK_OEM_MINUS
   //   case ::user::e_key_minus_oem:            return 0xbd; // VK_OEM_MINUS
   //   case ::user::e_key_hyphen:               return 0xbd; // VK_OEM_MINUS
   //   case ::user::e_key_dot:                  return 0xbe; // VK_OEM_PERIOD
   //   case ::user::e_key_period:               return 0xbe; // VK_OEM_PERIOD
   //   case ::user::e_key_slash:                return 0xbf; // VK_OEM_2
   //   case ::user::e_key_til:                  return 0xc0; // VK_OEM_3
   //   case ::user::e_key_grave:                return 0xc0; // VK_OEM_3
   //   case ::user::e_key_open_bracket:         return 0xdb; // VK_OEM_4
   //   case ::user::e_key_left_bracket:         return 0xdb; // VK_OEM_4
   //   case ::user::e_key_backslash:            return 0xdc; // VK_OEM_5
   //   case ::user::e_key_close_bracket:        return 0xdd; // VK_OEM_6
   //   case ::user::e_key_right_bracket:        return 0xdd; // VK_OEM_6
   //   case ::user::e_key_apostrophe:           return 0xde; // VK_OEM_7
   //   case ::user::e_key_non_us_back_slash:    return 0xe2; // VK_OEM_102
   //   case ::user::e_key_copy:                 return 0xf2; // VK_OEM_COPY
   //   case ::user::e_key_execute:              return 0x2b; // VK_EXECUTE
   //   case ::user::e_key_none:
   //   case ::user::e_key_refer_to_text_member:
   //   default:
   //      return 0;
   //}

}


#endif
