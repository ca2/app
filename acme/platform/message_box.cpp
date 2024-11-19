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
//#include "acme/platform/sequencer.h"
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


message_box::message_box(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails, ::nano::graphics::icon * picon)
{

   m_strMessage = strMessage;

   m_strTitle = strTitle;

   m_emessagebox = emessagebox;

   m_strDetails = strDetails;

   m_picon = picon;

}


message_box::message_box(const ::exception & exception, const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails, ::nano::graphics::icon * picon)
{

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


#ifdef DEBUG


huge_integer message_box::increment_reference_count()
{

   return ::particle::increment_reference_count();

}


huge_integer message_box::decrement_reference_count()
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
