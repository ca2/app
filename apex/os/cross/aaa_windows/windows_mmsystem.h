#pragma once


typedef DWORD           FOURCC;         /* a four character code */


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
                ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) |   \
                ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ))


/* MMIO macros */
#define mmioFOURCC(ch0, ch1, ch2, ch3)  MAKEFOURCC(ch0, ch1, ch2, ch3)


//struct music_midi_stream;


//struct music_midi_out;


/* MIDI data block header */
typedef struct midihdr_tag
{
   LPSTR       lpData;               /* pointer to locked data block */
   DWORD       dwBufferLength;       /* length of data in data block */
   DWORD       dwBytesRecorded;      /* used for input only */
   dword_ptr   dwUser;               /* for client's use */
   DWORD       dwFlags;              /* assorted flags (see defines) */
   struct midihdr_tag far *lpNext;   /* reserved for driver */
   dword_ptr   reserved;             /* reserved for driver */
#if (WINVER >= 0x0400)
   DWORD       dwOffset;             /* CALLBACK offset into buffer */
   dword_ptr   dwReserved[8];        /* Reserved for MMSYSTEM */
#endif
} MIDIHDR, *PMIDIHDR, NEAR *NPMIDIHDR, FAR *LPMIDIHDR;


//typedef struct music_midi_stream *       HMIDISTRM;


//typedef struct music_midi_out *          HMIDIOUT;



//struct audio_mixer;

//typedef struct audio_mixer FAR * LPAUDIOMIXER;


//typedef LPAUDIOMIXER HMIXER;



typedef UINT        MMVERSION;  /* major (high byte), minor (low byte) */





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


WINMMAPI UINT WINAPI mixerGetNumDevs(void);

typedef struct tagMIXERcaPSA
{
   WORD            wMid;                   /* manufacturer id */
   WORD            wPid;                   /* product id */
   MMVERSION       vDriverVersion;         /* version of the driver */
   CHAR            szPname[MAXPNAMELEN];   /* product name */
   DWORD           fdwSupport;             /* misc. support bits */
   DWORD           cDestinations;          /* count of destinations */
} MIXERcaPSA, *PMIXERcaPSA, *LPMIXERcaPSA;
typedef struct tagMIXERcaPSW
{
   WORD            wMid;                   /* manufacturer id */
   WORD            wPid;                   /* product id */
   MMVERSION       vDriverVersion;         /* version of the driver */
   WCHAR           szPname[MAXPNAMELEN];   /* product name */
   DWORD           fdwSupport;             /* misc. support bits */
   DWORD           cDestinations;          /* count of destinations */
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
   WORD            wMid;                   /* manufacturer id */
   WORD            wPid;                   /* product id */
   MMVERSION       vDriverVersion;         /* version of the driver */
   CHAR            szPname[MAXPNAMELEN];   /* product name */
   DWORD           fdwSupport;             /* misc. support bits */
   DWORD           cDestinations;          /* count of destinations */
   GUID            ManufacturerGuid;       /* for extensible MID mapping */
   GUID            ProductGuid;            /* for extensible PID mapping */
   GUID            NameGuid;               /* for name lookup in registry */
} MIXERcaPS2A, *PMIXERcaPS2A, *LPMIXERcaPS2A;
typedef struct tagMIXERcaPS2W
{
   WORD            wMid;                   /* manufacturer id */
   WORD            wPid;                   /* product id */
   MMVERSION       vDriverVersion;         /* version of the driver */
   WCHAR           szPname[MAXPNAMELEN];   /* product name */
   DWORD           fdwSupport;             /* misc. support bits */
   DWORD           cDestinations;          /* count of destinations */
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
   DWORD       cbStruct;               /* size of MIXERLINE structure */
   DWORD       dwDestination;          /* zero based destination index */
   DWORD       dwSource;               /* zero based source index (if source) */
   DWORD       dwLineID;               /* unique line id for mixer device */
   DWORD       fdwLine;                /* state/information about line */
   dword_ptr   dwUser;                 /* driver specific information */
   DWORD       dwComponentType;        /* component type line connects to */
   DWORD       cChannels;              /* number of channels line supports */
   DWORD       cConnections;           /* number of connections [possible] */
   DWORD       cControls;              /* number of controls at this line */
   CHAR        szShortName[MIXER_SHORT_NAME_CHARS];
   CHAR        szName[MIXER_LONG_NAME_CHARS];
   struct
   {
      DWORD       dwType;                 /* MIXERLINE_TARGETTYPE_xxxx */
      DWORD       dwDeviceID;             /* target device ID of device type */
      WORD        wMid;                   /* of target device */
      WORD        wPid;                   /*      " */
      MMVERSION   vDriverVersion;         /*      " */
      CHAR        szPname[MAXPNAMELEN];   /*      " */
   } Target;
} MIXERLINEA, *PMIXERLINEA, *LPMIXERLINEA;
typedef struct tagMIXERLINEW
{
   DWORD       cbStruct;               /* size of MIXERLINE structure */
   DWORD       dwDestination;          /* zero based destination index */
   DWORD       dwSource;               /* zero based source index (if source) */
   DWORD       dwLineID;               /* unique line id for mixer device */
   DWORD       fdwLine;                /* state/information about line */
   dword_ptr   dwUser;                 /* driver specific information */
   DWORD       dwComponentType;        /* component type line connects to */
   DWORD       cChannels;              /* number of channels line supports */
   DWORD       cConnections;           /* number of connections [possible] */
   DWORD       cControls;              /* number of controls at this line */
   WCHAR       szShortName[MIXER_SHORT_NAME_CHARS];
   WCHAR       szName[MIXER_LONG_NAME_CHARS];
   struct
   {
      DWORD       dwType;                 /* MIXERLINE_TARGETTYPE_xxxx */
      DWORD       dwDeviceID;             /* target device ID of device type */
      WORD        wMid;                   /* of target device */
      WORD        wPid;                   /*      " */
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
   DWORD           cbStruct;           /* size in bytes of MIXERCONTROL */
   DWORD           dwControlID;        /* unique control id for mixer device */
   DWORD           dwControlType;      /* MIXERCONTROL_CONTROLTYPE_xxx */
   DWORD           fdwControl;         /* MIXERCONTROL_CONTROLF_xxx */
   DWORD           cMultipleItems;     /* if MIXERCONTROL_CONTROLF_MULTIPLE set */
   CHAR            szShortName[MIXER_SHORT_NAME_CHARS];
   CHAR            szName[MIXER_LONG_NAME_CHARS];
   union
   {
      struct
      {
         LONG    lMinimum;           /* signed minimum for this control */
         LONG    lMaximum;           /* signed maximum for this control */
      } DUMMYSTRUCTNAME;
      struct
      {
         DWORD   dwMinimum;          /* unsigned minimum for this control */
         DWORD   dwMaximum;          /* unsigned maximum for this control */
      } DUMMYSTRUCTNAME2;
      DWORD       dwReserved[6];
   } Bounds;
   union
   {
      DWORD       cSteps;             /* # of steps between min & max */
      DWORD       cbCustomData;       /* size in bytes of custom data */
      DWORD       dwReserved[6];      /* !!! needed? we have cbStruct.... */
   } Metrics;
} MIXERCONTROLA, *PMIXERCONTROLA, *LPMIXERCONTROLA;
typedef struct tagMIXERCONTROLW
{
   DWORD           cbStruct;           /* size in bytes of MIXERCONTROL */
   DWORD           dwControlID;        /* unique control id for mixer device */
   DWORD           dwControlType;      /* MIXERCONTROL_CONTROLTYPE_xxx */
   DWORD           fdwControl;         /* MIXERCONTROL_CONTROLF_xxx */
   DWORD           cMultipleItems;     /* if MIXERCONTROL_CONTROLF_MULTIPLE set */
   WCHAR           szShortName[MIXER_SHORT_NAME_CHARS];
   WCHAR           szName[MIXER_LONG_NAME_CHARS];
   union
   {
      struct
      {
         LONG    lMinimum;           /* signed minimum for this control */
         LONG    lMaximum;           /* signed maximum for this control */
      } DUMMYSTRUCTNAME;
      struct
      {
         DWORD   dwMinimum;          /* unsigned minimum for this control */
         DWORD   dwMaximum;          /* unsigned maximum for this control */
      } DUMMYSTRUCTNAME2;
      DWORD       dwReserved[6];
   } Bounds;
   union
   {
      DWORD       cSteps;             /* # of steps between min & max */
      DWORD       cbCustomData;       /* size in bytes of custom data */
      DWORD       dwReserved[6];      /* !!! needed? we have cbStruct.... */
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
   DWORD           cbStruct;       /* size in bytes of MIXERLINECONTROLS */
   DWORD           dwLineID;       /* line id (from MIXERLINE.dwLineID) */
   union
   {
      DWORD       dwControlID;    /* MIXER_GETLINECONTROLSF_ONEBYID */
      DWORD       dwControlType;  /* MIXER_GETLINECONTROLSF_ONEBYTYPE */
   } DUMMYUNIONNAME;
   DWORD           cControls;      /* count of controls pmxctrl points to */
   DWORD           cbmxctrl;       /* size in bytes of _one_ MIXERCONTROL */
   LPMIXERCONTROLA pamxctrl;       /* pointer to first MIXERCONTROL array */
} MIXERLINECONTROLSA, *PMIXERLINECONTROLSA, *LPMIXERLINECONTROLSA;
typedef struct tagMIXERLINECONTROLSW
{
   DWORD           cbStruct;       /* size in bytes of MIXERLINECONTROLS */
   DWORD           dwLineID;       /* line id (from MIXERLINE.dwLineID) */
   union
   {
      DWORD       dwControlID;    /* MIXER_GETLINECONTROLSF_ONEBYID */
      DWORD       dwControlType;  /* MIXER_GETLINECONTROLSF_ONEBYTYPE */
   } DUMMYUNIONNAME;
   DWORD           cControls;      /* count of controls pmxctrl points to */
   DWORD           cbmxctrl;       /* size in bytes of _one_ MIXERCONTROL */
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
