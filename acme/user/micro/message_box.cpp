//
// Created by camilo on 2022-01-21 14:57 <3ThomasBorregaardSorensen
// Generalization by camilo on 31/01/2022 14:53 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "button.h"
#include "message_box.h"
#include "still.h"
#include "theme.h"
#include "acme/handler/sequence.h"
#include "acme/nano/graphics/device.h"
#include "acme/nano/graphics/icon.h"
#include "acme/user/micro/details_window.h"
#include "acme/user/micro/popup_button.h"
#include "acme/windowing/window.h"
#include "acme/operating_system/console_message_box.h"
#include "acme/operating_system/message_box.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
//#include "acme/handler/sequence.h"
#include "acme/platform/system.h"
#include "acme/platform/timer.h"
#include "acme/user/user/mouse.h"
#include "acme/_operating_system.h"
#include "acme/user/micro/user.h"
#include "acme/windowing/display.h"
#include "acme/windowing/windowing.h"


bool is_ui_possible();


void ns_do_main_loop(double dSeconds);


namespace micro
{


   message_box::message_box()
   {

      auto & r = m_rectangle;

      id() = e_dialog_result_none;

      set_flag(e_flag_should_create_sequence_on_synchronicity);

   }


   message_box::~message_box()
   {


   }


   ::string message_box::get_title()
   {

      return m_prealizable->m_strTitle;

   }


   void message_box::create_window()
   {

      ::micro::main_window::create_window();


   }


   void message_box::on_before_create_window(::acme::windowing::window* pacmewindowingwindow)
   {

      ::micro::dialog::on_before_create_window(pacmewindowingwindow);

      m_bStartCentered = true;

      m_strLabelDetails = "Details...";

      m_bMinimizeBox = false;
      m_bMaximizeBox = false;
      m_bResizeable = false;

      auto r = m_rectangle;


      m_pacmewindowingwindow->m_pointWindow = r.origin();
      m_pacmewindowingwindow->m_sizeWindow = r.size();

   }


   void message_box::destroy()
   {

      ::micro::dialog::destroy();
      ::acme::user::message_box::destroy();

   }


   void message_box::on_draw(::nano::graphics::device* pmicrodevice)
   {

      int_rectangle rectangleText;

      rectangleText = get_client_rectangle();

      rectangleText.bottom = rectangleText.top + rectangleText.height() * 3 / 4;

      rectangleText.deflate(25);

      if (m_picon)
      {

         pmicrodevice->draw(m_picon, 25, 25, 48, 48);

         rectangleText.left += 48 + 10;

      }

      pmicrodevice->draw_text123(
         m_prealizable->m_strMessage,
         rectangleText,
         e_align_top_left,
         e_draw_text_word_break,
         micro_theme()->m_pbrushWindow,
         micro_theme()->m_pbrushText,
         micro_theme()->m_pfont);

   }


   void message_box::defer_create_details_still()
   {

      if (m_prealizable->m_strDetails.has_character())
      {

         m_pstillDetails = øallocate::micro::still();

         m_pstillDetails->id() = "details";

         m_pstillDetails->m_strText = m_strLabelDetails;

         m_pstillDetails->m_bHyperlink = true;

         add_child(m_pstillDetails);

      }

   }


   ::collection::count get_line_count(const ::scoped_string & scopedstr)
   {

      ::collection::index iFind = 0;

      ::collection::count cLine = 1;

      while ((iFind = scopedstr(iFind).find_index('\n')) >= 0)
      {

         cLine++;

         iFind++;

      }

      return cLine;

   }


   void message_box::set_icon(::nano::graphics::icon* picon)
   {


      m_picon = picon;


   }


   void message_box::add_button(const ::scoped_string& scopedstrText, enum_dialog_result edialogresult, char chLetter)
   {

      ::micro::dialog::add_button(scopedstrText, edialogresult, chLetter);

   }


   void message_box::on_realize(::message_box* pmessagebox)
   {

      calculate_size();

      ::acme::user::message_box::on_realize(pmessagebox);

      set_icon(m_prealizable->m_picon);

      defer_create_details_still();

      if (m_prealizable->m_emessagebox & ::user::e_message_box_default_button_mask)
      {

         int iDefaultButtonMask = (int)(m_prealizable->m_emessagebox & ::user::e_message_box_default_button_mask);

         int iDefaultButtonIndex = iDefaultButtonMask >> 8;

         int iDefaultButton = iDefaultButtonIndex & 7;

         m_pacmeuserinteractionaChildren->element_at(iDefaultButton)->set_keyboard_focus();

      }
      else
      {

         m_pacmeuserinteractionaChildren->first()->set_keyboard_focus();

      }

      auto wButton = (int)(m_rectangle.width() * 0.2);

      auto hButton = (int)(m_rectangle.height() * 0.2);

      auto iRight = (int)(m_rectangle.width() - m_rectangle.width() * 0.025);

      auto iBottom = (int)(m_rectangle.height() - m_rectangle.width() * 0.025);

      auto wSpacing = (int)(m_rectangle.width() * 0.025);

      auto countButton = micro_button_count();

      for (auto iButton = countButton - 1; iButton >= 0; iButton--)
      {

         auto pmicrobutton = micro_button_at(iButton);

         pmicrobutton->m_rectangle.bottom = iBottom;
         pmicrobutton->m_rectangle.top = pmicrobutton->m_rectangle.bottom - hButton;
         pmicrobutton->m_rectangle.right = iRight;
         pmicrobutton->m_rectangle.left = pmicrobutton->m_rectangle.right - wButton;

         iRight = pmicrobutton->m_rectangle.left - wSpacing;

         printf_line("234");

      }

   }


   void message_box::calculate_size()
   {

#if !defined(UNIVERSAL_WINDOWS) && !defined(__ANDROID__)

      //int wScreen = 1280;
      //int hScreen = 768;

      auto sizeScreen = system()->acme_windowing()->acme_display()->get_main_screen_size();

      //operating_system_get_main_screen_size(wScreen, hScreen);

      auto wScreen = sizeScreen.cx;

      auto hScreen = sizeScreen.cy;

      //printf("message_box::calculate_size (wScreen,hScreen)=%d,%d\n", wScreen, hScreen);

      int w = wScreen / 2;

      if (w < 200)
      {

         w = wScreen * 9 / 10;

      }

      int h = (w / 16) * 5;

      if (wScreen < hScreen)
      {

         h = (w / 10) * 5;

      }
      int x = (wScreen - w) / 2;
      int y = (hScreen - h) / 2;

      m_rectangle.set_dimension(x, y, w, h);

#endif

   }


   void message_box::on_timer(::timer* ptimer)
   {

      if (ptimer->m_uTimer == 1021)
      {

         m_pstillTimeout->m_strText.formatf("%0.2fs", m_prealizable->m_psequence->remaining_from_timeout().floating_second());

         redraw();

      }

   }


   void message_box::set_dialog_result(const ::payload& payloadResult)
   {

      m_prealizable->m_payloadResult = payloadResult;

      on_dialog_result_set();

   }


   ::payload message_box::get_dialog_result()
   {

      return m_prealizable->m_payloadResult;

   }


   void message_box::on_create_window()
   {

      ::acme::user::interaction::on_create_window();

      int x = 25;

      if (m_picon)
      {

         x += 48 + 10;

      }

      if (m_pstillDetails)
      {

         m_pstillDetails->resize_to_fit();

         m_pstillDetails->m_rectangle.move_bottom_to(micro_button_at(0)->m_rectangle.bottom);

         m_pstillDetails->m_rectangle.move_left_to(x);

      }


      if (m_prealizable->m_psequence)
      {

         if (!m_prealizable->m_psequence->m_timeLocked.is_null())
         {

            m_pstillTimeout = øallocate::micro::still();

            m_pstillTimeout->id() = "timeout";

            add_child(m_pstillTimeout);

         }

      }
      if (m_pstillTimeout)
      {

         auto iBottom = (int)(m_rectangle.height() - m_rectangle.width() * 0.025);
         auto hButton = (int)(m_rectangle.height() * 0.2);
         auto wButton = (int)(m_rectangle.width() * 0.2);

         m_pstillTimeout->m_rectangle.bottom = iBottom;
         m_pstillTimeout->m_rectangle.top = m_pstillTimeout->m_rectangle.bottom - hButton / 2;
         m_pstillTimeout->m_rectangle.left = (int)(m_rectangle.width() * 0.025);
         m_pstillTimeout->m_rectangle.right = m_pstillTimeout->m_rectangle.left + wButton / 3;

         set_timer(1021, 200_ms);

      }
   }


#ifdef WINDOWS_DESKTOP
   CLASS_DECL_ACME int message_box_to_windows_message_box(::user::enum_message_box emessagebox);
   CLASS_DECL_ACME ::enum_dialog_result windows_message_box_result_to_dialog_result(int iResult);
#endif

#ifdef MACOS

   enum_dialog_result ns_alert_box(const_char_pointer pszMessage, const_char_pointer pszTitle, ::user::enum_message_box emessagebox);

#endif


   void message_box::on_click(const ::payload& payload, ::user::mouse* pmouse)
   {

      if (payload == "details")
      {

         //auto psequencer = øcreate_new < ::sequencer < ::conversation > >();

         auto pmessageboxDetails = __initialize_new::message_box(
            m_prealizable->m_strDetails,
            m_prealizable->m_strTitle + " : Details",
            ::user::e_message_box_ok,
            m_prealizable->m_strDetails);

         pmessageboxDetails->m_bDetails = true;

         pmessageboxDetails->send();

         pmouse->m_bRet = true;

         return;

      }
      else if (payload == "timeout")
      {

         pmouse->m_bRet = true;

         return;

      }

      set_dialog_result(payload);

      pmouse->m_bRet = true;

   }


   void message_box::on_right_click(const ::payload& payload, ::user::mouse* pmouse)
   {

      if (pmouse->m_pointHost.y < 48)
      {

         m_pacmewindowingwindow->defer_show_system_menu(pmouse);

         pmouse->m_bRet = true;

         return;

      }

      on_context_menu(pmouse);

      pmouse->m_bRet = true;

   }


   void message_box::on_context_menu(::user::mouse* pmouse)
   {

      auto ppopupbutton = øcreate_new<popup_button>();

      ::int_rectangle rectanglePointTo;

      rectanglePointTo.left = pmouse->m_pointAbsolute.x;
      rectanglePointTo.top = pmouse->m_pointAbsolute.y;
      rectanglePointTo.right = rectanglePointTo.left + 200;
      rectanglePointTo.bottom = rectanglePointTo.top + 2;

      ppopupbutton->acme_windowing_window()->m_rectanglePointingTo = rectanglePointTo;
#ifdef APPLE_IOS
      ppopupbutton->initialize_popup_button(
         "Dump to Clipboard...",
         pmouse->m_pointAbsolute.x, pmouse->m_pointAbsolute.y,
         this);
#else
      ppopupbutton->initialize_popup_button(
         "Dump to File...",
         pmouse->m_pointAbsolute.x, pmouse->m_pointAbsolute.y,
         this);
#endif
      ppopupbutton->main_async()
         << [this, ppopupbutton]()
         {

            auto result = ppopupbutton->m_payloadPopupButtonResult;

            if (result == e_dialog_result_yes)
            {

#ifdef APPLE_IOS

               system()->acme_windowing()->set_clipboard_text(
                  m_prealizable->m_strMessage + "\n\n"
                  + m_prealizable->m_strDetails);
               
#else

               display_temporary_file_with_text(
                  m_prealizable->m_strMessage + "\n\n"
                  + m_prealizable->m_strDetails);

#endif

            }

         };

      pmouse->m_bRet = true;
      
   }

   bool message_box::is_popup_window() const
   {

      return true;

   }


} // namespace micro



