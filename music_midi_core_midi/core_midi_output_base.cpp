//
//  output_base.cpp
//  music_midi_core_audio
//
//  Created by Camilo Sasuke Tsumanuma on 9/8/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"
#include "core_midi_output_base.h"


namespace music
{
   
   
   namespace midi
   {
      
      
      namespace core_midi
      {
         
         const int PITCH_BEND_CENTER = 8192;
         
         class timer
         {
         public:
            void Stop()
            {
            }
            void Start(int dur)
            {
               
            }
         };
         
         class StopNoteTimer : public timer
         {
            
            output_base* m_o;
         public:
            
            StopNoteTimer(output_base* o) : timer()
            {
               m_o = o;
            }
            
            void Notify()
            {
               m_o->stopNote();
               timer::Stop();
            }
            
            void start(int duration)
            {
               Start(duration);
            }
         };
         
         
         StopNoteTimer* stopNoteTimer = nullptr;
         
         

         output_base::output_base()
         {
            
            OSStatus returnval = MIDIClientCreate(CFSTR("AriaOutput"), nullptr, nullptr, &m_client);
            
            if (returnval != 0)
            {
               
               //fprintf(stderr, "MIDIClientCreate failed with error code %i (%s, %s)\n", (int)returnval,
                 //      GetMacOSStatusErrorString(returnval), GetMacOSStatusCommentString(returnval));
               
            }
            
            stopNoteTimer = new StopNoteTimer(this);
            
            m_playing = false;
            
         }

         // ------------------------------------------------------------------------------------------------------

         output_base::~output_base()
         {
            MIDIClientDispose(m_client);
            
            if (stopNoteTimer != nullptr)
            {
               delete stopNoteTimer;
               stopNoteTimer = nullptr;
            }
         }


         void output_base::playNote(int pitchID, int volume, int duration, int channel, int instrument)
         {
            if (m_playing) stopNote();
            
            m_last_note = pitchID;
            m_last_channel = channel;
            
            program_change(instrument, channel);
            note_on(pitchID, volume, channel);
            stopNoteTimer->start(duration);
            m_playing = true;
            
            return;
         }

// ------------------------------------------------------------------------------------------------------

void output_base::stopNote()
{
   if (not m_playing) return;
   
   note_off(m_last_channel, m_last_note, 0);
   m_playing = false;
   
   return;
}

// ------------------------------------------------------------------------------------------------------

void output_base::reset_all_controllers()
{
   for (int channel=0; channel<16; channel++)
   {
      control_change(channel, 0x78 /*120*/ /* all sound off */, 0);
      control_change(channel, 0x79 /*121*/ /* reset controllers */, 0);
      control_change(channel, 7 /* reset volume */, 127);
      control_change(channel, 10 /* reset pan */, 64);
      pitch_bend(channel, PITCH_BEND_CENTER);
   }
}
         
      } // namespace core_midi
      
      
   } // namespace midi
   
   
} // namespace music




