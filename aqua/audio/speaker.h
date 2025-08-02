#pragma once


////#include "acme/prototype/prototype/object.h"

namespace text_to_speech
{


   class CLASS_DECL_AQUA speaker:
      virtual public object
   {
   public:


      ::pointer<speaker>        m_pspeakerFallback;
      ::string                   m_strTtsImplementation;

      speaker();
      ~speaker() override;


      virtual void speak(const ::scoped_string & scopedstrText);

      virtual void speak(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, enum_synchronicity esynchronicity = e_synchronicity_asynchronous);

      virtual void speak(const ::scoped_string & scopedstrAttributes, const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, enum_synchronicity esynchronicity = e_synchronicity_asynchronous);

      virtual void stop(const ::scoped_string & scopedstrLang);

      virtual bool is_speaking(const ::scoped_string & scopedstrLang);


   };


} // namespace text_to_speech



