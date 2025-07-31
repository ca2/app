//
//  conversation_message.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 01/Oct/22. 00:59
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"
#include "message_box.h"
#include "acme/handler/sequence.h"
#include "acme/platform/node.h"
//#include "acme/handler/sequence.h"
#include "acme/nano/graphics/icon.h"

//#include "acme/filesystem/file/string_buffer.h"
//#include "acme/filesystem/file/text_stream.h"


namespace acme
{


   //::pointer<::conversation>node::create_new_message_conversation()
   //{
   //
   //   return __create_new < ::conversation_message >();
   //
   //}


} // namespace acme


//::string message_box::get_conversation_message()
//{
//
//   return m_strMessage;
//
//}
//
//
//::string message_box::get_conversation_title()
//{
//
//   return m_strTitle;
//
//}
//
//
//::e_message_box message_box::get_conversation_flags()
//{
//
//   return m_emessagebox;
//
//}
//
//
//::string message_box::get_conversation_details()
//{
//
//   return m_strDetails;
//
//}


message_box::message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
{

   preempt(30_s);

   m_strMessage = strMessage;

   m_strTitle = strTitle;

   m_emessagebox = emessagebox;

   m_strDetails = strDetails;

   m_picon = picon;

}


message_box::message_box(const ::exception & exception, const ::scoped_string & scopedstrMoreDetails)
{

   preempt(30_s);

   m_strMessage = exception.m_strMessage;

   m_strTitle = exception.m_strTitle;

   if (exception.m_econsequenceUserDefault == e_consequence_fatal)
   {

      m_emessagebox = e_message_box_icon_error;

   }
   else if (exception.m_econsequenceUserDefault == e_consequence_blocking)
   {

      m_emessagebox = e_message_box_icon_exclamation;

   }
   else if (exception.m_econsequenceUserDefault == e_consequence_workaroundable)
   {

      m_emessagebox = e_message_box_ok;

   }
   else
   {

      m_emessagebox = e_message_box_icon_asterisk;

   }

   m_strDetails.concatenate_with_separator("\n", exception.m_strTitle);

   m_strDetails.concatenate_with_separator("\n", exception.m_strMessage);

   m_strDetails.concatenate_with_separator("\n", scopedstrMoreDetails);

   m_strDetails.concatenate_with_separator("\n", exception.m_strDetails);

   m_strDetails.concatenate_with_separator("\n\nCallstack:\n", exception.m_strCallStackTrace);

}



message_box::message_box(const ::exception & exception, const ::scoped_string & strMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
{

   preempt(30_s);

   m_strMessage = exception.m_strMessage;

   m_strMessage.concatenate_with_separator("\n", strMessage);

   m_strTitle = strTitle;

   m_emessagebox = emessagebox;

   m_strDetails = strDetails;

   m_strDetails.concatenate_with_separator("\n", strDetails);

   m_strDetails.concatenate_with_separator("\n\nCallstack:\n", exception.m_strCallStackTrace);

   m_picon = picon;

}


message_box::~message_box()
{


}


#ifdef _DEBUG


long long message_box::increment_reference_count()
{

   return ::particle::increment_reference_count();

}


long long message_box::decrement_reference_count()
{

   return ::particle::decrement_reference_count();

}


#endif



//void conversation_message::aggregate(sequence * psequence)
//{
//   
//   //m_psequencer->m_phappening = __create_new < manual_reset_happening >();
//
//   do_asynchronously();
//   
//   ::pointer < conversation_message > pconversation = this;
//
//   m_psequencer->m_phappening->wait(1_min);
//
//   psequence->m_payload= pconversation->m_payloadResult;
//   
//}


//void conversation_message::run()
//{
//   
//   string_stream textstream;
//   
//   textstream << "Title:   " << m_strTitle << "\n";
//   textstream << "Message: " << m_strMessage << "\n";
//   textstream << "Flags:   " << (iptr) m_emessagebox << "\n";
//   textstream << "Details:\n";
//   textstream << m_strDetails << "\n";
//   
//   informationf(textstream.as_string());
//   
//}
//
//
//void conversation_message::complete_aggregation(::sequence * psequence)
//{
//
//   //string_stream textstream;
//
//   //textstream << "Title:   " << m_strTitle << "\n";
//   //textstream << "Message: " << m_strMessage << "\n";
//   //textstream << "Flags:   " << (iptr)m_emessagebox << "\n";
//   //textstream << "Details:\n";
//   //textstream << m_strDetails << "\n";
//
//   //informationf(textstream.as_string());
//
//}

::payload message_box::get_result_payload()
{

   return m_payloadResult;

}


void message_box::on_timed_out()
{

   m_payloadResult = e_dialog_result_timeout;

   on_sequence();

}



void message_box::run()
{

//   auto psequence = ::sequence::current();
//
//   if (psequence)
//   {
//
//      psequence->m_pparticle = this;
//
//   }

   m_preified->call();

}
