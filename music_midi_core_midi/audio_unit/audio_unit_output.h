//
//  audio_unit.hpp
//  music_midi_core_audio
//
//  Created by Camilo Sasuke Tsumanuma on 9/8/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once


namespace music
{
   
   
   namespace midi
   {
      
      
      namespace audio_unit
      {

         /**
          * @ingroup midi.players
          *
          * An OS X player that uses AudioUnit to output to the built-in software synthesizer.
          */
         class output :
            virtual public ::music::midi::core_midi::output_base
         {
         public:
            
            
            AUGraph        m_graph;
            AudioUnit      m_synth_unit;
            string         m_strCustomSoundFont;
            
            
            output(::object * pobject, const char* custom_sound_font);
            ~output();
            
            
            void setBank(u8 midiChannelInUse);
            void programChange(u8 progChangeNum, u8 midiChannelInUse);

            
            bool outputToDisk(const char* outputFilePath,
                              const char* data,
                              const int data_size,
                              string_array& errorMessages);
            
            virtual void note_on(int iChannel, unsigned char uchNote, unsigned char uchVelocity) ;
            virtual void note_off(int iChannel, unsigned char uchNote, unsigned char uchVelocity) ;
            virtual void program_change(int iChannel, unsigned char uchProgram);
            virtual void control_change(int iChannel, unsigned char uchController, unsigned char uchValue);
            virtual void pitch_bend(int iChannel, unsigned short ushBend);
            
         };

         
      } // namespace audio_unit
      
      
   } // namespace midi
   
   
} // namespace music




