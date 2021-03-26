#include "framework.h"


namespace net
{


   email::email()
   {

   }


   email::~email()
   {


   }


   ::e_status email::initialize(::object * pobject)
   {

      auto estatus = ::object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void email::prepare_headers()
   {

      auto psystem = m_psystem->m_papexsystem;

      m_strHeaders += "From: =?utf-8?B?" + psystem->m_papexsystem->base64().encode(m_strSenderName) + "?= <" + m_addressSender.to_string() + ">\r\n";
      m_strHeaders += "To: =?utf-8?B?" + psystem->m_papexsystem->base64().encode(m_strRecipientName) + "?= <" + m_addressRecipient.to_string() + ">\r\n";

   }


} // namespace net




