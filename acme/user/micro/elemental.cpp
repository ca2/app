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
// //// Child merged into elemental on 2024-10-05 05:17 <3ThomasBorregaardSorensen!!
// Created by camilo on 2022-01-21 05:10 PM <3ThomasBorregaardSorensen
//
// // merged from micro::elemental by camilo on 
// 2024-10-05 17:59 Odense Time <3ThomasBorregaardSorensen!!
// Created by camilo on 2024-09-26 22:59 Odense Time <3ThomasBorregaardSorensen!!
//
// micro::elemental Created by camilo on 31/01/2022 22:42 <3ThomasBorregaardSorensen!!
// From micro::elemental merged at ::user::elemental by
//    camilo on 2024-0926 15:04 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "button.h"
#include "elemental.h"
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
//#include "acme/platform/sequencer.h"
#include "acme/platform/system.h"
#include "acme/user/user/drag.h"
#include "acme/user/user/mouse.h"
#include "acme/user/user/tool.h"
#include "acme/windowing/windowing.h"


namespace micro
{


   elemental::elemental()
   {

      m_efont = e_font_sans;

   }


   elemental::~elemental()
   {


   }


   ::micro::theme* elemental::micro_theme()
   {

      return system()->micro_user()->micro_theme();

   }


   enum_font elemental::micro_font()
   {

      if (m_efont != e_font_none)
      {

         return m_efont;

      }

      return micro_theme()->m_efont;

   }


   ::micro::main_window* elemental::micro_main_window()
   {

      if (!micro_parent())
      {

         return nullptr;

      }

      return micro_parent()->micro_main_window();

   }


   void elemental::set_focus()
   {

      acme_windowing_window()->m_pacmeuserinteractionFocus = this;

      acme_windowing_window()->redraw();

   }


   bool elemental::is_focusable()
   {

      return false;

   }


   void elemental::set_capture()
   {

      acme_windowing_window()->m_pacmeuserinteractionCapture = this;

      acme_windowing_window()->set_capture();

   }


   bool elemental::has_capture()
   {

      if (!acme_windowing_window()->has_capture())
      {

         return false;

      }

      return acme_windowing_window()->m_pacmeuserinteractionCapture == this;

   }


   void elemental::release_capture()
   {

      if (acme_windowing_window()->m_pacmeuserinteractionCapture == this)
      {

         acme_windowing_window()->m_pacmeuserinteractionCapture.release();

         acme_windowing_window()->release_capture();

      }

   }


   void elemental::draw(::nano::graphics::device* pmicrodevice)
   {

      ::pointer<::nano::graphics::pen> pmicropenBorder;

      if (acme_windowing_window()->is_active_window())
      {

         pmicropenBorder = micro_theme()->m_ppenBorderFocus;

      }
      else
      {

         pmicropenBorder = micro_theme()->m_ppenBorder;

      }

      ::rectangle_i32 rectangleX;

      rectangleX = get_client_rectangle();

      pmicrodevice->rectangle(rectangleX, micro_theme()->m_pbrushWindow, pmicropenBorder);

      on_draw(pmicrodevice);

      draw_children(pmicrodevice);

   }


   void elemental::draw_children(::nano::graphics::device* pmicrodevice)
   {

      for (auto& pchild : *m_pacmeuserinteractionaChildren)
      {

         ::pointer<::micro::elemental> pelemental = pchild;

         pelemental->on_draw(pmicrodevice);

      }

   }


   void elemental::resize_to_fit()
   {

      auto pdevice = __create<::nano::graphics::device>();

      auto size = pdevice->get_text_extents(m_strText, micro_theme()->m_pfont);

      m_rectangle.right() = m_rectangle.left() + size.cx();

      m_rectangle.bottom() = m_rectangle.top() + size.cy();

   }


   //      //
   //// Created by camilo on 2024-09-26 18:52 Odense Time <3ThomasBorregaardSorensen!!
   ////
   //// micro::elemental Created by camilo on 31/01/2022 22:42 <3ThomasBorregaardSorensen!!
   //// From micro::elemental merged at ::user::elemental by
   ////    camilo on 2024-0926 15:04 <3ThomasBorregaardSorensen!!
   ////
   //#include "framework.h"
   //#include "drag.h"
   //#include "elemental.h"
   //#include "acme/constant/id.h"
   //#include "acme/handler/topic.h"
   //#include "acme/operating_system/a_system_menu.h"
   //#include "acme/platform/application.h"
   //#include "acme/platform/system.h"
   //#include "acme/windowing/window_base.h"
   //#include "platform/node.h"
   //
   //
   //      namespace user
   //      {


   //elemental::elemental()
   //{

   //   m_bMinimizeBox = true;
   //   m_bMaximizeBox = true;
   //   m_bResizeable = true;
   //   m_bTopMost = false;
   //   m_bStartCentered = false;
   //   m_bArbitraryPositioning = false;

   //}


   /*      elemental::~elemental()
         {


         }*/


   /*bool elemental::is_window_zoomed()
   {

      if (!acme_windowing_window())
      {

         return false;

      }

      bool bIsWindowZoomed = acme_windowing_window()->is_window_zoomed();

      if (!bIsWindowZoomed)
      {

         return false;

      }

      return true;

   }*/


   //void elemental::window_minimize()
   //{

   //   if (!acme_windowing_window())
   //   {

   //      throw ::exception(error_wrong_state);

   //   }

   //   acme_windowing_window()->window_minimize();

   //}


   //void elemental::window_maximize()
   //{

   //   if (!acme_windowing_window())
   //   {

   //      throw ::exception(error_wrong_state);

   //   }

   //   acme_windowing_window()->window_maximize();

   //}


   //void elemental::window_full_screen()
   //{

   //   if (!acme_windowing_window())
   //   {

   //      throw ::exception(error_wrong_state);

   //   }

   //   acme_windowing_window()->window_full_screen();

   //}


   //void elemental::window_restore()
   //{

   //   if (!acme_windowing_window())
   //   {

   //      throw ::exception(error_wrong_state);

   //   }

   //   acme_windowing_window()->window_restore();

   //}


   //void elemental::window_close()
   //{

   //   if (!acme_windowing_window())
   //   {

   //      throw ::exception(error_wrong_state);

   //   }

   //   acme_windowing_window()->window_close();

   //}


   //void elemental::_on_window_simple_action(const char * pszActionName)
   //{

   //   ::string strActionName(pszActionName);

   //   if (strActionName == "***move")
   //   {

   //      print_line("reaching here?!");
   //      //defer_perform_entire_reposition_process(nullptr);

   //      acme_windowing_window()->set_mouse_capture();
   //      acme_windowing_window()->m_bRepositioningWindowFromCenter = true;

   //   }
   //   else if (strActionName == "***size")
   //   {

   //      print_line("also here");

   //      acme_windowing_window()->set_mouse_capture();
   //      acme_windowing_window()->m_bResizingWindowFromBottomRight = true;

   //      //defer_perform_entire_resizing_process(::experience::e_frame_sizing_top_left, nullptr);

   //   }
   //   else
   //   {

   //      ::acme::user::interaction::_on_window_simple_action(pszActionName);

   //   }

   //}


   //::pointer<::operating_system::a_system_menu> elemental::create_system_menu(bool bContextual)
   //{

   //   auto psystemmenu = __allocate ::operating_system::a_system_menu();

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


   void elemental::set_mouse_capture()
   {

      if (!acme_windowing_window())
      {

         throw ::exception(error_wrong_state);

      }

      acme_windowing_window()->set_mouse_capture();

   }


   bool elemental::is_mouse_captured()
   {

      if (!acme_windowing_window())
      {

         throw ::exception(error_wrong_state);

      }

      return acme_windowing_window()->is_mouse_captured();

   }


   bool elemental::has_mouse_capture()
   {

      if (!acme_windowing_window())
      {

         throw ::exception(error_wrong_state);

      }

      return acme_windowing_window()->has_mouse_capture();

   }


   void elemental::release_mouse_capture()
   {

      if (!acme_windowing_window())
      {

         throw ::exception(error_wrong_state);

      }

      acme_windowing_window()->release_mouse_capture();

   }


   void elemental::on_initialize_particle()
   {


   }


   //void elemental::create_window()
   //{

   //   //auto pwindow = acme_windowing_window();

   //   //pwindow->create_window();

   //}


   void elemental::show_interaction()
   {


   }


   void elemental::hide_interaction()
   {


   }


   //void elemental::create()
   //{


   //}


   //void elemental::show_window()
   //{


   //}


   /*      void elemental::hide_window()
         {


         }*/


   //void elemental::message_loop()
   //{


   //}


   void elemental::implementation_message_loop_step()
   {


   }


   //::payload elemental::do_synchronously(const class time & timeWait)
   //{

   //   do_asynchronously();

   //   auto pmanualresetevent = __allocate manual_reset_event();

   //   if (m_psequencer)
   //   {

   //      m_psequencer->then([pmanualresetevent](auto psequencer)
   //      {

   //      pmanualresetevent->SetEvent();

   //      });

   //   }
   //   else
   //   {

   //      auto pwindow = acme_windowing_window();

   //      auto functionCloseExisting = pwindow->m_functionClose;

   //      pwindow->m_functionClose = [pmanualresetevent, functionCloseExisting](auto pinterchange)
   //         {

   //            if (functionCloseExisting)
   //            {

   //               functionCloseExisting(pinterchange);

   //            }

   //            pmanualresetevent->SetEvent();

   //         };

   //   }

   //   if (m_payloadResult.is_new())
   //   {

   //      pmanualresetevent->wait();

   //   }

   //   return m_payloadResult;

   //}


   //void elemental::draw(::nano::graphics::device * pmicrodevice)
   //{


   //}


   void elemental::on_draw(::nano::graphics::device* pmicrodevice)
   {


   }


   void elemental::on_char(int iChar)
   {

      //if (iChar == '\t' && m_pacmeuserinteractionaChildren.has_element())
      //{

      //   auto iFind = m_pacmeuserinteractionaChildren.find_first(acme_windowing_window()->m_pacmeuserinteractionFocus);

      //   iFind++;

      //   acme_windowing_window()->m_pacmeuserinteractionFocus = m_pacmeuserinteractionaChildren % iFind;

      //   redraw();

      //}
      //else if (acme_windowing_window()->m_pacmeuserinteractionFocus)
      //{

      //   acme_windowing_window()->m_pacmeuserinteractionFocus->on_char(iChar);

      //}

   }


   ::micro::elemental* elemental::hit_test(::user::mouse* pmouse, ::user::e_zorder ezorder)
   {

      auto point = pmouse->m_pointHost;

      host_to_client()(point);

      return on_hit_test(point, ezorder);

   }


   ::micro::elemental* elemental::on_hit_test(const ::point_i32& point, ::user::e_zorder ezorder)
   {

      if (m_pacmeuserinteractionaChildren)
      {

         for (auto& pchild : *m_pacmeuserinteractionaChildren)
         {

            ::pointer<::micro::elemental> pelemental = pchild;

            if (pelemental->m_rectangle.contains(point))
            {

               return pelemental;

            }

         }

      }

      return nullptr;

   }


   void elemental::add_child(::micro::elemental* pelementalChild)
   {

      pelementalChild->m_pacmeuserinteractionParent = this;

      __defer_construct_new(m_pacmeuserinteractionaChildren);

      m_pacmeuserinteractionaChildren->add(pelementalChild);

   }


   void elemental::add_button(const ::scoped_string& scopedstrText, enum_dialog_result edialogresult, char chLetter)
   {

      auto pbutton = __allocate ::micro::button();

      pbutton->m_strText = scopedstrText;
      pbutton->m_atom = edialogresult;
      pbutton->m_edialogresult1 = edialogresult;
      pbutton->m_chLetter = chLetter;
      //pbutton->m_bDefault = bDefault;

      add_child(pbutton);

   }


   ::micro::elemental* elemental::get_child_by_id(const ::atom& atom)
   {

      for (auto& pchild : *m_pacmeuserinteractionaChildren)
      {

         ::pointer<::micro::elemental> pelemental = pchild;

         if (pelemental->m_atom == atom)
         {

            return pelemental;

         }

      }

      return nullptr;

   }


   //::payload elemental::get_result()
   //{

   //   return m_payloadResult;

   //}


   void elemental::on_mouse_move(::user::mouse* pmouse)
   {

      if (acme_windowing_window()->m_pacmeuserinteractionHover)
      {

         ::pointer<::micro::elemental> pelemental;

         pelemental = acme_windowing_window()->m_pacmeuserinteractionHover;

         if (pelemental)
         {

            pelemental->on_mouse_move(pmouse);

         }

         return;

      }

      if (acme_windowing_window()->m_pacmeuserinteractionCapture
         && acme_windowing_window()->m_pacmeuserinteractionCapture != this)
      {

         ::pointer<::micro::elemental> pelemental;

         pelemental = acme_windowing_window()->m_pacmeuserinteractionCapture;

         if (pelemental)
         {

            pelemental->on_mouse_move(pmouse);

         }
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


   void elemental::on_left_button_down(::user::mouse* pmouse)
   {

      auto pchild = hit_test(pmouse, ::user::e_zorder_any);

      if (pchild)
      {

         auto pmainwindow = micro_main_window();

         if (pmainwindow)
         {

            pmainwindow->m_atomLeftButtonDown = pchild->m_atom;

         }

      }
      else
      {

         auto pmainwindow = micro_main_window();

         if (pmainwindow)
         {

            pmainwindow->m_atomLeftButtonDown = e_dialog_result_none;

         }

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


   void elemental::on_left_button_up(::user::mouse* pmouse)
   {

      release_capture();

      if (drag_on_button_up(pmouse))
      {

         return;

      }

      auto pchild = hit_test(pmouse, ::user::e_zorder_any);

      if (pchild)
      {

         auto pmainwindow = micro_main_window();

         if (pmainwindow)
         {

            pmainwindow->m_atomLeftButtonUp = pchild->m_atom;

         }

      }
      else
      {

         auto pmainwindow = micro_main_window();

         if (pmainwindow)
         {

            pmainwindow->m_atomLeftButtonUp = e_dialog_result_none;

         }

      }

      auto pmainwindow = micro_main_window();

      if (pmainwindow)
      {

         if (pmainwindow->m_atomLeftButtonUp == pmainwindow->m_atomLeftButtonDown
            && pmainwindow->m_atomLeftButtonUp != e_dialog_result_none)
         {

            pmainwindow->on_click(pmainwindow->m_atomLeftButtonUp, pmouse);

         }

      }

      if (drag_on_button_up(pmouse))
      {

         return;

      }

   }


   void elemental::on_right_button_down(::user::mouse* pmouse)
   {

      auto pchild = hit_test(pmouse, ::user::e_zorder_any);

      if (pchild)
      {

         auto pmainwindow = micro_main_window();

         if (pmainwindow)
         {

            pmainwindow->m_atomRightButtonDown = pchild->m_atom;

         }

      }
      else
      {

         auto pmainwindow = micro_main_window();

         if (pmainwindow)
         {

            pmainwindow->m_atomRightButtonDown = e_dialog_result_none;

         }

      }


      if (::is_set(pchild) && pchild->is_focusable())
      {

         pchild->set_focus();

      }

   }


   void elemental::on_right_button_up(::user::mouse* pmouse)
   {

      release_capture();

      auto pchild = hit_test(pmouse, ::user::e_zorder_any);

      if (pchild)
      {

         auto pmainwindow = micro_main_window();

         if (pmainwindow)
         {

            pmainwindow->m_atomRightButtonUp = pchild->m_atom;

         }

      }
      else
      {

         auto pmainwindow = micro_main_window();

         if (pmainwindow)
         {

            pmainwindow->m_atomRightButtonUp = e_dialog_result_none;

         }

      }

      auto pmainwindow = micro_main_window();

      if (pmainwindow)
      {

         if (pmainwindow->m_atomRightButtonUp == pmainwindow->m_atomRightButtonDown)
         {

            pmainwindow->on_right_click(pmainwindow->m_atomLeftButtonUp, pmouse);

         }

      }

   }


   void elemental::on_click(const ::payload& payload, ::user::mouse* pmouse)
   {


   }


   void elemental::on_right_click(const ::payload& payload, ::user::mouse* pmouse)
   {


   }


   //bool elemental::is_active()
   //{

   //   return false;

   //}


   //void elemental::set_active()
   //{


   //}


   //void elemental::draw_children(::nano::graphics::device * pmicrodevice)
   //{


   //}


   //void elemental::delete_drawing_objects()
   //{


   //}


   //bool elemental::get_dark_mode()
   //{

   //   return false;

   //}


   /*       void elemental::create_drawing_objects()
          {


          }*/


   //void elemental::update_drawing_objects()
   //{


   //}


   //::point_i32 elemental::origin()
   //{

   //   throw ::exception(error_wrong_state);

   //   return {};

   //}


   ::shift_i32 elemental::host_to_client()
   {

      return -client_to_host();

   }


   ::shift_i32 elemental::client_to_host()
   {

      return {};

   }


   ::shift_i32 elemental::absolute_to_client()
   {

      return -client_to_host();

   }


   ::shift_i32 elemental::client_to_absolute()
   {

      if (system()->acme_windowing()->get_ewindowing() == ::windowing::e_windowing_wayland)
      {

         return {};

      }

      auto r = get_window_rectangle();

      return r.top_left();

   }


   ::point_i32 elemental::origin()
   {
      auto r = get_window_rectangle();

      return r.top_left();

   }


   ::rectangle_i32 elemental::get_client_rectangle()
   {
      auto r = get_rectangle();

      r.offset(-r.top_left());

      return r;

   }


   ::micro::elemental* elemental::micro_parent()
   {

      return m_pacmeuserinteractionParent.cast<::micro::elemental>();

   }


   ::collection::count elemental::micro_button_count()
   {

      ::collection::count c = 0;

      for (auto& pinteraction : *m_pacmeuserinteractionaChildren)
      {

         auto pbutton = pinteraction.cast<::micro::button>();

         if (pbutton)
         {

            c++;

         }

      }

      return c;

   }


   ::micro::button* elemental::micro_button_at(::collection::index i)
   {

      ::collection::count c = 0;

      for (auto& pinteraction : *m_pacmeuserinteractionaChildren)
      {

         auto pbutton = pinteraction.cast<::micro::button>();

         if (pbutton)
         {

            if (i == c)
            {

               return pbutton;

            }

            c++;

         }

      }

      return nullptr;

   }


   //::point_i32 elemental::try_absolute_mouse_position(const ::point_i32 & point)
   //{

   //   auto p = point;

   //   client_to_absolute()(p);

   //   return p;

   //}


   //void elemental::drag_set_capture()
   //{

   //   set_capture();

   //}


   //bool elemental::on_drag_start(::point_i32 & point, ::item * pitem)
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


   //::point_i32 elemental::drag_mouse_cursor_position(::item * pitem, const ::point_i32 & point)
   //{

   //   //auto p = try_absolute_mouse_position(point);

   //   //return p;

   //   return point;

   //}


   //bool elemental::drag_shift(::item * pitem, ::user::mouse * pmouse)
   //{

   //   if (pitem->m_item.m_eelement == e_element_client)
   //   {

   //      auto point = drag_point(pitem, pmouse);

   //      set_position(point);

   //      return true;

   //   }

   //   return false;

   //}


   //bool elemental::drag_hover(::item * pitem)
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


   //void elemental::drag_release_capture()
   //{

   //   release_capture();

   //}


   //void elemental::drag_set_cursor(::item * pitem)
   //{

   //   auto pdrag = drag(pitem);

   //   set_cursor(pdrag->m_ecursor);

   //}


   /*   ::payload elemental::get_result()
      {

         return {};

      }*/


   //void elemental::on_mouse_move(::user::mouse * pmouse)
   //{


   //}


   //void elemental::on_left_button_down(::user::mouse * pmouse)
   //{


   //}


   //void elemental::on_left_button_up(::user::mouse * pmouse)
   //{


   //}


   //void elemental::on_click(const ::payload & payload, ::user::mouse * pmouse)
   //{


   //}


   //void elemental::on_right_button_down(::user::mouse * pmouse)
   //{


   //}


   //void elemental::on_right_button_up(::user::mouse * pmouse)
   //{


   //}


   //void elemental::on_right_click(const ::payload & payload, ::user::mouse * pmouse)
   //{


   //}


   void elemental::set_position(const ::point_i32& point)
   {

      acme_windowing_window()->set_position(point);

   }


   void elemental::display_temporary_file_with_text(const ::string& str)
   {

      string strAppId;

      strAppId = application()->m_strAppId;

      ::file::path pathFolder = directory_system()->home() / "application" / strAppId / "details";

      auto pathDetails = file_system()->time_put_contents(pathFolder, "details", "txt", str);

      node()->shell_open(pathDetails, "");

   }


   void elemental::destroy()
   {

      //if (m_psequencer)
      //{

      //   m_psequencer->on_sequence();

      //   m_psequencer.release();

      //}


      ::acme::user::interaction::destroy();
      //::user::drag_client::destroy();
      //::conversation::destroy();

      system()->erase_signal_handler(this);

   }


   //void elemental::create_interaction(::user::elemental * puserinteractionParent, const ::atom & atom)
   //{

   //   if (!atom.is_empty())
   //   {

   //      m_atom = atom;

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


   //void elemental::create_control(::user::elemental * puserinteractionParent, const ::atom & atom)
   //{

   //   m_atom = atom;

   //   create_child(puserinteractionParent);

   //}


   //void elemental::on_position_window()
   //{


   //}


   /*void elemental::on_size_window()
   {


   }*/


   void elemental::redraw()
   {


   }


   //void elemental::get_client_rectangle(::rectangle_i32 & rectangle)
   //{


   //}


   rectangle_i32 elemental::get_rectangle()
   {

      return m_rectangle;

   }


   //void elemental::set_capture()
   //{

   //   acme_windowing_window()->set_capture();

   //}


   //bool elemental::has_capture()
   //{

   //   return acme_windowing_window()->has_capture();

   //}


   //void elemental::release_capture()
   //{


   //}


   void elemental::set_cursor(enum_cursor ecursor)
   {


   }


   void elemental::synchronize_composited_micro_window()
   {


   }


   //void elemental::_run_modal_loop()
   //{


   //}


   bool elemental::is_popup_window() const
   {

      return false;

   }


   void elemental::handle(::topic* ptopic, ::context* pcontext)
   {

      if (ptopic->m_atom == id_operating_system_user_color_change)
      {

         redraw();

      }
      else if (ptopic->m_atom == id_set_application_dark_mode)
      {

         redraw();

      }
      else if (ptopic->m_atom == id_application_dark_mode_change)
      {

         redraw();

      }

   }


   //void elemental::do_asynchronously()
   //{

   //   ::pointer<::acme::windowing::window> pwindow = acme_windowing_window();

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


   //::micro::elemental * elemental::acme_user_interaction()
   //{

   //   return this;

   //}


   //::acme::windowing::window * elemental::acme_windowing_window()
   //{

   //   if (!acme_windowing_window())
   //   {

   //      if (m_pacmeuserinteractionParent)
   //      {

   //         return m_pacmeuserinteractionParent->acme_windowing_window();

   //      }

   //      __construct(acme_windowing_window());

   //   }

   //   return acme_windowing_window();

   //}


   //void elemental::get_text_selection(strsize & iBeg, strsize & iEnd) const
   //{


   //}


   //void elemental::get_text_selection(strsize & iBeg, strsize & iEnd, strsize & iComposingStart, strsize & iComposingEnd) const
   //{


   //}


   //::collection::index elemental::plain_edit_sel_to_column(::draw2d::graphics_pointer & pgraphics, strsize iSel)
   //{

   //   return -1;

   //}


   //::collection::index elemental::plain_edit_sel_to_column_x(::draw2d::graphics_pointer & pgraphics, strsize iSel, i32 & x)
   //{

   //   return -1;

   //}


   //::collection::index elemental::plain_edit_sel_to_line(::draw2d::graphics_pointer & pgraphics, strsize iSel)
   //{

   //   return -1;

   //}


   //::collection::index elemental::plain_edit_sel_to_line_x(::draw2d::graphics_pointer & pgraphics, strsize iSel, i32 & x)
   //{

   //   return -1;

   //}


   //strsize elemental::plain_edit_line_column_to_sel(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine, ::collection::index iColumn)
   //{

   //   return -1;

   //}


   //strsize elemental::plain_edit_line_x_to_sel(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine, i32 x)
   //{

   //   return -1;

   //}


   //::collection::index elemental::plain_edit_char_to_line(::draw2d::graphics_pointer & pgraphics, strsize iSel)
   //{

   //   return -1;

   //}


   ::trace_statement& elemental::raw_trace_statement_prefix(::trace_statement& statement) const
   {

      ::string strType = ::type(this).name();

      statement << strType;

      ::string strAtom = m_atom.as_string();

      if (strAtom.has_char() && strAtom != strType)
      {
         statement << "=" << strAtom;
      }

      statement << "  ";

      return statement;

   }


} // namespace micro
