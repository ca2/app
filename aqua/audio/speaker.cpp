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

      return m_pspeakerFallback->speak(scopedstrText);

   }


   void speaker::speak(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, enum_synchronicity esynchronicity)
   {

      if (m_pspeakerFallback.is_null())
      {

         //return false;

         return;

      }

      return m_pspeakerFallback->speak(scopedstrLang, scopedstrText, esynchronicity);

   }


   void speaker::speak(const ::scoped_string & scopedstrAttributes, const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, enum_synchronicity esynchronicity)
   {

      if (m_pspeakerFallback.is_null())
      {

         //return false;
         return;

      }

      return m_pspeakerFallback->speak(scopedstrAttributes, scopedstrLang, scopedstrText, esynchronicity);

   }


   void speaker::stop(const ::scoped_string & scopedstrLang)
   {

      if (m_pspeakerFallback.is_null())
      {

         //return false;
         return;

      }

      return m_pspeakerFallback->stop(scopedstrLang);

   }


   bool speaker::is_speaking(const ::scoped_string & scopedstrLang)
   {

      if (m_pspeakerFallback.is_null())
      {

         return false;

      }

      m_pspeakerFallback->speak(scopedstrLang);

      return true;

   }


} // namespace text_to_speech



