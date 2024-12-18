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

//static void CALLBACK rdpsnd_audio_callback_function(HWAVEOUT hwo, unsigned int uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
//
//CLASS_DECL_AURA int out_push_packet(WAVE_OUT_PACKET * ppacket);
//CLASS_DECL_AURA WAVE_OUT_PACKET * out_pop_packet(char chChannel);


//using out_packet_array = ref_array < WAVEOUT_PACKET >;


namespace wave
{

   class player;

   /// Intended purpose of player performance.
   enum enum_purpose
   {

      e_purpose_default,
      e_purpose_playback,
      e_purpose_live,
      e_purpose_playground

   };

} // namespace wave


namespace aqua
{


   class audio;


   class audio_mixer;


   class audio_mixer_user;


   class sound_track_player;


} // namespace aqua

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
//   unsigned short  wFormatTag;
//   unsigned short  nChannels;
//   unsigned int nSamplesPerSec;
//   unsigned int nAvgBytesPerSec;
//   unsigned short  nBlockAlign;
//   unsigned short  wBitsPerSample;
//   unsigned short  cbSize;
//} WAVEFORMATEX;
//
//
//typedef struct
//{
//   WAVEFORMATEX Format;
//   union
//   {
//      unsigned short wValidBitsPerSample;
//      unsigned short wSamplesPerBlock;
//      unsigned short wReserved;
//   } Samples;
//   unsigned int        dwChannelMask;
//   GUID         SubFormat;
//} WAVEFORMATEXTENSIBLE, *PWAVEFORMATEXTENSIBLE;
//
//#endif // !defined WINDOWS

//
//#include "out.h"
//
//#include "speaker.h"
//
//#include "sound_track_player.h"
//
//


namespace text_to_speech
{


   class speaker;


   class client;


} // namespace text_to_speech



