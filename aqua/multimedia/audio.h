#pragma once


namespace aqua
{


   class CLASS_DECL_AQUA audio :
      virtual public ::acme::department
   {
   protected:
      

      bool                 m_bTtsOptionInitialized;
      ::string             m_strTtsImplementation;


   public:


      ::audio::audio *     m_paudio;
      bool                 m_bLocalFileSystemSynch;
      ::duration           m_durationPreBuffer;


      audio();
      ~audio() override;


      virtual void play_audio(::file::file * pfile, bool bSynch = false);


      virtual string text_to_speech_implementation();
      virtual void text_to_speech_implementation(const ::string & strImplementation);

      virtual __pointer(::text_to_speech::speaker) create_text_to_speech_speaker(const ::string& strImplementation = nullptr);


      virtual void speak(const ::string & strText);
      virtual void speak(const ::string & strLang, const ::string & strText, bool bSynch, const ::string & strImplementation = nullptr);
      //virtual void trans_speak(const ::string & strLang, const ::string & strText, bool bSynch);
      //virtual void google_speak(const ::string & strLang, const ::string & strText, bool bSynch);

      

      virtual ::file_pointer get_rtp_file(const ::payload & payloadFile);


      virtual LPFN_NEW_MULTIMEDIA_DECODER get_multimedia_decoder_factory(const ::string & pszTitle);


      virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);


      virtual void defer_initialize_audio_playback(::wave::e_purpose epurpose = ::wave::purpose_playground);


   };


} // namespace aqua

//extern "C"
//typedef ::aqua::audio * GET_NEW_AUDIO();

//typedef GET_NEW_AUDIO * PFUNCTION_GET_NEW_AUDIO;

//CLASS_DECL_AQUA void set_get_new_audio(PFUNCTION_GET_NEW_AUDIO pfunction);

//extern "C"
//CLASS_DECL_AQUA ::aqua::audio * get_get_new_audio();


///CLASS_DECL_AQUA ::aqua::audio * get_context_audio(::object * pobject);



//namespace audio
//{
//
//
//   CLASS_DECL_AQUA string get_default_library_name();
//
//
//} // namespace audio
//


