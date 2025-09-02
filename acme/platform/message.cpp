//
// Created by camilo on 2025-08-31 02:17 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "message.h"


namespace platform
{


   message::message()
   {

      m_emessage = ::e_message_none;
      m_llWparam = 0;
      m_llLparam = 0;

   }


   message::~message()
   {


   }


   void message::initialize_message(enum_message emessage, long long llWparam,
                                                long long llLparam, const ::block &block)
   {

      m_emessage = emessage;
      m_llWparam = llWparam;
      m_llLparam = llLparam;
      m_memory = block;

   }


} // platform



