#pragma once


#include "acme/platform/timer_array.h"


namespace userpresence
{


   class CLASS_DECL_CORE department :
      virtual public ::acme::department,
      virtual public ::acme::timer_array
   {
   public:


      bool                       m_bUserPresenceFeatureRequired;
      bool                       m_bInit;
      ::pointer<presence>       m_ppresence;


      department();
      ~department() override;


      void initialize(::object * pobject) override;
      void destroy() override;


      virtual bool defer_initialize_user_presence();
      virtual bool defer_finalize_user_presence();


      virtual void message_queue_message_handler(::message::message * pmessage);

      virtual bool is_initialized();

      void _001OnTimer(::timer * ptimer) override;


      bool on_ui_mouse_message(::user::mouse * pmouse);


   };


} // namespace userpresence



