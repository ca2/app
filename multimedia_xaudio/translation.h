#pragma once


namespace multimedia
{


   namespace xaudio
   {


      CLASS_DECL_MULTIMEDIA_XAUDIO void translate(WAVEFORMATEX & formatex, ::wave::format * pwaveformat);
//      CLASS_DECL_MULTIMEDIA_XAUDIO void translate(WAVEHDR & wavehdr, ::wave::buffer * pwavebuffer, int iIndex);
      //    CLASS_DECL_MULTIMEDIA_XAUDIO LPWAVEHDR create_new_WAVEHDR(::wave::buffer * pwavebuffer, int iIndex);
      //  CLASS_DECL_MULTIMEDIA_XAUDIO LPWAVEHDR get_os_data(::wave::buffer * pwavebuffer, int iIndex);


      CLASS_DECL_MULTIMEDIA_XAUDIO ::e_status     translate(HRESULT mmr);


   } // namespace xaudio


} // namespace multimedia





