#include "framework.h"


namespace music
{
   
   
   namespace midi
   {
      
      
      namespace core_midi
      {
         

         sequence::sequence(::object * pobject) :
            ::object(pobject),
            ::music::midi::object(pobject),
            ::ikaraoke::karaoke(pobject),
            ::music::midi::sequence(pobject)
         {

            defer_create_mutex();

            m_buffera.Initialize(16, 4 * 1024, 0);

            m_midicallbackdata.m_psequence = this;

         }
         

         sequence::~sequence()
         {

            close_file();

         }



         //////////////////////////////////////////////////////////////////////////////
         //
         //
         //    seqStart
         //    Starts playback at the current position.
         //
         //
         //    pSeq                      - The sequencer instance.
         //
         //
         //    Returns
         //    - success: If the operation is successful.
         //
         //    - error_unsupported_function: If the sequencer instance is not
         //       stopped.
         //
         //    - MCIERR_DEVICE_NOT_READY: If the underlying MIDI device could
         //       not be opened or fails any call.
         //
         //    The sequencer must be prerolled before seqStart may be called.
         //
         //    Just feed everything in the ready queue to the device.
         //
         //
         ////////////////////////////////////////////////////////////////////////////
         ::estatus     sequence::Start()
         {

            single_lock sl(mutex(), TRUE);

            if (sequence::state_pre_rolled != get_state())
            {

               TRACE( "seqStart(): State is wrong! [%u]", get_state());

               return error_unsupported_function;

            }

            m_evMmsgDone.ResetEvent();

            ::estatus     estatus = ::success;

            sl.unlock();

            if(estatus == ::success)
            {

               thread()->PostMidiSequenceEvent(this, sequence::EventMidiPlaybackStart);

            }

            return estatus;

         }
         
         
         void sequence::OnEvent(::music::midi::sequence::event * pevent)
         {

            ::music::midi::sequence::OnEvent(pevent);
            
         }


         __pointer(::music::midi::message_out) sequence::get_message_out()
         {
            
            return ::music::midi::sequence::get_message_out();

         }


         __pointer(play_thread) sequence::on_midi_sequence_start()
         {
            
            auto iDevice = m_pthread->m_pplayer->get_midi_out_device().i64();
            
            __pointer(department) pdepartment = Application.midi();
            
            __pointer(play_thread) pthread;
            
            if(iDevice >= 0 && iDevice < pdepartment->m_messageouta.get_count())
            {
               
               pthread = __new(::music::midi::sequencer(this, pdepartment->m_messageouta[iDevice]));
               
            }
            else
            {
               
               auto iPort = iDevice - pdepartment->m_pmidiRealTime->m_iPortStart;
               
               if(iPort >= 0 && iPort < pdepartment->m_pmidiRealTime->m_cPortCount)
               {
               
                  pthread = __pointer(music_midi_real_time_new_play_thread(this, iPort));
                  
               }
               else
               {
                  
                  iPort = iPort - pdepartment->m_pmidiCoreMidi->m_iPortStart;
                  
                  if(iPort >= 0 && iPort < pdepartment->m_pmidiCoreMidi->m_cPortCount)
                  {
                     
                     pthread = __pointer(music_midi_core_midi_new_play_thread(this, iPort));
                     
                  }
                     
               }
               
            }

            return pthread;
            

            //return ::error_internal;

   //         single_lock sl(mutex(), TRUE);
   //
   //         if(get_state() != state_pre_rolled)
   //            return error_unsupported_function;
   //
   //         m_posPlay = 0;
   //         // CFStringRef nameRef;
   //         // MIDIEndpointRef portRef;
   //         // char name[128];
   //
   //         int portNumber = 0;
   //         std::string stringName;
   //         CFRunLoopRunInMode( kCFRunLoopDefaultMode, 0, false );
   //         if ( portNumber >= MIDIGetNumberOfDestinations() )
   //{
   //         }
   //
   //         //char name[2048];
   ////         portRef = MIDIGetDestination( 0 );
   ////         nameRef = ConnectedEndpointName(portRef);
   ////         CFStringGetCString( nameRef, name, sizeof(name), CFStringGetSystemEncoding());
   ////         CFRelease( nameRef );
   ////
   ////         stringName = name;
   //
   //         //m_pcmo = new CoreMidiOutput(stringName);
   //
   //         //m_bStart = false;
   //
   ////         m_pau = new AudioUnitOutput(nullptr);
   ////
   ////         //m_pau->note_on(128, 128, 0);
   ////
   ////         OSStatus result;
   ////
   //////         m_cl = nullptr;
   //////
   //////
   //////         result = CAClockNew(0, &m_cl);
   //////
   //////
   //////         if(result != noErr)
   //////         {
   //////
   //////            return translate_os_status(result);
   //////
   //////         }
   //////         // Create a client
   ////         //MIDIClientRef virtualMidi;
   ////         result = MIDIClientCreate(CFSTR("Virtual Client"),
   ////                                   MyMIDINotifyProc,
   ////                                   nullptr,
   ////                                   &m_virtualMidi);
   ////
   ////
   ////         if(result != noErr)
   ////         {
   ////
   ////            return translate_os_status(result);
   ////
   ////         }
   ////
   ////         // Create an endpoint
   ////         //MIDIEndpointRef virtualEndpoint;
   ////         result = MIDIDestinationCreate(m_virtualMidi, CFSTR("Virtual Destination"), MyMIDIReadProc, this, &m_virtualEndpoint);
   ////
   ////
   ////         if(result != noErr)
   ////         {
   ////
   ////            return translate_os_status(result);
   ////
   ////         }
   ////         m_sequence = nullptr;
   ////
   ////         OSStatus os = LoadSMF((const char *)m_pfile->get_data(),
   ////                               (int) m_pfile->get_size(),
   ////                               m_sequence, 0);
   ////
   ////         if(os != noErr)
   ////         {
   ////
   ////            return translate_os_status(os);
   ////
   ////         }
   ////
   ////         MusicSequenceType outType;
   ////
   ////         MusicSequenceGetSequenceType ( m_sequence, &outType );
   ////
   ////         // ************* Set the endpoint of the sequence to be our virtual endpoint
   ////         MusicSequenceSetMIDIEndpoint(m_sequence, m_virtualEndpoint);
   ////
   ////         // Create a new music player
   ////         // Initialise the music player
   ////         os = NewMusicPlayer(&m_player);
   ////         if(os != noErr)
   ////         {
   ////
   ////            return translate_os_status(os);
   ////
   ////         }
   ////
   ////         // Load the sequence into the music player
   ////         os = MusicPlayerSetSequence(m_player, m_sequence);
   ////         if(os != noErr)
   ////         {
   ////
   ////            return translate_os_status(os);
   ////
   ////         }
   ////         m_bStart = false;
   ////         // Called to do some MusicPlayer setup. This just
   ////         // reduces latency when MusicPlayerStart is called
   ////         os = MusicPlayerPreroll(m_player);
   ////         if(os != noErr)
   ////         {
   ////
   ////            return translate_os_status(os);
   ////
   ////         }
   ////
   ////         // Starts the music playing
   ////         os = MusicPlayerStart(m_player);
   ////
   ////         if(os != noErr)
   ////         {
   ////
   ////            return translate_os_status(os);
   ////
   ////         }
   ////
   ////         set_status(state_playing);
   ////
   ////
   ////         m_uiStart = ::get_tick();
   ////
   ////         return ::success;
   //
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
          *   ::music::error_unsupported_function If the sequencer instance is not
          *     playing.
          *
          * The sequencer must be playing before seqPause may be called.
          * Pausing the sequencer will cause all currently on notes to be turned
          * off. This may cause playback to be slightly inaccurate on restart
          * due to missing notes.
          *
          ***************************************************************************/
   //      ::estatus     sequence::Pause()
   //      {
   //         single_lock sl(mutex(), TRUE);
   //
   //         //    assert(nullptr != pSeq);
   //
   //         if (state_playing != get_state())
   //            return error_unsupported_function;
   //
   //         set_status(state_paused);
   //
   //         //::estatus     estatus = ::success;
   //         //    single_lock slStream(&m_csStream, false);
   //         //  slStream.lock();
   ////         if(m_pseq != nullptr)
   //         // {
   //         //          seq_stop_timer(m_pseq);
   //         // }
   //         //slStream.unlock();
   //
   //         SetLevelMeter(0);
   //
   //         return ::success;
   //      }

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
          *    ::music::error_unsupported_function If the sequencer instance is not
          *     paused.
          *
          * The sequencer must be paused before seqRestart may be called.
          *
          ***************************************************************************/
   //      ::estatus     sequence::Restart()
   //      {
   //         //    assert(nullptr != pSeq);
   //
   //         single_lock sl(mutex(), TRUE);
   //
   //         if (state_paused != get_state())
   //            return error_unsupported_function;
   //
   //         set_status(state_playing);
   //         m_evMmsgDone.ResetEvent();
   //
   //         //    ::estatus     estatus = 0;
   //         //    single_lock slStream(&m_csStream, false);
   //         //  slStream.lock();
   ////         if(m_pseq != nullptr)
   //         {
   //            //          seq_start_timer(m_pseq);
   //         }
   //         //slStream.unlock();
   //         return ::success;
   //      }

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
          *   ::music::error_unsupported_function If the sequencer instance is not
          *     paused or playing.
          *
          * The sequencer must be paused or playing before seqStop may be called.
          *
          ***************************************************************************/
         ::estatus     sequence::Stop()
         {

            single_lock sl(mutex(), TRUE);

            if(get_state() == state_stopping)
               return ::success;

            // Automatic success if we're already stopped
            if (get_state() != state_playing
                  && get_state() != state_paused)
            {
               m_flags.remove(sequence::FlagWaiting);
               GetPlayerLink().OnFinishCommand(command_stop);
               return ::success;
            }

            set_state(state_stopping);
            m_flags.add(sequence::FlagWaiting);

            m_eventMidiPlaybackEnd.ResetEvent();


   //         if(m_pseq != nullptr)
            //       {
            //        seq_stop_timer(m_pseq);
            //      if(::success != m_estatusLastError)
            //    {
            //     TRACE( "sequence::Stop() -> midiOutStop() returned %lu in seqStop()!\n", (u32)m_estatusLastError);
            //   m_flags.remove(FlagWaiting);
            // return error_not_ready;
            //}
            // }

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
          *   MCIERR_DEVICE_NOT_READY If the underlying device fails to report
          *     the position.
          *
          *   ::music::error_unsupported_function If the sequencer instance is not
          *     paused or playing.
          *
          * The sequencer must be paused, playing or prerolled before seqTime
          * may be called.
          *
          ***************************************************************************/
         ::estatus     sequence::get_ticks(imedia_position &  pTicks)
         {

            sync_lock sl(mutex());

            //::estatus                    mmr;

            if (sequence::state_playing != get_state() &&
                  sequence::state_paused != get_state() &&
                  sequence::state_pre_rolling != get_state() &&
                  sequence::state_pre_rolled != get_state() &&
                  sequence::state_opened != get_state() &&
                  sequence::state_stopping != get_state())
            {

               TRACE( "seqTime(): State wrong! [is %u]", get_state());

               return error_unsupported_function;

            }


            imedia_time t = 0;

            if(get_millis(t) == ::success)
            {

               pTicks = MillisecsToTicks(t);

               return ::success;

            }

            pTicks = 0;

            if (state_opened != get_state())
            {

               pTicks = m_tkBase;

            }

            return ::success;

         }


         ::estatus     sequence::get_millis(imedia_time & time)
         {

            single_lock sl(mutex());

            if (state_playing != get_state() &&
                  state_paused != get_state() &&
                  state_pre_rolling != get_state() &&
                  state_pre_rolled != get_state() &&
                  state_opened != get_state() &&
                  state_stopping != get_state())
            {

               TRACE( "seqTime(): State wrong! [is %u]", get_state());

               return error_unsupported_function;

            }

            if(m_psequencer != nullptr)
            {

               time = m_psequencer->get_millis();

               return ::success;

            }

   //         if(m_player != nullptr)
   //         {
   //
   //            Boolean bPlaying = false;
   //
   //            OSStatus os = MusicPlayerIsPlaying(m_player, &bPlaying);
   //
   //            if(os == noErr && bPlaying)
   //            {
   //
   //               MusicTimeStamp now = 0;
   //
   //               os = MusicPlayerGetTime (m_player, &now);
   //
   //               if(os == noErr)
   //               {
   //
   //                  Float64 f;
   //
   //                  os = MusicSequenceGetSecondsForBeats(m_sequence, now,  &f);
   //
   //                  if(os == noErr)
   //                  {
   //
   //                     UInt64 outHostTime = 0;
   //
   //                     MusicPlayerGetHostTimeForBeats ( m_player, now, &outHostTime );
   //
   //                     //m_posPlay = time = now * 1000;
   //
   //                     ///m_posPlay =  (outHostTime - m_uiStart) / (1000.0 * 1000.0);
   //
   //                     //m_posPlay = m_uiStart.elapsed();
   //
   //                     //time = m_posPlay;
   //
   //                     time = f * 1000.0;
   //
   //                     // time = outHostTime;
   //
   //                     return ::success;
   //
   //                  }
   //
   //               }
   //
   //            }
   //
   //         }

            time = 0;

            if (state_opened != get_state())
            {

               time = (iptr) TicksToMillisecs(m_tkBase);

               if (state_pre_rolled != get_state())
               {

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
         imedia_position sequence::MillisecsToTicks(imedia_time msOffset)
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
         imedia_time sequence::TicksToMillisecs(imedia_position tkOffset)
         {
            return file()->TicksToMillisecs(tkOffset);
         }


         void sequence::OnPositionCB(LPMIDIHDR lpmidihdr)
         {
            /*ASSERT(lpmidihdr != nullptr);
             LPBYTE lpbData = (LPBYTE) (lpmidihdr->lpData + lpmidihdr->dwOffset);
             MIDIEVENT * lpme = (MIDIEVENT *) lpbData;
             file::midi_stream_event_header * pheader = (file::midi_stream_event_header *) &lpme->dwParms[0];
             lpbData = (LPBYTE) pheader;
             LPDWORD lpdwParam;

             i32 iSize = pheader->m_dwLength;
             switch(pheader->m_dwType)
             {
             case 0:
             {
             array < ::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1 &> * plyriceventa = nullptr;
             array < ::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1 &> lyriceventa;
             for(i32 i = sizeof(file::midi_stream_event_header); i < iSize;)
             {
             pheader = (file::midi_stream_event_header *) &lpbData[i];
             lpdwParam = (LPDWORD) &lpbData[i + sizeof(file::midi_stream_event_header)];
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
             // x2x                  CArchive ar(&memFile, CArchive::load);
             lyriceventa.Serialize(ar);
             plyriceventa->append(lyriceventa); //
            //          }
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
             i += pheader->m_dwLength + sizeof(file::midi_stream_event_header);
             }
             //         if(plyriceventa != nullptr)
             {
             ::PostMessage(m_midicallbackdata.oswindow, WM_APP + 3388, 3388, (LPARAM) plyriceventa);
             }//
            //}
             break;
             case EVENT_ID_PAD:
             break;
             default:
             ASSERT(FALSE);
             break;
             }*/

         }

         //void CALLBACK sequence::MidiOutProc(HMIDIOUT hmo, u32 wMsg, u32 dwInstance, u32 dwParam1, u32 dwParam2)
         //{

         /*UNREFERENCED_PARAMETER(hmo);
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
          }*/

         //}


         bool sequence::IsPlaying()
         {
            return get_state() == state_playing ||
                   get_state() == state_stopping;
         }






   //      u32 sequence::set_status(u32 uiState)
   //      {
   //         m_uiPreviousState = m_uiState;
   //         m_uiState = uiState;
   //         return m_uiPreviousState;
   //      }
   //
   //      void sequence::SetSpecialModeV001Flag(bool bSet)
   //      {
   //         if(m_flags.has(flag_operation))
   //            m_flags.add(flag_was_operation);
   //         else
   //            m_flags.remove(flag_was_operation);
   //
   //         if(bSet)
   //            m_flags.add(flag_operation);
   //         else
   //            m_flags.remove(flag_operation);
   //      }

   //      void sequence::set_operation(e_operation eoperation)
   //      {
   //         m_uiPreSpecialModeV001State = m_uiState;
   //         SetSpecialModeV001Flag();
   //         m_eoperation = eoperation;
   //      }

   //      bool sequence::IsInSpecialModeV001()
   //      {
   //         return m_flags.has(flag_operation);
   //      }
   //
   //      bool sequence::WasInSpecialModeV001()
   //      {
   //         return m_flags.has(flag_was_operation);
   //      }


   //      void sequence::GetMidiDoneData(::music::midi::LPMIDIDONEDATA lpmdd)
   //      {
   //         lpmdd->m_flags = m_flags;
   //         lpmdd->m_uiSeqPreviousState = m_uiPreviousState;
   //         lpmdd->m_uiSeqState = m_uiState;
   //      }

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
             void sequence::SetKeyShift(i32 iShift)
             {*/
            bool bPlay = IsPlaying();
            imedia_position ticks = 0;
            if(bPlay)
            {

               ticks = get_position_ticks();

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


         double sequence::GetTempoShift()
         {

            return file()->GetTempoShift();

         }


         i32 sequence::SetTempoShift(i32 iTempoShift)
         {

            //midiStreamPause(m_hstream);
            if(::failed(file()->SetTempoShift(iTempoShift)))
               return false;
            //midiStreamRestart(m_hstream);
            return true;
         }


   //      bool sequence::SetMidiOutDevice(u32 uiDevice)
   //      {
   //
   //         if(uiDevice == ::music::midi::device_default)
   //         {
   //
   //            //m_uiDeviceID = MIDI_MAPPER;
   //
   //         }
   //         else
   //         {
   //
   //            m_uiDeviceID = uiDevice;
   //
   //         }
   //
   //         return true;
   //      }

   //      ::estatus     sequence::CloseStream()
   //      {
   //         single_lock sl(mutex(), TRUE);
   //         if(IsPlaying())
   //         {
   //            Stop();
   //         }
   //
   //         /* If we were prerolled, need to clean up -- have an open MIDI handle
   //          ** and buffers in the ready queue
   //          */
   //
   //         //         m_buffera.midiOutUnprepareHeader((HMIDIOUT) m_hstream);
   //
   ////         if (m_pseq != nullptr)
   //         //       {
   //         //        seq_free_context(m_pseq);
   //         //      m_pseq = nullptr;
   //         // }
   //
   //         set_status(state_opened);
   //
   //         return ::success;
   //      }

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
            single_lock sl(mutex(), TRUE);
            //   LPMIDIHDR lpmh = pevent->m_lpmh;
            //   midi_callback_data * lpData = &m_midicallbackdata;
            //::estatus     estatus;


            //         if(0 == m_uBuffersInMMSYSTEM)
            {
               TRACE( "seqBufferDone: normal sequencer shutdown.");

               /* Totally done! Free device and notify.
                */
   //            if(m_pseq != nullptr)
               {
                  /*if((estatus = m_buffera.midiOutUnprepareHeader((HMIDIOUT) m_hstream))
                   != ::success)
                   {
                   TRACE( "midiOutUnprepareHeader failed in seqBufferDone! (%lu)", (u32)estatus);
                  //              }*/
                  //           seq_free_context(m_pseq);
                  //         m_pseq = nullptr;
               }

               m_estatusLastError = ::success;
               m_flags.remove(FlagWaiting);

               m_evMmsgDone.SetEvent();
            }
         }

   //         void sequence::OnEvent(::music::midi::sequence::event * pevent)
   //      {
   //         ::music::midi::sequence::OnEvent(pevent);
   //         switch(pevent->m_eevent)
   //         {
   //
   ////            case EventStopped:
   ////            {
   ////               OnMidiPlaybackEnd(pevent);
   ////               set_status(state_opened);
   ////            }
   ////               break;
   //         case EventMidiPlaybackEnd:
   //         {
   //            OnMidiPlaybackEnd(pevent);
   //            set_status(state_opened);
   //         }
   //         break;
   //         default:
   //            break;
   //         }
   //      }

         /*imedia_position sequence::GetPositionTicks()
          {
          single_lock sl(mutex());
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
          }*/


         bool sequence::IsChangingTempo()
         {
            return m_flags.has(sequence::FlagTempoChange);
         }
         void sequence::SetTempoChangeFlag(bool bSet)
         {
            if(bSet)
               m_flags.add(sequence::FlagTempoChange);
            else
               m_flags.remove(sequence::FlagTempoChange);
         }


         bool sequence::IsNull()
         {

            if(is_null(this))
            {

               return true;

            }

            return false;

         }


         imedia_position sequence::TimeToPosition(imedia_time millis)
         {
            return imedia_position(MillisecsToTicks((iptr) millis));
         }

         imedia_time sequence::PositionToTime(imedia_position tk)
         {
            return imedia_time(TicksToMillisecs((imedia_position) (iptr) tk));
         }


         bool sequence::IsOpened()
         {

            return get_state() != state_no_file;

         }


         void sequence::buffer::Initialize(i32 iSize, u32 dwUser)
         {

            m_storage.allocate(iSize);
            m_midihdr.lpData           = (char *) m_storage.get_data();
            m_midihdr.dwBufferLength   = (u32) m_storage.get_size();
            m_midihdr.dwUser           = dwUser;
            m_bPrepared                = false;

         }


         void sequence::buffer_array::Initialize(i32 iCount, i32 iSize, u32 dwUser)
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


         /*      ::estatus     sequence::buffer::midiOutPrepareHeader(HMIDIOUT hmidiout)
          {
          ::estatus     mmr = 0;
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
          ::estatus     mmr = 0;
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
          }*/

         void sequence::buffer::SetNextMidiHdr(LPMIDIHDR lpNext)
         {
            m_midihdr.lpNext = lpNext;
         }


   //      ::estatus     sequence::buffer::midiStreamOut(seq_context_t * hmidiout)
         //    {
         /*         ASSERT(hmidiout != nullptr);
          return ::midiStreamOut(hmidiout, &m_midihdr, sizeof(m_midihdr));*/
         //     return ::success;
         //}

         //    ::estatus     sequence::buffer_array::midiStreamOut(seq_context_t * hmidiout)
         //  {
         /*
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
          return estatus;*/
         //   return ::success;
         // }


         void sequence::MuteAll(bool bMute, i32 iExcludeTrack)
         {

            bool bPlay = IsPlaying();

            imedia_position ticks = 0;

            if(bPlay)
            {

               ticks = get_position_ticks();

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

            imedia_position ticks = 0;

            if(bPlay)
            {

               ticks = get_position_ticks();

               Stop();

            }

            get_file()->MuteTrack(iIndex, bMute);

            if(bPlay)
            {

               m_pthread->PrerollAndWait(ticks);

               Start();

            }

         }


         imedia_position sequence::GetQuarterNote()
         {
            return get_file()->m_pFileHeader->GetQuarterNoteTicks();
         }


         i32 sequence::GetDefaultCodePage()
         {
            return 1252;
         }


         bool sequence::IsSettingPosition()
         {
            return m_flags.has(sequence::FlagSettingPos);
         }


         void sequence::SetSettingPositionFlag(bool bSet)
         {
            if(bSet)
               m_flags.add(sequence::FlagSettingPos);
            else
               m_flags.remove(sequence::FlagSettingPos);
         }


            __pointer(::music::midi::sequence::event) sequence::create_new_event(e_event eevent, LPMIDIHDR lpmidihdr)
         {

            ASSERT(::is_set(this));

            auto pevent           = __new(event());

            pevent->m_eevent        = eevent;
            pevent->m_psequence     = this;
            pevent->m_lpmh          = lpmidihdr;

            return pevent;

         }


         
         


         
         
      } // namespace core_midi


   } // namespace midi

      
} // namespace music



