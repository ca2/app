//
// Created by camilo on 2022-02-16 22:42 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "interchange.h"
#include "window_implementation.h"
#include "popup_button.h"
#include "button.h"
#include "acme/windowing/window_base.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"


namespace nano
{


namespace user
{


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

#if !defined(UNIVERSAL_WINDOWS) && !defined(__ANDROID__)

   //int wScreen = 1280;
   //int hScreen = 768;

   auto sizeScreen = m_pwindowbase->get_main_screen_size();

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

   ::int_rectangle rectangleMainScreen;

   rectangleMainScreen.set_dimension(0, 0, wScreen, hScreen);

   rectangleMainScreen.deflate(10);

   m_rectangle._001Constrain(rectangleMainScreen);

#endif

}


void popup_button::initialize_popup_button(const ::scoped_string & scopedstrText, int x, int y)
{

   calculate_size_and_position(x, y);

   add_button(strText, e_dialog_result_yes, 'y');

   add_button("Cancel", e_dialog_result_cancel, 'c');

   int wButton = 150;

   int hButton = 50;

   int iRight = m_rectangle.width();

   int iBottom = m_rectangle.height();

   int wSpacing = 25;

   for (::collection::index iButton = m_nanobuttona.get_upper_bound(); iButton >= 0; iButton--)
   {

      auto pnanobutton = m_nanobuttona[iButton];

      pnanobutton->m_rectangle.bottom() = iBottom;
      
      pnanobutton->m_rectangle.top() = pnanobutton->m_rectangle.bottom() - hButton;
      pnanobutton->m_rectangle.right() = iRight;
      pnanobutton->m_rectangle.left() = pnanobutton->m_rectangle.right() - wButton;

      iBottom = pnanobutton->m_rectangle.top();

      if (iButton >= 1)
      {

         pnanobutton->m_rectangle.top()--;

      }

   }

   //main_asynchronous([this]()
   //   {

   //      create();

   //      micro::interchange::display();

   //      aaa_message_loop();

   //   });

}


void popup_button::on_draw(::nano::graphics::device * pnanodevice)
{

   /*int_rectangle rectangleText;

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





void popup_button::on_click(const ::payload& payload, ::user::mouse * pmouse)
{

   m_payloadResult = payload;

   destroy();

}


   } // namespace user


} // namespace nano


