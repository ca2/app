// Created by camilo on 2022-03-09 21:11 <3ThomasBorregaardS�rensen!!


#ifdef WINDOWS
//
#include <MMReg.h>
////#include <Ks.h>
////#include <Ksmedia.h>
//
#else
//
////#include "acme/operating_system/cross/windows/windows_mmeapi.h"
////#include "acme/operating_system/cross/windows/windows_defs.h"

#if defined(WINDOWS)

#include <guiddef.h>

#else

typedef struct _GUID {
   unsigned long  Data1;
   unsigned short Data2;
   unsigned short Data3;
   unsigned char  Data4[ 8 ];
} GUID;

#endif

typedef struct {
   ::u16  wFormatTag;
   ::u16  nChannels;
   ::u32 nSamplesPerSec;
   ::u32 nAvgBytesPerSec;
   ::u16  nBlockAlign;
   ::u16  wBitsPerSample;
   ::u16  cbSize;
} WAVEFORMATEX;


typedef struct
{
   WAVEFORMATEX Format;
   union
   {
      ::u16 wValidBitsPerSample;
      ::u16 wSamplesPerBlock;
      ::u16 wReserved;
   } Samples;
   ::u32        dwChannelMask;
   GUID         SubFormat;
} WAVEFORMATEXTENSIBLE, *PWAVEFORMATEXTENSIBLE;

#endif // !defined WINDOWS



