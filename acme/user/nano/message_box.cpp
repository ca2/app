//
// Created by camilo on 2022-01-21 14:57 <3ThomasBorregaardSørensen
// Generalization by camilo on 31/01/2022 14:53 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system.h"
#include "_nano.h"


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

   rectangleText.bottom = rectangleText.top + rectangleText.height() * 3 / 4;

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

      m_pstillDetails = __new(nano_still);

      m_pstillDetails->m_atom = "details";

      m_pstillDetails->m_strText = m_strLabelDetails;

      m_pstillDetails->m_bHyperlink = true;

      add_child(m_pstillDetails);

   }

}


::count get_line_count(const ::string & str)
{

   strsize iFind = 0;

   ::count cLine = 1;

   while ((iFind = str.find('\n', iFind)) >= 0)
   {

      cLine++;

      iFind++;

   }

   return cLine;

}


void nano_message_box::calculate_size()
{


#if !defined(_UWP) && !defined(ANDROID)

   //int wScreen = 1280;
   //int hScreen = 768;

   auto sizeScreen = m_pimplementation->get_main_screen_size();

   //operating_system_get_main_screen_size(wScreen, hScreen);

   auto wScreen = sizeScreen.cx;

   auto hScreen = sizeScreen.cy;

   //printf("nano_message_box::calculate_size (wScreen,hScreen)=%d,%d\n", wScreen, hScreen);

   int w = wScreen / 2;
   int h = (w / 16) * 5;
   int x = (wScreen - w) / 2;
   int y = (hScreen - h) / 2;

   m_rectangle.set_dim(x, y, w, h);

   //printf("nano_message_box::calculate_size (w,h)=%d,%d\n", w, h);


#endif

}


void nano_message_box::initialize_conversation(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails)
{
   
   conversation_message::initialize_conversation(strMessage, strTitle, emessagebox, strTitle);

   calculate_size();

   auto emessageboxType = emessagebox & e_message_box_type_mask;

   switch (emessageboxType)
   {
      case e_message_box_ok_cancel:
         add_button("OK", e_dialog_result_ok);
         add_button("Cancel", e_dialog_result_cancel);
         break;
      case e_message_box_abort_retry_ignore:
         add_button("Abort", e_dialog_result_abort);
         add_button("Retry", e_dialog_result_retry);
         add_button("Ignore", e_dialog_result_ignore);
         break;
      case e_message_box_yes_no_cancel:
         add_button("Yes", e_dialog_result_yes);
         add_button("No", e_dialog_result_no);
         add_button("Cancel", e_dialog_result_cancel);
         break;
      case e_message_box_yes_no:
         add_button("Yes", e_dialog_result_yes);
         add_button("No", e_dialog_result_no);
         break;
      case e_message_box_retry_cancel:
         add_button("Retry", e_dialog_result_retry);
         add_button("Cancel", e_dialog_result_cancel);
         break;
      case e_message_box_cancel_try_continue:
         add_button("Cancel", e_dialog_result_cancel);
         add_button("Try", e_dialog_result_try_again);
         add_button("Continue", e_dialog_result_continue);
         break;
      default:
         add_button("OK", e_dialog_result_ok);
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

   for (index iButton = m_buttona.get_upper_bound(); iButton >= 0; iButton--)
   {

      auto pbutton = m_buttona[iButton];

      pbutton->m_rectangle.bottom = iBottom;
      pbutton->m_rectangle.top = pbutton->m_rectangle.bottom - hButton;
      pbutton->m_rectangle.right = iRight;
      pbutton->m_rectangle.left = pbutton->m_rectangle.right - wButton;

      iRight = pbutton->m_rectangle.left - wSpacing;

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

      m_pstillDetails->m_rectangle.move_bottom_to(m_buttona[0]->m_rectangle.bottom);

      m_pstillDetails->m_rectangle.move_left_to(25);

   }

}


//__pointer(::sequence < ::conversation >) nano_message_box::display(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox)
//{
//
//   auto psequence = __new(::sequence <::conversation >());
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


CLASS_DECL_ACME ::acme::system * get_system();


CLASS_DECL_ACME ::atom message_box_synchronous(::object * pobject, const char * pszMessage, const char * pszTitle, enum_message_box emessagebox, const char * pszDetails)
{

   initialize_nano_window();

   if (::is_null(pobject))
   {

      pobject = ::get_system();
      
   }

#if defined(_UWP)

   if(pobject->m_psystem->m_bConsole || !is_ui_possible())
   {

      return message_box_for_console(pszMessage, pszTitle, emessagebox, pszDetails);

   }
   else
   {

      throw ::exception(error_failed);

   }
   
#endif
   
   auto psequencer = pobject->create_message_box_sequencer(pszMessage, pszTitle, emessagebox, pszDetails);
   
   auto atomResult = psequencer->do_synchronously();
   
//   auto pmanualresetevent = __new(manual_reset_event);
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
////   auto pmessagebox = pobject->__create_new < nano_message_box >();
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
   __pointer(::object)                          m_pobject;
//   string                                       m_strMessage;
//   string                                       m_strTitle;
//   e_message_box                                m_emessagebox;
//   string                                       m_strDetails;


};


CLASS_DECL_ACME void message_box_asynchronous(::function < void(const ::atom & atom) > function, ::object * pobject, const char * pszMessage, const char * pszTitle, enum_message_box emessagebox, const char * pszDetails)
{

   auto pmessagebox = __new(message_box);

   pmessagebox->m_pobject = pobject;
   pmessagebox->initialize_conversation(pszMessage,pszTitle, emessagebox, pszDetails);

   //pobject->fork([pmessagebox]()
   //{

   initialize_nano_window();

   if (::is_null(pobject))
   {

      pobject = ::get_system();
      
   }

#if defined(_UWP)

   if(pobject->m_psystem->m_bConsole || !is_ui_possible())
   {

      auto result = message_box_for_console(pszMessage, pszTitle, emessagebox, pszDetails);

      function(result);

   }
   else
   {

      throw ::exception(error_failed);

   }
   
#endif
   
   //main_asynchronous([ pmessagebox, pobject ]()
   //{

      auto pnanomessagebox = pobject->__create_new < nano_message_box >();
   
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

      auto psequencer = __new(::sequencer < ::conversation >());

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

      auto result = pwindow->m_payloadResult;

      if (result == e_dialog_result_yes)
      {

         display_temporary_file_with_text(m_strMessage + "\n\n" + m_strDetails);

      }

   };

   pbutton->initialize_popup_button("Dump to File...", pmouse->m_point.x, pmouse->m_point.y);

   pbutton->do_asynchronously();

}


bool nano_message_box::is_popup_window() const
{
   
   return true;
   
}



