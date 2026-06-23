//
//  conversation_message.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 01/Oct/22. 00:59
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "message_box.h"
#include "acme/handler/sequence.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "framework.h"
//#include "acme/handler/sequence.h"
#include "acme/nano/graphics/icon.h"
#include "acme/user/micro/theme.h"
#include "acme/windowing/display.h"
#include "acme/windowing/windowing.h"
#include "acme/nano/graphics/context.h"
//#include "acme/filesystem/file/string_buffer.h"
//#include "acme/filesystem/file/text_stream.h"


namespace user_interface
{

//namespace  user
//{
////::pointer<::conversation>node::create_new_message_conversation()
////{
////
////   return create_newø < ::conversation_message >();z
////
////}
//
////
////} // namespace acme
//
//
////::string message_box::get_conversation_message()
////{
////
////   return m_strMessage;
////
////}
////
////
////::string message_box::get_conversation_title()
////{
////
////   return m_strTitle;
////
////}
////
////
////::user::e_message_box message_box::get_conversation_flags()
////{
////
////   return m_emessagebox;
////
////}
////
////
////::string message_box::get_conversation_details()
////{
////
////   return m_strDetails;
////
////}
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
//::string dialog::dialog_title() const
//{
//   
//   throw ::interface_only();
//   
//   return {};
//   
//}
//
//
//void dialog::display_dialog()
//{
//   
//   
//   
//}
//
//
////void dialog::display_dialog()
////{
////
////   throw ::interface_only();
////
////}
//
//
//void dialog::display_dialog_and_wait_dialog_response()
//{
//   
//   throw ::interface_only();
//   
//}
//
//
//void dialog::set_dialog_result(const ::payload & payloadResult)
//{
//   
//   throw ::interface_only();
//   
//}
//
//
//void dialog::on_dialog_result(const ::payload & payloadResult)
//{
//   
//   throw ::interface_only();
//   
//}
//
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
//
//message_box * dialog::get_message_box_payload()
//{
//   
//   return nullptr;
//   
//}
//
//
//class time dialog::dialog_timeout() const
//{
//   
//   throw ::interface_only();
//   
//   return {};
//   
//}
//
//
//
//::string dialog::dialog_details() const
//{
//   
//   throw ::interface_only();
//   
//   return {};
//   
//}
//
//
//::string_array_base dialog::dialog_details_icon_urls() const
//{
//   
//   throw ::interface_only();
//   
//   return {};
//   
//}
//
//
//dialog_payload::dialog_payload()
//{
//   
//   
//}
//
//
//dialog_payload::~dialog_payload()
//{
//   
//   
//}
//
//
//
//::string dialog_payload::dialog_title() const
//{
//   
//   return m_strTitle;
//   
//}
//
//
//
//void dialog_payload::display_dialog()
//{
//   
//   throw ::interface_only();
//   
//}
//
//
//void dialog_payload::on_dialog_result(const ::payload & payloadResult)
//{
//   
//   if (m_functionOnDialogResult2)
//   {
//      m_functionOnDialogResult2(payloadResult);
//   }
//   
//}
//
//
//class ::time dialog_payload::dialog_time_remaining_from_timeout() const
//{
//   
//   if (m_timeTimeout.is_null())
//   {
//      
//      return 0_s;
//      
//   }
//   
//   auto timeElapsed = m_timeShowStart.elapsed();
//   
//   if (timeElapsed > m_timeTimeout || m_timeCancelledTimeout.is_set())
//   {
//      
//      return 0_s;
//      
//   }
//   
//   return m_timeTimeout - timeElapsed;
//   
//}
//
//
//class ::time dialog_payload::dialog_timeout() const
//{
//   
//   return m_timeTimeout;
//   
//}
//
//
//void message_box::run()
//{
//   
//   throw ::interface_only();
//   
//   //   m_papplication->run_message_box(this);
//   
//}
//
//
//void message_box::display_dialog()
//{
//   
//   ::pointer < ::dialog_reifier > pdialogreifier;
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
//
//void message_box::on_dialog_result(const ::payload &payloadResult)
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
////
////dialog_reifier::dialog_reifier()
////{
////   
////   
////}
////
////
////dialog_reifier::~dialog_reifier()
////{
////   
////   
////}
////
////
////
////::string dialog_reifier::dialog_title() const
////{
////   
////   return m_pdialog->dialog_title();
////   
////}
////
////
////void dialog_reifier::display_dialog()
////{
////   
////   throw ::interface_only();
////   
////}
////
////
//////void dialog_reifier::display_dialog()
//////{
//////
////////   m_pdialog = pdialog;
////////
////////   display_dialog();
//////
//////}
////
////
////
////void dialog_reifier::set_dialog_result(const ::payload & payloadResult)
////{
////   
////   auto pdialog = m_pdialog;
////   
////   on_dialog_result(payloadResult);
////   
////   try
////   {
////      
////      if (pdialog)
////      {
////         
////         pdialog->on_dialog_result(payloadResult);
////         
////      }
////      
////   }
////   catch (...)
////   {
////      
////      
////   }
////   
////}
////
////
////class time dialog_reifier::dialog_time_remaining_from_timeout() const
////{
////   
////   return m_pdialog->dialog_time_remaining_from_timeout();
////   
////}
////
////
////class time dialog_reifier::dialog_timeout() const
////{
////   
////   return m_pdialog->dialog_timeout();
////   
////}
//
//
////message_box *dialog_reifier::get_message_box_payload()
////{
////
////   ::cast < class message_box > pmessagebox = m_pdialog;
////
////   return pmessageboxpayload;
////
////}
//


   message_box::message_box()
   {

   }

   // message_box::message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const
   // ::user::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
void message_box::initialize_message_box(const ::scoped_string &scopedstrMessage, const ::scoped_string &scopedstrTitle,
                                         const ::user::e_message_box &emessagebox,
                                         const ::scoped_string &scopedstrDetails,
                                         const ::string_array_base &straIconUrl)
{

      constructø(m_pmessagebox);

      m_pdialog = m_pmessagebox;

      m_pmessagebox->initialize_message_box(scopedstrMessage, scopedstrTitle, emessagebox, scopedstrDetails, straIconUrl);
   
   // m_strMessage = scopedstrMessage;
   //
   // m_strTitle = scopedstrTitle;
   //
   // m_emessagebox = emessagebox;
   //
   // m_strDetails = scopedstrDetails;
   //
   // if (::is_set(&straIconUrl))
   // {
   //
   //    m_straIconUrl = straIconUrl;
   // }


}


void message_box::initialize_message_box(const ::exception & exception, const ::scoped_string & scopedstrMoreDetails)
{

      constructø(m_pmessagebox);

      m_pdialog = m_pmessagebox;

      m_pmessagebox->initialize_message_box(exception, scopedstrMoreDetails);

   
   // m_strMessage = exception.m_strMessage;
   //
   // m_strTitle = exception.m_strTitle;
   //
   // if (exception.m_econsequenceUserDefault == e_consequence_fatal)
   // {
   //
   //    m_emessagebox = ::user::e_message_box_icon_error;
   //
   // }
   // else if (exception.m_econsequenceUserDefault == e_consequence_blocking)
   // {
   //
   //    m_emessagebox = ::user::e_message_box_icon_exclamation;
   //
   // }
   // else if (exception.m_econsequenceUserDefault == e_consequence_workaroundable)
   // {
   //
   //    m_emessagebox = ::user::e_message_box_ok;
   //
   // }
   // else
   // {
   //
   //    m_emessagebox = ::user::e_message_box_icon_asterisk;
   //
   // }
   //
   // m_strDetails.concatenate_with_separator("\n", exception.m_strTitle);
   //
   // m_strDetails.concatenate_with_separator("\n", exception.m_strMessage);
   //
   // m_strDetails.concatenate_with_separator("\n", scopedstrMoreDetails);
   //
   // m_strDetails.concatenate_with_separator("\n", exception.m_strDetails);
   //
   // m_strDetails.concatenate_with_separator("\n\nCallstack:\n", exception.m_strCallStackTrace);


}



//message_box::message_box(const ::exception & exception, const ::scoped_string & strMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
void message_box::initialize_message_box(const ::exception &exception, const ::scoped_string &strMessage,
                                         const ::scoped_string &scopedstrTitle,
                                         const ::user::e_message_box &emessagebox,
                                         const ::scoped_string &scopedstrDetails,
                                         const ::string_array_base &straIconUrl)
{

      constructø(m_pmessagebox);

      m_pdialog = m_pmessagebox;

      m_pmessagebox->initialize_message_box(exception, strMessage,
         scopedstrTitle, emessagebox, scopedstrDetails, straIconUrl);

   //
   // m_strMessage = exception.m_strMessage;
   //
   // m_strMessage.concatenate_with_separator("\n", strMessage);
   //
   // m_strTitle = scopedstrTitle;
   //
   // m_emessagebox = emessagebox;
   //
   // m_strDetails = scopedstrDetails;
   //
   // m_strDetails.concatenate_with_separator("\n", scopedstrDetails);
   //
   // m_strDetails.concatenate_with_separator("\n\nCallstack:\n", exception.m_strCallStackTrace);
   //
   // //m_picon2 = picon;
   //
   // m_straIconUrl = straIconUrl;
   //
   //
   //
   // /*       auto picon = createø<::nano::graphics::icon>();
   //
   //  auto pfile = file()->get("matter://main/icon.png");
   //
   //  picon->load_image_from_file(pfile);*/
   //
   //
   
}


message_box::~message_box()
{
   
   
}


   // void message_box::_001InitializeMessageBox()
   // {
   //
   //
   //    // ::cast < ::message_box_payload > pmessageboxpayload = pdialog;
   //    //
   //    // if (::is_null(pmessageboxpayload))
   //    // {
   //    //
   //    //    throw ::exception(error_wrong_state);
   //    //
   //    // }
   //
   //    auto emessageboxType = get_emessagebox() & ::user::e_message_box_type_mask;
   //
   //    switch (emessageboxType)
   //    {
   //    case ::user::e_message_box_ok_cancel:
   //       add_button("OK", e_dialog_result_ok, 'o');
   //       add_button("Cancel", e_dialog_result_cancel, 'c');
   //       break;
   //    case ::user::e_message_box_abort_retry_ignore:
   //       add_button("Abort", e_dialog_result_abort, 'a');
   //       add_button("Retry", e_dialog_result_retry, 'r');
   //       add_button("Ignore", e_dialog_result_ignore, 'i');
   //       break;
   //    case ::user::e_message_box_yes_no_cancel:
   //       add_button("Yes", e_dialog_result_yes, 'y');
   //       add_button("No", e_dialog_result_no, 'n');
   //       add_button("Cancel", e_dialog_result_cancel, 'c');
   //       break;
   //    case ::user::e_message_box_yes_no:
   //       add_button("Yes", e_dialog_result_yes, 'y');
   //       add_button("No", e_dialog_result_no, 'n');
   //       break;
   //    case ::user::e_message_box_retry_cancel:
   //       add_button("Retry", e_dialog_result_retry, 'r');
   //       add_button("Cancel", e_dialog_result_cancel, 'c');
   //       break;
   //    case ::user::e_message_box_cancel_try_continue:
   //       add_button("Cancel", e_dialog_result_cancel, 'c');
   //       add_button("Try", e_dialog_result_retry, 't');
   //       add_button("Continue", e_dialog_result_continue, 'e');
   //       break;
   //    default:
   //       add_button("OK", e_dialog_result_ok, 'o');
   //       break;
   //    }
   //
   //
   //
   // }


   ::string message_box::get_message() const
   {

      return m_pmessagebox->get_message();

   }


   ::string message_box::get_title() const
   {

      return m_pmessagebox->get_title();

   }


   ::user::e_message_box message_box::get_emessagebox() const
   {

      return m_pmessagebox->get_emessagebox();

   }


   // void message_box::_on_draw(::nano::graphics::context * pgraphicscontext)
   // {
   //
   //    i32_rectangle rectangleText;
   //
   //    rectangleText = get_client_rectangle();
   //
   //    rectangleText.bottom = rectangleText.top + rectangleText.height() * 3 / 4;
   //
   //    rectangleText.deflate(25);
   //
   //    if (m_picon)
   //    {
   //
   //       pgraphicscontext->draw_icon(25, 25, 48, 48, m_picon);
   //
   //       rectangleText.left += 48 + 10;
   //
   //    }
   //
   //    //::cast < ::message_box_payload > pmessageboxpayload = m_pdialog;
   //    pgraphicscontext->set_brush(micro_theme()->m_pbrushText);
   //    pgraphicscontext->set_font(micro_theme()->m_pfont);
   //
   //    pgraphicscontext->draw_text123(
   //       m_strMessage,
   //       rectangleText,
   //                                   e_draw_text_word_break,
   //       e_align_top_left);
   //
   //    //,
   //      // micro_theme()->m_pbrushWindow,
   //       //micro_theme()->m_pbrushText,
   //       //micro_theme()->m_pfont);
   //
   // }

   //
   //   void message_box::defer_create_details_still()
   //   {
   //
   //      ::cast < ::message_box_payload > pmessageboxpayload = m_pdialog;
   //
   //      if (pmessageboxpayload->m_strDetails.has_character())
   //      {
   //
   //         m_pstillDetails = allocateø::micro::still();
   //
   //         m_pstillDetails->id() = "details";
   //
   //         m_pstillDetails->m_strText = m_strLabelDetails;
   //
   //         m_pstillDetails->m_bHyperlink = true;
   //
   //         m_pstillDetails->m_bBorder = false;
   //
   //         add_child(m_pstillDetails);
   //
   //      }
   //
   //   }



   ::i32_rectangle message_box::initial_frame_rectangle()
{


      return m_pmessagebox->initial_frame_rectangle();


}


   void message_box::add_button(const ::scoped_string & scopedstrTitle, enum_dialog_result edialogresult, ::i8 chLetter)
{


}

//message_box *message_box::get_message_box_payload()
//{
//   
//   
//   return this;
//   
//}
//


void message_box::on_dialog_response(const ::payload &payloadResult       )
   {
   
   
}



void message_box::run()
{
   
   throw ::interface_only();
   
}

//#ifdef _DEBUG
//
//
//::i64 message_box::increment_reference_count()
//{
//
//   return ::particle::increment_reference_count();
//
//}
//
//
//::i64 message_box::decrement_reference_count()
//{
//
//   return ::particle::decrement_reference_count();
//
//}
//
//
//#endif
//


//void conversation_message::aggregate(sequence * psequence)
//{
//
//   //m_psequencer->m_phappening = create_newø < manual_reset_happening >();
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

::payload message_box::get_dialog_response()
{
   
   return m_pmessagebox->get_dialog_response();
   
}


void message_box::on_timed_out()
{


   
   // m_payloadResult = e_dialog_result_timeout;
   //
   // if (m_functionOnTimeOut)
   // {
   //
   //    m_functionOnTimeOut(this);
   //
   //    //  on_sequence();
   // }
   
}


::string message_box::dialog_details() const
{
   
   return m_pmessagebox->dialog_details();
   
}


void message_box::set_dialog_details_title(const scoped_string &scopedstrTitle)
   {
      m_pmessagebox->set_dialog_details_title(scopedstrTitle);
   }

::string_array_base message_box::dialog_details_icon_urls() const
{
   
   return m_pmessagebox->dialog_details_icon_urls();
   
}

   ::string_array_base & message_box::dialog_details_icon_urls()
   {

      return m_pmessagebox->dialog_details_icon_urls();

   }

   void message_box::set_user_activation_token(::user::activation_token * puseractivationtoken)
   {

      m_pmessagebox->set_user_activation_token(puseractivationtoken);

   }


   void message_box::display(e_display edisplay, const user::activation &useractivation)
   {


      m_pmessagebox->display(edisplay, useractivation);

   }

   // void message_box::async()
// {
//
//
// }
//
//
// void message_box::sync()
// {
//
//
// }


   ::function < void (::user_interface::message_box *) > & message_box::message_box_response_callback()
   {


      return m_pmessagebox->message_box_response_callback();


   }


   ::string message_box::dialog_details_title() const
   {


      return m_pmessagebox->dialog_details_title();

   }

//
// void message_box::run()
// {
// //
// ////   auto psequence = ::sequence::current();
// ////
// ////   if (psequence)
// ////   {
// ////
// ////      psequence->m_pparticle = this;
// ////
// ////   }
// //
// //   m_preified->call();
// //
// }


} // namespace user_interface


//} // namespace acme
