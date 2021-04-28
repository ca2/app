#pragma once


namespace music
{


   namespace midi
   {
      
      
      namespace core_midi
      {


         class file;
         class sequence;
         class sequence_thread;


         class CLASS_DECL_VERIWELL_MULTIMEDIA midi_callback_data
         {
         public:


            sequence *          m_psequence;


         };


         class CLASS_DECL_MUSIC_MIDI_CORE_MIDI sequence :
            virtual public ::music::midi::sequence
         {
         public:

            class buffer_array;


            class buffer
            {
            public:


               MIDIHDR              m_midihdr;
               memory               m_storage;
               bool                 m_bPrepared;

               bool IsPrepared();
               void Reset();
               void Initialize(i32 iSize, u32 dwUser);

               inline LPMIDIHDR GetMidiHdr() { return &m_midihdr; }

               void SetNextMidiHdr(LPMIDIHDR lpNext);


            };


            class buffer_array :
               public array < buffer, buffer >
            {
            public:


               void Reset();
               void Initialize(i32 iCount, i32 iSize, u32 dwUser);

            };

            
            class event :
            public ::music::midi::sequence::event
            {
            public:


               LPMIDIHDR                     m_lpmh;


            };
            
            buffer_array                        m_buffera;

            midi_callback_data                  m_midicallbackdata;




            u64                                 m_uiStart;
            bool                                m_bStart;

            
            sequence(::object * pobject);
            virtual ~sequence();


            void MuteAll(bool bMute = true, i32 iExcludeTrack = -1) override;
            void MuteTrack(i32 iIndex, bool bMute = true) override;


            virtual i32 GetDefaultCodePage() override;

            void SetLevelMeter(i32 iLevel) override;
            i32 SetKeyShift(i32 iKeyShift) override;
            i32 GetKeyShift() override;

            void OnMidiPlaybackEnd(::music::midi::sequence::event * pevent) override;
            i32 SetTempoShift(i32 iTempoShift);

            void OnPositionCB(LPMIDIHDR lpmidihdr);

            virtual __pointer(::music::midi::message_out) get_message_out() override;

            using ::ikaraoke::karaoke::TimeToPosition;
            using ::ikaraoke::karaoke::PositionToTime;

            virtual imedia_time TimeToPosition(imedia_time time) override;
            virtual imedia_time PositionToTime(imedia_time position) override;

            virtual bool IsOpened() override;

            virtual bool IsNull();
            virtual void SetTempoChangeFlag(bool bSet = true) override;
            virtual bool IsChangingTempo() override;

            virtual double GetTempoShift() override;


            virtual ::e_status     Start();

            virtual ::e_status     Stop();


            ::e_status     get_ticks(imedia_time & time) override;
            ::e_status     get_millis(imedia_time & time) override;


            imedia_time MillisecsToTicks(imedia_time msOffset) override;

            imedia_time TicksToMillisecs(imedia_time tkOffset) override;

            bool IsPlaying() override;

            bool IsSettingPosition() override;
            void SetSettingPositionFlag(bool bSet = true) override;

            imedia_time GetQuarterNote() override;


            inline __pointer(::music::midi::core_midi::file) file()
            {
               
               return get_file();
               
            }
            

            inline __pointer(::music::midi::core_midi::sequence_thread) thread()
            {
               return m_pthread;
            }

            virtual void OnEvent(::music::midi::sequence::event * pevent) override;
            
            using ::music::midi::sequence::create_new_event;
            virtual __pointer(::music::midi::sequence::event) create_new_event(sequence::e_event eevent, LPMIDIHDR lpmidihdr);

            virtual __pointer(::music::midi::play_thread) on_midi_sequence_start() override;

            ::music::midi::event * midi_sequence_get_next_event();

         };

         
      } // namespace core_midi


   } // namespace midi


} // namespace music



