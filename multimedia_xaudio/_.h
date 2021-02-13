#pragma once



#include "app-core/audio/audio/_.h"
#include "apex/operating_system.h"

#include <xaudio2.h>



#if defined(_MULTIMEDIA_XAUDIO_LIBRARY)
   #define CLASS_DECL_MULTIMEDIA_XAUDIO  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_MULTIMEDIA_XAUDIO  CLASS_DECL_IMPORT
#endif


#include "translation.h"


#include "factory_exchange.h"