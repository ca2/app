#pragma once


#ifdef __cplusplus
extern "C" {
#endif


typedef struct _WAVEOUT
{

   void * waveoutcontext;

   ::i32(*waveout_start)(void * waveoutcontext);

   ::i32(*waveout_write)(void * waveoutcontext, const void * pdata, ::u32 s);

   ::i32(*waveout_stop)(void * waveoutcontext);

   ::i32(*waveout_close)(void * waveoutcontext);

} WAVEOUT, *LPWAVEOUT;



typedef struct _AUDIOFORMAT
{

   ::i32   m_iChannels;
   ::i32   m_iSamplePerSec;
   ::i32   m_iBitsPerSample;

} AUDIOFORMAT, * LPAUDIOFORMAT;


#define WAVEOUT_MESSAGE_PACKET


typedef void WAVEOUT_CALLBACK(LPWAVEOUT pwaveout, ::u32 emessage, void * pdata, ::u32 s);

typedef WAVEOUT_CALLBACK * LPWAVEOUT_CALLBACK;

//#ifndef CLASS_DECL_AURA
//#if defined(_acid_project)
//#define CLASS_DECL_AURA
//#elif defined(_AURA_LIBRARY)
//#define CLASS_DECL_AURA  _CLASS_DECL_EXPORT
//#define LIBIDN_BUILDING
//#else
//#define CLASS_DECL_AURA  _CLASS_DECL_IMPORT
//#endif
//#endif

typedef LPWAVEOUT( * LPWAVEOUT_OPEN )(::i32 iChanel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);


CLASS_DECL_AQUA LPWAVEOUT waveout_open(::i32 iChanel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);

CLASS_DECL_AQUA ::i32 waveout_start(LPWAVEOUT pwaveout);

CLASS_DECL_AQUA ::i32 waveout_write(LPWAVEOUT pwaveout, const void * pdata, ::u32 s);

CLASS_DECL_AQUA ::i32 waveout_stop(LPWAVEOUT pwaveout);

CLASS_DECL_AQUA ::i32 waveout_close(LPWAVEOUT pwaveout);



#ifdef __cplusplus
} // extern "C"
#endif
