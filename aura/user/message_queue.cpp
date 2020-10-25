#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


namespace user
{


   message_queue::message_queue()
   {

      m_plistener          = nullptr;

   }


   message_queue::~message_queue()
   {

   }


   bool message_queue::create_message_queue(const char * pszName,::user::message_queue_listener * plistener)
   {

      m_plistener = plistener;

      if (!::user::interaction::create_message_queue(pszName))
      {

         return false;

      }

      m_plistener->install_message_queue_routing(this);

      return true;



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

      if(m_plistener != nullptr)
      {

         m_plistener->message_queue_message_handler(pmessage);

      }

   }


   bool message_queue::message_queue_is_initialized()
   {

      return is_window();

   }


   bool message_queue::message_queue_set_timer(uptr uiId,DWORD dwMillis)
   {

      return SetTimer(uiId,dwMillis,nullptr) != FALSE;

   }

   bool message_queue::message_queue_del_timer(uptr uiId)
   {

      return KillTimer(uiId) != FALSE;

   }

   bool message_queue::message_queue_post_message(const ::id & id,WPARAM wparam,lparam lparam)
   {

      return post_message(id, wparam, lparam);

   }


   LRESULT message_queue::message_queue_send_message(const ::id& id,WPARAM wparam,lparam lparam)
   {

      return send_message(id, wparam, lparam);

   }


   bool message_queue::message_queue_destroy()
   {

      return DestroyWindow() != FALSE;

   }


   void * message_queue::message_queue_get_os_handle()
   {

      return get_os_data();

   }


} // namespace user



