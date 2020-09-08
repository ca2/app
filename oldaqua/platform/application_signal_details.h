#pragma once



namespace aqua

{


   enum e_application_message
   {

      application_message_initialize1, // first initialization
      application_message_initialize2, // second initialization
      application_message_initialize3, // third initialization and so on...
      application_message_initialize, // last initialization
      application_message_start,
      application_message_process_initialize,
      application_message_finalize,
      application_message_exit_instance,
      application_message_init_application,
      application_message_none

   };

   class CLASS_DECL_AQUA application_message:
      public ::message::message
   {
   public:


      e_application_message             m_esignal;
      i32                          m_iRet;
      bool                             m_bOk;


      application_message(class ::channel * psignal,e_application_message esignal);


   };


} // namespace aqua