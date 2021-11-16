#pragma once


namespace text_to_speech
{


   class CLASS_DECL_AQUA speaker:
      virtual public object
   {
   public:


      __pointer(speaker)          m_pspeakerFallback;


      speaker();
      ~speaker() override;


      virtual ::e_status speak(const ::string & strText);

      virtual ::e_status speak(const ::string & strLang, const ::string & strText, bool bSynch = false);

      virtual ::e_status speak(const ::string & strAttributes, const ::string & strLang, const ::string & strText, bool bSynch = false);

      virtual ::e_status stop(string strLang);

      virtual bool is_speaking(string strLang);


   };


} // namespace text_to_speech



