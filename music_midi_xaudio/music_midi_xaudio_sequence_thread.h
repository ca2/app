#pragma once



namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         class CLASS_DECL_MUSIC_MIDI_MMSYSTEM sequence_thread :
            virtual public ::music::midi::sequence_thread
         {
         public:


            sequence_thread(::layered * pobjectContext);
            virtual ~sequence_thread();


            void install_message_routing(::channel * pchannel);

            ::music::midi::sequence * get_sequence();
            void Stop(imedia_time msEllapse);

            bool PostMidiSequenceEvent(::music::midi::sequence * pseq, ::music::midi::sequence::e_event event);

            bool PostMidiSequenceEvent(::music::midi::sequence * pseq, ::music::midi::sequence::e_event event, LPMIDIHDR lpmh);

            void PostNotifyEvent(::music::midi::player::e_notify_event eevent);

            void PrerollAndWait(double rate = 0.0);
            void PrerollAndWait(imedia_position tkStart);
            void Play(double dRate = 0.0);
            void Play(imedia_position tkStart);
            void PostGMReset();
            void PostTempoChange();
            void SendTempoChange();

            void ExecuteCommand(pointer < ::music::midi::player::command > pcommand);
            void _ExecuteCommand(pointer < ::music::midi::player::command > pcommand);

            virtual bool initialize_thread() override;
            virtual i32 exit_instance();

            DECL_GEN_SIGNAL(OnCommand)
            DECL_GEN_SIGNAL(OnMidiSequenceEvent)

         };


      } // namespace mmsystem


   } // namespace midi_mmsystem


} // namespace music





