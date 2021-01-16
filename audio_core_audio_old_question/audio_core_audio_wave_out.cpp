#include "framework.h"

extern
void InstallUncaughtExceptionHandler();

void WaveOutAudioQueueBufferCallback(void * inUserData, AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer);




namespace multimedia
{


   namespace audio_core_audio
   {


      out::out(::layered * pobjectContext) :
         object(pobject),
         ::thread(pobject),
         wave_base(pobject),
         toolbox(pobject),
         ::wave::out(pobject)
      {

         m_estate             = e_state_initial;
         m_pthreadCallback    = nullptr;
         m_estatusWave                = ::success;
         m_peffect            = nullptr;
         //m_dwLostSampleBytes  = 0;
         m_bDone              = false;
         m_eventRunning.ResetEvent();

      }

      out::~out()
      {

      }

      void out::install_message_routing(::channel * pchannel)
      {

         ::wave::out::install_message_routing(pchannel);


      }


      void out::OnOpen()
      {

         set_event_on_exit set_event_on_exitOpened(m_eventOpened);

         if(succeeded(m_estatusWave = translate(AudioQueueNewOutput(&m_dataformat, WaveOutAudioQueueBufferCallback, this, nullptr, kCFRunLoopCommonModes, 0, &m_Queue))))
            return;

         u32 uiBufferSizeLog2;
         u32 uiBufferSize;
         u32 uiAnalysisSize;
         u32 uiAllocationSize;
         u32 uiInterestSize;
         u32 uiSkippedSamplesCount;
         u32 uiBufferCount = m_iBufferCount;

         //   if(m_pwaveformat->nSamplesPerSec == 44100)
//         if(true)
//         {
//            uiBufferSizeLog2 = 16;
//            uiBufferSize = m_pwaveformat->nChannels * 2 * m_iBufferSampleCount; // 512 kbytes
//            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
//            if(m_iBufferCount > 0)
//            {
//               uiAllocationSize = m_iBufferCount * uiAnalysisSize;
//            }
//            else
//            {
//               uiAllocationSize = 8 * uiAnalysisSize;
//            }
//            uiInterestSize = 200;
//            uiSkippedSamplesCount = 2;
//         }
//         else
//
         if(m_pwaveformat->nSamplesPerSec == 22050)
         {
            uiBufferSizeLog2 = 10;
            uiBufferSize = 4 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 200;
            uiSkippedSamplesCount = 1;
         }
         else if(m_pwaveformat->nSamplesPerSec == 11025)
         {
            uiBufferSizeLog2 = 10;
            uiBufferSize = 2 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 2 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 200;
            uiSkippedSamplesCount = 1;
         }

         out_get_buffer()->PCMOutOpen(this, uiBufferSize, uiBufferCount, 64, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(this, m_pwaveformat->nChannels, uiBufferCount, m_iBufferSampleCount);

         /*

          i32 i, iSize;

          iSize = out_get_buffer()->GetBufferCount();

          for(i = 0; i < iSize; i++)
          {

          if(::success != (mmr =  waveOutPrepareHeader(m_Queue, create_new_WAVEHDR(out_get_buffer(), i), sizeof(WAVEHDR))))
          {
          TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
          return mmr;
          }

          //out_add_buffer(i);

          }

          */

         m_pprebuffer->SetMinL1BufferCount(out_get_buffer()->GetBufferCount() + 4);

         m_estate = e_state_opened;

         m_estatusWave = ::success;

      }


      bool out::initialize_thread()
      {

         if(!::wave::out::initialize_thread())
            return false;

         if(!toolbox::initialize_thread())
            return false;

         return true;

      }

      i32 out::exit_thread()
      {

         ::wave::out::exit_thread();

         toolbox::exit_thread();

         return thread::exit_thread();

      }

      ::e_status     out::out_open(thread * pthreadCallback, i32 iBufferCount, i32 iBufferSampleCount)
      {

         single_lock sLock(mutex(), TRUE);

         if(m_Queue != nullptr &&
               m_estate != e_state_initial)
            return ::success;

         m_pthreadCallback = pthreadCallback;

         ASSERT(m_Queue == nullptr);
         ASSERT(m_estate == e_state_initial);

         m_pwaveformat->wFormatTag = 0;
         m_pwaveformat->nChannels = 2;
         m_pwaveformat->nSamplesPerSec = 44100;
         m_pwaveformat->wBitsPerSample = sizeof(multimedia::audio::WAVEBUFFERDATA) * 8;
         m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         m_pwaveformat->cbSize = 0;

         __pointer(::audio::wave) audiowave = Application.audiowave();

         translate(*&m_dataformat, m_pwaveformat);
         if(::success == (m_estatusWave = translate(AudioQueueNewOutput(                              // 1
                                        &m_dataformat,                          // 2
                                        WaveOutAudioQueueBufferCallback,                            // 3
                                        this,                                      // 4
                                        m_runloop,                                         // 5
                                        kCFRunLoopDefaultMode,                        // 6
                                        0,                                            // 7
                                        &m_Queue                                // 8
                                        ))))
            goto Opened;
         m_pwaveformat->nSamplesPerSec = 22050;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         if(::success == (m_estatusWave = translate(AudioQueueNewOutput(                              // 1
                                        &m_dataformat,                          // 2
                                        WaveOutAudioQueueBufferCallback,                            // 3
                                        this,                                      // 4
                                        m_runloop,                                         // 5
                                        kCFRunLoopDefaultMode,                        // 6
                                        0,                                            // 7
                                        &m_Queue                                // 8
                                        ))))
            goto Opened;
         m_pwaveformat->nSamplesPerSec = 11025;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         if(::success == (m_estatusWave = translate(AudioQueueNewOutput(                              // 1
                                        &m_dataformat,                          // 2
                                        WaveOutAudioQueueBufferCallback,                            // 3
                                        this,                                      // 4
                                        m_runloop,                                         // 5
                                        kCFRunLoopDefaultMode,                        // 6
                                        0,                                            // 7
                                        &m_Queue                                // 8
                                        ))))
            goto Opened;

         return m_estatusWave;

Opened:

         u32 uiBufferSizeLog2;
         u32 uiBufferSize;
         u32 uiAnalysisSize;
         u32 uiAllocationSize;
         u32 uiInterestSize;
         u32 uiSkippedSamplesCount;
         u32 uiBufferCount = iBufferCount;

         if(m_pwaveformat->nSamplesPerSec == 44100)
         {
            uiBufferSizeLog2 = 16;
            uiBufferSize = m_pwaveformat->nChannels * 2 * iBufferSampleCount; // 512 kbytes
            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
            if(iBufferCount > 0)
            {
               uiAllocationSize = iBufferCount * uiAnalysisSize;
            }
            else
            {
               uiAllocationSize = 8 * uiAnalysisSize;
            }
            uiInterestSize = 200;
            uiSkippedSamplesCount = 2;
         }
         else if(m_pwaveformat->nSamplesPerSec == 22050)
         {
            uiBufferSizeLog2 = 10;
            uiBufferSize = 4 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 200;
            uiSkippedSamplesCount = 1;
         }
         //         else if(m_pwaveformat->nSamplesPerSec == 11025)
         else
         {
            uiBufferSizeLog2 = 10;
            uiBufferSize = 2 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 2 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 200;
            uiSkippedSamplesCount = 1;
         }

         out_get_buffer()->PCMOutOpen(this, uiBufferSize, uiBufferCount, 64, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(
         this, // callback thread (thread)
         m_pwaveformat->nChannels, // channel count
         uiBufferCount, // group count
         iBufferSampleCount); // group sample count

         /*         i32 i, iSize;
          iSize = out_get_buffer()->GetBufferCount();

          AudioQueueBufferRef buf;

          for(i = 0; i < iSize; i++)
          {

          buf = nullptr;

          if(0 != (status = AudioQueueAllocateBuffer (m_Queue, out_get_buffer_size(), &buf))
          {
          TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
          return error_failed;
          }

          m_Buffers.add(buf);

          }*/
         m_estate = e_state_opened;
         return m_estatusWave;
      }

      ::e_status     out::out_open_ex(thread * pthreadCallback, i32 iBufferCount, i32 iBufferSampleCount, u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitsPerSample, ::audio::e_purpose epurpose)
      {

         single_lock sLock(mutex(), TRUE);

         if(m_Queue != nullptr && m_estate != e_state_initial)
            return ::success;

         m_pthreadCallback = pthreadCallback;

         ASSERT(m_Queue == nullptr);

         ASSERT(m_estate == e_state_initial);

         m_pwaveformat->wFormatTag        = 0;
         m_pwaveformat->nChannels         = (::u16) uiChannelCount;
         m_pwaveformat->nSamplesPerSec    = uiSamplesPerSec;
         m_pwaveformat->wBitsPerSample    = (::u16) uiBitsPerSample;
         m_pwaveformat->nBlockAlign       = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         m_pwaveformat->nAvgBytesPerSec   = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         m_pwaveformat->cbSize            = 0;

         xxf_zero_pointer(&m_dataformat);

         translate(*&m_dataformat, m_pwaveformat);

         iBufferCount = 4;
         iBufferSampleCount = 1024;

         m_iBufferCount = iBufferCount;
         m_iBufferSampleCount = iBufferSampleCount;

         try
         {

            if(failed(m_estatusWave = translate(AudioQueueNewOutput(&m_dataformat, WaveOutAudioQueueBufferCallback, this, nullptr, kCFRunLoopCommonModes, 0, &m_Queue))))
               return m_estatusWave;

         }
         catch(...)
         {

            m_estatusWave = result_error;

            return m_estatusWave;

         }

         u32 uiBufferSizeLog2;
         u32 uiBufferSize;
         u32 uiAnalysisSize;
         u32 uiAllocationSize;
         u32 uiInterestSize;
         u32 uiSkippedSamplesCount;
         u32 uiBufferCount = iBufferCount;

         //   if(m_pwaveformat->nSamplesPerSec == 44100)
         if(true)
         {
            uiBufferSizeLog2 = 16;
            uiBufferSize = m_pwaveformat->nChannels * 2 * iBufferSampleCount; // 512 kbytes
            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
            if(iBufferCount > 0)
            {
               uiAllocationSize = iBufferCount * uiAnalysisSize;
            }
            else
            {
               uiAllocationSize = 8 * uiAnalysisSize;
            }
            uiInterestSize = 200;
            uiSkippedSamplesCount = 2;
         }
         else if(m_pwaveformat->nSamplesPerSec == 22050)
         {
            uiBufferSizeLog2 = 10;
            uiBufferSize = 4 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 200;
            uiSkippedSamplesCount = 1;
         }
         else if(m_pwaveformat->nSamplesPerSec == 11025)
         {
            uiBufferSizeLog2 = 10;
            uiBufferSize = 2 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 2 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 200;
            uiSkippedSamplesCount = 1;
         }

         out_get_buffer()->PCMOutOpen(this, uiBufferSize, uiBufferCount, 64, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(this, m_pwaveformat->nChannels, uiBufferCount, iBufferSampleCount);

         /*         i32 i, iSize;

          iSize = out_get_buffer()->GetBufferCount();

          for(i = 0; i < iSize; i++)
          {

          if(::success != (mmr =  waveOutPrepareHeader(m_Queue, create_new_WAVEHDR(out_get_buffer(), i), sizeof(WAVEHDR))))
          {
          TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
          return mmr;
          }

          //out_add_buffer(i);

          }*/


         m_estate = e_state_opened;

         return m_estatusWave;

      }



      ::e_status     out::out_close()
      {

         single_lock sLock(mutex(), TRUE);

         if(m_estate == e_state_playing)
         {
            out_stop();
         }

         if(m_estate != e_state_opened)
            return ::success;

         OSStatus status;

         free_buffers();

         /*         ::e_status     mmr;

          i32 i, iSize;

          iSize =  out_get_buffer()->GetBufferCount();

          for(i = 0; i < iSize; i++)
          {

          if(::success != (mmr = waveOutUnprepareHeader(m_Queue, wave_hdr(i), sizeof(WAVEHDR))))
          {
          TRACE("ERROR OPENING Unpreparing INPUT DEVICE buffer =%d", mmr);
          }

          delete wave_hdr(i);

          }*/

         status = AudioQueueDispose(m_Queue, 1);

         m_Queue = nullptr;

         m_pprebuffer->Reset();

         m_estate = e_state_initial;

         return ::success;

      }

      /*
       void out::OnMultimediaOpen(::message::message * pmessage)
       {
       UNREFERENCED_PARAMETER(pmessage);
       }


       void out::OnMultimediaDone(::message::message * pmessage)
       {

       __pointer(::message::base) pbase(pmessage);

       LPWAVEHDR lpwavehdr = (LPWAVEHDR) pbase->m_lparam.m_lparam;

       out_out_buffer_done(lpwavehdr->dwUser);

       }

       void out::OnMultimediaClose(::message::message * pmessage)
       {
       UNREFERENCED_PARAMETER(pmessage);
       }
       */

      /*void out::out_on_buffer_ready(::message::message * pmessage)
       {
       UNREFERENCED_PARAMETER(pmessage);
       }*/


      void out::out_buffer_ready(int iBuffer)
      {

         if(out_get_state() != e_state_playing)
         {
            TRACE("ERROR out::BufferReady while out_get_state() != e_state_playing");
            return;
         }

         AudioQueueBufferRef buf = audio_buffer(iBuffer);

         OSStatus status;

         if(m_peffect != nullptr)
         {

            m_peffect->Process16bits((i16 *) buf->mAudioData, out_get_buffer_size() / 2);

         }

         single_lock sLock(mutex(), TRUE);

         buf->mAudioDataByteSize = out_get_buffer_size();

         status = AudioQueueEnqueueBuffer(m_Queue, buf, 0, nullptr);

         VERIFY(status == 0);

         if(status == 0)
         {

            m_iBufferedCount++;

         }

      }


      ::e_status     out::out_stop()
      {

         single_lock sLock(mutex(), TRUE);

         if(m_estate != e_state_playing && m_estate != e_state_paused)
            return error_failed;

         m_eventStopped.ResetEvent();

         m_pprebuffer->Stop();

         m_estate = e_state_stopping;

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_core_audio output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_estatusWave = translate(AudioQueueReset(m_Queue));

         if(m_estatusWave == ::success)
         {
            m_estate = e_state_opened;
         }

         return m_estatusWave;

      }


      ::e_status     out::out_pause()
      {

         single_lock sLock(mutex(), TRUE);

         ASSERT(m_estate == e_state_playing);

         if(m_estate != e_state_playing)
            return error_failed;

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_core_audio output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_estatusWave = translate(AudioQueuePause(m_Queue));

         ASSERT(m_estatusWave == ::success);

         if(m_estatusWave == ::success)
         {
            m_estate = e_state_paused;
         }

         return m_estatusWave;

      }


      ::e_status     out::out_restart()
      {

         single_lock sLock(mutex(), TRUE);

         ASSERT(m_estate == e_state_paused);

         if(m_estate != e_state_paused)
         {

            m_estatusWave = error_failed;

            return m_estatusWave;

         }

         m_estatusWave = translate(AudioQueuePrime(m_Queue, 0, nullptr));

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_core_audio output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_estatusWave = translate(AudioQueueStart(m_Queue, nullptr));

         ASSERT(m_estatusWave == ::success);

         if(m_estatusWave == ::success)
         {

            m_estate = e_state_playing;

         }

         return m_estatusWave;

      }


      imedia_time out::out_get_time()
      {

         single_lock sLock(mutex(), TRUE);

         OSStatus                status;

         AudioTimeStamp          stamp;

         if(m_Queue != nullptr)
         {


            AudioQueueTimelineRef timeLine;

            status = AudioQueueCreateTimeline(m_Queue, &timeLine);
            if(status != noErr)
               return 0;

            status = AudioQueueGetCurrentTime(m_Queue, timeLine, &stamp, nullptr);

            if(status != 0)
               return 0;




            if(!(stamp.mFlags & kAudioTimeStampSampleTimeValid))
               return 0;

            return (imedia_time) stamp.mSampleTime * 1000 / m_pwaveformat->nSamplesPerSec;

         }
         else
            return 0;


      }


      imedia_time out::out_get_time()
      {

         single_lock sLock(mutex(), TRUE);

         OSStatus                status;

         AudioTimeStamp          stamp;

         if(m_Queue != nullptr)
         {

            AudioQueueTimelineRef timeLine;

            status = AudioQueueCreateTimeline(m_Queue, &timeLine);
            if(status != noErr)
               return 0;

            status = AudioQueueGetCurrentTime(m_Queue, timeLine, &stamp, nullptr);

            if(status != 0)
               return 0;


            if(!(stamp.mFlags & kAudioTimeStampSampleTimeValid))
               return 0;

            return (imedia_time) stamp.mSampleTime;

         }
         else
            return 0;


      }

      void out::out_on_playback_end()
      {

         out_stop();

         if(m_pprebuffer->m_pstreameffectOut != nullptr)
         {
            ::multimedia::iaudio::wave_stream_effect * peffect = m_pprebuffer->m_pstreameffectOut;
            m_pprebuffer->m_pstreameffectOut = nullptr;
            delete peffect;
         }

         m_eventStopped.SetEvent();

         m_pplayer->OnEvent(::wave::player::EventPlaybackEnd);

      }





      void * out::get_os_data()
      {

         return m_Queue;

      }



      void out::AudioQueueBufferCallback(AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer)
      {

         if(m_bDone)
            return;

         index iBuffer = m_Buffers.find_first(inCompleteAQBuffer);

         if(iBuffer < 0)
            return;

         m_iBufferedCount--;

         out_out_buffer_done((int) iBuffer);

      }


      AudioQueueRef out::out_get_safe_AudioQueueRef()
      {

         return m_Queue;

      }

      /*
       int out::run()
       {

       MESSAGE msg;

       while(m_bRun)
       {

       if(::PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
       {

       if(!pump_message())
       {

       break;

       }

       }


       if(m_estate == e_state_playing)
       {
       CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.25, false);
       }
       else
       {
       sleep(8_ms);
       }

       }

       return 0;
       }*/


      bool out::on_run_step()
      {

//         ::thread::on_run_step();

         if(m_estate == e_state_playing)
         {

            CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.25, false);

         }

         return true;

      }

      ::e_status     out::out_start(const imedia_time & position)
      {

         ::e_status     mmr = ::wave::out::out_start(position);

         if(mmr != 0)
            return mmr;

         m_estate = e_state_paused;

         m_estatusWave = out_restart();

         return m_estatusWave;

      }


   } // namespace audio_core_audio


} // namespace multimedia







void WaveOutAudioQueueBufferCallback(void * inUserData, AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer)
{

   ::multimedia::audio_core_audio::out * pwaveout = (::multimedia::audio_core_audio::out *) inUserData;

   if(pwaveout == nullptr)
      return;

   try
   {

      pwaveout->AudioQueueBufferCallback(inAQ, inCompleteAQBuffer);

   }
   catch(...)
   {

   }

}
