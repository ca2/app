//
//  _constant.h
//  aqua
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2022-09-06 22:58
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


namespace multimedia
{


   enum enum_exception
   {

      e_exception_undefined,
      e_exception_multimedia,
      e_exception_midi,
      e_exception_music,

   };


} // namespace multimedia


namespace aqua
{


   enum enum_media_type
   {

      e_media_type_unknown,
      e_media_type_aiff,
      e_media_type_cda,
      e_media_type_spotify_track,
      e_media_type_mpeg,
      e_media_type_twinvq,
      e_media_type_wm,
      e_media_type_wav,
      e_media_type_zip,
      e_media_type_rtp,
      e_media_type_midi,
      e_media_type_opaque_audio,

   };


enum enum_command
{

   command_open_plugin,

   
   command_open_media_item,
   
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


enum enum_player_state
{

   e_player_state_initial,
   e_player_state_playing,
   e_player_state_paused,
   e_player_state_fading_out_to_stop,

};


enum enum_player_happening
{

   e_player_happening_open_decoder,
   e_player_happening_open_device,
   e_player_happening_play,
   e_player_happening_stop,
   e_player_happening_execute_pause,
   e_player_happening_execute_restart,
   e_player_happening_eof,
   e_player_happening_playback_end,
   e_player_happening_stopped,
   e_player_happening_close_decoder,
   e_player_happening_fade_out_and_stop,
   e_player_happening_close_device,
   e_player_happening_open_decoder_failed,
   e_player_happening_open_device_failed,
   e_player_happening_start_device_failed,
   e_player_happening_destroy

};


} // namespace aqua
