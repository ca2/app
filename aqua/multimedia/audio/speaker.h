#pragma once

////////////////////////////////////////////////////////////////////////////////
//
//   ::tts::speaker class
//


namespace tts
{


   class CLASS_DECL_AQUA speaker:
      virtual public object
   {
   public:


      __pointer(speaker)          m_pspeakerFallback;


      speaker();

      virtual ~speaker();


      virtual bool speak(const string & strText);

      virtual bool speak(const string & strLang, const string & strText, bool bSynch = false);

      virtual bool speak(const string & strAttributes, const string & strLang, const string & strText, bool bSynch = false);

      virtual bool stop(string strLang);

      virtual bool is_speaking(string strLang);


   };


} // namespace tts






