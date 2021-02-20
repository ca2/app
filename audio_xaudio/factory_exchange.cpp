#include "framework.h"

//
//namespace multimedia
//{
//
//
//   namespace audio_xaudio
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
//   } // namespace audio_xaudio
//
//
//} // namespace multimedia


extern "C"
CLASS_DECL_EXPORT void audio_xaudio_factory_exchange(::factory_map * pfactorymap)
{

   //::multimedia::audio_xaudio::factory_exchange factoryexchange();

   create_factory < ::multimedia::audio_xaudio::in, ::wave::in >();
   create_factory < ::multimedia::audio_xaudio::out, ::wave::out >();


}









