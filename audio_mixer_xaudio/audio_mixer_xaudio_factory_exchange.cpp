#include "framework.h"


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      factory_exchange::factory_exchange()
      {

         //create_factory < callback                    >  (__type(::multimedia::audio_mixer::callback));
         create_factory <control                     >  (__type(::multimedia::audio_mixer::control));
         //create_factory <control_data                >  (__type(::multimedia::audio_mixer::control_data));
         create_factory <destination                 >  (__type(::multimedia::audio_mixer::destination));
         create_factory <device                      >  (__type(::multimedia::audio_mixer::device));
         create_factory <line_info                   >  (__type(::multimedia::audio_mixer::line_info));
         create_factory < audio_mixer                     >  (__type(::multimedia::audio_mixer::audio_mixer));
         //create_factory < department                   >  (__type(::multimedia::audio_mixer::font));
         create_factory <source                      >  (__type(::multimedia::audio_mixer::source));
         create_factory <thread                      >  (__type(::multimedia::audio_mixer::thread));
         /*create_factory <user::label                 >  (__type(::multimedia::audio_mixer::user::label));
         create_factory <user::control               >  (__type(::multimedia::audio_mixer::user::control));
         create_factory <user::level_control         >  (__type(::multimedia::audio_mixer::user::level_control));
         create_factory <user::toggle_control        >  (__type(::multimedia::audio_mixer::user::toggle_control));*/

      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace audio_mmsystem


} // namespace multimedia


void factory_exchange()
{
   ::multimedia::audio_mixer_mmsystem::factory_exchange factoryexchange();
}



