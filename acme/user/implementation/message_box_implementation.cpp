//
//  conversation_message.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 01/Oct/22. 00:59
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"
#include "message_box_implementation.h"
#include "acme/handler/sequence.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
//#include "acme/handler/sequence.h"
#include "acme/nano/graphics/icon.h"
#include "acme/user/micro/theme.h"
#include "acme/windowing/display.h"
#include "acme/windowing/windowing.h"
#include "acme/nano/graphics/context.h"
#include "acme/user/user/activation_token.h"
//#include "acme/filesystem/file/string_buffer.h"
//#include "acme/filesystem/file/text_stream.h"


namespace user_interface
{

//namespace  user
//{
////::pointer<::conversation>node::create_new_message_conversation()
////{
////
////   return create_newø < ::conversation_message >();
////
////}
//
////
////} // namespace acme
//
//
////::string message_box_implementation::get_conversation_message()
////{
////
////   return m_strMessage;
////
////}
////
////
////::string message_box_implementation::get_conversation_title()
////{
////
////   return m_strTitle;
////
////}
////
////
////::user::e_message_box message_box_implementation::get_conversation_flags()
////{
////
////   return m_emessagebox;
////
////}
////
////
////::string message_box_implementation::get_conversation_details()
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
//message_box_implementation * dialog::get_message_box_payload()
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
//void message_box_implementation::run()
//{
//   
//   throw ::interface_only();
//   
//   //   m_papplication->run_message_box(this);
//   
//}
//
//
//void message_box_implementation::display_dialog()
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
//   //      pdialogreifier = create_newø < ::micro::message_box_implementation >();
//   //
//   //   }
//   //
//   
//}
//
//
//void message_box_implementation::on_dialog_result(const ::payload &payloadResult)
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
////message_box_implementation *dialog_reifier::get_message_box_payload()
////{
////
////   ::cast < class message_box_implementation > pmessagebox = m_pdialog;
////
////   return pmessageboxpayload;
////
////}
//


   message_box_implementation::message_box_implementation()
   {

      m_pmessagebox = this;

   }

   // message_box_implementation::message_box_implementation(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const
   // ::user::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
void message_box_implementation::initialize_message_box(const ::scoped_string &scopedstrMessage, const ::scoped_string &scopedstrTitle,
                                         const ::user::e_message_box &emessagebox,
                                         const ::scoped_string &scopedstrDetails,
                                         const ::string_array_base &straIconUrl)
{

   system()->information("Initializing message box with message \"{}\".", scopedstrMessage);
   
   m_strMessage = scopedstrMessage;
   
   m_strTitle = scopedstrTitle;
   
   m_emessagebox = emessagebox;
   
   m_strDetails = scopedstrDetails;
   
   if (::is_set(&straIconUrl))
   {
      
      m_straIconUrl = straIconUrl;
   }


}


void message_box_implementation::initialize_message_box(const ::exception & exception, const ::scoped_string & scopedstrMoreDetails)
{
   
   m_strMessage = exception.m_strMessage;
   
   m_strTitle = exception.m_strTitle;
   
   if (exception.m_econsequenceUserDefault == e_consequence_fatal)
   {
      
      m_emessagebox = ::user::e_message_box_icon_error;
      
   }
   else if (exception.m_econsequenceUserDefault == e_consequence_blocking)
   {
      
      m_emessagebox = ::user::e_message_box_icon_exclamation;
      
   }
   else if (exception.m_econsequenceUserDefault == e_consequence_workaroundable)
   {
      
      m_emessagebox = ::user::e_message_box_ok;
      
   }
   else
   {
      
      m_emessagebox = ::user::e_message_box_icon_asterisk;
      
   }
   
   m_strDetails.concatenate_with_separator("\n", exception.m_strTitle);
   
   m_strDetails.concatenate_with_separator("\n", exception.m_strMessage);
   
   m_strDetails.concatenate_with_separator("\n", scopedstrMoreDetails);
   
   m_strDetails.concatenate_with_separator("\n", exception.m_strDetails);
   
   m_strDetails.concatenate_with_separator("\n\nCallstack:\n", exception.m_strCallStackTrace);


}



//message_box_implementation::message_box_implementation(const ::exception & exception, const ::scoped_string & strMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
void message_box_implementation::initialize_message_box(const ::exception &exception, const ::scoped_string &strMessage,
                                         const ::scoped_string &scopedstrTitle,
                                         const ::user::e_message_box &emessagebox,
                                         const ::scoped_string &scopedstrDetails,
                                         const ::string_array_base &straIconUrl)
{
   
   m_strMessage = exception.m_strMessage;
   
   m_strMessage.concatenate_with_separator("\n", strMessage);
   
   m_strTitle = scopedstrTitle;
   
   m_emessagebox = emessagebox;
   
   m_strDetails = scopedstrDetails;
   
   m_strDetails.concatenate_with_separator("\n", scopedstrDetails);
   
   m_strDetails.concatenate_with_separator("\n\nCallstack:\n", exception.m_strCallStackTrace);
   
   //m_picon2 = picon;
   
   m_straIconUrl = straIconUrl;


   
   /*       auto picon = createø<::nano::graphics::icon>();
    
    auto pfile = file()->get("matter://main/icon.png");
    
    picon->load_image_from_file(pfile);*/
   
   
   
}


message_box_implementation::~message_box_implementation()
{
   
   
}



   ::string message_box_implementation::get_message() const
   {

      return m_strMessage;

   }



   ::string message_box_implementation::get_title() const
   {

      return m_strTitle;

   }


   ::string message_box_implementation::dialog_details_title() const
   {

      return m_strDetailsTitle;

   }


   ::user::e_message_box message_box_implementation::get_emessagebox() const
   {

      return m_emessagebox;

   }


   void message_box_implementation::_001InitializeMessageBox()
   {


      // ::cast < ::message_box_payload > pmessageboxpayload = pdialog;
      //
      // if (::is_null(pmessageboxpayload))
      // {
      //
      //    throw ::exception(error_wrong_state);
      //
      // }

      auto emessageboxType = m_emessagebox & ::user::e_message_box_type_mask;

      switch (emessageboxType)
      {
      case ::user::e_message_box_ok_cancel:
         add_button("OK", e_dialog_result_ok, 'o');
         add_button("Cancel", e_dialog_result_cancel, 'c');
         break;
      case ::user::e_message_box_abort_retry_ignore:
         add_button("Abort", e_dialog_result_abort, 'a');
         add_button("Retry", e_dialog_result_retry, 'r');
         add_button("Ignore", e_dialog_result_ignore, 'i');
         break;
      case ::user::e_message_box_yes_no_cancel:
         add_button("Yes", e_dialog_result_yes, 'y');
         add_button("No", e_dialog_result_no, 'n');
         add_button("Cancel", e_dialog_result_cancel, 'c');
         break;
      case ::user::e_message_box_yes_no:
         add_button("Yes", e_dialog_result_yes, 'y');
         add_button("No", e_dialog_result_no, 'n');
         break;
      case ::user::e_message_box_retry_cancel:
         add_button("Retry", e_dialog_result_retry, 'r');
         add_button("Cancel", e_dialog_result_cancel, 'c');
         break;
      case ::user::e_message_box_cancel_try_continue:
         add_button("Cancel", e_dialog_result_cancel, 'c');
         add_button("Try", e_dialog_result_retry, 't');
         add_button("Continue", e_dialog_result_continue, 'e');
         break;
      default:
         add_button("OK", e_dialog_result_ok, 'o');
         break;
      }



   }

   // void message_box_implementation::set_dialog_response(const ::payload &payloadResult)
   // {
   //
   //    on_dialog_response(payloadResult);
   //
   // }

   //
   // void message_box_implementation::_on_draw(::nano::graphics::context * pgraphicscontext)
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
   //   void message_box_implementation::defer_create_details_still()
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



   ::i32_rectangle message_box_implementation::initial_frame_rectangle()
{

   information("message_box_implementation::initial_frame_rectangle");

   ::i32_rectangle rectangle(120, 108, 640 ,200);;

   #if !defined(UNIVERSAL_WINDOWS) && !defined(__ANDROID__)

         //::i32 wScreen = 1280;
         //::i32 hScreen = 768;

         auto sizeScreen = system()->acme_windowing()->acme_display()->get_main_screen_size();

         //operating_system_get_main_screen_size(wScreen, hScreen);

         auto wScreen = sizeScreen.cx;

         auto hScreen = sizeScreen.cy;

         informationf("message_box_implementation::calculate_size (wScreen,hScreen)=%d,%d\n", wScreen, hScreen);

         ::i32 w = wScreen / 2;

         informationf("w(1)=%d", w);

         if (w < 600)
         {

            w = wScreen * 9 / 10;

            informationf("w(2)=%d", w);

         }

         ::i32 h = (w / 16) * 5;

         informationf("h(1)=%d", h);

         if (h < 300)
         {

            h = (hScreen / 12) * 5;

            informationf("h(2)=%d", h);

         }

         ::i32 x = (wScreen - w) / 2;

         ::i32 y = (hScreen - h) / 2;

         rectangle.set_dimension(x, y, w, h);

   #endif

   return rectangle;

}


   void message_box_implementation::add_button(const ::scoped_string & scopedstrTitle, enum_dialog_result edialogresult, ::i8 chLetter)
{


}

//message_box_implementation *message_box_implementation::get_message_box_payload()
//{
//   
//   
//   return this;
//   
//}
//


void message_box_implementation::on_dialog_response(const ::payload &payloadResult)
{

      ::user_interface::dialog_implementation::on_dialog_response(payloadResult);

      if (m_functionOnMessageBoxResult)
      {

         m_functionOnMessageBoxResult(this);

      }

      //m_manualresethappeningDialogResult.set_happening();

   
}


   void message_box_implementation::set_dialog_details_title(const ::scoped_string & scopedstrTitle)
   {

      m_strDetailsTitle = scopedstrTitle;

   }

   ::string_array_base & message_box_implementation::dialog_details_icon_urls()
   {

      return m_straDetailsIconUrl;

   }


void message_box_implementation::run()
{
   
   throw ::interface_only();
   
}

//#ifdef _DEBUG
//
//
//::i64 message_box_implementation::increment_reference_count()
//{
//
//   return ::particle::increment_reference_count();
//
//}
//
//
//::i64 message_box_implementation::decrement_reference_count()
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

::payload message_box_implementation::get_dialog_response()
{
   
   return m_payloadResult;
   
}


void message_box_implementation::on_timed_out()
{
   
   m_payloadResult = e_dialog_result_timeout;
   
   if (m_functionOnTimeOut)
   {
      
      m_functionOnTimeOut(this);
      
      //  on_sequence();
   }
   
}


::string message_box_implementation::dialog_details() const
{
   
   return m_strDetails;
   
}


::string_array_base message_box_implementation::dialog_details_icon_urls() const
{
   
   return m_straDetailsIconUrl;
   
}



   void message_box_implementation::set_user_activation_token(::user::activation_token * puseractivationtoken)
   {


      m_puseractivationtoken = puseractivationtoken;

   }




::function < void (::user_interface::message_box *) > & message_box_implementation::message_box_response_callback()
   {


      return m_functionOnMessageBoxResult;

   }

// void message_box_implementation::async()
// {
//
//
// }
//
//
// void message_box_implementation::sync()
// {
//
//
// }


//
// void message_box_implementation::run()
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
