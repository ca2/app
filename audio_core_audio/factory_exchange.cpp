#include "framework.h"


//namespace multimedia
//{
//
//
//   namespace audio_core_audio
//   {
//
//
//      factory_exchange::factory_exchange()
//      {
//
//         create_factory < in, ::wave::in >();
//         create_factory < out, ::wave::out >();
//
//      }
//
//
//      factory_exchange::~factory_exchange()
//      {
//      }
//
//
//   } // namespace audio_core_audio
//
//
//} // namespace multimedia


extern "C"
void audio_core_audio_factory_exchange(::factory_map * pfactorymap)
{

   //::multimedia::audio_core_audio::factory_exchange factoryexchange();
   create_factory < ::multimedia::audio_core_audio::in, ::wave::in >();
   create_factory < ::multimedia::audio_core_audio::out, ::wave::out >();
}








