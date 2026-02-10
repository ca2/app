#pragma once


#include "acme/platform/department.h"


namespace aqua
{


   class CLASS_DECL_AQUA audio :
      virtual public ::platform::department
   {
   protected:
      

      bool                 m_bTtsOptionInitialized;


   public:

      ::string             m_strTtsImplementation;

      ::audio::audio *     m_paudio;
      bool                 m_bLocalFileSystemSynch;
      class ::time           m_timePreBuffer;


      audio();
      ~audio() override;


      virtual void play_audio(const ::payload & payloadFile, enum_synchronicity esynchronicity = e_synchronicity_asynchronous);
      virtual void _play_audio(::file::file * pfile, enum_synchronicity esynchronicity = e_synchronicity_asynchronous);


      virtual string text_to_speech_implementation();
      virtual void text_to_speech_implementation(const ::scoped_string & scopedstrImplementation);

      virtual ::pointer<::text_to_speech::speaker>create_text_to_speech_speaker(const ::scoped_string & scopedstrImplementation = nullptr);


      virtual void speak(const ::scoped_string & scopedstrText);
      virtual void speak(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, enum_synchronicity esynchronicity, const ::scoped_string & scopedstrImplementation = nullptr);
      //virtual void trans_speak(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, bool bSynch);
      //virtual void google_speak(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, bool bSynch);

      

      virtual ::file_pointer get_rtp_file(const ::payload & payloadFile);


      virtual LPFN_NEW_MULTIMEDIA_DECODER get_multimedia_decoder_factory(const ::scoped_string & scopedstrTitle);


      virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);


      virtual void defer_initialize_audio_playback(::wave::enum_purpose epurpose = ::wave::e_purpose_playground);


   };


} // namespace aqua

//extern "C"
//typedef ::aqua::audio * GET_NEW_AUDIO();

//typedef GET_NEW_AUDIO * PFUNCTION_GET_NEW_AUDIO;

//CLASS_DECL_AQUA void set_get_new_audio(PFUNCTION_GET_NEW_AUDIO pfunction);

//extern "C"
//CLASS_DECL_AQUA ::aqua::audio * get_get_new_audio();


///CLASS_DECL_AQUA ::aqua::audio * get_context_audio(::particle * pparticle);



//namespace audio
//{
//
//
//   CLASS_DECL_AQUA string audio_get_default_implementation_name();
//
//
//} // namespace audio
//


