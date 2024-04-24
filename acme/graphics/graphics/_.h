// Created by camilo on 2023-11-04 01:08 <3ThomasBorregaardBorregaard!!
#pragma once


namespace graphics
{


   class output_purpose;

   
   enum enum_output_purpose
   {

      e_output_purpose_none,
      e_output_purpose_fps = 1,
      //e_output_purpose_auto = 1,
      e_output_purpose_offscreen = 0x80,
      e_output_purpose_offscreen_fps = e_output_purpose_offscreen | e_output_purpose_fps,
      e_output_purpose_screen = 0x8000,
      e_output_purpose_screen_fps = e_output_purpose_screen | e_output_purpose_fps,
      //e_output_purpose_screen_auto = e_output_purpose_screen | e_output_purpose_auto,

   };


   DECLARE_ENUMERATION(e_output_purpose, enum_output_purpose);


} // namespace graphics



