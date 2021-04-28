#pragma once


namespace userpresence
{


   class CLASS_DECL_CORE department :
      virtual public ::acme::department,
      virtual public ::acme::timer_array
   {
   public:


      bool                       m_bUserPresenceFeatureRequired;
      bool                       m_bInit;
      __pointer(presence)        m_ppresence;


      department();
      virtual ~department();


      virtual ::e_status initialize(::object * pobject) override;
      virtual ::e_status finalize() override;


      virtual bool defer_initialize_user_presence();
      virtual bool defer_finalize_user_presence();


      virtual void message_queue_message_handler(::message::message * pmessage);

      virtual bool is_initialized();

      virtual void _001OnTimer(::timer * ptimer) override;


      bool on_ui_mouse_message(::user::mouse * pmouse);


   };


} // namespace userpresence



