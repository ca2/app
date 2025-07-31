#include "framework.h"
#include "speaker.h"


namespace text_to_speech
{


   speaker::speaker()
   {


   }


   speaker::~speaker()
   {


   }


   void speaker::speak(const ::scoped_string & scopedstrText)
   {

      if (m_pspeakerFallback.is_null())
      {

         return;

      }

      return m_pspeakerFallback->speak(strText);

   }


   void speaker::speak(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, bool bSynch)
   {

      if (m_pspeakerFallback.is_null())
      {

         //return false;

         return;

      }

      return m_pspeakerFallback->speak(strLang, strText, bSynch);

   }


   void speaker::speak(const ::scoped_string & scopedstrAttributes, const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, bool bSynch)
   {

      if (m_pspeakerFallback.is_null())
      {

         //return false;
         return;

      }

      return m_pspeakerFallback->speak(strAttributes, strLang, strText, bSynch);

   }


   void speaker::stop(string strLang)
   {

      if (m_pspeakerFallback.is_null())
      {

         //return false;
         return;

      }

      return m_pspeakerFallback->stop(strLang);

   }


   bool speaker::is_speaking(string strLang)
   {

      if (m_pspeakerFallback.is_null())
      {

         return false;

      }

      m_pspeakerFallback->speak(strLang);

      return true;

   }


} // namespace text_to_speech



