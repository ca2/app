//
//  conversation_message.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 01/Oct/22. 00:59
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"
#include "acme/handler/sequence.h"
#include "acme/nano/graphics/icon.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "message_box.h"

//#include "acme/filesystem/file/string_buffer.h"
//#include "acme/filesystem/file/text_stream.h"


namespace user_interface
{

//namespace user
//{
//::pointer<::conversation>node::create_new_message_conversation()
//{
//
//   return create_newø < ::conversation_message >();
//
//}


//} // namespace acme


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
//::user::e_message_box message_box::get_conversation_flags()
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

dialog::dialog()
{
   
   
}


dialog::~dialog()
{
   
   
}


   ::i32_rectangle dialog::initial_frame_rectangle()
{

   return m_pdialog->initial_frame_rectangle();

}

   void dialog::on_initialize_dialog()
{

m_pdialog->on_initialize_dialog();

}


   void dialog::display(::e_display edisplay, const ::user::activation & useractivation)
{

   m_pdialog->display(edisplay, useractivation);

}

//::string dialog::dialog_title() const
//{
//   
//   throw ::interface_only();
//   
//   return {};
//   
//}


//void dialog::display_dialog()
//{
//   
//   
//   
//}
//

//void dialog::display_dialog()
//{
//
//   throw ::interface_only();
//
//}


//void dialog::display_dialog_and_wait_dialog_response()
//{
//   
//   throw ::interface_only();
//   
//}
//

//void dialog::set_dialog_result(const ::payload & payloadResult)
//{
//   
//   throw ::interface_only();
//   
//}


//void dialog::on_dialog_result(const ::payload & payloadResult)
//{
//   
//   throw ::interface_only();
//   
//}

//
//class time dialog::dialog_time_remaining_from_timeout() const
//{
//   
//   throw ::interface_only();
//   
//   return {};
//   
//}
//

//message_box_payload * dialog::get_message_box_payload()
//{
//   
//   return nullptr;
//   
//}
//

//class time dialog::dialog_timeout() const
//{
//   
//   throw ::interface_only();
//   
//   return {};
//   
//}



::string dialog::dialog_details() const
{

   return m_pdialog->dialog_details();

}


::string_array_base dialog::dialog_details_icon_urls() const
{
   
   return m_pdialog->dialog_details_icon_urls();
}


::string_array_base & dialog::dialog_details_icon_urls()
{

   return m_pdialog->dialog_details_icon_urls();

}

//dialog::dialog()
//{
//   
//   
//}
//
//
//dialog::~dialog()
//{
//   
//   
//}



::string dialog::dialog_title() const
{
   
   return m_pdialog->dialog_title();
   
}



::function<void(const ::payload &)> & dialog::dialog_response_callback()
{

   return m_pdialog->dialog_response_callback();

}


//void dialog::display_dialog()
//{
//   
//   throw ::interface_only();
//   
//}


void dialog::on_dialog_response(const ::payload & payloadResult)
{

   //return m_pdialog->on_dialog_result(payloadResult);

}


class ::time dialog::dialog_time_remaining_from_timeout() const
{

   return m_pdialog->dialog_time_remaining_from_timeout();
   //if (m_timeTimeout.is_null())
   // {
   //
   //    return 0_s;
   //
   // }
   //
   // auto timeElapsed = m_timeShowStart.elapsed();
   //
   // if (timeElapsed > m_timeTimeout || m_timeCancelledTimeout.is_set())
   // {
   //
   //    return 0_s;
   //
   // }
   //
   // return m_timeTimeout - timeElapsed;
   
}


class ::time dialog::dialog_timeout() const
{
   
   return m_pdialog->dialog_timeout();
   
}

//
//void message_box_payload::run()
//{
//   
//   throw ::interface_only();
//   
//   //   m_papplication->run_message_box(this);
//   
//}
//
//
//void message_box_payload::display_dialog()
//{
//   
//   ::pointer < ::dialog > pdialogreifier;
//   
//   
//   
//   //   if (m_bDetails)
//   //   {
//   //
//   //      pdialogreifier = create_newø < ::micro::details_window >();
//   //
//   //   }
//   //   else
//   //   {
//   //
//   //      pdialogreifier = create_newø < ::micro::message_box >();
//   //
//   //   }
//   //
//   
//}

//
//void message_box_payload::on_dialog_result(const ::payload &payloadResult)
//{
//   
//   m_payloadResult = payloadResult;
//   
//   if (m_functionOnMessageBoxResult)
//   {
//      
//      m_functionOnMessageBoxResult(this);
//      
//   }
//   else if (m_functionOnDialogResult2)
//   {
//      m_functionOnDialogResult2(payloadResult);
//   }
//}
//
//
//dialog::dialog()
//{
//   
//   
//}
//
//
//dialog::~dialog()
//{
//   
//   
//}
//
//
//
//::string dialog::dialog_title() const
//{
//   
//   return m_pdialog->dialog_title();
//   
//}
//
//
//void dialog::display_dialog()
//{
//   
//   throw ::interface_only();
//   
//}


//void dialog::display_dialog()
//{
//
////   m_pdialog = pdialog;
////
////   display_dialog();
//
//}


   bool dialog::is_waiting_for_dialog_response()
{


   return m_pdialog->is_waiting_for_dialog_response();

}

 void dialog::wait_dialog_response(const class ::time & timeTimeout)
{
    
    //m_pmanualresethappeningDialogResponse->wait(timeTimeout);

   m_pdialog->wait_dialog_response(timeTimeout);
    
 }

void dialog::on_dialog_finished()
{


}


void dialog::set_dialog_type(enum_dialog edialog)
{


   m_pdialog->set_dialog_type(edialog);

}


    ::payload dialog::get_dialog_response()
{


   return m_pdialog->get_dialog_response();

}


void dialog::set_dialog_response(const ::payload & payloadResult)
{
   
//   auto pdialog = m_pdialog;


   m_pdialog->set_dialog_response(payloadResult);
   
   //on_dialog_result(payloadResult);
   
   //m_pmanualresethappeningDialogResponse->set_happening();
   
   
//   try
//   {
//      
//      if (pdialog)
//      {
//         
//         pdialog->on_dialog_result(payloadResult);
//         
//      }
//      
//   }
//   catch (...)
//   {
//      
//      
//   }
   
}


//class time dialog::dialog_time_remaining_from_timeout() const
//{
//   
//   return m_pdialog->dialog_time_remaining_from_timeout();
//   
//}

//
//class time dialog::dialog_timeout() const
//{
//   
//   return m_pdialog->dialog_timeout();
//   
//}


//message_box_payload *dialog::get_message_box_payload()
//{
//   
//   ::cast <  message_box > pmessagebox = m_pdialog;
//   
//   return pmessageboxpayload;
//   
//}


////message_box_payload::message_box_payload(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
//message_box_payload::message_box_payload(const ::scoped_string &scopedstrMessage, const ::scoped_string &scopedstrTitle,
//                                         const ::user::e_message_box &emessagebox,
//                                         const ::scoped_string &scopedstrDetails,
//                                         const ::string_array_base &straIconUrl)
//{
//   
//   m_strMessage = scopedstrMessage;
//   
//   m_strTitle = scopedstrTitle;
//   
//   m_emessagebox = emessagebox;
//   
//   m_strDetails = scopedstrDetails;
//   
//   if (::is_set(&straIconUrl))
//   {
//      
//      m_straIconUrl = straIconUrl;
//   }
//   
//}
//
//
//message_box_payload::message_box_payload(const ::exception & exception, const ::scoped_string & scopedstrMoreDetails)
//{
//   
//   m_strMessage = exception.m_strMessage;
//   
//   m_strTitle = exception.m_strTitle;
//   
//   if (exception.m_econsequenceUserDefault == e_consequence_fatal)
//   {
//      
//      m_emessagebox = ::user::e_message_box_icon_error;
//      
//   }
//   else if (exception.m_econsequenceUserDefault == e_consequence_blocking)
//   {
//      
//      m_emessagebox = ::user::e_message_box_icon_exclamation;
//      
//   }
//   else if (exception.m_econsequenceUserDefault == e_consequence_workaroundable)
//   {
//      
//      m_emessagebox = ::user::e_message_box_ok;
//      
//   }
//   else
//   {
//      
//      m_emessagebox = ::user::e_message_box_icon_asterisk;
//      
//   }
//   
//   m_strDetails.concatenate_with_separator("\n", exception.m_strTitle);
//   
//   m_strDetails.concatenate_with_separator("\n", exception.m_strMessage);
//   
//   m_strDetails.concatenate_with_separator("\n", scopedstrMoreDetails);
//   
//   m_strDetails.concatenate_with_separator("\n", exception.m_strDetails);
//   
//   m_strDetails.concatenate_with_separator("\n\nCallstack:\n", exception.m_strCallStackTrace);
//   
//}
//
//
//
////message_box_payload::message_box_payload(const ::exception & exception, const ::scoped_string & strMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
//message_box_payload::message_box_payload(const ::exception &exception, const ::scoped_string &strMessage,
//                                         const ::scoped_string &scopedstrTitle,
//                                         const ::user::e_message_box &emessagebox,
//                                         const ::scoped_string &scopedstrDetails,
//                                         const ::string_array_base &straIconUrl)
//{
//   
//   m_strMessage = exception.m_strMessage;
//   
//   m_strMessage.concatenate_with_separator("\n", strMessage);
//   
//   m_strTitle = scopedstrTitle;
//   
//   m_emessagebox = emessagebox;
//   
//   m_strDetails = scopedstrDetails;
//   
//   m_strDetails.concatenate_with_separator("\n", scopedstrDetails);
//   
//   m_strDetails.concatenate_with_separator("\n\nCallstack:\n", exception.m_strCallStackTrace);
//   
//   //m_picon2 = picon;
//   
//   m_straIconUrl = straIconUrl;
//   
//   
//   /*       auto picon = createø<::nano::graphics::icon>();
//    
//    auto pfile = file()->get("matter://main/icon.png");
//    
//    picon->load_image_from_file(pfile);*/
//   
//   
//   
//}
//
//
//message_box_payload::~message_box_payload()
//{
//   
//   
//}
//
//
//message_box_payload *message_box_payload::get_message_box_payload()
//{
//   
//   
//   return this;
//   
//}
//
//
//
//
//
////#ifdef _DEBUG
////
////
////::i64 message_box_payload::increment_reference_count()
////{
////
////   return ::particle::increment_reference_count();
////
////}
////
////
////::i64 message_box_payload::decrement_reference_count()
////{
////
////   return ::particle::decrement_reference_count();
////
////}
////
////
////#endif
////
//
//
////void conversation_message::aggregate(sequence * psequence)
////{
////
////   //m_psequencer->m_phappening = create_newø < manual_reset_happening >();
////
////   do_asynchronously();
////
////   ::pointer < conversation_message > pconversation = this;
////
////   m_psequencer->m_phappening->wait(1_min);
////
////   psequence->m_payload= pconversation->m_payloadResult;
////
////}
//
//
////void conversation_message::run()
////{
////
////   string_stream textstream;
////
////   textstream << "Title:   " << m_strTitle << "\n";
////   textstream << "Message: " << m_strMessage << "\n";
////   textstream << "Flags:   " << (iptr) m_emessagebox << "\n";
////   textstream << "Details:\n";
////   textstream << m_strDetails << "\n";
////
////   informationf(textstream.as_string());
////
////}
////
////
////void conversation_message::complete_aggregation(::sequence * psequence)
////{
////
////   //string_stream textstream;
////
////   //textstream << "Title:   " << m_strTitle << "\n";
////   //textstream << "Message: " << m_strMessage << "\n";
////   //textstream << "Flags:   " << (iptr)m_emessagebox << "\n";
////   //textstream << "Details:\n";
////   //textstream << m_strDetails << "\n";
////
////   //informationf(textstream.as_string());
////
////}
//
//::payload message_box_payload::get_result_payload()
//{
//   
//   return m_payloadResult;
//   
//}
//
//
//void message_box_payload::on_timed_out()
//{
//   
//   m_payloadResult = e_dialog_result_timeout;
//   
//   if (m_functionOnTimeOut)
//   {
//      
//      m_functionOnTimeOut(this);
//      
//      //  on_sequence();
//   }
//   
//}
//
//
//::string message_box_payload::dialog_details() const
//{
//   
//   return m_strDetails;
//   
//}
//
//
//::string_array_base message_box_payload::dialog_details_icon_urls() const
//{
//   
//   return m_straDetailsIconUrl;
//   
//}
//
//
//// void message_box_payload::async()
//// {
////
////
//// }
////
////
//// void message_box_payload::sync()
//// {
////
////
//// }
//
//
////
//// void message_box_payload::run()
//// {
//// //
//// ////   auto psequence = ::sequence::current();
//// ////
//// ////   if (psequence)
//// ////   {
//// ////
//// ////      psequence->m_pparticle = this;
//// ////
//// ////   }
//// //
//// //   m_preified->call();
//// //
//// }


} // namespace user_interface

//} // namespace acme



