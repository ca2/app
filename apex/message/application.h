#pragma once


namespace message
{


   enum e_application
   {

      application_none,
      application_process_init,
      application_init1, // first initialization
      application_init2, // second initialization
      application_init3, // third initialization and so on...
      application_init, // last initialization
      application_init_instance,
      application_begin,
      application_end,
      application_term_instance,
      application_term, // from on and so, to...
      application_term3, // first finalization
      application_term2, // second finalization
      application_term1, // third finalization
      application_process_term

   };


   class CLASS_DECL_APEX application :
      public ::message::message
   {
   public:


      e_application              m_eapplication;
      i32                        m_iRet;
      bool                       m_bOk;


      application(e_application eapplication);


   };


} // namespace message



