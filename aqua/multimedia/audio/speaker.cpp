#include "framework.h"


namespace text_to_speech
{


   speaker::speaker()
   {

   }


   speaker::~speaker()
   {
   }


   bool speaker::speak(const ::string & strText)
   {

      if (m_pspeakerFallback.is_null())
      {

         return false;

      }

      return m_pspeakerFallback->speak(strText);

   }


   bool speaker::speak(const ::string & strLang, const ::string & strText, bool bSynch)
   {

      if (m_pspeakerFallback.is_null())
      {

         return false;

      }

      return m_pspeakerFallback->speak(strLang, strText, bSynch);

   }


   bool speaker::speak(const ::string & strAttributes, const ::string & strLang, const ::string & strText, bool bSynch)
   {

      if (m_pspeakerFallback.is_null())
      {

         return false;

      }

      return m_pspeakerFallback->speak(strAttributes, strLang, strText, bSynch);

   }


   bool speaker::stop(string strLang)
   {

      if (m_pspeakerFallback.is_null())
      {

         return false;

      }

      return m_pspeakerFallback->stop(strLang);

   }


   bool speaker::is_speaking(string strLang)
   {

      if (m_pspeakerFallback.is_null())
      {

         return false;

      }

      return m_pspeakerFallback->speak(strLang);

   }



} // namespace text_to_speech




