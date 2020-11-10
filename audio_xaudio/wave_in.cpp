#include "framework.h"


namespace multimedia
{


   namespace audio_xaudio
   {


      in::in()
      {

         m_pencoder = nullptr;
         m_estate = state_initial;
         m_bResetting = false;

      }


      in::~in()
      {

      }


      ::estatus in::init_thread()
      {

         TRACE("in::init_instance %X\n", get_ithread());

         //SetMainWnd(nullptr);

         //ASSERT(GetMainWnd() == nullptr);

         set_thread_priority(::priority_highest);

//         m_evInitialized.SetEvent();

         return true;

      }


      void in::term_thread()
      {

         m_eventExitInstance.SetEvent();

         thread::term_thread();

      }


      void in::pre_translate_message(::message::message * pmessage)
      {
         SCAST_PTR(::message::base, pbase, pmessage);
         //ASSERT(GetMainWnd() == nullptr);
         //if(pbase->m_id == MM_WIM_OPEN ||
         //   pbase->m_id == MM_WIM_CLOSE ||
         //   pbase->m_id == MM_WIM_DATA)
         //{
         //   translate_in_message(pbase);
         //   if(pbase->m_bRet)
         //      return;
         //}
         return thread::pre_translate_message(pbase);
      }

      ::estatus     in::in_open(i32 iBufferCount, i32 iBufferSampleCount)
      {

//         if(m_hwavein != nullptr && m_estate != state_initial)
//         {
//            in_initialize_encoder();
//
//            return ::success;
//
//         }
//
//         single_lock sLock(mutex(), TRUE);
//         ::estatus     estatus;
//         ASSERT(m_hwavein == nullptr);
//         ASSERT(m_estate == state_initial);
//
//         m_pwaveformat->wFormatTag = WAVE_FORMAT_PCM;
//         m_pwaveformat->nChannels = 2;
//         m_pwaveformat->nSamplesPerSec = 44100;
//         m_pwaveformat->wBitsPerSample = sizeof(::audio::WAVEBUFFERDATA) * 8;
//         m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
//         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
//         m_pwaveformat->cbSize = 0;
//         __pointer(::audio::wave) audiowave = Application.audiowave();
//         m_iBuffer = 0;
//
//         if(MMSYSERR_NOERROR == (estatus = xaudio::translate(waveInOpen(
//            &m_hwavein,
//            audiowave->m_uiWaveInDevice,
//            wave_format(),
//            get_os_int(),
//            (u32) 0,
//            CALLBACK_THREAD))))
//            goto Opened;
//
//         m_pwaveformat->nSamplesPerSec = 22050;
//         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
//         if(MMSYSERR_NOERROR == (estatus = xaudio::translate(waveInOpen(
//            &m_hwavein,
//            WAVE_MAPPER,
//            wave_format(),
//            (u32) get_os_int(),
//            (u32) 0,
//            CALLBACK_THREAD))))
//            goto Opened;
//         m_pwaveformat->nSamplesPerSec = 11025;
//         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
//         if(MMSYSERR_NOERROR == (estatus = xaudio::translate(waveInOpen(
//            &m_hwavein,
//            WAVE_MAPPER,
//            wave_format(),
//            (u32) get_os_int(),
//            (u32) 0,
//            CALLBACK_THREAD))))
//            goto Opened;
//
//         if(estatus !=MMSYSERR_NOERROR)
//         {
//            if(estatus == MMSYSERR_ALLOCATED)
//            {
//               TRACE("Specified resource is already allocated.");
//            }
//            else if(estatus == MMSYSERR_BADDEVICEID)
//            {
//               TRACE("Specified device identifier is out of range.");
//            }
//            else if(estatus == WAVERR_BADFORMAT)
//            {
//               TRACE("Attempted to open with an unsupported waveform-audio_xaudio format.");
//            }
//            TRACE("ERROR OPENING WAVE INPUT DEVICE");
//            return estatus;
//         }
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
//         else if(m_pwaveformat->nSamplesPerSec == 11025)
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
//         i32 i, iSize;
//
//         iSize = (i32) in_get_buffer()->GetBufferCount();
//
//         for(i = 0; i < iSize; i++)
//         {
//
//            if(MMSYSERR_NOERROR != (estatus = xaudio::translate(waveInPrepareHeader(m_hwavein, xaudio::create_new_WAVEHDR(in_get_buffer(), i), sizeof(WAVEHDR)))))
//            {
//               TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
//               return estatus;
//            }
//
//            in_add_buffer(i);
//
//         }
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
         return ::success;

      }


      ::estatus     in::in_close()
      {

         single_lock sLock(mutex(), TRUE);

         //::estatus     estatus;

         //if(m_estate != state_opened && m_estate != state_stopped)
         //   return ::success;

         //estatus = in_reset();

         //i32 i, iSize;

         //iSize = (i32) in_get_buffer()->GetBufferCount();

         //for(i = 0; i < iSize; i++)
         //{

         //   if(::success != (estatus = xaudio::translate(waveInUnprepareHeader(m_hwavein, wave_hdr(i), sizeof(WAVEHDR)))))
         //   {
         //      TRACE("ERROR OPENING Unpreparing INPUT DEVICE buffer");
         //      //return estatus;
         //   }

         //   delete wave_hdr(i);

         //}

         //estatus = xaudio::translate(waveInClose(m_hwavein));

         //m_hwavein = nullptr;

         //m_estate = state_initial;

         return ::success;

      }

      ::estatus     in::in_start()
      {

         single_lock sLock(mutex(), TRUE);

         if(m_estate == state_recording)
            return ::success;

         //ASSERT(m_estate == state_opened || m_estate == state_stopped);

         if(m_estate != state_opened && m_estate != state_stopped)
            return ::success;

         //::estatus     estatus;

         //if(::success != (estatus = xaudio::translate(waveInStart(m_hwavein))))
         //{
         //   TRACE("ERROR starting INPUT DEVICE ");
         //   return estatus;
         //}

         m_estate = state_recording;

         return ::success;

      }

      ::estatus     in::in_stop()
      {

         single_lock sLock(mutex(), TRUE);

         if(m_estate != state_recording)
            return error_failed;

//         ::estatus     estatus;

         m_estate = state_stopping;

         //try
         //{

         //   if(::success != (estatus = xaudio::translate(waveInStop(m_hwavein))))
         //   {

         //      TRACE("in::in_stop : ERROR OPENING stopping INPUT DEVICE ");

         //   }

         //}
         //catch(...)
         //{

         //   TRACE("in::in_stop : Exception OPENING stopping INPUT DEVICE ");

         //}

         m_estate = state_stopped;

         m_eventStopped.SetEvent();

         return ::success;

      }


      //void CALLBACK in::in_proc(HWAVEIN hwi, ::u32 uMsg, ::u32 dwInstance, ::u32 dwParam1, ::u32 dwParam2)
      //{

      //   UNREFERENCED_PARAMETER(hwi);
      //   UNREFERENCED_PARAMETER(dwInstance);
      //   UNREFERENCED_PARAMETER(dwParam1);
      //   UNREFERENCED_PARAMETER(dwParam2);
      //   if(uMsg == WIM_DATA)
      //   {
      //      ASSERT(FALSE);
      //      /*      u32 msSampleTime = timeGetTime();
      //      thread * pthread = (thread *) dwInstance;
      //      ASSERT(pthread != nullptr);
      //      LPWAVEHDR lpWaveHdr = (LPWAVEHDR) dwParam1;
      //      LPWAVEPROCDATAMESSAGE lpxfwm = new WAVEPROCDATAMESSAGE;
      //      lpxfwm->bDelete = TRUE;
      //      lpxfwm->msSampleTime = msSampleTime;
      //      //      lpxfwm->tkSamplePosition = tkPosition;
      //      lpxfwm->lpWaveHdr = lpWaveHdr;
      //      pthread->post_thread_message(
      //      WM_USER,
      //      (WPARAM) WAVM_WAVE_PROC_DATA,
      //      (LPARAM) lpxfwm);
      //      //      i++;
      //      //      if( i > 2)
      //      //         i = 0;*/
      //   }

      //}


      ::estatus     in::in_reset()
      {

         single_lock sLock(mutex(), TRUE);

         m_bResetting = true;

         //if(m_hwavein == nullptr)
         //{

         //   return ::success;

         //}

         //::estatus     estatus;

         //if(m_estate == state_recording)
         //{

         //   if(::success != (estatus = in_stop()))
         //   {

         //      TRACE("in::Reset error stopping input device");

         //      return estatus;

         //   }

         //}


         //try
         //{

         //   if(::success != (estatus = xaudio::translate(waveInReset(m_hwavein))))
         //   {
         //
         //      TRACE("in::Reset error resetting input device");

         //      return estatus;

         //   }

         //}
         //catch(...)
         //{
         //}

         //m_estate = state_opened;

         m_bResetting = false;

         return ::success;

      }


      void in::translate_in_message(::message::message * pmessage)
      {

         SCAST_PTR(::message::base, pbase, pmessage);

         //ASSERT(pbase->m_id == MM_WIM_OPEN || pbase->m_id == MM_WIM_CLOSE || pbase->m_id == MM_WIM_DATA);

         //if(pbase->m_id == MM_WIM_DATA)
         //{
         //
         //   m_iBuffer--;
         //
         //   u32 msSampleTime = timeGetTime();
         //
         //   LPWAVEHDR lpwavehdr = (LPWAVEHDR) pbase->m_lparam.m_lparam;

         //   in_get_buffer()->get_buffer((i32) lpwavehdr->dwUser)->OnMultimediaDone();

         //   m_listenerset.in_data_proc(this, msSampleTime, (i32) lpwavehdr->dwUser);

         //   if(m_pencoder != nullptr)
         //   {
         //      m_pencoder->EncoderWriteBuffer(lpwavehdr->lpData, lpwavehdr->dwBytesRecorded);
         //   }

         //   if(!in_is_resetting() && in_is_recording())
         //   {
         //      in_add_buffer((i32) lpwavehdr->dwUser);
         //   }

         //}

         pbase->m_bRet = true;

      }


      ::estatus     in::in_add_buffer(i32 iBuffer)
      {

         //return in_add_buffer(wave_hdr(iBuffer));

         return ::success;

      }


      //::estatus     in::in_add_buffer(LPWAVEHDR lpwavehdr)
      //{

      //   ::estatus     estatus;

      //   if(::success != (estatus = xaudio::translate(waveInAddBuffer(m_hwavein, lpwavehdr, sizeof(WAVEHDR)))))
      //   {

      //      TRACE("ERROR OPENING Adding INPUT DEVICE buffer");

      //   }

      //   m_iBuffer++;

      //   return estatus;

      //}


      bool in::in_initialize_encoder()
      {

         if(m_pencoder == nullptr)
            return false;

         if(!::wave::in::in_initialize_encoder())
            return false;

         return true;

      }

      WAVEFORMATEX * in::wave_format()
      {

         xaudio::translate(m_waveformatex, m_pwaveformat);

         return &m_waveformatex;

      }

      //HWAVEIN in::in_get_safe_HWAVEIN()
      //{
      //
      //   if(this == nullptr)
      //      return nullptr;

      //   return m_hwavein;

      //}

      void * in::get_os_data()
      {

         //return m_hwavein;

         return nullptr;
      }


      //LPWAVEHDR in::wave_hdr(int iBuffer)
      //{

      //   return ::multimedia::xaudio::get_os_data(in_get_buffer(), iBuffer);

      //}


   } // namespace audio_xaudio


} // namespace multimedia






