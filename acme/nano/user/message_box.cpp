//
// Created by camilo on 2022-01-21 14:57 <3ThomasBorregaardSorensen
// Generalization by camilo on 31/01/2022 14:53 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "button.h"
#include "message_box.h"
#include "still.h"
#include "theme.h"
#include "acme/nano/graphics/device.h"
#include "acme/nano/graphics/icon.h"
#include "acme/nano/user/details_window.h"
#include "acme/nano/user/popup_button.h"
#include "acme/nano/windowing/window.h"
#include "acme/operating_system/console_message_box.h"
#include "acme/operating_system/message_box.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/sequencer.h"
#include "acme/platform/system.h"
#include "acme/user/user/mouse.h"
#include "acme/_operating_system.h"
#include "acme/nano/user/user.h"


bool is_ui_possible();
void ns_do_main_loop(double dSeconds);


namespace nano
{


   namespace user
   {


      message_box::message_box()
      {

      }


      message_box::~message_box()
      {


      }


      void message_box::create_window()
      {

         ::nano::user::main_window::create_window();

         m_pwindow->m_bStartCentered = true;

         m_strLabelDetails = "Details...";

         m_pwindow->m_bMinimizeBox = false;
         m_pwindow->m_bMaximizeBox = false;
         m_pwindow->m_bResizeable = false;




      }


      void message_box::on_draw(::nano::graphics::device * pnanodevice)
      {

         rectangle_i32 rectangleText;

         rectangleText = get_client_rectangle();

         rectangleText.bottom() = rectangleText.top() + rectangleText.height() * 3 / 4;

         rectangleText.deflate(25);

         if(m_picon)
         {

            pnanodevice->draw(m_picon, 25, 25, 48, 48);

            rectangleText.left() += 48+10;

         }

         pnanodevice->draw_text123(
            m_strMessage,
            rectangleText,
            e_align_top_left,
            e_draw_text_word_break,
            nano_user_theme()->m_pbrushWindow,
            nano_user_theme()->m_pbrushText,
            nano_user_theme()->m_pfont);

      }


      void message_box::defer_create_details_still()
      {

         if (m_strDetails.has_char())
         {

            m_pstillDetails = ::place(new ::nano::user::still());

            m_pstillDetails->m_atom = "details";

            m_pstillDetails->m_strText = m_strLabelDetails;

            m_pstillDetails->m_bHyperlink = true;

            add_child(m_pstillDetails);

         }

      }


      ::collection::count get_line_count(const ::string & str)
      {

         ::collection::index iFind = 0;

         ::collection::count cLine = 1;

         while ((iFind = str(iFind).find_index('\n')) >= 0)
         {

            cLine++;

            iFind++;

         }

         return cLine;

      }


      void message_box::set_icon(::nano::graphics::icon* picon)
      {
         m_picon = picon;
      //    if(!picon)
      //    {
      // m_pstillIcon = nullptr;
      //
      //       return;
      //
      //    }
      //    __construct_new(m_pstillIcon);
      //
      //    m_pstillIcon->set_icon(picon);
      }

      
      void message_box::calculate_size()
      {

      #if !defined(UNIVERSAL_WINDOWS) && !defined(ANDROID)

         //int wScreen = 1280;
         //int hScreen = 768;

         auto sizeScreen = nano_windowing_window()->get_main_screen_size();

         //operating_system_get_main_screen_size(wScreen, hScreen);

         auto wScreen = sizeScreen.cx();

         auto hScreen = sizeScreen.cy();

         //printf("message_box::calculate_size (wScreen,hScreen)=%d,%d\n", wScreen, hScreen);

         int w = wScreen / 2;
         int h = (w / 16) * 5;
         int x = (wScreen - w) / 2;
         int y = (hScreen - h) / 2;

         m_rectangle.set_dimension(x, y, w, h);

         //printf("message_box::calculate_size (w,h)=%d,%d\n", w, h);


      #endif

      }


      void message_box::initialize_conversation(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails, ::nano::graphics::icon * picon)
      {

         conversation_message::initialize_conversation(strMessage, strTitle, emessagebox, strDetails, picon);

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

         set_icon(picon);

         defer_create_details_still();

         if (emessagebox & e_message_box_default_button_mask)
         {

            int iDefaultButtonMask = (int)(emessagebox & e_message_box_default_button_mask);

            int iDefaultButtonIndex = iDefaultButtonMask >> 8;

            int iDefaultButton = iDefaultButtonIndex & 7;

            m_elementalaChildren[iDefaultButton]->set_focus();

         }
         else
         {

            m_elementalaChildren[0]->set_focus();

         }

         auto wButton = (::i32) (m_rectangle.width() * 0.2);

         auto hButton = (::i32) (m_rectangle.height() * 0.2);

         auto iRight = (::i32) (m_rectangle.width() - m_rectangle.width() * 0.025);

         auto iBottom = (::i32) (m_rectangle.height() - m_rectangle.width() * 0.025);

         auto wSpacing = (::i32) (m_rectangle.width() * 0.025);

         auto countButton = nano_user_button_count();

         for (auto iButton = countButton - 1; iButton >= 0; iButton--)
         {

            auto pnanobutton = nano_user_button_at(iButton);

            pnanobutton->m_rectangle.bottom() = iBottom;
            pnanobutton->m_rectangle.top() = pnanobutton->m_rectangle.bottom() - hButton;
            pnanobutton->m_rectangle.right() = iRight;
            pnanobutton->m_rectangle.left() = pnanobutton->m_rectangle.right() - wButton;

            iRight = pnanobutton->m_rectangle.left() - wSpacing;

         }


      }


      //void message_box::initialize_message_box(const ::string & strMessage, const string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails)
      //{
      //
      //   m_functionClose = [this](nano::user::interchange * pinterchange)
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



      //void message_box::do_message_box(const ::string& strMessage, const string& strTitle, const ::e_message_box& emessagebox, const ::string & strDetails)
      //{
      //
      //   m_functionClose = [this](nano::user::interchange* pinterchange)
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


      void message_box::on_before_create_window(::nano::windowing::window * pwindowbase)
      {

         // pwindowbase->m_bMinimizeBox = false;
         // pwindowbase->m_bMaximizeBox = false;
         // pwindowbase->m_bResizeable = false;

      }


      void message_box::on_create_window()
      {

         ::nano::user::interaction::on_create_window();

         int x = 25;

         if(m_picon)
         {

            x+= 48 + 10;

         }

         if (m_pstillDetails)
         {

            m_pstillDetails->resize_to_fit();

            m_pstillDetails->m_rectangle.move_bottom_to(nano_user_button_at(0)->m_rectangle.bottom());

            m_pstillDetails->m_rectangle.move_left_to(x);

         }

      }


      //pointer< ::sequence < ::conversation > > message_box::display(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox)
      //{
      //
      //   auto psequence = ::place(new ::sequence <::conversation > ());
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


      //LRESULT message_box::window_procedure(UINT message, WPARAM wparam, LPARAM lparam)
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




      struct message_box_conversation_message :
         virtual public conversation_message
      {
      public:


         ::function < void(const ::payload & payload) >  m_function;
         ::pointer<::object>                             m_pobject;
      //   string                                        m_strMessage;
      //   string                                        m_strTitle;
      //   e_message_box                                 m_emessagebox;
      //   string                                        m_strDetails;


      };



      void message_box::on_click(const ::payload& payload, ::user::mouse * pmouse)
      {

         if (payload == "details")
         {

            auto psequencer = __create_new < ::sequencer < ::conversation > >();

            auto pdetailswindow = __create_new < ::nano::user::details_window >();

            psequencer->m_psequence = pdetailswindow;

            pdetailswindow->m_psequencer = psequencer;

            pdetailswindow->initialize_conversation(m_strDetails, m_strTitle + " : Details", e_message_box_ok, m_strDetails);

            pdetailswindow->do_synchronously();

            m_payloadResult.unset();

            return;

         }

         m_payloadResult = payload;

         destroy();

      }


      void message_box::on_right_click(const ::payload& payload, ::user::mouse * pmouse)
      {

         if (pmouse->m_pointHost.y() < 48)
         {

            m_pwindow->defer_show_system_menu(pmouse);

            return;

         }

         auto ppopupbutton = __create_new < popup_button >();

         auto pwindow = ppopupbutton->nano_windowing_window();

         pwindow->m_functionClose = [this](::nano::user::interaction * pinteraction)
         {

            auto result = pinteraction->m_payloadResult.as_atom();

            if (result == e_dialog_result_yes)
            {

               display_temporary_file_with_text(m_strMessage + "\n\n" + m_strDetails);

            }

         };

         auto pwindowParent = this->nano_windowing_window();

         ppopupbutton->initialize_popup_button("Dump to File...", pmouse->m_pointAbsolute.x(), pmouse->m_pointAbsolute.y(), pwindowParent);

         ppopupbutton->do_asynchronously();

      }


      bool message_box::is_popup_window() const
      {

         return true;

      }


   } // namespace user


} // namespace nano


CLASS_DECL_ACME pointer< ::sequencer < ::conversation > > message_box_sequencer(::particle * pparticle, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
{

   if (::is_null(pparticle))
   {
      
      auto psequencer = ::operating_system::message_box::create_sequencer(::platform::get()->system(),                                                        scopedstrMessage, scopedstrTitle,
                                                        emessagebox,
                                                        scopedstrDetails, picon);
      
      return psequencer;
//      auto pmessagebox = ::platform::get()->__create < ::operating_system::message_box >();
//
//      return pmessagebox->create_sequencer(scopedstrMessage, scopedstrTitle, emessagebox, scopedstrDetails);

   }

   //initialize_nano_window(pparticle->factory());

   if (::is_null(pparticle))
   {

      throw ::exception(error_null_pointer);
      
   }

#if defined(UNIVERSAL_WINDOWS)

   if(pparticle->platform()->m_bConsole || !is_ui_possible())
   {

      auto psequencer = pparticle->__create_new < ::sequencer < ::conversation > >();

      auto pmessagebox = pparticle->__create_new < ::operating_system::console_message_box >();

      psequencer->m_psequence = pmessagebox;

      pmessagebox->m_psequencer = psequencer;

      pmessagebox->initialize_conversation(scopedstrMessage, scopedstrTitle, emessagebox, scopedstrDetails);

      return psequencer;

//      return message_box_for_console(scopedstrMessage, scopedstrTitle, emessagebox, scopedstrDetails);

   }
   else
   {

      throw ::exception(error_failed);

   }
   
#endif

   auto psequencer = pparticle->node()->create_message_box_sequencer(scopedstrMessage, scopedstrTitle, emessagebox, scopedstrDetails, picon);
   
   return psequencer;
   
   //auto atomResult = psequencer->do_synchronously();
   
//   auto pmanualresetevent = ::place(new manual_reset_event());
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
////   auto pmessagebox = pparticle->__create_new < message_box >();
////
////   atom idResult;
////
////   manual_reset_event event;
////
////   pmessagebox->display(pszMessage, pszTitle, emessagebox, pszDetails);
////
////   pmessagebox->m_functionClose = [&idResult, &event](nano::user::interchange * pinterchange)
////   {
////
////      idResult = pinterchange->m_atomResult;
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
   
   //return atomResult;

}



CLASS_DECL_ACME ::payload message_box_synchronous(::particle * pparticle, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
{

   if (::is_null(pparticle))
   {

      auto psequencer = ::operating_system::message_box::create_sequencer(::platform::get()->system(),                                                        scopedstrMessage, scopedstrTitle,
                                                              emessagebox,
                                                              scopedstrDetails, picon);

      return psequencer->do_synchronously();

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

   auto pnode = pparticle->node();

   auto psequencer = pnode->create_message_box_sequencer(scopedstrMessage, scopedstrTitle, emessagebox, scopedstrDetails, picon);
   
   auto atomResult = psequencer->do_synchronously();
   
//   auto pmanualresetevent = ::place(new manual_reset_event());
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
////   auto pmessagebox = pparticle->__create_new < message_box >();
////
////   atom idResult;
////
////   manual_reset_event event;
////
////   pmessagebox->display(pszMessage, pszTitle, emessagebox, pszDetails);
////
////   pmessagebox->m_functionClose = [&idResult, &event](nano::user::interchange * pinterchange)
////   {
////
////      idResult = pinterchange->m_atomResult;
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



CLASS_DECL_ACME void message_box_asynchronous(::function < void(const ::payload & payload) > function, ::particle * pparticle, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
{

   auto pmessagebox = ::place(new ::nano::user::message_box_conversation_message());

   pmessagebox->m_pobject = pparticle;
   pmessagebox->initialize_conversation(scopedstrMessage,scopedstrTitle, emessagebox, scopedstrDetails, picon);

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

      auto pnanomessagebox = pparticle->__create_new < ::nano::user::message_box >();
   
      ::payload idResult;
   
      manual_reset_event event;

      pnanomessagebox->initialize_conversation(
         pmessagebox->m_strMessage,
         pmessagebox->m_strTitle,
         pmessagebox->m_emessagebox,
         pmessagebox->m_strDetails,
         pmessagebox->m_picon);
      
      auto pwindow = pnanomessagebox->nano_windowing_window();

      pwindow->m_functionClose = [ pmessagebox ](::nano::user::interaction * pinteraction)
      {
      
         auto result = pinteraction->m_payloadResult;
         
         if(pmessagebox->m_function)
         {
      
            pmessagebox->m_function(result);
            
         }
      
      };

      pnanomessagebox->do_asynchronously();

   //});

}

