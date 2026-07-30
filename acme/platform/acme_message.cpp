//
// Created by camilo on 2025-01-08 22:42 BRT <3ThomasBS_!!
//
#include "framework.h"
#include "message.h"


namespace acme
{


   message& message::operator = (const ::acme::message& message)
   {

      if (this != &message)
      {

         ::property_object::operator=(message);

         m_union = message.m_union;

         m_time = message.m_time;
         m_iTimestamp = message.m_iTimestamp;
         m_pointMessage = message.m_pointMessage;
         m_eusermessage = message.m_eusermessage;
         m_wparam = message.m_wparam;
         m_lparam = message.m_lparam;
         m_lresult = message.m_lresult;
         m_bRet = message.m_bRet;

      }

      return *this;

   }

     
   ::user::activation_token *message::user_activation_token() 
   { 
         
      return nullptr; 
      
   }


} // namespace acme



