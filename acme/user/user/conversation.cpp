// Created by camilo on 2022-05-08 19:00:00 <3ThomasBorregaardS�rensen!!
#include "framework.h"
#include "conversation.h"


void conversation::initialize_conversation(const ::string & strMessage, const string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails)
{


}


void conversation::do_conversation(const ::string& strMessage, const string& strTitle, const ::e_message_box& emessagebox, const ::string & strDetails)
{


}


::string conversation::get_conversation_message()
{

   return "";

}


::string conversation::get_conversation_title()
{

   return "";

}


::e_message_box conversation::get_conversation_flags()
{

   return e_message_box_ok;

}


::string conversation::get_conversation_details()
{

   return "";

}


::payload conversation::do_synchronously(const class ::wait & wait)
{
   
   return e_message_box_ok;
   
}


void conversation::do_asynchronously()
{

}



