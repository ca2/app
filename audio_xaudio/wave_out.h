#pragma once


namespace multimedia
{


   namespace audio_xaudio
   {


      class  CLASS_DECL_AUDIO_XAUDIO out :
         virtual public ::wave::out,
         virtual public IXAudio2VoiceCallback
      {
      public:


         
         // Called when the voice has just finished playing a contiguous audio stream.
         STDMETHOD_(void,OnStreamEnd());

         // Unused methods in this application
         STDMETHOD_(void,OnVoiceProcessingPassEnd());
         STDMETHOD_(void,OnVoiceProcessingPassStart(UINT32 SamplesRequired)) ;
         STDMETHOD_(void,OnBufferEnd(void * pBufferContext))  ;
         STDMETHOD_(void,OnBufferStart(void * pBufferContext));
         STDMETHOD_(void,OnLoopEnd(void * pBufferContext));
         STDMETHOD_(void,OnVoiceError(void * pBufferContext,HRESULT Error));
         //class run_step_thread :
         //   virtual public ::thread
         //{
         //public:

         //   out * m_pout;

         //   run_step_thread(out * pout);

         //   virtual i32 run();

         //};

         ::comptr<IXAudio2>                                 m_pxaudio;
         IXAudio2MasteringVoice *                           m_pvoice;
         IXAudio2SourceVoice *                              m_psourcevoice;

//         run_step_thread *                m_prunstepthread;

         tick                             m_tickLastBuffer;
         int                              m_iBuffer;

         WAVEFORMATEX                     m_waveformatex;



         out();
         virtual ~out();


         ::estatus     out_start(const imedia_time & position);
         //virtual bool  on_run_step();
         void install_message_routing(::channel * pchannel);

         virtual imedia_time out_get_time() override;
         virtual void out_filled(index iBuffer) override;
         //virtual void out_buffer_ready(LPWAVEHDR lpwavehdr);

//         virtual ::estatus     out_open(::thread * pthreadCallback, ::count iBufferCount, ::count iBufferSampleCount) override;
         virtual ::estatus     out_open_ex(::thread * pthreadCallback, u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitsPerSample,::wave::e_purpose epurpose) override;
         virtual ::estatus     out_stop() override;
         virtual ::estatus     out_close() override;
         virtual ::estatus     out_pause() override;
         virtual ::estatus     out_restart() override;
         virtual void * get_os_data();
         //HWAVEOUT out_get_safe_HWAVEOUT();

         virtual void out_on_playback_end() override;
         virtual void out_free(index iBuffer) override;
         //virtual void out_free(LPWAVEHDR lpwavehdr);

         virtual ::estatus init_thread() override;
         //virtual i32 exit_instance();

         ::count out_get_buffered_buffer_count() override;

         //virtual i32 run();

         //DECL_GEN_SIGNAL(OnMultimediaOpen);
         //DECL_GEN_SIGNAL(OnMultimediaDone);
         //DECL_GEN_SIGNAL(OnMultimediaClose);

//         virtual void out_out_buffer_done(int iBuffer);
         //       virtual void out_out_buffer_done(LPWAVEHDR lpwavehdr);

         WAVEFORMATEX * wave_format();
         //LPWAVEHDR wave_hdr(int iBuffer);
         //virtual void out_run_step();
         virtual void out_prebuffer_eof() override;

      };


   } // namespace audio_xaudio


} // namespace multimedia



