//
//  mouse_hook_interface.h
//  input_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 27/10/23 17:25
//
#pragma once


namespace input
{


   class mouse_hook
   {
   public:
      
      
      virtual void mouse_proc(enum_message emessage) = 0;

      
   };


} // namespace input



