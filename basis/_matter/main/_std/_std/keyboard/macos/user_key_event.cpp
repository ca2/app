if([event modifierFlags] & NSNumericPadKeyMask) // arrow keys have this mask
{
   
   NSString * arrow = [event charactersIgnoringModifiers];
   
   unichar key = 0;
   
   if([arrow length] == 0)
      return ::user::key_none;            // reject dead keys
   
   if([arrow length] == 1)
   {
      
      key = [arrow characterAtIndex:0];
      
      if(key == NSLeftArrowFunctionKey)
      {
         
         return 1002; //::user::key_left;
         
      }
      
      if(key == NSRightArrowFunctionKey)
      {
         
         return 1004; //::user::key_right;
         
      }
      
      if(key == NSUpArrowFunctionKey)
      {
         
         return 1003; // ::user::key_up;
         
      }
      
      if(key == NSDownArrowFunctionKey)
      {
         
         return 1005; // ::user::key_down;
         
      }
      
   }
   
}
else
{
   
   unsigned short ush = [event keyCode];
   
   return ush;
   
   if(ush == 12)
   {
      return ::user::key_q;
   }
   else if(ush == 13)
   {
      return ::user::key_w;
   }
   else if(ush == 14)
   {
      return ::user::key_e;
   }
   else if(ush == 15)
   {
      return ::user::key_r;
   }
   else if(ush == 17)
   {
      return ::user::key_t;
   }
   else if(ush == 16)
   {
      return ::user::key_y;
   }
   else if(ush == 32)
   {
      return ::user::key_u;
   }
   else if(ush == 34)
   {
      return ::user::key_i;
   }
   else if(ush == 31)
   {
      return ::user::key_o;
   }
   else if(ush == 35)
   {
      return ::user::key_p;
   }
   else if(ush == 0)
   {
      return ::user::key_a;
   }
   else if(ush == 1)
   {
      return ::user::key_s;
   }
   else if(ush == 2)
   {
      return ::user::key_d;
   }
   else if(ush == 3)
   {
      return ::user::key_f;
   }
   else if(ush == 5)
   {
      return ::user::key_g;
   }
   else if(ush == 4)
   {
      return ::user::key_h;
   }
   else if(ush == 38)
   {
      return ::user::key_j;
   }
   else if(ush == 40)
   {
      return ::user::key_k;
   }
   else if(ush == 37)
   {
      return ::user::key_l;
   }
   else if(ush == 41)
   {
      return ::user::key_semicolon;
   }
   else if(ush == 6)
   {
      return ::user::key_z;
   }
   else if(ush == 7)
   {
      return ::user::key_x;
   }
   else if(ush == 8)
   {
      return ::user::key_c;
   }
   else if(ush == 9)
   {
      return ::user::key_v;
   }
   else if(ush == 11)
   {
      return ::user::key_b;
   }
   else if(ush == 45)
   {
      return ::user::key_n;
   }
   else if(ush == 46)
   {
      return ::user::key_m;
   }
   else if(ush == 43)
   {
      return ::user::key_comma;
   }
   else if(ush == 47)
   {
      return ::user::key_dot;
   }
   else if(ush == 44)
   {
      //         return ::user::key_;
   }
   else if(ush == 18)
   {
      return ::user::key_1;
   }
   else if(ush == 19)
   {
      return ::user::key_2;
   }
   else if(ush == 20)
   {
      return ::user::key_3;
   }
   else if(ush == 21)
   {
      return ::user::key_4;
   }
   else if(ush == 23)
   {
      return ::user::key_5;
   }
   else if(ush == 22)
   {
      return ::user::key_6;
   }
   else if(ush == 26)
   {
      return ::user::key_7;
   }
   else if(ush == 28)
   {
      return ::user::key_8;
   }
   else if(ush == 25)
   {
      return ::user::key_9;
   }
   else if(ush == 29)
   {
      return ::user::key_0;
   }
   else if(ush == 36)
   {
      return ::user::key_return;
   }
   else if(ush == 48)
   {
      return ::user::key_tab;
   }
   else if(ush == 51)
   {
      return ::user::key_back;
   }
   else if(ush == 117)
   {
      return ::user::key_delete;
   }
   else if(ush == 44)
   {
      return ::user::key_semicolon2;
   }
   else if(ush == 24)
   {
      return ::user::key_equal;
   }
   else if(ush == 27)
   {
      return ::user::key_hyphen;
   }
   else if(ush == 94)
   {
      return ::user::key_slash2;
   }
   else if(ush == 30)
   {
      return ::user::key_openbracket2;
   }
   else if(ush == 42)
   {
      return ::user::key_closebracket2;
   }
   else if(ush == 39)
   {
      return ::user::key_til2;
   }
   else if(ush == 33)
   {
      return ::user::key_acute2;
   }
   else if(ush == 115)
   {
      return ::user::key_home;
   }
   else if(ush == 119)
   {
      return ::user::key_end;
   }
   
}

return ::user::key_none;;
