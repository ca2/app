#include "framework.h" // from "axis/user/user.h"
#include "macos.h"


namespace macos
{


   message_queue::message_queue(::object * pobject):
      ::object(pobject),
      ::user::message_queue(pobject)
   {

      m_plistener          = NULL;

   }


   message_queue::~message_queue()
   {

   }


   bool message_queue::create_message_queue(const char * pszName,::user::message_queue_listener * plistener)
   {

      if(!::user::message_queue::create_message_queue(pszName,plistener))
         return true;

      return ::user::interaction::create_message_queue(pszName);

   }


   void message_queue::message_handler(::message::base * pbase)
   {

      message_queue_message_handler(pbase);

      if(pbase->m_bRet)
         return;

      ::user::interaction::message_handler(pbase);

   }


   void message_queue::message_queue_message_handler(::message::message * pmessage)
   {

      if(m_plistener != NULL)
      {

         m_plistener->message_queue_message_handler(pmessage);

      }

   }


   bool message_queue::message_queue_is_initialized()
   {

      return IsWindow();

   }


   bool message_queue::message_queue_set_timer(uptr uiId,DWORD dwMillis)
   {

      return SetTimer(uiId,dwMillis,NULL) != FALSE;

   }

   bool message_queue::message_queue_del_timer(uptr uiId)
   {

      return KillTimer(uiId) != FALSE;

   }

   bool message_queue::message_queue_post_message(u32 uiMessage,WPARAM wparam,lparam lparam)
   {

      return post_message(uiMessage,wparam,lparam);

   }

   LRESULT message_queue::message_queue_send_message(u32 uiMessage,WPARAM wparam,lparam lparam)
   {

      return send_message(uiMessage,wparam,lparam);

   }

   bool message_queue::message_queue_destroy()
   {

      return DestroyWindow();

   }


   void * message_queue::message_queue_get_os_handle()
   {

      return get_os_data();

   }


} // namespace windows




































