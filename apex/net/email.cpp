#include "framework.h"


namespace net
{


   email::email()
   {

   }


   email::~email()
   {


   }


   ::e_status email::initialize(::context_object * pcontextobject)
   {

      auto estatus = ::object::initialize(pcontextobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void email::prepare_headers()
   {

      auto psystem = get_system();

      m_strHeaders += "From: =?utf-8?B?" + psystem->base64().encode(m_strSenderName) + "?= <" + m_addressSender.to_string() + ">\r\n";
      m_strHeaders += "To: =?utf-8?B?" + psystem->base64().encode(m_strRecipientName) + "?= <" + m_addressRecipient.to_string() + ">\r\n";

   }


} // namespace net




