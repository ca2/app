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


enum enum_number : ::u8
{

   e_number_none,
   e_number_i8 = 2,
   e_number_u8 = 4,
   e_number_i16 = 2 | 8,
   e_number_u16 = 4 | 8,
   e_number_i32 = 2 | 16,
   e_number_u32 = 4 | 16,
   e_number_i64 = 2 | 32,
   e_number_u64 = 4 | 32,
   e_number_f32 = 64,
   e_number_f64 = 65,
};



