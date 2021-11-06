if(pkey->m_uiMessage == e_message_key_down ||
   pkey->m_uiMessage == e_message_key_up)
{

   switch(pkey->m_nChar)
   {
   case 'a':
   case 'A':
      pkey->m_ekey = ::user::e_key_a;
      break;
   case 'b':
   case 'B':
      pkey->m_ekey = ::user::e_key_b;
      break;
   case 'c':
   case 'C':
      pkey->m_ekey = ::user::e_key_c;
      break;
   case 'd':
   case 'D':
      pkey->m_ekey = ::user::e_key_d;
      break;
   case 'e':
   case 'E':
      pkey->m_ekey = ::user::e_key_e;
      break;
   case 'f':
   case 'F':
      pkey->m_ekey = ::user::e_key_f;
      break;
   case 'g':
   case 'G':
      pkey->m_ekey = ::user::e_key_g;
      break;
   case 'h':
   case 'H':
      pkey->m_ekey = ::user::e_key_h;
      break;
   case 'i':
   case 'I':
      pkey->m_ekey = ::user::e_key_i;
      break;
   case 'j':
   case 'J':
      pkey->m_ekey = ::user::e_key_j;
      break;
   case 'k':
   case 'K':
      pkey->m_ekey = ::user::e_key_k;
      break;
   case 'l':
   case 'L':
      pkey->m_ekey = ::user::e_key_l;
      break;
   case 'm':
   case 'M':
      pkey->m_ekey = ::user::e_key_m;
      break;
   case 'n':
   case 'N':
      pkey->m_ekey = ::user::e_key_n;
      break;
   case 'o':
   case 'O':
      pkey->m_ekey = ::user::e_key_o;
      break;
   case 'p':
   case 'P':
      pkey->m_ekey = ::user::e_key_p;
      break;
   case 'q':
   case 'Q':
      pkey->m_ekey = ::user::e_key_q;
      break;
   case 'r':
   case 'R':
      pkey->m_ekey = ::user::e_key_r;
      break;
   case 's':
   case 'S':
      pkey->m_ekey = ::user::e_key_s;
      break;
   case 't':
   case 'T':
      pkey->m_ekey = ::user::e_key_t;
      break;
   case 'u':
   case 'U':
      pkey->m_ekey = ::user::e_key_u;
      break;
   case 'v':
   case 'V':
      pkey->m_ekey = ::user::e_key_v;
      break;
   case 'w':
   case 'W':
      pkey->m_ekey = ::user::e_key_w;
      break;
   case 'x':
   case 'X':
      pkey->m_ekey = ::user::e_key_x;
      break;
   case 'y':
   case 'Y':
      pkey->m_ekey = ::user::e_key_y;
      break;
   case 'z':
   case 'Z':
      pkey->m_ekey = ::user::e_key_z;
      break;
   case '0':
      pkey->m_ekey = ::user::e_key_0;
      break;
   case '1':
      pkey->m_ekey = ::user::e_key_1;
      break;
   case '2':
      pkey->m_ekey = ::user::e_key_2;
      break;
   case '3':
      pkey->m_ekey = ::user::e_key_3;
      break;
   case '4':
      pkey->m_ekey = ::user::e_key_4;
      break;
   case '5':
      pkey->m_ekey = ::user::e_key_5;
      break;
   case '6':
      pkey->m_ekey = ::user::e_key_6;
      break;
   case '7':
      pkey->m_ekey = ::user::e_key_7;
      break;
   case '8':
      pkey->m_ekey = ::user::e_key_8;
      break;
   case '9':
      pkey->m_ekey = ::user::e_key_9;
      break;
   case VK_SHIFT:
      pkey->m_ekey = ::user::e_key_shift;
      break;
   case VK_MENU:
      pkey->m_ekey = ::user::e_key_alt;
      break;
   case VK_CONTROL:
      pkey->m_ekey = ::user::e_key_control;
      break;
   case VK_DELETE:
      pkey->m_ekey = ::user::e_key_delete;
      break;
   case VK_BACK:
      pkey->m_ekey = ::user::e_key_back;
      break;
   case VK_UP:
      pkey->m_ekey = ::user::e_key_up;
      break;
   case VK_DOWN:
      pkey->m_ekey = ::user::e_key_down;
      break;
   case VK_RIGHT:
      pkey->m_ekey = ::user::e_key_right;
      break;
   case VK_LEFT:
      pkey->m_ekey = ::user::e_key_left;
      break;
   case VK_OEM_PERIOD:
      pkey->m_ekey = ::user::e_key_dot;
      break;
   case VK_OEM_COMMA:
      pkey->m_ekey = ::user::e_key_comma;
      break;
   case VK_OEM_MINUS:
      pkey->m_ekey = ::user::e_key_hyphen;
      break;
   case VK_RETURN:
      pkey->m_ekey = ::user::e_key_return;
      break;
   case VK_TAB:
      pkey->m_ekey = ::user::e_key_tab;
      break;
   case VK_SPACE:
      pkey->m_ekey = ::user::e_key_space;
      break;
   default:
      pkey->m_ekey = m_mapKey[(i32)pkey->m_nChar];
      break;
   }

   return;

}
