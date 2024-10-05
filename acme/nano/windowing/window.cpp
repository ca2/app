//
// Created by camilo on 31/01/2022 16:16 <3ThomasBorregaardSorensen!!
//
// renamed window from window by camilo on
//    2024-09-26 15:38 <3ThomasBorregaardSorensen!!
// // Merged from windowing_base to
//     windowing to nano_use by camilo on 2024-10-05 11:12 <3ThomasBorregaardSorensen!!
//                   //
// Created by camilo on 2024-05-26 21:50 <3ThomasBorregaardSorensen!!
// // Merged from windowing_base to
//     windowing by camilo on 2024-10-05 10:36 <3ThomasBorregaardSorensen!!
//

//

   //
// Created by camilo on 2023-10-06 <3ThomasBorregaardSorensen!!
//
// nano::user::window Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSorensen!!
// Merged into window on 2024-04-26 14:52
//
//
#include "framework.h"
#include "display.h"
#include "window.h"
//#include "window_implementation.h"
#include "acme/nano/graphics/device.h"
#include "interaction.h"
#include "button.h"
#include "user.h"
#include "acme/nano/nano.h"
#include "acme/handler/topic.h"
#include "acme/nano/graphics/font.h"
#include "acme/constant/id.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/sequencer.h"
#include "acme/platform/system.h"
#include "acme/user/user/drag.h"
#include "acme/user/user/mouse.h"
#include "acme/user/user/tool.h"
#include "acme/nano/user/user.h"


namespace nano
{


   namespace windowing
   {


      window::window() :
         m_pointCursor2(I32_MINIMUM)
      {

         m_bRepositioningWindowFromCenter = false;
         m_bResizingWindowFromBottomRight = false;

      //}
      //{

         m_bTopMost = false;

         m_iFontSize = 14;

         m_efont = e_font_sans;

         auto pitemClient = tool().defer_item(e_element_client);

         enable_drag(pitemClient, ::user::e_zorder_back);

         m_bNcActive = false;

         m_bStartCentered = false;

         m_bArbitraryPositioning = false;

         m_bCapture = false;

      }


      window::~window()
      {

         output_debug_string("window::~window()");

      }


      //::pointer < item_container > window::item_form()
      //{
      //
      //   return item_container(id_user_interface);
      //
      //}


      void window::on_initialize_particle()
      {

         ::object::on_initialize_particle();

         __construct(m_puserinterchange);

         m_puserinterchange->m_puserinteractionbase = this;

         nano()->user()->m_interchangea.add(this);

         //::user::element::on_initialize_particle();

         //_synchronous_lock synchronouslock(nano()->user()->synchronization());

         //nano()->user()->m_windowbasea.add(this);


      }


      void window::draw(::nano::graphics::device * pnanodevice)
      {

         ::pointer<::nano::graphics::pen>pnanopenBorder;

         if (is_active())
         {

            pnanopenBorder = m_ppenBorderFocus;

         }
         else
         {

            pnanopenBorder = m_ppenBorder;

         }

         ::rectangle_i32 rectangleX;

         get_client_rectangle(rectangleX);

         pnanodevice->rectangle(rectangleX, m_pbrushWindow, pnanopenBorder);

         on_draw(pnanodevice);

         draw_children(pnanodevice);

      }


      //::rectangle_i32 window::get_window_rectangle()
      //{

      //   return m_rectangle;

      //}


      void window::draw_children(::nano::graphics::device * pnanodevice)
      {

         for (auto & pchild : m_childa)
         {

            pchild->on_draw(pnanodevice);

         }

      }


      void window::create()
      {

         m_puserinterchange->create_window();

      }


      void window::on_create_window()
      {

         update_drawing_objects();

         m_puserinteractionbase->on_create_window();


      }


      void window::destroy()
      {

         if (m_puserinterchange)
         {

            m_puserinterchange->destroy();

            m_puserinterchange.release();

         }

         if (m_functionClose)
         {

            m_functionClose(this);

            m_functionClose.clear();

         }

         if (m_psequencer)
         {

            m_psequencer->on_sequence();

            m_psequencer.release();

         }

         if (nano()->user())
         {

            nano()->user()->m_interchangea.erase(this);

         }

         //_synchronous_lock synchronouslock(nano()->user()->synchronization());

         //nano()->user()->m_windowbasea.erase(this);




         ::user::interaction_base::destroy();

      }


      void window::show_window()
      {

         m_puserinterchange->show_window();

      }


      void window::hide()
      {

         m_puserinterchange->hide();

      }


      void window::message_loop()
      {

         m_puserinterchange->message_loop();

      }



      void window::on_draw(::nano::graphics::device * pnanodevice)
      {

         //m_puserinterchange->draw(pnanodevice);

      }


      void window::on_char(int iChar)
      {

         if (iChar == '\t' && m_childa.has_element())
         {

            auto iFind = m_childa.find_first(m_pchildFocus);

            iFind++;

            m_pchildFocus = m_childa % iFind;

            redraw();

         }
         else if (m_pchildFocus)
         {

            m_pchildFocus->on_char(iChar);

         }

      }


      bool window::is_active()
      {

         return m_bNcActive;

      }


      void window::set_active()
      {

         m_puserinterchange->set_active_window();

      }


      void window::delete_drawing_objects()
      {

         m_pbrushWindow.release();

         m_ppenBorder.release();

         m_ppenBorder.release();

      }


      bool window::get_dark_mode()
      {

         return system()->dark_mode();


      }


      void window::create_drawing_objects()
      {

         if (!m_pfont)
         {

#if REFERENCING_DEBUGGING

            ::allocator::add_referer({ this, __FUNCTION_FILE_LINE__ });

#endif

            __construct(m_pfont, nullptr);

            m_pfont->m_iFontSize = m_iFontSize;

            m_pfont->m_strFontName = node()->font_name(m_efont);

         }

         bool bDarkMode = get_dark_mode();

         if (bDarkMode)
         {

            m_colorWindow = argb(255, 0, 0, 0);
            m_colorText = argb(255, 255, 255, 255);
            m_colorHyperlink = argb(255, 40, 90, 245);
            m_colorHyperlinkHover = argb(255, 70, 180, 255);
            m_colorFocus = argb(255, 2, 128, 255);

         }
         else
         {

            m_colorWindow = argb(255, 255, 255, 255);
            m_colorText = argb(255, 0, 0, 0);
            m_colorHyperlink = argb(255, 50, 100, 185);
            m_colorHyperlinkHover = argb(255, 100, 180, 225);
            m_colorFocus = argb(255, 2, 58, 235);

         }

         m_pbrushWindow = ::nano::graphics::create_solid_brush(this, m_colorWindow);

         m_pbrushText = ::nano::graphics::create_solid_brush(this, m_colorText);

         m_pbrushHyperlink = ::nano::graphics::create_solid_brush(this, m_colorHyperlink);

         m_pbrushHyperlinkHover = ::nano::graphics::create_solid_brush(this, m_colorHyperlinkHover);

         m_ppenBorder = ::nano::graphics::create_pen(this, 1, m_colorText);

         m_ppenBorderFocus = ::nano::graphics::create_pen(this, 1, m_colorFocus);

      }


      void window::update_drawing_objects()
      {

         delete_drawing_objects();

         nano()->graphics();

         create_drawing_objects();

      }


      bool window::defer_perform_entire_reposition_process(::user::mouse * pmouse)
      {

         if (m_puserinterchange)
         {

            if (m_puserinterchange->defer_perform_entire_reposition_process(pmouse))
            {

               return true;

            }

         }

         return false;

      }


      bool window::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse)
      {

         if (m_puserinterchange)
         {

            if (m_puserinterchange->defer_perform_entire_resizing_process(eframeSizing, pmouse))
            {

               return true;

            }

         }

         return false;

      }


      ::point_i32 window::try_absolute_mouse_position(const ::point_i32 & point)
      {

         return m_puserinterchange->try_absolute_mouse_position(point);

      }


      ::point_i32 window::origin()
      {

         return m_rectangle.origin();

      }


      ::nano::user::child * window::hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder)
      {

         auto point = pmouse->m_pointHost;

         host_to_client()(point);

         return on_hit_test(point, ezorder);

      }



      ::nano::user::child * window::on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
      {

         for (auto & pchild : m_childa)
         {

            if (pchild->m_rectangle.contains(point))
            {

               return pchild;

            }

         }

         return nullptr;

      }


      void window::add_child(::nano::user::child * pchild)
      {

         pchild->m_pinterchange = this;

         m_childa.add(pchild);

      }


      void window::add_button(const ::scoped_string & scopedstrText, enum_dialog_result edialogresult, char chLetter)
      {

         auto pbutton = ::place(new ::nano::user::button());

         pbutton->m_strText = scopedstrText;
         pbutton->m_atom = edialogresult;
         pbutton->m_edialogresult1 = edialogresult;
         pbutton->m_chLetter = chLetter;
         //pbutton->m_bDefault = bDefault;

         m_nanobuttona.add(pbutton);

         add_child(pbutton);

      }



      ::nano::user::child * window::get_child_by_id(const ::atom & atom)
      {

         for (auto & pchild : m_childa)
         {

            if (pchild->m_atom == atom)
            {

               return pchild;

            }

         }

         return nullptr;

      }


      ::payload window::get_result()
      {

         return m_payloadResult;

      }


      void window::on_mouse_move(::user::mouse * pmouse)
      {

         if (m_pchildHover)
         {

            m_pchildHover->on_mouse_move(pmouse);

            return;

         }

         if (m_pchildCapture)
         {

            m_pchildCapture->on_mouse_move(pmouse);

            return;

         }

         if (drag_on_mouse_move(pmouse))
         {

            return;

         }

         auto pchild = hit_test(pmouse, ::user::e_zorder_any);

         if (pchild)
         {

            pchild->on_mouse_move(pmouse);

         }

      }


      void window::on_left_button_down(::user::mouse * pmouse)
      {

         auto pchild = hit_test(pmouse, ::user::e_zorder_any);

         if (pchild)
         {

            m_atomLeftButtonDown = pchild->m_atom;

         }
         else
         {

            m_atomLeftButtonDown = e_dialog_result_none;

         }

         auto pitemClient = tool().defer_item(e_element_client);

         auto pdragClient = drag(pitemClient);

         if (pdragClient && !pchild)
         {

            if (drag_on_button_down(pitemClient, pmouse))
            {

               return;

            }

         }

         if (::is_set(pchild) && pchild->is_focusable())
         {

            pchild->set_focus();

         }

      }


      void window::on_left_button_up(::user::mouse * pmouse)
      {

         release_capture();

         if (drag_on_button_up(pmouse))
         {

            return;

         }

         auto pchild = hit_test(pmouse, ::user::e_zorder_any);

         if (pchild)
         {

            m_atomLeftButtonUp = pchild->m_atom;

         }
         else
         {

            m_atomLeftButtonUp = e_dialog_result_none;

         }

         if (m_atomLeftButtonUp == m_atomLeftButtonDown && m_atomLeftButtonUp != e_dialog_result_none)
         {

            m_payloadResult = m_atomLeftButtonUp;

            on_click(m_payloadResult, pmouse);

         }

         if (drag_on_button_up(pmouse))
         {

            return;

         }

      }


      void window::on_right_button_down(::user::mouse * pmouse)
      {

         auto pchild = hit_test(pmouse, ::user::e_zorder_any);

         if (pchild)
         {

            m_atomRightButtonDown = pchild->m_atom;

         }
         else
         {

            m_atomRightButtonDown = e_dialog_result_none;

         }


         if (::is_set(pchild) && pchild->is_focusable())
         {

            pchild->set_focus();

         }

      }


      void window::on_right_button_up(::user::mouse * pmouse)
      {

         release_capture();

         auto pchild = hit_test(pmouse, ::user::e_zorder_any);

         if (pchild)
         {

            m_atomRightButtonUp = pchild->m_atom;

         }
         else
         {

            m_atomRightButtonUp = e_dialog_result_none;

         }

         if (m_atomRightButtonUp == m_atomRightButtonDown)
         {

            on_right_click(m_atomLeftButtonUp, pmouse);

         }

      }


      void window::on_click(const ::payload & payload, ::user::mouse * pmouse)
      {


      }


      void window::on_right_click(const ::payload & payload, ::user::mouse * pmouse)
      {


      }


      //void window::set_position(const ::point_i32 & point)
      //{

      //   m_puserinterchange->set_position(point);

      //}


      void window::redraw()
      {

         m_puserinterchange->redraw();

      }


      void window::set_interaction_rectangle(const ::rectangle_i32 & rectangle)
      {

         m_rectangle = rectangle;

      }


      ::rectangle_i32 window::get_interaction_rectangle()
      {

         return m_rectangle;

      }


      void window::get_client_rectangle(::rectangle_i32 & rectangle)
      {

         rectangle.left() = 0;
         rectangle.top() = 0;
         rectangle.right() = m_rectangle.width();
         rectangle.bottom() = m_rectangle.height();

      }


      // ::rectangle_i32 window::get_window_rectangle()
      // {
      //
      //    return m_rectangle;
      //
      // }


      void window::set_capture()
      {

         if (m_bCapture)
         {

            return;

         }

         m_puserinterchange->set_capture();

         m_bCapture = true;

      }


      void window::set_cursor(enum_cursor ecursor)
      {

         m_puserinterchange->set_cursor(ecursor);

      }


      bool window::has_capture()
      {

         return m_puserinterchange->has_capture();

      }


      void window::release_capture()
      {

         m_pchildCapture = nullptr;

         if (!m_bCapture)
         {

            return;

         }

         m_bCapture = false;

         m_puserinterchange->release_capture();

      }


      ::pointer<::nano::graphics::device>window::create_device()
      {

         throw interface_only();

         return nullptr;

      }


      void window::display_temporary_file_with_text(const ::string & str)
      {

         string strAppId;

         strAppId = application()->m_strAppId;

         ::file::path pathFolder = acmedirectory()->home() / "application" / strAppId / "details";

         auto pathDetails = acmefile()->time_put_contents(pathFolder, "details", "txt", str);

         node()->shell_open(pathDetails, "");

      }



      void window::_run_modal_loop()
      {

         m_puserinterchange->_run_modal_loop();

      }


      ::payload window::do_synchronously(const class time & timeWait)
      {

         do_asynchronously();

         auto pmanualresetevent = ::place(new manual_reset_event());

         if (m_psequencer)
         {

            m_psequencer->then([pmanualresetevent](auto psequencer)
            {

               pmanualresetevent->SetEvent();

            });

         }
         else
         {

            auto functionCloseExisting = m_functionClose;

            m_functionClose = [pmanualresetevent, functionCloseExisting](auto pinterchange)
            {

               if (functionCloseExisting)
               {

                  functionCloseExisting(pinterchange);

               }

               pmanualresetevent->SetEvent();

            };

         }

         if (m_payloadResult.is_new())
         {

            pmanualresetevent->wait();

         }

         return m_payloadResult;

      }

   // ::atom window::do_synchronously()
   // {
   //
   //    //main_synchronous(1_min, [this]()
   //    //{
   //
   //
   //    //main_asynchronous([this]()
   //       //{
   //
   //    create();
   //
   //    nano::user::window::display();
   //
   //   aaa_message_loop();
   //
   //    //});
   //
   //    //display(m_strMessage, m_strTitle, m_emessagebox, m_strDetails);
   //
   // //});
   //
   //    return m_atomResult;
   //
   // }



   void window::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == id_set_application_dark_mode)
      {

         m_puserinterchange->handle(ptopic, pcontext);

      }

   }


   //::user::item & window::user_item(const ::item * pitem)
   //{
   //
   //   return m_useritemmap[pitem];
   //
   //}


   void window::do_asynchronously()
   {

      create();

      show_window();

   }

   // // Merged from windowing_base to
//     windowing to nano_use by camilo on 2024-10-05 11:12 <3ThomasBorregaardSorensen!!
//                   //
// Created by camilo on 2024-05-26 21:50 <3ThomasBorregaardSorensen!!
// // Merged from windowing_base to
//     windowing by camilo on 2024-10-05 10:36 <3ThomasBorregaardSorensen!!
//

//

   //
// Created by camilo on 2023-10-06 <3ThomasBorregaardSorensen!!
//
// nano::user::window Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSorensen!!
// Merged into window on 2024-04-26 14:52
//
//#include "framework.h"
//#include "window.h"
//#include "platform/system.h"
//#include "acme/nano/nano.h"
//#include "acme/nano/graphics/device.h"
//#include "acme/nano/user/display.h"
//#include "acme/operating_system/a_system_menu.h"
//#include "acme/parallelization/synchronous_lock.h"
//#include "acme/platform/application.h"
//#include "acme/user/user/interaction_base.h"
//#include "acme/windowing/windowing_base.h"
//
//
//   namespace windowing
//   {
//

      //window::window() :
      //   m_pointCursor2(I32_MINIMUM)
      //{

      //   m_bRepositioningWindowFromCenter = false;
      //   m_bResizingWindowFromBottomRight = false;

      //}


      //window::~window()
      //{

      //   output_debug_string("window::~window()");

      //}



      ::user::interaction_base * window::user_interaction_base()
      {

         return m_puserinteractionbase;

      }


      ::nano::user::window * window::user_interchange()
      {

         return this;

      }


      //void window::on_initialize_particle()
      //{

      //   ::user::element::on_initialize_particle();

      //   _synchronous_lock synchronouslock(nano()->user()->synchronization());

      //   nano()->user()->m_windowbasea.add(this);

      //}


      //void window::destroy()
      //{

      //   ::user::element::destroy();

      //   _synchronous_lock synchronouslock(nano()->user()->synchronization());

      //   nano()->user()->m_windowbasea.erase(this);

      //}


      bool window::is_windowing_popup()
      {

         return false;

      }


      ::point_i32 window::windowing_popup_origin()
      {

         return {};

      }


      ::size_i32 window::windowing_popup_size()
      {

         return {};

      }


      void window::_on_windowing_close_window()
      {


      }


      bool window::is_satellite_window()
      {

         return false;

      }


      //window * window::user_interchange()
      //{

      //   return this;

      //}


      ::string window::get_window_text()
      {

         return {};

      }


      // ::pointer < ::operating_system::a_system_menu > window::create_system_menu(bool bContextual)
      // {
      //
      //    return ::nano::user::window::create_system_menu(bContextual);
      //
      // }


      //bool window::defer_perform_entire_reposition_process(::user::mouse * pmouse)
      //{

      //   return false;

      //}


      //bool window::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse)
      //{

      //   return false;

      //}



      // static thread_local ::pointer_array < window > t_nanowindowimplementationa;
      //
      //
      //
      // ::pointer_array < window > & window::nanowindowimplementationa()
      // {
      //
      //    return t_nanowindowimplementationa;
      //
      // }


      // window::window()
      // {
      //
      //
      // }
      //
      //
      // window::~window()
      // {
      //
      //    output_debug_string("window::~window()");
      //
      // }


      ::nano::user::display * window::get_display()
      {

         return nullptr;

      }


      // void window::draw(device * pnanodevice)
      // {
      //
      //    m_pinterface->draw(pnanodevice);
      //
      // }


      // bool window::get_dark_mode()
      // {
      //
      //    return m_pinterface->get_dark_mode();
      //
      // }


      bool window::is_active_window()
      {

         //return m_pinterface->is_active();

         return false;

      }


      // void window::nano_window_on_create()
      // {
      //
      //    //node()->fetch_user_color();
      //
      //    //system()->add_signal_handler({ use_t{}, this }, id_operating_system_user_color_change);
      //
      //    create_drawing_objects();
      //
      //    on_create();
      //
      // }




      void window::nano_window_on_destroy()
      {


      }


      void window::create_window()
      {

      }


      void window::_create_window()
      {


      }


      //void window::on_create_window()
      //{

      //   m_puserinteractionbase->on_create_window();

      //}




      //void window::show_window()
      //{

      //}


      void window::hide_window()
      {


      }


      //void window::message_loop()
      //{


      //}


      void window::set_active_window()
      {


      }



      //::point_i32 window::try_absolute_mouse_position(const ::point_i32 & point)
      //{

      //   //return window_interface::try_absolute_mouse_position(point);

      //   return point;

      //}


      //void window::handle(::topic * ptopic, ::context * pcontext)
      //{

      //   // if(ptopic->m_atom == id_operating_system_user_color_change)
      //   // {
      //   //
      //   //    update_drawing_objects();
      //   //
      //   //    redraw();
      //   //
      //   // }
      //   // else if(ptopic->m_atom == id_set_application_dark_mode)
      //   // {
      //   //
      //   //    update_drawing_objects();
      //   //
      //   //    redraw();
      //   //
      //   // }
      //   // else if(ptopic->m_atom == id_application_dark_mode_change)
      //   // {
      //   //
      //   //    update_drawing_objects();
      //   //
      //   //    redraw();
      //   //
      //   // }

      //}


      ::size_i32 window::get_main_screen_size()
      {

         auto pdisplay = get_display();

         if (::is_null(pdisplay))
         {

            return { 800, 600 };
         }

         return pdisplay->get_main_screen_size();

      }


      // ::payload window::do_synchronously(const class time & timeWait)
      // {
      //
      //    create();
      //
      //    m_pinterface->show_window();
      //
      //    message_loop();
      //
      //    // auto pmanualresetevent = ::place(new manual_reset_event());
      //    //
      //    // m_pinterface->m_psequencer->then([ pmanualresetevent](auto psequencer)
      //    // {
      //    //
      //    //    pmanualresetevent->SetEvent();
      //    //
      //    // });
      //    //
      //    // auto pinterface = m_pinterface;
      //    //
      //    // if(pinterface->m_payloadResult.is_new())
      //    // {
      //    //
      //    //    pmanualresetevent->wait();
      //    //
      //    // }
      //    //
      //    // //   auto pmessagebox = pparticle->__create_new < message_box >();
      //    // //
      //    // //   atom idResult;
      //    // //
      //    // //   manual_reset_event event;
      //    // //
      //    // //   pmessagebox->display(pszMessage, pszTitle, emessagebox, pszDetails);
      //    // //
      //    // //   pmessagebox->m_functionClose = [&idResult, &event](nano::user::window * pwindow)
      //    // //   {
      //    // //
      //    // //      idResult = pwindow->m_atomResult;
      //    // //
      //    // //      event.SetEvent();
      //    // //
      //    // //   };
      //    // //
      //    // //   if(is_single_main_user_thread() && is_main_thread())
      //    // //   {
      //    // //
      //    // //      pmessagebox->_run_modal_loop();
      //    // //
      //    // //   }
      //    // //   else
      //    // //   {
      //    // //      event.wait();
      //    // //
      //    // //   }
      //    // //
      //    // //   //auto idResult = pmessagebox->get_result();
      //    // //
      //    // //   return idResult;
      //
      //    return pinterface->m_payloadResult;
      //
      // }

      //::atom message_box::do_synchronously()
      //{
      //
      //   //main_synchronous(1_min, [this]()
      //   //{
      //
      //
      //   //main_asynchronous([this]()
      //      //{
      //
      //   create();
      //
      //   nano::user::window::display();
      //
      //  aaa_message_loop();
      //
      //   //});
      //
      //   //display(m_strMessage, m_strTitle, m_emessagebox, m_strDetails);
      //
      ////});
      //
      //   return m_atomResult;
      //
      //}


      void window::_on_window_simple_action(const char * pszActionName)
      {

         if (!m_puserinteractionbase)
         {

            throw ::exception(error_failed);

         }

         m_puserinteractionbase->_on_window_simple_action(pszActionName);

      }


      void window::defer_show_system_menu(::user::mouse * pmouse)
      {


      }

      void window::interchange_message_loop_step()
      {


      }


      //void window::on_char(int iChar)
      //{


      //}

      //::atom message_box::do_synchronously()
      //{
      //
      //   //main_synchronous(1_min, [this]()
      //   //{
      //
      //
      //   //main_asynchronous([this]()
      //      //{
      //
      //   create();
      //
      //   nano::user::window::display();
      //
      //   aaa_message_loop();
      //
      //   //});
      //
      //   //display(m_strMessage, m_strTitle, m_emessagebox, m_strDetails);
      //
      ////});
      //
      //   return m_atomResult;
      //
      //}


      //void message_box::do_asynchronously()
      //{
      //
      //   m_functionClose = [this](nano::user::window * pwindow)
      //   {
      //
      //      m_psequence->on_sequence();
      //
      //   };
      //
      //   main_asynchronous([this]()
      //      {
      //
      //         create();
      //
      //         nano::user::window::display();
      //
      //         aaa_message_loop();
      //
      //      });
      //
      //   //display(m_strMessage, m_strTitle, m_emessagebox, m_strDetails);
      //
      ////});
      //
      //   //return m_atomResult;
      //
      //}
      //
      //


      void window::set_interface_client_size(const ::size_i32 & sizeWindow) // set_size
      {

         m_sizeWindow = sizeWindow;

      }


      void window::set_rectangle(const rectangle_i32 & rectangle)
      {

         auto r = rectangle;

         main_send([this, r]()
                   {

                         set_rectangle_unlocked(r);

                   });

      }


      void window::set_position(const point_i32 & point)
      {

         auto p = point;

         main_post([this, p]()
         {

               set_position_unlocked(p);

         });

      }


      void window::set_size(const size_i32 & size)
      {

         auto s = size;

         main_post([this, s]()
         {

               set_size_unlocked(s);

         });


      }


      void window::set_rectangle_unlocked(const rectangle_i32 & rectangle)
      {

         set_position_unlocked(rectangle.top_left());

         set_size_unlocked(rectangle.size());

      }


      void window::set_position_unlocked(const point_i32 & point)
      {


      }


      void window::set_size_unlocked(const size_i32 & size)
      {


      }


      ::rectangle_i32 window::get_window_rectangle()
      {

         ::rectangle_i32 rectangle;

         main_send([this, &rectangle]()
         {

               rectangle = get_window_rectangle_unlocked();

         });

         return rectangle;

      }


      ::rectangle_i32 window::get_window_rectangle_unlocked()
      {

         return {};

      }


      void window::on_a_system_menu_item(::operating_system::a_system_menu_item * psystemmenuitem)
      {

         ::string strActionName(psystemmenuitem->m_strAtom);

         if (strActionName == "minimize")
         {

            window_minimize();

         }
         else if (strActionName == "maximize")
         {

            window_maximize();

         }
         else if (strActionName == "maximize")
         {

            window_maximize();

         }
         else if (strActionName == "about_box")
         {

            application()->show_about_box();

         }
         else if (strActionName == "close")
         {

            window_close();

         }
         else if (strActionName == "")
         {

            print_line("reaching here?!");
            //defer_perform_entire_reposition_process(nullptr);

         }
         else if (strActionName == "")
         {

            print_line("also here");

            //defer_perform_entire_resizing_process(::experience::e_frame_sizing_top_left, nullptr);

         }


      }


   //} // namespace windowing






} // namespace user


} //  namespace nano



