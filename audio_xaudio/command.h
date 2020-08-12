#pragma once


namespace audio
{


   enum enum_command
   {

      command_open_decoder,

      command_open_file,
      command_open_file_aiff,
      command_open_file_cda,
      command_open_file_rtp, // currently a non seekable mp3 file stream
      command_open_file_mp3,
      command_open_file_vqf,
      command_open_file_wm,
      command_open_file_wav,

      command_open_device,
      command_close_device,

      command_execute_play,
      command_execute_record,
      command_execute_stop,
      command_execute_pause,
      command_execute_restart,
      

   };


} // namespace audio



