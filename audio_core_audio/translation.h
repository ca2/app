#pragma once


namespace multimedia
{


   namespace audio_core_audio
   {



      void translate(AudioStreamBasicDescription & formatex, ::wave::format * pwaveformat);
      ::estatus     translate(OSStatus status);

      /*

            void translate(WAVEHDR & wavehdr, ::wave::buffer * pwavebuffer, int iIndex);
            LPWAVEHDR create_new_WAVEHDR(::wave::buffer * pwavebuffer, int iIndex);
            LPWAVEHDR get_os_data(::wave::buffer * pwavebuffer, int iIndex);

      */


   } // namespace audio_core_audio


} // namespace multimedia





