#pragma once


namespace music
{


   namespace midi
   {
      
      
      namespace core_midi
      {

         
         class CLASS_DECL_MUSIC_MIDI_CORE_MIDI file :
            virtual public ::music::midi::file
         {
         public:



            file(::layered * pobjectContext);
            virtual ~file();


            /*         double GetTempoShiftRate();

             bool IsTrackMute(i32 iIndex);

             void MuteAll(bool bMute = true, i32 iExcludeTrack = -1);

             void MuteTrack(i32 iIndex, bool bMute = true);

             ::estatus     WorkSeekBegin();

             ::estatus     CalcTkLength();

             ::estatus     CreateTempoMap();

             ::estatus     ImmediatePutTempoChange();

             ::estatus     GetTempoEvent(::music::midi::event & event);

             void OnStop();

             u32 GetImageSize();

             LPBYTE GetImage();

             ::estatus     Format0();

             ::estatus     InsertTempoEvent();

             ::music::midi::tempo_map_entry * GetTempoMapEntry(const imedia_time & position);

             i32 GetTempoShift();

             ::estatus     SetTempoShift(i32 iTempoShift);

             void ToWorkStorage();

             void FromWorkStorage();

             i32 GetKeyShift();

             i32 SetKeyShift(i32 iKeyShift);

             bool IsSoftKaraokeFile(bool bWork = false, string_array * pstra = nullptr);

             bool IsXFFile();

             bool IsTune1000File();

             bool IsOpened();

             ::estatus     RebuildIndex();

             ::estatus     WriteHeader(MIDIFILEHDR * lpmfh);

             ::estatus     ChangeEventDelta(::music::midi::event *pEvent, imedia_time tkNewDelta);

             ::estatus     ReplaceSameDeltaEvent(::music::midi::event & pEventNew);

             ::estatus     GetPreviousEvent(::music::midi::event * pPreviousEvent, ::music::midi::event * pEvent);

             ::estatus     SaveFile(const char * lpFilePath);

             ::estatus     WorkWriteXFTracks(string_array & tokena, imedia_position_array & positiona, ::music::xf::info_header & xfinfoheader);

             i32 CalcMelodyTrack(::music::midi::events ** ppEvents, imedia_position_array * pTicks);

             i32 WorkCalcMelodyTrack(::music::midi::events ** ppEvents, imedia_position_array & positiona, int_array & iaTokenLine);

             i32 GetFormat();

             ::estatus     WorkMergeTracks();

             ::estatus     WorkStreamRender(LPMIDIHDR lpmh, imedia_time tkMax, u32 cbPrerollNomimalMax);

             ::estatus     WorkGetNextEvent(::music::midi::event * & pevent, imedia_time tkMax, bool bTkMaxInclusive);

             ::estatus     WorkGetNextRawEvent(::music::midi::event * & pevent, imedia_time tkMax, bool bTkMaxInclusive);

             ::estatus     WorkGetNextRawMidiEvent(::music::midi::event * & pevent, imedia_time tkMax, bool bTkMaxInclusive);

             ::estatus     WorkSeek(::imedia_time tkPosition, LPMIDIHDR lpmh);

             void delete_contents();

             i32 GetDivision();

             imedia_time GetPosition();

             void AttachSeekSync(::ikaraoke::events_tracks_v1 * ptracksv1);

             bool IsNull();

             void WorkSeekEnd();

             ::estatus     OpenFile(::music::midi::file::buffer &file, i32 openMode);

             ::estatus     OpenFile(::file::file & file, i32 openMode);

             ::estatus     OpenFile(primitive::memory * pmemstorage, i32 openMode, ::music::e_storage);

             ::estatus     OpenFile(primitive::memory * pmemstorage, ::music::midi::file::e_open eopenmode, ::music::e_storage estorage);

             ::estatus     SaveFile(::file::file & file);

             ::estatus     CloseFile();

             ::estatus     GetFileInfo(PSMFFILEINFO psfi);

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

             ::estatus     StreamRender(LPMIDIHDR lpmh, imedia_time tkMax, u32 cbPrerollNomimalMax);

             ::estatus     StreamEvent(imedia_time tkDelta, ::music::midi::event * Event, LPMIDIHDR lpmh, imedia_time tkMax, u32 cbPrerollNomimalMax);

             ::estatus     StreamEventF1(imedia_time tkDelta, array < ::music::midi::event *, ::music::midi::event * > & eventptra, LPMIDIHDR lpmh, imedia_time tkMax, u32 cbPrerollNomimalMax);

             ::estatus     seek(imedia_time tkPosition, LPMIDIHDR lpmh);

             ::estatus     seek(imedia_time tkPosition);

             ::estatus     Build();

             ::estatus     GetNextEvent(::music::midi::event *& pevent, imedia_time tkMax, bool   bTkMaxInclusive);

             ::estatus     GetNextEventTkPosition(imedia_time * pTkPosition, imedia_time tkMax);

             void _SyncSeek(imedia_time tkPosition, ::ikaraoke::events_tracks_v1 * ptracksv1);

             void _SyncSeek(imedia_time tkPosition);

             ::estatus     InsertParmData(imedia_time tkDelta, LPMIDIHDR lpmh);

             ::estatus     InsertLyricEvents(::ikaraoke::lyric_event_v1 * pLyricEvent, LPMIDIHDR lpmh);

             ::estatus     InsertPadEvent(imedia_time tkDelta, LPMIDIHDR lpmh);

             void SetOpened(bool bOpened = true);
             */


         };
         
         
      } // namespace core_midi


   } // namespace midi


} // namespace music




