#pragma once


namespace music
{


   namespace midi
   {


      namespace core_midi
      {


         class player_callback;


         class CLASS_DECL_MUSIC_MIDI_CORE_MIDI player :
            virtual public ::music::midi::player::player
         {
         public:


            player(::layered * pobjectContext);
            virtual ~player();



            void install_message_routing(::channel * pchannel) override;


            //bool PlayRate(double dRate = 0.0, u32 dwEllapse = 500) override;
            //bool Play(imedia_position tkStart, u32 dwEllapse = 500) override;

            virtual bool init_thread() override;
            virtual void term_thread() override;
            virtual void pre_translate_message(::message::message * pmessage) override;
            void OnMmsgDone(::music::midi::sequence *pSeq) override;
            DECL_GEN_SIGNAL(OnUserMessage);
            //virtual void SaveFile(memory & memory) override;
            void SetPosition(double dRate) override;
            void pause() override;
            //void close_file() override;
            //void SendReset();
            //virtual bool ExecuteCommand(enum_command ecommand, u32 dwEllapse) override;
            virtual void OnMidiOutDeviceChange() override;

            //virtual var get_midi_out_device() override;
            //void PostNotifyEvent(e_notify_event eevent) override;

            //imedia_position RateToTicks(double dRate) override;

            bool SetTempoShift(i32 iTempoShift);

            //bool SetMidiOutDevice(u32 uiDevice) override;

            //virtual ::estatus     set_client(::music::midi::player_client * pclient) override;

            ::estatus     Initialize(::thread * pthread);

            bool IsPlaying() override;

            //void PostGMReset() override;
            //void PostTempoChange() override;
            //void SendTempoChange() override; // verificar


            //DECL_GEN_SIGNAL(OnNotifyEvent);
            DECL_GEN_SIGNAL(OnMultimediaMidiOutputMessageDone);
            //DECL_GEN_SIGNAL(OnMultimediaMidiOutputMessagePositionCB);

            // midi central listener
            virtual void on_attribute_change(::message::message * pmessage) override;


         };


      } // namespace core_midi


   } // namespace midi


} // namespace music



