//
//  conversation_message.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 01/Oct/22. 00:59
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#include "framework.h"
#include "conversation_message.h"


namespace acme
{


   ::pointer<::conversation>node::create_new_message_conversation()
   {
   
      return __create_new < ::conversation_message >();
   
   }


} // namespace acme


::string conversation_message::get_conversation_message()
{

   return m_strMessage;

}


::string conversation_message::get_conversation_title()
{

   return m_strTitle;

}


::e_message_box conversation_message::get_conversation_flags()
{

   return m_emessagebox;

}


::string conversation_message::get_conversation_details()
{

   return m_strDetails;

}


void conversation_message::initialize_conversation(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails)
{

   m_strMessage = strMessage;

   m_strTitle = strTitle;

   m_emessagebox = emessagebox;

   m_strDetails = strDetails;

}


::payload conversation_message::do_synchronously(const class ::wait & wait)
{
   
   do_asynchronously();

   return e_dialog_result_none;
   
}


void conversation_message::do_asynchronously()
{
   
   auto pstringbuffer = __new(string_buffer);
   
   text_stream textstream(pstringbuffer);
   
   textstream << "Title:   " << m_strTitle << "\n";
   textstream << "Message: " << m_strMessage << "\n";
   textstream << "Flags:   " << (iptr) m_emessagebox << "\n";
   textstream << "Details:\n";
   textstream << m_strDetails << "\n";
   
   output_debug_string(pstringbuffer->m_str);
   
}

