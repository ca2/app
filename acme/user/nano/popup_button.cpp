//
// Created by camilo on 2022-02-16 22:42 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window.h"
#include "window_implementation.h"
#include "popup_button.h"
#include "button.h"
//#include "acme/primitive/geometry2d/_geometry2d.h"


popup_button::popup_button()
{

   m_bTopMost = true;

   m_bArbitraryPositioning = true;

}


popup_button::~popup_button()
{


}



void popup_button::calculate_size_and_position(int x, int y)
{

#if !defined(UNIVERSAL_WINDOWS) && !defined(ANDROID)

   //int wScreen = 1280;
   //int hScreen = 768;

   auto sizeScreen = m_pimplementation->get_main_screen_size();

   //operating_system_get_main_screen_size(wScreen, hScreen);

   auto wScreen = sizeScreen.cx();

   auto hScreen = sizeScreen.cy();

   //printf("popup_button::calculate_size_and_position (wScreen,hScreen)=%d,%d\n", wScreen, hScreen);

   int w = 150;
   int h = 50 * 2;
   
   if (x == INT_MIN || y == INT_MIN)
   {

      x = (wScreen - w) / 2;

      y = (hScreen - h) / 2;

   }

   m_rectangle.set_dimension(x, y, w, h);

   ::rectangle_i32 rectangleMainScreen;

   rectangleMainScreen.set_dimension(0, 0, wScreen, hScreen);

   rectangleMainScreen.deflate(10);

   m_rectangle._001Constrain(rectangleMainScreen);

#endif

}


void popup_button::initialize_popup_button(const ::string & strText, int x, int y)
{

   calculate_size_and_position(x, y);

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

      pbutton->m_rectangle.bottom() = iBottom;
      pbutton->m_rectangle.top() = pbutton->m_rectangle.bottom() - hButton;
      pbutton->m_rectangle.right() = iRight;
      pbutton->m_rectangle.left() = pbutton->m_rectangle.right() - wButton;

      iBottom = pbutton->m_rectangle.top();

   }

   //main_asynchronous([this]()
   //   {

   //      create();

   //      nano_window::display();

   //      message_loop();

   //   });

}


void popup_button::on_draw(nano_device * pnanodevice)
{

   /*rectangle_i32 rectangleText;

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
      m_pfont);*/

}



