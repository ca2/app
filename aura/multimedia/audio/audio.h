#pragma once



//struct WAVE_OUT_PACKET
//{
//
//   char        m_chChannel;
//   void *      m_pdata;
//   int         m_iChannelCount;
//   int         m_iSamplesPerSec;
//
//};
//

//static void CALLBACK rdpsnd_audio_callback_function(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
//
//CLASS_DECL_AURA int out_push_packet(WAVE_OUT_PACKET * ppacket);
//CLASS_DECL_AURA WAVE_OUT_PACKET * out_pop_packet(char chChannel);


//using out_packet_array = ref_array < WAVEOUT_PACKET >;


namespace wave
{

   class player;

   /// Intended purpose of player performance.
   enum e_purpose
   {

      purpose_default,
      purpose_playback,
      purpose_live,
      purpose_playground

   };

} // namespace wave


#include "out.h"

#include "sound_track_player.h"


