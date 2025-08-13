//
// Created by camilo on 2024-10-24 18:19 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "platform.h"
//#include "acme.h"
#include "context.h"
//#include "system_factory.h"
#include "application_flags.h"
#include "acme/constant/gender.h"
#include "acme/parallelization/_types.h"
#include "acme/prototype/collection/map.h"
#include "acme/prototype/prototype/factory.h"

namespace platform
{

   struct aqua_system_layer_t
   {
      ::pointer<::aqua::audio>                        m_paudio;

      ::pointer<::aqua::multimedia>                   m_pmultimedia;

      ::pointer<::aqua::audio_mixer>                  m_paudiomixer;

      ::pointer<::aqua::estamira>                     m_pestamira;



   };


   class CLASS_DECL_ACME aqua_system_layer
   {
   public:


      virtual void on_add_session(::platform::session* papexsession);

      //virtual void initialize_rich_text();

      virtual ::xml::xml* _xml();

      virtual void speak(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrLang = "en-us", enum_gender egender = e_gender_none);

      virtual void initialize_xml();

      virtual void create_audio();

      virtual void defer_audio();

      virtual void defer_multimedia();

      virtual void defer_audio_mixer();

      virtual ::factory::factory_pointer audio_mixer_factory();

      //virtual bool has_audio() override;

      virtual ::aqua::multimedia* defer_get_multimedia();

      virtual ::aqua::audio_mixer * get_audio_mixer();


      virtual ::aqua::audio * audio();

      virtual bool has_audio();

      virtual  ::aqua::multimedia * multimedia();


   };



} // namespace platform

