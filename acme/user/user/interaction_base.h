//
// Created by camilo on 2024-09-26 18:50 Odense Time <3ThomasBorregaardSorensen!!
//
// nano::user::window_interface Created by camilo on 31/01/2022 22:37 <3ThomasBorregaardSorensen!!
// From nano::user::window_interface merged at ::user::interaction_base by
//    camilo on 2024-0926 15:01 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/prototype/geometry2d/shift.h"
#include "acme/user/user/element.h"
#include "drag_client.h"


namespace operating_system
{


    class a_system_menu_item;
    class a_system_menu;


} // namespace operating_system



namespace user
{


class CLASS_DECL_ACME interaction_base :
    virtual public ::user::element,
   virtual public ::user::drag_client,
   virtual public ::conversation_message,
   virtual public ::source,
   virtual public ::user::check,
   virtual public ::user::text
    {

public:

    bool                                      m_bMinimizeBox;
    bool                                      m_bMaximizeBox;
    bool                                      m_bResizeable;
    bool                                     m_bTopMost;


   ::pointer < ::windowing::window_base >    m_pwindowbase;


    interaction_base();
    ~interaction_base() override;


    virtual ::pointer < ::operating_system::a_system_menu > create_system_menu(bool bContextual = true);


   void handle(::topic * ptopic, ::context * pcontext) override;
   virtual void do_asynchronously();
   virtual ::payload do_synchronously(const class time & timeWait);



   ::user::interaction_base * user_interaction_base() override;





//
// //
// // Created by camilo on 31/01/2022 22:37 <3ThomasBorregaardSorensen!!
// //
// #pragma once
//
//
// //#include "acme/prototype/geometry2d/_geometry2d.h"
// ////#include "acme/prototype/prototype/object.h"
// ///
// #include "acme/prototype/geometry2d/shift.h"
// #include "acme/user/user/element.h"
// #include "user/user/interaction_base.h"
//
//
// namespace nano
// {
//
//
//    namespace user
//    {
//
//
// class CLASS_DECL_ACME window_interface :
//    virtual public ::user::interaction_base
// {
// public:


   void on_initialize_particle() override;

   virtual void create();

   virtual void show_window();

   virtual void message_loop();

   virtual void implementation_message_loop_step();

   virtual void draw(::nano::graphics::device * pnanodevice);

   virtual void on_draw(::nano::graphics::device * pnanodevice);

   virtual void on_char(int iChar);

   virtual bool is_active();
   virtual void set_active();

   virtual void draw_children(::nano::graphics::device * pnanodevice);

   virtual void delete_drawing_objects();
   virtual bool get_dark_mode();

   virtual void create_drawing_objects();
   virtual void update_drawing_objects();

   virtual ::point_i32 origin();

   //virtual bool defer_perform_entire_reposition_process();


   // virtual ::pointer < ::operating_system::a_system_menu > create_system_menu();
   //
   // //bool defer_perform_entire_reposition_process(::user::mouse * pmouse) override;
   //
   // //bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse) override;
   //
   // virtual bool defer_perform_entire_reposition_process(::user::mouse * pmouse);
   //
   // virtual bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse);


   virtual ::shift_i32 host_to_client();
   virtual ::shift_i32 client_to_host();

   virtual ::shift_i32 absolute_to_client();
   virtual ::shift_i32 client_to_absolute();

   virtual ::point_i32 try_absolute_mouse_position(const ::point_i32 & point);

      // drag_client
   void drag_set_capture() override;
   bool on_drag_start(::point_i32 & point, ::item * pitem) override;
   ::point_i32 drag_mouse_cursor_position(::item* pitem, const ::point_i32 & point) override;
   bool drag_shift(::item * pitem, ::user::mouse * pmouse) override;
   bool drag_hover(::item * pitem) override;
   void drag_release_capture() override;
   void drag_set_cursor(::item * pitem) override;


   // virtual ::nano::user::child * nano_user_hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder);
   // virtual ::nano::user::child * nano_user_on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder);
   // virtual void nano_user_add_child(::nano::user::child * pchild);

   virtual ::payload get_result();

   virtual void on_mouse_move(::user::mouse * pmouse);
   virtual void on_left_button_down(::user::mouse * pmouse);
   virtual void on_left_button_up(::user::mouse * pmouse);
   virtual void on_click(const ::payload & payload, ::user::mouse * pmouse);
   virtual void on_right_button_down(::user::mouse * pmouse);
   virtual void on_right_button_up(::user::mouse * pmouse);
   virtual void on_right_click(const ::payload & payload, ::user::mouse * pmouse);


   //virtual LRESULT window_procedure(UINT message, WPARAM wparam, LPARAM lparam);

   virtual void move_to(const ::point_i32 & point);

   void destroy() override;

   virtual void redraw();

   virtual void get_client_rectangle(::rectangle_i32 & rectangle);
   virtual ::rectangle_i32 get_window_rectangle() override;

   virtual void set_capture();

   virtual bool has_capture() const;

   virtual void release_capture();

   virtual void set_cursor(enum_cursor ecursor);

   virtual void synchronize_composited_nano_window();

   virtual void _run_modal_loop();

   virtual bool is_popup_window() const;


   // Text Edit
   void get_text_selection(strsize & iBeg, strsize & iEnd) const override;
   virtual void get_text_selection(strsize& iBeg, strsize& iEnd, strsize & iComposingStart, strsize & iComposingEnd) const;
   virtual ::collection::index plain_edit_sel_to_column(::draw2d::graphics_pointer& pgraphics, strsize iSel);
   virtual ::collection::index plain_edit_sel_to_column_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32 & x);
   virtual ::collection::index plain_edit_sel_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel);
   virtual ::collection::index plain_edit_sel_to_line_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32 & x);
   virtual strsize plain_edit_line_column_to_sel(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, ::collection::index iColumn);
   virtual strsize plain_edit_line_x_to_sel(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, i32 x);
   virtual ::collection::index plain_edit_char_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel);


   ::trace_statement & raw_trace_statement_prefix(::trace_statement & statement) const override;

   virtual void create_interaction(::user::interaction * puserinteractionParent, const ::atom & atom = nullptr);


   virtual void create_control(::user::interaction * puserinteractionParent, const ::atom & atom);

//
// };
//
//
//
//
//    } // namespace user
//
//
// } // namespace nano
//
//
//

};


} // user



