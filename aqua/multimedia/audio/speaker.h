#pragma once


namespace text_to_speech
{


   class CLASS_DECL_AQUA speaker:
      virtual public object
   {
   public:


      __pointer(speaker)         m_pspeakerFallback;
      ::string                   m_strTtsImplementation;

      speaker();
      ~speaker() override;


      virtual void speak(const ::string & strText);

      virtual void speak(const ::string & strLang, const ::string & strText, bool bSynch = false);

      virtual void speak(const ::string & strAttributes, const ::string & strLang, const ::string & strText, bool bSynch = false);

      virtual void stop(string strLang);

      virtual bool is_speaking(string strLang);


   };


} // namespace text_to_speech



