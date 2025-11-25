//
// // Created from micro::interchange by
// // camilo on 2024-10-05 16:52 <3ThomasBorregaardSorensen!!
// Created by camilo on 31/01/2022 14:32 <3ThomasBorregaardSorensen!!
// renamed interchange from interchange by camilo on
//    2024-09-26 15:37 <3ThomasBorregaardSorensen!!
// 
// // // Merged from (acme)windowing and (acme)windowing_system by
// //   camilo on 2024-10-05 11:07 <3ThomasBorregaardSorensen!!
// //   (acme)windowing_system::windowing_system
// //       ---->windowing::windowing_base
// // //       ---->micro::user
// //   (acme)windowing::window_base
// //       ---->micro::interchange
//
// //// Child merged into main_window on 2024-10-05 05:17 <3ThomasBorregaardSorensen!!
// Created by camilo on 2022-01-21 05:10 PM <3ThomasBorregaardSorensen
//
// // merged from micro::main_window by camilo on 
// 2024-10-05 17:59 Odense Time <3ThomasBorregaardSorensen!!
// Created by camilo on 2024-09-26 22:59 Odense Time <3ThomasBorregaardSorensen!!
//
// micro::main_window Created by camilo on 31/01/2022 22:42 <3ThomasBorregaardSorensen!!
// From micro::main_window merged at ::user::main_window by
//    camilo on 2024-0926 15:04 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "button.h"
#include "main_window.h"
#include "user.h"
#include "acme/constant/id.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/handler/topic.h"
#include "acme/nano/graphics/device.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/theme.h"
#include "acme/windowing/window.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
//#include "acme/handler/sequence.h"
#include "acme/platform/system.h"
#include "acme/user/user/drag.h"
#include "acme/user/user/mouse.h"
#include "acme/user/user/tool.h"
#include "acme/windowing/window.h"
#include "acme/windowing/windowing.h"


namespace micro
{


   main_window::main_window()
   {

      m_efont = e_font_sans;

      auto pitemClient = stock_item(e_element_client);

      enable_drag(pitemClient, ::user::e_zorder_back);

   }


   main_window::~main_window()
   {


   }


   void main_window::create_window()
   {

      ::micro::elemental::create_window();


   }


   ::shift_int main_window::client_to_host()
   {

      if (system()->acme_windowing()->get_application_host_window())
      {

         return ::micro::elemental::client_to_host();

      }
      else
      {

         return {};

      }

   }


   void main_window::on_before_create_window(acme::windowing::window * pacmewindowingwindow)
   {

      ::micro::elemental::on_before_create_window(pacmewindowingwindow);

      m_bMinimizeBox = true;
      m_bMaximizeBox = true;
      m_bResizeable = true;
      m_bTopMost = false;
      m_bStartCentered = false;
      m_bArbitraryPositioning = false;

      pacmewindowingwindow->m_pacmeuserinteraction = this;

   }


   /*     ::micro::theme * main_window::micro_theme()
        {

           return system()->acme_windowing()->micro_theme();

        }*/


        /* enum_font main_window::micro_font()
         {

            if (m_efont != e_font_none)
            {

               return m_efont;

            }

            return micro_theme()->m_efont;

         }*/

         ///child


         //void main_window::set_keyboard_focus()
         //{

         //   acme_windowing_window()->m_pmicrouserinteractionFocus = this;

         //   acme_windowing_window()->redraw();

         //}


         //bool main_window::is_keyboard_focusable()
         //{

         //   return false;

         //}


         //void main_window::set_mouse_capture()
         //{

         //   acme_windowing_window()->m_pmicrouserinteractionCapture = this;

         //   acme_windowing_window()->set_mouse_capture();

         //}


         //bool main_window::has_mouse_capture()
         //{

         //   if (!acme_windowing_window()->has_mouse_capture())
         //   {

         //      return false;

         //   }

         //   return acme_windowing_window()->m_pmicrouserinteractionCapture == this;

         //}


         //void main_window::release_mouse_capture()
         //{

         //   if (acme_windowing_window()->m_pmicrouserinteractionCapture == this)
         //   {

         //      acme_windowing_window()->m_pmicrouserinteractionCapture.release();

         //      acme_windowing_window()->release_mouse_capture();

         //   }

         //}


         //void main_window::draw(::nano::graphics::device * pmicrodevice)
         //{

         //   ::pointer<::nano::graphics::pen>pmicropenBorder;

         //   if (acme_windowing_window()->is_active_window())
         //   {

         //      pmicropenBorder = micro_theme()->m_ppenBorderFocus;

         //   }
         //   else
         //   {

         //      pmicropenBorder = micro_theme()->m_ppenBorder;

         //   }

         //   ::int_rectangle rectangleX;

         //   rectangleX = get_client_rectangle();

         //   pmicrodevice->rectangle(rectangleX, micro_theme()->m_pbrushWindow, pmicropenBorder);

         //   on_draw(pmicrodevice);

         //   draw_children(pmicrodevice);

         //}


         //void main_window::draw_children(::nano::graphics::device * pmicrodevice)
         //{

         //   for (auto & pchild : m_microuserelementalaChildren)
         //   {

         //      pchild->on_draw(pmicrodevice);

         //   }

         //}


   ::micro::main_window * main_window::micro_main_window()
   {

      return this;

   }


   //void main_window::resize_to_fit()
   //{

   //   auto pdevice = øcreate < ::nano::graphics::device >();

   //   auto size = pdevice->get_text_extents(m_strText, micro_theme()->m_pfont);

   //   m_rectangle.right = m_rectangle.left + size.cx();

   //   m_rectangle.bottom = m_rectangle.top + size.cy();

   //}

   ////      //
   ////// Created by camilo on 2024-09-26 18:52 Odense Time <3ThomasBorregaardSorensen!!
   //////
   ////// micro::main_window Created by camilo on 31/01/2022 22:42 <3ThomasBorregaardSorensen!!
   ////// From micro::main_window merged at ::user::main_window by
   //////    camilo on 2024-0926 15:04 <3ThomasBorregaardSorensen!!
   //////
   ////#include "framework.h"
   ////#include "drag.h"
   ////#include "main_window.h"
   ////#include "acme/constant/id.h"
   ////#include "acme/handler/topic.h"
   ////#include "acme/operating_system/a_system_menu.h"
   ////#include "acme/platform/application.h"
   ////#include "acme/platform/system.h"
   ////#include "acme/windowing/window_base.h"
   ////#include "platform/node.h"
   ////
   ////
   ////      namespace user
   ////      {


   //         //main_window::main_window()
   //         //{

   //         //   m_bMinimizeBox = true;
   //         //   m_bMaximizeBox = true;
   //         //   m_bResizeable = true;
   //         //   m_bTopMost = false;
   //         //   m_bStartCentered = false;
   //         //   m_bArbitraryPositioning = false;

   //         //}


   //   /*      main_window::~main_window()
   //         {


   //         }*/


   //         /*bool main_window::is_window_zoomed()
   //         {

   //            if (!m_pacmewindowingwindow)
   //            {

   //               return false;

   //            }

   //            bool bIsWindowZoomed = m_pacmewindowingwindow->is_window_zoomed();

   //            if (!bIsWindowZoomed)
   //            {

   //               return false;

   //            }

   //            return true;

   //         }*/


   //         //void main_window::window_minimize()
   //         //{

   //         //   if (!m_pacmewindowingwindow)
   //         //   {

   //         //      throw ::exception(error_wrong_state);

   //         //   }

   //         //   m_pacmewindowingwindow->window_minimize();

   //         //}


   //         //void main_window::window_maximize()
   //         //{

   //         //   if (!m_pacmewindowingwindow)
   //         //   {

   //         //      throw ::exception(error_wrong_state);

   //         //   }

   //         //   m_pacmewindowingwindow->window_maximize();

   //         //}


   //         //void main_window::window_full_screen()
   //         //{

   //         //   if (!m_pacmewindowingwindow)
   //         //   {

   //         //      throw ::exception(error_wrong_state);

   //         //   }

   //         //   m_pacmewindowingwindow->window_full_screen();

   //         //}


   //         //void main_window::window_restore()
   //         //{

   //         //   if (!m_pacmewindowingwindow)
   //         //   {

   //         //      throw ::exception(error_wrong_state);

   //         //   }

   //         //   m_pacmewindowingwindow->window_restore();

   //         //}


   //         //void main_window::window_close()
   //         //{

   //         //   if (!m_pacmewindowingwindow)
   //         //   {

   //         //      throw ::exception(error_wrong_state);

   //         //   }

   //         //   m_pacmewindowingwindow->window_close();

   //         //}


   //void main_window::_on_window_simple_action(const_char_pointer pszActionName)
   //{

   //   ::string strActionName(scopedstrActionName);

   //   if (strActionName == "minimize")
   //   {

   //      display(e_display_iconic);

   //   }
   //   else if (strActionName == "maximize")
   //   {

   //      display(e_display_zoomed);

   //   }
   //   else if (strActionName == "restore")
   //   {

   //      display(e_display_normal);

   //   }
   //   else if (strActionName == "about_box")
   //   {

   //      application()->show_about_box();

   //   }
   //   else if (strActionName == "close")
   //   {

   //      window_close();

   //   }
   //   else if (strActionName == "***move")
   //   {

   //      print_line("reaching here?!");
   //      //defer_perform_entire_reposition_process(nullptr);

   //      m_pacmewindowingwindow->set_mouse_capture();
   //      m_pacmewindowingwindow->m_bRepositioningWindowFromCenter = true;

   //   }
   //   else if (strActionName == "***size")
   //   {

   //      print_line("also here");

   //      m_pacmewindowingwindow->set_mouse_capture();
   //      m_pacmewindowingwindow->m_bResizingWindowFromBottomRight = true;

   //      //defer_perform_entire_resizing_process(::experience::e_frame_sizing_top_left, nullptr);

   //   }

   //}


   //::pointer<::operating_system::a_system_menu> main_window::create_system_menu(bool bContextual)
   //{

   //   auto psystemmenu = øallocate ::operating_system::a_system_menu();

   //   if (m_bMinimizeBox)
   //   {

   //      psystemmenu->add_item("Minimize", "minimize");

   //   }

   //   if (!bContextual || is_window_zoomed())
   //   {

   //      psystemmenu->add_item("Restore", "restore");

   //   }

   //   if (m_bMaximizeBox)
   //   {

   //      if (!bContextual || !is_window_zoomed())
   //      {

   //         psystemmenu->add_item("Maximize", "maximize");

   //      }

   //   }

   //   if (::windowing::get_etoolkit() == ::windowing::e_toolkit_gtk4 ||
   //      ::windowing::get_etoolkit() == ::windowing::e_toolkit_gtk3)
   //   {
   //      psystemmenu->add_item("Drag to Move", "***move");
   //   }
   //   else
   //   {
   //      psystemmenu->add_item("Move", "***move");

   //   }

   //   if (m_bResizeable)
   //   {

   //      if (::windowing::get_etoolkit() == ::windowing::e_toolkit_gtk4 ||
   //         ::windowing::get_etoolkit() == ::windowing::e_toolkit_gtk3)
   //      {
   //         psystemmenu->add_item("Drag to Size", "***size");
   //      }
   //      else
   //      {
   //         psystemmenu->add_item("Size", "***size");

   //      }

   //   }

   //   psystemmenu->add_separator();

   //   psystemmenu->add_item("About...", "about_box");

   //   psystemmenu->add_separator();

   //   psystemmenu->add_item("Close", "close");

   //   return psystemmenu;

   //}


   //void main_window::set_mouse_capture()
   //{

   //   if (!m_pacmewindowingwindow)
   //   {

   //      throw ::exception(error_wrong_state);

   //   }

   //   m_pacmewindowingwindow->set_mouse_capture();

   //}


   //bool main_window::is_mouse_captured()
   //{

   //   if (!m_pacmewindowingwindow)
   //   {

   //      throw ::exception(error_wrong_state);

   //   }

   //   return m_pacmewindowingwindow->is_mouse_captured();

   //}


   //bool main_window::has_mouse_capture()
   //{

   //   if (!m_pacmewindowingwindow)
   //   {

   //      throw ::exception(error_wrong_state);

   //   }

   //   return m_pacmewindowingwindow->has_mouse_capture();

   //}


   //void main_window::release_mouse_capture()
   //{

   //   if (!m_pacmewindowingwindow)
   //   {

   //      throw ::exception(error_wrong_state);

   //   }

   //   m_pacmewindowingwindow->release_mouse_capture();

   //}


   void main_window::on_initialize_particle()
   {


   }


   //void main_window::create_window()
   //{

   //   auto pwindow = acme_windowing_window();

   //   pwindow->create_window();

   //}


   void main_window::show()
   {

      if (!m_pacmeuserinteractionParent)
      {

         acme_windowing_window()->show_window();

      }

   }


   void main_window::hide()
   {

      if (!m_pacmeuserinteractionParent)
      {

         acme_windowing_window()->hide_window();

      }

   }


   //void main_window::create()
   //{


   //}


   //void main_window::show_window()
   //{


   //}


   /*      void main_window::hide_window()
         {


         }*/


         //void main_window::message_loop()
         //{


         //}


   void main_window::implementation_message_loop_step()
   {


   }


   //void main_window::run()
   //{

   //   //do_modal();

   //   //auto pmanualresethappening = øallocate manual_reset_happening();

   //   //if (m_psequencer)
   //   //{

   //   //   m_psequencer->then([pmanualresethappening](auto psequencer)
   //   //   {

   //   //   pmanualresethappening->set_happening();

   //   //   });

   //   //}
   //   //else
   //   //{

   //   //   auto pwindow = acme_windowing_window();

   //   //   auto functionCloseExisting = pwindow->m_functionClose;

   //   //   pwindow->m_functionClose = [pmanualresethappening, functionCloseExisting](auto pinterchange)
   //   //      {

   //   //         if (functionCloseExisting)
   //   //         {

   //   //            functionCloseExisting(pinterchange);

   //   //         }

   //   //         pmanualresethappening->set_happening();

   //   //      };

   //   //}

   //   //if (m_payloadResult.is_new())
   //   //{

   //   //   pmanualresethappening->wait();

   //   //}

   //   //return m_payloadResult;

   //}


   //void main_window::complete_aggregation(::sequence * psequence)
   //{

   //   psequence->aggregate_payload(m_pay)

   //}

   //void main_window::draw(::nano::graphics::device * pmicrodevice)
   //{


   //}


   //void main_window::on_draw(::nano::graphics::device * pmicrodevice)
   //{


   //}


   //void main_window::on_char(int iChar)
   //{

   //   if (iChar == '\t' && m_microuserelementalaChildren.has_element())
   //   {

   //      auto iFind = m_microuserelementalaChildren.find_first(acme_windowing_window()->m_pmicrouserinteractionFocus);

   //      iFind++;

   //      acme_windowing_window()->m_pmicrouserinteractionFocus = m_microuserelementalaChildren % iFind;

   //      redraw();

   //   }
   //   else if (acme_windowing_window()->m_pmicrouserinteractionFocus)
   //   {

   //      acme_windowing_window()->m_pmicrouserinteractionFocus->on_char(iChar);

   //   }

   //}


   //::micro::main_window * main_window::hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder)
   //{

   //   auto point = pmouse->m_pointHost;

   //   host_to_client()(point);

   //   return on_hit_test(point, ezorder);

   //}


   //::micro::main_window * main_window::on_hit_test(const ::int_point & point, ::user::e_zorder ezorder)
   //{

   //   for (auto & pchild : m_microuserinteractionaChildren)
   //   {

   //      if (pchild->m_rectangle.contains(point))
   //      {

   //         return pchild;

   //      }

   //   }

   //   return nullptr;

   //}


   //void main_window::add_child(::micro::main_window * pinteractionChild)
   //{

   //   pinteractionChild->m_pmicrouserinteractionParent = this;

   //   m_microuserinteractionaChildren.add(pinteractionChild);

   //}


   //void main_window::add_button(const ::scoped_string & scopedstrText, enum_dialog_result edialogresult, char chLetter)
   //{

   //   auto pbutton = øallocate ::micro::button();

   //   pbutton->m_strText = scopedstrText;
   //   pbutton->id() = edialogresult;
   //   pbutton->m_edialogresult1 = edialogresult;
   //   pbutton->m_chLetter = chLetter;
   //   //pbutton->m_bDefault = bDefault;

   //   m_microuserinteractionaChildren.add(pbutton);

   //   add_child(pbutton);

   //}


   //::micro::main_window * main_window::get_child_by_id(const ::atom & atom)
   //{

   //   for (auto & pchild : m_microuserinteractionaChildren)
   //   {

   //      if (pchild->id() == atom)
   //      {

   //         return pchild;

   //      }

   //   }

   //   return nullptr;

   //}


   //::payload main_window::get_result()
   //{

   //   return m_payloadResult;

   //}


   ::string main_window::get_title()
   {

      return payload("main_window.title").as_string();

   }


   //void main_window::on_mouse_move(::user::mouse * pmouse)
   //{

   //   if (acme_windowing_window()->m_pmicrouserinteractionHover)
   //   {

   //      acme_windowing_window()->m_pmicrouserinteractionHover->on_mouse_move(pmouse);

   //      return;

   //   }

   //   if (acme_windowing_window()->m_pmicrouserinteractionCapture)
   //   {

   //      acme_windowing_window()->m_pmicrouserinteractionCapture->on_mouse_move(pmouse);

   //      return;

   //   }

   //   if (drag_on_mouse_move(pmouse))
   //   {

   //      return;

   //   }

   //   auto pchild = hit_test(pmouse, ::user::e_zorder_any);

   //   if (pchild)
   //   {

   //      pchild->on_mouse_move(pmouse);

   //   }

   //}


   //void main_window::on_left_button_down(::user::mouse * pmouse)
   //{

   //   auto pchild = hit_test(pmouse, ::user::e_zorder_any);

   //   if (pchild)
   //   {

   //      m_atomLeftButtonDown = pchild->id();

   //   }
   //   else
   //   {

   //      m_atomLeftButtonDown = e_dialog_result_none;

   //   }

   //   auto pitemClient = tool().defer_item(e_element_client);

   //   auto pdragClient = drag(pitemClient);

   //   if (pdragClient && !pchild)
   //   {

   //      if (drag_on_button_down(pitemClient, pmouse))
   //      {

   //         return;

   //      }

   //   }

   //   if (::is_set(pchild) && pchild->is_keyboard_focusable())
   //   {

   //      pchild->set_keyboard_focus();

   //   }

   //}


   //void main_window::on_left_button_up(::user::mouse * pmouse)
   //{

   //   release_mouse_capture();

   //   if (drag_on_button_up(pmouse))
   //   {

   //      return;

   //   }

   //   auto pchild = hit_test(pmouse, ::user::e_zorder_any);

   //   if (pchild)
   //   {

   //      m_atomLeftButtonUp = pchild->id();

   //   }
   //   else
   //   {

   //      m_atomLeftButtonUp = e_dialog_result_none;

   //   }

   //   if (m_atomLeftButtonUp == m_atomLeftButtonDown && m_atomLeftButtonUp != e_dialog_result_none)
   //   {

   //      m_payloadResult = m_atomLeftButtonUp;

   //      on_click(m_payloadResult, pmouse);

   //   }

   //   if (drag_on_button_up(pmouse))
   //   {

   //      return;

   //   }

   //}


   //void main_window::on_right_button_down(::user::mouse * pmouse)
   //{

   //   auto pchild = hit_test(pmouse, ::user::e_zorder_any);

   //   if (pchild)
   //   {

   //      m_atomRightButtonDown = pchild->id();

   //   }
   //   else
   //   {

   //      m_atomRightButtonDown = e_dialog_result_none;

   //   }


   //   if (::is_set(pchild) && pchild->is_keyboard_focusable())
   //   {

   //      pchild->set_keyboard_focus();

   //   }

   //}


   //void main_window::on_right_button_up(::user::mouse * pmouse)
   //{

   //   release_mouse_capture();

   //   auto pchild = hit_test(pmouse, ::user::e_zorder_any);

   //   if (pchild)
   //   {

   //      m_atomRightButtonUp = pchild->id();

   //   }
   //   else
   //   {

   //      m_atomRightButtonUp = e_dialog_result_none;

   //   }

   //   if (m_atomRightButtonUp == m_atomRightButtonDown)
   //   {

   //      on_right_click(m_atomLeftButtonUp, pmouse);

   //   }

   //}


   //void main_window::on_click(const ::payload & payload, ::user::mouse * pmouse)
   //{


   //}


   //void main_window::on_right_click(const ::payload & payload, ::user::mouse * pmouse)
   //{


   //}


   //bool main_window::is_active()
   //{

   //   return false;

   //}


   //void main_window::set_active()
   //{


   //}


   //void main_window::draw_children(::nano::graphics::device * pmicrodevice)
   //{


   //}


   //void main_window::delete_drawing_objects()
   //{


   //}


   //bool main_window::get_dark_mode()
   //{

   //   return false;

   //}


   /*       void main_window::create_drawing_objects()
          {


          }*/


          //void main_window::update_drawing_objects()
          //{


          //}


          //::int_point main_window::origin()
          //{

          //   throw ::exception(error_wrong_state);

          //   return {};

          //}


          //::shift_int main_window::host_to_client()
          //{

          //   return -client_to_host();

          //}


          //::shift_int main_window::client_to_host()
          //{

          //   return {};

          //}


          //::shift_int main_window::absolute_to_client()
          //{

          //   return -client_to_host();

          //}


          //::shift_int main_window::client_to_absolute()
          //{

          //   if (::windowing::get_ewindowing() == ::windowing::e_windowing_wayland)
          //   {

          //      return {};

          //   }

          //   auto r = get_window_rectangle();

          //   return r.top_left();

          //}


   ::int_point main_window::origin()
   {
      auto r = get_window_rectangle();

      return r.top_left();

   }


   //::int_rectangle main_window::get_client_rectangle()
   //{
   //   auto r = get_window_rectangle();

   //   r.offset(-r.top_left());

   //   return r;

   //}


   //::collection::count main_window::micro_button_count()
   //{

   //   ::collection::count c = 0;

   //   for (auto & pmicrouserinteraction : m_microuserinteractionaChildren)
   //   {

   //      auto pbutton = pmicrouserinteraction.cast < ::micro::button >();

   //      if (pbutton)
   //      {

   //         c++;

   //      }

   //   }

   //   return c;

   //}

   //::micro::main_window * main_window::micro_parent()
   //{

   //   return m_pmicrouserinteractionParent;

   //}

   //::micro::button * main_window::micro_button_at(::collection::index i)
   //{

   //   ::collection::count c = 0;

   //   for (auto & pmicrouserinteraction : m_microuserinteractionaChildren)
   //   {

   //      auto pbutton = pmicrouserinteraction.cast < ::micro::button >();

   //      if (pbutton)
   //      {

   //         if (i == c)
   //         {

   //            return pbutton;

   //         }

   //         c++;

   //      }

   //   }

   //   return nullptr;

   //}


   //::int_point main_window::try_absolute_mouse_position(const ::int_point & point)
   //{

   //   auto p = point;

   //   client_to_absolute()(p);

   //   return p;

   //}


   //void main_window::drag_set_mouse_capture()
   //{

   //   set_mouse_capture();

   //}


   //bool main_window::on_drag_start(::int_point & point, ::item * pitem)
   //{

   //   if (pitem->m_item.m_eelement == e_element_client)
   //   {

   //      auto pdrag = drag(pitem);

   //      if (defer_perform_entire_reposition_process(pdrag->m_pmouse))
   //      {

   //         return false;

   //      }

   //      point = origin();

   //      return true;

   //   }

   //   return false;

   //}


   //::int_point main_window::drag_mouse_cursor_position(::item * pitem, const ::int_point & point)
   //{

   //   //auto p = try_absolute_mouse_position(point);

   //   //return p;

   //   return point;

   //}


   //bool main_window::drag_shift(::item * pitem, ::user::mouse * pmouse)
   //{

   //   if (pitem->m_item.m_eelement == e_element_client)
   //   {

   //      auto point = drag_point(pitem, pmouse);

   //      set_position(point);

   //      return true;

   //   }

   //   return false;

   //}


   //bool main_window::drag_hover(::item * pitem)
   //{

   //   if (pitem->m_item.m_eelement == e_element_client)
   //   {

   //      set_cursor(e_cursor_hand);

   //      return true;

   //   }
   //   else if (pitem->m_item.m_eelement == e_element_resize)
   //   {

   //      set_cursor(e_cursor_size_bottom_right);

   //      return true;

   //   }

   //   return false;

   //}


   //void main_window::drag_release_capture()
   //{

   //   release_mouse_capture();

   //}


   //void main_window::drag_set_cursor(::item * pitem)
   //{

   //   auto pdrag = drag(pitem);

   //   set_cursor(pdrag->m_ecursor);

   //}


   /*   ::payload main_window::get_result()
      {

         return {};

      }*/


      //void main_window::on_mouse_move(::user::mouse * pmouse)
      //{


      //}


      //void main_window::on_left_button_down(::user::mouse * pmouse)
      //{


      //}


      //void main_window::on_left_button_up(::user::mouse * pmouse)
      //{


      //}


      //void main_window::on_click(const ::payload & payload, ::user::mouse * pmouse)
      //{


      //}


      //void main_window::on_right_button_down(::user::mouse * pmouse)
      //{


      //}


      //void main_window::on_right_button_up(::user::mouse * pmouse)
      //{


      //}


      //void main_window::on_right_click(const ::payload & payload, ::user::mouse * pmouse)
      //{


      //}


   void main_window::set_position(const ::int_point & point)
   {

      m_pacmewindowingwindow->set_position(point);

   }


   void main_window::display_temporary_file_with_text(const ::scoped_string & scopedstr)
   {

      string strAppId;

      strAppId = application()->m_strAppId;

      ::file::path pathFolder = directory_system()->home() / "application" / strAppId / "details";

      auto pathDetails = file_system()->time_put_contents(pathFolder, "details", "txt", scopedstr);

      node()->shell_open(pathDetails, "");

   }


   void main_window::destroy()
   {

      //if (m_psequencer)
      //{

      //   m_psequencer->on_sequence();

      //   m_psequencer.release();

      //}


      ::micro::elemental::destroy();
      // ::user::drag_client::destroy();
      //::conversation::destroy();


      // ::cast < ::manager > pmanager = system();
      //
      // pmanager->erase_signal_handler(this);

   }


   //void main_window::create_interaction(::user::main_window * puserinteractionParent, const ::atom & atom)
   //{

   //   if (!atom.is_empty())
   //   {

   //      id() = atom;

   //   }

   //   ::e_status estatus;

   //   if (!puserinteractionParent)
   //   {

   //      create_host();

   //   }
   //   else
   //   {

   //      create_child(puserinteractionParent);

   //   }

   //}


   //void main_window::create_control(::user::main_window * puserinteractionParent, const ::atom & atom)
   //{

   //   id() = atom;

   //   create_child(puserinteractionParent);

   //}


   ////void main_window::on_position_window()
   ////{


   ////}


   ///*void main_window::on_size_window()
   //{


   //}*/


   void main_window::redraw()
   {

      ::acme::user::interaction::redraw();


   }


   //void main_window::get_client_rectangle(::int_rectangle & rectangle)
   //{


   //}


   int_rectangle main_window::get_window_rectangle()
   {

      return acme_windowing_window()->get_window_rectangle();

   }


   //void main_window::set_mouse_capture()
   //{

   //   m_pacmewindowingwindow->set_mouse_capture();

   //}


   //bool main_window::has_mouse_capture()
   //{

   //   return m_pacmewindowingwindow->has_mouse_capture();

   //}


   //void main_window::release_mouse_capture()
   //{


   //}


   void main_window::set_cursor(enum_cursor ecursor)
   {


   }


   void main_window::synchronize_composited_micro_window()
   {


   }


   //void main_window::_run_modal_loop()
   //{


   //}


   bool main_window::is_popup_window() const
   {

      return false;

   }


   void main_window::_on_window_simple_action(const_char_pointer pszActionName, ::user::activation_token * puseractivationtoken)
   {

      ::string strActionName(pszActionName);

      if (strActionName == "***move")
      {

         print_line("reaching here?!");
         //defer_perform_entire_reposition_process(nullptr);

         m_pacmewindowingwindow->set_mouse_capture();
         m_pacmewindowingwindow->m_bRepositioningWindowFromCenter = true;

      }
      else if (strActionName == "***size")
      {

         print_line("also here");

         m_pacmewindowingwindow->set_mouse_capture();
         m_pacmewindowingwindow->m_bResizingWindowFromBottomRight = true;

         //defer_perform_entire_resizing_process(::experience::e_frame_sizing_top_left, nullptr);

      }
      else
      {

         ::acme::user::interaction::_on_window_simple_action(pszActionName, puseractivationtoken);

      }

   }


   void main_window::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if (ptopic->id() == id_operating_system_user_color_change)
      {

         redraw();

      }
      else if (ptopic->id() == id_set_application_dark_mode)
      {

         redraw();

      }
      else if (ptopic->id() == id_application_dark_mode_change)
      {

         redraw();

      }

   }


   void main_window::run()
   {

      show();

   }


   //void main_window::do_asynchronously()
   //{

   //   ::pointer<::acme::windowing::window> pwindow = m_pacmewindowingwindow;

   //   auto procedure = [pwindow]()
   //      {

   //         pwindow->create_window();

   //         pwindow->show_window();

   //      };

   //   if (is_main_thread())
   //   {

   //      procedure();

   //   }
   //   else
   //   {

   //      user_post(procedure);

   //   }

   //}


   //::micro::main_window * main_window::acme_user_interaction()
   //{

   //   return this;

   //}


   /*::acme::windowing::window * main_window::acme_windowing_window()
   {

      if (!m_pacmewindowingwindow)
      {

         if (m_pelementalParent)
         {

            return m_pelementalParent->acme_windowing_window();

         }

         øconstruct(m_pacmewindowingwindow);

      }

      return m_pacmewindowingwindow;

   }
*/

//void main_window::get_text_selection(character_count & iBeg, character_count & iEnd) const
//{


//}


//void main_window::get_text_selection(character_count & iBeg, character_count & iEnd, character_count & iComposingStart, character_count & iComposingEnd) const
//{


//}


//::collection::index main_window::plain_edit_sel_to_column(::draw2d::graphics_pointer & pgraphics, character_count iSel)
//{

//   return -1;

//}


//::collection::index main_window::plain_edit_sel_to_column_x(::draw2d::graphics_pointer & pgraphics, character_count iSel, int & x)
//{

//   return -1;

//}


//::collection::index main_window::plain_edit_sel_to_line(::draw2d::graphics_pointer & pgraphics, character_count iSel)
//{

//   return -1;

//}


//::collection::index main_window::plain_edit_sel_to_line_x(::draw2d::graphics_pointer & pgraphics, character_count iSel, int & x)
//{

//   return -1;

//}


//character_count main_window::plain_edit_line_column_to_sel(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine, ::collection::index iColumn)
//{

//   return -1;

//}


//character_count main_window::plain_edit_line_x_to_sel(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine, int x)
//{

//   return -1;

//}


//::collection::index main_window::plain_edit_char_to_line(::draw2d::graphics_pointer & pgraphics, character_count iSel)
//{

//   return -1;

//}


   ::trace_statement & main_window::raw_trace_statement_prefix(::trace_statement & statement) const
   {

      ::string strType = ::type(this).name();

      statement << strType;

      ::string strAtom = id().as_string();

      if (strAtom.has_character() && strAtom != strType)
      {
         statement << "=" << strAtom;
      }

      statement << "  ";

      return statement;

   }


} // namespace micro
