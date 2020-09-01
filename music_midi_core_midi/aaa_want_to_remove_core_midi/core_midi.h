//
//  audio_unitgraph.h
//  music_midi_core_midi
//
//  Created by Camilo Sasuke Tsumanuma on 19/05/19.
//  Copyright © 2019 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
#include <AudioUnit/AUComponent.h>
#else
#include <AUComponent.h>
#endif
#include <mach/mach_time.h>

#include <CoreAudio/CoreAudioTypes.h>
#include <CoreFoundation/CoreFoundation.h>


#include "app/music_midi_core_midi/core_midi_output_base.h"

#include "app/music_midi_core_midi/core_midi_input_base.h"

#include "core_midi_message_out.h"

#include "core_midi_message_in.h"

#include "core_midi_sequencer.h"

#include "core_midi_midi.h"
