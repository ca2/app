#pragma once


#ifndef _WAVEFORMATEX_
#define _WAVEFORMATEX_

/*
 *  extended waveform format structure used for all non-PCM formats. this
 *  structure is common to all non-PCM formats.
 */
typedef struct tWAVEFORMATEX
{
    ::u16        wFormatTag;         /* format type */
    ::u16        nChannels;          /* number of channels (i.e. mono, stereo...) */
    ::u32       nSamplesPerSec;     /* sample rate */
    ::u32       nAvgBytesPerSec;    /* for buffer estimation */
    ::u16        nBlockAlign;        /* block size_i32 of data */
    ::u16        wBitsPerSample;     /* number of bits per sample of mono data */
    ::u16        cbSize;             /* the count in bytes of the size_i32 of */
                                    /* extra information (after cbSize) */
} WAVEFORMATEX, *PWAVEFORMATEX, *NPWAVEFORMATEX, *LPWAVEFORMATEX;

#endif /* _WAVEFORMATEX_ */


#if !defined(WINDOWS)


typedef struct tag_WAVEHDR
{
   byte *      lpbyte;
   ::u32       uiCount;
} WAVEHDR, * LPWAVEHDR;



#endif



#if !defined(WINDOWS)



typedef void * HWAVEOUT;


typedef int MMRESULT;




#endif

