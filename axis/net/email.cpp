#include "framework.h"


namespace net
{


   email::email()
   {

   }


   email::~email()
   {


   }


   ::estatus email::initialize(::object * pobjectContext)
   {

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void email::prepare_headers()
   {

      m_strHeaders += "From: =?utf-8?B?" + System.base64().encode(m_strSenderName) + "?= <" + m_addressSender.to_string() + ">\r\n";
      m_strHeaders += "To: =?utf-8?B?" + System.base64().encode(m_strRecipientName) + "?= <" + m_addressRecipient.to_string() + ">\r\n";

   }


} // namespace net




