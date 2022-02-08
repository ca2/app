#include "framework.h"
#include "_uwp.h"

//////////////////////////////////////////////////////////////////////////
//
// FILE: TextSpeaker.h
//
// Defines a simple C++ class to speak some text.
//
// by Giovanni Dicanio <gdicanio@mvps.org>
//
// 2010, December 28th
//
//////////////////////////////////////////////////////////////////////////


//#include <sapi.h>               // SAPI

// Declare local identifiers:

using namespace Platform;
using namespace ::winrt::Windows::Foundation;
using namespace ::winrt::Windows::Foundation::Collections;
using namespace ::winrt::Windows::Media::SpeechSynthesis;


namespace universal_windows
{


   namespace tts
   {


      //------------------------------------------------------------------------
      // Simple class to speak some text (using SAPI).
      //------------------------------------------------------------------------

      speaker::speaker()
      {

      }


      speaker::~speaker()
      {

      }

      //--------------------------------------------------------------------
      // Initializes the text speaker.
      //--------------------------------------------------------------------
      bool speaker::initialize(string strLang)
      {

         destroy(strLang);

         //
         // Create text to speech engine
         //
         ::winrt::Windows::Media::SpeechSynthesis::SpeechSynthesizer ^ psynth = ref new ::winrt::Windows::Media::SpeechSynthesis::SpeechSynthesizer();
         if (psynth == nullptr)
         {

            return false;

         }

         m_synth[strLang] =  psynth;

         if(strLang.is_empty())
         {

            strLang = "en";

         }
         // get all of the installed voices
         IVectorView<VoiceInformation ^> ^voices = ::winrt::Windows::Media::SpeechSynthesis::SpeechSynthesizer::AllVoices;

         for (unsigned int index = 0; index < voices->Size; index++)
         {
            // create a combo box item, and copy the voice data into that
            VoiceInformation ^voice = voices->GetAt(index);
            string strL = voice->Language;
            if (::str::begins_ci(strL, strLang))
            {
               try
               {
                  psynth->Voice = voice;
                  return true;
               }
               catch(...)
               {

               }

            }

         }


         return false;

      }
      bool speaker::initialize_translator(string strLang)
      {

         return false;

      }

      bool speaker::destroy(string strLang)
      {

         if(m_synth[strLang] != nullptr)
         {

//            m_synth[strLang]->();

         }

         m_synth[strLang] = nullptr;



         return true;
      }
      bool speaker::finalize_translator(string strLang)
      {

         return false;

      }


      //--------------------------------------------------------------------
      // Speaks some text.
      // (The input text must not be empty.)
      //--------------------------------------------------------------------
      bool speaker::speak(const string & text)
      {

         return speak("",text);

      }


      //--------------------------------------------------------------------
      // Speaks some text.
      // (The input text must not be empty.)
      //--------------------------------------------------------------------
      bool speaker::speak(const ::string & strLang, const string & text, bool bSync)
      {

         //
         // Input text must not be empty
         //
         if(text.is_empty())
         {

            // nothing to speak?!?!
            return false;

         }

         bool bTts = false;

         //if((!m_tts.lookup(strLang, bTts) || bTts) && m_voice[strLang].is_set() || (!is_speaking(strLang) && m_time.elapsed()[strLang] > 30 * 1000))
         if (!m_tts.lookup(strLang, bTts))
         {

            if (initialize(strLang))
            {

               m_tts[strLang] = true;

            }
            else
            {

               m_tts[strLang] = false;

               if (!initialize_translator(strLang))
               {

                  return false;

               }

            }

         }


         wstring wstr(text);

         if(bSync)
         {

            ::wait_then(GetSpeechStreamTask(strLang, wstr), [=](SpeechSynthesisStream ^speechStream)
            {

               auto pfile = create_memory_file(speechStream);

               paudio->play_audio(pfile, true);

            });

         }
         else
         {

            ::fork_then(get_application(), GetSpeechStreamTask(strLang, wstr), [=](SpeechSynthesisStream ^speechStream)
            {

               paudio->play_audio(create_memory_file(speechStream->GetInputStreamAt(0)), true);

            });

         }

         return true;

      }


      bool speaker::is_speaking(string strLang)
      {
         return false;
         //if(m_synth[strLang].is_null())
         //{

         //   return false;

         //}

         //SPVOICESTATUS status ={};

         //HRESULT hr = m_voice[strLang]->GetStatus(&status,nullptr);

         //if(FAILED(hr))
         //{

         //   return false;

         //}

         //return (status.dwRunningState & SPRS_IS_SPEAKING) != false;

      }


      bool speaker::stop(string strLang)
      {

         if (m_tts[strLang])
         {

            destroy(strLang);

         }
         else
         {

            finalize_translator(strLang);

         }

         return true;

      }

      //actual creation of the stream using the new voice synthesis stream
      IAsyncOperation < SpeechSynthesisStream^ > ^ speaker::GetSpeechStreamTask(string strLang, string text)
      {
         return m_synth[strLang]->SynthesizeTextToStreamAsync(text);
      }
   } // namespace tts


} // namespace universal_windows










