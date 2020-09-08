#pragma once



namespace apex

{


   enum e_application_message
   {

      application_message_none,
      application_message_process_init,
      application_message_init1, // first initialization
      application_message_init2, // second initialization
      application_message_init3, // third initialization and so on...
      application_message_init, // last initialization
      application_message_init_instance,
      application_message_begin,
      application_message_end,
      application_message_term_instance,
      application_message_term, // from on and so, to...
      application_message_term3, // first finalization
      application_message_term2, // second finalization
      application_message_term1, // third finalization
      application_message_process_term

   };

   class CLASS_DECL_APEX application_message:
      public ::message::message
   {
   public:


      e_application_message             m_esignal;
      i32                          m_iRet;
      bool                             m_bOk;


      application_message(e_application_message esignal);


   };


} // namespace apex
