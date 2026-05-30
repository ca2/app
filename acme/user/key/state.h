//
// Created by camilo on 2026-05-29 12:38 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#pragma once


namespace key
{

   enum enum_state : u8
   {

      e_state_none = 0,
      e_state_pressed = 1<<0,
      e_state_repeat= 1 <<1,

   };


   DECLARE_C_FLAG(e_state, enum_state);

} // namespace key
