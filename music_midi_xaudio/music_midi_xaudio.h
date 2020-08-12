#pragma once


#include "app-veriwell/multimedia/multimedia/multimedia.h"
#include "app/multimedia_xaudio/multimedia_xaudio.h"


#if defined(_VERIWELL_MULTIMEDIA_MUSIC_MIDI_MMSYSTEM_LIBRARY)
   #define CLASS_DECL_MUSIC_MIDI_MMSYSTEM  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_MUSIC_MIDI_MMSYSTEM  CLASS_DECL_IMPORT
#endif



#include "music_midi_xaudio_translation.h"

#include "music_midi_xaudio_sequence.h"

#include "player/music_midi_xaudio_player.h"

#include "music_midi_xaudio_out.h"

#include "music_midi_xaudio_file.h"
          
#include "music_midi_xaudio_sequence_thread.h"

#include "music_midi_xaudio_factory_exchange.h"



