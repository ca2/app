//
// Created by camilo on 31/01/2022 16:16 <3ThomasBorregaardSorensen!!
//
// renamed interchange from interchange by camilo on
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
// nano::user::window_base Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSorensen!!
// Merged into window_base on 2024-04-26 14:52
//
//
#include "framework.h"
#include "interchange.h"
#include "window_implementation.h"
#include "acme/nano/graphics/device.h"
#include "child.h"
#include "button.h"
#include "user.h"
#include "acme/nano/nano.h"
#include "acme/handler/topic.h"
#include "acme/nano/graphics/font.h"
#include "acme/constant/id.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/sequencer.h"
#include "acme/platform/system.h"
#include "acme/user/user/drag.h"
#include "acme/user/user/mouse.h"
#include "acme/user/user/tool.h"
#include "acme/windowing/window_base.h"


namespace nano
{


   namespace user
   {


      interchange::interchange()
      {

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


      interchange::~interchange()
      {


      }


      //::pointer < item_container > interchange::item_form()
      //{
      //
      //   return item_container(id_user_interface);
      //
      //}


      void interchange::on_initialize_particle()
      {

         ::object::on_initialize_particle();

         __construct(m_pwindowbase);

         m_pwindowbase->m_puserinteractionbase = this;

         system()->m_pnano->user()->m_interchangea.add(this);

      }


      void interchange::draw(::nano::graphics::device * pnanodevice)
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

      ::rectangle_i32 interchange::get_window_rectangle()
      {

         return m_rectangle;

      }


      void interchange::draw_children(::nano::graphics::device * pnanodevice)
      {

         for (auto & pchild : m_childa)
         {

            pchild->on_draw(pnanodevice);

         }

      }


      void interchange::create()
      {

         m_pwindowbase->create_window();

      }


      void interchange::on_create_window()
      {

         update_drawing_objects();

      }


      void interchange::destroy()
      {

         if (m_pwindowbase)
         {

            m_pwindowbase->destroy();

            m_pwindowbase.release();

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

         if (system()->m_pnano->m_puser)
         {

            system()->m_pnano->m_puser->m_interchangea.erase(this);

         }

         ::user::interaction_base::destroy();

      }


      void interchange::show_window()
      {

         m_pwindowbase->show_window();

      }


      void interchange::hide()
      {

         m_pwindowbase->hide();

      }


      void interchange::message_loop()
      {

         m_pwindowbase->message_loop();

      }



      void interchange::on_draw(::nano::graphics::device * pnanodevice)
      {

         //m_pwindowbase->draw(pnanodevice);

      }


      void interchange::on_char(int iChar)
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


      bool interchange::is_active()
      {

         return m_bNcActive;

      }


      void interchange::set_active()
      {

         m_pwindowbase->set_active_window();

      }


      void interchange::delete_drawing_objects()
      {

         m_pbrushWindow.release();

         m_ppenBorder.release();

         m_ppenBorder.release();

      }


      bool interchange::get_dark_mode()
      {

         return system()->dark_mode();


      }


      void interchange::create_drawing_objects()
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


      void interchange::update_drawing_objects()
      {

         delete_drawing_objects();

         nano()->graphics();

         create_drawing_objects();

      }


      bool interchange::defer_perform_entire_reposition_process(::user::mouse * pmouse)
      {

         if (m_pwindowbase)
         {

            if (m_pwindowbase->defer_perform_entire_reposition_process(pmouse))
            {

               return true;

            }

         }

         return false;

      }


      bool interchange::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse)
      {

         if (m_pwindowbase)
         {

            if (m_pwindowbase->defer_perform_entire_resizing_process(eframeSizing, pmouse))
            {

               return true;

            }

         }

         return false;

      }


      ::point_i32 interchange::try_absolute_mouse_position(const ::point_i32 & point)
      {

         return m_pwindowbase->try_absolute_mouse_position(point);

      }


      ::point_i32 interchange::origin()
      {

         return m_rectangle.origin();

      }


      ::nano::user::child * interchange::hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder)
      {

         auto point = pmouse->m_pointHost;

         host_to_client()(point);

         return on_hit_test(point, ezorder);

      }



      ::nano::user::child * interchange::on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
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


      void interchange::add_child(::nano::user::child * pchild)
      {

         pchild->m_pinterchange = this;

         m_childa.add(pchild);

      }


      void interchange::add_button(const ::scoped_string & scopedstrText, enum_dialog_result edialogresult, char chLetter)
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



      ::nano::user::child * interchange::get_child_by_id(const ::atom & atom)
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


      ::payload interchange::get_result()
      {

         return m_payloadResult;

      }


      void interchange::on_mouse_move(::user::mouse * pmouse)
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


      void interchange::on_left_button_down(::user::mouse * pmouse)
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


      void interchange::on_left_button_up(::user::mouse * pmouse)
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


      void interchange::on_right_button_down(::user::mouse * pmouse)
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


      void interchange::on_right_button_up(::user::mouse * pmouse)
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


      void interchange::on_click(const ::payload & payload, ::user::mouse * pmouse)
      {


      }


      void interchange::on_right_click(const ::payload & payload, ::user::mouse * pmouse)
      {


      }


      void interchange::set_position(const ::point_i32 & point)
      {

         m_pwindowbase->set_position(point);

      }


      void interchange::redraw()
      {

         m_pwindowbase->redraw();

      }


      void interchange::set_interaction_rectangle(const ::rectangle_i32 & rectangle)
      {

         m_rectangle = rectangle;

      }


      ::rectangle_i32 interchange::get_interaction_rectangle()
      {

         return m_rectangle;

      }


      void interchange::get_client_rectangle(::rectangle_i32 & rectangle)
      {

         rectangle.left() = 0;
         rectangle.top() = 0;
         rectangle.right() = m_rectangle.width();
         rectangle.bottom() = m_rectangle.height();

      }


      // ::rectangle_i32 interchange::get_window_rectangle()
      // {
      //
      //    return m_rectangle;
      //
      // }


      void interchange::set_capture()
      {

         if (m_bCapture)
         {

            return;

         }

         m_pwindowbase->set_capture();

         m_bCapture = true;

      }


      void interchange::set_cursor(enum_cursor ecursor)
      {

         m_pwindowbase->set_cursor(ecursor);

      }


      bool interchange::has_capture()
      {

         return m_pwindowbase->has_capture();

      }


      void interchange::release_capture()
      {

         m_pchildCapture = nullptr;

         if (!m_bCapture)
         {

            return;

         }

         m_bCapture = false;

         m_pwindowbase->release_capture();

      }


      ::pointer<::nano::graphics::device>interchange::create_device()
      {

         throw interface_only();

         return nullptr;

      }


      void interchange::display_temporary_file_with_text(const ::string & str)
      {

         string strAppId;

         strAppId = application()->m_strAppId;

         ::file::path pathFolder = acmedirectory()->home() / "application" / strAppId / "details";

         auto pathDetails = acmefile()->time_put_contents(pathFolder, "details", "txt", str);

         node()->shell_open(pathDetails, "");

      }



      void interchange::_run_modal_loop()
      {

         m_pwindowbase->_run_modal_loop();

      }


      ::payload interchange::do_synchronously(const class time & timeWait)
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

   // ::atom interchange::do_synchronously()
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
   //    nano::user::interchange::display();
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



   void interchange::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == id_set_application_dark_mode)
      {

         m_pwindowbase->handle(ptopic, pcontext);

      }

   }


   //::user::item & interchange::user_item(const ::item * pitem)
   //{
   //
   //   return m_useritemmap[pitem];
   //
   //}


   void interchange::do_asynchronously()
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
// nano::user::window_base Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSorensen!!
// Merged into window_base on 2024-04-26 14:52
//
#include "framework.h"
#include "window_base.h"
#include "platform/system.h"
#include "acme/nano/nano.h"
#include "acme/nano/graphics/device.h"
#include "acme/nano/user/display.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
#include "acme/user/user/interaction_base.h"
#include "acme/windowing/windowing_base.h"


   namespace windowing
   {


      window_base::window_base() :
         m_pointCursor2(I32_MINIMUM)
      {

         m_bRepositioningWindowFromCenter = false;
         m_bResizingWindowFromBottomRight = false;

      }


      window_base::~window_base()
      {

         output_debug_string("window_base::~window_base()");

      }



      ::user::interaction_base * window_base::user_interaction_base()
      {

         return m_puserinteractionbase;

      }


      ::windowing::window_base * window_base::windowing_window_base()
      {

         return this;

      }


      void window_base::on_initialize_particle()
      {

         ::user::element::on_initialize_particle();

         _synchronous_lock synchronouslock(system()->windowing_base()->synchronization());

         system()->windowing_base()->m_windowbasea.add(this);

      }


      void window_base::destroy()
      {

         ::user::element::destroy();

         _synchronous_lock synchronouslock(system()->windowing_base()->synchronization());

         system()->windowing_base()->m_windowbasea.erase(this);

      }


      bool window_base::is_windowing_popup()
      {

         return false;

      }


      ::point_i32 window_base::windowing_popup_origin()
      {

         return {};

      }


      ::size_i32 window_base::windowing_popup_size()
      {

         return {};

      }


      void window_base::_on_windowing_close_window()
      {


      }


      bool window_base::is_satellite_window()
      {

         return false;

      }


      window_base * window_base::owner_window()
      {

         return nullptr;

      }


      ::string window_base::get_window_text()
      {

         return {};

      }


      // ::pointer < ::operating_system::a_system_menu > window_base::create_system_menu(bool bContextual)
      // {
      //
      //    return ::nano::user::window_base::create_system_menu(bContextual);
      //
      // }


      bool window_base::defer_perform_entire_reposition_process(::user::mouse * pmouse)
      {

         return false;

      }


      bool window_base::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse)
      {

         return false;

      }



      // static thread_local ::pointer_array < window_base > t_nanowindowimplementationa;
      //
      //
      //
      // ::pointer_array < window_base > & window_base::nanowindowimplementationa()
      // {
      //
      //    return t_nanowindowimplementationa;
      //
      // }


      // window_base::window_base()
      // {
      //
      //
      // }
      //
      //
      // window_base::~window_base()
      // {
      //
      //    output_debug_string("window_base::~window_base()");
      //
      // }


      ::nano::user::display * window_base::get_display()
      {

         return nullptr;

      }


      // void window_base::draw(device * pnanodevice)
      // {
      //
      //    m_pinterface->draw(pnanodevice);
      //
      // }


      // bool window_base::get_dark_mode()
      // {
      //
      //    return m_pinterface->get_dark_mode();
      //
      // }


      bool window_base::is_active_window()
      {

         //return m_pinterface->is_active();

         return false;

      }


      // void window_base::nano_window_on_create()
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




      void window_base::nano_window_on_destroy()
      {


      }


      void window_base::create_window()
      {

      }


      void window_base::_create_window()
      {


      }


      void window_base::on_create_window()
      {

         m_puserinteractionbase->on_create_window();

      }




      void window_base::show_window()
      {

      }


      void window_base::hide_window()
      {


      }


      void window_base::message_loop()
      {


      }


      void window_base::set_active_window()
      {


      }



      ::point_i32 window_base::try_absolute_mouse_position(const ::point_i32 & point)
      {

         //return window_interface::try_absolute_mouse_position(point);

         return point;

      }


      void window_base::handle(::topic * ptopic, ::context * pcontext)
      {

         // if(ptopic->m_atom == id_operating_system_user_color_change)
         // {
         //
         //    update_drawing_objects();
         //
         //    redraw();
         //
         // }
         // else if(ptopic->m_atom == id_set_application_dark_mode)
         // {
         //
         //    update_drawing_objects();
         //
         //    redraw();
         //
         // }
         // else if(ptopic->m_atom == id_application_dark_mode_change)
         // {
         //
         //    update_drawing_objects();
         //
         //    redraw();
         //
         // }

      }


      ::size_i32 window_base::get_main_screen_size()
      {

         auto pdisplay = get_display();

         if (::is_null(pdisplay))
         {

            return { 800, 600 };

         }

         return pdisplay->get_main_screen_size();

      }


      // ::payload window_base::do_synchronously(const class time & timeWait)
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
      //    // //   pmessagebox->m_functionClose = [&idResult, &event](nano::user::interchange * pwindow)
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
      //   nano::user::interchange::display();
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


      void window_base::_on_window_simple_action(const char * pszActionName)
      {

         if (!m_puserinteractionbase)
         {

            throw ::exception(error_failed);

         }

         m_puserinteractionbase->_on_window_simple_action(pszActionName);

      }


      void window_base::defer_show_system_menu(::user::mouse * pmouse)
      {


      }

      void window_base::implementation_message_loop_step()
      {


      }


      void window_base::on_char(int iChar)
      {


      }

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
      //   nano::user::interchange::display();
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
      //   m_functionClose = [this](nano::user::interchange * pwindow)
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
      //         nano::user::interchange::display();
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


      void window_base::set_interface_client_size(const ::size_i32 & sizeWindow) // set_size
      {

         m_sizeWindow = sizeWindow;

      }


      void window_base::set_rectangle(const rectangle_i32 & rectangle)
      {

         auto r = rectangle;

         main_send([this, r]()
                   {

                         set_rectangle_unlocked(r);

                   });

      }


      void window_base::set_position(const point_i32 & point)
      {

         auto p = point;

         main_post([this, p]()
         {

               set_position_unlocked(p);

         });

      }


      void window_base::set_size(const size_i32 & size)
      {

         auto s = size;

         main_post([this, s]()
         {

               set_size_unlocked(s);

         });


      }


      void window_base::set_rectangle_unlocked(const rectangle_i32 & rectangle)
      {

         set_position_unlocked(rectangle.top_left());

         set_size_unlocked(rectangle.size());

      }


      void window_base::set_position_unlocked(const point_i32 & point)
      {


      }


      void window_base::set_size_unlocked(const size_i32 & size)
      {


      }


      ::rectangle_i32 window_base::get_window_rectangle()
      {

         ::rectangle_i32 rectangle;

         main_send([this, &rectangle]()
         {

               rectangle = get_window_rectangle_unlocked();

         });

         return rectangle;

      }


      ::rectangle_i32 window_base::get_window_rectangle_unlocked()
      {

         return {};

      }


      void window_base::on_a_system_menu_item(::operating_system::a_system_menu_item * psystemmenuitem)
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



