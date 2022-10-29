#include "framework.h"
#include "apex/message/channel.h"


namespace message
{

   class ::channel * CreateSignal()
   {
      return memory_new class ::channel();
   }



//
//
//   CLASS_DECL_AURA bool is_idle_message(::message::message * pmessage)
//   {
//
//      ::pointer<::user::message>pusermessage(pmessage);
//
//      // Return false if the message just dispatched should _not_
//      // cause on_idle to be run.  Messages which do not usually
//      // affect the state of the ::account::user interface and happen very
//      // often are checked for.
//
//      if(pusermessage == nullptr)
//         return false;
//
//      // redundant e_message_mouse_move and e_message_non_client_mouse_move
//      if(pusermessage->is_message() && (pusermessage->m_atom == e_message_mouse_move || pusermessage->m_atom == e_message_non_client_mouse_move))
//      {
//         return true;
//      }
//
//      // e_message_paint and WM_SYSTIMER (caret blink)
//      return pusermessage->m_atom != e_message_paint && pusermessage->m_atom != 0x0118;
//
//   }
//
//
//
//   CLASS_DECL_AURA bool is_idle_message(MESSAGE * pmsg)
//
//   {
//
//      // Return false if the message just dispatched should _not_
//      // cause on_idle to be run.  Messages which do not usually
//      // affect the state of the ::account::user interface and happen very
//      // often are checked for.
//
//      if(pmsg == nullptr)
//
//         return false;
//
//      // redundant e_message_mouse_move and e_message_non_client_mouse_move
//      if(pmsg->message == e_message_mouse_move || pmsg->message == e_message_non_client_mouse_move)
//
//      {
//         return true;
//      }
//
//      // e_message_paint and WM_SYSTIMER (caret blink)
//      return pmsg->message != e_message_paint && pmsg->message != 0x0118;
//
//
//   }


} // namespace message



