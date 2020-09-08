#pragma once


namespace music
{
   
   
   namespace midi
   {
      
      
      namespace core_midi
      {
         /**
          * @ingroup midi.players
          *
          * The base class for OSX output classes
          */
         class output_base :
            virtual public ::music::midi::message_out
         {
         public:
            MIDIClientRef m_client;
            int m_last_note;
            int m_last_channel;
            bool m_playing;
            
            output_base();
            virtual ~output_base();
            
            void playNote(int pitchID, int volume, int duration, int channel, int instrument);
            void stopNote();
            
         //   virtual void note_on(const int note, const int volume, const int channel) = 0;
         //   virtual void note_off(const int note, const int channel) = 0;
         //   virtual void prog_change(const int instrument, const int channel) = 0;
         //   virtual void controlchange(const int controller, const int value, const int channel) = 0;
         //   virtual void pitch_bend(const int value, const int channel) = 0;
            
            
            virtual ::estatus note_on(int iChannel, unsigned char uchNote, unsigned char uchVelocity) = 0;
            virtual ::estatus note_off(int iChannel, unsigned char uchNote, unsigned char uchVelocity) = 0;
            virtual ::estatus program_change(int iChannel, unsigned char uchProgram) = 0;
            virtual void control_change(int iChannel, unsigned char uchController, unsigned char uchValue) = 0;
            virtual void pitch_bend(int iChannel, unsigned short ushBend) = 0;
            
            void reset_all_controllers();
         };

         
      } // namespace core_midi
      
      
   } // namespace midi
   
   
} // namespace music




