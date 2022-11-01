#pragma once


#include "apex/message/message.h"


class form_document;


namespace html
{


   class message :
      public ::message::message
   {
   public:


      ::pointer<::html_data>              m_phtmldata;
      ::pointer<::message::message>       m_pmessage;
      ::pointer<::user::interaction>      m_puserinteraction;


      message();


   };


} // namespace html






