#include "framework.h"


namespace aqua
{


   audio::audio()
   {

      m_paudio = nullptr;

   }


   audio::~audio()
   {


   }


   void audio::play_audio(::file::file * pfile, bool bSynch)
   {

      throw ::interface_only_exception();

   }


   __pointer(::tts::speaker) audio::create_tts_speaker()
   {

      throw ::interface_only_exception();

      return nullptr;

   }


   void audio::speak(const ::string & strText)
   {

      throw ::interface_only_exception();

   }


   void audio::speak(const ::string & strLang, const ::string & strText, bool bSynch)
   {

      throw ::interface_only_exception();

   }


   void audio::trans_speak(const ::string & strLang, const ::string & strText, bool bSynch)
   {

      throw ::interface_only_exception();

   }


   void audio::google_speak(const ::string & strLang, const ::string & strText, bool bSynch)
   {

      throw ::interface_only_exception();

   }


   LPFN_NEW_MULTIMEDIA_DECODER audio::get_multimedia_decoder_factory(const ::string & strTitle)
   {
   
      return nullptr;
   
   }


   ::file_pointer audio::get_rtp_file(const ::payload & payloadFile)
   {

      throw ::interface_only_exception();

      return nullptr;

   }


   LPWAVEOUT audio::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
   {

      throw ::interface_only_exception();

      return nullptr;

   }


   ::e_status audio::defer_initialize_audio_playback(::wave::e_purpose epurpose)
   {

      return error_interface_only;

   }


} // namespace aura

//
//static PFUNCTION_GET_NEW_AUDIO g_pgetnewaudio = nullptr;
//
//
//CLASS_DECL_AQUA void set_get_new_audio(PFUNCTION_GET_NEW_AUDIO pgetnewaudio)
//{
//
//   g_pgetnewaudio = pgetnewaudio;
//
//}
//
//
//CLASS_DECL_AQUA ::aqua::audio * get_new_audio()
//{
//
//   if ((iptr)g_pgetnewaudio < 65536)
//   {
//
//      return nullptr;
//
//   }
//
//   return g_pgetnewaudio();
//
//}


//CLASS_DECL_AQUA ::aqua::audio * get_context_audio(::object * pobject)
//{
//
//   return get_system()->defer_get_audio();
//
//}

//
//CLASS_DECL_AQUA bool has_audio()
//{
//
//   return ::is_set(get_system()->m_paudio);
//
//}




