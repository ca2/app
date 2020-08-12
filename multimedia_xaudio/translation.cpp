#include "framework.h"


namespace multimedia
{


   namespace xaudio
   {


      void translate(WAVEFORMATEX & waveformatex, ::wave::format * pwaveformat)
      {


         waveformatex.wFormatTag        = pwaveformat->wFormatTag;           // format type
         waveformatex.nChannels         = pwaveformat->nChannels;            // number of channels (i.e. mono, stereo...)
         waveformatex.nSamplesPerSec    = pwaveformat->nSamplesPerSec;       // sample rate
         waveformatex.nAvgBytesPerSec   = pwaveformat->nAvgBytesPerSec;      // for buffer estimation
         waveformatex.nBlockAlign       = pwaveformat->nBlockAlign;          // block size of data
         waveformatex.wBitsPerSample    = pwaveformat->wBitsPerSample;       // number of bits per sample of mono data
         waveformatex.cbSize            = pwaveformat->cbSize;               // the count in bytes of the size of
         // extra information (after cbSize)

      }


      //void translate(WAVEHDR & wavehdr, ::wave::buffer * pwavebuffer, int iBuffer)
      //{

      //   ::wave::buffer::item * pbuffer = pwavebuffer->get_buffer(iBuffer);
      //
      //   pbuffer->m_posdata            = &wavehdr;

      //   wavehdr.lpData                = (LPSTR) pbuffer->m_pData;
      //   wavehdr.dwBufferLength        = pwavebuffer->m_uiBufferSize;
      //   wavehdr.dwBytesRecorded       = 0;
      //   wavehdr.dwUser                = pbuffer->m_iIndex;
      //   wavehdr.dwFlags               = 0;

      //}


      //LPWAVEHDR create_new_WAVEHDR(::wave::buffer * pwavebuffer, int iBuffer)
      //{

      //   LPWAVEHDR lpwavehdr = new WAVEHDR;

      //   translate(*lpwavehdr, pwavebuffer, iBuffer);

      //   return lpwavehdr;

      //}

      //LPWAVEHDR get_os_data(::wave::buffer * pwavebuffer, int iBuffer)
      //{
      //
      //   ::wave::buffer::item * pbuffer = pwavebuffer->get_buffer(iBuffer);

      //   LPWAVEHDR pwavehdr = (LPWAVEHDR) pbuffer->get_os_data();

      //   return pwavehdr;

      //}

      ::estatus     translate(HRESULT hr)
      {

         if(SUCCEEDED(hr))
            return ::success;
         else
            return error_failed;

      }


   } // namespace xaudio


} // namespace multimedia





