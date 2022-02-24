//
// Created by camilo on 2022-02-16 22:42 <3ThomasBorregaardS�rensen!!
//
#include "framework.h"
#include "_nano.h"


popup_button::popup_button()
{

   m_bArbitraryPositioning = true;

}



popup_button::~popup_button()
{


}



void popup_button::calculate_size()
{


   auto sizeScreen = operating_system_get_main_screen_size();

   int wScreen = sizeScreen.cx;
   int hScreen = sizeScreen.cy;

   int w = 150;
   int h = 50 * 2;
   int x = (wScreen - w) / 2;
   int y = (hScreen - h) / 2;

   m_rectangle.set_dim(x, y, w, h);

}


void popup_button::display_synchronously(const ::string & strText)
{

   calculate_size();

   add_button(strText, e_dialog_result_yes);

   add_button("Cancel", e_dialog_result_cancel);

   int wButton = 150;

   int hButton = 50;

   int iRight = m_rectangle.width();

   int iBottom = m_rectangle.height();

   int wSpacing = 25;

   for (index iButton = m_buttona.get_upper_bound(); iButton >= 0; iButton--)
   {

      auto pbutton = m_buttona[iButton];

      pbutton->m_rectangle.bottom = iBottom;
      pbutton->m_rectangle.top = pbutton->m_rectangle.bottom - hButton;
      pbutton->m_rectangle.right = iRight;
      pbutton->m_rectangle.left = pbutton->m_rectangle.right - wButton;

      iBottom = pbutton->m_rectangle.top;

   }

   create();

   nano_window::display_synchronously();

}


void popup_button::on_draw(nano_device * pnanodevice)
{

   /*rectangle_i32 rectangleText;

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
      m_pfont);*/

}



