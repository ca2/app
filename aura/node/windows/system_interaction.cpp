#include "framework.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "_windows.h"
//#endif
//#include "aura/message.h"
//#include "aura/procedure.h"
//#include "system_interaction.h"
//
//
//namespace user
//{
//
//
//   system_interaction::system_interaction()
//   {
//
//      m_ewindowflag -= e_window_flag_graphical;
//      //m_bMessageWindow = true;
//
//   }
//
//
//   system_interaction::~system_interaction()
//   {
//
//
//   }
//
//
//   void system_interaction::install_message_routing(::channel * pchannel)
//   {
//
//      ::user::interaction::install_message_routing(pchannel);
//
//      MESSAGE_LINK(e_message_destroy, pchannel, this, System_interaction::_001OnDestroy);
//      MESSAGE_LINK(e_message_display_change, pchannel,this,System_interaction::_001OnMessage);
//
//   }
//
//
//   bool system_interaction::is_system_message_window()
//   {
//
//      return true;
//
//   }
//
//
//   bool system_interaction::DestroyWindow()
//   {
//
//      return ::user::interaction::DestroyWindow();
//
//   }
//
//
//   void system_interaction::_001OnDestroy(::message::message * pmessage)
//   {
//
//      __pointer(::user::message) pusermessage(pmessage);
//
//      ::output_debug_string("system_interaction::_001OnDestroy");
//
//   }
//
//
//
//
//} // namespace base
//
//
//
//
