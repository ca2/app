#pragma once


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         namespace player
         {


            class callback;


            class CLASS_DECL_MUSIC_MIDI_MMSYSTEM window :
               public ::user::interaction
            {
            public:


               ::music::midi::player::callback_interface * m_pcallback;


               window(::object * pobject);
               virtual ~window();

               ::music::midi::player::callback_interface * get_callback();

               using ::user::interaction::create;
               virtual bool create();

               void set_callback(::music::midi::player::callback_interface * pcallback);

               void install_message_routing(::channel * pchannel);

               DECLARE_MESSAGE_HANDLER(_001OnNotifyEvent)
               DECLARE_MESSAGE_HANDLER(_001OnMmsgDone)
               DECLARE_MESSAGE_HANDLER(_001OnUserMessage)
               DECLARE_MESSAGE_HANDLER(_001OnApp3388Message)
            };


         } // namespace player


      } // namespace mmsystem


   } // namespace midi_mmsystem


} // namespace music





