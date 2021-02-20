#pragma once


#define  VERSION_MINOR              0x00
#define  VERSION_MAJOR              0x04
#define  SEQ_VERSION                ((u32)(::u16)((byte)VERSION_MINOR | (((::u16)(byte)VERSION_MAJOR) << 8)))

#define MMSG_DONE                   (WM_USER+20)


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         class buffer;
         class sequence;
         class sequence_thread;


         class CLASS_DECL_MUSIC_MIDI_MMSYSTEM midi_callback_data
         {
         public:


            sequence *          m_psequence;


         };


         class CLASS_DECL_MUSIC_MIDI_MMSYSTEM sequence :
            virtual public ::music::midi::sequence
         {
         public:

            class buffer_array;


            class buffer
            {
            public:


               MIDIHDR              m_midihdr;
               memory    m_storage;
               bool                 m_bPrepared;

               bool IsPrepared();
               void Reset();
               void Initialize(i32 iSize, uptr dwUser);

               ::e_status     midiStreamOut(HMIDISTRM hmidiout);
               ::e_status     midiOutPrepareHeader(HMIDIOUT hmidiout);
               ::e_status     midiOutUnprepareHeader(HMIDIOUT hmidiout);


               inline LPMIDIHDR GetMidiHdr() { return &m_midihdr; }

               void SetNextMidiHdr(LPMIDIHDR lpNext);


            };


            class buffer_array :
               public array < buffer, buffer >
            {
            public:


               void Reset();
               void Initialize(i32 iCount, i32 iSize, uptr dwUser);


               ::e_status     midiStreamOut(HMIDISTRM hmidiout);
               ::e_status     midiOutPrepareHeader(HMIDIOUT hmidiout);
               ::e_status     midiOutUnprepareHeader(HMIDIOUT hmidiout);

            };

            class event :
               public ::music::midi::sequence::event
            {
            public:


               LPMIDIHDR                     m_lpmh;


            };


            buffer_array                  m_buffera;

            HMIDISTRM                     m_hstream;

            midi_callback_data            m_midicallbackdata;




            sequence(::layered * pobjectContext);
            virtual ~sequence();


            inline u32 GetState();
            inline u32 GetPreviousState();
            u32 SetState(u32 uiState);

            void SetSpecialModeV001Flag(bool bSet = true);

            void MuteAll(bool bMute = true, i32 iExcludeTrack = -1);
            void MuteTrack(i32 iIndex, bool bMute = true);


            virtual i32 GetDefaultCodePage();

            void Prepare(::ikaraoke::data & data);
            void Prepare(i32 iTrack, ::ikaraoke::data & data);
            void Prepare(
            string2a & str2a,
            imedia_position_2darray & tka2DTokensTicks,
            i32 iMelodyTrack,
            int2a & ia2TokenLine,
            ::ikaraoke::data & data);

            imedia_time GetPositionTicks();
            void SetLevelMeter(i32 iLevel);
            ::e_status     CloseStream();
            bool SetMidiOutDevice(u32 uiDevice);
            i32 SetKeyShift(i32 iKeyShift);
            i32 GetKeyShift();

            void OnMidiPlaybackEnd(::music::midi::sequence::event * pevent);
            i32 SetTempoShift(i32 iTempoShift);

            void OnPositionCB(LPMIDIHDR lpmidihdr);
            void OnDone(HMIDISTRM hmidistream, LPMIDIHDR lpmidihdr);
            virtual void GetTimeLength(imedia_time & time);
            virtual void GetPositionLength(imedia_time & position);

            using ::ikaraoke::karaoke::TimeToPosition;
            using ::ikaraoke::karaoke::PositionToTime;

            virtual imedia_time TimeToPosition(imedia_time time);
            virtual imedia_time PositionToTime(imedia_time position);

            virtual bool IsOpened();

            virtual bool IsNull();
            virtual void SetTempoChangeFlag(bool bSet = true);
            virtual bool IsChangingTempo();

            virtual i32 GetTempoShift();
            virtual void GetMidiDoneData(::music::midi::LPMIDIDONEDATA lpmdd);
            virtual bool IsInSpecialModeV001();
            virtual bool WasInSpecialModeV001();
            virtual void set_operation(e_operation eoperation);

            virtual void OnEvent(::music::midi::sequence::event * pevent);


            ::e_status     AllocBuffers();

            VOID FreeBuffers();

            //::e_status     OpenFile(const char * lpFileName, i32 openMode);
            ::e_status     OpenFile(::music::midi::sequence & sequence, i32 iOpenMode);
            ::e_status     OpenFile(::file::file & ar, i32 openMode);
            ::e_status     OpenFile(const char * lpFileName, i32 openMode);
            ::e_status     OpenFile(memory * pmemorystorage, i32 openMode, ::music::e_storage estorage);

            ::e_status     CloseFile();
            ::e_status     SaveFile(const char * lpFileName);
            ::e_status     SaveFile();
            ::e_status     SaveFile(file_pointer &ar);

            ::e_status     Preroll(::thread * pthread, ::music::midi::LPPREROLL lpPreroll, bool bThrow);
            ::e_status     Start();

            ::e_status     Pause();

            ::e_status     Restart();

            //::e_status     Stop(u32 dwEllapse);
            ::e_status     Stop();

            void get_position(imedia_time  & time);
            void get_time(imedia_time  & time);

            ::e_status     get_ticks(imedia_time & time);
            ::e_status     get_millis(imedia_time & time);


            imedia_time MillisecsToTicks(imedia_time msOffset);

            imedia_time TicksToMillisecs(imedia_time tkOffset);

            bool IsPlaying();

            static void CALLBACK MidiOutProc(HMIDIOUT hmo, ::u32 wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);


            bool IsSettingPosition();
            void SetSettingPositionFlag(bool bSet = true);

            imedia_time GetQuarterNote();


            inline __pointer(::music::midi::mmsystem::buffer) file()
            {
               return get_file();
            }

            inline __pointer(::music::midi::mmsystem::sequence_thread) thread()
            {
               return m_pthread;
            }

            using ::music::midi::sequence::create_new_event;
            virtual ::music::midi::sequence::event * create_new_event(::music::midi::sequence::e_event eevent, LPMIDIHDR lpmidihdr);

         };


      } // namespace mmsystem


   } // namespace midi


} // namespace music







