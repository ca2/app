// Created by camilo on 2022-05-08 18:24 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "message_box.h"


micro_message_box::micro_message_box()
{
    

}


micro_message_box::~micro_message_box()
{


}


void micro_message_box::do_message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::::user::e_message_box& emessagebox)
{

   m_psequence->m_p->do_message_box(strMessage, strTitle, emessagebox);

}




