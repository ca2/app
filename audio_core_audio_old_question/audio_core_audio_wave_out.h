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
         i32                                   m_iBufferCount;
         i32                                   m_iBufferSampleCount;


         out(::layered * pobjectContext);
         virtual ~out();


         void install_message_routing(::channel * pchannel) override;

         virtual imedia_time out_get_position_millis() override;
         imedia_position out_get_position() override;
         virtual void out_buffer_ready(int iBuffer);

         virtual ::estatus     out_open(::thread * pthreadCallback, i32 iBufferCount, i32 iBufferSampleCount);
         virtual ::estatus     out_open_ex(::thread * pthreadCallback, i32 iBufferCount, i32 iBufferSampleCount, u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitsPerSample, ::audio::e_purpose epurpose);
         virtual ::estatus     out_stop() override;
         virtual ::estatus     out_close() override;
         virtual ::estatus     out_pause() override;
         virtual ::estatus     out_restart() override;
         virtual void * get_os_data();
         AudioQueueRef out_get_safe_AudioQueueRef();

         ::estatus     out_start(const imedia_position & position) override;


         virtual void out_on_playback_end() override;

         virtual bool initialize_thread() override;
         virtual i32 exit_thread() override;


         void AudioQueueBufferCallback(AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer);

         //int run();


         virtual bool on_run_step();


         void OnOpen();

      } ;


   } // namespace audio_core_audio


} // namespace multimedia



