////
//// Created by camilo on 2024-09-26 18:50 Odense Time <3ThomasBorregaardSorensen!!
////
//// micro::window_interface Created by camilo on 31/01/2022 22:37 <3ThomasBorregaardSorensen!!
//// From micro::window_interface merged at ::acme::user::interaction by
////    camilo on 2024-0926 15:01 <3ThomasBorregaardSorensen!!
////
//#pragma once
//
//
//#include "acme/prototype/geometry2d/shift.h"
//#include "acme/user/user/element.h"
//#include "drag_client.h"
//
//
//namespace operating_system
//{
//
//
//    class a_system_menu_item;
//    class a_system_menu;
//
//
//} // namespace operating_system
//
//
//
//namespace user
//{
//
//
//class CLASS_DECL_ACME interaction_base :
//    virtual public ::user::element,
//   virtual public ::user::drag_client,
//   virtual public ::conversation_message,
//   virtual public ::source,
//   virtual public ::user::check,
//   virtual public ::user::text
//    {
//
//public:
//
//    bool                                        m_bMinimizeBox;
//    bool                                        m_bMaximizeBox;
//    bool                                        m_bResizeable;
//    bool                                        m_bTopMost;
//    bool                                        m_bStartCentered;
//    bool                                        m_bArbitraryPositioning;
//
//
//   ::pointer < ::acme::windowing::window >      m_pnanowindowingwindow;
//   ::pointer < ::acme::user::interaction >      m_pacmeuserinteractionParent;
//
//
//    interaction_base();
//    ~interaction_base() override;
//
//
//    virtual ::pointer < ::operating_system::a_system_menu > create_system_menu(bool bContextual = true);
//
//
//   void handle(::topic * ptopic, ::handler_context * pcontext) override;
//
//
//   //virtual void do_interchange();
//   void do_asynchronously() override;
//   ::payload do_synchronously(const class time & timeWait) override;
//
//
//
//   ::acme::user::interaction * acme_user_interaction() override;
//   ::acme::windowing::window * acme_windowing_window() override;
//
//
//
////
//// //
//// // Created by camilo on 31/01/2022 22:37 <3ThomasBorregaardSorensen!!
//// //
//// #pragma once
////
////
//// //#include "acme/prototype/geometry2d/_geometry2d.h"
//// ////#include "acme/prototype/prototype/object.h"
//// ///
//// #include "acme/prototype/geometry2d/shift.h"
//// #include "acme/user/user/element.h"
//// #include "user/user/interaction_base.h"
////
////
//// namespace nano
//// {
////
////
////    namespace user
////    {
////
////
//// class CLASS_DECL_ACME window_interface :
////    virtual public ::acme::user::interaction
//// {
//// public:
//
//
//   void on_initialize_particle() override;
//
//   virtual void create();
//
//   virtual void show_window();
//
//   virtual void hide_window();
//
//   virtual void message_loop();
//
//   virtual void implementation_message_loop_step();
//
//   virtual void draw(::nano::graphics::device * pnanodevice);
//
//   virtual void on_draw(::nano::graphics::device * pnanodevice);
//
//   virtual void on_char(int iChar);
//
//   virtual bool is_active();
//   virtual void set_active();
//
//   virtual void draw_children(::nano::graphics::device * pnanodevice);
//
//   virtual void delete_drawing_objects();
//   virtual bool get_dark_mode();
//
//   virtual void create_drawing_objects();
//   virtual void update_drawing_objects();
//
//   virtual ::int_point origin();
//
//   //virtual bool defer_perform_entire_reposition_process();
//
//
//   // virtual ::pointer < ::operating_system::a_system_menu > create_system_menu();
//   //
//   // //bool defer_perform_entire_reposition_process(::user::mouse * pmouse) override;
//   //
//   // //bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse) override;
//   //
//   // virtual bool defer_perform_entire_reposition_process(::user::mouse * pmouse);
//   //
//   // virtual bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse);
//
//
//   virtual ::shift_int host_to_client();
//   virtual ::shift_int client_to_host();
//
//   virtual ::shift_int absolute_to_client();
//   virtual ::shift_int client_to_absolute();
//
//   virtual ::int_point try_absolute_mouse_position(const ::int_point & point);
//
//      // drag_client
//   void drag_set_capture() override;
//   bool on_drag_start(::int_point & point, ::item * pitem) override;
//   ::int_point drag_mouse_cursor_position(::item* pitem, const ::int_point & point) override;
//   bool drag_shift(::item * pitem, ::user::mouse * pmouse) override;
//   bool drag_hover(::item * pitem) override;
//   void drag_release_capture() override;
//   void drag_set_cursor(::item * pitem) override;
//
//
//   // virtual ::micro::child * nano_user_hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder);
//   // virtual ::micro::child * nano_user_on_hit_test(const ::int_point & point, ::user::e_zorder ezorder);
//   // virtual void nano_user_add_child(::micro::child * pchild);
//
//   virtual ::payload get_result();
//
//   virtual void on_mouse_move(::user::mouse * pmouse);
//   virtual void on_left_button_down(::user::mouse * pmouse);
//   virtual void on_left_button_up(::user::mouse * pmouse);
//   virtual void on_click(const ::payload & payload, ::user::mouse * pmouse);
//   virtual void on_right_button_down(::user::mouse * pmouse);
//   virtual void on_right_button_up(::user::mouse * pmouse);
//   virtual void on_right_click(const ::payload & payload, ::user::mouse * pmouse);
//
//
//   //virtual LRESULT window_procedure(UINT message, WPARAM wparam, LPARAM lparam);
//
//   void set_position(const ::int_point & point) override;
//
//   void destroy() override;
//
//   void redraw() override;
//
//   virtual void get_client_rectangle(::int_rectangle & rectangle);
//   ::int_rectangle get_window_rectangle() override;
//
//   void set_capture() override;
//
//   bool has_capture() override;
//
//   void release_capture() override;
//
//   void set_cursor(enum_cursor ecursor) override;
//
//   virtual void synchronize_composited_nano_window();
//
//   void _run_modal_loop() override;
//
//   virtual bool is_popup_window() const;
//
//
//   // Text Edit
//   void get_text_selection(character_count & iBeg, character_count & iEnd) const override;
//   virtual void get_text_selection(character_count& iBeg, character_count& iEnd, character_count & iComposingStart, character_count & iComposingEnd) const;
//   virtual ::collection::index plain_edit_sel_to_column(::draw2d::graphics_pointer& pgraphics, character_count iSel);
//   virtual ::collection::index plain_edit_sel_to_column_x(::draw2d::graphics_pointer& pgraphics, character_count iSel, int & x);
//   virtual ::collection::index plain_edit_sel_to_line(::draw2d::graphics_pointer& pgraphics, character_count iSel);
//   virtual ::collection::index plain_edit_sel_to_line_x(::draw2d::graphics_pointer& pgraphics, character_count iSel, int & x);
//   virtual character_count plain_edit_line_column_to_sel(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, ::collection::index iColumn);
//   virtual character_count plain_edit_line_x_to_sel(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, int x);
//   virtual ::collection::index plain_edit_char_to_line(::draw2d::graphics_pointer& pgraphics, character_count iSel);
//
//
//   ::trace_statement & raw_trace_statement_prefix(::trace_statement & statement) const override;
//
//   virtual void create_interaction(::user::interaction * puserinteractionParent, const ::atom & atom = nullptr);
//
//
//   virtual void create_control(::user::interaction * puserinteractionParent, const ::atom & atom);
//
//
//   virtual void on_position_window();
//   virtual void on_size_window();
//
//   bool is_window_zoomed() override;
//   void window_minimize() override;
//   void window_maximize() override; // m_pwindow->m_puserinteraction->display(::e_display_zoomed);
//   void window_full_screen() override; // m_pwindow->m_puserinteraction->display(::e_display_full_screen);
//   void window_restore() override; // m_pwindow->m_puserinteraction->display(::e_display_normal);
//   void window_close() override;
//
//   void set_mouse_capture() override;
//   bool is_mouse_captured() override;
//   bool has_mouse_capture() override;
//   void release_mouse_capture() override;
//
//
//   void _on_window_simple_action(const char * pszActionName) override;
//
//
////
//// };
////
////
////
////
////    } // namespace user
////
////
//// } // namespace nano
////
////
////
//
//};
//
//
//} // user
//
//
//
