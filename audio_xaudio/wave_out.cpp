#include "framework.h"
#include "aura/message.h"


namespace multimedia
{


   namespace audio_xaudio
   {


      out::out()
      {

         m_estate             = state_initial;
         m_pthreadCallback    = nullptr;

      }


      out::~out()
      {

      }


      void out::install_message_routing(::channel * pchannel)
      {

         ::wave::out::install_message_routing(pchannel);

      }


      ::estatus out::init_thread()
      {

         if (!::wave::out::init_thread())
         {

            return false;

         }

         set_thread_priority(::priority_time_critical);

         return true;

      }


      ::estatus     out::out_open_ex(thread * pthreadCallback, u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitsPerSample, ::wave::e_purpose epurpose)
      {

         single_lock sLock(mutex(), TRUE);

         if(m_pxaudio.is_set() && m_pvoice != nullptr && m_psourcevoice != nullptr && m_estate != state_initial)
            return ::success;

         m_iBuffer = 0;

         m_pthreadCallback = pthreadCallback;
         ::estatus     estatus;
         ASSERT(m_pxaudio.is_null());
         ASSERT(m_pvoice == nullptr);
         ASSERT(m_psourcevoice == nullptr);
         ASSERT(m_estate == state_initial);

         CoInitializeEx(nullptr,COINIT_MULTITHREADED);

         if(FAILED(XAudio2Create(&m_pxaudio,0,XAUDIO2_DEFAULT_PROCESSOR)))
         {

            return error_failed;

         }

#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/) && defined(_DEBUG)
         // To see the trace output, you need to view ETW logs for this application:
         //    Go to Control Panel, Administrative Tools, Event Viewer.
         //    View->Show Analytic and Debug Logs.
         //    Applications and Services Logs / Microsoft / Windows / XAudio2.
         //    Right click on Microsoft Windows XAudio2 debug logging, Properties, then Enable Logging, and hit OK
         XAUDIO2_DEBUG_CONFIGURATION debug = {0};
         debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
         debug.BreakMask = XAUDIO2_LOG_ERRORS;
         m_pxaudio->SetDebugConfiguration(&debug,0);
#endif


         HRESULT hr;

         if(FAILED(hr = m_pxaudio->CreateMasteringVoice(&m_pvoice,uiChannelCount, uiSamplesPerSec)))
         {
            return error_failed;
         }
         int iSampleRate = XAUDIO2_MIN_SAMPLE_RATE;
         estatus = ::success;
         m_pwaveformat->m_waveformat.wFormatTag = WAVE_FORMAT_PCM;
         m_pwaveformat->m_waveformat.nChannels = uiChannelCount;
         m_pwaveformat->m_waveformat.nSamplesPerSec = uiSamplesPerSec;
         m_pwaveformat->m_waveformat.wBitsPerSample = sizeof(::wave::WAVEBUFFERDATA) * 8 ;
         m_pwaveformat->m_waveformat.nBlockAlign = m_pwaveformat->m_waveformat.wBitsPerSample  * uiChannelCount / 8;
         m_pwaveformat->m_waveformat.nAvgBytesPerSec = m_pwaveformat->m_waveformat.nSamplesPerSec * m_pwaveformat->m_waveformat.nBlockAlign;
         //m_pwaveformat->cbSize = 0;
         __pointer(::wave::wave) audiowave = Audio.audiowave();

         //if(FAILED(hr = m_pxaudio->CreateSourceVoice(&m_psourcevoice,wave_format(),XAUDIO2_VOICE_NOSRC | XAUDIO2_VOICE_NOPITCH,1.0f,this)))
         if(FAILED(hr = m_pxaudio->CreateSourceVoice(&m_psourcevoice,wave_format(),0,1.0f,this)))
         {
            return error_failed;
         }

         if(estatus != ::success)
         {

            TRACE(status_message(estatus));

            return estatus;

         }
         ::count iBufferCount;
//Opened:

         ::count iBufferSampleCount = 4096;

         if(epurpose == ::wave::purpose_playback)
         {

            iBufferCount = 8;
            iBufferSampleCount = (1 << 9);

         }
         else if(epurpose == ::wave::purpose_playground)
         {

            iBufferCount = 2;
            iBufferSampleCount = (1 << 9);

         }
         else
         {

            iBufferCount = 4;
            iBufferSampleCount = (1 << 9);

         }

         int iAlign = 2048;

         auto uiBufferSize = iBufferSampleCount * m_pwaveformat->m_waveformat.nChannels * 2;

         uiBufferSize = max(uiBufferSize,2048);

         ASSERT((uiBufferSize % 2048) == 0);// Streaming size must be 2K aligned to use for async I/O

         iBufferSampleCount = uiBufferSize / (m_pwaveformat->m_waveformat.nChannels * 2);



         out_get_buffer()->PCMOutOpen(this, uiBufferSize, iBufferCount,iAlign, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(m_pwaveformat->m_waveformat.nChannels, iBufferCount, iBufferSampleCount);

         m_estate = state_opened;

         m_epurpose = epurpose;

         return ::success;

      }



      ::estatus     out::out_close()
      {

         single_lock sLock(mutex(), TRUE);

         if(m_estate == state_playing)
         {
            out_stop();
         }

         if(m_estate != state_opened)
            return ::success;

         ::estatus     estatus;

//         i32 i, iSize;
         //i32 iSize;

         auto iSize =  out_get_buffer()->GetBufferCount();

         //for(i = 0; i < iSize; i++)
         //{

         estatus = xaudio::translate(m_psourcevoice->Stop());


         //for(i = 0; i < iSize; i++)
         //{

         //   delete m_bufferptra[i];

         //}


         //m_psourcevoice->DestroyVoice();

         try
         {

            m_psourcevoice->DestroyVoice();

         }
         catch(...)
         {

         }

         //m_bufferptra.remove_all();

         m_psourcevoice = nullptr;


         try
         {


            if(m_pvoice != nullptr)
            {

               m_pvoice->DestroyVoice();

            }
         }
         catch (...)
         {

         }

         m_pvoice = nullptr;

         try
         {


            if(m_pxaudio.is_set())
            {

               m_pxaudio->StopEngine();

            }

         }
         catch (...)
         {

         }

         m_pxaudio.Release();

         //estatus = xaudio::translate(waveOutClose(m_hwaveout));

         //m_hwaveout = nullptr;

         ::wave::out::out_close();

         return ::success;

      }



      void out::out_filled(index iBuffer)
      {

         sync_lock sl(mutex());

         if(out_get_state() != state_playing)
         {

            TRACE("ERROR out::BufferReady while out_get_state() != state_playing");

            return;

         }

         ::wave::buffer * pwbuffer = out_get_buffer();

         ::wave::buffer::item * pbuffer = pwbuffer->get_buffer(iBuffer);

         ::estatus     estatus;

         XAUDIO2_BUFFER b;

         ·zero(b);

         b.pContext = pbuffer;
         b.AudioBytes = (::u32) (pwbuffer->m_uiBufferSize);
         b.pAudioData = (const byte *)pbuffer->m_pData;
         b.Flags = m_bEOS ? XAUDIO2_END_OF_STREAM : 0;

         //single_lock sLock(mutex(),TRUE);

#if 0

         char sz[256];

         ·zero(sz);

         if(memmem(b.pAudioData,pwbuffer->m_uiBufferSize,sz,sizeof(sz)))
         {

            output_debug_string("too much zeros in audio buffer\n");

         }

#endif

         if(m_millisLastBuffer.timeout(50_tick))
         {

            output_debug_string("too much delay for submitting audio buffer\n");

         }

         m_iBufferedCount++;

         estatus = xaudio::translate(m_psourcevoice->SubmitSourceBuffer(&b));

         VERIFY(::success == estatus);

         if(estatus != ::success)
         {

            m_iBufferedCount--;

         }

      }


      ::estatus     out::out_stop()
      {

         single_lock sLock(mutex(), TRUE);

         if(m_estate != state_playing && m_estate != state_paused)
            return error_failed;

         //m_pprebuffer->stop();

         m_estate = state_stopping;

         //// waveOutReset
         //// The waveOutReset function stops playback on the given
         //// waveform-audio_xaudio output device and resets the current position
         //// to zero. All pending playback buffers are marked as done and
         //// returned to the application.
         m_estatusWave = xaudio::translate(m_psourcevoice->Stop());

         if(m_estatusWave == ::success)
         {

            m_estate = state_opened;

         }

         return m_estatusWave;

      }


      ::estatus     out::out_pause()
      {

         single_lock sLock(mutex(), TRUE);

         ASSERT(m_estate == state_playing);

         if(m_estate != state_playing)
            return error_failed;

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_xaudio output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.

         m_estatusWave = xaudio::translate(m_psourcevoice->Stop());

         ASSERT(m_estatusWave == ::success);

         if(m_estatusWave == ::success)
         {
            m_estate = state_paused;
         }

         return m_estatusWave;

      }


      ::estatus     out::out_start(const imedia_time & position)
      {

         sync_lock sl(mutex());

         //if(m_estate == state_playing)
         //   return ::success;

         //ASSERT(m_estate == state_opened || m_estate == state_stopped);

         //m_bEOS = false;

         //m_estate = state_playing;

         //m_pprebuffer->start(position);

         //for(index i = 0; i < out_get_buffer()->GetBufferCount(); i++)
         //{

         //   out_free(i);

         //}

         m_estatusWave = ::wave::out::out_start(position);

         if(m_estatusWave != ::success)
         {

            return m_estatusWave;

         }

         m_estatusWave = xaudio::translate(m_psourcevoice->Start(0,XAUDIO2_COMMIT_NOW));

         return ::success;

      }


      ::estatus     out::out_restart()
      {

         single_lock sLock(mutex(), TRUE);

         ASSERT(m_estate == state_paused);

         if(m_estate != state_paused)
            return error_failed;

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_xaudio output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_estatusWave = xaudio::translate(m_psourcevoice->Start(0,XAUDIO2_COMMIT_NOW));

         ASSERT(m_estatusWave == ::success);

         if(m_estatusWave == ::success)
         {

            m_estate = state_playing;

         }

         return m_estatusWave;

      }


      imedia_time out::out_get_time()
      {

         single_lock sLock(mutex(), TRUE);

//         ::estatus                    estatus;

         XAUDIO2_VOICE_STATE s;

         if(m_psourcevoice != nullptr)
         {

            m_psourcevoice->GetState(&s);

            i64 i = s.SamplesPlayed;
            i *= 1000;
            i /= m_pwaveformat->m_waveformat.nSamplesPerSec;
            return i;

         }
         else
            return 0;


      }

      /*imedia_time out::get_position_for_synch()
      {
         imedia_time position = get_position();
         if(m_pprebuffer != nullptr && m_pprebuffer->m_pdecoder != nullptr)
            return m_pprebuffer->m_position + position - m_pprebuffer->m_pdecoder->audio_plugin_get_lost_position_offset(position) - m_dwLostSampleCount * m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         else
            return m_pprebuffer->m_position + position - m_dwLostSampleCount * m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
      }*/

//      imedia_time out::out_get_time()
//      {
//
//         single_lock sLock(mutex(), TRUE);
//
////         ::estatus                    estatus;
//
//         XAUDIO2_VOICE_STATE s;
//
//         if (m_psourcevoice != nullptr)
//         {
//
//            m_psourcevoice->GetState(&s);
//
//            return s.SamplesPlayed;
//
//         }
//         else
//         {
//
//            return 0;
//
//         }
//
//      }


      void out::out_free(index iBuffer)
      {

         ::wave::out::out_free(iBuffer);

      }


      void out::out_on_playback_end()
      {

         out_stop();

         if(m_pprebuffer->m_pstreameffectOut != nullptr)
         {
            ::iaudio::wave_stream_effect * peffect = m_pprebuffer->m_pstreameffectOut;
            m_pprebuffer->m_pstreameffectOut = nullptr;
            delete peffect;
         }

         m_pplayer->post_event(::wave::player::player_event_playback_end);

      }


      ::count out::out_get_buffered_buffer_count()
      {

         return ::wave::out::out_get_buffered_buffer_count();

      }


      WAVEFORMATEX * out::wave_format()
      {

         xaudio::translate(m_waveformatex, m_pwaveformat);

         return &m_waveformatex;

      }


      void * out::get_os_data()
      {
         return m_psourcevoice;
      }


      //void out::out_run_step()
      //{

      //   int iPlay =  -1;


      //}

      void out::out_prebuffer_eof()
      {

         ::wave::out::out_prebuffer_eof();

      }


      void out::OnStreamEnd()
      {

         //out_on_playback_end();

      }


      //
      // Callback handlers, only implement the buffer events for maintaining play state
      //
      void out::OnVoiceProcessingPassStart(::u32 /*bytesRequired*/)
      {
      }
      void out::OnVoiceProcessingPassEnd()
      {
      }

      void out::OnBufferStart(void* pBufferContext)
      {

         ::wave::buffer::item * pbuffer = (::wave::buffer::item *)pBufferContext;

         //pbuffer->m_bIsPlaying =  true;

      }

      void out::OnBufferEnd(void* pBufferContext)
      {

         //if(get_thread_priority() != ::priority_time_critical)
         //{

         //   set_thread_priority(::priority_time_critical);

         //}

         ::u64 freq;
         QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
         double timerFrequency = (1.0 / freq);
         ::u64 startTime;
         QueryPerformanceCounter((LARGE_INTEGER *)&startTime);


         ::wave::buffer::item * pbuffer = (::wave::buffer::item *)pBufferContext;

         //pbuffer->m_bIsPlaying = false;

         i32 iBuffer = (i32)pbuffer->m_iIndex;

         m_psynththread->on_free(iBuffer);

         ::u64 endTime;
         QueryPerformanceCounter((LARGE_INTEGER *)&endTime);
         double timeDifferenceInseconds = ((endTime - startTime) * timerFrequency);
         if(timeDifferenceInseconds > 0.040)
         {
            ::output_debug_string("too much delay to create audio\n");
         }



      }


      void out::OnLoopEnd(void* /*bufferContext*/)
      {
      }
      void out::OnVoiceError(void* /*bufferContext*/, HRESULT /*error*/)
      {
      }
      //out::run_step_thread::run_step_thread(out * pout):
      //   ::thread(pout->get_context_application())
      //{
      //}


      //i32 out::run_step_thread::run()
      //{

      //   while(m_bRun && m_pout->m_estate == out::state_playing)
      //   {
      //      m_pout->out_run_step();
      //   }


      //   return 0;
      //}


   } // namespace audio_xaudio


} // namespace multimedia






