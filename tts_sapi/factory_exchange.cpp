#include "framework.h"


void tts_sapi_tts_speaker_factory_exchange(::factory_map * pfactorymap);


extern "C"
void tts_sapi_factory_exchange(::factory_map * pfactorymap)
{

   tts_sapi_tts_speaker_factory_exchange(pfactorymap);
   

}


