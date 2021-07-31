#pragma once

#include <agile.h>

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Media::SpeechSynthesis;
using namespace Platform;


namespace uwp
{


   namespace tts
   {


      //------------------------------------------------------------------------
      // Simple class to speak some text (using SAPI).
      //------------------------------------------------------------------------
      class speaker:
         virtual public ::tts::speaker
      {
      public:


         string_map < Agile < Windows::Media::SpeechSynthesis::SpeechSynthesizer > >        m_synth;
         string_map < ::u32 >                                                       m_time;
         string_map < bool >                                                        m_tts;


         //--------------------------------------------------------------------
         // Initializes the text speaker.
         //--------------------------------------------------------------------
         speaker();
         virtual ~speaker();

         virtual bool initialize(string strLang);
         virtual bool initialize_translator(string strLang);
         virtual bool destroy(string strLang);
         virtual bool finalize_translator(string strLang);

         //--------------------------------------------------------------------
         // Speaks some text.
         // (The input text must not be empty.)
         //--------------------------------------------------------------------
         virtual bool speak(const string & text) override;

         virtual bool speak(const string & strLang, const string & text, bool bSync = false) override;

         virtual bool is_speaking(string strLang) override;

         virtual bool stop(string strLang) override;

         IAsyncOperation < SpeechSynthesisStream^ > ^ GetSpeechStreamTask(string strLang, string strText);


      };


   } // namespace tts


} // namespace uwp






