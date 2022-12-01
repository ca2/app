#pragma once


namespace programming
{


   class CLASS_DECL_CORE application :
      virtual public ::aura::application
   {
   public:


///      semaphore                     m_semCompiler;
      //      script_manager *                            m_pmanager;


      application();
      ~application() override;


      DECLARE_MESSAGE_HANDLER(on_application_signal);


      void on_request(::request * prequest) override;


      string get_visual_studio_build();


   };


} // namespace html





