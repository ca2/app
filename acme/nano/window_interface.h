//
// Created by camilo on 31/01/2022 22:37 <3ThomasBorregaardSørensen!!
//
#pragma once


class CLASS_DECL_ACME nano_window_interface :
   virtual public ::object
{
public:


   void on_initialize_object() override;

   virtual void create();

   virtual void display_synchronously();

   virtual void message_loop();

   virtual void draw(nano_device * pnanodevice);

   virtual void on_draw(nano_device * pnanodevice);

   virtual void on_char(int iChar);

   virtual bool is_active();

   virtual void draw_children(nano_device * pnanodevice);

   virtual void delete_drawing_objects();
   virtual bool get_dark_mode();

   virtual void create_drawing_objects();
   virtual void update_drawing_objects();

   virtual ::id hit_test(int x, int y);
   virtual void add_child(nano_child * pchild);

   virtual ::id get_result();

   virtual void on_mouse_move(int x, int y);
   virtual void on_left_button_down(int x, int y);
   virtual void on_left_button_up(int x, int y);
   virtual void on_click(const ::id & id);

   //virtual LRESULT window_procedure(UINT message, WPARAM wparam, LPARAM lparam);

   virtual void move_to(int x, int y);

   virtual void destroy();

   virtual void redraw();

   virtual void get_client_rectangle(::rectangle_i32 & rectangle);
   virtual void get_window_rectangle(::rectangle_i32 & rectangle);

   virtual void set_capture();

   virtual void release_capture();

   virtual void set_cursor(enum_cursor ecursor);

   virtual void synchronize_composited_nano_window();


};



