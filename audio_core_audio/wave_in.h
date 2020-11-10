#pragma once


namespace multimedia
{


   namespace audio_core_audio
   {


      class  CLASS_DECL_AUDIO_CORE_AUDIO in :
         virtual public toolbox,
         virtual public ::wave::in
      {
      public:


         bool                             m_bIsRunning;


         in();
         virtual ~in();


         virtual bool in_initialize_encoder() override;


         virtual ::estatus     in_add_buffer(i32 iBuffer) override;


         virtual void * get_os_data();


         AudioQueueRef in_get_safe_AudioQueueRef();


         ::estatus     in_open(i32 iBufferCount, i32 iBufferSampleCount) override;
         ::estatus     in_close() override;
         ::estatus     in_stop() override;
         ::estatus     in_start() override;
         ::estatus     in_reset() override;


         virtual ::estatus init_thread() override;
         virtual void term_thread() override;
         virtual void pre_translate_message(::message::message * pmessage) override;


         static void HandleInputBuffer(void                                 *aqData,
                                       AudioQueueRef                        inAQ,
                                       AudioQueueBufferRef                  inBuffer,
                                       const AudioTimeStamp                 *inStartTime,
                                       ::u32                               inNumPackets,
                                       const AudioStreamPacketDescription   *inPacketDesc);


         void HandleInputBuffer(AudioQueueRef                        inAQ,
                                AudioQueueBufferRef                  inBuffer,
                                const AudioTimeStamp                 *inStartTime,
                                ::u32                               inNumPackets,
                                const AudioStreamPacketDescription   *inPacketDesc);


      };


   } // namespace audio_core_audio


} // namespace multimedia




