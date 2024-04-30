//
// Created by camilo on 2022-01-21 14:57 <3ThomasBorregaardSorensen
// Generalization by camilo on 31/01/2022 14:53 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "message_box.h"
#include "device.h"
#include "still.h"
#include "button.h"
#include "window_implementation.h"
#include "acme/user/nano/details_window.h"
#include "acme/user/nano/popup_button.h"
#include "acme/user/user/mouse.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/sequencer.h"
#include "acme/platform/system.h"
#include "acme/operating_system/message_box.h"
#include "acme/_operating_system.h"


bool is_ui_possible();
void ns_do_main_loop(double dSeconds);


nano_message_box::nano_message_box()
{

   m_bStartCentered = true;

   m_strLabelDetails = "Details...";

}


nano_message_box::~nano_message_box()
{


}


void nano_message_box::on_draw(nano_device * pnanodevice)
{

   rectangle_i32 rectangleText;

   get_client_rectangle(rectangleText);

   rectangleText.bottom() = rectangleText.top() + rectangleText.height() * 3 / 4;

   rectangleText.deflate(25);

   pnanodevice->draw_text123(
      m_strMessage, 
      rectangleText,
      e_align_top_left,
      e_draw_text_word_break,
      m_pbrushWindow, 
      m_pbrushText, 
      m_pfont);

}



void nano_message_box::defer_create_details_still()
{

   if (m_strDetails.has_char())
   {

      m_pstillDetails = __allocate< nano_still >();

      m_pstillDetails->m_atom = "details";

      m_pstillDetails->m_strText = m_strLabelDetails;

      m_pstillDetails->m_bHyperlink = true;

      add_child(m_pstillDetails);

   }

}


::raw::count get_line_count(const ::string & str)
{

   ::raw::index iFind = 0;

   ::raw::count cLine = 1;

   while ((iFind = str(iFind).find_index('\n')) >= 0)
   {

      cLine++;

      iFind++;

   }

   return cLine;

}


void nano_message_box::calculate_size()
{

#if !defined(UNIVERSAL_WINDOWS) && !defined(ANDROID)

   //int wScreen = 1280;
   //int hScreen = 768;

   auto sizeScreen = m_pimplementation->get_main_screen_size();

   //operating_system_get_main_screen_size(wScreen, hScreen);

   auto wScreen = sizeScreen.cx();

   auto hScreen = sizeScreen.cy();

   //printf("nano_message_box::calculate_size (wScreen,hScreen)=%d,%d\n", wScreen, hScreen);

   int w = wScreen / 2;
   int h = (w / 16) * 5;
   int x = (wScreen - w) / 2;
   int y = (hScreen - h) / 2;

   m_rectangle.set_dimension(x, y, w, h);

   //printf("nano_message_box::calculate_size (w,h)=%d,%d\n", w, h);


#endif

}


void nano_message_box::initialize_conversation(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails)
{
   
   conversation_message::initialize_conversation(strMessage, strTitle, emessagebox, strDetails);

   calculate_size();

   auto emessageboxType = emessagebox & e_message_box_type_mask;

   switch (emessageboxType)
   {
      case e_message_box_ok_cancel:
         add_button("OK", e_dialog_result_ok, 'o');
         add_button("Cancel", e_dialog_result_cancel, 'c');
         break;
      case e_message_box_abort_retry_ignore:
         add_button("Abort", e_dialog_result_abort, 'a');
         add_button("Retry", e_dialog_result_retry, 'r');
         add_button("Ignore", e_dialog_result_ignore, 'i');
         break;
      case e_message_box_yes_no_cancel:
         add_button("Yes", e_dialog_result_yes, 'y');
         add_button("No", e_dialog_result_no, 'n');
         add_button("Cancel", e_dialog_result_cancel, 'c');
         break;
      case e_message_box_yes_no:
         add_button("Yes", e_dialog_result_yes, 'y');
         add_button("No", e_dialog_result_no, 'n');
         break;
      case e_message_box_retry_cancel:
         add_button("Retry", e_dialog_result_retry, 'r');
         add_button("Cancel", e_dialog_result_cancel, 'c');
         break;
      case e_message_box_cancel_try_continue:
         add_button("Cancel", e_dialog_result_cancel, 'c');
         add_button("Try", e_dialog_result_try_again, 't');
         add_button("Continue", e_dialog_result_continue, 'n');
         break;
      default:
         add_button("OK", e_dialog_result_ok, 'o');
         break;
   }

   defer_create_details_still();

   if (emessagebox & e_message_box_default_button_mask)
   {

      int iDefaultButtonMask = (int)(emessagebox & e_message_box_default_button_mask);

      int iDefaultButtonIndex = iDefaultButtonMask >> 8;

      int iDefaultButton = iDefaultButtonIndex & 7;

      m_childa[iDefaultButton]->set_focus();

   }
   else
   {

      m_childa[0]->set_focus();

   }

   auto wButton = (::i32) (m_rectangle.width() * 0.2);

   auto hButton = (::i32) (m_rectangle.height() * 0.2);

   auto iRight = (::i32) (m_rectangle.width() - m_rectangle.width() * 0.025);

   auto iBottom = (::i32) (m_rectangle.height() - m_rectangle.width() * 0.025);

   auto wSpacing = (::i32) (m_rectangle.width() * 0.025);

   for (::raw::index iButton = m_nanobuttona.get_upper_bound(); iButton >= 0; iButton--)
   {

      auto pnanobutton = m_nanobuttona[iButton];

      pnanobutton->m_rectangle.bottom() = iBottom;
      pnanobutton->m_rectangle.top() = pnanobutton->m_rectangle.bottom() - hButton;
      pnanobutton->m_rectangle.right() = iRight;
      pnanobutton->m_rectangle.left() = pnanobutton->m_rectangle.right() - wButton;

      iRight = pnanobutton->m_rectangle.left() - wSpacing;

   }


}


//void nano_message_box::initialize_message_box(const ::string & strMessage, const string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails)
//{
//
//   m_functionClose = [this](nano_window * pwindow)
//   {
//
//      m_psequence->on_sequence();
//
//   };
//
//   m_strMessage = strMessage;
//
//   m_strDetails = strDetails;
//
//   m_emessagebox = emessagebox;
//
//   m_strTitle = strTitle;
//
//}



//void nano_message_box::do_message_box(const ::string& strMessage, const string& strTitle, const ::e_message_box& emessagebox, const ::string & strDetails)
//{
//
//   m_functionClose = [this](nano_window* pwindow)
//   {
//
//      m_psequence->on_sequence();
//
//   };
//
//   main_asynchronous([this, strMessage, strTitle, emessagebox, strDetails]()
//      {
//
//         display(strMessage, strTitle, emessagebox, strDetails);
//
//      });
//
//}


void nano_message_box::on_create()
{

   if (m_pstillDetails)
   {

      m_pstillDetails->resize_to_fit();

      m_pstillDetails->m_rectangle.move_bottom_to(m_nanobuttona[0]->m_rectangle.bottom());

      m_pstillDetails->m_rectangle.move_left_to(25);

   }

}


//pointer< ::sequence < ::conversation > > nano_message_box::display(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox)
//{
//
//   auto psequence = __allocate< ::sequence <::conversation > >();
//
//   psequence->m_p = this;
//
//   fork([strMessage, strTitle, emessagebox, psequence]()
//      {
//
//         psequence->m_p->display_synchronously(strMessage, strTitle, emessagebox);
//
//         psequence->on_sequence();
//
//      });
//
//   return psequence;
//
//}


//LRESULT nano_message_box::window_procedure(UINT message, WPARAM wparam, LPARAM lparam)
//{
//
//   return ::DefWindowProc(m_hwnd, message, wparam, lparam);
//
//}


//CLASS_DECL_ACME ::acme::system * system();
#ifdef WINDOWS_DESKTOP
CLASS_DECL_ACME int message_box_to_windows_message_box(enum_message_box emessagebox);
CLASS_DECL_ACME enum_dialog_result windows_message_box_result_to_dialog_result(int iResult);
#endif

#ifdef MACOS

enum_dialog_result ns_alert_box(const char * pszMessage, const char * pszTitle, enum_message_box emessagebox);

#endif


CLASS_DECL_ACME ::atom message_box_synchronous(::particle * pparticle, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails)
{

   if (::is_null(pparticle))
   {

      auto pmessagebox = ::platform::get()->__create < ::operating_system::message_box >();

      return pmessagebox->do_modal(scopedstrMessage, scopedstrTitle, emessagebox, scopedstrDetails);

   }

   //initialize_nano_window(pparticle->factory());

   if (::is_null(pparticle))
   {

      throw ::exception(error_null_pointer);
      
   }

#if defined(UNIVERSAL_WINDOWS)

   if(pparticle->platform()->m_bConsole || !is_ui_possible())
   {

      return message_box_for_console(scopedstrMessage, scopedstrTitle, emessagebox, scopedstrDetails);

   }
   else
   {

      throw ::exception(error_failed);

   }
   
#endif

   pparticle->system()->nano();

   auto psequencer = pparticle->node()->create_message_box_sequencer(scopedstrMessage, scopedstrTitle, emessagebox, scopedstrDetails);
   
   auto atomResult = psequencer->do_synchronously();
   
//   auto pmanualresetevent = __allocate< manual_reset_event >();
//   
//   atom atomResult;
//   
//   psequence->then([ pmanualresetevent, &atomResult ](auto psequence)
//   {
//
//      atomResult = psequence->m_atomResult;
//
//      pmanualresetevent->SetEvent();
//      
//   });
//
//   pmanualresetevent->wait();
//
////   auto pmessagebox = pparticle->__create_new < nano_message_box >();
////
////   atom idResult;
////
////   manual_reset_event event;
////
////   pmessagebox->display(pszMessage, pszTitle, emessagebox, pszDetails);
////
////   pmessagebox->m_functionClose = [&idResult, &event](nano_window * pwindow)
////   {
////
////      idResult = pwindow->m_atomResult;
////
////      event.SetEvent();
////
////   };
////
////   if(is_single_main_user_thread() && is_main_thread())
////   {
////
////      pmessagebox->_run_modal_loop();
////
////   }
////   else
////   {
////      event.wait();
////
////   }
////
////   //auto idResult = pmessagebox->get_result();
////
////   return idResult;
   
   return atomResult;

}


struct message_box :
   virtual public conversation_message
{
public:


   ::function < void(const ::atom & atom) >     m_function;
   ::pointer<::object>                         m_pobject;
//   string                                       m_strMessage;
//   string                                       m_strTitle;
//   e_message_box                                m_emessagebox;
//   string                                       m_strDetails;


};


CLASS_DECL_ACME void message_box_asynchronous(::function < void(const ::atom & atom) > function, ::particle * pparticle, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails)
{

   auto pmessagebox = __allocate< message_box >();

   pmessagebox->m_pobject = pparticle;
   pmessagebox->initialize_conversation(scopedstrMessage,scopedstrTitle, emessagebox, scopedstrDetails);

   //pparticle->fork([pmessagebox]()
   //{

   //initialize_nano_window(pparticle->factory());

   if (::is_null(pparticle))
   {

      throw ::exception(error_null_pointer);
      
   }

#if defined(UNIVERSAL_WINDOWS)

   if(pparticle->platform()->m_bConsole || !is_ui_possible())
   {

      auto result = message_box_for_console(scopedstrMessage, scopedstrTitle, emessagebox, scopedstrDetails);

      function(result);

   }
   else
   {

      throw ::exception(error_failed);

   }
   
#endif

   pparticle->system()->nano();
   
   //main_asynchronous([ pmessagebox, pparticle ]()
   //{

      auto pnanomessagebox = pparticle->__create_new < nano_message_box >();
   
      atom idResult;
   
      manual_reset_event event;

      pnanomessagebox->initialize_conversation(
         pmessagebox->m_strMessage,
         pmessagebox->m_strTitle,
         pmessagebox->m_emessagebox,
         pmessagebox->m_strDetails);

      pnanomessagebox->m_functionClose = [ pmessagebox ](nano_window * pwindow)
      {
      
         auto result = pwindow->m_payloadResult;
         
         if(pmessagebox->m_function)
         {
      
            pmessagebox->m_function(result);
            
         }
      
      };

      pnanomessagebox->do_asynchronously();

   //});

}


void nano_message_box::on_click(const ::atom & atom, ::user::mouse * pmouse)
{

   if (atom == "details")
   {

      auto psequencer = __create_new < ::sequencer < ::conversation > >();

      auto pdetailswindow = __create_new < nano_details_window >();

      psequencer->m_psequence = pdetailswindow;

      pdetailswindow->m_psequencer = psequencer;

      pdetailswindow->initialize_conversation(m_strDetails, m_strTitle + " : Details", e_message_box_ok, m_strDetails);

      pdetailswindow->do_synchronously();

      m_payloadResult.unset();

      return;

   }

   m_payloadResult = atom;

   destroy();

}


void nano_message_box::on_right_click(const ::atom & atom, ::user::mouse * pmouse)
{

   auto pbutton = __create_new < popup_button >();

   pbutton->m_functionClose = [this](nano_window * pwindow)
   {

      auto result = pwindow->m_payloadResult.as_atom();

      if (result == e_dialog_result_yes)
      {

         display_temporary_file_with_text(m_strMessage + "\n\n" + m_strDetails);

      }

   };

   pbutton->initialize_popup_button("Dump to File...", pmouse->m_pointAbsolute.x(), pmouse->m_pointAbsolute.y());

   pbutton->do_asynchronously();

}


bool nano_message_box::is_popup_window() const
{
   
   return true;
   
}



