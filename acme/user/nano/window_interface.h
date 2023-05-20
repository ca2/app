//
// Created by camilo on 31/01/2022 22:37 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "acme/primitive/geometry2d/_geometry2d.h"
////#include "acme/primitive/primitive/object.h"


class CLASS_DECL_ACME nano_window_interface :
   virtual public ::object
{
public:


   void on_initialize_particle() override;

   virtual void create();

   virtual void display();

   virtual void message_loop();

   virtual void draw(nano_device * pnanodevice);

   virtual void on_draw(nano_device * pnanodevice);

   virtual void on_char(int iChar);

   virtual bool is_active();
   virtual void set_active();

   virtual void draw_children(nano_device * pnanodevice);

   virtual void delete_drawing_objects();
   virtual bool get_dark_mode();

   virtual void create_drawing_objects();
   virtual void update_drawing_objects();

   virtual ::shift_i32 screen_to_client();
   virtual ::shift_i32 client_to_screen();

   virtual ::nano_child * hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder);
   virtual ::nano_child * on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder);
   virtual void add_child(nano_child * pchild);

   virtual ::atom get_result();

   virtual void on_mouse_move(::user::mouse * pmouse);
   virtual void on_left_button_down(::user::mouse * pmouse);
   virtual void on_left_button_up(::user::mouse * pmouse);
   virtual void on_click(const ::atom & atom, ::user::mouse * pmouse);
   virtual void on_right_button_down(::user::mouse * pmouse);
   virtual void on_right_button_up(::user::mouse * pmouse);
   virtual void on_right_click(const ::atom & atom, ::user::mouse * pmouse);


   //virtual LRESULT window_procedure(UINT message, WPARAM wparam, LPARAM lparam);

   virtual void move_to(const ::point_i32 & point);

   void destroy() override;

   virtual void redraw();

   virtual void get_client_rectangle(::rectangle_i32 & rectangle);
   virtual void get_window_rectangle(::rectangle_i32 & rectangle);

   virtual void set_capture();

   virtual bool has_capture() const;

   virtual void release_capture();

   virtual void set_cursor(enum_cursor ecursor);

   virtual void synchronize_composited_nano_window();

   virtual void _run_modal_loop();

   virtual bool is_popup_window() const;

};



