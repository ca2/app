#pragma once


namespace music
{


   namespace midi_alsa
   {


      namespace player
      {


         class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA callback :
            virtual public ::music::midi::player::callback
         {
         public:



            friend class window;
            window m_wnd;

            callback(::aura::application *  papp);
            virtual ~callback();



         };


      } // namespace player


   } // namespace midi_alsa


} // namespace music








