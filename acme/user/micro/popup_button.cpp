//
// Created by camilo on 2022-02-16 22:42 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "popup_button.h"
#include "button.h"
#include "acme/windowing/window.h"
#include "acme/platform/system.h"
#include "acme/user/user/mouse.h"
#include "acme/windowing/display.h"
#include "acme/windowing/windowing.h"


namespace micro
{


   popup_button::popup_button()
   {

      m_bTopMost = true;

   }


   popup_button::~popup_button()
   {


   }


   void popup_button::calculate_size_and_position(::i32 x, ::i32 y)
   {

#if !defined(UNIVERSAL_WINDOWS) && !defined(__ANDROID__)

      //::i32 wScreen = 1280;
      //::i32 hScreen = 768;

      auto sizeScreen = system()->acme_windowing()->acme_display()->get_main_screen_size();

      //operating_system_get_main_screen_size(wScreen, hScreen);

      auto wScreen = sizeScreen.cx;

      auto hScreen = sizeScreen.cy;

      //printf("popup_button::calculate_size_and_position (wScreen,hScreen)=%d,%d\n", wScreen, hScreen);

      ::i32 w = 150;
      ::i32 h = 50 * 2;

      if (x == INT_MIN || y == INT_MIN)
      {

         x = (wScreen - w) / 2;

         y = (hScreen - h) / 2;

      }

      m_rectangle.set_dimension(x, y, w, h);

      ::i32_rectangle rectangleMainScreen;

      rectangleMainScreen.set_dimension(0, 0, wScreen, hScreen);

      rectangleMainScreen.deflate(10);

      m_rectangle._001Constrain(rectangleMainScreen);

#endif

   }


   void popup_button::create_window()
   {

      ::micro::main_window::create_window();

      m_bTopMost = true;

      m_bArbitraryPositioning = true;

   }


   void popup_button::initialize_popup_button(const ::scoped_string & scopedstrText, ::i32 x, ::i32 y, ::acme::user::interaction * pacmeuserinteractionOwner)
   {

//      m_pdialog = message_box(scopedstrText);

      m_pacmeuserinteractionOwner = pacmeuserinteractionOwner;

      calculate_size_and_position(x, y);

      add_button(scopedstrText, e_dialog_result_yes, 'y');

      add_button("Cancel", e_dialog_result_cancel, 'c');

      ::i32 wButton = 150;

      ::i32 hButton = 50;

      ::i32 iRight = m_rectangle.width();

      ::i32 iBottom = m_rectangle.height();

      ::i32 wSpacing = 25;

      auto countButton = micro_button_count();

      for (::collection::index iButton = countButton - 1; iButton >= 0; iButton--)
      {

         auto pmicrobutton = micro_button_at(iButton);

         pmicrobutton->m_rectangle.bottom = iBottom;

         pmicrobutton->m_rectangle.top = pmicrobutton->m_rectangle.bottom - hButton;
         pmicrobutton->m_rectangle.right = iRight;
         pmicrobutton->m_rectangle.left = pmicrobutton->m_rectangle.right - wButton;

         iBottom = pmicrobutton->m_rectangle.top;

         if (iButton >= 1)
         {

            pmicrobutton->m_rectangle.top--;

         }

      }

      //main_asynchronous([this]()
      //   {

      //      create();

      //      micro::interchange::display();

      //      aaa_message_loop();

      //   });

   }


   void popup_button::on_draw(::nano::graphics::context * pgraphicscontext)
   {

      /*i32_rectangle rectangleText;

      get_client_rectangle(rectangleText);

      rectangleText.bottom = rectangleText.top + rectangleText.height() * 3 / 4;

      rectangleText.deflate(25);

      pgraphicscontext->draw_text123(
         m_strMessage,
         rectangleText,
         e_align_top_left,
         e_draw_text_word_break,
         m_pbrushWindow,
         m_pbrushText,
         m_pfont);*/

   }


   void popup_button::set_dialog_response(const ::payload & payloadResult)
   {

      ::user_interface::dialog_implementation::set_dialog_response(payloadResult);
//      ::dialog_reifier::set_dialog_result(payloadResult);
      //m_payloadPopupButtonResult = payloadResult;

      //on_dialog_result_set();

   }


   void popup_button::on_click(const ::payload & payload, ::user::mouse * pmouse)
   {

      //::micro::dialog::on_click(payload, pmouse);
      //m_payloadPopupButtonResult = payload;

      //destroy();

      set_dialog_response(payload);
      
      pmouse->m_bRet = true;
      
      //return true;
   }


   ::pointer < ::operating_system::a_system_menu > popup_button::create_system_menu(bool bContextual)
   {

      return {};

   }



} // namespace micro


