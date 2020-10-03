#pragma once


#include "app-core/audio/audio/_.h"
#include <AudioToolbox/AudioToolbox.h>


#if defined(_AUDIO_MMSYSTEM_LIBRARY)
   #define CLASS_DECL_AUDIO_CORE_AUDIO  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_AUDIO_CORE_AUDIO  CLASS_DECL_IMPORT
#endif


#include "aligned_pointer.h"
#include "aligned.h"


#include "translation.h"


#include "toolbox.h"


#include "wave_out.h"
#include "wave_in.h"




#include "factory_exchange.h"
