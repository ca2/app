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

      __throw(error_interface_only);

   }


   __pointer(::tts::speaker) audio::create_tts_speaker()
   {

      __throw(error_interface_only);

      return nullptr;

   }


   void audio::speak(const ::string & strText)
   {

      __throw(error_interface_only);

   }


   void audio::speak(const ::string & strLang, const ::string & strText, bool bSynch)
   {

      __throw(error_interface_only);

   }


   void audio::trans_speak(const ::string & strLang, const ::string & strText, bool bSynch)
   {

      __throw(error_interface_only);

   }


   void audio::google_speak(const ::string & strLang, const ::string & strText, bool bSynch)
   {

      __throw(error_interface_only);

   }


   LPFN_NEW_MULTIMEDIA_DECODER audio::get_multimedia_decoder_factory(const ::string & strTitle)
   {
   
      return nullptr;
   
   }


   ::file_pointer audio::get_rtp_file(const ::payload & varFile)
   {

      __throw(error_interface_only);

      return nullptr;

   }


   LPWAVEOUT audio::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
   {

      __throw(error_interface_only);

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




