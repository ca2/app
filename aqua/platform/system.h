#pragma once


#include "apex/platform/system.h"


namespace aqua
{


   class CLASS_DECL_AQUA system :
      virtual public ::apex::system
   {
   public:


      // ::pointer<::aqua::audio>                        m_paudio;
      //
      // ::pointer<::aqua::multimedia>                   m_pmultimedia;
      //
      // ::pointer<::aqua::audio_mixer>                  m_paudiomixer;
      //
      // ::pointer<::aqua::estamira>                     m_pestamira;
      //

      system();
      ~system() override;


      void aqua_construct();


      void common_construct();


      //void on_set_platform() override;

      void on_initialize_particle() override;


      virtual void on_add_session(::platform::session* papexsession) override;

      //virtual void initialize_rich_text();

      ::xml::xml* _xml() override;

      void speak(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrLang = "en-us", enum_gender egender = e_gender_none) override;


      virtual void create_audio() override;

      void defer_audio() override;

      virtual void defer_multimedia() override;

      virtual void defer_audio_mixer() override;

      virtual ::factory::factory_pointer audio_mixer_factory() override;

      bool has_audio() override;

      virtual ::aqua::multimedia* defer_get_multimedia() override;

      virtual ::aqua::audio_mixer * get_audio_mixer() override;

      void initialize_xml() override;

    ::aqua::audio * audio()  override;

       virtual bool has_audio() const; 

       ::aqua::multimedia * multimedia() override;


   };


} // namespace aqua




