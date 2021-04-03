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


         ::u32                                    m_NumPacketsToRead;
         array < AudioStreamPacketDescription * >  m_PacketDescs;
         bool                                      m_bDone;
         i32                                   m_iBufferCount;
         i32                                   m_iBufferSampleCount;


         out(::object * pobject);
         virtual ~out();


         void install_message_routing(::channel * pchannel) override;

         virtual imedia_time out_get_time() override;
         imedia_time out_get_time() override;
         virtual void out_buffer_ready(int iBuffer);

         virtual ::e_status     out_open(::thread * pthreadCallback, i32 iBufferCount, i32 iBufferSampleCount);
         virtual ::e_status     out_open_ex(::thread * pthreadCallback, i32 iBufferCount, i32 iBufferSampleCount, u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitsPerSample, ::audio::e_purpose epurpose);
         virtual ::e_status     out_stop() override;
         virtual ::e_status     out_close() override;
         virtual ::e_status     out_pause() override;
         virtual ::e_status     out_restart() override;
         virtual void * get_os_data();
         AudioQueueRef out_get_safe_AudioQueueRef();

         ::e_status     out_start(const imedia_time & position) override;


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



