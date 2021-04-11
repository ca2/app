#pragma once


//#include "music_midi_alsa_player_window.h"
//#include "music_midi_alsa_player_callback.h"
//#include "music_midi_alsa_player_interface.h"


namespace music
{


   namespace midi
   {


      namespace alsa
      {


      class sequence_thread;






         class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA player :
            virtual public ::music::midi::callback,
            virtual public ::music::midi::player
         {
         public:


            player(::object * pobject);
            virtual ~player();


            void install_message_routing(::channel * pchannel) override;


            bool PlayRate(double dRate = 0.0, ::u32 dwEllapse = 584) override;
            bool Play(imedia_position tkStart, ::u32 dwEllapse = 584) override;

            virtual bool init_thread() override;
            virtual void term_thread() override;

            virtual void pre_translate_message(::message::message * pobj) override;

            void OnMmsgDone(::music::midi::sequence *pSeq);
            DECLARE_MESSAGE_HANDLER(OnUserMessage);
               //void SaveFile(const char * lpszPathName);
            void SetPosition(double dRate);
            virtual void pause() override;
            virtual void close_file() override;
            void SendReset();
            bool ExecuteCommand(::music::midi::e_command ecommand, ::u32 dwEllapse);
            virtual void OnMidiOutDeviceChange();

            //::u32 GetMidiOutDevice();
            //void PostNotifyEvent(::music::midi::e_notify_event eevent);

            imedia_position RateToTicks(double dRate);

            bool SetTempoShift(int32_t iTempoShift);

            bool SetMidiOutDevice(::u32 uiDevice);

            ::e_status SetInterface(player * pinterface);

            ::e_status Initialize(::thread * pthread);

            bool IsPlaying();

            void PostGMReset();
            void PostTempoChange();
            void SendTempoChange(); // verificar


            DECLARE_MESSAGE_HANDLER(OnNotifyEvent);
            DECLARE_MESSAGE_HANDLER(OnMultimediaMidiOutputMessageDone);
            DECLARE_MESSAGE_HANDLER(OnMultimediaMidiOutputMessagePositionCB);

            // midi central listener
            DECLARE_MESSAGE_HANDLER(on_attribute_change);



            virtual bool OnOpenMidiPlayer();


            virtual bool Initialize(sp(::music::midi::midi) pcentral);
            virtual bool Finalize();


            virtual bool OpenMidiPlayer();


            virtual void OnMmsgDone(::music::midi::sequence *pSeq, ::music::midi::LPMIDIDONEDATA lpmdd);
            virtual void OnMidiPlayerNotifyEvent(::music::midi::notify_event * pdata);
            virtual void OnMidiLyricEvent(array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> * pevents);

         };


      } // namespace alsa


   } // namespace midi


} // namespace music






