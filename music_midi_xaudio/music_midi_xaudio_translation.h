#pragma once


#define MIDIMSG(status,channel,data1,data2) ( (u32)((status<<4) | channel | (data1<<8) | (data2<<16)) )


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         CLASS_DECL_MUSIC_MIDI_MMSYSTEM ::e_status     MMRESULT mmr;


      } // namespace mmsystem


   } // namespace midi


} // namespace music