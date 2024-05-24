#pragma once


enum e_scalar
{



   scalar_none,
   scalar_default,
   scalar_download_size,
   scalar_app_install_progress,
   scalar_app_install_progress_min,
   scalar_app_install_progress_max,

   scalar_streaming_velocity,
   // to the right accelerates, to left certain range,
   // slow down, to left pass certain range, rewinds.

   scalar_tempo,
   scalar_position,
   scalar_key_shift,
   scalar_audio_volume,
   scalar_time,
   scalar_progress,

};


enum e_scalar_flags
{
   // flags;
   scalar_set        = 0x0000001,
   scalar_slide      = 0x0000002

};
