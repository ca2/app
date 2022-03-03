//
// Created by camilo on 06/02/2022 12:17 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "acme/operating_system.h"
#include "_nano.h"


nano_details_window::nano_details_window()
{
   
   m_efont = e_font_monospace;

   m_strLabelDetails = "Dump to file";

}


nano_details_window::~nano_details_window()
{


}


void nano_details_window::calculate_size()
{


   auto sizeScreen = operating_system_get_main_screen_size();

   int wScreen = sizeScreen.cx;
   int hScreen = sizeScreen.cy;

   int w = wScreen / 2;
   int h = (w /8) * 5;
   int x = (wScreen - w) / 2;
   int y = (hScreen - h) / 2;

   m_rectangle.set_dim(x, y, w, h);



}


void nano_details_window::on_click(const ::atom& atom, int x, int y)
{

   if (atom == "details")
   {

      //string m_strDetails;

      display_temporary_file_with_text(m_strDetails);

      //pdetailswindow->display_synchronously(m_strDetails, m_strTitle + " : Details", e_message_box_ok, m_strDetails);

      //m_atomResult.clear();

      return;

   }

   nano_message_box::on_click(atom, x, y);

}



