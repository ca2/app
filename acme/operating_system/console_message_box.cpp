// Created by camilo on 2024-08-09 14:34 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "console_message_box.h"


namespace operating_system
{


   console_message_box::console_message_box()
   {


   }


   console_message_box::~console_message_box()
   {


   }


   ::payload console_message_box::do_synchronously(const class time & timeWait)
   {

      return message_box_for_console(m_strMessage, m_strTitle, m_emessagebox);

   }


} // namespace operating_system



