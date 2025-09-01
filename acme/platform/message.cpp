//
// Created by camilo on 2025-08-31 02:17 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "application_message.h"

//
//namespace platform
//{


   application_message::application_message()
   {

      m_eapplicationmessage = e_application_message_none;
      m_llWparam = 0;
      m_llLparam = 0;

   }


   application_message::~application_message()
   {


   }


   void application_message::initialize_application_message(enum_application_message eapplicationmessage, long long llWparam, long long llLparam, const ::block & block)
   {

      m_eapplicationmessage = eapplicationmessage;
      m_llWparam = llWparam;
      m_llLparam = llLparam;
      m_memory = block;

   }
//
//} // platform