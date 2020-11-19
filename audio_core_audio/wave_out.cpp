#include "framework.h"
#include "aura/message.h"


void WaveOutAudioQueueBufferCallback(void * inUserData, AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer);


namespace multimedia
{


   namespace audio_core_audio
   {


      out::out()
      {

         m_estate             = state_initial;
         m_pthreadCallback    = nullptr;
         m_estatusWave        = ::success;
         m_bDone              = false;

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

         if(!::wave::out::init_thread())
         {
            
            return false;
            
         }

         if(!toolbox::init_thread())
         {
            
            return false;
            
         }

         return true;

      }
   

      void out::term_thread()
      {

         ::wave::out::term_thread();

         toolbox::term_thread();

         thread::term_thread();

      }


      ::estatus out::out_open_ex(thread * pthreadCallback, u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitsPerSample, ::wave::e_purpose epurpose)
      {

         sync_lock sl(mutex());

         if(m_Queue != nullptr && m_estate != state_initial)
         {

            return ::success;

         }

         m_pthreadCallback = pthreadCallback;

         ASSERT(m_Queue == nullptr);

         ASSERT(m_estate == state_initial);

         m_pwaveformat->wFormatTag        = 0;
         m_pwaveformat->nChannels         = (::u16) uiChannelCount;
         m_pwaveformat->nSamplesPerSec    = uiSamplesPerSec;
         m_pwaveformat->wBitsPerSample    = (::u16) uiBitsPerSample;
         m_pwaveformat->nBlockAlign       = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         m_pwaveformat->nAvgBytesPerSec   = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         m_pwaveformat->cbSize            = 0;

         ·zero_pointer(&m_dataformat);

         translate(m_dataformat, m_pwaveformat);

         int iBufferCount = 8;

         int iBufferSampleCount = 8192;

         if(epurpose == ::wave::purpose_playground)
         {

            iBufferCount = 2;

            iBufferSampleCount = uiSamplesPerSec / 40;

         }
         else if(epurpose == ::wave::purpose_playback)
         {

            iBufferCount = 8;

            iBufferSampleCount = uiSamplesPerSec / 20;

         }
         else if(epurpose == ::wave::purpose_live)
         {

            iBufferCount = 4;

            iBufferSampleCount = uiSamplesPerSec / 40;

         }

         m_epurpose = epurpose;
         m_iBufferCount = iBufferCount;
         m_iBufferSampleCount = iBufferSampleCount;

         m_estatusWave = error_failed;
         
         try
         {

            OSStatus osstatus = AudioQueueNewOutput(&m_dataformat, WaveOutAudioQueueBufferCallback, this, nullptr, nullptr, 0, &m_Queue);
            
            m_estatusWave = translate(osstatus);

         }
         catch(...)
         {

            m_estatusWave = error_failed;

            return m_estatusWave;

         }

         int iFrameSize = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;

         int iBufferSize = iBufferSampleCount * iFrameSize;

         out_get_buffer()->PCMOutOpen(this, iBufferSize, iBufferCount, 64, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open( m_pwaveformat->nChannels, iBufferCount, iBufferSampleCount);

         m_estate = state_opened;

         return m_estatusWave;

      }


      ::estatus out::out_close()
      {

         if(m_estate == state_playing)
         {

            out_stop();

         }

         if(m_estate != state_opened)
         {

            return ::success;

         }

         m_estate = state_closing;

         OSStatus status;

         int i = 0;

         ::u32 property_running;

         ::u32 size;

         while(i < 50)
         {

            property_running = 0;

            size = sizeof(property_running);

            {
               
               sync_lock sl(mutex());

               status = AudioQueueGetProperty(m_Queue, kAudioQueueProperty_IsRunning, &property_running, &size);
               
            }

            if(status != 0)
            {

               break;

            }

            if(!property_running)
            {

               break;

            }

            i++;

            Sleep(100);

         }

         free_buffers();
         
         {
         
            sync_lock sl(mutex());

            status = AudioQueueDispose(m_Queue, FALSE);
            
         }

         m_Queue = nullptr;

         m_estate = state_initial;

         return ::success;

      }


      void out::out_filled(index iBuffer)
      {

         if(out_get_state() != state_playing)
         {

            TRACE("ERROR out::BufferReady while out_get_state() != state_playing");

            return;

         }

         sync_lock sl(mutex());

         AudioQueueBufferRef buffer = audio_buffer(iBuffer);

         OSStatus status;

         buffer->mAudioDataByteSize = (::u32) out_get_buffer_size();

         status = AudioQueueEnqueueBuffer(m_Queue, buffer, 0, nullptr);

         if(status == 0)
         {

            m_iBufferedCount++;

         }

      }

   
      ::estatus out::out_stop()
      {

         sync_lock sl(mutex());

         if(m_estate != state_playing && m_estate != state_paused)
         {

            return error_failed;

         }

         m_estate = state_stopping;
         
         OSStatus status = AudioQueueStop(m_Queue, FALSE);

         m_estatusWave = translate(status);

         if(m_estatusWave == ::success)
         {

            m_estate = state_opened;

         }

         return m_estatusWave;

      }


      ::estatus out::out_pause()
      {

         sync_lock sl(mutex());

         ASSERT(m_estate == state_playing);

         if(m_estate != state_playing)
         {

            return error_failed;

         }

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_core_audio output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         OSStatus status = AudioQueuePause(m_Queue);
         
         m_estatusWave = translate(status);

         ASSERT(m_estatusWave == ::success);

         if(m_estatusWave == ::success)
         {

            m_estate = state_paused;

         }

         return m_estatusWave;

      }


      ::estatus out::out_restart()
      {

         sync_lock sl(mutex());

         ASSERT(m_estate == state_paused);

         if(m_estate != state_paused)
         {

            m_estatusWave = error_failed;

            return m_estatusWave;

         }

         m_estatusWave = _out_start();

         return m_estatusWave;

      }


      ::estatus out::_out_start()
      {

         sync_lock sl(mutex());

         OSStatus statusPrime = AudioQueuePrime(m_Queue, 0, nullptr);

         m_estatusWave = translate(statusPrime);

         ASSERT(m_estatusWave == ::success);

         OSStatus statusStart = AudioQueueStart(m_Queue, nullptr);

         string strErrorString = apple_error_string(statusStart);

         string strErrorDescription = apple_error_description(statusStart);

         m_estatusWave = translate(statusStart);

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

            imedia_time iTime = (imedia_time) stamp.mSampleTime * 1000 / m_pwaveformat->nSamplesPerSec;

            return iTime;

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

         ::wave::out::out_on_playback_end();

      }


      void * out::get_os_data()
      {

         return m_Queue;

      }



      void out::AudioQueueBufferCallback(AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer)
      {

         if(m_bDone)
         {

            return;

         }

         index iBuffer = m_Buffers.find_first(inCompleteAQBuffer);

         if(iBuffer < 0)
         {

            return;

         }

         m_psynththread->on_free(iBuffer);

      }


      AudioQueueRef out::out_get_safe_AudioQueueRef()
      {

         return m_Queue;

      }


      bool out::on_run_step()
      {

         if(m_estate == state_playing)
         {

            CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.25, false);

         }

         return true;

      }


      ::estatus     out::out_start(const imedia_time & position)
      {

         ::estatus     estatus = ::wave::out::out_start(position);

         if(failed(estatus))
         {

            return estatus;

         }

         m_estatusWave = _out_start();

         return m_estatusWave;

      }


   } // namespace audio_core_audio


} // namespace multimedia




void WaveOutAudioQueueBufferCallback(void * inUserData, AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer)
{

   ::multimedia::audio_core_audio::out * pwaveout = (::multimedia::audio_core_audio::out *) inUserData;

   if(pwaveout == nullptr)
   {

      return;

   }

   try
   {

      pwaveout->AudioQueueBufferCallback(inAQ, inCompleteAQBuffer);

   }
   catch(...)
   {

   }

}



