///////////////////////////////////////////////////////////////////////////////
//
// File Name: vmsaudio.h
// Long Name: Veriwell Musical Audio papp Programming Interface
//
// Author: Camilo Sasuke Tsumanuma
//
// Creation Date: 2003-03-07
//
// Purpose: Define global elements.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef VMSAUDIO_INCLUDE_FILE
#define VMSAUDIO_INCLUDE_FILE

#include "gen/gen.h"
#include "iaud/iaud.h"
#include "notsad/notsad.h"

#ifdef _VMSAUDIO_DLL
    #define CLASS_DECL_VMSAUDIO  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_VMSAUDIO  CLASS_DECL_IMPORT
#endif

#include "aud_global.h"


#include "WaveCentralContainer.h"
#include "WaveInListener.h"
#include "WaveInListenerSet.h"

#include "Command.h"
#include "WavePlayerCommand.h"
#include "WaveRecorderCommand.h"


#include "WavePlayer.h"
#include "WavePreBuffer.h"
#include "WaveOut.h"
#include "WaveRecorder.h"
#include "WaveIn.h"

#include "WaveCentral.h"



#endif // _VMSAUDIO_INCLUDE_FILE
