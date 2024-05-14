//
// Created by camilo on 31/01/2022 22:42 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window_interface.h"
#include "acme/platform/system.h"
#include "acme/primitive/geometry2d/rectangle.h"
#include "acme/user/user/drag.h"
#include "acme/user/user/mouse.h"



namespace nano
{

namespace user
{


void window_interface::on_initialize_particle()
{


}


void window_interface::create()
{


}


void window_interface::display()
{


}


void window_interface::message_loop()
{


}


void window_interface::implementation_message_loop_step()
{


}


void window_interface::draw(device * pnanodevice)
{

}


void window_interface::on_draw(device * pnanodevice)
{


}


void window_interface::on_char(int iChar)
{


}


bool window_interface::is_active()
{

   return false;

}


void window_interface::set_active()
{

}


void window_interface::draw_children(device * pnanodevice)
{


}

void window_interface::delete_drawing_objects()
{


}


bool window_interface::get_dark_mode()
{

   return false;

}


void window_interface::create_drawing_objects()
{

}


void window_interface::update_drawing_objects()
{


}


::point_i32 window_interface::origin()
{

   throw ::exception(error_wrong_state);

   return {};

}


bool window_interface::defer_perform_entire_reposition_process()
{

   return false;

}


::shift_i32 window_interface::host_to_client()
{

   return - client_to_host();

}


::shift_i32 window_interface::client_to_host()
{

   return {};

}


::shift_i32 window_interface::absolute_to_client()
{

   return - client_to_host();

}


::shift_i32 window_interface::client_to_absolute()
{

   if(system()->m_ewindowing == e_windowing_wayland)
   {

      return {};

   }

   ::rectangle_i32 r;

   get_window_rectangle(r);

   return r.top_left();

}


::point_i32 window_interface::try_absolute_mouse_position(const ::point_i32& point)
{

   auto p = point;

   client_to_absolute()(p);
   
   return p;

}


void window_interface::drag_set_capture()
{

   set_capture();

}


bool window_interface::on_drag_start(::point_i32 & point, ::item * pitem)
{

   if (pitem->m_item.m_eelement == e_element_client)
   {

      if(defer_perform_entire_reposition_process())
      {

         return false;

      }

      point = origin();

      return true;

   }

   return false;

}


::point_i32 window_interface::drag_mouse_cursor_position(::item* pitem, const ::point_i32 & point)
{

   auto p = try_absolute_mouse_position(point);

   return p;

}



bool window_interface::drag_shift(::item * pitem, ::user::mouse * pmouse)
{

   if (pitem->m_item.m_eelement == e_element_client)
   {

      auto point = drag_point(pitem, pmouse);

      move_to(point);

      return true;

   }

   return false;

}


bool window_interface::drag_hover(::item * pitem)
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


void window_interface::drag_release_capture()
{

   release_capture();

}


void window_interface::drag_set_cursor(::item * pitem)
{

   auto pdrag = drag(pitem);

   set_cursor(pdrag->m_ecursor);

}


child * window_interface::hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder)
{

   auto point = pmouse->m_pointHost;

   host_to_client()(point);

   return on_hit_test(point, ezorder);

}


child * window_interface::on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
{

   return nullptr;

}


void window_interface::add_child(child * pchild)
{


}


::atom window_interface::get_result()
{

   return {};

}


void window_interface::on_mouse_move(::user::mouse * pmouse)
{


}


void window_interface::on_left_button_down(::user::mouse * pmouse)
{

}


void window_interface::on_left_button_up(::user::mouse * pmouse)
{


}


void window_interface::on_click(const ::atom & atom, ::user::mouse * pmouse)
{


}


void window_interface::on_right_button_down(::user::mouse * pmouse)
{


}


void window_interface::on_right_button_up(::user::mouse * pmouse)
{


}


void window_interface::on_right_click(const ::atom & atom, ::user::mouse * pmouse)
{

}


void window_interface::move_to(const ::point_i32 & point)
{


}


void window_interface::destroy()
{


}


void window_interface::redraw()
{


}


void window_interface::get_client_rectangle(::rectangle_i32 & rectangle)
{


}


void window_interface::get_window_rectangle(::rectangle_i32 & rectangle)
{


}


void window_interface::set_capture()
{


}


bool window_interface::has_capture() const
{

   return false;

}


void window_interface::release_capture()
{


}


void window_interface::set_cursor(enum_cursor ecursor)
{


}


void window_interface::synchronize_composited_nano_window()
{


}


void window_interface::_run_modal_loop()
{
   
   
}


bool window_interface::is_popup_window() const
{
   
   return false;
   
}


   } // namespace user


} // namespace nano


