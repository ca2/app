#pragma once


typedef ::u32           FOURCC;         /* a four character code */


#ifdef _WIN32
#ifndef _WINMM_
#define WINMMAPI        DECLSPEC_IMPORT
#else
#define WINMMAPI
#endif
#define _loadds
#define _huge
#else
#define WINMMAPI
#endif

/*
 *
 *
 */
#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
                ((::u32)(byte)(ch0) | ((::u32)(byte)(ch1) << 8) |   \
                ((::u32)(byte)(ch2) << 16) | ((::u32)(byte)(ch3) << 24 ))


/* MMIO macros */
#define mmioFOURCC(ch0, ch1, ch2, ch3)  MAKEFOURCC(ch0, ch1, ch2, ch3)


//struct music_midi_stream;


//struct music_midi_out;


/* MIDI data block header */
typedef struct midihdr_tag
{
   char *       lpData;               /* pointer to locked data block */
   ::u32       dwBufferLength;       /* length of data in data block */
   ::u32       dwBytesRecorded;      /* used for input only */
   dword_ptr   dwUser;               /* for client's use */
   ::u32       dwFlags;              /* assorted flags (see defines) */
   struct midihdr_tag far *lpNext;   /* reserved for driver */
   dword_ptr   reserved;             /* reserved for driver */
#if (WINVER >= 0x0400)
   ::u32       dwOffset;             /* CALLBACK offset into buffer */
   dword_ptr   dwReserved[8];        /* Reserved for MMSYSTEM */
#endif
} MIDIHDR, *PMIDIHDR, NEAR *NPMIDIHDR, FAR *LPMIDIHDR;


//typedef struct music_midi_stream *       HMIDISTRM;


//typedef struct music_midi_out *          HMIDIOUT;



//struct audio_mixer;

//typedef struct audio_mixer FAR * LPAUDIOMIXER;


//typedef LPAUDIOMIXER HMIXER;



typedef ::u32        MMVERSION;  /* major (high byte), minor (low byte) */





/****************************************************************************

                    General constants and data types

****************************************************************************/


/* general constants */
#define MAXPNAMELEN      32     /* max product name length (including nullptr) */
#define MAXERRORLENGTH   256    /* max error text length (including nullptr) */
#define MAX_JOYSTICKOEMVXDNAME 260 /* max oem vxd name length (including nullptr) */

/*
 *  Microsoft Manufacturer and Product ID's (these have been moved to
 *  MMREG.H for Windows 4.00 and above).
 */
#define MM_MICROSOFT            1   /* Microsoft Corporation */
#define MM_MIDI_MAPPER          1   /* MIDI Mapper */
#define MM_WAVE_MAPPER          2   /* Wave Mapper */
#define MM_SNDBLST_MIDIOUT      3   /* Sound Blaster MIDI output port */
#define MM_SNDBLST_MIDIIN       4   /* Sound Blaster MIDI input port */
#define MM_SNDBLST_SYNTH        5   /* Sound Blaster internal synthesizer */
#define MM_SNDBLST_WAVEOUT      6   /* Sound Blaster waveform output */
#define MM_SNDBLST_WAVEIN       7   /* Sound Blaster waveform input */
#define MM_ADLIB                9   /* Ad Lib-compatible synthesizer */
#define MM_MPU401_MIDIOUT      10   /* MPU401-compatible MIDI output port */
#define MM_MPU401_MIDIIN       11   /* MPU401-compatible MIDI input port */
#define MM_PC_JOYSTICK         12   /* Joystick adapter */



#define MIXER_SHORT_NAME_CHARS   16
#define MIXER_LONG_NAME_CHARS    64



/* */
/*  MMRESULT error return values specific to the mixer API */
/* */
/* */
#define MIXERR_INVALLINE            (MIXERR_AXIS + 0)
#define MIXERR_INVALCONTROL         (MIXERR_AXIS + 1)
#define MIXERR_INVALVALUE           (MIXERR_AXIS + 2)
#define MIXERR_LASTERROR            (MIXERR_AXIS + 2)


#define MIXER_OBJECTF_HANDLE    0x80000000L
#define MIXER_OBJECTF_MIXER     0x00000000L
#define MIXER_OBJECTF_HMIXER    (MIXER_OBJECTF_HANDLE|MIXER_OBJECTF_MIXER)
#define MIXER_OBJECTF_WAVEOUT   0x10000000L
#define MIXER_OBJECTF_HWAVEOUT  (MIXER_OBJECTF_HANDLE|MIXER_OBJECTF_WAVEOUT)
#define MIXER_OBJECTF_WAVEIN    0x20000000L
#define MIXER_OBJECTF_HWAVEIN   (MIXER_OBJECTF_HANDLE|MIXER_OBJECTF_WAVEIN)
#define MIXER_OBJECTF_MIDIOUT   0x30000000L
#define MIXER_OBJECTF_HMIDIOUT  (MIXER_OBJECTF_HANDLE|MIXER_OBJECTF_MIDIOUT)
#define MIXER_OBJECTF_MIDIIN    0x40000000L
#define MIXER_OBJECTF_HMIDIIN   (MIXER_OBJECTF_HANDLE|MIXER_OBJECTF_MIDIIN)
#define MIXER_OBJECTF_AUX       0x50000000L


WINMMAPI ::u32 WINAPI mixerGetNumDevs(void);

typedef struct tagMIXERcaPSA
{
   ::u16            wMid;                   /* manufacturer id */
   ::u16            wPid;                   /* product id */
   MMVERSION       vDriverVersion;         /* version of the driver */
   char            szPname[MAXPNAMELEN];   /* product name */
   ::u32           fdwSupport;             /* misc. support bits */
   ::u32           cDestinations;          /* count of destinations */
} MIXERcaPSA, *PMIXERcaPSA, *LPMIXERcaPSA;
typedef struct tagMIXERcaPSW
{
   ::u16            wMid;                   /* manufacturer id */
   ::u16            wPid;                   /* product id */
   MMVERSION       vDriverVersion;         /* version of the driver */
   WCHAR           szPname[MAXPNAMELEN];   /* product name */
   ::u32           fdwSupport;             /* misc. support bits */
   ::u32           cDestinations;          /* count of destinations */
} MIXERcaPSW, *PMIXERcaPSW, *LPMIXERcaPSW;
#ifdef UNICODE
typedef MIXERcaPSW MIXERcaPS;
typedef PMIXERcaPSW PMIXERcaPS;
typedef LPMIXERcaPSW LPMIXERcaPS;
#else
typedef MIXERcaPSA MIXERcaPS;
typedef PMIXERcaPSA PMIXERcaPS;
typedef LPMIXERcaPSA LPMIXERcaPS;
#endif // UNICODE
typedef struct tagMIXERcaPS2A
{
   ::u16            wMid;                   /* manufacturer id */
   ::u16            wPid;                   /* product id */
   MMVERSION       vDriverVersion;         /* version of the driver */
   char            szPname[MAXPNAMELEN];   /* product name */
   ::u32           fdwSupport;             /* misc. support bits */
   ::u32           cDestinations;          /* count of destinations */
   GUID            ManufacturerGuid;       /* for extensible MID mapping */
   GUID            ProductGuid;            /* for extensible PID mapping */
   GUID            NameGuid;               /* for name lookup in registry */
} MIXERcaPS2A, *PMIXERcaPS2A, *LPMIXERcaPS2A;
typedef struct tagMIXERcaPS2W
{
   ::u16            wMid;                   /* manufacturer id */
   ::u16            wPid;                   /* product id */
   MMVERSION       vDriverVersion;         /* version of the driver */
   WCHAR           szPname[MAXPNAMELEN];   /* product name */
   ::u32           fdwSupport;             /* misc. support bits */
   ::u32           cDestinations;          /* count of destinations */
   GUID            ManufacturerGuid;       /* for extensible MID mapping */
   GUID            ProductGuid;            /* for extensible PID mapping */
   GUID            NameGuid;               /* for name lookup in registry */
} MIXERcaPS2W, *PMIXERcaPS2W, *LPMIXERcaPS2W;
#ifdef UNICODE
typedef MIXERcaPS2W MIXERcaPS2;
typedef PMIXERcaPS2W PMIXERcaPS2;
typedef LPMIXERcaPS2W LPMIXERcaPS2;
#else
typedef MIXERcaPS2A MIXERcaPS2;
typedef PMIXERcaPS2A PMIXERcaPS2;
typedef LPMIXERcaPS2A LPMIXERcaPS2;
#endif // UNICODE




#define MIXER_GETLINECONTROLSF_ALL          0x00000000L
#define MIXER_GETLINECONTROLSF_ONEBYID      0x00000001L
#define MIXER_GETLINECONTROLSF_ONEBYTYPE    0x00000002L

#define MIXER_GETLINECONTROLSF_QUERYMASK    0x0000000FL








typedef struct tagMIXERLINEA
{
   ::u32       cbStruct;               /* size of MIXERLINE structure */
   ::u32       dwDestination;          /* zero based destination index */
   ::u32       dwSource;               /* zero based source index (if source) */
   ::u32       dwLineID;               /* unique line id for mixer device */
   ::u32       fdwLine;                /* state/information about line */
   dword_ptr   dwUser;                 /* driver specific information */
   ::u32       dwComponentType;        /* component type line connects to */
   ::u32       cChannels;              /* number of channels line supports */
   ::u32       cConnections;           /* number of connections [possible] */
   ::u32       cControls;              /* number of controls at this line */
   char        szShortName[MIXER_SHORT_NAME_CHARS];
   char        szName[MIXER_LONG_NAME_CHARS];
   struct
   {
      ::u32       dwType;                 /* MIXERLINE_TARGETTYPE_xxxx */
      ::u32       dwDeviceID;             /* target device ID of device type */
      ::u16        wMid;                   /* of target device */
      ::u16        wPid;                   /*      " */
      MMVERSION   vDriverVersion;         /*      " */
      char        szPname[MAXPNAMELEN];   /*      " */
   } Target;
} MIXERLINEA, *PMIXERLINEA, *LPMIXERLINEA;
typedef struct tagMIXERLINEW
{
   ::u32       cbStruct;               /* size of MIXERLINE structure */
   ::u32       dwDestination;          /* zero based destination index */
   ::u32       dwSource;               /* zero based source index (if source) */
   ::u32       dwLineID;               /* unique line id for mixer device */
   ::u32       fdwLine;                /* state/information about line */
   dword_ptr   dwUser;                 /* driver specific information */
   ::u32       dwComponentType;        /* component type line connects to */
   ::u32       cChannels;              /* number of channels line supports */
   ::u32       cConnections;           /* number of connections [possible] */
   ::u32       cControls;              /* number of controls at this line */
   WCHAR       szShortName[MIXER_SHORT_NAME_CHARS];
   WCHAR       szName[MIXER_LONG_NAME_CHARS];
   struct
   {
      ::u32       dwType;                 /* MIXERLINE_TARGETTYPE_xxxx */
      ::u32       dwDeviceID;             /* target device ID of device type */
      ::u16        wMid;                   /* of target device */
      ::u16        wPid;                   /*      " */
      MMVERSION   vDriverVersion;         /*      " */
      WCHAR       szPname[MAXPNAMELEN];   /*      " */
   } Target;
} MIXERLINEW, *PMIXERLINEW, *LPMIXERLINEW;
#ifdef UNICODE
typedef MIXERLINEW MIXERLINE;
typedef PMIXERLINEW PMIXERLINE;
typedef LPMIXERLINEW LPMIXERLINE;
#else
typedef MIXERLINEA MIXERLINE;
typedef PMIXERLINEA PMIXERLINE;
typedef LPMIXERLINEA LPMIXERLINE;
#endif // UNICODE



typedef struct tagMIXERCONTROLA
{
   ::u32           cbStruct;           /* size in bytes of MIXERCONTROL */
   ::u32           dwControlID;        /* unique control id for mixer device */
   ::u32           dwControlType;      /* MIXERCONTROL_CONTROLTYPE_xxx */
   ::u32           fdwControl;         /* MIXERCONTROL_CONTROLF_xxx */
   ::u32           cMultipleItems;     /* if MIXERCONTROL_CONTROLF_MULTIPLE set */
   char            szShortName[MIXER_SHORT_NAME_CHARS];
   char            szName[MIXER_LONG_NAME_CHARS];
   union
   {
      struct
      {
         ::i32    lMinimum;           /* signed minimum for this control */
         ::i32    lMaximum;           /* signed maximum for this control */
      } DUMMYSTRUCTNAME;
      struct
      {
         ::u32   dwMinimum;          /* unsigned minimum for this control */
         ::u32   dwMaximum;          /* unsigned maximum for this control */
      } DUMMYSTRUCTNAME2;
      ::u32       dwReserved[6];
   } Bounds;
   union
   {
      ::u32       cSteps;             /* # of steps between min & max */
      ::u32       cbCustomData;       /* size in bytes of custom data */
      ::u32       dwReserved[6];      /* !!! needed? we have cbStruct.... */
   } Metrics;
} MIXERCONTROLA, *PMIXERCONTROLA, *LPMIXERCONTROLA;
typedef struct tagMIXERCONTROLW
{
   ::u32           cbStruct;           /* size in bytes of MIXERCONTROL */
   ::u32           dwControlID;        /* unique control id for mixer device */
   ::u32           dwControlType;      /* MIXERCONTROL_CONTROLTYPE_xxx */
   ::u32           fdwControl;         /* MIXERCONTROL_CONTROLF_xxx */
   ::u32           cMultipleItems;     /* if MIXERCONTROL_CONTROLF_MULTIPLE set */
   WCHAR           szShortName[MIXER_SHORT_NAME_CHARS];
   WCHAR           szName[MIXER_LONG_NAME_CHARS];
   union
   {
      struct
      {
         ::i32    lMinimum;           /* signed minimum for this control */
         ::i32    lMaximum;           /* signed maximum for this control */
      } DUMMYSTRUCTNAME;
      struct
      {
         ::u32   dwMinimum;          /* unsigned minimum for this control */
         ::u32   dwMaximum;          /* unsigned maximum for this control */
      } DUMMYSTRUCTNAME2;
      ::u32       dwReserved[6];
   } Bounds;
   union
   {
      ::u32       cSteps;             /* # of steps between min & max */
      ::u32       cbCustomData;       /* size in bytes of custom data */
      ::u32       dwReserved[6];      /* !!! needed? we have cbStruct.... */
   } Metrics;
} MIXERCONTROLW, *PMIXERCONTROLW, *LPMIXERCONTROLW;
#ifdef UNICODE
typedef MIXERCONTROLW MIXERCONTROL;
typedef PMIXERCONTROLW PMIXERCONTROL;
typedef LPMIXERCONTROLW LPMIXERCONTROL;
#else
typedef MIXERCONTROLA MIXERCONTROL;
typedef PMIXERCONTROLA PMIXERCONTROL;
typedef LPMIXERCONTROLA LPMIXERCONTROL;
#endif // UNICODE



/* */
/*  Commonly used control types for specifying MIXERCONTROL.dwControlType */
/* */

#define MIXERCONTROL_CONTROLTYPE_CUSTOM         (MIXERCONTROL_CT_CLASS_CUSTOM | MIXERCONTROL_CT_UNITS_CUSTOM)
#define MIXERCONTROL_CONTROLTYPE_BOOLEANMETER   (MIXERCONTROL_CT_CLASS_METER | MIXERCONTROL_CT_SC_METER_POLLED | MIXERCONTROL_CT_UNITS_BOOLEAN)
#define MIXERCONTROL_CONTROLTYPE_SIGNEDMETER    (MIXERCONTROL_CT_CLASS_METER | MIXERCONTROL_CT_SC_METER_POLLED | MIXERCONTROL_CT_UNITS_SIGNED)
#define MIXERCONTROL_CONTROLTYPE_PEAKMETER      (MIXERCONTROL_CONTROLTYPE_SIGNEDMETER + 1)
#define MIXERCONTROL_CONTROLTYPE_UNSIGNEDMETER  (MIXERCONTROL_CT_CLASS_METER | MIXERCONTROL_CT_SC_METER_POLLED | MIXERCONTROL_CT_UNITS_UNSIGNED)
#define MIXERCONTROL_CONTROLTYPE_BOOLEAN        (MIXERCONTROL_CT_CLASS_SWITCH | MIXERCONTROL_CT_SC_SWITCH_BOOLEAN | MIXERCONTROL_CT_UNITS_BOOLEAN)
#define MIXERCONTROL_CONTROLTYPE_ONOFF          (MIXERCONTROL_CONTROLTYPE_BOOLEAN + 1)
#define MIXERCONTROL_CONTROLTYPE_MUTE           (MIXERCONTROL_CONTROLTYPE_BOOLEAN + 2)
#define MIXERCONTROL_CONTROLTYPE_MONO           (MIXERCONTROL_CONTROLTYPE_BOOLEAN + 3)
#define MIXERCONTROL_CONTROLTYPE_LOUDNESS       (MIXERCONTROL_CONTROLTYPE_BOOLEAN + 4)
#define MIXERCONTROL_CONTROLTYPE_STEREOENH      (MIXERCONTROL_CONTROLTYPE_BOOLEAN + 5)
#define MIXERCONTROL_CONTROLTYPE_BASS_BOOST     (MIXERCONTROL_CONTROLTYPE_BOOLEAN + 0x00002277)
#define MIXERCONTROL_CONTROLTYPE_BUTTON         (MIXERCONTROL_CT_CLASS_SWITCH | MIXERCONTROL_CT_SC_SWITCH_BUTTON | MIXERCONTROL_CT_UNITS_BOOLEAN)
#define MIXERCONTROL_CONTROLTYPE_DECIBELS       (MIXERCONTROL_CT_CLASS_NUMBER | MIXERCONTROL_CT_UNITS_DECIBELS)
#define MIXERCONTROL_CONTROLTYPE_SIGNED         (MIXERCONTROL_CT_CLASS_NUMBER | MIXERCONTROL_CT_UNITS_SIGNED)
#define MIXERCONTROL_CONTROLTYPE_UNSIGNED       (MIXERCONTROL_CT_CLASS_NUMBER | MIXERCONTROL_CT_UNITS_UNSIGNED)
#define MIXERCONTROL_CONTROLTYPE_PERCENT        (MIXERCONTROL_CT_CLASS_NUMBER | MIXERCONTROL_CT_UNITS_PERCENT)
#define MIXERCONTROL_CONTROLTYPE_SLIDER         (MIXERCONTROL_CT_CLASS_SLIDER | MIXERCONTROL_CT_UNITS_SIGNED)
#define MIXERCONTROL_CONTROLTYPE_PAN            (MIXERCONTROL_CONTROLTYPE_SLIDER + 1)
#define MIXERCONTROL_CONTROLTYPE_QSOUNDPAN      (MIXERCONTROL_CONTROLTYPE_SLIDER + 2)
#define MIXERCONTROL_CONTROLTYPE_FADER          (MIXERCONTROL_CT_CLASS_FADER | MIXERCONTROL_CT_UNITS_UNSIGNED)
#define MIXERCONTROL_CONTROLTYPE_VOLUME         (MIXERCONTROL_CONTROLTYPE_FADER + 1)
#define MIXERCONTROL_CONTROLTYPE_BASS           (MIXERCONTROL_CONTROLTYPE_FADER + 2)
#define MIXERCONTROL_CONTROLTYPE_TREBLE         (MIXERCONTROL_CONTROLTYPE_FADER + 3)
#define MIXERCONTROL_CONTROLTYPE_EQUALIZER      (MIXERCONTROL_CONTROLTYPE_FADER + 4)
#define MIXERCONTROL_CONTROLTYPE_SINGLESELECT   (MIXERCONTROL_CT_CLASS_LIST | MIXERCONTROL_CT_SC_LIST_SINGLE | MIXERCONTROL_CT_UNITS_BOOLEAN)
#define MIXERCONTROL_CONTROLTYPE_MUX            (MIXERCONTROL_CONTROLTYPE_SINGLESELECT + 1)
#define MIXERCONTROL_CONTROLTYPE_MULTIPLESELECT (MIXERCONTROL_CT_CLASS_LIST | MIXERCONTROL_CT_SC_LIST_MULTIPLE | MIXERCONTROL_CT_UNITS_BOOLEAN)
#define MIXERCONTROL_CONTROLTYPE_MIXER          (MIXERCONTROL_CONTROLTYPE_MULTIPLESELECT + 1)
#define MIXERCONTROL_CONTROLTYPE_MICROTIME      (MIXERCONTROL_CT_CLASS_TIME | MIXERCONTROL_CT_SC_TIME_MICROSECS | MIXERCONTROL_CT_UNITS_UNSIGNED)
#define MIXERCONTROL_CONTROLTYPE_MILLITIME      (MIXERCONTROL_CT_CLASS_TIME | MIXERCONTROL_CT_SC_TIME_MILLISECS | MIXERCONTROL_CT_UNITS_UNSIGNED)

/* */
/*  MIXERLINECONTROLS */
/* */

typedef struct tagMIXERLINECONTROLSA
{
   ::u32           cbStruct;       /* size in bytes of MIXERLINECONTROLS */
   ::u32           dwLineID;       /* line id (from MIXERLINE.dwLineID) */
   union
   {
      ::u32       dwControlID;    /* MIXER_GETLINECONTROLSF_ONEBYID */
      ::u32       dwControlType;  /* MIXER_GETLINECONTROLSF_ONEBYTYPE */
   } DUMMYUNIONNAME;
   ::u32           cControls;      /* count of controls pmxctrl points to */
   ::u32           cbmxctrl;       /* size in bytes of _one_ MIXERCONTROL */
   LPMIXERCONTROLA pamxctrl;       /* pointer to first MIXERCONTROL array */
} MIXERLINECONTROLSA, *PMIXERLINECONTROLSA, *LPMIXERLINECONTROLSA;
typedef struct tagMIXERLINECONTROLSW
{
   ::u32           cbStruct;       /* size in bytes of MIXERLINECONTROLS */
   ::u32           dwLineID;       /* line id (from MIXERLINE.dwLineID) */
   union
   {
      ::u32       dwControlID;    /* MIXER_GETLINECONTROLSF_ONEBYID */
      ::u32       dwControlType;  /* MIXER_GETLINECONTROLSF_ONEBYTYPE */
   } DUMMYUNIONNAME;
   ::u32           cControls;      /* count of controls pmxctrl points to */
   ::u32           cbmxctrl;       /* size in bytes of _one_ MIXERCONTROL */
   LPMIXERCONTROLW pamxctrl;       /* pointer to first MIXERCONTROL array */
} MIXERLINECONTROLSW, *PMIXERLINECONTROLSW, *LPMIXERLINECONTROLSW;
#ifdef UNICODE
typedef MIXERLINECONTROLSW MIXERLINECONTROLS;
typedef PMIXERLINECONTROLSW PMIXERLINECONTROLS;
typedef LPMIXERLINECONTROLSW LPMIXERLINECONTROLS;
#else
typedef MIXERLINECONTROLSA MIXERLINECONTROLS;
typedef PMIXERLINECONTROLSA PMIXERLINECONTROLS;
typedef LPMIXERLINECONTROLSA LPMIXERLINECONTROLS;
#endif // UNICODE
