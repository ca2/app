//
// // Created from nano::user::interchange by
// // camilo on 2024-10-05 16:52 <3ThomasBorregaardSorensen!!
// Created by camilo on 31/01/2022 14:32 <3ThomasBorregaardSorensen!!
// renamed interchange from interchange by camilo on
//    2024-09-26 15:37 <3ThomasBorregaardSorensen!!
// 
// // // Merged from (acme)windowing and (acme)windowing_system by
// //   camilo on 2024-10-05 11:07 <3ThomasBorregaardSorensen!!
// //   (acme)windowing_system::windowing_system
// //       ---->windowing::windowing_base
// // //       ---->nano::user::user
// //   (acme)windowing::window_base
// //       ---->nano::user::interchange
//
// //// Child merged into interaction on 2024-10-05 05:17 <3ThomasBorregaardSorensen!!
// Created by camilo on 2022-01-21 05:10 PM <3ThomasBorregaardSorensen

#include "framework.h"
#include "interaction.h"
#include "user.h"
#include "window.h"
#include "acme/nano/nano.h"

//
// // merged from user::interaction_base by camilo on 
// 2024-10-05 17:59 Odense Time <3ThomasBorregaardSorensen!!
// Created by camilo on 2024-09-26 22:59 Odense Time <3ThomasBorregaardSorensen!!
//
// nano::user::interaction Created by camilo on 31/01/2022 22:42 <3ThomasBorregaardSorensen!!
// From nano::user::interaction merged at ::user::interaction by
//    camilo on 2024-0926 15:04 <3ThomasBorregaardSorensen!!
//
//#include "framework.h"
#include "drag.h"
#include "interaction.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/windowing/window_base.h"
#include "platform/node.h"


namespace user
{

namespace nano
{


   namespace user
   {


      interaction::interaction()
      {


      }


      interaction::~interaction()
      {


      }



      ::nano::user::theme * interaction::nano_user_theme()
      {

         return nano()->user()->nano_user_theme();

      }


      enum_font interaction::nano_user_font()
      {

         if (m_efont != e_font_none)
         {

            return m_efont;

         }

         return nano_user_theme()->m_efont;

      }

      ///child


      void interaction::set_focus()
      {

         nano_user_window()->m_pchildFocus = this;

         nano_user_window()->redraw();

      }


      bool interaction::is_focusable()
      {

         return false;

      }


      void interaction::on_mouse_move(::user::mouse * pmouse)
      {


      }


      void interaction::set_capture()
      {

         nano_user_window()->m_pchildCapture = this;

         nano_user_window()->set_capture();

      }


      bool interaction::has_capture()
      {

         if (!nano_user_window()->has_capture())
         {

            return false;

         }

         return nano_user_window()->m_pchildCapture == this;

      }


      void interaction::release_capture()
      {

         if (nano_user_window()->m_pchildCapture == this)
         {

            nano_user_window()->m_pchildCapture.release();

            nano_user_window()->release_capture();

         }

      }


      void interaction::resize_to_fit()
      {

         auto pdevice = __create < ::nano::graphics::device >();

         auto size = pdevice->get_text_extents(m_strText, nano_user_window()->m_pfont);

         m_rectangle.right() = m_rectangle.left() + size.cx();

         m_rectangle.bottom() = m_rectangle.top() + size.cy();

      }

//      //
//// Created by camilo on 2024-09-26 18:52 Odense Time <3ThomasBorregaardSorensen!!
////
//// nano::user::interaction Created by camilo on 31/01/2022 22:42 <3ThomasBorregaardSorensen!!
//// From nano::user::interaction merged at ::user::interaction by
////    camilo on 2024-0926 15:04 <3ThomasBorregaardSorensen!!
////
//#include "framework.h"
//#include "drag.h"
//#include "interaction.h"
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


         interaction::interaction()
         {

            m_bMinimizeBox = true;
            m_bMaximizeBox = true;
            m_bResizeable = true;
            m_bTopMost = false;
            m_bStartCentered = false;
            m_bArbitraryPositioning = false;

         }


         interaction::~interaction()
         {


         }


         bool interaction::is_window_zoomed()
         {

            if (!m_pwindowbase)
            {

               return false;

            }

            bool bIsWindowZoomed = m_pwindowbase->is_window_zoomed();

            if (!bIsWindowZoomed)
            {

               return false;

            }

            return true;

         }


         void interaction::window_minimize()
         {

            if (!m_pwindowbase)
            {

               throw ::exception(error_wrong_state);

            }

            m_pwindowbase->window_minimize();

         }


         void interaction::window_maximize()
         {

            if (!m_pwindowbase)
            {

               throw ::exception(error_wrong_state);

            }

            m_pwindowbase->window_maximize();

         }


         void interaction::window_full_screen()
         {

            if (!m_pwindowbase)
            {

               throw ::exception(error_wrong_state);

            }

            m_pwindowbase->window_full_screen();

         }


         void interaction::window_restore()
         {

            if (!m_pwindowbase)
            {

               throw ::exception(error_wrong_state);

            }

            m_pwindowbase->window_restore();

         }


         void interaction::window_close()
         {

            if (!m_pwindowbase)
            {

               throw ::exception(error_wrong_state);

            }

            m_pwindowbase->window_close();

         }


         void interaction::_on_window_simple_action(const char * pszActionName)
         {

            ::string strActionName(pszActionName);

            if (strActionName == "minimize")
            {

               display(e_display_iconic);

            }
            else if (strActionName == "maximize")
            {

               display(e_display_zoomed);

            }
            else if (strActionName == "restore")
            {

               display(e_display_normal);

            }
            else if (strActionName == "about_box")
            {

               application()->show_about_box();

            }
            else if (strActionName == "close")
            {

               window_close();

            }
            else if (strActionName == "***move")
            {

               print_line("reaching here?!");
               //defer_perform_entire_reposition_process(nullptr);

               m_pwindowbase->set_mouse_capture();
               m_pwindowbase->m_bRepositioningWindowFromCenter = true;

            }
            else if (strActionName == "***size")
            {

               print_line("also here");

               m_pwindowbase->set_mouse_capture();
               m_pwindowbase->m_bResizingWindowFromBottomRight = true;

               //defer_perform_entire_resizing_process(::experience::e_frame_sizing_top_left, nullptr);

            }

         }



         ::pointer<::operating_system::a_system_menu> interaction::create_system_menu(bool bContextual)
         {

            auto psystemmenu = ::place(new ::operating_system::a_system_menu());

            if (m_bMinimizeBox)
            {

               psystemmenu->add_item("Minimize", "minimize");

            }

            if (!bContextual || is_window_zoomed())
            {

               psystemmenu->add_item("Restore", "restore");

            }

            if (m_bMaximizeBox)
            {

               if (!bContextual || !is_window_zoomed())
               {

                  psystemmenu->add_item("Maximize", "maximize");

               }

            }

            if (node()->get_etoolkit() == e_toolkit_gtk4 ||
               node()->get_etoolkit() == e_toolkit_gtk3)
            {
               psystemmenu->add_item("Drag to Move", "***move");
            }
            else
            {
               psystemmenu->add_item("Move", "***move");

            }

            if (m_bResizeable)
            {

               if (node()->get_etoolkit() == e_toolkit_gtk4 ||
                  node()->get_etoolkit() == e_toolkit_gtk3)
               {
                  psystemmenu->add_item("Drag to Size", "***size");
               }
               else
               {
                  psystemmenu->add_item("Size", "***size");

               }

            }

            psystemmenu->add_separator();

            psystemmenu->add_item("About...", "about_box");

            psystemmenu->add_separator();

            psystemmenu->add_item("Close", "close");

            return psystemmenu;

         }


         void interaction::set_mouse_capture()
         {

            if (!m_pwindowbase)
            {

               throw ::exception(error_wrong_state);

            }

            m_pwindowbase->set_mouse_capture();

         }


         bool interaction::is_mouse_captured()
         {

            if (!m_pwindowbase)
            {

               throw ::exception(error_wrong_state);

            }

            return m_pwindowbase->is_mouse_captured();

         }


         bool interaction::has_mouse_capture()
         {

            if (!m_pwindowbase)
            {

               throw ::exception(error_wrong_state);

            }

            return m_pwindowbase->has_mouse_capture();

         }


         void interaction::release_mouse_capture()
         {

            if (!m_pwindowbase)
            {

               throw ::exception(error_wrong_state);

            }

            m_pwindowbase->release_mouse_capture();

         }



         void interaction::on_initialize_particle()
         {


         }




         void interaction::create()
         {


         }


         void interaction::show_window()
         {


         }


         void interaction::hide_window()
         {


         }


         void interaction::message_loop()
         {


         }


         void interaction::implementation_message_loop_step()
         {


         }


         void interaction::draw(::nano::graphics::device * pnanodevice)
         {


         }


         void interaction::on_draw(::nano::graphics::device * pnanodevice)
         {


         }


         void interaction::on_char(int iChar)
         {


         }


         bool interaction::is_active()
         {

            return false;

         }


         void interaction::set_active()
         {


         }


         void interaction::draw_children(::nano::graphics::device * pnanodevice)
         {


         }


         void interaction::delete_drawing_objects()
         {


         }


         bool interaction::get_dark_mode()
         {

            return false;

         }


         void interaction::create_drawing_objects()
         {


         }


         void interaction::update_drawing_objects()
         {


         }


         ::point_i32 interaction::origin()
         {

            throw ::exception(error_wrong_state);

            return {};

         }


         ::shift_i32 interaction::host_to_client()
         {

            return -client_to_host();

         }


         ::shift_i32 interaction::client_to_host()
         {

            return {};

         }


         ::shift_i32 interaction::absolute_to_client()
         {

            return -client_to_host();

         }


         ::shift_i32 interaction::client_to_absolute()
         {

            if (system()->m_ewindowing == e_windowing_wayland)
            {

               return {};

            }

            auto r = get_window_rectangle();

            return r.top_left();

         }


         ::point_i32 interaction::try_absolute_mouse_position(const ::point_i32 & point)
         {

            auto p = point;

            client_to_absolute()(p);

            return p;

         }


         void interaction::drag_set_capture()
         {

            set_capture();

         }


         bool interaction::on_drag_start(::point_i32 & point, ::item * pitem)
         {

            if (pitem->m_item.m_eelement == e_element_client)
            {

               auto pdrag = drag(pitem);

               if (defer_perform_entire_reposition_process(pdrag->m_pmouse))
               {

                  return false;

               }

               point = origin();

               return true;

            }

            return false;

         }


         ::point_i32 interaction::drag_mouse_cursor_position(::item * pitem, const ::point_i32 & point)
         {

            auto p = try_absolute_mouse_position(point);

            return p;

         }


         bool interaction::drag_shift(::item * pitem, ::user::mouse * pmouse)
         {

            if (pitem->m_item.m_eelement == e_element_client)
            {

               auto point = drag_point(pitem, pmouse);

               set_position(point);

               return true;

            }

            return false;

         }


         bool interaction::drag_hover(::item * pitem)
         {

            if (pitem->m_item.m_eelement == e_element_client)
            {

               set_cursor(e_cursor_hand);

               return true;

            }
            else if (pitem->m_item.m_eelement == e_element_resize)
            {

               set_cursor(e_cursor_size_bottom_right);

               return true;

            }

            return false;

         }


         void interaction::drag_release_capture()
         {

            release_capture();

         }


         void interaction::drag_set_cursor(::item * pitem)
         {

            auto pdrag = drag(pitem);

            set_cursor(pdrag->m_ecursor);

         }


         ::payload interaction::get_result()
         {

            return {};

         }


         void interaction::on_mouse_move(::user::mouse * pmouse)
         {


         }


         void interaction::on_left_button_down(::user::mouse * pmouse)
         {


         }


         void interaction::on_left_button_up(::user::mouse * pmouse)
         {


         }


         void interaction::on_click(const ::payload & payload, ::user::mouse * pmouse)
         {


         }


         void interaction::on_right_button_down(::user::mouse * pmouse)
         {


         }


         void interaction::on_right_button_up(::user::mouse * pmouse)
         {


         }


         void interaction::on_right_click(const ::payload & payload, ::user::mouse * pmouse)
         {


         }


         void interaction::set_position(const ::point_i32 & point)
         {

            m_pwindowbase->set_position(point);

         }


         void interaction::destroy()
         {

            ::user::element::destroy();
            ::user::drag_client::destroy();
            ::conversation::destroy();

            system()->erase_signal_handler(this);

         }


         void interaction::create_interaction(::user::interaction * puserinteractionParent, const ::atom & atom)
         {

            if (!atom.is_empty())
            {

               m_atom = atom;

            }

            ::e_status estatus;

            if (!puserinteractionParent)
            {

               create_host();

            }
            else
            {

               create_child(puserinteractionParent);

            }

         }


         void interaction::create_control(::user::interaction * puserinteractionParent, const ::atom & atom)
         {

            m_atom = atom;

            create_child(puserinteractionParent);

         }


         void interaction::on_position_window()
         {


         }


         void interaction::on_size_window()
         {


         }


         void interaction::redraw()
         {


         }


         void interaction::get_client_rectangle(::rectangle_i32 & rectangle)
         {


         }


         rectangle_i32 interaction::get_window_rectangle()
         {

            return {};

         }


         void interaction::set_capture()
         {

            m_pwindowbase->set_capture();

         }


         bool interaction::has_capture()
         {

            return m_pwindowbase->has_capture();

         }


         void interaction::release_capture()
         {


         }


         void interaction::set_cursor(enum_cursor ecursor)
         {


         }


         void interaction::synchronize_composited_nano_window()
         {


         }


         void interaction::_run_modal_loop()
         {


         }


         bool interaction::is_popup_window() const
         {

            return false;

         }


         void interaction::handle(::topic * ptopic, ::context * pcontext)
         {

            if (ptopic->m_atom == id_operating_system_user_color_change)
            {

               update_drawing_objects();

               redraw();

            }
            else if (ptopic->m_atom == id_set_application_dark_mode)
            {

               update_drawing_objects();

               redraw();

            }
            else if (ptopic->m_atom == id_application_dark_mode_change)
            {

               update_drawing_objects();

               redraw();

            }

         }


         void interaction::do_asynchronously()
         {

            ::pointer<::windowing::window_base> pwindowbase = m_pwindowbase;

            auto procedure = [pwindowbase]()
               {

                  pwindowbase->create_window();

                  pwindowbase->show_window();

               };

            if (is_main_thread())
            {

               procedure();

            }
            else
            {

               user_post(procedure);

            }

         }


         ::payload interaction::do_synchronously(const class time & timeWait)
         {

            create();

            show_window();

            message_loop();

            return m_payloadResult;

         }


         ::user::interaction * interaction::user_interaction_base()
         {

            return this;

         }


         ::windowing::window_base * interaction::windowing_window_base()
         {

            return m_pwindowbase;

         }


         void interaction::get_text_selection(strsize & iBeg, strsize & iEnd) const
         {


         }


         void interaction::get_text_selection(strsize & iBeg, strsize & iEnd, strsize & iComposingStart, strsize & iComposingEnd) const
         {


         }


         ::collection::index interaction::plain_edit_sel_to_column(::draw2d::graphics_pointer & pgraphics, strsize iSel)
         {

            return -1;

         }


         ::collection::index interaction::plain_edit_sel_to_column_x(::draw2d::graphics_pointer & pgraphics, strsize iSel, i32 & x)
         {

            return -1;

         }


         ::collection::index interaction::plain_edit_sel_to_line(::draw2d::graphics_pointer & pgraphics, strsize iSel)
         {

            return -1;

         }


         ::collection::index interaction::plain_edit_sel_to_line_x(::draw2d::graphics_pointer & pgraphics, strsize iSel, i32 & x)
         {

            return -1;

         }


         strsize interaction::plain_edit_line_column_to_sel(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine, ::collection::index iColumn)
         {

            return -1;

         }


         strsize interaction::plain_edit_line_x_to_sel(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine, i32 x)
         {

            return -1;

         }


         ::collection::index interaction::plain_edit_char_to_line(::draw2d::graphics_pointer & pgraphics, strsize iSel)
         {

            return -1;

         }


         ::trace_statement & interaction::raw_trace_statement_prefix(::trace_statement & statement) const
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





   } // namespace user


} // namespace nano



