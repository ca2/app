// Created by camilo on 2022-05-08 18:24 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "message_box.h"


micro_message_box::micro_message_box()
{


}


micro_message_box::~micro_message_box()
{


}


void micro_message_box::do_message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox)
{

   m_psequence->m_p->do_message_box(strMessage, strTitle, emessagebox);

}


namespace aura
{


   __pointer(::conversation) node::create_new_message_box_conversation()
   {

      return __new(::micro_message_box());

   }


} // namespace aura



