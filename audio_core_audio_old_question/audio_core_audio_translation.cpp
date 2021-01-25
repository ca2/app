#include "framework.h"


namespace multimedia
{


   namespace audio_core_audio
   {


      void translate(AudioStreamBasicDescription & waveformatex, ::wave::format * pwaveformat)
      {

         __zero(waveformatex);
         waveformatex.mReserved         = 0;
         FillOutASBDForLPCM (
         waveformatex,
         (Float64) pwaveformat->nSamplesPerSec,
         pwaveformat->nChannels,
         8 * sizeof(::audio::WAVEBUFFERDATA),
         8 * sizeof(::audio::WAVEBUFFERDATA),
         false,
         false);


         /*         waveformatex.mSampleRate       = (Float64) ;
                  waveformatex.mFormatID         = kAudioFormatLinearPCM;
                  waveformatex.mFormatFlags      = kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked | kAudioFormatFlagsNativeEndian;
                  waveformatex.mChannelsPerFrame = ;
                  waveformatex.mBytesPerFrame    = waveformatex.mChannelsPerFrame * sizeof(::audio::WAVEBUFFERDATA);
                  waveformatex.mFramesPerPacket  = 1;
                  waveformatex.mBytesPerPacket   = waveformatex.mBytesPerFrame * waveformatex.mFramesPerPacket;
                  waveformatex.mBitsPerChannel   = 8 * sizeof(::audio::WAVEBUFFERDATA);
                  waveformatex.mReserved         = 0;

          */
      }


      ::e_status     translate(OSStatus status)
      {

         switch(status)
         {
         case 0:
            return ::success;

         case kAudioFormatUnsupportedDataFormatError:
            return ::multimedia::result_bad_format;

         default:
            return error_failed;

         };

      }


      /*

      void translate(WAVEHDR & wavehdr, ::wave::buffer * pwavebuffer, int iBuffer)
      {

         ::wave::buffer::item * pbuffer = pwavebuffer->get_buffer(iBuffer);

         pbuffer->m_posdata            = &wavehdr;

         wavehdr.lpData                = (char *) pbuffer->m_pData;
         wavehdr.dwBufferLength        = pwavebuffer->m_uiBufferSize;
         wavehdr.dwBytesRecorded       = 0;
         wavehdr.dwUser                = pbuffer->m_iIndex;
         wavehdr.dwFlags               = 0;

      }


      LPWAVEHDR create_new_WAVEHDR(::wave::buffer * pwavebuffer, int iBuffer)
      {

         LPWAVEHDR lpwavehdr = new WAVEHDR;

         translate(*lpwavehdr, pwavebuffer, iBuffer);

         return lpwavehdr;

      }

      LPWAVEHDR get_os_data(::wave::buffer * pwavebuffer, int iBuffer)
      {

         ::wave::buffer::item * pbuffer = pwavebuffer->get_buffer(iBuffer);

         LPWAVEHDR pwavehdr = (LPWAVEHDR) pbuffer->get_os_data();

         return pwavehdr;

      }

      */


   } // namespace audio_core_audio


} // namespace multimedia




