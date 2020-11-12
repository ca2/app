#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         buffer::buffer(::layered * pobjectContext) :
            ::object(pobject),
            memory_container (pobject),
            ::music::midi::file::buffer(pobject)
         {


            m_estorage              = ::music::storage_none;

            m_tkLength              = 0;
            m_dwFormat              = 0;
            m_dwTracks              = 0;
            m_MusicTempoTimeDivision        = 0;

            m_dwPendingUserEvent    = 0;
            m_cbPendingUserEvent    = 0;
            m_hpbPendingUserEvent   = 0;

            m_iKeyShift             = 0;
            m_iTempoShift           = 0;


            m_pFileHeader = nullptr;

            keep_pointer((void **) &m_pMThd);
            keep_pointer((void **) &m_pFileHeader);

         }

         buffer::~buffer()
         {

            CloseFile();

            if(m_ptracks != nullptr)
            {
               delete m_ptracks;
               m_ptracks = nullptr;
            }

            if(m_estorage == ::music::storage_attach)
            {
               detach();
            }

         }


         ::estatus     buffer::OpenFile(::music::midi::file::buffer &file, i32 openMode)
         {

            ::estatus                   smfrc = ::success;

            m_ptracks->m_iMelodyTrackTipA = -1;

            m_iOpenMode = openMode;

            GetFlags().clear();

            if(openMode == file::OpenForParsingLevel3)
            {
               GetFlags().add(file::DisablePlayLevel1Operations);
            }

            m_ptracks->GetFlags() = GetFlags();

            u32 cbImage = file.GetImageSize();
            try
            {
               allocate(cbImage);
            }
            catch(memory_exception * pe)
            {
               TRACE( "smfOpenFile: No memory for image! [%08lX]", cbImage);
               smfrc = error_no_memory;
               delete pe;
               goto smf_Open_File_Cleanup;
            }

            byte * lpbImage;

            lpbImage = GetImage();

            ::memcpy_dup(lpbImage, file.GetImage(), cbImage);

            /* If the file exists, parse it just enough to pull out the header and
            ** build a track index.
            */
            smfrc = Build();

smf_Open_File_Cleanup:

            if (::success != smfrc)
            {
            }
            else
            {
               SetOpened();
            }

            return smfrc;
         }

         ::estatus     buffer::OpenFile(memory * pmemorystorage, i32 openMode, e_storage estorage)
         {
            ASSERT(pmemorystorage != nullptr);

            ::estatus     smfrc = ::success;

            m_ptracks->m_iMelodyTrackTipA = -1;

            m_iOpenMode = openMode;

            GetFlags().clear();

            if(openMode == file::OpenForParsingLevel3)
            {

               GetFlags().add(file::DisablePlayLevel1Operations);

            }

            m_ptracks->GetFlags() = GetFlags();

            if(estorage == ::music::storage_copy)
            {
               this->get_primitive_memory()->operator=(*pmemorystorage);
            }
            else if(estorage == ::music::storage_attach)
            {
               if(m_estorage == ::music::storage_attach)
               {
                  detach();
               }
               else if(m_estorage == ::music::storage_own)
               {
                  delete detach();
               }
               attach(pmemorystorage);
            }
            else if(estorage == ::music::storage_own)
            {
               if(m_estorage == ::music::storage_attach)
               {
                  detach();
               }
               this->get_primitive_memory()->operator=(*pmemorystorage);
            }

            m_estorage = estorage;


            /* If the file exists, parse it just enough to pull out the header and
            ** build a track index.
            */

            smfrc = Build();

            if (::success == smfrc)
            {
               SetOpened();
            }
            return smfrc;
         }


         ::estatus     buffer::OpenFile(memory * pmemorystorage, file::e_open eopenmode, e_storage estorage)
         {

            return OpenFile(pmemorystorage, (i32) eopenmode, estorage);

         }


         /*****************************************************************************
         *
         * smfOpenFile
         *
         * This function opens a MIDI file for access.
         *
         * psofs                     - Specifies the file to open and associated
         *                             parameters. Contains a valid HSMF handle
         *                             on success.
         *
         * Returns
         *   success The specified file was opened.
         *
         *   SMF_OPEN_FAILED The specified file could not be opened because it
         *     did not exist or could not be created on the disk.
         *
         *   error_invalid_file The specified file was corrupt or not a MIDI file.
         *
         *   error_no_memory There was insufficient memory to open the file.
         *
         *   SMF_INVALID_PARM The given flags or time division in the
         *     SMFOPENFILESTRUCT were invalid.
         *
         *****************************************************************************/
         ::estatus     buffer::OpenFile(::file::file & ar, i32 openMode)
         {
            ::estatus                   smfrc = ::success;

            m_ptracks->m_iMelodyTrackTipA = -1;

            m_iOpenMode = openMode;

            GetFlags().clear();

            if(openMode == file::OpenForParsingLevel3)
            {
               GetFlags().add(file::DisablePlayLevel1Operations);
            }

            m_ptracks->GetFlags() = GetFlags();


            get_memory()->transfer_from_begin(ar);

            /* If the file exists, parse it just enough to pull out the header and
            ** build a track index.
            */
            smfrc = Build();

            if (::success != smfrc)
            {
            }
            else
            {
               SetOpened();
            }

            return smfrc;
         }

         /*****************************************************************************
         *
         * smfCloseFile
         *
         * This function closes an open MIDI file.
         *
         * hSmf                      - The handle of the open file to close.
         *
         * Returns
         *   success The specified file was closed.
         *   SMF_INVALID_PARM The given handle was not valid.
         *
         * Any track handles opened from this file handle are invalid after this
         * call.
         *
         *****************************************************************************/
         ::estatus     buffer::CloseFile()
         {
            single_lock(&m_cs, TRUE);
            SetOpened(false);
            delete_contents();
            return ::success;
         }


         void buffer::delete_contents()
         {
            single_lock(&m_cs, TRUE);
            SetOpened(false);


            m_ptracks->clear();


            m_tempomap.remove_all();


            m_bPendingLyric = false;


            for(i32 i = 0; i < m_mepaOnQuarterNote.get_size(); i++)
            {
               delete m_mepaOnQuarterNote.element_at(i);
            }
            m_mepaOnQuarterNote.remove_all();


            for(i32 i = 0; i < m_mepaImmediate.get_size(); i++)
            {
               delete m_mepaImmediate.element_at(i);
            }
            m_mepaImmediate.remove_all();


            m_tkLength              = 0;
            m_dwFormat              = 0;
            m_dwTracks              = 0;
            m_MusicTempoTimeDivision        = 0;

            m_dwPendingUserEvent    = 0;
            m_cbPendingUserEvent    = 0;
            m_hpbPendingUserEvent   = 0;


            m_iKeyShift             = 0;
            m_iTempoShift           = 0;

            m_pFileHeader           = nullptr;

         }




         /******************************************************************************
         *
         * smfGetFileInfo This function gets information about the MIDI file.
         *
         * hSmf                      - Specifies the open MIDI file to inquire about.
         *
         * psfi                      - A structure which will be filled in with
         *                             information about the file.
         *
         * Returns
         *   success Information was gotten about the file.
         *   SMF_INVALID_PARM The given handle was invalid.
         *
         *****************************************************************************/
         ::estatus     buffer::GetFileInfo(
         PSMFFILEINFO            psfi)
         {
            //    PSMF                    pSmf = (PSMF)hSmf;
            //    assert(pSmf != nullptr);
            ASSERT(psfi != nullptr);

            /*
            ** Just fill in the structure with useful information.
            */
            psfi->dwTracks      = m_dwTracks;
            //psfi->dwTracks      = m_ptracks->get_size();
            psfi->dwFormat      = m_dwFormat;
            psfi->dwTimeDivision= m_MusicTempoTimeDivision;
            psfi->tkLength      = m_tkLength;

            return ::success;
         }

         /******************************************************************************
         *
         * smfTicksToMillisecs
         *
         * This function returns the millisecond offset into the file given the
         * tick offset.
         *
         * hSmf                      - Specifies the open MIDI file to perform
         *                             the conversion on.
         *
         * tkOffset                  - Specifies the tick offset into the stream
         *                             to convert.
         *
         * Returns the number of milliseconds from the start of the stream.
         *
         * The conversion is performed taking into ac::count the file's time division and
         * tempo map from the first track. Note that the same millisecond value
         * might not be valid at a later time if the tempo track is rewritten.
         *
         *****************************************************************************/
         iptr buffer::TicksToMillisecs(imedia_time tkOffset)
         {
            single_lock(&m_cs, true);
            if(!IsOpened())
               return 0xffffffff;

            ::music::midi::tempo_map_entry *  ptempo;
            i32                  idx;
            u32                 uSMPTE;
            u32                dwTicksPerSec;

            if (tkOffset > m_tkLength)
            {
               //TRACE( "sTTM: Clipping ticks to file length!");
               tkOffset = m_tkLength;
            }

            /* SMPTE time is easy -- no tempo map, just linear conversion
            ** Note that 30-Drop means nothing to us here since we're not
            ** converting to a colonized format, which is where dropping
            ** happens.
            */
            if (m_MusicTempoTimeDivision & 0x8000)
            {
               uSMPTE = -(i32)(char)((m_MusicTempoTimeDivision >> 8)&0xFF);
               if (29 == uSMPTE)
                  uSMPTE = 30;

               dwTicksPerSec = (u32)uSMPTE *
                               (u32)(byte)(m_MusicTempoTimeDivision & 0xFF);

               return (u32)muldiv32((i32) tkOffset, 1000L, dwTicksPerSec);
            }

            /* Walk the tempo map and find the nearest tick position. Linearly
            ** calculate the rest (using MATH.ASM)
            */

            for (idx = 0; idx < m_tempomap.get_size(); idx++)
            {
               ptempo = &m_tempomap.element_at(idx);
               if (tkOffset < ptempo->tkTempo)
                  break;
            }

            if(idx <= 0)
               idx = 0;
            else
               idx--;

            if(idx >= m_tempomap.get_size())
               return 0;

            if(idx <= 0)
               ptempo = &m_tempomap.element_at(0);
            else
               ptempo = &m_tempomap.element_at(idx);

            /* ptempo is the tempo map entry preceding the requested tick offset.
            */

            return ptempo->msBase + muldiv32((i32)(tkOffset - ptempo->tkTempo), ptempo->dwTempo, 1000L * m_MusicTempoTimeDivision);

         }


         /******************************************************************************
         *
         * smfMillisecsToTicks
         *
         * This function returns the nearest tick offset into the file given the
         * millisecond offset.
         *
         * hSmf                      - Specifies the open MIDI file to perform the
         *                             conversion on.
         *
         * msOffset                  - Specifies the millisecond offset into the stream
         *                             to convert.
         *
         * Returns the number of ticks from the start of the stream.
         *
         * The conversion is performed taking into ac::count the file's time division and
         * tempo map from the first track. Note that the same tick value
         * might not be valid at a later time if the tempo track is rewritten.
         * If the millisecond value does not exactly map to a tick value, then
         * the tick value will be rounded down.
         *
         *****************************************************************************/
         imedia_time buffer::MillisecsToTicks(imedia_time msOffset)
         {

            single_lock(&m_cs, true);

            if(!IsOpened())
               return 0xffffffff;

            if(m_tempomap.get_size() <= 0)
               return 0x80000000;

            ::music::midi::tempo_map_entry *    ptempo;
            i32                      idx;
            u32                    uSMPTE;
            u32                   dwTicksPerSec;
            imedia_time                   tkOffset;

            /* SMPTE time is easy -- no tempo map, just linear conversion
            ** Note that 30-Drop means nothing to us here since we're not
            ** converting to a colonized format, which is where dropping
            ** happens.
            */
            if (m_MusicTempoTimeDivision & 0x8000)
            {
               uSMPTE = -(i32)(char)((m_MusicTempoTimeDivision >> 8)&0xFF);
               if (29 == uSMPTE)
                  uSMPTE = 30;

               dwTicksPerSec = (u32)uSMPTE * (u32)(byte)(m_MusicTempoTimeDivision & 0xFF);

               return (i64) muldiv32((i32) msOffset, dwTicksPerSec, 1000L);
            }

            /* Walk the tempo map and find the nearest millisecond position. Linearly
            ** calculate the rest (using MATH.ASM)
            */
            //ptempo = m_pTempoMap;
            ptempo = &m_tempomap.element_at(0);
            ASSERT(ptempo != nullptr);

            //for (idx = 0; idx < m_cTempoMap; idx++, ptempo++)
            for (idx = 0; idx < m_tempomap.get_size(); idx++)
            {
               ptempo = &m_tempomap.element_at(idx);
               if (msOffset < ptempo->msBase)
                  break;
            }
            ptempo = &m_tempomap.element_at(--idx);

            /* ptempo is the tempo map entry preceding the requested tick offset.
            */

            tkOffset = ptempo->tkTempo + muldiv32((i32) msOffset-ptempo->msBase, 1000L * m_MusicTempoTimeDivision, ptempo->dwTempo);

            if (tkOffset > m_tkLength)
            {
               //TRACE( "sMTT: Clipping ticks to file length!");
               tkOffset = m_tkLength;
            }

            return tkOffset;
         }

         imedia_time  buffer::PositionToTime(
         imedia_time position)
         {
            return TicksToMillisecs(position);
         }

         imedia_time  buffer::TimeToPosition(
         imedia_time time)
         {
            return MillisecsToTicks(time);
         }

         void  buffer::PositionToTime(imedia_time_array & timea, imedia_position_array  & positiona, iptr tkOffset)
         {
            if(tkOffset < 0)
            {
               for(i32 i = 0; i < positiona.get_size(); i++)
               {
                  imedia_time tk = positiona[i];
                  imedia_time tkResult =  tk + tkOffset;
                  if(tkResult > tk)
                     tkResult = 0;

                  timea.add(
                  PositionToTime(tkResult));
               }
            }
            else
            {
               for(i32 i = 0; i < positiona.get_size(); i++)
               {
                  imedia_time tk = positiona[i];
                  imedia_time tkResult =  tk + tkOffset;
                  if(tkResult < tk)
                     tkResult = 0xFFFFFFFF;
                  timea.add(
                  PositionToTime(
                  tkResult));
               }
            }
         }

         void buffer::TicksToMillisecs(imedia_time_2darray * p2DMillis, imedia_position_2darray *p2DTicks, iptr tkOffset)
         {
            ASSERT(p2DMillis->get_size() == 0);
            p2DMillis->set_app(get_object());
            p2DMillis->set_size_create(p2DTicks->get_size());
            i32 i;
            for(i = 0; i < p2DTicks->get_size(); i++)
            {
               TicksToMillisecs(
               p2DMillis->element_at(i),
               p2DTicks->element_at(i),
               tkOffset);
            }

         }

         void buffer::PositionToTime(imedia_time_2darray  & timea, imedia_position_2darray  & positiona, iptr tkOffset)
         {
            ASSERT(timea.get_size() == 0);
            timea.set_app(get_object());
            timea.set_size_create(positiona.get_size());
            i32 i;
            for(i = 0; i < positiona.get_size(); i++)
            {
               PositionToTime(
               timea[i],
               positiona[i],
               tkOffset);
            }

         }

         void  buffer::TicksToMillisecs(imedia_time_array *pMillisArray, imedia_position_array *pTickArray, iptr tkOffset)
         {
            if(tkOffset < 0)
            {
               for(i32 i = 0; i < pTickArray->get_size(); i++)
               {
                  imedia_time tk = pTickArray->operator [](i);
                  imedia_time tkResult =  tk + tkOffset;
                  if(tkResult > tk)
                     tkResult = 0;

                  pMillisArray->add(
                  (imedia_time)
                  TicksToMillisecs(
                  tkResult));
               }
            }
            else
            {
               for(i32 i = 0; i < pTickArray->get_size(); i++)
               {
                  imedia_time tk = pTickArray->operator [](i);
                  imedia_time tkResult =  tk + tkOffset;
                  if(tkResult < tk)
                     tkResult = 0xFFFFFFFF;
                  pMillisArray->add(
                  (imedia_time)
                  TicksToMillisecs(
                  tkResult));
               }
            }
         }


         void  buffer::MillisecsToTicks(
         imedia_position_array *pTickArray,
         imedia_time_array *pMillisArray,
         imedia_time msOffset)
         {
            if(msOffset < 0)
            {
               for(i32 i = 0; i < pMillisArray->get_size(); i++)
               {
                  imedia_time ms = pMillisArray->operator [](i);
                  imedia_time msResult = ms + msOffset;
                  if(msResult > ms)
                     msResult = 0;
                  pTickArray->add(
                  (imedia_time)
                  MillisecsToTicks(
                  msResult));
               }
            }
            else
            {
               for(i32 i = 0; i < pMillisArray->get_size(); i++)
               {
                  imedia_time ms = pMillisArray->operator [](i);
                  imedia_time msResult = ms + msOffset;
                  if(msResult < ms)
                     msResult = 0xffffffff;
                  pTickArray->add(
                  (imedia_time)
                  MillisecsToTicks(
                  msResult));
               }
            }

         }

         void  buffer::TimeToPosition(
         imedia_position_array & positiona,
         imedia_time_array  & timea,
         imedia_time msOffset)
         {
            if(msOffset < 0)
            {
               for(i32 i = 0; i < timea.get_size(); i++)
               {
                  imedia_time ms = timea[i];
                  imedia_time msResult = ms + msOffset;
                  if(msResult < 0)
                     msResult = 0;
                  positiona.add(
                  TimeToPosition(
                  msResult));
               }
            }
            else
            {
               for(i32 i = 0; i < timea.get_size(); i++)
               {
                  imedia_time ms = timea[i];
                  imedia_time msResult = ms + msOffset;
                  if(msResult < ms)
                     msResult = 0xffffffff;
                  positiona.add(
                  TimeToPosition(
                  msResult));
               }
            }

         }

         ::estatus     buffer::StreamEventF1(imedia_time tkDelta,
                                        array < ::music::midi::event *, ::music::midi::event * > & eventptra,
                                        LPMIDIHDR lpmh,
                                        imedia_time tkMax,
                                        u32 cbPrerollNomimalMax
                                       )
         {
            UNREFERENCED_PARAMETER(tkMax);
            UNREFERENCED_PARAMETER(cbPrerollNomimalMax);
            ::estatus                   smfrc;

            if(eventptra.get_size() <= 0)
            {
               return ::success;
            }

            ::music::midi::event * pevent;
            i32 iSize = sizeof(midi_stream_event_header);
            i32 i;
            for(i = 0; i < eventptra.get_size(); i++)
            {
               pevent = eventptra[i];
               ASSERT(pevent->GetFlags() & 1);
               iSize += (i32) pevent->GetParamSize();
               iSize += sizeof(midi_stream_event_header);
            }

            m_memstorageF1.set_size(iSize);
            byte * lpbParam;
            LPDWORD lpdwType;
            midi_stream_event_header * pheader;
            pheader = (midi_stream_event_header *) &m_memstorageF1.get_data()[0];
            pheader->m_dwLength = iSize - sizeof(midi_stream_event_header);
            pheader->m_dwType = 0;
            iSize = sizeof(midi_stream_event_header);
            for(i = 0; i < eventptra.get_size(); i++)
            {
               pevent = eventptra[i];
               lpbParam = pevent->GetParam();
               lpdwType = (LPDWORD) lpbParam;
               pheader = (midi_stream_event_header *) &m_memstorageF1.get_data()[iSize];
               pheader->m_dwLength = (u32) pevent->GetParamSize();
               pheader->m_dwType = *lpdwType;
               ::memcpy_dup(
               &m_memstorageF1.get_data()[iSize + sizeof(midi_stream_event_header)],
               lpbParam,
               pheader->m_dwLength);
               iSize += pheader->m_dwLength + sizeof(midi_stream_event_header);
            }

            m_cbPendingUserEvent = (u32) m_memstorageF1.get_size();
            m_hpbPendingUserEvent = m_memstorageF1.get_data();
            ASSERT(m_hpbPendingUserEvent);
            GetFlags().remove(file::InsertSysEx);
            m_dwPendingUserEvent = ((MEVT_F_CALLBACK | MEVT_F_LONG |(((u32)MEVT_COMMENT)<<24)) & 0xFF000000L);

            smfrc = InsertParmData(tkDelta, lpmh);
            if (::success != smfrc)
            {
               TRACE( "smfInsertParmData[2] %u", (u32)smfrc);
               return smfrc;
            }
            return smfrc;
         }

         ::estatus     buffer::StreamEvent(
         imedia_time                   tkDelta,
         ::music::midi::event *        pEvent,
         LPMIDIHDR               lpmh,
         imedia_time                   tkMax,
         u32                   cbPrerollNominalMax)
         {
            UNREFERENCED_PARAMETER(tkMax);
            UNREFERENCED_PARAMETER(cbPrerollNominalMax);
            //   TRACE("buffer::StreamEvent tkDelta %d\n", tkDelta);

            u32                   dwTempo;
            LPDWORD                 lpdw;
            ::estatus        smfrc;
            lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
            ASSERT(!(pEvent->GetFlags() & 1));
            if(pEvent->GetFlags() & 1)
            {
               ASSERT(FALSE);
            }
            else if (pEvent->GetFullType() < sys_ex)
            {
               if(pEvent->GetType() == program_change)
               {
                  i32 iTrack = pEvent->GetTrack();
                  i32 iProgramChange = pEvent->GetChB1();
                  m_keyframe.rbProgram[iTrack] = (byte) iProgramChange;
                  //if(iProgramChange == 54)
                  //{
                  // pEvent->SetChB1(62);
                  //}
               }
               if(pEvent->GetTrack() == 9 ||
                     pEvent->GetTrack() == 15)
               {
                  //         TRACE("ReadEvents Track %d Program %d", pEvent->GetTrack(), m_keyframe.rbProgram[pEvent->GetTrack()]);
               }
               if((pEvent->GetType() == note_on ||
                     pEvent->GetType() == note_off)
                     && !((m_keyframe.rbProgram[pEvent->GetTrack()] == 0)
                         ))
                  //&& (pEvent->GetTrack() == 9 ||
                  //pEvent->GetTrack() == 15)))
               {
                  i32 iNotePitch = pEvent->GetNotePitch();
                  iNotePitch += m_iKeyShift;
                  while(iNotePitch >= 0x80)
                  {
                     iNotePitch -= 12;
                  }
                  while(iNotePitch < 0)
                  {
                     iNotePitch += 12;
                  }
                  pEvent->SetNotePitch((byte) iNotePitch);
               }

               *lpdw++ = (u32)tkDelta;
               *lpdw++ = 0;
               *lpdw++ = (((u32)MEVT_SHORTMSG)<<24) |
                         ((u32)pEvent->GetFullType()) |
                         (((u32)pEvent->GetChB1()) << 8) |
                         (((u32)pEvent->GetChB2()) << 16);

               lpmh->dwBytesRecorded += 3*sizeof(u32);
            }
            else if (pEvent->GetFullType() == meta &&
                     pEvent->GetMetaType() ==  meta_end_of_track)
            {
               /* These are ignoreable since smfReadNextEvent()
               ** takes care of track merging
               */
            }
            else if (meta == pEvent->GetFullType() && meta_tempo == pEvent->GetMetaType())
            {

               if (pEvent->GetParamSize() != 3)
               {

                  TRACE( "smfReadEvents: Corrupt tempo event");

                  return error_invalid_file;

               }

               dwTempo = (((u32)pEvent->GetParam()[0])<<16)|
                         (((u32)pEvent->GetParam()[1])<<8)|
                         ((u32)pEvent->GetParam()[2]);
               dwTempo = (u32) ((double) dwTempo / GetTempoShiftRate());
               u32 dw = (((u32)MEVT_TEMPO)<<24)| dwTempo;


               *lpdw++ = (u32)tkDelta;
               *lpdw++ = 0;
               *lpdw++ = dw;

               lpmh->dwBytesRecorded += 3*sizeof(u32);
            }
            //       else if ((Meta == pEvent->GetType()) &&
            //          (05 == pEvent->GetType()))
            ///      {
            /**lpdw++ = (u32)pEvent->tkDelta;
            *lpdw++ = 0;
            *lpdw++ = MEVT_F_SHORT | MEVT_F_CALLBACK |
            (((u32)MEVT_SHORTMSG )<<24) |
            ((u32)7) |
            (((u32)13) << 8) |
            (((u32)31) << 16);
            lpmh->dwBytesRecorded += 3*sizeof(u32);*/
            //m_cbPendingUserEvent = ((u32)MEVT_SHORTMSG )<<24;
            //         str = (char *) malloc(pEvent->cbParm + 1);
            //         strncpy(str, (const char *) pEvent->hpbParm,  pEvent->cbParm);
            //         str[pEvent->cbParm] = 0;
            //         printf("%s", str);

            //         m_cbPendingUserEvent = pEvent->cbParm;
            //            m_hpbPendingUserEvent = pEvent->hpbParm;
            //            m_fdwSMF &= ~FlagInsertSysEx;
            //         m_dwPendingUserEvent = MEVT_F_CALLBACK |(((u32)MEVT_LONGMSG )<<24);
            //m_dwPendingUserEvent = (((u32)MEVT_LONGMSG )<<24);
            //         smfrc = smfInsertParmData(pSmf, pEvent->tkDelta, lpmh);
            //            if (::success != smfrc)
            //            {
            //                TRACE( "smfInsertParmData[2] %u", (u32)smfrc);
            //                return smfrc;
            //            }

            //            lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);


            //smfrc = smfInsertParmData(pSmf, pEvent->tkDelta, lpmh);
            //if (::success != smfrc)
            //{
            //    TRACE( "smfInsertParmData[2] %u", (u32)smfrc);
            //    return smfrc;
            //}
            //         _CrtSetReportFile(_CRT_WARN, debugFile);
            //         _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);

            //_RPT0(_CRT_WARN, "Lyric:");
            //_RPT1(_CRT_WARN, "%s", lpmh->lpData);
            //_RPT0(_CRT_WARN, "\n");

            //    }
            else if (pEvent->GetFullType() != meta)
               //   else
            {
               //            if(pEvent->GetFullType() == SysEx)
               //         {
               //                break;
               //            }
               /* Must be F0 or F7 system exclusive or FF meta
               ** that we didn't recognize
               */

               m_cbPendingUserEvent = (u32) pEvent->GetParamSize();
               m_hpbPendingUserEvent = pEvent->GetParam();
               GetFlags().remove(file::InsertSysEx);

               if(pEvent->GetFullType() == sys_ex_end)
               {
                  m_dwPendingUserEvent = ((u32)MEVT_LONGMSG) << 24;
               }
               else if(pEvent->GetFullType() == sys_ex)
               {
                  GetFlags().add(file::InsertSysEx);
                  ++m_cbPendingUserEvent;

                  /* Falling through...
                  */

                  m_dwPendingUserEvent = ((u32)MEVT_LONGMSG) << 24;
               }

               smfrc = InsertParmData(tkDelta, lpmh);
               if (::success != smfrc)
               {
                  TRACE( "smfInsertParmData[2] %u", (u32)smfrc);
                  return smfrc;
               }

               lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
            }
            else // Meta
            {
               // se o meta event possuir tkDelta > 0,
               // insere o evento no stream para que n�o haja perda de sincronismo
               if(tkDelta > 0)
               {
                  InsertPadEvent(tkDelta, lpmh);
                  lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
               }
            }
            return ::success;
         }

         /******************************************************************************
         *
         * smfReadEvents
         *
         * This function reads events from a track.
         *
         * hSmf                      - Specifies the file to read data from.
         *
         * lpmh                      - Contains information about the buffer to fill.
         *
         * tkMax                     - Specifies a cutoff point in the stream
         *                             beyond which events will not be read.
         *
         * Return@rdes
         *   success The events were successfully read.
         *   SMF_END_OF_TRACK There are no more events to read in this track.
         *   error_invalid_file A disk error occured on the file.
         *
         * @xref <f smfWriteEvents>
         *****************************************************************************/
         ::estatus     buffer::StreamRender(
         LPMIDIHDR               lpmh,
         imedia_time                   tkMax,
         u32                   cbPrerollNominalMax)
         {

            //    PSMF                    pSmf = (PSMF)hSmf;
            ::estatus                   smfrc;
            ::music::midi::event * pevent;
            LPDWORD                 lpdw;
            //    u32                   dwTempo;
            imedia_time               tkDelta;
            //   imedia_time               tkPosition;
            //   imedia_time               tkMin;
            //   imedia_time               tk;
            i32                  iTrackFound;
            //   i32                  i;
            imedia_time               tkLastDelta = 0 ;
            imedia_time                   tkOnQuarterNoteDelta = 0;
            //   imedia_time               tkLastPositionCB = 0x7fffffff;
            //CXfplayerApp *pApp = (CXfplayerApp *) &System;
            //ASSERT(pApp != nullptr);
            //CXfplayerDoc *pDoc = (CXfplayerDoc *) pApp->GetPlayingDocument();
            //ASSERT(pDoc != nullptr);
            //   char * str;
            //assert(pSmf != nullptr);
            ASSERT(lpmh != nullptr);

            /*
            ** read events from the track and pack them into the buffer in polymsg
            ** format.
            **
            ** If a SysEx or meta would go over a buffer boundry, split it.
            */
            lpmh->dwBytesRecorded = 0;
            if (m_dwPendingUserEvent)
            {
               smfrc = InsertParmData((imedia_time)0, lpmh);
               if (::success != smfrc)
               {
                  TRACE( "smfInsertParmData() -> %u", (u32)smfrc);
                  return smfrc;
               }
            }
            //   if(m_pendingLyricEventArray.get_size() > 0)
            //   {
            //      smfrc = InsertLyricEvents(nullptr, lpmh);
            //        if (::success != smfrc)
            //      {
            //        TRACE( "smfInsertParmData() -> %u", (u32)smfrc);
            //      return smfrc;
            //}
            //}

            lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);

            if (GetFlags().has(file::EndOfFile))
            {

               return success_end_of_file;

            }

            /*if(pDoc->m_iBufferingOffsetTokenIndex >= pDoc->m_TokensOffsetTicks.get_size())
            {
            tkNextOffsetLyricEvent = -1;
            }
            else
            {
            tkNextOffsetLyricEvent = pDoc->m_TokensOffsetTicks[pDoc->m_iBufferingOffsetTokenIndex ];
            }
            if(pDoc->m_iBufferingTokenIndex >= pDoc->m_TokensTicks.get_size())
            {
            tkNextLyricEvent = -1;
            }
            else
            {
            tkNextLyricEvent = pDoc->m_TokensTicks[pDoc->m_iBufferingTokenIndex ];
            }*/
            //   ::ikaraoke::lyric_events_v1 *pEventsV1;
            while(TRUE)
            {
               ASSERT(lpmh->dwBytesRecorded <= lpmh->dwBufferLength);
               if(lpmh->dwBytesRecorded > cbPrerollNominalMax)
               {
                  break;
               }

               /* If we know ahead of time we won't have room for the
               ** event, just break out now. We need 2 u32's for the
               ** terminator event and at least 2 u32's for any
               ** event we might store - this will allow us a full
               ** i16 event or the delta time and stub for a long
               ** event to be split.
               */
               /*
               now 16 DWORDS
               */
               if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4*sizeof(u32))
               {
                  break;
               }




               //smfrc = GetNextEventTkPosition(&tkPosition, tkMax);


               /*        if (::success != smfrc)
               {
               smfrc = GetNextEvent((event *)&event, tkMax, TRUE);
               ASSERT(::success != smfrc); */

               /* smfGetNextEvent doesn't set this because smfSeek uses it
               ** as well and needs to distinguish between reaching the
               ** seek point and reaching end-of-file.
               **
               ** To the ::account::user, however, we present the selection between
               ** their given tkBase and tkEnd as the entire file, therefore
               ** we want to translate this into EOF.
               */
               /*if (success_reached_tk_max == smfrc)
               {
               m_fdwSMF |= FlagEof;
               }

               TRACE( "smfReadEvents: ReadEvents() -> %u", (u32)smfrc);
               break;
               }*/
               iTrackFound = -1;
               tkLastDelta = 0;
               /*      while(TRUE)
               {
               for(i = 0; i < m_eventsTracksForPositionCB.get_size(); i++)
               {
               pEventsV1 = m_eventsTracksForPositionCB.get_at(i);
               if(pEventsV1->GetClassOrder() == 1)
               {
               while(m_ptracks->m_tkPosition >
               (tk = pEventsV1->GetCurrentTkTokenPosition()))
               {
               pEventsV1->m_iCurrentToken++;
               }
               }
               else
               {
               while(m_ptracks->m_tkPosition >
               (tk = ((::ikaraoke::lyric_events_v2 *)pEventsV1)->GetCurrentTkNotePosition()))
               {
               pEventsV1->m_iCurrentNote++;
               }
               }
               if(iTrackFound < 0)
               {
               if(tk >= 0)
               if(tkPosition >= tk)
               {
               tkMin = tk;
               iTrackFound = i;
               }
               }
               else
               {
               if(tk >= 0)
               if(tkPosition >= tk)
               {
               if(tk < tkMin)
               {
               tkMin = tk;
               iTrackFound = i;
               }
               }

               }
               }
               if(iTrackFound < 0)
               break;
               else
               {
               pEventsV1 = m_eventsTracksForPositionCB.get_at(iTrackFound);
               #ifdef _DEBUG
               //         if(pEventsV1->m_iType == 1)
               //         {
               //            TRACE("ReadEvents pEventsV1->m_iCurrentToken = %d\n", pEventsV1->m_iCurrentToken);
               //            TRACE("ReadEvents pEventsV1->m_iType = %d\n", pEventsV1->m_iType);
               //            TRACE("ReadEvents m_ptracks->m_tkPosition = %d\n", m_ptracks->m_tkPosition);
               //         }
               #endif
               tkDelta = tkMin - m_ptracks->m_tkPosition;
               if((tkDelta - tkLastDelta) == 0)
               {
               pEventsV1->m_tkDelta = 0;
               InsertLyricEvents(pEventsV1, lpmh);
               }
               else
               {
               if(m_pendingLyricEventArray.get_size() > 0)
               {
               smfrc = InsertLyricEvents(nullptr, lpmh);
               if(MetaPending == smfrc)
               {
               break;
               }
               else if (::success != smfrc)
               {

               TRACE( "smfInsertLyricEvent %u", (u32)smfrc);
               return smfrc;
               }
               lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
               }
               pEventsV1->m_tkDelta = tkDelta - tkLastDelta;
               InsertLyricEvents(pEventsV1, lpmh);
               }

               iTrackFound = -1;
               tkLastDelta = tkDelta;
               }
               if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4*sizeof(u32))
               {
               break;
               }
               }*/
               /*if(m_pendingLyricEventArray.get_size() > 0)
               {
               if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4*sizeof(u32))
               {
               break;
               }
               smfrc = InsertLyricEvents(nullptr, lpmh);
               if(MetaPending == smfrc)
               {
               break;
               }
               else if (::success != smfrc)
               {
               TRACE( "smfInsertLyricEvent %u", (u32)smfrc);
               return smfrc;
               }
               lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
               }*/
               if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4*sizeof(u32))
               {
                  m_ptracks->m_tkPosition += tkDelta;
                  break;
               }

               smfrc = GetNextEvent(pevent, tkMax, TRUE);
               if (::success != smfrc)
               {
                  /* smfGetNextEvent doesn't set this because smfSeek uses it
                  ** as well and needs to distinguish between reaching the
                  ** seek point and reaching end-of-file.
                  **
                  ** To the ::account::user, however, we present the selection between
                  ** their given tkBase and tkEnd as the entire file, therefore
                  ** we want to translate this into EOF.
                  */
                  if(success_reached_tk_max == smfrc)
                  {
                     GetFlags().add(file::EndOfFile);
                  }

                  TRACE( "smfReadEvents: ReadEvents() -> %u", (u32)smfrc);
                  break;
               }
               ::estatus     vmsr;
               vmsr = StreamEvent(tkDelta, pevent, lpmh, tkMax, cbPrerollNominalMax);

            }

            return (GetFlags().has(file::EndOfFile)) ? success_end_of_file : ::success;
         }

         /******************************************************************************
         *
         * smfReadEvents
         *
         * This function reads events from a track.
         *
         * hSmf                      - Specifies the file to read data from.
         *
         * lpmh                      - Contains information about the buffer to fill.
         *
         * tkMax                     - Specifies a cutoff point in the stream
         *                             beyond which events will not be read.
         *
         * Return@rdes
         *   success The events were successfully read.
         *   SMF_END_OF_TRACK There are no more events to read in this track.
         *   error_invalid_file A disk error occured on the file.
         *
         * @xref <f smfWriteEvents>
         *****************************************************************************/

         ::estatus     buffer::InsertLyricEvents(
         ::ikaraoke::lyric_event_v1 *      pLyricEvent,
         LPMIDIHDR         lpmh)
         {
            UNREFERENCED_PARAMETER(pLyricEvent);
            UNREFERENCED_PARAMETER(lpmh);
            /*    LPDWORD                 lpdw;
            u32                   dwRounded;
            u32               dwLength;
            u32               dwSize;
            imedia_time               tkDelta;

            if(pLyricEvent != nullptr)
            {
            m_pendingLyricEventArray.add(*pLyricEvent);
            if(pLyricEvent->GetClassOrder() == 1)
            pLyricEvent->m_iCurrentToken++;
            else
            {
            ::ikaraoke::lyric_events_v2 * pPendingLyricEventV2 =
            (::ikaraoke::lyric_events_v2 *) pLyricEvent;
            pPendingLyricEventV2->m_iCurrentNote++;
            if(pPendingLyricEventV2->m_iCurrentNote <
            pPendingLyricEventV2->m_msaNotesPosition.get_size())
            {
            u32_array dwArray;
            //            VERIFY(1 == pPendingLyricEventV2->GetNoteTokens(m_pPendingLyricEventV1->m_iCurrentNote, dwArray));
            pPendingLyricEventV2->GetNoteTokens(pPendingLyricEventV2->m_iCurrentNote, dwArray);
            if(dwArray.get_size() > 0)
            pPendingLyricEventV2->m_iCurrentToken = dwArray.get_at(0);
            else
            pPendingLyricEventV2->m_iCurrentToken = -1;
            }
            }
            return ::success;
            }

            ASSERT(lpmh != nullptr);

            if(m_pendingLyricEventArray.get_size() <= 0)
            {
            return ::success;
            }

            tkDelta = m_pendingLyricEventArray[0].m_tkDelta;

            ASSERT(tkDelta >= 0);

            /* Can't fit 4 u32's? (tkDelta + stream-id + event + some data)
            ** Can't do anything.
            */
            /*ASSERT(lpmh->dwBufferLength >= lpmh->dwBytesRecorded);
            //   m_dwPendingUserEvent = MEVT_F_CALLBACK |
            //             (((u32)MEVT_LONGMSG)<<24);
            //   m_cbPendingUserEvent = 2 * sizeof(u32);

            if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4 * sizeof(u32))
            {
            if (0 == tkDelta)
            return ::success;

            /* If we got here with a real delta, that means smfReadEvents screwed
            ** up calculating left space and we should flag it somehow.
            */
            /*        TRACE( "Can't fit initial piece of SysEx into buffer!");
            return error_invalid_file;
            }

            CMemFile memFile;
            CArchive ar(&memFile, CArchive::store);
            m_pendingLyricEventArray.Serialize(ar);
            ar.Flush();
            dwSize = (memFile.get_length() + sizeof(u32) + 3) & (~3L);


            lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
            dwLength = lpmh->dwBufferLength - lpmh->dwBytesRecorded - 3*sizeof(u32);
            if(dwSize > dwLength)
            return MetaPending;
            dwLength = dwSize;

            //   u32 dwa = MEVT_F_CALLBACK;
            //   u32 dwb = MEVT_LONGMSG;
            //   u32 dwc = MEVT_F_LONG;
            //   u32 dwd = MEVT_COMMENT;

            ASSERT((dwSize & 3L) == 0);
            dwRounded = dwSize;
            //dwRounded = (dwLength + 3) & (~3L);

            //tkOffset = tkDelta;
            *lpdw++ = (u32) tkDelta;
            *lpdw++ = 0;
            //*lpdw++ = ((MEVT_F_CALLBACK | MEVT_F_LONG |(((u32)MEVT_LONGMSG)<<24)) & 0xFF000000L )   | (dwLength & 0x00FFFFFFL);;
            *lpdw++ = ((MEVT_F_CALLBACK | MEVT_F_LONG |(((u32)MEVT_COMMENT)<<24)) & 0xFF000000L )   | (dwLength & 0x00FFFFFFL);;
            *lpdw++ = EVENT_ID_LYRIC_V1;

            //   if(m_cbPendingLyricEventV1 >= (3 * sizeof(u32)))
            //   {
            //      // offset Lyric CallBack Event Code
            //      *lpdw++ = m_pPendingLyricEventV1->m_Union.m_pevent->m_nType;
            //   }
            //   if(m_cbPendingLyricEventV1 >= (2 * sizeof(u32)))
            //   {
            //      // offset Lyric CallBack Event Code
            //      *lpdw++ = m_pPendingLyricEventV1->m_Union.m_pevent->m_nTrack;
            //   }
            //   if(m_cbPendingLyricEventV1 >= (1 * sizeof(u32)))
            //   {
            //      // offset Lyric CallBack Event Code
            //      *lpdw++ = m_pPendingLyricEventV1->m_Union.m_pevent->m_nCurrentIndex;
            //      m_pPendingLyricEventV1->m_Union.m_pevent->m_nCurrentIndex++;
            //   }
            memFile.seek_to_begin();
            memFile.read(lpdw, dwLength);
            while(0 < m_pendingLyricEventArray.get_size())
            {
            m_pendingLyricEventArray.remove_at(
            m_pendingLyricEventArray.get_size() - 1);
            }
            lpmh->dwBytesRecorded += 3*sizeof(u32) + dwRounded;
            */
            return ::success;
         }

         ::estatus     buffer::InsertPadEvent(
         imedia_time            tkDelta,
         LPMIDIHDR         lpmh)

         {
            LPDWORD                 lpdw;
            u32                   dwRounded;
            u32               dwLength;


            ASSERT(tkDelta >= 0);
            //    assert(pSmf != nullptr);
            ASSERT(lpmh != nullptr);

            /* Can't fit 4 u32's? (tkDelta + stream-id + event + some data)
            ** Can't do anything.
            */
            ASSERT(lpmh->dwBufferLength >= lpmh->dwBytesRecorded);
            //   m_dwPendingUserEvent = MEVT_F_CALLBACK |
            //             (((u32)MEVT_LONGMSG)<<24);
            //   m_cbPendingUserEvent = 2 * sizeof(u32);
            //   if(!m_cbPendingLyricEventV1)
            //   if(!1)
            //   {
            //      return ::success;
            //   }

            if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4 * sizeof(u32))
            {
               if (0 == tkDelta)
                  return ::success;

               /* If we got here with a real delta, that means smfReadEvents screwed
               ** up calculating left space and we should flag it somehow.
               */
               TRACE( "Can't fit initial piece of SysEx into buffer!");
               return error_invalid_file;

            }

            lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
            dwLength = lpmh->dwBufferLength - lpmh->dwBytesRecorded - 3*sizeof(u32);
            dwLength = min(dwLength, 8);

            //u32 dwa = MEVT_F_CALLBACK;
            //   u32 dwb = MEVT_LONGMSG;
            //   u32 dwc = MEVT_F_LONG;
            //   u32 dwd = MEVT_COMMENT;

            dwRounded = (dwLength + 3) & (~3L);

            //tkOffset = tkDelta;
            *lpdw++ = (u32) tkDelta;
            *lpdw++ = 0;
            //*lpdw++ = ((MEVT_F_CALLBACK | MEVT_F_LONG |(((u32)MEVT_LONGMSG)<<24)) & 0xFF000000L )   | (dwLength & 0x00FFFFFFL);;
            //   *lpdw++ = ((MEVT_F_CALLBACK | MEVT_F_LONG |(((u32)MEVT_COMMENT)<<24)) & 0xFF000000L )   | (dwLength & 0x00FFFFFFL);;
            *lpdw++ = ((MEVT_F_LONG |(((u32)MEVT_COMMENT)<<24)) & 0xFF000000L )   | (dwLength & 0x00FFFFFFL);;
            *lpdw++ = 0;
            *lpdw++ = EVENT_ID_PAD;

            //   if(m_cbPendingLyricEventV1 >= (3 * sizeof(u32)))
            //   {
            //      // offset Lyric CallBack Event Code
            //      *lpdw++ = m_pPendingLyricEventV1->m_Union.m_pevent->m_nType;
            //   }
            //   if(m_cbPendingLyricEventV1 >= (2 * sizeof(u32)))
            //   {
            //      // offset Lyric CallBack Event Code
            //      *lpdw++ = m_pPendingLyricEventV1->m_Union.m_pevent->m_nTrack;
            //   }
            //   if(m_cbPendingLyricEventV1 >= (1 * sizeof(u32)))
            //   {
            //      // offset Lyric CallBack Event Code
            //      *lpdw++ = m_pPendingLyricEventV1->m_Union.m_pevent->m_nCurrentIndex;
            //      m_pPendingLyricEventV1->m_Union.m_pevent->m_nCurrentIndex++;
            //   }
            //   m_pPendingLyricEventV1->ToData(lpdw, m_cbPendingLyricEventV1);
            //   if (0 == (m_cbPendingLyricEventV1 -= dwLength))
            //   {
            //   }
            //   else
            //   {
            //      i32 i = 5;
            //   }

            lpmh->dwBytesRecorded += 3*sizeof(u32) + dwRounded;
            return ::success;
         }
         /******************************************************************************
         *
         * smfInsertParmData
         *
         * Inserts pending long data from a track into the given buffer.
         *
         * pSmf                      - Specifies the file to read data from.
         *
         * tkDelta                   - Specfices the tick delta for the data.
         *
         * lpmh                      - Contains information about the buffer to fill.
         *
         * Returns
         *   success The events were successfully read.
         *   error_invalid_file A disk error occured on the file.
         *
         * Fills as much data as will fit while leaving room for the buffer
         * terminator.
         *
         * If the long data is depleted, resets m_dwPendingUserEvent so
         * that the next event may be read.
         *
         *****************************************************************************/
         ::estatus     buffer::InsertParmData(
         imedia_time                   tkDelta,
         LPMIDIHDR               lpmh)
         {
            u32                   dwLength;
            u32                   dwRounded;
            LPDWORD                 lpdw;

            //    assert(pSmf != nullptr);
            ASSERT(lpmh != nullptr);

            /* Can't fit 4 u32's? (tkDelta + stream-id + event + some data)
            ** Can't do anything.
            */
            ASSERT(lpmh->dwBufferLength >= lpmh->dwBytesRecorded);

            if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4*sizeof(u32))
            {
               if (0 == tkDelta)
                  return ::success;

               /* If we got here with a real delta, that means smfReadEvents screwed
               ** up calculating left space and we should flag it somehow.
               */
               TRACE( "Can't fit initial piece of SysEx into buffer!");
               return error_invalid_file;
            }

            lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);

            dwLength = lpmh->dwBufferLength - lpmh->dwBytesRecorded - 3*sizeof(u32);
            dwLength = min(dwLength, m_cbPendingUserEvent);

            *lpdw++ = (u32)tkDelta;
            *lpdw++ = 0L;
            *lpdw++ = (m_dwPendingUserEvent & 0xFF000000L) | (dwLength & 0x00FFFFFFL);

            dwRounded = (dwLength + 3) & (~3L);

            if (GetFlags().has(file::InsertSysEx))
            {
               byte * lpb = (byte *) lpdw;
               *lpb++ = sys_ex;
               GetFlags().remove(file::InsertSysEx);
               --dwLength;
               --m_cbPendingUserEvent;
               lpdw = (LPDWORD) lpb;
            }

            if (dwLength & 0x80000000L)
            {
               TRACE( "dwLength %08lX  dwBytesRecorded %08lX  dwBufferLength %08lX", dwLength, lpmh->dwBytesRecorded, lpmh->dwBufferLength);
               TRACE( "cbPendingUserEvent %08lX  dwPendingUserEvent %08lX dwRounded %08lX", m_cbPendingUserEvent, m_dwPendingUserEvent, dwRounded);
               TRACE( "offset into MIDI image %08lX", (u32)(m_hpbPendingUserEvent - GetImage()));
               TRACE( "!hmemcpy is about to fault");
            }

            ::memcpy_dup(lpdw, m_hpbPendingUserEvent, dwLength);
            if (0 == (m_cbPendingUserEvent -= dwLength))
               m_dwPendingUserEvent = 0;

            lpmh->dwBytesRecorded += 3*sizeof(u32) + dwRounded;

            return ::success;
         }

         /******************************************************************************
         *
         * smfSeek
         *
         * This function moves the file pointer within a track
         * and gets the state of the track at the new position. It returns a buffer of
         * state information which can be used to set up to play from the new position.
         *
         * hSmf                      - Handle of file to seek within
         *
         * tkPosition                - The position to seek to in the track.
         *
         * lpmh                      - A buffer to contain the state information.
         *
         * Returns
         *   success | The state was successfully read.
         *   SMF_END_OF_TRACK | The pointer was moved to end of track and no state
         *     information was returned.
         *   SMF_INVALID_PARM | The given handle or buffer was invalid.
         *   error_no_memory | There was insufficient memory in the given buffer to
         *     contain all of the state data.
         *
         * The state information in the buffer includes patch changes, tempo changes,
         * time signature, key signature,
         * and controller information. Only the most recent of these paramters before
         * the current position will be stored. The state buffer will be returned
         * in polymsg format so that it may be directly transmitted over the MIDI
         * bus to bring the state up to date.
         *
         * The buffer is mean to be sent as a streaming buffer; i.e. immediately
         * followed by the first data buffer. If the requested tick position
         * does not exist in the file, the last event in the buffer
         * will be a MEVT_NOP with a delta time calculated to make sure that
         * the next stream event plays at the proper time.
         *
         * The meta events (tempo, time signature, key signature) will be the
         * first events in the buffer if they exist.
         *
         * Use smfGetStateMaxSize to determine the maximum size of the state
         * information buffer. State information that will not fit into the given
         * buffer will be lost.
         *
         * On return, the dwBytesRecorded field of lpmh will contain the
         * actual number of bytes stored in the buffer.
         *
         *****************************************************************************/


         ::estatus     buffer::seek(
         imedia_time                   tkPosition,
         LPMIDIHDR               lpmh)
         {
            ::estatus         smfrc;
            ::music::midi::event *        pevent;
            LPDWORD                 lpdw;
            byte                    bEvent;
            u32                    idx;
            u32                    idxChannel;
            u32                    idxController;

            _SyncSeek(tkPosition);

            __memset(&m_keyframe, 0, sizeof(m_keyframe));



            __memset(&m_keyframe, 0xFF, sizeof(m_keyframe));
            __memset(&m_keyframe.rbProgram, 0x00, sizeof(m_keyframe.rbProgram));

            m_ptracks->m_tkPosition = 0;
            GetFlags().remove(file::EndOfFile);
            m_ptracks->GetFlags().remove(file::EndOfFile);

            m_ptracks->seek_begin();
            //for (ptrk = m_rTracks, idxTrack = m_dwTracks; idxTrack--; ptrk++)

            while (::success == (smfrc = GetNextEvent(pevent, tkPosition, FALSE)))
            {

               if (meta == (bEvent = pevent->GetFullType()))
               {
                  if (pevent->GetMetaType() == meta_tempo)
                  {
                     if (pevent->GetParamSize() != sizeof(m_keyframe.rbTempo))
                        return error_invalid_file;

                     ::memcpy_dup((byte *)m_keyframe.rbTempo, pevent->GetParam(), pevent->GetParamSize());
                  }
               }
               if((bEvent & 0xF0) == program_change)
               {
                  m_keyframe.rbProgram[bEvent & 0x0F] = pevent->GetChB1();
               }
               else if((bEvent & 0xF0) == control_change)
               {
                  m_keyframe.rbControl[(((::u16)bEvent & 0x0F)*120) + pevent->GetChB1()] =
                  pevent->GetChB2();
               }
            }

            if(success_reached_tk_max != smfrc)
            {
               return smfrc;
            }

            /* Build lpmh from keyframe
            */
            lpmh->dwBytesRecorded = 0;
            lpdw = (LPDWORD)lpmh->lpData;

            /* Tempo change event?
            */
            if (KF_EMPTY != m_keyframe.rbTempo[0] ||
                  KF_EMPTY != m_keyframe.rbTempo[1] ||
                  KF_EMPTY != m_keyframe.rbTempo[2])
            {
               if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 3*sizeof(u32))
                  return error_no_memory;

               *lpdw++ = 0;
               *lpdw++ = 0;
               //      *lpdw++ = (((u32)m_keyframe.rbTempo[2])<<16)|
               //                (((u32)m_keyframe.rbTempo[1])<<8)|
               //            ((u32)m_keyframe.rbTempo[0])|
               //            (((u32)MEVT_SHORTMSG) << 24);
               //
               //      *lpdw++ = (((u32)m_keyframe.rbTempo[0])<<16)|
               //                (((u32)m_keyframe.rbTempo[1])<<8)|
               //             ((u32)m_keyframe.rbTempo[2])|
               //            (((u32)MEVT_SHORTMSG) << 24);

               u32 dwTempo =   (((u32)m_keyframe.rbTempo[0])<<16)|
                                    (((u32)m_keyframe.rbTempo[1])<<8)|
                                    ((u32)m_keyframe.rbTempo[2]);
               dwTempo = (u32) ((double) dwTempo / GetTempoShiftRate());
               u32 dw = (((u32)MEVT_TEMPO)<<24)| dwTempo;


               //*lpdw++ = (u32)pEvent->_GetDelta();
               //*lpdw++ = 0;
               //*lpdw++ = dw;
               *lpdw++ = dw;

               //*lpdw++ = (((u32)m_keyframe.rbTempo[0])<<16)|
               //        (((u32)m_keyframe.rbTempo[1])<<8)|
               //      ((u32)m_keyframe.rbTempo[2])|
               //    (((u32)MEVT_TEMPO) << 24);
               //        *lpdw++ = (((u32)m_keyframe.rbTempo[2])<<16)|
               //                (((u32)m_keyframe.rbTempo[1])<<8)|
               //              ((u32)m_keyframe.rbTempo[0])|
               ///            (((u32)MEVT_TEMPO) << 24);

               lpmh->dwBytesRecorded += 3*sizeof(u32);
            }

            /* Program change events?
            */
            for (idx = 0; idx < 16; idx++)
            {
               if (KF_EMPTY != m_keyframe.rbProgram[idx])
               {
                  if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 3*sizeof(u32))
                     return error_no_memory;

                  *lpdw++ = 0;
                  *lpdw++ = 0;
                  *lpdw++ = (((u32)MEVT_SHORTMSG) << 24)      |
                            ((u32)program_change)         |
                            ((u32)idx)                        |
                            (((u32)m_keyframe.rbProgram[idx]) << 8);

                  lpmh->dwBytesRecorded += 3*sizeof(u32);
               }
            }

            /* Controller events?
            */
            idx = 0;
            for (idxChannel = 0; idxChannel < 16; idxChannel++)
            {
               for (idxController = 0; idxController < 120; idxController++)
               {
                  if (KF_EMPTY != m_keyframe.rbControl[idx])
                  {
                     if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 3*sizeof(u32))
                        return error_no_memory;

                     *lpdw++ = 0;
                     *lpdw++ = 0;
                     *lpdw++ = (((u32)MEVT_SHORTMSG << 24)     |
                                ((u32)control_change)       |
                                ((u32)idxChannel)               |
                                (((u32)idxController) << 8)     |
                                (((u32)m_keyframe.rbControl[idx]) << 16));


                     lpmh->dwBytesRecorded += 3*sizeof(u32);
                  }

                  idx++;
               }
            }

            /* Force all tracks to be at tkPosition. We are guaranteed that
            ** all tracks will be past the event immediately preceding tkPosition;
            ** this will force correct delta-ticks to be generated so that events
            ** on all tracks will line up properly on a seek into the middle of the
            ** file.
            */
            // ^^^^ This cause problems... tracks are already positioned...
            // changing track position make all the song envents be shifted
            // irregularly...
            //    for (ptrk = m_rTracks, idxTrack = m_dwTracks; idxTrack--; ptrk++)
            //   for (idxTrack = m_dwTracks; idxTrack--;)
            //  {
            //   ptrk = m_tracks[idxTrack];
            //  ptrk->tkPosition        = tkPosition;
            //}
            //return seek(tkPosition);

            return ::success;
         }

         ::estatus     buffer::seek(
         imedia_time                   tkPosition)
         {
            ::estatus      smfrc;
            ::music::midi::event *     pevent;


            m_ptracks->m_tkPosition = 0;
            GetFlags().remove(file::EndOfFile);
            m_ptracks->GetFlags().remove(file::EndOfFile);

            m_ptracks->seek_begin();

            while(::success == (smfrc = GetNextEvent(pevent, tkPosition, FALSE)));

            if (success_reached_tk_max != smfrc)
            {
               return smfrc;
            }

            return ::success;
         }


         ::estatus     buffer::GetNextEvent(::music::midi::event * & pevent, imedia_time tkMax, bool bTkMaxInclusive)
         {

            if (GetFlags().has(file::EndOfFile))
            {

               return success_end_of_file;

            }

            if(!GetFlags().has(file::DisablePlayLevel1Operations))
            {
               if(m_mepaImmediate.get_size() > 0)
               {
                  ::music::midi::event * peventImmediate = m_mepaImmediate.element_at(0);
                  *pevent = *peventImmediate;
                  delete peventImmediate;
                  m_mepaImmediate.remove_at(0);
                  return ::success;
               }
               if(m_mepaOnQuarterNote.get_size() > 0)
               {
                  imedia_time tkMod = m_ptracks->m_tkPosition  % WORDSWAP(m_pFileHeader->wDivision);
                  imedia_time tkQuarterNote;
                  if(tkMod == 0)
                  {
                     tkQuarterNote = m_ptracks->m_tkPosition;
                  }
                  else
                  {
                     tkQuarterNote = m_ptracks->m_tkPosition + WORDSWAP(m_pFileHeader->wDivision) - tkMod;
                  }
                  imedia_time tkPosition;
                  ::estatus     smfrc = GetNextEventTkPosition(&tkPosition, tkMax);
                  if(smfrc == ::success_end_of_file)
                     GetFlags().add(file::EndOfFile);
                  if(tkPosition > tkQuarterNote)
                  {
                     m_ptracks->m_tkPosition  = tkQuarterNote;
                     *pevent = *m_mepaOnQuarterNote.element_at(0);
                     delete m_mepaOnQuarterNote.element_at(0);
                     m_mepaOnQuarterNote.remove_at(0);
                     return ::success;
                  }
               }
            }

            ::estatus     smfrc   = m_ptracks->GetNextEvent(pevent, tkMax, bTkMaxInclusive, false, false);

            if(!GetFlags().has(file::DisablePlayLevel1Operations))
            {
               if(pevent->GetType() == note_on &&
                     pevent->GetNoteVelocity() != 0)
               {
                  m_ptracks->m_iaNoteOn.element_at(pevent->GetTrack())++;
                  m_ptracks->m_iaLevel.element_at(pevent->GetTrack())
                     = pevent->GetNoteVelocity();
               }
               else if((pevent->GetType() == note_on &&
                        pevent->GetNoteVelocity() == 0) ||
                       pevent->GetType() == note_off)
               {
                  i32 iCount = m_ptracks->m_iaNoteOn.element_at(pevent->GetTrack());
                  if(iCount > 0)
                     iCount--;
                  m_ptracks->m_iaNoteOn.element_at(pevent->GetTrack()) =
                  iCount;
                  if(iCount == 0)
                     m_ptracks->m_iaLevel.element_at(pevent->GetTrack())
                        = 0;
               }
            }
            if(smfrc == ::success_end_of_file)
               GetFlags().add(file::EndOfFile);
            return smfrc;



         }

         ::estatus     buffer::GetNextEventTkPosition(imedia_time * pTkPosition, imedia_time tkMax)
         {

            if (GetFlags().has(file::EndOfFile))
            {

               return success_end_of_file;

            }

            return m_ptracks->GetNextEventTkPosition(pTkPosition, tkMax);

         }




         /*
         *   mysmfGetTrackEventData
         *
         *
         *
         *
         ****/
         u32 mysmfGetTrackEventData(__pointer(::music::midi::file::buffer) pSmf, ::music::midi::event * pEvent, byte * pData[])
         {

            u32                len;
            byte *                  hpbImage;
            u32                index;

            ASSERT(pSmf != nullptr);
            ASSERT(pEvent != nullptr);

            len = pEvent->m_iParamSize;

            *pData = (uchar *) LocalAlloc(LPTR,len);

            hpbImage = (byte *) pEvent->m_pParam;

            for(index = 0; len; index++)
            {
               *pData[index] = *hpbImage++;
            }

            return len;
         }


         ::estatus     buffer::MergeTracks()
         {
            i32 i;
            u32 dwAllocation;
            ::music::midi::track * ptrack;


            dwAllocation = sizeof(CHUNKHDR) + sizeof(MIDIFILEHDR);

            for(i = 0; i < m_ptracks->GetMidiTrackCount(); i++)
            {
               ptrack = m_ptracks->MidiTrackAt(i);
               dwAllocation += ptrack->GetTrackImageLength();
//               ptrack->SetAutoAllocation();
            }

            try
            {
               allocate(dwAllocation);
            }
            catch(memory_exception * pe)
            {
               delete pe;
               return error_no_memory;
            }

            byte * hpbDest, * hpbSrc;

            hpbDest = GetImage();

            hpbDest += sizeof(CHUNKHDR);

            hpbDest += sizeof(MIDIFILEHDR);

            for(i = 0; i < m_ptracks->GetMidiTrackCount(); i++)
            {

               ptrack = m_ptracks->MidiTrackAt(i);
               hpbSrc = ptrack->GetTrackImage();
               ::memcpy_dup(hpbDest, hpbSrc, ptrack->GetTrackImageLength());
               ptrack->Initialize(m_ptracks);
               ptrack->WriteHeaderLength();
               hpbDest += ptrack->GetTrackImageLength();

            }

            hpbDest = GetImage();

            CHUNKHDR * lpch = (CHUNKHDR *) hpbDest;
            lpch->fourccType = FOURCC_MThd;
            //lpch->dwLength = DWORDSWAP(this->get_size());
            lpch->dwLength = DWORDSWAP(sizeof(MIDIFILEHDR));

            //   m_ptracks->remove_all();
            SetOpened();
            return ::success;

         }

         ::estatus     buffer::WorkMergeTracks()
         {
            ::music::midi::track * ptrack;
            for(i32 i = 0; i < m_ptracks->GetMidiTrackCount(); i++)
            {
               ptrack = m_ptracks->MidiTrackAt(i);
               ptrack->FromWorkTrack(false);
            }
            return MergeTracks();
         }



         //i32 buffer::CalcMelodyTrack(::music::midi::events **ppEvents, imedia_position_array *pTicks)
         //{
         //    return -1;
         // return m_ptracks->CalcMelodyTrack(ppEvents, pTicks, m_pFileHeader->wFormat);
         //}

         /*i32 buffer::WorkCalcMelodyTrack(
            ::music::midi::events ** ppEvents,
            imedia_position_array & positiona,
            int_array & iaTokenLine)
         {
            return m_ptracks->WorkCalcMelodyTrack(
               ppEvents,
               positiona,
               iaTokenLine,
               m_pFileHeader->wFormat);
         }*/

         ::estatus     buffer::SaveFile(const char * lpcFilePath)
         {
            HMMIO                   hmmio = (HMMIO)nullptr;
            //    ::estatus                   smfrc = ::success;
            MMIOINFO                mmioinfo;

            ASSERT(lpcFilePath != nullptr);

            LPTSTR lpFilePath = _tcsdup(lpcFilePath);

            /* Verify that the file can be opened or created
            */
            __memset(&mmioinfo, 0, sizeof(mmioinfo));

            hmmio = mmioOpen(lpFilePath, &mmioinfo, MMIO_WRITE |MMIO_ALLOCBUF);
            if ((HMMIO)nullptr == hmmio)
            {
               TRACE(_T( "smfOpenFile: mmioOpen failed!"));
               return ESaveFailed;
            }

            if(mmioWrite(hmmio, (char _huge* ) GetImage(), GetImageSize()) != (i32) GetImageSize())
            {
               TRACE(_T( "smfOpenFile: mmioOpen failed!"));
               return ESaveFailed;
            }

            return ::success;
         }

         ::estatus     buffer::SaveFile(::file::file &ar)
         {
            ar.write(GetImage(), GetImageSize());
            return ::success;
         }

         bool buffer::IsTune1000File()
         {
            return m_ptracks->IsTune1000File();
         }

         bool buffer::IsSoftKaraokeFile(bool bWork, string_array * pstra)
         {
            return m_ptracks->IsSoftKaraokeFile(bWork, pstra);
         }

         /*buffer::estatus  buffer::DeleteEvent(event_base *pEvent)
         {
         buffer::estatus      smfrc;
         if(pEvent->GetImage() > 0)
         {
         if(pEvent->_GetDelta() != 0)
         {
         // if this event being deleted has non-zero delta,
         // the previous event must have it delta corrected;
         event   previousEvent;
         if(buffer::success != (smfrc = GetPreviousEvent(
         &previousEvent,
         pEvent)))
         {
         return smfrc;
         }
         if(buffer::success != (smfrc = ChangeEventDelta(
         &previousEvent,
         previouspevent->m_tkDelta + pEvent->_GetDelta())))
         {
         return smfrc;
         }
         }
         track * pTrack = m_ptracks->GetEventTrack(pEvent);
         if(pTrack == nullptr)
         return TrackNotFound;
         pTrack->m_smti.m_cbLength -= pEvent->GetImageSize();
         pTrack->WriteHeaderLength();
         m_cbImage -= pEvent->GetImageSize();
         __memmov(
         pEvent->GetImage(),
         pEvent->GetImage() + pEvent->GetImageSize(),
         m_cbImage - (pEvent->GetImage() - m_hpbImage) - pEvent->GetImageSize());
         if(buffer::success != (smfrc = BuildIndex()))
         {
         return smfrc;
         }

         return buffer::success;
         }
         else
         {
         return buffer::success;
         }

         } */

         ::estatus     buffer::GetPreviousEvent(
         ::music::midi::event  * pPreviousEvent,
         ::music::midi::event  * pEvent)
         {
            UNREFERENCED_PARAMETER(pPreviousEvent);

            ::estatus                   smfrc;
            ::music::midi::event *           pevent;
            ::music::midi::event *           peventPrevious;

            m_ptracks->m_tkPosition = 0;
            GetFlags().remove(file::EndOfFile);
            m_ptracks->GetFlags().remove(file::EndOfFile);

            m_ptracks->seek_begin();
            //for (ptrk = m_rTracks, idxTrack = m_dwTracks; idxTrack--; ptrk++)

            while(::success == (smfrc = GetNextEvent(pevent, pEvent->GetPosition(), TRUE)))
            {
               if(pevent->GetImage() == pEvent->GetImage())
               {
                  pEvent->operator =(*peventPrevious);
                  return ::success;
               }
               peventPrevious = pevent;
            }

            if (success_reached_tk_max != smfrc)
            {
               return smfrc;
            }

            return ::success;

         }

         ::estatus     buffer::ReplaceSameDeltaEvent(::music::midi::event &eventNew)
         {
            i32 iCurrentTrack = m_ptracks->m_iCurrentTrack;
            if(iCurrentTrack < 0)
               return EError;
            ::music::midi::track * pTrkMidi = (::music::midi::track *) m_ptracks->TrackAt(iCurrentTrack);
            ASSERT(pTrkMidi->GetType() == ::music::midi::track_base::TypeMidi);
            i32 iCurrentEvent = pTrkMidi->GetCurrentEvent();
            if(iCurrentEvent < 0)
               return EError;

            ::music::midi::track_v8 & trackWork = pTrkMidi->GetWorkTrack();

            ::music::midi::event & event = trackWork.EventAt(iCurrentEvent);

            event = eventNew;
            return ::success;
         }
         /*::estatus     ReplaceSameDeltaEvent(::music::midi::event *pEventOld, CMidiEventV007 *pEventNew)
         {
         ASSERT(pEventOld->_GetDeltaTicks() == pEventNew->_GetDeltaTicks());
         ASSERT(pEventNew->IsAutoAllocated());
         track * pTrack = m_ptracks->GetEventTrack(pEventOld);
         if(pTrack == nullptr)
         return TrackNotFound;
         byte * hpbImage = pEventOld->GetImage();
         byte * hpbFileImage = m_hpbImage;
         if(pEventOld->GetImageSize() != pEventNew->m_cbImage)
         {
         i32 iAddUp = pEventNew->m_cbImage - pEventOld->GetImageSize();
         pEventNew->m_pTrack = pTrack;
         allocate_add_up(iAddUp);
         hpbImage += hpbFileImage - m_hpbImage;
         pTrack->m_smti.m_cbLength += iAddUp;
         pTrack->WriteHeaderLength();
         __memmov(
         hpbImage + iAddUp,
         hpbImage,
         m_cbImage - (hpbImage - m_hpbImage));
         m_cbImage += iAddUp;
         }
         ::memcpy_dup(hpbImage, pEventNew->GetImage(), pEventNew->m_cbImage);

         WriteHeader();

         return ::success;*/

         /*   ASSERT(pEventOld->_GetDeltaTicks() == pEventNew->_GetDeltaTicks());
         ASSERT(pEventNew->IsAutoAllocated());
         track * pTrack = m_ptracks->GetEventTrack(pEventOld);
         if(pTrack == nullptr)
         return TrackNotFound;
         byte * hpbImage = pEventOld->GetImage();
         byte * hpbFileImage = m_hpbImage;
         if(pEventOld->GetImageSize() != pEventNew->m_cbImage)
         {
         i32 iAddUp = pEventNew->m_cbImage - pEventOld->GetImageSize();
         pEventNew->m_pTrack = pTrack;
         allocate_add_up(iAddUp);
         hpbImage += hpbFileImage - m_hpbImage;
         pTrack->m_smti.m_cbLength += iAddUp;
         pTrack->WriteHeaderLength();
         __memmov(
         hpbImage + iAddUp,
         hpbImage,
         m_cbImage - (hpbImage - m_hpbImage));
         m_cbImage += iAddUp;
         }
         ::memcpy_dup(hpbImage, pEventNew->GetImage(), pEventNew->m_cbImage);

         WriteHeader();

         return ::success;

         }*/

         /*::estatus     ChangeEventDelta(::music::midi::event *pEvent, imedia_time tkNewDelta)
         {
         ::estatus     smfrc;
         if(pEvent->_GetDelta() != tkNewDelta)
         {
         track * pTrack = m_ptracks->GetEventTrack(pEvent);
         if(pTrack == nullptr)
         return TrackNotFound;
         byte buffer[256];
         u32 dwSetUsed = ::music::midi::event::SetVDWord(buffer, 256, tkNewDelta);
         imedia_time tkOldDelta;
         u32 dwGetUsed = ::music::midi::event::GetVDWord(pEvent->GetImage(), 256, &tkOldDelta);
         ASSERT(tkOldDelta == pEvent->_GetDelta());
         byte * hpbImage = pEvent->GetImage();
         if(dwSetUsed != dwGetUsed)
         {
         i32 iAddUp = dwSetUsed - dwGetUsed;
         if(iAddUp > 0)
         {
         if(!allocate(m_cbImage + iAddUp))
         {
         TRACE("DeleteEvent No Memory for deleting\n");
         return ::music::midi::error_no_memory;
         }
         }
         pTrack->m_smti.m_cbLength += iAddUp;
         pTrack->WriteHeaderLength();
         __memmov(
         hpbImage + iAddUp,
         hpbImage,
         m_cbImage - (hpbImage - m_hpbImage));
         m_cbImage += iAddUp;
         if(::success != (smfrc = BuildIndex()))
         {
         return smfrc;
         }
         }
         ::music::midi::event::SetVDWord(hpbImage, dwSetUsed, tkNewDelta);
         return ::success;
         }
         else
         return ::success;

         }*/

         ::estatus     buffer::WriteHeader(MIDIFILEHDR * lpmfh)
         {
            m_pMThd = (CHUNKHDR *) GetImage();
            //   u32 dwLength = m_cbImage - sizeof(CHUNKHDR);
            //  m_pMThd->dwLength = DWORDSWAP(dwLength);
            m_pMThd->fourccType = FOURCC_MThd;
            m_pMThd->dwLength = DWORDSWAP(sizeof(MIDIFILEHDR));
            m_pFileHeader = (LPMIDIFILEHDR) (GetImage() + sizeof(CHUNKHDR));
            ::memcpy_dup(m_pFileHeader, lpmfh, sizeof(MIDIFILEHDR));
            return ::success;
         }



         bool buffer::IsXFFile()
         {
            m_ptracks->seek_begin();
            return m_ptracks->IsXFFile();
         }

         i32 buffer::SetKeyShift(i32 iKeyShift)
         {
            m_iKeyShift = iKeyShift;
            return true;
         }

         i32 buffer::GetKeyShift()
         {
            return m_iKeyShift;
         }


         void buffer::FromWorkStorage()
         {
            m_ptracks->FromWorkStorage();

         }
         void buffer::ToWorkStorage()
         {
            m_ptracks->ToWorkStorage();
         }

         ::estatus     buffer::SetTempoShift(i32 iTempoShift)
         {
            m_iTempoShift = iTempoShift;
            return ::success;
         }

         i32 buffer::GetTempoShift()
         {
            return m_iTempoShift;
         }

         double buffer::GetTempoShiftRate()
         {
            return exp((double) m_iTempoShift * log(3.0) / 10.0);
         }


         ::music::midi::tempo_map_entry * buffer::GetTempoMapEntry(const imedia_time & tk)
         {
            i32 idx;
            for (idx = 0; idx < m_tempomap.get_size(); idx++)
            {
               ::music::midi::tempo_map_entry & tempo = m_tempomap.element_at(idx);
               if((i32) tk < (i32) tempo.tkTempo)
                  break;
            }
            if(idx <= 0)
               return nullptr;
            else
               return &m_tempomap.element_at(idx - 1);
         }

         // event must have space to put event data
         ::estatus     buffer::GetTempoEvent(::music::midi::event &event)
         {
            ::music::midi::tempo_map_entry * pmtme = GetTempoMapEntry(m_ptracks->m_tkPosition);
            if(pmtme != nullptr)
            {
               double dTempo;
               dTempo = pmtme->dwTempo;
               //dTempo = dTempo / GetTempoShiftRate();
               union
               {
                  u32   dw;
                  byte    ba[4];
               } uA, uB;
               uA.dw = (u32) dTempo;
               uB.ba[0] = uA.ba[2];
               uB.ba[1] = uA.ba[1];
               uB.ba[2] = uA.ba[0];

               event.SetFullType(meta);
               event.SetMetaType(meta_tempo);
               event.SetParam(&uB.dw, 3);
            }
            return ::success;

         }

         ::estatus     buffer::InsertTempoEvent()
         {
            ::music::midi::tempo_map_entry * pmtme = GetTempoMapEntry(m_ptracks->m_tkPosition);
            if(pmtme != nullptr)
            {
               ::music::midi::event * pevent = new ::music::midi::event();
               GetTempoEvent(*pevent);
               m_mepaOnQuarterNote.add(pevent);
            }
            return ::success;
         }

         ::estatus     buffer::Format0()
         {
            MIDIFILEHDR fileHdr;

            fileHdr.wFormat = WORDSWAP(0);
            fileHdr.wDivision = m_pFileHeader->wDivision ;
            fileHdr.wTracks = WORDSWAP(1) ;

            ::music::midi::track * pTrackUnion = new ::music::midi::track(get_object());
            pTrackUnion->Initialize(m_ptracks);
            m_ptracks->CompactTracks(*pTrackUnion, true, true);

            m_ptracks->RemoveAllMidiTracks();
            ::music::midi::track * ptrack = m_ptracks->CreateTrack();
            *ptrack = *pTrackUnion;


            ::estatus     smfrc;
            if(MMSYSERR_NOERROR != (smfrc = MergeTracks()))
               return smfrc;

            WriteHeader(&fileHdr);

            if(MMSYSERR_NOERROR != (smfrc = Build()))
               return smfrc;

            return ::success;
         }

         byte * buffer::GetImage()
         {
            return get_data();
         }

         u32 buffer::GetImageSize()
         {
            return (u32) this->get_size();
         }

         void buffer::OnStop()
         {
            m_ptracks->OnStop();
         }


         ::estatus     buffer::ImmediatePutTempoChange()
         {

            ::music::midi::event * pevent = new ::music::midi::event;

            GetTempoEvent(*pevent);

            m_mepaImmediate.add(pevent);

            return ::success;

         }



         ::estatus     buffer::WorkStreamRender(LPMIDIHDR lpmh, imedia_time tkMax, u32 cbPrerollNominalMax)
         {
            ::estatus           smfrc;
            ::music::midi::event *           pevent;
            array < ::music::midi::event *, ::music::midi::event * > eventptraPositionCB;
            LPDWORD                    lpdw;
            imedia_time                        tkDelta;
            imedia_time                        tkLastDelta = 0 ;
            imedia_time                      tkOnQuarterNoteDelta = 0;
            //   imedia_time                        tkLastPosition;
            imedia_time      tkPosition;
            imedia_time      tkPositionF1;
            imedia_time &    tkLastPosition = m_positionLastWorkRender;
            ASSERT(lpmh != nullptr);

            /////////////////////////////////////////////////////////////////////////////
            // read events from the track and pack them into the buffer in polymsg
            // format.
            //
            // If a SysEx or meta would go over a buffer boundry, split it.
            /////////////////////////////////////////////////////////////////////////////

            lpmh->dwBytesRecorded = 0;
            if(m_dwPendingUserEvent)
            {
               smfrc = InsertParmData((imedia_time)0, lpmh);
               if(::success != smfrc)
               {
                  TRACE( "smfInsertParmData() -> %u", (u32)smfrc);
                  return smfrc;
               }
            }

            lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);

            if (GetFlags().has(file::EndOfFile))
            {
               return success_end_of_file;
            }

            if(tkLastPosition > GetPosition())
            {
               tkLastPosition = GetPosition();
            }
            while(true)
            {
               ASSERT(lpmh->dwBytesRecorded <= lpmh->dwBufferLength);
               if(lpmh->dwBytesRecorded > cbPrerollNominalMax
                     && eventptraPositionCB.get_size() <= 0)
               {
                  break;
               }

               // If we know ahead of time we won't have room for the
               // event, just break out now. We need 2 u32's for the
               // terminator event and at least 2 u32's for any
               // event we might store - this will allow us a full
               // i16 event or the delta time and stub for a long
               // event to be split.
               //
               //


               // now 16 DWORDS
               //
               if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4*sizeof(u32))
               {
                  break;
               }

               tkLastDelta = 0;

               if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4*sizeof(u32))
               {
                  //         m_ptracks->m_tkPosition += tkDelta;
                  break;
               }

               smfrc = WorkGetNextEvent(pevent, tkMax, TRUE);
               if (::success != smfrc)
               {
                  // smfGetNextEvent doesn't set this because smfSeek uses it
                  // as well and needs to distinguish between reaching the
                  // seek point and reaching end-of-file.
                  //
                  // To the ::account::user, however, we present the selection between
                  // their given tkBase and tkEnd as the entire file, therefore
                  // we want to translate this into EOF.
                  //
                  return smfrc;

                  TRACE( "smfReadEvents: ReadEvents() -> %u", (u32)smfrc);
                  break;
               }

               ASSERT(GetPosition() >= tkLastPosition);

               tkPosition  = GetPosition();
               tkDelta     = tkPosition - tkLastPosition;

               // The position CB events are grouped in a single position CB
               // event after other type of simultaneous events.
               // The {if block} change the order of simultaneous events.
               // position CB events ( pevent->GetFlags() & 1 )
               // are streamed together in a single position CB event, through
               // StreamEventF1 member function.
               // These position CB events are put after any other kind of event
               // that have the same position.
               // The order of the non PositionCB events are not altered.

               if(pevent->GetFlags() & 1)
               {
                  if(eventptraPositionCB.get_size() <= 0)
                  {
                     // This is the first PositionCB event
                     // at the F1 position.
                     eventptraPositionCB.add(pevent);
                     tkPositionF1   = tkPosition;
                  }
                  else if(tkPosition == tkPositionF1)
                  {
                     // This is another PositionCB event
                     // at the F1 position.
                     eventptraPositionCB.add(pevent);
                  }
                  else
                  {
                     // This is another PositionCB event
                     // at another position.

                     ASSERT(tkPositionF1 >= tkLastPosition);

                     tkDelta = tkPositionF1 - tkLastPosition;
                     StreamEventF1(tkDelta, eventptraPositionCB, lpmh, tkMax, cbPrerollNominalMax);
                     tkLastPosition = tkPositionF1;
                     eventptraPositionCB.remove_all();

                     eventptraPositionCB.add(pevent);
                     tkPositionF1   = tkPosition;
                  }
               }
               else
               {
                  if(eventptraPositionCB.get_size() > 0)
                  {
                     if(pevent->GetPosition() != eventptraPositionCB[0]->GetPosition())
                     {
                        ASSERT(tkPositionF1 >= tkLastPosition);

                        tkDelta = tkPositionF1 - tkLastPosition;
                        StreamEventF1(tkDelta, eventptraPositionCB, lpmh, tkMax, cbPrerollNominalMax);
                        tkDelta = tkPosition - tkPositionF1;
                        eventptraPositionCB.remove_all();
                     }
                     else
                     {
                        // The event to be streamed in the following StreamEvent function
                        // has the same position of the eventptraPositionCB events.
                        // So, when these eventptraPositionCB events are streamed,
                        // the event delta will be zero.
                        tkDelta = tkPosition - tkPositionF1;
                        tkPositionF1   = tkPosition;
                     }
                  }
                  /*         if(pevent->GetType() == NoteOn)
                  {
                  TRACE("WorkStreamRender: NoteOn     position %d Delta %d Track %d\n",
                  m_ptracks->GetPosition(),
                  tkDelta,
                  pevent->GetTrack());
                  }
                  else
                  {
                  TRACE("WorkStreamRender: Type Other position %d Delta %d\n",
                  m_ptracks->GetPosition(),
                  tkDelta);
                  }*/

                  StreamEvent(tkDelta, pevent, lpmh, tkMax, cbPrerollNominalMax);
                  tkLastPosition = tkPosition;
               }

            }

            return (GetFlags().has(file::EndOfFile)) ? success_end_of_file : ::success;
         }

         ::estatus     buffer::WorkGetNextRawEvent(
         ::music::midi::event *&      pevent,
         imedia_time                tkMax,
         bool                  bTkMaxInclusive)
         {
            if(GetFlags().has(file::EndOfFile))
            {
               return success_end_of_file;
            }
            ::estatus     smfrc = m_ptracks->WorkGetNextRawEvent(
                             pevent,
                             tkMax,
                             bTkMaxInclusive,
                             false);
            if(smfrc == ::success_end_of_file)
            {
               GetFlags().add(file::EndOfFile);
            }
            return smfrc;
         }

         ::estatus     buffer::WorkGetNextRawMidiEvent(
         ::music::midi::event *&      pevent,
         imedia_time                tkMax,
         bool                  bTkMaxInclusive)
         {
            if(GetFlags().has(file::EndOfFile))
            {
               return success_end_of_file;
            }
            ::estatus     smfrc = m_ptracks->WorkGetNextRawMidiEvent(
                             pevent,
                             tkMax,
                             bTkMaxInclusive,
                             false);
            if(smfrc == ::success_end_of_file)
            {
               GetFlags().add(file::EndOfFile);
            }
            return smfrc;
         }

         ::estatus     buffer::WorkGetNextEvent(
         ::music::midi::event *&      pevent,
         imedia_time                tkMax,
         bool                  bTkMaxInclusive)
         {
            if (GetFlags().has(file::EndOfFile))
            {
               return success_end_of_file;
            }
            // XXX
            /*   if(!GetFlags().has(DisablePlayLevel1Operations))
            {
            if(m_mepaImmediate.get_size() > 0)
            {
            event * peventImmediate = m_mepaImmediate.element_at(0);
            pevent = peventImmediate;
            delete peventImmediate;
            m_mepaImmediate.remove_at(0);
            return ::success;
            }
            if(m_mepaOnQuarterNote.get_size() > 0)
            {
            imedia_time tkMod = m_ptracks->m_tkPosition  % WORDSWAP(m_pFileHeader->wDivision);
            imedia_time tkQuarterNote;
            if(tkMod == 0)
            {
            tkQuarterNote = m_ptracks->m_tkPosition;
            }
            else
            {
            tkQuarterNote = m_ptracks->m_tkPosition + WORDSWAP(m_pFileHeader->wDivision) - tkMod;
            }
            imedia_time tkPosition;
            ::estatus     smfrc = GetNextEventTkPosition(&tkPosition, tkMax);
            if(smfrc == ::success_end_of_file)
            GetFlags().add(file::EndOfFile);
            if(tkPosition > tkQuarterNote)
            {
            m_ptracks->m_tkPosition  = tkQuarterNote;
            pevent = m_mepaOnQuarterNote.element_at(0);
            delete m_mepaOnQuarterNote.element_at(0);
            m_mepaOnQuarterNote.remove_at(0);
            return ::success;
            }
            }
            }*/

            ::estatus     smfrc;
            while(true)
            {
               smfrc   = m_ptracks->WorkGetNextEvent(
                         pevent,
                         tkMax,
                         bTkMaxInclusive,
                         false);
               if(smfrc != ::success)
               {
                  break;
               }
               //      if(GetFlags().has(DisablePlayLevel1Operations))
               //    {
               //     break;
               //      }
               if(GetFlags().has(file::DisableMute))
               {
                  break;
               }
               else
               {
                  if(pevent->GetType() == note_on
                        && pevent->GetNoteVelocity() > 0
                        && m_iaMuteTrack.contains(pevent->GetTrack()))
                  {
                     ASSERT(TRUE);
                  }
                  else
                  {
                     break;
                  }
               }
            }

            if(!GetFlags().has(file::DisablePlayLevel1Operations))
            {
               if(pevent->GetType() == note_on &&
                     pevent->GetNoteVelocity() != 0)
               {
                  m_ptracks->m_iaNoteOn.element_at(pevent->GetTrack())++;
                  m_ptracks->m_iaLevel.element_at(pevent->GetTrack())
                     = pevent->GetNoteVelocity();
               }
               else if((pevent->GetType() == note_on &&
                        pevent->GetNoteVelocity() == 0) ||
                       pevent->GetType() == note_off)
               {
                  i32 iCount = m_ptracks->m_iaNoteOn.element_at(pevent->GetTrack());
                  if(iCount > 0)
                     iCount--;
                  m_ptracks->m_iaNoteOn.element_at(pevent->GetTrack()) =
                  iCount;
                  if(iCount == 0)
                     m_ptracks->m_iaLevel.element_at(pevent->GetTrack())
                        = 0;
               }
            }
            if(smfrc == ::success_end_of_file)
            {
               GetFlags().add(file::EndOfFile);
            }
            return smfrc;



         }


         ::estatus     buffer::WorkSeek(
         imedia_time                   tkPosition,
         LPMIDIHDR               lpmh)
         {

            ::estatus            smfrc;
            ::music::midi::event *           pevent;
            LPDWORD                    lpdw;
            byte                       bEvent;
            u32                       idx;
            u32                       idxChannel;
            u32                       idxController;

            _SyncSeek(tkPosition);

            m_positionLastWorkRender.set_maximum();

            __memset(&m_keyframe, 0xFF, sizeof(m_keyframe));
            __memset(&m_keyframe.rbProgram, 0x00, sizeof(m_keyframe.rbProgram));

            m_ptracks->m_tkPosition = 0;
            GetFlags().remove(file::EndOfFile);
            m_ptracks->GetFlags().remove(file::EndOfFile);

            m_ptracks->WorkSeekBegin();

            while (::success == (smfrc = WorkGetNextEvent(pevent, tkPosition, FALSE)))
            {
               if (meta == (bEvent = pevent->GetFullType()))
               {
                  if (pevent->GetMetaType() == meta_tempo)
                  {
                     if (pevent->GetParamSize() != sizeof(m_keyframe.rbTempo))
                        return error_invalid_file;

                     ::memcpy_dup((byte *)m_keyframe.rbTempo, pevent->GetParam(), pevent->GetParamSize());
                  }
               }
               if((bEvent & 0xF0) == program_change)
               {
                  m_keyframe.rbProgram[bEvent & 0x0F] = pevent->GetChB1();
               }
               else if((bEvent & 0xF0) == control_change)
               {
                  m_keyframe.rbControl[(((::u16)bEvent & 0x0F)*120) + pevent->GetChB1()] =
                  pevent->GetChB2();
               }
            }

            if (success_reached_tk_max != smfrc)
            {
               return smfrc;
            }

            /* Build lpmh from keyframe
            */
            //lpmh->dwBytesRecorded = 0;
            lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);

            /* Tempo change event?
            */
            if (KF_EMPTY != m_keyframe.rbTempo[0] ||
                  KF_EMPTY != m_keyframe.rbTempo[1] ||
                  KF_EMPTY != m_keyframe.rbTempo[2])
            {
               if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 3*sizeof(u32))
                  return error_no_memory;

               *lpdw++ = 0;
               *lpdw++ = 0;
               u32 dwTempo =   (((u32)m_keyframe.rbTempo[0])<<16)|
                                    (((u32)m_keyframe.rbTempo[1])<<8)|
                                    ((u32)m_keyframe.rbTempo[2]);
               dwTempo = (u32) ((double) dwTempo / GetTempoShiftRate());
               u32 dw = (((u32)MEVT_TEMPO)<<24)| dwTempo;

               *lpdw++ = dw;

               lpmh->dwBytesRecorded += 3*sizeof(u32);
            }

            /* Program change events?
            */
            for (idx = 0; idx < 16; idx++)
            {
               if (KF_EMPTY != m_keyframe.rbProgram[idx])
               {
                  if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 3*sizeof(u32))
                     return error_no_memory;

                  *lpdw++ = 0;
                  *lpdw++ = 0;
                  *lpdw++ = (((u32)MEVT_SHORTMSG) << 24)      |
                            ((u32)program_change)         |
                            ((u32)idx)                        |
                            (((u32)m_keyframe.rbProgram[idx]) << 8);

                  lpmh->dwBytesRecorded += 3*sizeof(u32);
               }
            }

            /* Controller events?
            */
            idx = 0;
            for (idxChannel = 0; idxChannel < 16; idxChannel++)
            {
               for (idxController = 0; idxController < 120; idxController++)
               {
                  if (KF_EMPTY != m_keyframe.rbControl[idx])
                  {
                     if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 3*sizeof(u32))
                        return error_no_memory;

                     *lpdw++ = 0;
                     *lpdw++ = 0;
                     *lpdw++ = (((u32)MEVT_SHORTMSG << 24)     |
                                ((u32)control_change)       |
                                ((u32)idxChannel)               |
                                (((u32)idxController) << 8)     |
                                (((u32)m_keyframe.rbControl[idx]) << 16));


                     lpmh->dwBytesRecorded += 3*sizeof(u32);
                  }

                  idx++;
               }
            }

            /* Force all tracks to be at tkPosition. We are guaranteed that
            ** all tracks will be past the event immediately preceding tkPosition;
            ** this will force correct delta-ticks to be generated so that events
            ** on all tracks will line up properly on a seek into the middle of the
            ** file.
            */
            // ^^^^ This cause problems... tracks are already positioned...
            // changing track position make all the song envents be shifted
            // irregularly...
            //    for (ptrk = m_rTracks, idxTrack = m_dwTracks; idxTrack--; ptrk++)
            //   for (idxTrack = m_dwTracks; idxTrack--;)
            //  {
            //   ptrk = m_tracks[idxTrack];
            //  ptrk->tkPosition        = tkPosition;
            //}
            //return seek(tkPosition);

            return ::success;
         }

         /*         ::estatus     buffer::CreateTempoMap()
                  {
                     bool bFirst = true;
                     ::music::midi::tempo_map_entry tempo;
                     ::estatus     smfrc;
                     ::music::midi::event * pevent;
                     m_ptracks->WorkSeekBegin();
                     while (success
                        == (smfrc = WorkGetNextRawMidiEvent(pevent, MAX_TICKS, TRUE)))
                     {
                        if (meta == pevent->GetFullType() &&
                           meta_tempo == pevent->GetMetaType() &&
                           (pevent->GetFlags() != 1))
                        {
                           if (3 != pevent->GetParamSize())
                           {
                              return error_invalid_file;
                           }

                           if (bFirst && m_ptracks->m_tkPosition != 0)
                           {
                              /* Inserting first event and the absolute time is zero.
                              ** Use defaults of 500,000 uSec/qn from MIDI spec
                              */

         /*tempo.tkTempo = 0;
         tempo.msBase  = 0;
         tempo.dwTempo = ::music::midi::DefaultTempo;
         m_tempomap.add(tempo);


         bFirst = false;
         }

         tempo.tkTempo = m_ptracks->m_tkPosition;

         if (bFirst)
         tempo.msBase = 0;
         else
         {
         ::music::midi::tempo_map_entry * pLastTempo = &m_tempomap.element_at(m_tempomap.get_size() - 1) ;
         /* NOTE: Better not be here unless we're q/n format!
         */
         //                ptempo->msBase = (ptempo-1)->msBase +
         //                               muldiv32(ptempo->tkTempo-((ptempo-1)->tkTempo),
         //                                      (ptempo-1)->dwTempo,
         //                                    1000L*m_MusicTempoTimeDivision);
         /*tempo.msBase = (pLastTempo)->msBase +
            muldiv32((i32) (tempo.tkTempo-((pLastTempo)->tkTempo)),
            (pLastTempo)->dwTempo,
            1000L * m_MusicTempoTimeDivision);
         }

         tempo.dwTempo = (((u32)pevent->GetParam()[0])<<16) |
         (((u32)pevent->GetParam()[1])<<8) |
         ((u32)pevent->GetParam()[2]);

         m_tempomap.add(tempo);
         }
         }
         if (0 == m_tempomap.get_size())
         {
         TRACE("File contains no tempo map! Insert default tempo.");

         ::music::midi::tempo_map_entry * ptempo = &m_tempomap.add_new();
         ptempo->tkTempo = 0;
         ptempo->msBase  = 0;
         //      ptempo->dwTempo = DefaultTempo;
         ptempo->dwTempo = ::music::midi::DefaultTempo;
         }

         return ::success;

         }*/

         ::estatus     buffer::CalcTkLength()
         {
            m_tkLength = m_ptracks->CalcTkLength();
            return ::success;

         }

         ::estatus     buffer::WorkSeekBegin()
         {
            m_ptracks->WorkSeekBegin();
            GetFlags().remove(file::EndOfFile);
            m_tkLastDelta = 0;
            m_positionLastWorkRender.set_maximum();
            return ::success;
         }

         void buffer::MuteTrack(i32 iIndex, bool bMute)
         {
            if(bMute)
            {
               m_iaMuteTrack.add_unique(iIndex);
            }
            else
            {
               m_iaMuteTrack.remove(iIndex);
            }
         }

         void buffer::MuteAll(bool bMute, i32 iExcludeTrack)
         {
            for(i32 i = 0; i < 16; i++)
            {
               if(i == iExcludeTrack)
               {
                  MuteTrack(i, !bMute);
               }
               else
               {
                  MuteTrack(i, bMute);
               }
            }
         }

         bool buffer::IsTrackMute(i32 iIndex)
         {
            return m_iaMuteTrack.contains(iIndex);
         }


         bool buffer::IsNull()
         {
            if(this == nullptr)
               return true;
            return false;
         }

         void buffer::WorkSeekEnd()
         {
            GetTracks().WorkSeekEnd();
         }

         void buffer::AttachSeekSync(::ikaraoke::events_tracks_v1 *ptracksv1)
         {
            m_evtrkv1ptraSeek.add(ptracksv1);
         }

         void buffer::_SyncSeek(imedia_time tkPosition)
         {
            for(i32 i = 0; i < m_evtrkv1ptraSeek.get_size(); i++)
            {
               _SyncSeek(tkPosition, m_evtrkv1ptraSeek.element_at(i));
            }
         }

         void buffer::_SyncSeek(
         imedia_time tkPosition,
         ::ikaraoke::events_tracks_v1 *ptracksv1)
         {
            ASSERT(ptracksv1 != nullptr);
            ::ikaraoke::lyric_events_v1 * pEventsV1;
            ::ikaraoke::lyric_events_v2 * pEventsV2;

            ::index iTokenIndex = -1;
            ::index iNoteIndex = -1;
            ::index i;
            for(i = 0; i < ptracksv1->get_size(); i++)
            {
               pEventsV1 =   ptracksv1->get_at(i);
               if(pEventsV1->GetClassOrder() == 2)
               {
                  pEventsV2 = (::ikaraoke::lyric_events_v2 *) pEventsV1;
                  iNoteIndex = pEventsV2->GetPositionNote(tkPosition);
                  if(iNoteIndex >= 0)
                  {
                     break;
                  }
                  iTokenIndex = pEventsV2->GetPositionToken(tkPosition);
                  if(iTokenIndex >= 0)
                  {
                     break;
                  }
               }
            }
            if(iTokenIndex < 0 && iNoteIndex < 0)
            {
               iTokenIndex = 0;
               iNoteIndex = 0;
            }
            else if(iNoteIndex < 0)
            {
               iNoteIndex = pEventsV2->GetTokenFirstNote(iTokenIndex);
               if(iNoteIndex < 0)
                  iNoteIndex = 0;
            }
            else if(iTokenIndex < 0)
            {
               iTokenIndex = pEventsV2->GetNoteFirstToken(iNoteIndex);
               if(iTokenIndex < 0)
                  iTokenIndex = 0;
            }
            for(i = 0; i < ptracksv1->get_size(); i++)
            {
               ptracksv1->get_at(i)->m_iCurrentToken = iTokenIndex;
               ptracksv1->get_at(i)->m_iCurrentNote = iNoteIndex;
            }
         }



         imedia_time buffer::GetPosition()
         {
            return m_ptracks->GetPosition();
         }

         i32 buffer::GetDivision()
         {
            return WORDSWAP(m_pFileHeader->wDivision);
         }

         i32 buffer::GetFormat()
         {
            return WORDSWAP(m_pFileHeader->wFormat);
         }


         ::estatus     buffer::WorkWriteXFTracks(
         string_array &  tokena,
         imedia_position_array & positiona,
         ::music::xf::info_header & xfinfoheader)
         {
            ::music::midi::tracks & tracka = GetTracks();

            while(tracka.GetTrackCount() > 1)
            {
               tracka.remove_at(1);
            }



            ::music::midi::track & track = *(class ::music::midi::track *) tracka.TrackAt(0);
            if(!track.IsXFFile())
            {
               byte XFVERSIONID[] =
               {
                  0x43,  // YAMAHA ID
                  0x7B,  //
                  0x00,  //
                  0x58,  // X
                  0x46,  // F
                  0x30,  // 0
                  0x32,   // 2
                  0x00,
                  0x11
               };
               track.seek_begin();
               ::music::midi::event eventV008;
               eventV008.SetPosition(0);
               eventV008.SetFullType(meta);
               eventV008.SetMetaType(::music::midi::MetaSeqSpecific);
               eventV008.SetParam(XFVERSIONID, sizeof(XFVERSIONID));
               track.GetWorkTrack().insert_at(0, eventV008);
            }

            ::music::xf::info_header xfInfoHeader;

            class ::music::midi::track * pmiditrack = tracka.CreateTrack(FOURCC_XFIH);

            pmiditrack->WorkWriteXFInfoHeader(
            nullptr,
            &xfinfoheader,
            nullptr);
            pmiditrack->GetEvent().SetFullType(meta);
            pmiditrack->GetEvent().SetMetaType(meta_end_of_track);
            pmiditrack->GetEvent().SetParam(nullptr, 0);
            pmiditrack->GetEvent().SetDelta(0);
            pmiditrack->WorkWriteEvent();

            pmiditrack = tracka.CreateTrack(FOURCC_XFIH);

            pmiditrack->WriteXFLyricTrack(tokena, positiona, "L1");

            return ::success;
         }


         bool buffer::IsOpened()
         {
            return GetFlags().has(file::Opened);
         }

         void buffer::SetOpened(bool bOpened)
         {
            if(bOpened)
            {
               GetFlags().add(file::Opened);
            }
            else
            {
               GetFlags().remove(file::Opened);
            }
         }


      } //namespace mmsystem


   } // namespace midi


} // namespace music









