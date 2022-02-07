//
// Created by camilo on 2022-01-21 14:57 <3ThomasBorregaardSørensen
// Generalization by camilo on 31/01/2022 14:53 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system.h"
#include "_nano.h"


nano_message_box::nano_message_box()
{

   m_bStartCentered = true;

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


void nano_message_box::add_button(const char * pszText, enum_dialog_result edialogresult)
{

   auto pbutton = __new(nano_button);

   pbutton->m_strText = pszText;
   pbutton->m_atom = edialogresult;

   m_buttona.add(pbutton);

   add_child(pbutton);

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


   auto sizeScreen = operating_system_get_main_screen_size();

   int wScreen = sizeScreen.cx;
   int hScreen = sizeScreen.cy;

   int w = wScreen / 2;
   int h = (w / 16) * 5;
   int x = (wScreen - w) / 2;
   int y = (hScreen - h) / 2;

   m_rectangle.set_dim(x, y, w, h);



}


void nano_message_box::display_synchronously(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails)
{

   calculate_size();

   m_strMessage = strMessage;

   m_strDetails = strDetails;

   m_strTitle = strTitle;

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

   if (strDetails.has_char())
   {

      m_pstillDetails = __new(nano_still);

      m_pstillDetails->m_atom = "details";

      m_pstillDetails->m_strText = "Details...";

      m_pstillDetails->m_bHyperlink = true;

      add_child(m_pstillDetails);

   }

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

   int wButton = 150;

   int hButton = 50;

   int iRight = m_rectangle.width() - 25;

   int iBottom = m_rectangle.height() - 25;

   int wSpacing = 25;

   for (index iButton = m_buttona.get_upper_bound(); iButton >= 0; iButton--)
   {

      auto pbutton = m_buttona[iButton];

      pbutton->m_rectangle.bottom = iBottom;
      pbutton->m_rectangle.top = pbutton->m_rectangle.bottom - hButton;
      pbutton->m_rectangle.right = iRight;
      pbutton->m_rectangle.left = pbutton->m_rectangle.right - wButton;

      iRight = pbutton->m_rectangle.left - wSpacing;

   }

   create();


   nano_window::display_synchronously();

}


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



CLASS_DECL_ACME ::atom os_message_box(::object * pobject, const char * pszMessage, const char * pszTitle, enum_message_box emessagebox, const ::string & strDetails)
{

   initialize_nano();

   auto pmessagebox = pobject->__create_new < nano_message_box >();

   pmessagebox->display_synchronously(pszMessage, pszTitle, emessagebox, strDetails);

   auto idResult = pmessagebox->get_result();

   return idResult;

}


void nano_message_box::on_click(const ::atom & atom)
{


   if (atom == "details")
   {

      auto pdetailswindow = __create_new < nano_details_window >();

      pdetailswindow->m_strMessage = m_strDetails;

      pdetailswindow->display_synchronously(m_strDetails, m_strTitle + " : Details", e_message_box_ok);


      return;

   }

   m_atomResult = atom;

   destroy();

}



