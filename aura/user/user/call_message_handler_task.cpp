// Created By Camilo 2020-12-27 21:59 BRT <3ThomasBS, Mummi and bilbo!!
// twitch streams... twitch chatting...
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
////#include "aura/user/user/_component.h"
#endif
#include "call_message_handler_task.h"
#include "interaction.h"


namespace user
{


   call_message_handler_task::call_message_handler_task(interaction * pinteraction, const ::atom & atom, wparam wparam, lparam lparam) :
      m_atom(atom),
      m_pinteraction(pinteraction),
      m_wparam(wparam),
      m_lparam(lparam)
   {

   }

   call_message_handler_task::~call_message_handler_task()
   {

   }


   void call_message_handler_task::run()
   {

      m_pinteraction->call_message_handler(m_atom, m_wparam, m_lparam);

      //return ::success;

   }


} // namespace user



