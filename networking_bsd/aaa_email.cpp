#include "framework.h"
#include "acme/prototype/string/base64.h"


namespace net
{


   email::email()
   {

   }


   email::~email()
   {


   }


   void email::initialize(::particle * pparticle)
   {

      //auto estatus = ::object::initialize(pparticle);

      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void email::prepare_headers()
   {

      auto psystem = system();

      auto pbase64 = psystem->base64();

      m_strHeaders += "From: =?utf-8?B?" + pbase64->encode(m_strSenderName) + "?= <" + m_addressSender.to_string() + ">\r\n";
      m_strHeaders += "To: =?utf-8?B?" + pbase64->encode(m_strRecipientName) + "?= <" + m_addressRecipient.to_string() + ">\r\n";

   }


} // namespace net




