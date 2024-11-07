#include "framework.h"
#include "system_aqua.h"


namespace platform
{


   void aqua_system_layer::on_add_session(::platform::session* papexsession)
   {
   }


   //void aqua_system_layer::initialize_rich_text(){}

   ::xml::xml* aqua_system_layer::_xml()
   {
      return nullptr;
   }


   void aqua_system_layer::speak(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrLang,
                                 enum_gender egender)
   {
   }


   void aqua_system_layer::initialize_xml()
   {


   }


   void aqua_system_layer::create_audio()
   {
   }


   void aqua_system_layer::defer_audio()
   {
   }


   void aqua_system_layer::defer_multimedia()
   {
   }


   void aqua_system_layer::defer_audio_mixer()
   {
   }


    ::factory::factory_pointer  aqua_system_layer::audio_mixer_factory()
   {
      return {};
   }


   //virtual bool has_audio() override{}

    ::aqua::multimedia*  aqua_system_layer::defer_get_multimedia()
   {
      return nullptr;
   }


    ::aqua::audio_mixer*  aqua_system_layer::get_audio_mixer()
   {
      return nullptr;
   }


    ::aqua::audio*  aqua_system_layer::audio()
   {
      return nullptr;
   }


    bool  aqua_system_layer::has_audio()
   {
      return false;
   }


   ::aqua::multimedia* aqua_system_layer::multimedia()
   {
      return nullptr;
   }



} // namespace platform
