#include "framework.h"
#include "aura/user/_user.h"


#ifdef WINDOWS_DESKTOP


namespace user
{


   message_window::message_window()
   {

      m_plistener          = nullptr;

   }


   message_window::~message_window()
   {

   }


   bool message_window::create_message_window(const char * pszName,::user::message_window_listener * plistener)
   {

      m_plistener = plistener;

      if (!::user::interaction::create_message_window(pszName))
      {

         return false;

      }

      if (m_plistener)
      {

         m_plistener->install_message_window_routing(this);

      }

      return true;



   }


   void message_window::message_handler(::user::message * pusermessage)
   {

      message_window_message_handler(pusermessage);

      if (pusermessage->m_bRet)
      {

         return;

      }

      ::user::interaction::message_handler(pusermessage);

   }


   void message_window::message_window_message_handler(::message::message * pmessage)
   {

      if(m_plistener != nullptr)
      {

         m_plistener->message_window_message_handler(pmessage);

      }

   }


   bool message_window::message_window_is_initialized()
   {

      return is_window();

   }


   bool message_window::message_window_set_timer(uptr uId,::u32 dwMillis)
   {

      return SetTimer(uId,dwMillis,nullptr) != false;

   }

   bool message_window::message_window_del_timer(uptr uId)
   {

      return KillTimer(uId) != false;

   }

   bool message_window::message_window_post_message(const ::id & id,wparam wparam,lparam lparam)
   {

      return post_message(id, wparam, lparam);

   }


   lresult message_window::message_window_send_message(const ::id& id,wparam wparam,lparam lparam)
   {

      return send_message(id, wparam, lparam);

   }


   bool message_window::message_window_destroy()
   {

      return DestroyWindow() != false;

   }


   void * message_window::message_window_get_os_handle()
   {

      return get_os_data();

   }


} // namespace user


#endif




