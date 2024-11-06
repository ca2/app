//
// Created by camilo on 31/01/2022 22:37 <3ThomasBorregaardSorensen!!
//
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
//    virtual public ::acme::user::interaction
// {
// public:
//
//
//    void on_initialize_particle() override;
//
//    virtual void create();
//
//    virtual void show_window();
//
//    virtual void message_loop();
//
//    virtual void implementation_message_loop_step();
//
//    virtual void draw(::nano::graphics::device * pnanodevice);
//
//    virtual void on_draw(::nano::graphics::device * pnanodevice);
//
//    virtual void on_char(int iChar);
//
//    virtual bool is_active();
//    virtual void set_active();
//
//    virtual void draw_children(::nano::graphics::device * pnanodevice);
//
//    virtual void delete_drawing_objects();
//    virtual bool get_dark_mode();
//
//    virtual void create_drawing_objects();
//    virtual void update_drawing_objects();
//
//    virtual ::int_point origin();
//
//    //virtual bool defer_perform_entire_reposition_process();
//
//
//    // virtual ::pointer < ::operating_system::a_system_menu > create_system_menu();
//    //
//    // //bool defer_perform_entire_reposition_process(::user::mouse * pmouse) override;
//    //
//    // //bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse) override;
//    //
//    // virtual bool defer_perform_entire_reposition_process(::user::mouse * pmouse);
//    //
//    // virtual bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse);
//
//
//    virtual ::shift_int host_to_client();
//    virtual ::shift_int client_to_host();
//
//    virtual ::shift_int absolute_to_client();
//    virtual ::shift_int client_to_absolute();
//
//    virtual ::int_point try_absolute_mouse_position(const ::int_point & point);
//
//       // drag_client
//    void drag_set_capture() override;
//    bool on_drag_start(::int_point & point, ::item * pitem) override;
//    ::int_point drag_mouse_cursor_position(::item* pitem, const ::int_point & point) override;
//    bool drag_shift(::item * pitem, ::user::mouse * pmouse) override;
//    bool drag_hover(::item * pitem) override;
//    void drag_release_capture() override;
//    void drag_set_cursor(::item * pitem) override;
//
//
//    virtual ::micro::child * hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder);
//    virtual ::micro::child * on_hit_test(const ::int_point & point, ::user::e_zorder ezorder);
//    virtual void add_child(::micro::child * pchild);
//
//    virtual ::payload get_result();
//
//    virtual void on_mouse_move(::user::mouse * pmouse);
//    virtual void on_left_button_down(::user::mouse * pmouse);
//    virtual void on_left_button_up(::user::mouse * pmouse);
//    virtual void on_click(const ::payload & payload, ::user::mouse * pmouse);
//    virtual void on_right_button_down(::user::mouse * pmouse);
//    virtual void on_right_button_up(::user::mouse * pmouse);
//    virtual void on_right_click(const ::payload & payload, ::user::mouse * pmouse);
//
//
//    //virtual LRESULT window_procedure(UINT message, WPARAM wparam, LPARAM lparam);
//
//    virtual void move_to(const ::int_point & point);
//
//    void destroy() override;
//
//    virtual void redraw();
//
//    virtual void get_client_rectangle(::int_rectangle & rectangle);
//    virtual void get_window_rectangle(::int_rectangle & rectangle);
//
//    virtual void set_capture();
//
//    virtual bool has_capture() const;
//
//    virtual void release_capture();
//
//    virtual void set_cursor(enum_cursor ecursor);
//
//    virtual void synchronize_composited_nano_window();
//
//    virtual void _run_modal_loop();
//
//    virtual bool is_popup_window() const;
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
