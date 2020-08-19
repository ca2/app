#include "framework.h"


//namespace user
//{
//
//
//   LRESULT message::send()
//   {
//
//      try
//      {
//
//         if (m_uiMessage == message_post_user && m_wparam == 1)
//         {
//
//            __pointer(::message::base) pbase(m_lparam);
//
//            return m_puserinteraction->send(pbase);
//
//         }
//
//         return m_puserinteraction->send_message(m_uiMessage, m_wparam, m_lparam);
//
//      }
//      catch (...)
//      {
//
//      }
//
//      return 0;
//
//   }
//
//
//   ::estatus     message::ThreadProcSendMessage(LPVOID point)

//   {
//
//      message * pmessage = (message *)point;

//
//      pmessage->send();
//
//      delete pmessage;
//
//      return ::success;
//
//   }
//
//   void message::post(__pointer(::user::interaction) puie, UINT uiMessage, WPARAM wparam, LPARAM lparam, ::e_priority epriority)

//   {
//      message * pmessage = new message;
//      pmessage->m_puserinteraction = puie;
//      pmessage->m_uiMessage = uiMessage;
//      pmessage->m_wparam = wparam;
//      pmessage->m_lparam = lparam;

//      ::begin_thread(puie->get_context_application(), &ThreadProcSendMessage, pmessage, epriority);
//   }
//
//}
//
//
//
