////
//// Created by camilo on 2024-09-26 18:52 Odense Time <3ThomasBorregaardSorensen!!
////
//// nano::user::interaction_base Created by camilo on 31/01/2022 22:42 <3ThomasBorregaardSorensen!!
//// From nano::user::interaction_base merged at ::user::interaction_base by
////    camilo on 2024-0926 15:04 <3ThomasBorregaardSorensen!!
////
//#include "framework.h"
//#include "drag.h"
//#include "interaction_base.h"
//#include "acme/constant/id.h"
//#include "acme/handler/topic.h"
//#include "acme/operating_system/a_system_menu.h"
//#include "acme/platform/application.h"
//#include "acme/platform/system.h"
//#include "acme/windowing/window_base.h"
//#include "platform/node.h"
//
//
//namespace user
//{
//
//
//   interaction_base::interaction_base()
//   {
//
//      m_bMinimizeBox = true;
//      m_bMaximizeBox = true;
//      m_bResizeable = true;
//      m_bTopMost = false;
//      m_bStartCentered = false;
//      m_bArbitraryPositioning = false;
//
//   }
//
//
//   interaction_base::~interaction_base()
//   {
//
//
//   }
//
//
//   bool interaction_base::is_window_zoomed()
//   {
//
//      if(!m_pwindowbase)
//      {
//
//         return false;
//
//      }
//
//      bool bIsWindowZoomed = m_pwindowbase->is_window_zoomed();
//
//      if(!bIsWindowZoomed)
//      {
//
//         return false;
//
//      }
//
//      return true;
//
//   }
//
//
//   void interaction_base::window_minimize()
//   {
//
//      if(!m_pwindowbase)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      m_pwindowbase->window_minimize();
//
//   }
//
//
//   void interaction_base::window_maximize()
//   {
//
//      if(!m_pwindowbase)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      m_pwindowbase->window_maximize();
//
//   }
//
//
//   void interaction_base::window_full_screen()
//   {
//
//      if(!m_pwindowbase)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      m_pwindowbase->window_full_screen();
//
//   }
//
//
//   void interaction_base::window_restore()
//   {
//
//      if(!m_pwindowbase)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      m_pwindowbase->window_restore();
//
//   }
//
//
//   void interaction_base::window_close()
//   {
//
//      if(!m_pwindowbase)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      m_pwindowbase->window_close();
//
//   }
//
//
//   void interaction_base::_on_window_simple_action(const char * pszActionName)
//   {
//
//      ::string strActionName(pszActionName);
//
//      if(strActionName == "minimize")
//      {
//
//         display(e_display_iconic);
//
//      }
//      else if(strActionName == "maximize")
//      {
//
//         display(e_display_zoomed);
//
//      }
//      else if(strActionName == "restore")
//      {
//
//         display(e_display_normal);
//
//      }
//      else if(strActionName == "about_box")
//      {
//
//         application()->show_about_box();
//
//      }
//      else if(strActionName == "close")
//      {
//
//         window_close();
//
//      }
//      else if(strActionName == "***move")
//      {
//
//         print_line("reaching here?!");
//         //defer_perform_entire_reposition_process(nullptr);
//
//         m_pwindowbase->set_mouse_capture();
//         m_pwindowbase->m_bRepositioningWindowFromCenter = true;
//
//      }
//      else if(strActionName == "***size")
//      {
//
//         print_line("also here");
//
//         m_pwindowbase->set_mouse_capture();
//      m_pwindowbase->m_bResizingWindowFromBottomRight = true;
//
//         //defer_perform_entire_resizing_process(::experience::e_frame_sizing_top_left, nullptr);
//
//      }
//
//   }
//
//
//
//   ::pointer<::operating_system::a_system_menu> interaction_base::create_system_menu(bool bContextual)
//   {
//
//      auto psystemmenu = ::place(new ::operating_system::a_system_menu());
//
//      if (m_bMinimizeBox)
//      {
//
//         psystemmenu->add_item("Minimize", "minimize");
//
//      }
//
//      if (!bContextual || is_window_zoomed())
//      {
//
//         psystemmenu->add_item("Restore", "restore");
//
//      }
//
//      if (m_bMaximizeBox)
//      {
//
//         if (!bContextual || !is_window_zoomed())
//         {
//
//            psystemmenu->add_item("Maximize", "maximize");
//
//         }
//
//      }
//
//      if(::windowing::get_etoolkit() == e_toolkit_gtk4 ||
//         ::windowing::get_etoolkit() == e_toolkit_gtk3)
//      {
//         psystemmenu->add_item("Drag to Move", "***move");
//      }
//      else
//      {
//         psystemmenu->add_item("Move", "***move");
//
//      }
//
//      if (m_bResizeable)
//      {
//
//         if(::windowing::get_etoolkit() == e_toolkit_gtk4 ||
//            ::windowing::get_etoolkit() == e_toolkit_gtk3)
//         {
//            psystemmenu->add_item("Drag to Size", "***size");
//         }
//         else
//         {
//            psystemmenu->add_item("Size", "***size");
//
//         }
//
//      }
//
//      psystemmenu->add_separator();
//
//      psystemmenu->add_item("About...", "about_box");
//
//      psystemmenu->add_separator();
//
//      psystemmenu->add_item("Close", "close");
//
//      return psystemmenu;
//
//   }
//
//
//   void interaction_base::set_mouse_capture()
//   {
//
//      if(!m_pwindowbase)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      m_pwindowbase->set_mouse_capture();
//
//   }
//
//
//   bool interaction_base::is_mouse_captured()
//   {
//
//      if(!m_pwindowbase)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      return m_pwindowbase->is_mouse_captured();
//
//   }
//
//
//   bool interaction_base::has_mouse_capture()
//   {
//
//      if(!m_pwindowbase)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      return m_pwindowbase->has_mouse_capture();
//
//   }
//
//
//   void interaction_base::release_mouse_capture()
//   {
//
//      if(!m_pwindowbase)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      m_pwindowbase->release_mouse_capture();
//
//   }
//
//
//
//   void interaction_base::on_initialize_particle()
//   {
//
//
//   }
//
//
//
//
//   void interaction_base::create()
//   {
//
//
//   }
//
//
//   void interaction_base::show_window()
//   {
//
//
//   }
//
//
//   void interaction_base::hide_window()
//   {
//
//
//   }
//
//
//   void interaction_base::message_loop()
//   {
//
//
//   }
//
//
//   void interaction_base::implementation_message_loop_step()
//   {
//
//
//   }
//
//
//   void interaction_base::draw(::nano::graphics::device* pnanodevice)
//   {
//
//
//   }
//
//
//   void interaction_base::on_draw(::nano::graphics::device* pnanodevice)
//   {
//
//
//   }
//
//
//   void interaction_base::on_char(int iChar)
//   {
//
//
//   }
//
//
//   bool interaction_base::is_active()
//   {
//
//      return false;
//
//   }
//
//
//   void interaction_base::set_active()
//   {
//
//
//   }
//
//
//   void interaction_base::draw_children(::nano::graphics::device* pnanodevice)
//   {
//
//
//   }
//
//
//   void interaction_base::delete_drawing_objects()
//   {
//
//
//   }
//
//
//   bool interaction_base::get_dark_mode()
//   {
//
//      return false;
//
//   }
//
//
//   void interaction_base::create_drawing_objects()
//   {
//
//
//   }
//
//
//   void interaction_base::update_drawing_objects()
//   {
//
//
//   }
//
//
//   ::point_i32 interaction_base::origin()
//   {
//
//      throw ::exception(error_wrong_state);
//
//      return {};
//
//   }
//
//
//   ::shift_i32 interaction_base::host_to_client()
//   {
//
//      return -client_to_host();
//
//   }
//
//
//   ::shift_i32 interaction_base::client_to_host()
//   {
//
//      return {};
//
//   }
//
//
//   ::shift_i32 interaction_base::absolute_to_client()
//   {
//
//      return -client_to_host();
//
//   }
//
//
//   ::shift_i32 interaction_base::client_to_absolute()
//   {
//
//      if (::windowing::get_ewindowing() == ::windowing::e_windowing_wayland)
//      {
//
//         return {};
//
//      }
//
//      auto r = get_window_rectangle();
//
//      return r.top_left();
//
//   }
//
//
//   ::point_i32 interaction_base::try_absolute_mouse_position(const ::point_i32& point)
//   {
//
//      auto p = point;
//
//      client_to_absolute()(p);
//
//      return p;
//
//   }
//
//
//   void interaction_base::drag_set_capture()
//   {
//
//      set_capture();
//
//   }
//
//
//   bool interaction_base::on_drag_start(::point_i32& point, ::item* pitem)
//   {
//
//      if (pitem->m_item.m_eelement == e_element_client)
//      {
//
//         auto pdrag = drag(pitem);
//
//         if (defer_perform_entire_reposition_process(pdrag->m_pmouse))
//         {
//
//            return false;
//
//         }
//
//         point = origin();
//
//         return true;
//
//      }
//
//      return false;
//
//   }
//
//
//   ::point_i32 interaction_base::drag_mouse_cursor_position(::item* pitem, const ::point_i32& point)
//   {
//
//      auto p = try_absolute_mouse_position(point);
//
//      return p;
//
//   }
//
//
//   bool interaction_base::drag_shift(::item* pitem, ::user::mouse* pmouse)
//   {
//
//      if (pitem->m_item.m_eelement == e_element_client)
//      {
//
//         auto point = drag_point(pitem, pmouse);
//
//         set_position(point);
//
//         return true;
//
//      }
//
//      return false;
//
//   }
//
//
//   bool interaction_base::drag_hover(::item* pitem)
//   {
//
//      if (pitem->m_item.m_eelement == e_element_client)
//      {
//
//         set_cursor(e_cursor_hand);
//
//         return true;
//
//      }
//      else if (pitem->m_item.m_eelement == e_element_resize)
//      {
//
//         set_cursor(e_cursor_size_bottom_right);
//
//         return true;
//
//      }
//
//      return false;
//
//   }
//
//
//   void interaction_base::drag_release_capture()
//   {
//
//      release_capture();
//
//   }
//
//
//   void interaction_base::drag_set_cursor(::item* pitem)
//   {
//
//      auto pdrag = drag(pitem);
//
//      set_cursor(pdrag->m_ecursor);
//
//   }
//
//
//   ::payload interaction_base::get_result()
//   {
//
//      return {};
//
//   }
//
//
//   void interaction_base::on_mouse_move(::user::mouse* pmouse)
//   {
//
//
//   }
//
//
//   void interaction_base::on_left_button_down(::user::mouse* pmouse)
//   {
//
//
//   }
//
//
//   void interaction_base::on_left_button_up(::user::mouse* pmouse)
//   {
//
//
//   }
//
//
//   void interaction_base::on_click(const ::payload& payload, ::user::mouse* pmouse)
//   {
//
//
//   }
//
//
//   void interaction_base::on_right_button_down(::user::mouse* pmouse)
//   {
//
//
//   }
//
//
//   void interaction_base::on_right_button_up(::user::mouse* pmouse)
//   {
//
//
//   }
//
//
//   void interaction_base::on_right_click(const ::payload& payload, ::user::mouse* pmouse)
//   {
//
//
//   }
//
//
//   void interaction_base::set_position(const ::point_i32& point)
//   {
//
//      m_pwindowbase->set_position(point);
//
//   }
//
//
//   void interaction_base::destroy()
//   {
//
//      ::user::element::destroy();
//      ::user::drag_client::destroy();
//      ::conversation::destroy();
//
//      system()->erase_signal_handler(this);
//
//   }
//
//
//   void interaction_base::create_interaction(::user::interaction* puserinteractionParent, const ::atom& atom)
//   {
//
//      if (!atom.is_empty())
//      {
//
//         m_atom = atom;
//
//      }
//
//      ::e_status estatus;
//
//      if (!puserinteractionParent)
//      {
//
//         create_host();
//
//      }
//      else
//      {
//
//         create_child(puserinteractionParent);
//
//      }
//
//   }
//
//
//   void interaction_base::create_control(::user::interaction* puserinteractionParent, const ::atom& atom)
//   {
//
//      m_atom = atom;
//
//      create_child(puserinteractionParent);
//
//   }
//
//
//   void interaction_base::on_position_window()
//   {
//
//
//   }
//
//
//   void interaction_base::on_size_window()
//   {
//
//
//   }
//
//
//   void interaction_base::redraw()
//   {
//
//
//   }
//
//
//   void interaction_base::get_client_rectangle(::rectangle_i32& rectangle)
//   {
//
//
//   }
//
//
//   rectangle_i32 interaction_base::get_window_rectangle()
//   {
//
//      return {};
//
//   }
//
//
//   void interaction_base::set_capture()
//   {
//
//      m_pwindowbase->set_capture();
//
//   }
//
//
//   bool interaction_base::has_capture()
//   {
//
//      return m_pwindowbase->has_capture();
//
//   }
//
//
//   void interaction_base::release_capture()
//   {
//
//
//   }
//
//
//   void interaction_base::set_cursor(enum_cursor ecursor)
//   {
//
//
//   }
//
//
//   void interaction_base::synchronize_composited_nano_window()
//   {
//
//
//   }
//
//
//   void interaction_base::_run_modal_loop()
//   {
//
//
//   }
//
//
//   bool interaction_base::is_popup_window() const
//   {
//
//      return false;
//
//   }
//
//
//   void interaction_base::handle(::topic* ptopic, ::context* pcontext)
//   {
//
//      if (ptopic->m_atom == id_operating_system_user_color_change)
//      {
//
//         update_drawing_objects();
//
//         redraw();
//
//      }
//      else if (ptopic->m_atom == id_set_application_dark_mode)
//      {
//
//         update_drawing_objects();
//
//         redraw();
//
//      }
//      else if (ptopic->m_atom == id_application_dark_mode_change)
//      {
//
//         update_drawing_objects();
//
//         redraw();
//
//      }
//
//   }
//
//
//   void interaction_base::do_asynchronously()
//   {
//
//      ::pointer<::nano::windowing::window> pwindowbase = m_pwindowbase;
//
//      auto procedure = [pwindowbase]()
//      {
//
//         pwindowbase->create_window();
//
//         pwindowbase->show_window();
//
//      };
//
//      if (is_main_thread())
//      {
//
//         procedure();
//
//      }
//      else
//      {
//
//         user_post(procedure);
//
//      }
//
//   }
//
//
//   ::payload interaction_base::do_synchronously(const class time& timeWait)
//   {
//
//      create();
//
//      show_window();
//
//      message_loop();
//
//      return m_payloadResult;
//
//   }
//
//
//   ::user::interaction_base* interaction_base::user_interaction_base()
//   {
//
//      return this;
//
//   }
//
//
//   ::nano::windowing::window* interaction_base::windowing_window_base()
//   {
//
//      return m_pwindowbase;
//
//   }
//
//
//   void interaction_base::get_text_selection(strsize& iBeg, strsize& iEnd) const
//   {
//
//
//   }
//
//
//   void interaction_base::get_text_selection(strsize& iBeg, strsize& iEnd, strsize& iComposingStart, strsize& iComposingEnd) const
//   {
//
//
//   }
//
//
//   ::collection::index interaction_base::plain_edit_sel_to_column(::draw2d::graphics_pointer& pgraphics, strsize iSel)
//   {
//
//      return -1;
//
//   }
//
//
//   ::collection::index interaction_base::plain_edit_sel_to_column_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32& x)
//   {
//
//      return -1;
//
//   }
//
//
//   ::collection::index interaction_base::plain_edit_sel_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel)
//   {
//
//      return -1;
//
//   }
//
//
//   ::collection::index interaction_base::plain_edit_sel_to_line_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32& x)
//   {
//
//      return -1;
//
//   }
//
//
//   strsize interaction_base::plain_edit_line_column_to_sel(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, ::collection::index iColumn)
//   {
//
//      return -1;
//
//   }
//
//
//   strsize interaction_base::plain_edit_line_x_to_sel(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, i32 x)
//   {
//
//      return -1;
//
//   }
//
//
//   ::collection::index interaction_base::plain_edit_char_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel)
//   {
//
//      return -1;
//
//   }
//
//
//   ::trace_statement& interaction_base::raw_trace_statement_prefix(::trace_statement& statement) const
//   {
//
//      ::string strType = ::type(this).name();
//
//      statement << strType;
//
//      ::string strAtom = m_atom.as_string();
//
//      if (strAtom.has_char() && strAtom != strType)
//      {
//         statement << "=" << strAtom;
//      }
//
//      statement << "  ";
//
//      return statement;
//
//   }
//
//
//
//
//} // user
//
//
//
