//
// Created by camilo on 31/01/2022 22:42 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "window_interface.h"
#include "acme/primitive/geometry2d/_geometry2d.h"
#include "acme/user/user/mouse.h"


void nano_window_interface::on_initialize_particle()
{


}


void nano_window_interface::create()
{


}


void nano_window_interface::display()
{


}


void nano_window_interface::message_loop()
{


}


void nano_window_interface::draw(nano_device * pnanodevice)
{

}


void nano_window_interface::on_draw(nano_device * pnanodevice)
{


}


void nano_window_interface::on_char(int iChar)
{


}


bool nano_window_interface::is_active()
{

   return false;

}


void nano_window_interface::set_active()
{

}


void nano_window_interface::draw_children(nano_device * pnanodevice)
{


}

void nano_window_interface::delete_drawing_objects()
{


}


bool nano_window_interface::get_dark_mode()
{

   return false;

}


void nano_window_interface::create_drawing_objects()
{

}


void nano_window_interface::update_drawing_objects()
{


}


::shift_i32 nano_window_interface::screen_to_client()
{

   ::rectangle_i32 r;

   get_window_rectangle(r);

   return  - r.top_left();

}


::shift_i32 nano_window_interface::client_to_screen()
{

   ::rectangle_i32 r;

   get_window_rectangle(r);

   return r.top_left();

}


nano_child * nano_window_interface::hit_test(::user::mouse * pmouse)
{

   auto point = pmouse->m_point;

   screen_to_client()(point);

   return on_hit_test(point);

}


nano_child * nano_window_interface::on_hit_test(const ::point_i32 & point)
{

   return nullptr;

}


void nano_window_interface::add_child(nano_child * pchild)
{


}


::atom nano_window_interface::get_result()
{

   return {};

}


void nano_window_interface::on_mouse_move(::user::mouse * pmouse)
{


}


void nano_window_interface::on_left_button_down(::user::mouse * pmouse)
{

}


void nano_window_interface::on_left_button_up(::user::mouse * pmouse)
{


}


void nano_window_interface::on_click(const ::atom & atom, ::user::mouse * pmouse)
{


}


void nano_window_interface::on_right_button_down(::user::mouse * pmouse)
{


}


void nano_window_interface::on_right_button_up(::user::mouse * pmouse)
{


}


void nano_window_interface::on_right_click(const ::atom & atom, ::user::mouse * pmouse)
{

}


void nano_window_interface::move_to(const ::point_i32 & point)
{


}


void nano_window_interface::destroy()
{


}


void nano_window_interface::redraw()
{


}


void nano_window_interface::get_client_rectangle(::rectangle_i32 & rectangle)
{


}


void nano_window_interface::get_window_rectangle(::rectangle_i32 & rectangle)
{


}


void nano_window_interface::set_capture()
{


}


bool nano_window_interface::has_capture() const
{

   return false;

}


void nano_window_interface::release_capture()
{


}


void nano_window_interface::set_cursor(enum_cursor ecursor)
{


}


void nano_window_interface::synchronize_composited_nano_window()
{


}


void nano_window_interface::_run_modal_loop()
{
   
   
}


bool nano_window_interface::is_popup_window() const
{
   
   return false;
   
}
