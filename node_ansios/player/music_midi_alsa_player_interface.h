#pragma once


namespace music
{


   namespace midi_alsa
   {


      namespace player
      {



         class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA player :
            virtual public callback,
            virtual public ::music::midi::player::player
         {
         public:


            player_interface(sp(::base::application) papp);
            virtual ~player_interface();

         };


      } // namespace player


   } // namespace midi_alsa


} // namespace music


