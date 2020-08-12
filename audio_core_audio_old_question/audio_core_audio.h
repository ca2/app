#pragma once


#include "app-core/multimedia/multimedia/multimedia.h"
#include <AudioToolbox/AudioToolbox.h>



#if defined(_AUDIO_MMSYSTEM_LIBRARY)
   #define CLASS_DECL_AUDIO_CORE_AUDIO  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_AUDIO_CORE_AUDIO  CLASS_DECL_IMPORT
#endif


#include "audio_core_aligned_pointer.h"
#include "audio_core_aligned.h"


#include "audio_core_audio_translation.h"


#include "audio_core_audio_toolbox.h"


#include "audio_core_audio_out.h"
#include "audio_core_audio_in.h"




#include "audio_core_audio_factory_exchange.h"