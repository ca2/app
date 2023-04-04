//
// Created by camilo on 06/02/2022 12:17 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "details_window.h"
#include "window_implementation.h"
#include "button.h"
#include "acme/primitive/geometry2d/_geometry2d.h"
//#include "acme/operating_system.h"


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


#if !defined(UNIVERSAL_WINDOWS) && !defined(ANDROID)

   //int wScreen = 1280;
   //int hScreen = 768;

   auto sizeScreen = m_pimplementation->get_main_screen_size();

   //operating_system_get_main_screen_size(wScreen, hScreen);

   auto wScreen = sizeScreen.cx;

   auto hScreen = sizeScreen.cy;

   int w = wScreen / 2;
   int h = (w /8) * 5;
   int x = (wScreen - w) / 2;
   int y = (hScreen - h) / 2;

   m_rectangle.set_dimension(x, y, w, h);

#endif

}


void nano_details_window::on_click(const ::atom& atom, ::user::mouse * pmouse)
{

   if (atom == "details")
   {

      //string m_strDetails;

      display_temporary_file_with_text(m_strDetails);

      //pdetailswindow->display_synchronously(m_strDetails, m_strTitle + " : Details", e_message_box_ok, m_strDetails);

      //m_atomResult.clear();

      return;

   }

   nano_message_box::on_click(atom, pmouse);

}




