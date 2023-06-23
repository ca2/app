#include "framework.h"
#include "audio.h"
#include "acme/exception/interface_only.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/platform/context.h"


namespace aqua
{


   audio::audio()
   {

      m_bTtsOptionInitialized = false;
      m_paudio = nullptr;

   }


   audio::~audio()
   {


   }


   void audio::play_audio(const ::payload& payloadFile, bool bSynch)
   {

      auto pfile = file() -> get_reader(payloadFile);

      _play_audio(pfile, bSynch);

   }


   void audio::_play_audio(::file::file * pfile, bool bSynch)
   {

      throw ::interface_only();

   }


   string audio::text_to_speech_implementation()
   {

      if (!m_bTtsOptionInitialized)
      {

         m_bTtsOptionInitialized = true;

         if(m_strTtsImplementation.is_empty())
         {

            ::file::path pathImplementation;

            pathImplementation = dir()->config() / "config/system/text_to_speech.txt";

            m_strTtsImplementation = file()->safe_get_string(pathImplementation);

         }

      }

      return m_strTtsImplementation;

   }


   void audio::text_to_speech_implementation(const ::string & strTtsImplementation)
   {

      if (!m_bTtsOptionInitialized)
      {

         m_bTtsOptionInitialized = true;

      }

      ::file::path pathImplementation;

      pathImplementation = dir()->config() / "config/system/text_to_speech.txt";

      file()->put_text(pathImplementation, strTtsImplementation);

      m_strTtsImplementation = file()->as_string(pathImplementation);

      //return ::success;

   }


   ::pointer<::text_to_speech::speaker>audio::create_text_to_speech_speaker(const ::string & strImplementation)
   {

      UNREFERENCED_PARAMETER(strImplementation);

      throw ::interface_only();

      return nullptr;

   }


   void audio::speak(const ::string & strText)
   {

      throw ::interface_only();

   }


   void audio::speak(const ::string & strLang, const ::string & strText, bool bSynch, const ::string & strImplementation)
   {

      throw ::interface_only();

   }


   //void audio::trans_speak(const ::string & strLang, const ::string & strText, bool bSynch)
   //{

   //   throw ::interface_only();

   //}


   //void audio::google_speak(const ::string & strLang, const ::string & strText, bool bSynch)
   //{

   //   throw ::interface_only();

   //}


   LPFN_NEW_MULTIMEDIA_DECODER audio::get_multimedia_decoder_factory(const ::string & strTitle)
   {
   
      return nullptr;
   
   }


   ::file_pointer audio::get_rtp_file(const ::payload & payloadFile)
   {

      throw ::interface_only();

      return nullptr;

   }


   LPWAVEOUT audio::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
   {

      throw ::interface_only();

      return nullptr;

   }


   void audio::defer_initialize_audio_playback(::wave::enum_purpose epurpose)
   {

      throw ::interface_only();

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


//CLASS_DECL_AQUA ::aqua::audio * get_context_audio(::particle * pparticle)
//{
//
//   return acmesystem()->defer_get_audio();
//
//}

//
//CLASS_DECL_AQUA bool has_audio()
//{
//
//   return ::is_set(acmesystem()->m_paudio);
//
//}




