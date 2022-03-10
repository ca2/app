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

//static void CALLBACK rdpsnd_audio_callback_function(HWAVEOUT hwo, ::u32 uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
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

//#ifdef WINDOWS
////
//#include <MMReg.h>
//////#include <Ks.h>
//////#include <Ksmedia.h>
////
//#else
////
//////#include "acme/operating_system/cross/windows/windows_mmeapi.h"
//////#include "acme/operating_system/cross/windows/windows_defs.h"
//typedef struct _GUID {
//   unsigned long  Data1;
//   unsigned short Data2;
//   unsigned short Data3;
//   unsigned char  Data4[ 8 ];
//} GUID;
//typedef struct {
//   ::u16  wFormatTag;
//   ::u16  nChannels;
//   ::u32 nSamplesPerSec;
//   ::u32 nAvgBytesPerSec;
//   ::u16  nBlockAlign;
//   ::u16  wBitsPerSample;
//   ::u16  cbSize;
//} WAVEFORMATEX;
//
//
//typedef struct
//{
//   WAVEFORMATEX Format;
//   union
//   {
//      ::u16 wValidBitsPerSample;
//      ::u16 wSamplesPerBlock;
//      ::u16 wReserved;
//   } Samples;
//   ::u32        dwChannelMask;
//   GUID         SubFormat;
//} WAVEFORMATEXTENSIBLE, *PWAVEFORMATEXTENSIBLE;
//
//#endif // !defined WINDOWS


#include "out.h"

#include "speaker.h"

#include "sound_track_player.h"


