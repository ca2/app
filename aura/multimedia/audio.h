#pragma once


typedef ::multimedia::decoder * CDECL NEW_MULTIMEDIA_DECODER();


typedef NEW_MULTIMEDIA_DECODER * LPFN_NEW_MULTIMEDIA_DECODER;


namespace aura
{


   class CLASS_DECL_AURA audio :
      virtual public ::apex::department
   {
   public:


      bool           m_bLocalFileSystemSynch;
      ::duration     m_durationPreBuffer;


      audio();
      virtual ~audio();


      virtual void play_audio(const var & varFile, bool bSynch = false);


      virtual __pointer(::tts::speaker) create_tts_speaker();

      virtual void speak(const string & strText);
      virtual void speak(const string & strLang, const string & strText, bool bSynch);
      virtual void trans_speak(const string & strLang, const string & strText, bool bSynch);
      virtual void google_speak(const string & strLang, const string & strText, bool bSynch);


      virtual ::file_pointer get_rtp_file(const ::var & varFile);


      virtual LPFN_MULTIMEDIA_NEW_DECODER get_multimedia_decoder_factory(const char * pszTitle);


      virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);



   };


} // namespace aura

extern "C"
typedef ::aura::audio * GET_NEW_AUDIO();

typedef GET_NEW_AUDIO * PFUNCTION_GET_NEW_AUDIO;

CLASS_DECL_AURA void set_get_new_audio(PFUNCTION_GET_NEW_AUDIO pfunction);

extern "C"
CLASS_DECL_AURA ::aura::audio * get_get_new_audio();


CLASS_DECL_AURA ::aura::audio * get_context_audio(::layered * pobjectContext);


CLASS_DECL_AURA bool has_audio();


namespace audio
{


   CLASS_DECL_AURA string get_default_library_name();


} // namespace audio



