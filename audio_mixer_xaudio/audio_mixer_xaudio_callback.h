#pragma once


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM callback
      {
      public:


         callback();
         virtual ~callback();


         virtual ::multimedia::audio_mixer::user::level_control * allocate_level_control();
         virtual ::multimedia::audio_mixer::user::toggle_control * allocate_toggle_control();
         virtual ::multimedia::audio_mixer::user::label * allocate_label();


      };


   } // namespace audio_mixer_mmsystem


} // namespace multimedia



