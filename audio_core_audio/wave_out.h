#pragma once


namespace multimedia
{


   namespace audio_core_audio
   {


      class  CLASS_DECL_AUDIO_CORE_AUDIO out :
         virtual public toolbox,
         virtual public ::wave::out
      {
      public:


         UInt32                                    m_NumPacketsToRead;
         array < AudioStreamPacketDescription * >  m_PacketDescs;
         bool                                      m_bDone;
         iptr                                   m_iBufferCount;
         iptr                                   m_iBufferSampleCount;


         out();
         virtual ~out();


         void install_message_routing(::channel * pchannel) override;

         virtual imedia_time out_get_time() override;
         imedia_time out_get_time() override;
         virtual void out_filled(index iBuffer) override;

         virtual ::estatus     out_open_ex(::thread * pthreadCallback, u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitsPerSample, ::wave::e_purpose epurpose) override;
         virtual ::estatus     out_stop() override;
         virtual ::estatus     out_close() override;
         virtual ::estatus     out_pause() override;
         virtual ::estatus     out_restart() override;
         virtual void * get_os_data();
         AudioQueueRef out_get_safe_AudioQueueRef();

         virtual ::estatus     _out_start();

         ::estatus     out_start(const imedia_time & position) override;


         virtual void out_on_playback_end() override;

         virtual ::estatus init_thread() override;
         virtual void term_thread() override;


         void AudioQueueBufferCallback(AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer);


         virtual bool on_run_step();


//         void OnOpen();

      };


   } // namespace audio_core_audio


} // namespace multimedia



