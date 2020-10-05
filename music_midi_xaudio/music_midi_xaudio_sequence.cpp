#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         sequence::sequence(::layered * pobjectContext) :
            ::object(pobject),
            ::ikaraoke::karaoke(pobject),
            ::music::midi::sequence(pobject)
         {

            m_hstream = nullptr;

            m_buffera.Initialize(16, m_cbPreroll, (uptr) (void *) &m_midicallbackdata);
            m_midicallbackdata.m_psequence = this;


         };

         sequence::~sequence()
         {

            CloseFile();

         }


         /***************************************************************************
         *
         * seqAllocBuffers
         *
         * allocate buffers for this instance.
         *
         * pSeq                      - The sequencer instance to allocate buffers for.
         *
         * Returns
         *   success If the operation was successful.
         *
         *   MCIERR_OUT_OF_MEMORY  If there is insufficient memory for
         *     the requested number and size of buffers.
         *
         * seqAllocBuffers allocates playback buffers based on the
         * cbBuffer and cBuffer fields of pSeq. cbBuffer specifies the
         * number of bytes in each buffer, and cBuffer specifies the
         * number of buffers to allocate.
         *
         * seqAllocBuffers must be called before any other sequencer call
         * on a newly allocted SEQUENCE structure. It must be paired with
         * a call to seqFreeBuffers, which should be the last call made
         * before the SEQUENCE structure is discarded.
         *
         ***************************************************************************/
         ::estatus     sequence::AllocBuffers()
         {
            ASSERT(FALSE);
            /*
            u32                   dwEachBufferSize;
            u32                   dwAlloc;
            u32                    i;
            LPBYTE                  lpbWork;

            //    assert(pSeq != nullptr);

            SetState(state_no_file);
            m_lpmhFree  = nullptr;
            m_lpbAlloc  = nullptr;
            //    m_hSmf      = (HSMF)nullptr;

            // First make sure we can allocate the buffers they asked for
            //
            dwEachBufferSize = sizeof(MIDIHDR) + (u32)(m_cbBuffer);
            dwAlloc          = dwEachBufferSize * (u32)(m_cBuffer);

            //m_lpbAlloc = (uchar *) GlobalAllocPtr(GMEM_MOVEABLE|GMEM_SHARE, dwAlloc);
            m_lpbAlloc = (uchar *) HeapAlloc(GetProcessHeap(), 0, dwAlloc);
            if (nullptr == m_lpbAlloc)
            return MCIERR_OUT_OF_MEMORY;

            // Initialize all MIDIHDR's and __throw( them into a free list
            //
            m_lpmhFree = nullptr;

            lpbWork = m_lpbAlloc;
            for (i=0; i < m_cBuffer; i++)
            {
            ((LPMIDIHDR)lpbWork)->lpNext            = m_lpmhFree;

            ((LPMIDIHDR)lpbWork)->lpData            = (char *) (lpbWork + sizeof(MIDIHDR));
            ((LPMIDIHDR)lpbWork)->dwBufferLength    = m_cbBuffer;
            ((LPMIDIHDR)lpbWork)->dwBytesRecorded   = 0;
            ((LPMIDIHDR)lpbWork)->dwUser            = (u32)(u32)this;
            ((LPMIDIHDR)lpbWork)->dwFlags           = 0;

            m_lpmhFree = (LPMIDIHDR)lpbWork;

            lpbWork += dwEachBufferSize;
            }

            return ::success;*/

            return error_failed;

         }

         /***************************************************************************
         *
         * seqFreeBuffers
         *
         * Free buffers for this instance.
         *
         * pSeq                      - The sequencer instance to free buffers for.
         *
         * seqFreeBuffers frees all allocated memory belonging to the
         * given sequencer instance pSeq. It must be the last call
         * performed on the instance before it is destroyed.
         *
         ****************************************************************************/
         VOID sequence::FreeBuffers()
         {
            ASSERT(FALSE);
         }

         /***************************************************************************
         *
         * seqOpenFile
         *
         * Associates a MIDI file with the given sequencer instance.
         *
         * pSeq                      - The sequencer instance.
         *
         * Returns
         *   success If the operation is successful.
         *
         *   error_unsupported_function If there is already a file open
         *     on this instance.
         *
         *   MCIERR_OUT_OF_MEMORY If there was insufficient memory to
         *     allocate internal buffers on the file.
         *
         *   MCIERR_INVALID_FILE If initial attempts to parse the file
         *     failed (such as the file is not a MIDI or RMI file).
         *
         * seqOpenFile may only be called if there is no currently open file
         * on the instance. It must be paired with a call to seqCloseFile
         * when operations on this file are complete.
         *
         * The pstrFile field of pSeq contains the name of the file
         * to open. This name will be passed directly to mmioOpen; it may
         * contain a specifcation for a custom MMIO file handler. The task
         * context used for all I/O will be the task which calls seqOpenFile.
         *
         ***************************************************************************/

         ::estatus     sequence::OpenFile(::music::midi::sequence & sequence, i32 openMode)
         {

            ::estatus                    rc = ::success;
            SMFFILEINFO             sfi;
            ::estatus                    smfrc;
            u32                cbBuffer;

            if (GetState() != state_no_file)
            {

               return error_unsupported_function;

            }

            m_iOpenMode = openMode;

            smfrc = file()->OpenFile(*sequence.get_file(), openMode);


            if(::success != smfrc)
            {

               goto Seq_Open_File_Cleanup;

            }

            file()->GetFileInfo(&sfi);

            m_MusicTempoTimeDivision = sfi.dwTimeDivision;
            m_tkLength       = sfi.tkLength;
            if(m_iOpenMode == file::open_for_playing)
            {
               m_msLength      = TicksToMillisecs(m_tkLength);
            }
            /* Track buffers must be big enough to hold the state data returned
            ** by smfSeek()
            */
            cbBuffer = min(m_cbBuffer, ::music::midi::GetStateMaxSize());


Seq_Open_File_Cleanup:
            if (::success != rc)
               CloseFile();
            else
               SetState(state_opened);

            return rc;
         }


         ::estatus     sequence::OpenFile(const char * lpFileName, i32 openMode)
         {

            file_pointer file;

            try
            {

               file = Context.file().get_file(lpFileName, ::file::mode_read | ::file::share_deny_write | ::file::type_binary);

            }
            catch(...)
            {

            }

            return OpenFile(*file, openMode);

         }


         ::estatus     sequence::OpenFile(memory * pmemorystorage, i32 openMode, e_storage estorage)
         {

            SMFFILEINFO                sfi;
            ::estatus                       smfrc;
            u32                   cbBuffer;

            if (GetState() != state_no_file)
            {

               CloseFile();

            }

            m_iOpenMode = openMode;

            smfrc = file()->OpenFile(pmemorystorage, openMode, estorage);

            if (::success != smfrc)
            {

            }
            else
            {
               file()->GetFileInfo(&sfi);

               m_MusicTempoTimeDivision = sfi.dwTimeDivision;
               m_tkLength       = sfi.tkLength;
               if(m_iOpenMode == file::open_for_playing)
               {
                  m_msLength      = TicksToMillisecs(m_tkLength);
               }
               /* Track buffers must be big enough to hold the state data returned
               ** by smfSeek()
               */
               cbBuffer = min(m_cbBuffer, ::music::midi::GetStateMaxSize());
            }

            if(::success != smfrc)
               CloseFile();
            else
               SetState(state_opened);

            return smfrc;

         }

         ::estatus     sequence::OpenFile(::file::file & ar, i32 openMode)
         {

            SMFFILEINFO                sfi;
            ::estatus                       smfrc = ::success;
            u32                   cbBuffer;

            if (GetState() != state_no_file)
            {

               return error_unsupported_function;

            }



            //   m_pstrFile = _tcsdup(lpFileName);
            //   m_strFile = lpFileName;

            //    ASSERT(m_pstrFile != nullptr);

            m_iOpenMode = openMode;

            //    sofs.pstrName     = m_pstrFile;

            //PSMF pSmf = new SMF();

            //smfrc = file()->OpenFile(&sofs);
            smfrc = file()->OpenFile(ar, openMode);

            //smfrc = smfOpenFile(&sofs);
            if (::success != smfrc)
            {
            }
            else
            {
               //    m_hSmf = sofs.hSmf;
               //    ((PSMF) m_hSmf)->GetFileInfo(&sfi);
               file()->GetFileInfo(&sfi);

               m_MusicTempoTimeDivision = sfi.dwTimeDivision;
               m_tkLength       = sfi.tkLength;
               if(m_iOpenMode == file::open_for_playing)
               {
                  m_msLength      = TicksToMillisecs(m_tkLength);
               }
               /* Track buffers must be big enough to hold the state data returned
               ** by smfSeek()
               */
               cbBuffer = min(m_cbBuffer, ::music::midi::GetStateMaxSize());
            }

            if(::success != smfrc)
               CloseFile();
            else
               SetState(state_opened);

            return smfrc;

         }


         /***************************************************************************
         *
         * seqCloseFile
         *
         * Deassociates a MIDI file with the given sequencer instance.
         *
         * pSeq                      -  The sequencer instance.
         *
         * Returns
         *   success If the operation is successful.
         *
         *   error_unsupported_function If the sequencer instance is not
         *     stopped.
         *
         * A call to seqCloseFile must be paired with a prior call to
         * seqOpenFile. All buffers associated with the file will be
         * freed and the file will be closed. The sequencer must be
         * stopped before this call will be accepted.
         *
         ***************************************************************************/
         ::estatus     sequence::CloseFile()
         {

            single_lock sl(&m_mutex, true);

            //if (state_no_file == GetState())
            //   return error_unsupported_function;

            file()->CloseFile();

            /* If we were prerolled, need to clean up -- have an open MIDI handle
            ** and buffers in the ready queue
            */

            //    single_lock slStream(&m_csStream, false);

            //    for (lpmh = m_lpmhFree; lpmh; lpmh = lpmh->lpNext)
            //    for (lpmh = m_buffera[0]; lpmh != nullptr; lpmh = lpmh->lpNext)


            /*   m_lpmhFree = nullptr;

            if (m_lpmhPreroll != nullptr)
            {
            slStream.lock();
            if(m_hstream != nullptr)
            {
            midiOutUnprepareHeader((HMIDIOUT) m_hstream, m_lpmhPreroll, sizeof(*m_lpmhPreroll));
            }
            slStream.unlock();
            }
            m_lpmhPreroll = nullptr;*/
            //    slStream.lock();
            if (m_hstream != nullptr)
            {
               m_buffera.midiOutUnprepareHeader((HMIDIOUT) m_hstream);
               midiStreamClose( m_hstream);
               m_hstream = nullptr;
            }
            //  slStream.unlock();

            SetState(state_no_file);

            return ::success;

         }


         /***************************************************************************
         *
         * seqPreroll
         *
         * Prepares the file for playback at the given position.
         *
         * pSeq                      - The sequencer instance.
         *
         * lpPreroll                 - Specifies the starting and ending tick
         *                             positions to play between.
         *
         * Returns
         *   success If the operation is successful.
         *
         *   error_unsupported_function If the sequencer instance is not
         *     opened or prerolled.
         *
         * open the device so we can initialize channels.
         *
         * Loop through the tracks. For each track, seek to the given position and
         * send the init data SMF gives us to the handle.
         *
         * Wait for all init buffers to finish.
         *
         * Unprepare the buffers (they're only ever sent here; the sequencer
         * engine merges them into a single stream during normal playback) and
         * refill them with the first chunk of data from the track.
         *
         *
         ****************************************************************************/
         ::estatus     sequence::Preroll(::thread * pthread, ::music::midi::LPPREROLL lpPreroll, bool bThrow)
         {

            UNREFERENCED_PARAMETER(pthread);

            single_lock sl(&m_mutex, TRUE);

            i32                 i;
            ::estatus                    smfrc;
            ::estatus      estatus = ::success;
            MIDIPROPTIMEDIV         mptd;
            LPMIDIHDR               lpmh = nullptr;
            u32                uDeviceID;


            ASSERT(m_iOpenMode == file::open_for_playing || IsInSpecialModeV001());

            m_flags.remove(FlagEOF);

            m_estatusLastError = ::success;

            if(GetState() != state_opened &&
                  GetState() != state_pre_rolled &&
                  !IsInSpecialModeV001())
               return error_unsupported_function;

            m_tkBase = lpPreroll->tkBase;
            m_tkEnd = lpPreroll->tkEnd;
            if(m_hstream != nullptr)
            {
               // Recollect buffers from MMSYSTEM back into free queue
               //
               SetState(::music::midi::sequence::state_reset);
               midiOutReset((HMIDIOUT) m_hstream);
               while (m_uBuffersInMMSYSTEM)
                  Sleep(0);
            }
            else
            {
            }

            m_uBuffersInMMSYSTEM = 0;
            SetState(::music::midi::sequence::state_pre_rolling);

            //
            // We've successfully opened the file and all of the tracks; now
            // open the MIDI device and set the time division.
            //
            // NOTE: seqPreroll is equivalent to seek; device might already be open
            //

            if (m_hstream == nullptr)
            {
               uDeviceID = m_uiDeviceID;
               //uDeviceID = MIDI_MAPPER;
               estatus = translate_mmr(midiStreamOpen(&m_hstream,
                                                      &uDeviceID,
                                                      1,
                                                      (uptr) &MidiOutProc,
                                                      0,
                                                      CALLBACK_FUNCTION));
               if(estatus != ::success)
               {
                  m_hstream = nullptr;
                  if(bThrow)
                  {
                     SetState(state_opened);
                     __throw(multimedia::exception(multimedia::exception_music, EMidiPlayerPrerollStreamOpen));
                  }
                  TRACE("midiStreamOpenError %d\n", estatus);
                  //goto seq_Preroll_Cleanup;
                  if(estatus == MMSYSERR_BADDEVICEID)
                     goto seq_Preroll_Cleanup;
                  else if(estatus == MMSYSERR_INVALPARAM)
                     goto seq_Preroll_Cleanup;
                  else if(estatus == MMSYSERR_NOMEM)
                     goto seq_Preroll_Cleanup;
                  else
                     goto seq_Preroll_Cleanup;
               }

               mptd.cbStruct  = sizeof(mptd);

               mptd.dwTimeDiv = m_MusicTempoTimeDivision;

               estatus = midiStreamProperty(m_hstream, (LPBYTE) &mptd, MIDIPROP_SET | MIDIPROP_TIMEDIV);

               if (estatus != ::success)
               {

                  TRACE( "midiStreamProperty() -> %04X", (WORD)estatus);

                  midiStreamClose(m_hstream);

                  m_hstream = nullptr;

                  estatus = error_not_ready;

                  if(bThrow)
                  {

                     SetState(state_opened);

                     __throw(multimedia::exception(multimedia::exception_midi, estatus));

                  }

                  goto seq_Preroll_Cleanup;

               }

            }

            estatus = ::success;

            m_buffera.Reset();

            lpmh = &m_buffera[0].m_midihdr;

            if(IsInSpecialModeV001())
            {
               if(m_eoperation == operation_general_midi_reset)
               {
                  const uchar gmModeOn[] =
                  {
                     //        0x00, 0x00, 0x00, 0x00,
                     //        0x00, 0x00, 0x00, 0x00,
                     //        0x1b, 0x8a, 0x06, MEVT_TEMPO,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x06, 0x00, 0x00, MEVT_LONGMSG,
                     0xf0, 0x7e, 0x7f, 0x09,
                     0x01, 0xf7, 0x00, 0x00
                  };
                  char * lpch = lpmh->lpData + lpmh->dwBytesRecorded;
                  lpmh->dwBytesRecorded += sizeof(gmModeOn);
                  ::memcpy_dup(lpch, gmModeOn, sizeof(gmModeOn));
                  SetSpecialModeV001Flag(false);
               }
            }

            smfrc = file()->WorkSeek(m_tkBase, lpmh);

            m_tkPrerollBase = get_file()->GetPosition();




            m_flags.remove(FlagEOF);
            file()->GetFlags().remove(file::EndOfFile);
            for(i = 1; i < m_buffera.get_size(); i++)
            {
               lpmh = m_buffera[i].GetMidiHdr();

               smfrc = file()->WorkStreamRender(lpmh, m_tkEnd, m_cbPrerollNominalMax);

               if(::success != smfrc && success_end_of_file != smfrc)
               {

                  TRACE( "SFP: smfReadEvents() -> %u", (u32)smfrc);

                  estatus, smfrc;

                  goto seq_Preroll_Cleanup;

               }


               if (success_end_of_file == smfrc)
               {
                  m_flags.add(FlagEOF);
                  break;
               }
            }

            estatus = m_buffera.midiOutPrepareHeader((HMIDIOUT) m_hstream);
            if (estatus != ::success)
            {

               TRACE( "midiOutPrepare(preroll) -> %lu!", (u32)estatus);

               estatus = error_not_ready;

               if(bThrow)
               {

                  SetState(state_opened);

                  __throw(multimedia::exception(multimedia::exception_midi, estatus));

               }
               else
               {
                  goto seq_Preroll_Cleanup;
               }
            }


            estatus = m_buffera.midiStreamOut(m_hstream);
            if (estatus != ::success)
            {
               TRACE( "midiOutPrepare(preroll) -> %lu!", (u32)estatus);
               estatus = error_not_ready;
               if(bThrow)
               {
                  SetState(state_opened);
                  __throw(multimedia::exception(multimedia::exception_midi, EMidiPlayerPrerollPrepareHeader2));
               }
               else
               {
                  goto seq_Preroll_Cleanup;
               }
            }
            m_uBuffersInMMSYSTEM +=(u32)  m_buffera.get_size();

seq_Preroll_Cleanup:

            if (estatus != ::success)
            {
               SetState(state_opened);
               m_flags.remove(::music::midi::sequence::FlagWaiting);
            }
            else
            {
               SetState(state_pre_rolled);
            }

            return estatus;
         }

         /***************************************************************************
         *
         * seqStart
         *
         * Starts playback at the current position.
         *
         * pSeq                      - The sequencer instance.
         *
         * Returns
         *   success If the operation is successful.
         *
         *   error_unsupported_function If the sequencer instance is not
         *     stopped.
         *
         *   error_not_ready If the underlying MIDI device could
         *     not be opened or fails any call.
         *
         * The sequencer must be prerolled before seqStart may be called.
         *
         * Just feed everything in the ready queue to the device.
         *
         ***************************************************************************/
         ::estatus     sequence::Start()
         {

            single_lock sl(&m_mutex, TRUE);

            if (::music::midi::sequence::state_pre_rolled != GetState())
            {

               TRACE( "seqStart(): State is wrong! [%u]", GetState());

               return error_unsupported_function;

            }

            SetState(::music::midi::sequence::state_playing);

            m_evMmsgDone.ResetEvent();

            ::estatus     estatus = ::success;
            if(m_hstream != nullptr)
            {
               estatus = midiStreamRestart(m_hstream);
            }
            sl.unlock();
            if(estatus == ::success)
            {
               thread()->PostMidiSequenceEvent(this, ::music::midi::sequence::EventMidiPlaybackStart);

            }
            return estatus;
         }

         /***************************************************************************
         *
         * seqPause
         *
         * Pauses playback of the instance.
         *
         * pSeq                      - The sequencer instance.
         *
         * Returns
         *   success If the operation is successful.
         *
         *   error_unsupported_function If the sequencer instance is not
         *     playing.
         *
         * The sequencer must be playing before seqPause may be called.
         * Pausing the sequencer will cause all currently on notes to be turned
         * off. This may cause playback to be slightly inaccurate on restart
         * due to missing notes.
         *
         ***************************************************************************/
         ::estatus     sequence::Pause()

         {
            single_lock sl(&m_mutex, TRUE);

            //    assert(nullptr != pSeq);

            if (state_playing != GetState())
               return error_unsupported_function;

            SetState(state_paused);

            ::estatus     estatus = ::success;
            //    single_lock slStream(&m_csStream, false);
            //  slStream.lock();
            if(m_hstream != nullptr)
            {
               estatus = midiStreamPause(m_hstream);
            }
            //slStream.unlock();

            SetLevelMeter(0);

            return ::success;
         }

         /***************************************************************************
         *
         * seqRestart
         *
         * Restarts playback of an instance after a pause.
         *
         * pSeq                      - The sequencer instance.
         *
         * Returns
         *    success If the operation is successful.
         *
         *    error_unsupported_function If the sequencer instance is not
         *     paused.
         *
         * The sequencer must be paused before seqRestart may be called.
         *
         ***************************************************************************/
         ::estatus     sequence::Restart()
         {
            //    assert(nullptr != pSeq);

            single_lock sl(&m_mutex, TRUE);

            if (state_paused != GetState())
               return error_unsupported_function;

            SetState(state_playing);
            m_evMmsgDone.ResetEvent();

            //    ::estatus     estatus = 0;
            //    single_lock slStream(&m_csStream, false);
            //  slStream.lock();
            if(m_hstream != nullptr)
            {
               midiStreamRestart(m_hstream);
            }
            //slStream.unlock();
            return ::success;
         }

         /***************************************************************************
         *
         * seqStop
         *
         * Totally stops playback of an instance.
         *
         * pSeq                      - The sequencer instance.
         *
         * Returns
         *   success If the operation is successful.
         *
         *   error_unsupported_function If the sequencer instance is not
         *     paused or playing.
         *
         * The sequencer must be paused or playing before seqStop may be called.
         *
         ***************************************************************************/
         ::estatus     sequence::Stop()
         {

            single_lock sl(&m_mutex, TRUE);

            if(GetState() == state_stopping)
               return ::success;

            // Automatic success if we're already stopped
            if (GetState() != state_playing
                  && GetState() != state_paused)
            {
               m_flags.remove(::music::midi::sequence::FlagWaiting);
               GetPlayerLink().OnFinishCommand(::music::midi::player::command_stop);
               return ::success;
            }

            SetState(state_stopping);
            m_flags.add(::music::midi::sequence::FlagWaiting);

            m_eventMidiPlaybackEnd.ResetEvent();

            if(m_hstream != nullptr)
            {

               m_estatusLastError = midiStreamStop(m_hstream);

               if(::success != m_estatusLastError)
               {

                  TRACE( "::music::midi::sequence::Stop() -> midiOutStop() returned %lu in seqStop()!\n", (u32)m_estatusLastError);

                  m_flags.remove(FlagWaiting);

                  return error_not_ready;

               }

            }

            //m_eventMidiPlaybackEnd.lock();

            SetLevelMeter(0);

            return ::success;

         }

         /***************************************************************************
         *
         * seqTime
         *
         * Determine the current position in playback of an instance.
         *
         * pSeq                      - The sequencer instance.
         *
         * pTicks                    - A pointer to a u32 where the current position
         *                             in ticks will be returned.
         *
         * Returns
         *   success If the operation is successful.
         *
         *   error_not_ready If the underlying device fails to report
         *     the position.
         *
         *   error_unsupported_function If the sequencer instance is not
         *     paused or playing.
         *
         * The sequencer must be paused, playing or prerolled before seqTime
         * may be called.
         *
         ***************************************************************************/
         ::estatus     sequence::get_ticks(imedia_time &  pTicks)
         {
            single_lock sl(&m_mutex);
            if(!sl.lock(millis(184)))
               return ::multimedia::result_internal;

            ::estatus                    mmr;
            MMTIME                  mmt;

            if (::music::midi::sequence::state_playing != GetState() &&
                  ::music::midi::sequence::state_paused != GetState() &&
                  ::music::midi::sequence::state_pre_rolling != GetState() &&
                  ::music::midi::sequence::state_pre_rolled != GetState() &&
                  ::music::midi::sequence::state_opened != GetState() &&
                  ::music::midi::sequence::state_stopping != GetState())
            {
               TRACE( "seqTime(): State wrong! [is %u]", GetState());
               return error_unsupported_function;
            }

            pTicks = 0;
            if (state_opened != GetState())
            {
               pTicks = m_tkBase;
               if (state_pre_rolled != GetState())
               {
                  mmt.wType = TIME_TICKS;
                  //            single_lock slStream(&m_csStream, false);
                  //          slStream.lock();
                  if(m_hstream == nullptr)
                  {
                     TRACE("m_hmidi == nullptr!!!!");
                     return error_not_ready;
                  }
                  else
                  {
                     try
                     {

                        mmr = midiStreamPosition(m_hstream, &mmt, sizeof(mmt));

                        if (::success != mmr)
                        {

                           TRACE( "midiStreamPosition() returned %lu", (u32)mmr);

                           return error_not_ready;

                        }

                     }
                     catch(...)
                     {

                        return error_not_ready;

                     }

                     pTicks += mmt.u.ticks;

                  }

                  //        slStream.unlock();

               }

            }

            return ::success;

         }

         void sequence::get_time(imedia_time & time)
         {
            get_millis(time);
         }

         ::estatus     sequence::get_millis(imedia_time & time)
         {
            single_lock sl(&m_mutex);
            if(!sl.lock(millis(184)))
               return ::multimedia::result_internal;

            ::estatus                    mmr;
            MMTIME                  mmt;

            if (state_playing != GetState() &&
                  state_paused != GetState() &&
                  state_pre_rolling != GetState() &&
                  state_pre_rolled != GetState() &&
                  state_opened != GetState() &&
                  state_stopping != GetState())
            {
               TRACE( "seqTime(): State wrong! [is %u]", GetState());
               return error_unsupported_function;
            }

            time = 0;
            if (state_opened != GetState())
            {
               time = (iptr) TicksToMillisecs(m_tkBase);
               if (state_pre_rolled != GetState())
               {
                  mmt.wType = TIME_MS;
                  //            single_lock slStream(&m_csStream, false);
                  //          slStream.lock();
                  if(m_hstream == nullptr)
                  {
                     TRACE("m_hmidi == nullptr!!!!");
                     return error_not_ready;
                  }
                  else
                  {
                     try
                     {

                        mmr = midiStreamPosition(m_hstream, &mmt, sizeof(mmt));
                        if (::success != mmr)
                        {
                           TRACE( "midiStreamPosition() returned %lu", (u32)mmr);
                           return error_not_ready;
                        }
                     }
                     catch(...)
                     {
                        return error_not_ready;
                     }
                     time += mmt.u.ms;
                  }
                  //        slStream.unlock();
               }
            }

            return ::success;
         }

         /***************************************************************************
         *
         * seqMillisecsToTicks
         *
         * Given a millisecond offset in the output stream, returns the associated
         * tick position.
         *
         * pSeq                      - The sequencer instance.
         *
         * msOffset                  - The millisecond offset into the stream.
         *
         * Returns the number of ticks into the stream.
         *
         ***************************************************************************/
         imedia_time sequence::MillisecsToTicks(imedia_time msOffset)
         {
            return file()->MillisecsToTicks(msOffset);
         }

         /***************************************************************************
         *
         * seqTicksToMillisecs
         *
         * Given a tick offset in the output stream, returns the associated
         * millisecond position.
         *
         * pSeq                      - The sequencer instance.
         *
         * tkOffset                  - The tick offset into the stream.
         *
         * Returns the number of milliseconds into the stream.
         *
         ***************************************************************************/
         imedia_time sequence::TicksToMillisecs(imedia_time tkOffset)
         {
            return file()->TicksToMillisecs(tkOffset);
         }

         void sequence::OnDone(HMIDISTRM hmidistream, LPMIDIHDR lpmidihdr)
         {
            UNREFERENCED_PARAMETER(hmidistream);
            ::estatus                   smfrc;
            midi_callback_data *      lpData;
            ASSERT(lpmidihdr != nullptr);
            lpData = (midi_callback_data *) lpmidihdr->dwUser;
            ASSERT(lpData != nullptr);

            ::music::midi::sequence * psequence = lpData->m_psequence;

            sequence_thread * pthread = dynamic_cast < sequence_thread * > (psequence->m_pthread);

            ASSERT(nullptr != lpmidihdr);

            --m_uBuffersInMMSYSTEM;

            if(m_uBuffersInMMSYSTEM <= 0)
            {
               m_evBuffersZero.SetEvent();
            }

            if (state_reset == GetState())
            {
               // We're recollecting buffers from MMSYSTEM
               //
               //      if (lpmidihdr != m_lpmhPreroll)
               //    {
               //     lpmidihdr->lpNext    = m_lpmhFree;
               //   m_lpmhFree           = lpmidihdr;
               //      }
               return;
            }

            bool bStopping = state_stopping == GetState();
            bool bEndOfPlay = m_uBuffersInMMSYSTEM <= 0;
            bool bSpecialModeV001End = m_flags.has(flag_operation_end);

            if (bStopping || bEndOfPlay || bSpecialModeV001End)
            {
               //
               // Reached EOF, just put the buffer back on the free
               // list
               //
               if(bSpecialModeV001End)
               {
                  m_flags.remove(flag_operation_end);
                  TRACE("void CALLBACK ::music::midi::sequence::MidiOutProc m_flags.has(flag_operation_end\n");
                  pthread->PostMidiSequenceEvent(
                  this,
                  ::music::midi::sequence::EventSpecialModeV001End,
                  lpmidihdr);
               }
               else if(bStopping)
               {
                  if(m_uBuffersInMMSYSTEM == 0)
                  {
                     TRACE("void CALLBACK ::music::midi::sequence::MidiOutProc state_stopping == pSeq->GetState()\n");
                     pthread->PostMidiSequenceEvent(
                     this,
                     ::music::midi::sequence::EventStopped,
                     lpmidihdr);
                  }
               }
               else
               {
                  if(m_flags.has(FlagEOF))
                  {
                     TRACE("void CALLBACK ::music::midi::sequence::MidiOutProc m_flags.has(FlagEOF\n");
                  }
                  if(m_uBuffersInMMSYSTEM <= 0)
                  {
                     pthread->PostMidiSequenceEvent(
                     this,
                     ::music::midi::sequence::EventMidiPlaybackEnd,
                     lpmidihdr);
                  }
               }
            }
            else
            {
               if(IsInSpecialModeV001())
               {
                  if(m_eoperation == operation_general_midi_reset)
                  {
                     const uchar gmModeOn[] =
                     {
                        //        0x00, 0x00, 0x00, 0x00,
                        //        0x00, 0x00, 0x00, 0x00,
                        //        0x1b, 0x8a, 0x06, MEVT_TEMPO,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x06, 0x00, 0x00, MEVT_LONGMSG,
                        0xf0, 0x7e, 0x7f, 0x09,
                        0x01, 0xf7, 0x00, 0x00
                     };
                     lpmidihdr->dwBytesRecorded = sizeof(gmModeOn);
                     ::memcpy_dup(lpmidihdr->lpData, gmModeOn, sizeof(gmModeOn));
                  }
                  else if(m_eoperation == operation_tempo_change)
                  {
                     ::music::midi::event event;
                     file()->GetTempoEvent(event);
                     file()->StreamEvent(event.GetDelta(), &event, lpmidihdr, 0x7fffffff, 256);
                     // lpmidihdr->dwBytesRecorded = sizeof(gmModeOn);
                     // ::memcpy_dup(lpmidihdr->lpData, gmModeOn, sizeof(gmModeOn));
                  }
                  else
                  {
                     ASSERT(FALSE);
                  }
                  //post_thread_message(lpData->dwThreadID, MIDIPLAYERMESSAGE_STREAMOUT, (WPARAM) pSeq, (LPARAM) lpmidihdr);
                  pthread->PostMidiSequenceEvent(
                  this,
                  EventMidiStreamOut,
                  lpmidihdr);
                  m_flags.add(flag_operation_end);
                  smfrc = ::success;
                  return;
               }
               //
               // Not EOF yet; attempt to fill another buffer
               //
               pthread->PostMidiSequenceEvent(
               this,
               EventMidiStreamOut,
               lpmidihdr);
            }

         }

         void sequence::OnPositionCB(LPMIDIHDR lpmidihdr)
         {
            ASSERT(lpmidihdr != nullptr);
            LPBYTE lpbData = (LPBYTE) (lpmidihdr->lpData + lpmidihdr->dwOffset);
            MIDIEVENT * lpme = (MIDIEVENT *) lpbData;
            file::buffer::midi_stream_event_header * pheader = (file::buffer::midi_stream_event_header *) &lpme->dwParms[0];
            lpbData = (LPBYTE) pheader;
            LPDWORD lpdwParam;

            i32 iSize = pheader->m_dwLength;
            switch(pheader->m_dwType)
            {
            case 0:
            {
               array < ::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1 &> * plyriceventa = nullptr;
               array < ::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1 &> lyriceventa;
               for(i32 i = sizeof(file::buffer::midi_stream_event_header); i < iSize;)
               {
                  pheader = (file::buffer::midi_stream_event_header *) &lpbData[i];
                  lpdwParam = (LPDWORD) &lpbData[i + sizeof(file::buffer::midi_stream_event_header)];
                  ASSERT(*lpdwParam == pheader->m_dwType);
                  switch(pheader->m_dwType)
                  {
                  case EVENT_ID_LYRIC_V1:
                  {
                     if(plyriceventa == nullptr)
                     {
                        plyriceventa = new array <::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1 &>;
                     }
                     ::memory_file memFile(get_context_application(), (LPBYTE) &lpdwParam[1], pheader->m_dwLength - sizeof(u32));
                     /* x2x                  CArchive ar(&memFile, CArchive::load);
                     lyriceventa.Serialize(ar);
                     plyriceventa->append(lyriceventa); */
                  }
                  break;
                  case EVENT_ID_PAD:
                  {
                  }
                  break;
                  case EVENT_ID_NOTE_ON:
                  {
                     ::file::byte_stream_memory_file memFile(get_context_application(), (LPBYTE) &lpdwParam[1], pheader->m_dwLength - sizeof(u32));
                     for(i32 i = 0; i < m_iaLevel.get_size(); i++)
                     {
                        BYTE b;
                        memFile >> b;
                        m_iaLevel.element_at(i) = b;
                     }
                  }
                  break;
                  }
                  i += pheader->m_dwLength + sizeof(file::buffer::midi_stream_event_header);
               }
               /*         if(plyriceventa != nullptr)
               {
               ::PostMessage(m_midicallbackdata.oswindow, WM_APP + 3388, 3388, (LPARAM) plyriceventa);
               }*/
            }
            break;
            case EVENT_ID_PAD:
               break;
            default:
               ASSERT(FALSE);
               break;
            }

         }

         void CALLBACK sequence::MidiOutProc(HMIDIOUT hmo, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
         {

            UNREFERENCED_PARAMETER(hmo);
            UNREFERENCED_PARAMETER(dwInstance);
            UNREFERENCED_PARAMETER(dwParam2);

            LPMIDIHDR               lpmh         = (LPMIDIHDR) dwParam1;

            switch(wMsg)
            {
            case MOM_POSITIONCB:
               ((midi_callback_data *) lpmh->dwUser)->m_psequence->OnPositionCB(lpmh);
               break;
            case MOM_DONE:
               ((midi_callback_data *) lpmh->dwUser)->m_psequence->OnDone(nullptr,lpmh);
               return;
            }

         }


         bool sequence::IsPlaying()
         {
            return GetState() == state_playing ||
                   GetState() == state_stopping;
         }




         ::estatus     sequence::SaveFile()
         {

            return SaveFile(file()->m_strName);

         }


         ::estatus     sequence::SaveFile(const char * lpFileName)
         {

            return file()->SaveFile(lpFileName);

         }


         ::estatus     sequence::SaveFile(file_pointer &ar)
         {

            return file()->SaveFile(*ar);

         }


         u32 sequence::SetState(u32 uiState)
         {

            m_uiPreviousState = m_uiState;

            m_uiState = uiState;

            return m_uiPreviousState;

         }


         void sequence::SetSpecialModeV001Flag(bool bSet)
         {

            if(m_flags.has(flag_operation))
               m_flags.add(flag_was_operation);
            else
               m_flags.remove(flag_was_operation);

            if(bSet)
               m_flags.add(flag_operation);
            else
               m_flags.remove(flag_operation);

         }


         void sequence::set_operation(e_operation eoperation)
         {

            m_uiPreSpecialModeV001State = m_uiState;

            SetSpecialModeV001Flag();

            m_eoperation = eoperation;

         }


         bool sequence::IsInSpecialModeV001()
         {

            return m_flags.has(flag_operation);

         }


         bool sequence::WasInSpecialModeV001()
         {

            return m_flags.has(flag_was_operation);

         }


         void sequence::GetMidiDoneData(::music::midi::LPMIDIDONEDATA lpmdd)
         {

            lpmdd->m_flags = m_flags;

            lpmdd->m_uiSeqPreviousState = m_uiPreviousState;

            lpmdd->m_uiSeqState = m_uiState;

         }


         i32 sequence::GetKeyShift()
         {

            if(m_pfile == nullptr)
               return 0;

            return file()->GetKeyShift();

         }


         i32 sequence::SetKeyShift(i32 iKeyShift)
         {

            /*//    single_lock slStream(&m_csStream, false);
            //  slStream.lock();
            if(m_hstream)
            {
            midiStreamPause(m_hstream);
            if(!file()->SetKeyShift(iKeyShift))
            return false;
            midiStreamRestart(m_hstream);
            }
            //slStream.unlock();
            return true;
            void ::music::midi::sequence::SetKeyShift(i32 iShift)
            {*/

            bool bPlay = IsPlaying();

            imedia_time ticks = 0;

            if(bPlay)
            {

               ticks = GetPositionTicks();

               Stop();

            }

            get_file()->SetKeyShift(iKeyShift);

            if(bPlay)
            {

               m_pthread->PrerollAndWait(ticks);

               Start();

            }

            //}

            return true;

         }


         i32 sequence::GetTempoShift()
         {

            return file()->GetTempoShift();

         }



         i32 sequence::SetTempoShift(i32 iTempoShift)
         {

            //midiStreamPause(m_hstream);

            if(failed(file()->SetTempoShift(iTempoShift)))
               return false;

            //midiStreamRestart(m_hstream);

            return true;

         }


         bool sequence::SetMidiOutDevice(u32 uiDevice)
         {

            if(uiDevice == ::music::midi::device_default)
            {

               m_uiDeviceID = MIDI_MAPPER;

            }
            else
            {

               m_uiDeviceID = uiDevice;

            }

            return true;
         }

         ::estatus     sequence::CloseStream()
         {
            single_lock sl(&m_mutex, TRUE);
            if(IsPlaying())
            {
               Stop();
            }

            /* If we were prerolled, need to clean up -- have an open MIDI handle
            ** and buffers in the ready queue
            */

            m_buffera.midiOutUnprepareHeader((HMIDIOUT) m_hstream);

            if (m_hstream != nullptr)
            {
               midiStreamClose( m_hstream);
               m_hstream = nullptr;
            }

            SetState(state_opened);

            return ::success;
         }

         void sequence::SetLevelMeter(i32 iLevel)
         {
            for(i32 i = 0; i < m_iaLevel.get_size(); i++)
            {
               m_iaLevel.element_at(i) = iLevel;
            }
         }

         void sequence::OnMidiPlaybackEnd(::music::midi::sequence::event * pevent)
         {
            UNREFERENCED_PARAMETER(pevent);
            single_lock sl(&m_mutex, TRUE);
            //   LPMIDIHDR lpmh = pevent->m_lpmh;
            //   midi_callback_data * lpData = &m_midicallbackdata;
            ::estatus     estatus;


            if(0 == m_uBuffersInMMSYSTEM)
            {
               TRACE( "seqBufferDone: normal sequencer shutdown.");

               /* Totally done! Free device and notify.
               */
               if(m_hstream)
               {
                  if((estatus = m_buffera.midiOutUnprepareHeader((HMIDIOUT) m_hstream))
                        != ::success)
                  {
                     TRACE( "midiOutUnprepareHeader failed in seqBufferDone! (%lu)", (u32)estatus);
                  }
                  midiStreamClose(m_hstream);
                  m_hstream = nullptr;
               }

               m_estatusLastError = ::success;
               m_flags.remove(FlagWaiting);

               m_evMmsgDone.SetEvent();
            }
         }

         void sequence::OnEvent(::music::midi::sequence::event * pevent)
         {
            switch(pevent->m_eevent)
            {
            case EventSpecialModeV001End:
            {
               SetSpecialModeV001Flag(false);
               OnMidiPlaybackEnd(pevent);
               SetState(m_uiPreSpecialModeV001State);
            }
            break;
            case EventStopped:
            {
               OnMidiPlaybackEnd(pevent);
               SetState(state_opened);
            }
            break;
            case EventMidiPlaybackEnd:
            {
               OnMidiPlaybackEnd(pevent);
               SetState(state_opened);
            }
            break;
            case EventMidiStreamOut:
            {



               single_lock sl(&m_mutex, TRUE);

               ::music::midi::mmsystem::sequence::event * pev = (::music::midi::mmsystem::sequence::event *) pevent;

               if(m_flags.has(FlagEOF))
               {

                  return;

               }

               LPMIDIHDR lpmh = pev->m_lpmh;

               ::estatus     smfrc;

               if(IsInSpecialModeV001())
               {
                  TRACE("::music::midi::sequence::OnEvent EventMidiStreamOut IsInSpecialModeV001");
               }
               else
               {
                  smfrc = file()->WorkStreamRender(lpmh, m_tkEnd, m_cbPrerollNominalMax);
               }

               switch(smfrc)
               {
               case success:

                  break;

               case success_end_of_file:

                  m_flags.add(FlagEOF);

                  smfrc = ::success;

                  break;

               default:


                  TRACE( "smfReadEvents returned %lu in callback!", (u32) smfrc);

                  SetState(state_stopping);

                  break;

               }

               if(::music::midi::sequence::state_stopping == GetState())
               {

                  thread()->PostMidiSequenceEvent(this, EventMidiPlaybackEnd, lpmh);

                  return;

               }

               ::estatus     estatus;

               if(m_hstream != nullptr)
               {

                  estatus = midiStreamOut(m_hstream, lpmh, sizeof(*lpmh));

                  if(estatus == ::success)
                  {

                     ++m_uBuffersInMMSYSTEM;

                  }
                  else
                  {

                     TRACE("seqBufferDone(): midiStreamOut() returned %lu!", (u32)estatus);

                     SetState(::music::midi::sequence::state_stopping);

                  }


               }

            }
            default:
               break;
            }
         }

         imedia_time sequence::GetPositionTicks()
         {
            single_lock sl(&m_mutex);
            if(!sl.lock(millis(0)))
               return -1;
            MMTIME mmt;
            mmt.wType = TIME_TICKS;
            if(::success ==
                  midiStreamPosition(
                  m_hstream,
                  &mmt,
                  sizeof(mmt)))
               return mmt.u.ticks + m_tkPrerollBase;
            else
               return -1;
         }


         bool sequence::IsChangingTempo()
         {
            return m_flags.has(::music::midi::sequence::FlagTempoChange);
         }
         void sequence::SetTempoChangeFlag(bool bSet)
         {
            if(bSet)
               m_flags.add(::music::midi::sequence::FlagTempoChange);
            else
               m_flags.remove(::music::midi::sequence::FlagTempoChange);
         }




         bool sequence::IsNull()
         {
            if(this == nullptr)
               return true;
            return false;
         }

         imedia_time sequence::TimeToPosition(imedia_time millis)
         {
            return imedia_time(MillisecsToTicks((iptr) millis));
         }

         imedia_time sequence::PositionToTime(imedia_time tk)
         {
            return imedia_time(TicksToMillisecs((imedia_time) (iptr) tk));
         }

         void sequence::GetPosition(imedia_time & position)
         {
            get_ticks(position);
         }

         bool sequence::IsOpened()
         {
            return GetState() != state_no_file;
         }

         void sequence::GetTimeLength(imedia_time & time)
         {
            time = m_msLength;
         }



         void sequence::Prepare(
         string2a & str2a,
         imedia_position_2darray & tka2DTokensTicks,
         i32 iMelodyTrack,
         int2a & ia2TokenLine,
         ::ikaraoke::data & data)
         {

            UNREFERENCED_PARAMETER(str2a);

            ::music::midi::file::buffer & file = *this->file();

            ::music::midi::tracks & tracks = file.GetTracks();

            ASSERT(!file.IsNull());
            file.GetTracks().seek_begin();
            imedia_time               tkMax = file.m_tkLength;
            imedia_time               tkLastPosition = 0;


            ::ikaraoke::static_data & staticdata = data.GetStaticData();

            if(staticdata.m_LyricsDisplayOffset < 480)
            {
               staticdata.m_LyricsDisplayOffset = 480;
            }
            if(staticdata.m_LyricsDisplayOffset > 720)
            {
               staticdata.m_LyricsDisplayOffset = 720;
            }
            staticdata.m_LyricsDisplay = 30;

            imedia_position_2darray tk2DNoteOnPositions(get_object());
            imedia_position_2darray tk2DNoteOffPositions(get_object());
            imedia_position_2darray tk2DBegPositions(get_object());
            imedia_position_2darray tk2DEndPositions(get_object());
            imedia_time_2darray ms2DTokensMillis(get_object());
            imedia_time_2darray ms2DNoteOnMillis(get_object());
            imedia_time_2darray ms2DNoteOffMillis(get_object());
            imedia_time_2darray ms2DBegMillis(get_object());
            imedia_time_2darray ms2DEndMillis(get_object());
            ::music::midi::events midiEvents;




            // Note on and off events
            // and maximum and minimum
            // pitch bend peaks.
            ::music::midi::events midiEventsLevel2;

            ::music::midi::events noteOnEvents;
            ::music::midi::events noteOffEvents;

            ::music::midi::events eventsLevel2Beg;
            ::music::midi::events eventsLevel2End;
            ::ikaraoke::events_tracks_v1 lyricEventsForPositionCB;
            ::ikaraoke::events_tracks_v1 lyricEventsForBouncingBall;
            ::ikaraoke::events_tracks_v1 lyricEventsForScoring;
            ::ikaraoke::events_tracks_v1 lyricEvents;

            //   tracks.seek_begin();
            // tracks.GetXFInfoHeaders(
            //  &m_xfInfoHeaders);



            file.PositionToTime(
            ms2DTokensMillis,
            tka2DTokensTicks,
            0);

            ::ikaraoke::lyric_events_v2 *pLyricEventsV2;
            ::ikaraoke::lyric_events_v2 *pLyricEventsV2_;
            ::ikaraoke::lyric_events_v2 *pLyricEventsV2B;
            ::ikaraoke::lyric_events_v2 *pLyricEventsV2C;
            ::music::midi::events *pMidiEventsV1;

            tk2DNoteOnPositions.set_size_create(tka2DTokensTicks.get_size());
            tk2DNoteOffPositions.set_size_create(tka2DTokensTicks.get_size());
            tk2DBegPositions.set_size_create(tka2DTokensTicks.get_size());
            tk2DEndPositions.set_size_create(tka2DTokensTicks.get_size());
            i32 i;
            for(i = 0; i < tka2DTokensTicks.get_size(); i++)
            {
               pLyricEventsV2 = new ::ikaraoke::lyric_events_v2();
               pLyricEventsV2B = new ::ikaraoke::lyric_events_v2();
               pLyricEventsV2C = new ::ikaraoke::lyric_events_v2();
               pLyricEventsV2_ = new ::ikaraoke::lyric_events_v2();
               staticdata.m_eventsv1.add(pLyricEventsV2);
               staticdata.m_eventsv1.add(pLyricEventsV2B);
               staticdata.m_eventsv1.add(pLyricEventsV2C);
               staticdata.m_eventsv1.add(pLyricEventsV2_);
               lyricEvents.add(pLyricEventsV2_);
               lyricEventsForScoring.add(pLyricEventsV2);
               lyricEventsForPositionCB.add(pLyricEventsV2B);
               lyricEventsForBouncingBall.add(pLyricEventsV2C);
               pLyricEventsV2->m_iType = 0;
               pLyricEventsV2->m_iOrder = i;
               pLyricEventsV2->m_iType = 2;
               pLyricEventsV2->m_iOrder = i;
               pLyricEventsV2B->m_iType = ikaraoke::EventRunningElement;
               pLyricEventsV2B->m_iOrder = i;
               pLyricEventsV2C->m_iType = 4;
               pLyricEventsV2C->m_iOrder = i;
               pMidiEventsV1 = nullptr;
               if(iMelodyTrack < 0)
               {
                  pLyricEventsV2->m_iTrack =
                  file.WorkCalcMelodyTrack(
                  &pMidiEventsV1,
                  tka2DTokensTicks.operator[](i),
                  ia2TokenLine[i]);
               }
               else
               {
                  pLyricEventsV2->m_iTrack = iMelodyTrack;
               }
               pLyricEventsV2B->m_iTrack = pLyricEventsV2->m_iTrack;
               pLyricEventsV2C->m_iTrack = pLyricEventsV2->m_iTrack;
               pLyricEventsV2_->m_iTrack = pLyricEventsV2->m_iTrack;
               if(pLyricEventsV2->m_iTrack < 0)
               {
                  pLyricEventsV2->m_iTrack = tracks.m_iMelodyTrackTipA;
                  pLyricEventsV2B->m_iTrack = tracks.m_iMelodyTrackTipA;
                  pLyricEventsV2C->m_iTrack = tracks.m_iMelodyTrackTipA;
                  pLyricEventsV2_->m_iTrack = tracks.m_iMelodyTrackTipA;
               }
               staticdata.SetGuessMelodyTrack(pLyricEventsV2->m_iTrack);
               if(pLyricEventsV2->m_iTrack >= 0)
               {
                  if(file.GetFormat() == 0)
                  {
                     tracks.TrackAt(0)->WorkSeekBegin();
                     ((::music::midi::track *)tracks.TrackAt(0))->WorkGetNoteOnOffEventsV1(
                     &midiEvents,
                     (i32) pLyricEventsV2->m_iTrack,
                     file.GetFormat() == 1);
                     tracks.TrackAt(0)->WorkSeekBegin();
                     ((::music::midi::track *)tracks.TrackAt(0))->WorkGetLevel2Events(
                     &midiEventsLevel2,
                     (i32) pLyricEventsV2->m_iTrack,
                     file.GetFormat() == 1);
                  }
                  else
                  {
                     tracks.TrackAt(pLyricEventsV2->m_iTrack)->seek_begin();
                     ((::music::midi::track *)tracks.TrackAt(pLyricEventsV2->m_iTrack))->GetLevel2Events(
                     &midiEvents,
                     (i32) pLyricEventsV2->m_iTrack,
                     file.GetFormat() == 1);
                     tracks.TrackAt(pLyricEventsV2->m_iTrack)->seek_begin();
                     ((::music::midi::track *)tracks.TrackAt(pLyricEventsV2->m_iTrack))->GetLevel2Events(
                     &midiEventsLevel2,
                     (i32) pLyricEventsV2->m_iTrack,
                     file.GetFormat() == 1);
                  }
               }

               ::music::midi::util miditutil(get_object());

               miditutil.PrepareNoteOnOffEvents(
               &noteOnEvents,
               &noteOffEvents,
               (i32) pLyricEventsV2->m_iTrack,
               file.GetFormat(),
               &midiEvents,
               tka2DTokensTicks.operator[](i));

               miditutil.PrepareLevel2Events(
               &eventsLevel2Beg,
               &eventsLevel2End,
               (i32) pLyricEventsV2->m_iTrack,
               file.GetFormat(),
               &midiEventsLevel2,
               tka2DTokensTicks.operator[](i));


               tk2DNoteOnPositions[i]     = noteOnEvents.m_tkaEventsPosition;
               tk2DNoteOffPositions[i]    = noteOffEvents.m_tkaEventsPosition;
               tk2DBegPositions[i]        = eventsLevel2Beg.m_tkaEventsPosition;
               tk2DEndPositions[i]        = eventsLevel2End.m_tkaEventsPosition;
               pLyricEventsV2->m_dwaNotesData.copy(noteOnEvents.m_dwaEventsData);
               pLyricEventsV2B->m_dwaNotesData.copy(eventsLevel2Beg.m_dwaEventsData);
               pLyricEventsV2C->m_dwaNotesData.copy(eventsLevel2Beg.m_dwaEventsData);
               pLyricEventsV2_->m_dwaNotesData.copy(eventsLevel2Beg.m_dwaEventsData);
               midiEvents.remove_all();
               noteOnEvents.remove_all();
               noteOffEvents.remove_all();
               midiEventsLevel2.remove_all();
               eventsLevel2Beg.remove_all();
               eventsLevel2End.remove_all();
               delete pMidiEventsV1;
            }

            file.PositionToTime(
            ms2DNoteOnMillis,
            tk2DNoteOnPositions,
            0);

            file.PositionToTime(
            ms2DNoteOffMillis,
            tk2DNoteOffPositions,
            0);

            file.PositionToTime(
            ms2DBegMillis,
            tk2DBegPositions,
            0);

            file.PositionToTime(
            ms2DEndMillis,
            tk2DEndPositions,
            0);


            ::ikaraoke::lyric_events_v1 *pLyricEventsV1;


            for(i = 0; i < tka2DTokensTicks.get_size(); i++)
            {
               pLyricEventsV2 = (::ikaraoke::lyric_events_v2 *) lyricEvents.get_at(i);
               staticdata.m_eventstracks.add(pLyricEventsV2);
               file.TimeToPosition(
               pLyricEventsV2->m_tkaTokensPosition,
               ms2DTokensMillis[i],
               0);
               file.TimeToPosition(
               pLyricEventsV2->m_tkaNotesPosition,
               ms2DNoteOnMillis[i],
               0);

               imedia_time time1(0);
               imedia_time time2(0);

               pLyricEventsV2->m_msaTokensPosition.CopySorted(
               ms2DTokensMillis[i],
               time1,
               time2);

               pLyricEventsV2->m_msaNotesDuration.Diff(
               ms2DNoteOffMillis[i],
               ms2DNoteOnMillis[i]);

               imedia_time time3(0);
               imedia_time time4(0);

               pLyricEventsV2->m_msaNotesPosition.CopySorted(
               ms2DNoteOnMillis[i],
               time3,
               time4);

               imedia_time time5(0x7fffffff);

               pLyricEventsV2->m_msaTokensDuration.ElementDiff(
               ms2DTokensMillis[i],
               time5);

            }


            for(i = 0; i < tka2DTokensTicks.get_size(); i++)
            {
               pLyricEventsV1 = new ::ikaraoke::lyric_events_v1();
               pLyricEventsV1->m_iType = ikaraoke::EventAdvanceShow;
               pLyricEventsV1->m_iOrder = i;
               //staticdata.m_eventsTracksForPositionCB.add(pLyricEventsV1);
               file.TimeToPosition(
               pLyricEventsV1->m_tkaTokensPosition,
               ms2DTokensMillis[i],
               -1000);
               //lyric_track * pLyricTrk = file.GetTracks().CreateLyricTrack();
               //pLyricTrk->Prepare(*pLyricEventsV1);
            }


            for(i = 0; i < tka2DTokensTicks.get_size(); i++)
            {
               pLyricEventsV2 = (::ikaraoke::lyric_events_v2 *) lyricEventsForScoring.get_at(i);
               staticdata.m_eventsTracksForScoring.add(pLyricEventsV2);
               file.TimeToPosition(
               pLyricEventsV2->m_tkaTokensPosition,
               ms2DTokensMillis[i],
               0);
               file.TimeToPosition(
               pLyricEventsV2->m_tkaNotesPosition,
               ms2DNoteOnMillis[i],
               0);

               imedia_time time1(-100);
               imedia_time time2(0);

               pLyricEventsV2->m_msaTokensPosition.CopySorted(
               ms2DTokensMillis[i],
               time1,
               time2);

               pLyricEventsV2->m_msaNotesDuration.Diff(
               ms2DNoteOffMillis[i],
               ms2DNoteOnMillis[i]);

               imedia_time time3(-100);
               imedia_time time4(0);

               pLyricEventsV2->m_msaNotesPosition.CopySorted(
               ms2DNoteOnMillis[i],
               time3,
               time4);

               imedia_time time5(0x7fffffff);

               pLyricEventsV2->m_msaTokensDuration.ElementDiff(
               ms2DTokensMillis[i],
               time5);

               pLyricEventsV2->PrepareForScoring(this);
            }







            for(i = 0; i < tka2DTokensTicks.get_size(); i++)
            {
               pLyricEventsV2 = (::ikaraoke::lyric_events_v2 *) lyricEventsForPositionCB.get_at(i);
               staticdata.m_eventsTracksForPositionCB.add(pLyricEventsV2);

               staticdata.m_eventstracksV002.add(pLyricEventsV2);

               file.TimeToPosition(
               pLyricEventsV2->m_tkaTokensPosition,
               ms2DTokensMillis[i],
               -100);

               file.TimeToPosition(
               pLyricEventsV2->m_tkaNotesPosition,
               ms2DNoteOnMillis[i],
               -100);

               imedia_time time1(-100);
               imedia_time time2(0);

               pLyricEventsV2->m_msaTokensPosition.CopySorted(
               ms2DTokensMillis[i],
               time1,
               time2);

               pLyricEventsV2->m_msaNotesDuration.Diff(
               ms2DNoteOffMillis[i],
               ms2DNoteOnMillis[i]);

               /*
               pLyricEventsV2->m_msaNotesDuration.Diff(
               ms2DNoteOffMillis[i],
               ms2DNoteOnMillis[i]);
               */


               imedia_time time3(-100);
               imedia_time time4(0);

               pLyricEventsV2->m_msaNotesPosition.CopySorted(
               ms2DNoteOnMillis[i],
               time3,
               time4);

               imedia_time time5(0x7fffffff);

               pLyricEventsV2->m_msaTokensDuration.ElementDiff(
               ms2DTokensMillis[i],
               time5);

               pLyricEventsV2->PrepareForLyricsDisplay(this);
               //lyric_track * pLyricTrk = file.GetTracks().CreateLyricTrack();
               //pLyricTrk->Prepare(*pLyricEventsV2);
            }










            for(i = 0; i < tka2DTokensTicks.get_size(); i++)
            {
               pLyricEventsV2 = (::ikaraoke::lyric_events_v2 *) lyricEventsForBouncingBall.get_at(i);
               staticdata.m_eventsTracksForBouncingBall.add(pLyricEventsV2);

               file.TimeToPosition(
               pLyricEventsV2->m_tkaTokensPosition,
               ms2DTokensMillis[i],
               -100);

               file.TimeToPosition(
               pLyricEventsV2->m_tkaNotesPosition,
               ms2DNoteOnMillis[i],
               -100);

               imedia_time time1(-100);
               imedia_time time2(0);

               pLyricEventsV2->m_msaTokensPosition.CopySorted(
               ms2DTokensMillis[i],
               time1,
               time2);

               pLyricEventsV2->m_msaNotesDuration.Diff(
               ms2DEndMillis[i],
               ms2DBegMillis[i]);

               /*
               pLyricEventsV2->m_msaNotesDuration.Diff(
               ms2DNoteOffMillis[i],
               ms2DNoteOnMillis[i]);
               */

               imedia_time time3(-100);
               imedia_time time4(0);

               pLyricEventsV2->m_msaNotesPosition.CopySorted(
               ms2DNoteOnMillis[i],
               time3,
               time4);

               imedia_time time5(0x7fffffff);

               pLyricEventsV2->m_msaTokensDuration.ElementDiff(
               ms2DTokensMillis[i],
               time5);

               pLyricEventsV2->PrepareForBouncingBall(this);
            }

         }

         void sequence::Prepare(i32 iTrack, ::ikaraoke::data & data)
         {

            ::music::midi::mmsystem::buffer & file = *this->file();

            ::music::midi::tracks & tracks = file.GetTracks();

            string2a & str2a = data.GetStaticData().m_str2aRawTokens;

            imedia_position_2darray position2a;

            int2a ia2TokenLine;


            ia2TokenLine.add_new();

            tracks.WorkSeekBegin();
            tracks.WorkGetEmptyXFTokens(
            iTrack,
            str2a,
            position2a,
            nullptr);

            Prepare(
            str2a,
            position2a,
            iTrack,
            ia2TokenLine,
            data);

         }

         void sequence::Prepare(::ikaraoke::data & data)
         {
            ::music::midi::mmsystem::buffer & file = *this->file();
            ::music::midi::tracks & tracks = file.GetTracks();
            string2a & str2a = data.GetStaticData().m_str2aRawTokens;
            imedia_position_2darray position2a;
            int2a i2aTokenLine;

            ::music::xf::info_headers xfihs;
            get_file()->GetTracks().GetXFInfoHeaders(&xfihs);

            ::ikaraoke::static_data & staticdata = data.GetStaticData();
            string str;

            // add Title
            staticdata.m_straTitleFormat.add("%0");
            staticdata.m_str2aTitle.set_app(get_object());
            staticdata.m_str2aTitle.add_new();
            staticdata.m_str2aTitle[0].add(xfihs.m_strSongName);

            if(xfihs.m_xfInfoHeader.m_straComposer.get_size() > 0)
            {
               // add Performer
               staticdata.m_straTitleFormat.add("Performer: %0");
               xfihs.m_xfInfoHeader.m_straPerformer.get_format_string(str, ", ");
               staticdata.m_str2aTitle.add_new();
               staticdata.m_str2aTitle[1].add(str);

               // add Composer
               staticdata.m_straTitleFormat.add("Composer: %0");
               xfihs.m_xfInfoHeader.m_straComposer.get_format_string(str, ", ");
               staticdata.m_str2aTitle.add_new();
               staticdata.m_str2aTitle[1].add(str);


               //      staticdata.m_straPerformer = xfihs.m_xfInfoHeader.m_straPerformer;
               //    staticdata.m_straArtist = xfihs.m_xfInfoHeader.m_straPerformer;
            }

            staticdata.m_dwDefaultCodePage = 1252; // Latin (Default of All Default Code Pages)

            if(xfihs.m_xfaInfoHeaderLS.get_count())
            {
               staticdata.m_dwDefaultCodePage = ::music::xf::SymbolCharCodeToCodePage(xfihs.m_xfaInfoHeaderLS[0].m_strLanguage);
            }

            tracks.WorkSeekBegin();
            //tracks.WorkGetXFTokens(staticdata.m_dwDefaultCodePage, str2a, position2a, i2aTokenLine, nullptr);
            tracks.WorkGetXFTokens((u32) -1, str2a, position2a, i2aTokenLine, nullptr, false);

            Prepare(
            str2a,
            position2a,
            -1,
            i2aTokenLine,
            data);

            tracks.WorkSeekBegin();
            tracks.WorkGetLongestXFLyrics(staticdata.m_strLyrics, false);
            tracks.WorkGetLongestXFLyrics(staticdata.m_strLyricsEx1, true);



         }


         void sequence::GetPositionLength(imedia_time &position)
         {
            position = m_tkLength;
         }

         void sequence::buffer::Initialize(i32 iSize, uptr dwUser)
         {
            m_storage.allocate(iSize);
            m_midihdr.lpData           = (char *) m_storage.get_data();
            m_midihdr.dwBufferLength   = (u32) m_storage.get_size();
            m_midihdr.dwUser           = dwUser;
            m_bPrepared                = false;

         }

         void sequence::buffer_array::Initialize(i32 iCount, i32 iSize, uptr dwUser)
         {
            set_size(iCount);

            i32 i;

            /*   for(i32 i = 0; i < this->get_size() - 1; i++)
            {
            this->element_at(i).SetNextMidiHdr(this->element_at(i + 1).GetMidiHdr());
            }

            if(this->get_size() > 1)
            {
            this->element_at(get_upper_bound()).SetNextMidiHdr(this->element_at(0).GetMidiHdr());
            }
            else
            {
            this->element_at(0).SetNextMidiHdr(nullptr);
            }*/

            for(i = 0; i < this->get_size(); i++)
            {
               this->element_at(i).Initialize(iSize, dwUser);
            }
         }

         void sequence::buffer_array::Reset()
         {
            for(i32 i = 0; i < this->get_size(); i++)
            {
               this->element_at(i).Reset();
            }
         }

         void sequence::buffer::Reset()
         {
            m_midihdr.dwBytesRecorded  = 0;
            m_midihdr.dwFlags          = 0;
         }

         bool sequence::buffer::IsPrepared()
         {
            return m_bPrepared;
         }


         ::estatus     sequence::buffer::midiOutPrepareHeader(HMIDIOUT hmidiout)
         {

            ::estatus     mmr = ::success;

            if(hmidiout == nullptr)
               return mmr;

            if(m_bPrepared)
               return mmr;

            mmr = ::midiOutPrepareHeader(hmidiout, &m_midihdr, sizeof(m_midihdr));

            if(mmr == ::success)
            {

               m_bPrepared = true;

            }

            return mmr;

         }


         ::estatus     sequence::buffer::midiOutUnprepareHeader(HMIDIOUT hmidiout)
         {

            ::estatus     mmr = ::success;

            if(hmidiout == nullptr)
               return mmr;

            if(!m_bPrepared)
               return mmr;

            mmr = ::midiOutUnprepareHeader(hmidiout, &m_midihdr, sizeof(m_midihdr));

            if(mmr == ::success)
            {

               m_bPrepared = false;

            }

            return mmr;

         }

         ::estatus     sequence::buffer_array::midiOutUnprepareHeader(HMIDIOUT hmidiout)
         {
            ::estatus     mmr = ::success;

            for (i32 i = 0; i < this->get_size(); i++)
            {
               ::estatus     mmrBuffer = this->element_at(i).midiOutUnprepareHeader(hmidiout);
               if(mmrBuffer != ::success)
               {
                  mmr = mmrBuffer;
               }
            }
            return mmr;
         }

         ::estatus     sequence::buffer_array::midiOutPrepareHeader(HMIDIOUT hmidiout)
         {
            ::estatus     estatus = ::success;
            for(i32 i = 0; i < this->get_size(); i++)
            {
               estatus = this->element_at(i).midiOutPrepareHeader(
                         hmidiout);
               if(estatus != ::success)
               {
                  for(; i >= 0; i--)
                  {
                     this->element_at(i).midiOutUnprepareHeader(hmidiout);
                  }
                  return estatus;
               }
            }
            return estatus;
         }

         void sequence::buffer::SetNextMidiHdr(LPMIDIHDR lpNext)
         {
            m_midihdr.lpNext = lpNext;
         }


         ::estatus     sequence::buffer::midiStreamOut(HMIDISTRM hmidiout)
         {
            ASSERT(hmidiout != nullptr);
            return ::midiStreamOut(hmidiout, &m_midihdr, sizeof(m_midihdr));
         }

         ::estatus     sequence::buffer_array::midiStreamOut(HMIDISTRM hmidiout)
         {
            ::estatus     estatus = ::success;
            for(i32 i = 0; i < this->get_size(); i++)
            {
               estatus = this->element_at(i).midiStreamOut(
                         hmidiout);
               if(estatus != ::success)
               {
                  //         for(; i >= 0; i--)
                  //       {
                  //        this->element_at(i).midiOutUnprepareHeader(hmidiout);
                  //   }
                  return estatus;
               }
            }
            return estatus;
         }





         void sequence::MuteAll(bool bMute, i32 iExcludeTrack)
         {
            bool bPlay = IsPlaying();
            imedia_time ticks = 0;
            if(bPlay)
            {
               ticks = GetPositionTicks();
               Stop();
            }
            get_file()->MuteAll(bMute, iExcludeTrack);
            if(bPlay)
            {
               m_pthread->PrerollAndWait(ticks);
               Start();
            }
         }

         void sequence::MuteTrack(i32 iIndex, bool bMute)
         {
            bool bPlay = IsPlaying();
            imedia_time ticks = 0;
            if(bPlay)
            {
               ticks = GetPositionTicks();
               Stop();
            }
            get_file()->MuteTrack(iIndex, bMute);
            if(bPlay)
            {
               m_pthread->PrerollAndWait(ticks);
               Start();
            }
         }

         imedia_time sequence::GetQuarterNote()
         {
            return get_file()->m_pFileHeader->GetQuarterNoteTicks();
         }


         i32 sequence::GetDefaultCodePage()
         {
            return 1252;
         }


         bool sequence::IsSettingPosition()
         {
            return m_flags.has(::music::midi::sequence::FlagSettingPos);
         }


         void sequence::SetSettingPositionFlag(bool bSet)
         {
            if(bSet)
               m_flags.add(::music::midi::sequence::FlagSettingPos);
            else
               m_flags.remove(::music::midi::sequence::FlagSettingPos);
         }

         u32 sequence::GetPreviousState()
         {
            return m_uiPreviousState;
         }

         u32 sequence::GetState()
         {
            return m_uiState;
         }

         ::music::midi::sequence::event * sequence::create_new_event(::music::midi::sequence::e_event eevent, LPMIDIHDR lpmidihdr)
         {

            ASSERT(this != nullptr);

            event * pevent          = new event();

            pevent->m_eevent        = eevent;
            pevent->m_psequence     = this;
            pevent->m_lpmh          = lpmidihdr;

            return pevent;

         }


      } // namespace mmsystem


   } // namespace midi


} // namespace music









