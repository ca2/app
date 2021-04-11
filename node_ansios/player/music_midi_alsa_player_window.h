#pragma once


namespace music
{


   namespace midi_alsa
   {


      namespace player
      {


         class callback;


         class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA window :
            public ::user::interaction
         {
         public:


            ::music::midi::player::callback * m_pcallback;


            window(sp(::base::application) papp);
            virtual ~window();

            ::music::midi::player::callback * get_callback();

            using ::user::interaction::create;
            virtual bool create();

            void set_callback(::music::midi::player::callback * pcallback);

            void install_message_handling(::message::dispatch * pinterface);

            DECLARE_MESSAGE_HANDLER(_001OnNotifyEvent);
               DECLARE_MESSAGE_HANDLER(_001OnMmsgDone);
               DECLARE_MESSAGE_HANDLER(_001OnUserMessage);
               DECLARE_MESSAGE_HANDLER(_001OnApp3388Message);
         };


      } // namespace player


   } // namespace midi_alsa


} // namespace music



