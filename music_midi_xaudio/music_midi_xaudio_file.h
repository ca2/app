#pragma once


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         class CLASS_DECL_MUSIC_MIDI_MMSYSTEM buffer :
            virtual public ::music::midi::file::buffer
         {
         public:



            buffer(::object * pobject);
            virtual ~buffer();


            double GetTempoShiftRate();

            bool IsTrackMute(i32 iIndex);

            void MuteAll(bool bMute = true, i32 iExcludeTrack = -1);

            void MuteTrack(i32 iIndex, bool bMute = true);

            ::e_status     WorkSeekBegin();

            ::e_status     CalcTkLength();

            //::e_status     CreateTempoMap();

            ::e_status     ImmediatePutTempoChange();

            ::e_status     GetTempoEvent(::music::midi::event & event);

            void OnStop();

            u32 GetImageSize();

            LPBYTE GetImage();

            ::e_status     Format0();

            ::e_status     InsertTempoEvent();

            ::music::midi::tempo_map_entry * GetTempoMapEntry(const imedia_time & position);

            i32 GetTempoShift();

            ::e_status     SetTempoShift(i32 iTempoShift);

            void ToWorkStorage();

            void FromWorkStorage();

            i32 GetKeyShift();

            i32 SetKeyShift(i32 iKeyShift);

            bool IsSoftKaraokeFile(bool bWork = false, string_array * pstra = nullptr);

            bool IsXFFile();

            bool IsTune1000File();

            bool IsOpened();

            ::e_status     RebuildIndex();

            ::e_status     WriteHeader(MIDIFILEHDR * lpmfh);

            ::e_status     ChangeEventDelta(::music::midi::event *pEvent, imedia_time tkNewDelta);

            ::e_status     ReplaceSameDeltaEvent(::music::midi::event & pEventNew);

            ::e_status     GetPreviousEvent(::music::midi::event * pPreviousEvent, ::music::midi::event * pEvent);

            ::e_status     SaveFile(const char * lpFilePath);

            ::e_status     WorkWriteXFTracks(string_array & tokena, imedia_position_array & positiona, ::music::xf::info_header & xfinfoheader);

            //i32 CalcMelodyTrack(::music::midi::events ** ppEvents, imedia_position_array * pTicks);

            //i32 WorkCalcMelodyTrack(::music::midi::events ** ppEvents, imedia_position_array & positiona, int_array & iaTokenLine);

            i32 GetFormat();

            ::e_status     MergeTracks();

            ::e_status     WorkMergeTracks();

            ::e_status     WorkStreamRender(LPMIDIHDR lpmh, imedia_time tkMax, u32 cbPrerollNomimalMax);

            ::e_status     WorkGetNextEvent(::music::midi::event * & pevent, imedia_time tkMax, bool bTkMaxInclusive);

            ::e_status     WorkGetNextRawEvent(::music::midi::event * & pevent, imedia_time tkMax, bool bTkMaxInclusive);

            ::e_status     WorkGetNextRawMidiEvent(::music::midi::event * & pevent, imedia_time tkMax, bool bTkMaxInclusive);

            ::e_status     WorkSeek(imedia_time tkPosition, LPMIDIHDR lpmh);

            void delete_contents();

            i32 GetDivision();

            imedia_time GetPosition();

            void AttachSeekSync(::ikaraoke::events_tracks_v1 * ptracksv1);

            bool IsNull();

            void WorkSeekEnd();

            ::e_status     OpenFile(::music::midi::file::buffer &file, i32 openMode);

            ::e_status     OpenFile(::file::file & file, i32 openMode);

            ::e_status     OpenFile(memory * pmemstorage, i32 openMode, ::music::e_storage);

            ::e_status     OpenFile(memory * pmemstorage, ::music::midi::file::e_open eopenmode, ::music::e_storage estorage);

            ::e_status     SaveFile(::file::file & file);

            ::e_status     CloseFile();

            ::e_status     GetFileInfo(PSMFFILEINFO psfi);

            iptr TicksToMillisecs(imedia_time tkOffset);

            void TicksToMillisecs(imedia_time_array *pMillisArray, imedia_position_array *pTickArray, iptr tkOffset);

            void TicksToMillisecs(imedia_time_2darray *p2DMillisArray, imedia_position_2darray * p2DTicksArray, iptr tkOffset);

            void PositionToTime(imedia_time_2darray  & timea, imedia_position_2darray  & positiona, iptr tkOffset);

            void PositionToTime(imedia_time_array  & timea, imedia_position_array  & positiona, iptr tkOffset);

            imedia_time MillisecsToTicks(imedia_time msOffset);

            imedia_time PositionToTime(imedia_time msOffset);

            imedia_time TimeToPosition(imedia_time msOffset);

            void MillisecsToTicks(imedia_position_array * pTickArray, imedia_time_array *pMillisArray, imedia_time msOffset);

            void TimeToPosition(imedia_position_array & positiona, imedia_time_array & timea, imedia_time msOffset);

            ::e_status     StreamRender(LPMIDIHDR lpmh, imedia_time tkMax, u32 cbPrerollNomimalMax);

            ::e_status     StreamEvent(imedia_time tkDelta, ::music::midi::event * Event, LPMIDIHDR lpmh, imedia_time tkMax, u32 cbPrerollNomimalMax);

            ::e_status     StreamEventF1(imedia_time tkDelta, array < ::music::midi::event *, ::music::midi::event * > & eventptra, LPMIDIHDR lpmh, imedia_time tkMax, u32 cbPrerollNomimalMax);

            ::e_status     seek(imedia_time tkPosition, LPMIDIHDR lpmh);

            ::e_status     seek(imedia_time tkPosition);

            //::e_status     Build();

            ::e_status     GetNextEvent(::music::midi::event *& pevent, imedia_time tkMax, bool   bTkMaxInclusive);

            ::e_status     GetNextEventTkPosition(imedia_time * pTkPosition, imedia_time tkMax);

            void _SyncSeek(imedia_time tkPosition, ::ikaraoke::events_tracks_v1 * ptracksv1);

            void _SyncSeek(imedia_time tkPosition);

            ::e_status     InsertParmData(imedia_time tkDelta, LPMIDIHDR lpmh);

            ::e_status     InsertLyricEvents(::ikaraoke::lyric_event_v1 * pLyricEvent, LPMIDIHDR lpmh);

            ::e_status     InsertPadEvent(imedia_time tkDelta, LPMIDIHDR lpmh);

            void SetOpened(bool bOpened = true);


         };


      } // namespacemmsystem


   } // namespace midi


} // namespace music





