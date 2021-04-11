#pragma once


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM thread :
         public ::thread,
         public ::database::client
      {
      public:


         enum e_message
         {
            MessageMixerThread = WM_USER + 113,
         };

         bool                                m_bPendingShowCommand;

         __pointer(::multimedia::audio_mixer::department) m_psection;


         thread(__pointer(base_application) papp);
         virtual ~thread();


         static LRESULT CALLBACK MessageProc(
            i32 code,       // hook code
            WPARAM wParam,  // undefined
            LPARAM lParam   // address of structure with message data
            );


         void install_message_routing(::channel * pchannel);

         virtual bool initialize_thread() override;
         virtual i32 exit_instance();
         virtual bool on_idle(::i32 lCount);
         virtual void pre_translate_message(::message::message * pmessage);


         DECLARE_MESSAGE_HANDLER(OnMixerMessage)
            DECLARE_MESSAGE_HANDLER(OnVmsmException)
            DECLARE_MESSAGE_HANDLER(OnUserMessage)


      };


   } // namespace audio_mixer_mmsystem


} // namespace multimedia





