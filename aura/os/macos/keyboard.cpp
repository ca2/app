//
//  keyboard.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 01/06/20.
//

#include "framework.h"


namespace user
{

   CLASS_DECL_AURA ::user::enum_key vkcode_to_userkey(wparam wparam)
   {

      iptr vkcode = (iptr)wparam;
      
      switch(vkcode)
      {
            case kVK_ANSI_0:
               return ::user::e_key_0;
            case kVK_ANSI_1:
               return ::user::e_key_1;
            case kVK_ANSI_2:
               return ::user::e_key_2;
            case kVK_ANSI_3:
               return ::user::e_key_3;
            case kVK_ANSI_4:
               return ::user::e_key_4;
            case kVK_ANSI_5:
               return ::user::e_key_5;
            case kVK_ANSI_6:
               return ::user::e_key_6;
            case kVK_ANSI_7:
               return ::user::e_key_7;
            case kVK_ANSI_8:
               return ::user::e_key_8;
            case kVK_ANSI_9:
               return ::user::e_key_9;
            case kVK_ANSI_A:
               return ::user::e_key_a;
            case kVK_ANSI_B:
               return ::user::e_key_b;
            case kVK_ANSI_C:
               return ::user::e_key_c;
            case kVK_ANSI_D:
               return ::user::e_key_d;
            case kVK_ANSI_E:
               return ::user::e_key_e;
            case kVK_ANSI_F:
               return ::user::e_key_f;
            case kVK_ANSI_G:
               return ::user::e_key_g;
            case kVK_ANSI_H:
               return ::user::e_key_h;
            case kVK_ANSI_I:
               return ::user::e_key_i;
            case kVK_ANSI_J:
               return ::user::e_key_j;
            case kVK_ANSI_K:
               return ::user::e_key_k;
            case kVK_ANSI_L:
               return ::user::e_key_l;
            case kVK_ANSI_M:
               return ::user::e_key_m;
            case kVK_ANSI_N:
               return ::user::e_key_n;
            case kVK_ANSI_O:
               return ::user::e_key_o;
            case kVK_ANSI_P:
               return ::user::e_key_p;
            case kVK_ANSI_Q:
               return ::user::e_key_q;
            case kVK_ANSI_R:
               return ::user::e_key_r;
            case kVK_ANSI_S:
               return ::user::e_key_s;
            case kVK_ANSI_T:
               return ::user::e_key_t;
            case kVK_ANSI_U:
               return ::user::e_key_u;
            case kVK_ANSI_V:
               return ::user::e_key_v;
            case kVK_ANSI_W:
               return ::user::e_key_w;
            case kVK_ANSI_X:
               return ::user::e_key_x;
            case kVK_ANSI_Y:
               return ::user::e_key_y;
            case kVK_ANSI_Z:
               return ::user::e_key_z;

      case kVK_Delete:
         return ::user::e_key_back;
      case kVK_Shift:
         return ::user::e_key_lshift;
      case kVK_RightShift:
         return ::user::e_key_rshift;
      case kVK_Control:
         return ::user::e_key_lcontrol;
      case kVK_RightControl:
         return ::user::e_key_rcontrol;
      case kVK_Option:
         return ::user::e_key_lalt;
      case kVK_RightOption:
         return ::user::e_key_ralt;
      case kVK_ForwardDelete:
         return ::user::e_key_delete;
      case kVK_Return:
         return ::user::e_key_return;
      case kVK_Tab:
         return ::user::e_key_tab;
      case kVK_LeftArrow:
         return ::user::e_key_left;
      case kVK_RightArrow:
         return ::user::e_key_right;
      case kVK_UpArrow:
         return ::user::e_key_up;
      case kVK_DownArrow:
         return ::user::e_key_down;
      case kVK_PageUp:
         return ::user::e_key_prior;
      case kVK_PageDown:
         return ::user::e_key_next;
      case kVK_Home:
         return ::user::e_key_home;
      case kVK_End:
         return ::user::e_key_end;
      case kVK_Command:
         return ::user::e_key_lcommand;
      case kVK_RightCommand:
         return ::user::e_key_rcommand;


      }

      return ::user::e_key_none;

   }


} // namespace user
