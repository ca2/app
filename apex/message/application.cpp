#include "framework.h"
#include "acme/constant/message.h"
#include "application.h"


namespace message
{


   application::application(e_application eapplication)
   {

      m_emessage = e_message_application;
      m_eapplication = eapplication;
      m_bOk = true;

   }


} // namespace message




