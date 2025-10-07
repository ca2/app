// Created by camilo on 2022-05-08 19:00:00 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "conversation.h"


void conversation::initialize_conversation(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::::user::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
{


}


void conversation::do_conversation(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::::user::e_message_box& emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
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


::::user::e_message_box conversation::get_conversation_flags()
{

   return ::user::e_message_box_ok;

}


::string conversation::get_conversation_details()
{

   return "";

}


::payload conversation::get_conversation_result()
{

   return {};

}


void conversation::display_conversation_options()
{

}


void conversation::run()
{

   display_conversation_options();

}


void conversation::complete_step(::sequencer & sequencer)
{

   auto payloadResult = get_conversation_result();

   sequencer.add_result(payloadResult);

}


//
//
//::payload conversation::do_synchronously(const class time & timeWait)
//{
//   
//   return ::user::e_message_box_ok;
//   
//}
//
//
//void conversation::do_asynchronously()
//{
//
//}



