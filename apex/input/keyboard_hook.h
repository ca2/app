//
//  keyboard_hook_interface.h
//  input_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 27/10/23 17:23
//
#pragma once


namespace input
{


   class keyboard_hook
   {
   public:
      
      
      virtual void keyboard_proc(::user::enum_message emessage, ::i32 iVirtualKeyCode, ::i32 iScanCode) = 0;

      
   };


} // namespace input



