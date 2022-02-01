//
// Created by camilo on 31/01/2022 16:16 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"


nano_window::nano_window()
{


}


nano_window::~nano_window()
{


}


void nano_window::draw(nano_device * pnanodevice)
{

   get_client_rectangle(m_rectangleClient);

   __pointer(::nano_pen) pnanopenBorder;

   if (is_active())
   {

      pnanopenBorder = m_ppenBorderFocus;

   }
   else
   {

      pnanopenBorder = m_ppenBorder;

   }

   pnanodevice->rectangle(m_rectangleClient, m_pbrushWindow, m_ppenBorder);

   on_draw(pnanodevice);

   draw_children(pnanodevice);

}


void nano_window::draw_children(nano_device * pnanodevice)
{

   for (auto & pchild: m_childa)
   {

      pchild->on_draw(pnanodevice);

   }

}


void nano_window::create()
{

   __construct(m_pnanowindowImpl);

   m_pnanowindowImpl->create();

}


void nano_window::display_synchronously()
{

   m_pnanowindowImpl->display_synchronously();

}


void nano_window::message_loop()
{

   m_pnanowindowImpl->display_synchronously();

}



void nano_window::on_draw(nano_device * pnanodevice)
{

   m_pnanowindowImpl->draw(pnanodevice);

}


void nano_window::on_char(int iChar)
{

   m_pnanowindowImpl->on_char(iChar);

}


bool nano_window::is_active()
{

   return m_pnanowindowImpl->is_active();

}


void nano_window::delete_drawing_objects()
{

   m_pnanowindowImpl->delete_drawing_objects();

}


bool nano_window::get_dark_mode()
{

   return m_pnanowindowImpl->get_dark_mode();

}


void nano_window::create_drawing_objects()
{

   m_pnanowindowImpl->create_drawing_objects();

}


void nano_window::update_drawing_objects()
{

   m_pnanowindowImpl->update_drawing_objects();

}


::id nano_window::hit_test(int x, int y)
{

   return m_pnanowindowImpl->hit_test(x, y);

}


void nano_window::add_child(nano_child * pchild)
{

   m_pnanowindowImpl->add_child(pchild);

}


::id nano_window::get_result()
{

   return m_pnanowindowImpl->get_result();

}


void nano_window::on_mouse_move(int x, int y)
{

   m_pnanowindowImpl->on_mouse_move(x, y);

}


void nano_window::on_left_button_down(int x, int y)
{

   m_pnanowindowImpl->on_left_button_down(x, y);

}


void nano_window::on_left_button_up(int x, int y)
{

   m_pnanowindowImpl->on_left_button_up(x, y);

}


void nano_window::on_click(const ::id & id)
{

   m_pnanowindowImpl->on_click(id);

}


void nano_window::move_to(int x, int y)
{

   m_pnanowindowImpl->move_to(x, y);

}


void nano_window::destroy()
{

   m_pnanowindowImpl->destroy();

}


void nano_window::redraw()
{

   m_pnanowindowImpl->redraw();

}


void nano_window::get_client_rectangle(::rectangle_i32 & rectangle)
{

   m_pnanowindowImpl->get_client_rectangle(rectangle);

}


void nano_window::set_capture()
{

   m_pnanowindowImpl->set_capture();

}
