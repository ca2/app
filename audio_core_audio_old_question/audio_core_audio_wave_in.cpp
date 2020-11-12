#include "framework.h"


namespace multimedia
{


   namespace audio_core_audio
   {


      in::in(::layered * pobjectContext) :
         object(pobject),
         ::thread(pobject),
         wave_base(pobject),
         toolbox(pobject),
         ::wave::in(pobject)
      {

         m_pencoder = nullptr;
         m_estate = state_initial;
         m_bResetting = false;


      }

      in::~in()
      {
      }

      bool in::initialize_thread()
      {
         TRACE("in::init_instance %X\n", get_os_int());
         //SetMainWnd(nullptr);
         //ASSERT(GetMainWnd() == nullptr);
         ::multithreading::set_priority(::priority_highest);
         m_evInitialized.SetEvent();


         if(!::wave::in::initialize_thread())
            return false;



         if(!toolbox::initialize_thread())
            return false;


         return true;
      }

      i32 in::exit_thread()
      {
         m_eventExitInstance.SetEvent();
         return thread::exit_thread();
      }

      void in::pre_translate_message(::message::message * pmessage)
      {
         SCAST_PTR(::message::base, pbase, pmessage);
         //ASSERT(GetMainWnd() == nullptr);
         /*         if(pbase->m_id == MM_WIM_OPEN ||
                     pbase->m_id == MM_WIM_CLOSE ||
                     pbase->m_id == MM_WIM_DATA)
                  {
                     translate_in_message(pbase);
                     if(pbase->m_bRet)
                        return;
                  }*/
         return thread::pre_translate_message(pbase);
      }

      ::estatus     in::in_open(i32 iBufferCount, i32 iBufferSampleCount)
      {

         if(m_Queue != nullptr && m_estate != state_initial)
         {
            in_initialize_encoder();
            return ::success;
         }


         return error_failed;

//         single_lock sLock(mutex(), TRUE);
//         ASSERT(m_Queue == nullptr);
//         ASSERT(m_estate == state_initial);
//
//         m_pwaveformat->wFormatTag = 0;
//         m_pwaveformat->nChannels = 2;
//         m_pwaveformat->nSamplesPerSec = 44100;
//         m_pwaveformat->wBitsPerSample = sizeof(::audio::WAVEBUFFERDATA) * 8;
//         m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
//         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
//         m_pwaveformat->cbSize = 0;
//         __pointer(::audio::wave) audiowave = Application.audiowave();
//         m_iBuffer = 0;
//
//         if(::success == (m_estatusWave  = translate(AudioQueueNewInput(                              // 1
//                                                          &m_dataformat,                          // 2
//                                                          &HandleInputBuffer,                            // 3
//                                                          this,                                      // 4
//                                                          nullptr,                                         // 5
//                                                          kCFRunLoopCommonModes,                        // 6
//                                                          0,                                            // 7
//                                                          &m_Queue                                // 8
//                                                          ))))
//            goto Opened;
//         m_pwaveformat->nSamplesPerSec = 22050;
//         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
//         if(::success == (m_estatusWave  = translate(AudioQueueNewInput(                              // 1
//                                                            &m_dataformat,                          // 2
//                                                            &HandleInputBuffer,                            // 3
//                                                            this,                                      // 4
//                                                            nullptr,                                         // 5
//                                                            kCFRunLoopCommonModes,                        // 6
//                                                            0,                                            // 7
//                                                            &m_Queue                                // 8
//                                                            ))))
//            goto Opened;
//         m_pwaveformat->nSamplesPerSec = 11025;
//         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
//         if(::success == (m_estatusWave  = translate(AudioQueueNewInput(                              // 1
//                                                            &m_dataformat,                          // 2
//                                                            &HandleInputBuffer,                            // 3
//                                                            this,                                      // 4
//                                                            nullptr,                                         // 5
//                                                            kCFRunLoopCommonModes,                        // 6
//                                                            0,                                            // 7
//                                                            &m_Queue                                // 8
//                                                            ))))
//            goto Opened;
//
//         return m_estatusWave;
//
//Opened:
//         u32 uiBufferSizeLog2;
//         u32 uiBufferSize;
//         u32 uiAnalysisSize;
//         u32 uiAllocationSize;
//         u32 uiInterestSize;
//         u32 uiSkippedSamplesCount;
//
//         if(m_pwaveformat->nSamplesPerSec == 44100)
//         {
//            uiBufferSizeLog2 = 16;
//            uiBufferSize = m_pwaveformat->nChannels * 2 * iBufferSampleCount; // 512 kbytes
//            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
//            if(iBufferCount > 0)
//            {
//               uiAllocationSize = iBufferCount * uiBufferSize;
//            }
//            else
//            {
//               uiAllocationSize = 8 * uiAnalysisSize;
//            }
//            uiInterestSize = 200;
//            uiSkippedSamplesCount = 2;
//         }
//         else if(m_pwaveformat->nSamplesPerSec == 22050)
//         {
//            uiBufferSizeLog2 = 9;
//            uiBufferSize = 4 * 1 << uiBufferSizeLog2;
//            uiAnalysisSize = 16 * 1 << uiBufferSizeLog2;
//            uiAllocationSize = 4 * uiAnalysisSize;
//            uiInterestSize = 600;
//            uiSkippedSamplesCount = 1;
//         }
////         else if(m_pwaveformat->nSamplesPerSec == 11025)
//         else
//         {
//            uiBufferSizeLog2 = 9;
//            uiBufferSize = 2 * 1 << uiBufferSizeLog2;
//            uiAnalysisSize = 8 * 1 << uiBufferSizeLog2;
//            uiAllocationSize = 4 * uiAnalysisSize;
//            uiInterestSize = 600;
//            uiSkippedSamplesCount = 1;
//         }
//         in_get_buffer()->FFTOpen(
//            uiAllocationSize,
//            uiBufferSize,
//            uiAnalysisSize,
//            uiInterestSize,
//            uiSkippedSamplesCount);
//
///*         i32 i, iSize;
//
//         iSize = (i32) in_get_buffer()->GetBufferCount();
//
//         for(i = 0; i < iSize; i++)
//         {
//
//            if(::success != (mmr =  waveInPrepareHeader(m_Queue, create_new_WAVEHDR(in_get_buffer(), i), sizeof(WAVEHDR))))
//            {
//               TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
//               return mmr;
//            }
//
//            in_add_buffer(i);
//
//         }*/
//
//         if(m_pencoder != nullptr && !in_initialize_encoder())
//         {
//
//            m_estate = state_opened;
//
//            in_close();
//
//            return (::estatus    ) -1;
//
//         }
//
//         m_estate = state_opened;
//
//         return ::success;

      }


      ::estatus     in::in_close()
      {

         single_lock sLock(mutex(), TRUE);

         ::estatus     mmr;

         if(m_estate != state_opened && m_estate != state_stopped)
            return ::success;

         mmr = in_reset();


         free_buffers();

         /*         i32 i, iSize;

                  iSize = (i32) in_get_buffer()->GetBufferCount();

                  for(i = 0; i < iSize; i++)
                  {

                     if(::success != (mmr = waveInUnprepareHeader(m_Queue, wave_hdr(i), sizeof(WAVEHDR))))
                     {
                        TRACE("ERROR OPENING Unpreparing INPUT DEVICE buffer");
                        //return mmr;
                     }

                     delete wave_hdr(i);

                  }*/

         m_estatusWave = translate(AudioQueueDispose(m_Queue, 1));

         m_Queue = nullptr;

         m_estate = state_initial;

         return mmr;

      }


      ::estatus     in::in_start()
      {

         single_lock sLock(mutex(), TRUE);

         if(m_estate == state_recording)
            return ::success;

         if(m_estate != state_opened && m_estate != state_stopped)
            return ::success;

         if(::success != (m_estatusWave = translate(AudioQueueStart(m_Queue, nullptr))))
         {

            TRACE("ERROR starting INPUT DEVICE ");

            return m_estatusWave;

         }

         m_estate = state_recording;

         return ::success;

      }


      ::estatus     in::in_stop()
      {

         single_lock sLock(mutex(), TRUE);

         if(m_estate != state_recording)
            return error_failed;

         OSStatus status;

         m_estate = state_stopping;

         try
         {
            if(0 != (status = AudioQueueStop(m_Queue, 1)))
            {
               TRACE("in::in_stop : ERROR OPENING stopping INPUT DEVICE ");
            }
         }
         catch(...)
         {
            TRACE("in::in_stop : Exception OPENING stopping INPUT DEVICE ");
         }
         m_estate = state_stopped;

         m_eventStopped.SetEvent();

         return ::success;

      }

      /*
            void CALLBACK in::in_proc(HWAVEIN hwi, ::u32 uMsg, ::u32 dwInstance, ::u32 dwParam1, ::u32 dwParam2)
            {

               UNREFERENCED_PARAMETER(hwi);
               UNREFERENCED_PARAMETER(dwInstance);
               UNREFERENCED_PARAMETER(dwParam1);
               UNREFERENCED_PARAMETER(dwParam2);
               if(uMsg == WIM_DATA)
               {
                  ASSERT(FALSE);
                       u32 msSampleTime = timeGetTime();
                  thread * pthread = (thread *) dwInstance;
                  ASSERT(pthread != nullptr);
                  LPWAVEHDR lpWaveHdr = (LPWAVEHDR) dwParam1;
                  LPWAVEPROCDATAMESSAGE lpxfwm = new WAVEPROCDATAMESSAGE;
                  lpxfwm->bDelete = TRUE;
                  lpxfwm->msSampleTime = msSampleTime;
                  //      lpxfwm->tkSamplePosition = tkPosition;
                  lpxfwm->lpWaveHdr = lpWaveHdr;
                  pthread->post_thread_message(
                  WM_USER,
                  (WPARAM) WAVM_WAVE_PROC_DATA,
                  (LPARAM) lpxfwm);
                  //      i++;
                  //      if( i > 2)
                  //         i = 0;
      //         }
        //    }*/

      ::estatus     in::in_reset()
      {
         single_lock sLock(mutex(), TRUE);
         m_bResetting = true;
         if(m_Queue == nullptr)
         {
            return error_failed;
         }

         ::estatus     mmr;
//         OSStatus status;
         if(m_estate == state_recording)
         {
            if(::success != (mmr = in_stop()))
            {
               TRACE("in::Reset error stopping input device");
               return mmr;
            }
         }
         try
         {
//            if(0 != (status = AudioQueueReset(m_Queue)))
            if(0 != (AudioQueueReset(m_Queue)))
            {
               TRACE("in::Reset error resetting input device");
               return error_failed;
            }
         }
         catch(...)
         {
         }

         m_estate = state_opened;

         m_bResetting = false;

         return mmr;

      }



      ::estatus     in::in_add_buffer(i32 iBuffer)
      {

         AudioQueueBufferRef buf = audio_buffer(iBuffer);

         AudioQueueEnqueueBuffer(m_Queue, buf, 0, nullptr);

         return ::success;

      }





      bool in::in_initialize_encoder()
      {

         if(m_pencoder == nullptr)
            return false;

         if(!::wave::in::in_initialize_encoder())
            return false;

         return true;

      }


      AudioQueueRef in::in_get_safe_AudioQueueRef()
      {

         if(is_null(*this))
            return nullptr;

         return m_Queue;

      }


      void * in::get_os_data()
      {

         return m_Queue;

      }


      void in::HandleInputBuffer(void                                 *aqData,
                                      AudioQueueRef                        inAQ,
                                      AudioQueueBufferRef                  inBuffer,
                                      const AudioTimeStamp                 *inStartTime,
                                      ::u32                               inNumPackets,
                                      const AudioStreamPacketDescription   *inPacketDesc)
      {

         in * pwavein = (in *) aqData;               // 1

         pwavein->HandleInputBuffer(inAQ, inBuffer, inStartTime, inNumPackets, inPacketDesc);

      }


      void in::HandleInputBuffer( AudioQueueRef                        inAQ,
                                       AudioQueueBufferRef                  inBuffer,
                                       const AudioTimeStamp                 *inStartTime,
                                       ::u32                               inNumPackets,
                                       const AudioStreamPacketDescription   *inPacketDesc)
      {

         if(inNumPackets == 0 && m_dataformat.mBytesPerPacket != 0)
            inNumPackets = inBuffer->mAudioDataByteSize / m_dataformat.mBytesPerPacket;

         m_iBuffer--;

         u32 msSampleTime = ::get_tick();

         int iBuffer = (int) m_Buffers.find_first(inBuffer);

         m_listenerset.in_data_proc(this, msSampleTime, iBuffer);

         if(m_pencoder != nullptr)
         {

            m_pencoder->EncoderWriteBuffer(inBuffer->mAudioData, inBuffer->mAudioDataByteSize);

         }

         if(!in_is_resetting() && in_is_recording())
         {

            in_add_buffer(iBuffer);

         }


         if (m_bIsRunning == 0)                                         // 5
            return;


      }


   } // namespace audio_core_audio


} // namespace multimedia






