//
//  keyboard.cpp
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 01/06/20.
//

#include "framework.h"


namespace user
{

   CLASS_DECL_ACME ::user::enum_key vkcode_to_userkey(WPARAM wparam)
   {

      iptr vkcode = (iptr)wparam;
      
      switch(vkcode)
      {
            case kVK_ANSI_0:
               return key_0;
            case kVK_ANSI_1:
               return key_1;
            case kVK_ANSI_2:
               return key_2;
            case kVK_ANSI_3:
               return key_3;
            case kVK_ANSI_4:
               return key_4;
            case kVK_ANSI_5:
               return key_5;
            case kVK_ANSI_6:
               return key_6;
            case kVK_ANSI_7:
               return key_7;
            case kVK_ANSI_8:
               return key_8;
            case kVK_ANSI_9:
               return key_9;
            case kVK_ANSI_A:
               return key_a;
            case kVK_ANSI_B:
               return key_b;
            case kVK_ANSI_C:
               return key_c;
            case kVK_ANSI_D:
               return key_d;
            case kVK_ANSI_E:
               return key_e;
            case kVK_ANSI_F:
               return key_f;
            case kVK_ANSI_G:
               return key_g;
            case kVK_ANSI_H:
               return key_h;
            case kVK_ANSI_I:
               return key_i;
            case kVK_ANSI_J:
               return key_j;
            case kVK_ANSI_K:
               return key_k;
            case kVK_ANSI_L:
               return key_l;
            case kVK_ANSI_M:
               return key_m;
            case kVK_ANSI_N:
               return key_n;
            case kVK_ANSI_O:
               return key_o;
            case kVK_ANSI_P:
               return key_p;
            case kVK_ANSI_Q:
               return key_q;
            case kVK_ANSI_R:
               return key_r;
            case kVK_ANSI_S:
               return key_s;
            case kVK_ANSI_T:
               return key_t;
            case kVK_ANSI_U:
               return key_u;
            case kVK_ANSI_V:
               return key_v;
            case kVK_ANSI_W:
               return key_w;
            case kVK_ANSI_X:
               return key_x;
            case kVK_ANSI_Y:
               return key_y;
            case kVK_ANSI_Z:
               return key_z;

      case kVK_Delete:
         return key_back;
      case kVK_Shift:
         return key_lshift;
      case kVK_RightShift:
         return key_rshift;
      case kVK_Control:
         return key_lcontrol;
      case kVK_RightControl:
         return key_rcontrol;
      case kVK_Option:
         return key_lalt;
      case kVK_RightOption:
         return key_ralt;
      case kVK_ForwardDelete:
         return key_delete;
      case kVK_Return:
         return key_return;
      case kVK_Tab:
         return key_tab;
      case kVK_LeftArrow:
         return key_left;
      case kVK_RightArrow:
         return key_right;
      case kVK_UpArrow:
         return key_up;
      case kVK_DownArrow:
         return key_down;
      case kVK_PageUp:
         return key_prior;
      case kVK_PageDown:
         return key_next;
      case kVK_Home:
         return key_home;
      case kVK_End:
         return key_end;
      case kVK_Command:
         return key_lcommand;
      case kVK_RightCommand:
         return key_rcommand;


      }

      return key_none;

   }


} // namespace user
