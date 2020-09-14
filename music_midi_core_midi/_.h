#pragma once


#include "app-veriwell/multimedia/multimedia/_.h"

//#include <CoreFoundation/CoreFoundation.h>
//#include <CoreFoundation/CFByteOrder.h>
#ifdef MACOS
#include <CoreServices/CoreServices.h>
#else
//#include <UIServices/UIServices.h>
#endif
#include <AudioToolbox/AudioToolbox.h>
#include <AudioToolbox/MusicPlayer.h>
#include <AudioUnit/AudioUnit.h>
#include <CoreMIDI/CoreMIDI.h>
#include <CoreMIDI/MIDIServices.h>


#if defined(_VERIWELL_MULTIMEDIA_MUSIC_MIDI_CORE_MIDI_LIBRARY)
   #define CLASS_DECL_MUSIC_MIDI_CORE_MIDI  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_MUSIC_MIDI_CORE_MIDI  CLASS_DECL_IMPORT
#endif


namespace music
{
   

   namespace midi
   {
      
      
      namespace core_midi
      {


         class sequence;
         

      } // namespace core_midi
      

   } // namespace midi
   
   
} // namespace music




//::music::midi::message_out * music_midi_audio_unit_new_message_out(::layered * pobjectContext);

//::music::midi::play_thread * music_midi_real_time_new_play_thread(::music::midi::sequence * psequence, index iPort);

//::music::midi::play_thread * music_midi_core_midi_new_play_thread(::music::midi::sequence * psequence, index iPort);

::music::midi::midi * music_midi_real_time_new_midi();

//::music::midi::midi * music_midi_core_midi_new_midi(::music::midi::midi * pmidiParent);


#include "translation.h"

//#include "music_midi_core_midi_sequence.h"

//#include "music_midi_core_midi_player.h"

//#include "music_midi_core_midi_file.h"
          
//#include "music_midi_core_midi_sequence_thread.h"

#include "time.h"

#include "output_base.h"

#include "message_out.h"

#include "input_base.h"

#include "message_in.h"

#include "sequencer.h"

#include "factory_exchange.h"


#include "midi.h"




