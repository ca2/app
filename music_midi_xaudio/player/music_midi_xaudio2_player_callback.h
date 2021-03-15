#pragma once


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         namespace player
         {


            class CLASS_DECL_MUSIC_MIDI_MMSYSTEM callback :
               virtual public ::music::midi::player::callback_interface
            {
            public:



               friend class window;
               window m_wnd;

               callback(::context_object * pcontextobject);
               virtual ~callback();

               virtual bool initialize();
               virtual bool finalize();

               virtual void OnMmsgDone(::music::midi::sequence *pSeq, ::music::midi::LPMIDIDONEDATA lpmdd);
               virtual void OnMidiPlayerNotifyEvent(::music::midi::player::notify_event * pdata);
               virtual void OnMidiLyricEvent(array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> * pevents);


            };


         } // namespace player


      } // namespace mmsystem


   } // namespace midi_mmsystem


} // namespace music








