#include "framework.h"
//#include "aura/user/_user.h"


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


   void message_window::create_message_window(const ::string & pszName,::user::message_window_listener * plistener)
   {

      m_plistener = plistener;

      m_bMessageWindow = true;

      m_strWindowText = pszName;

      create_host();

      //if (!create_host())
      //{

      //   return false;

      //}

      if (m_plistener)
      {

         m_plistener->install_message_window_routing(this);

      }

      //return true;



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


   void message_window::message_window_set_timer(uptr uId, const ::duration & duration)
   {

      SetTimer(uId, duration, nullptr);

   }


   void message_window::message_window_del_timer(uptr uId)
   {

      KillTimer(uId);

   }


   void message_window::message_window_post_message(const ::atom & atom,wparam wparam,lparam lparam)
   {

      post_message(atom, wparam, lparam);

   }


   lresult message_window::message_window_send_message(const ::atom& atom,wparam wparam,lparam lparam)
   {

      return send_message(atom, wparam, lparam);

   }


   void message_window::message_window_destroy()
   {

      start_destroying_window();

   }


   void * message_window::message_window_get_os_handle()
   {

      return get_os_data();

   }


} // namespace user


#endif




