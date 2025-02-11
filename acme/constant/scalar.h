// Created by camilo on 2022-11-17 04:17 <3ThomasBorregaardSorensen!!
#pragma once


enum enum_scalar
{



   e_scalar_none,
   e_scalar_default,
   e_scalar_download_size,
   e_scalar_download_progress_rate,
   e_scalar_app_install_progress,
   e_scalar_app_install_progress_min,
   e_scalar_app_install_progress_max,

   e_scalar_streaming_velocity,
   // to the right accelerates, to left certain range,
   // slow down, to left pass certain range, rewinds.

   e_scalar_tempo,
   e_scalar_position,
   e_scalar_key_shift,
   e_scalar_audio_volume,
   e_scalar_time,
   e_scalar_progress,

};


enum enum_scalar_flags
{
   // flags;
   e_scalar_set = 0x0000001,
   e_scalar_slide = 0x0000002

};


enum enum_number : unsigned char
{

   e_number_none,
   e_number_char = 2,
   e_number_unsigned_char = 4,
   e_number_short = 2 | 8,
   e_number_unsigned_short = 4 | 8,
   e_number_int = 2 | 16,
   e_number_unsigned_int = 4 | 16,
   e_number_long_long = 2 | 32,
   e_number_unsigned_long_long = 4 | 32,
   e_number_float = 64,
   e_number_double = 65,
};



