//
// Created by camilo on 31/01/2022 15:37 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"


void ns_screen_copy(CGRect & rect, const RECTANGLE_I32 & rectangle);

void ns_screen_copy(CGPoint & cgpoint, const POINT_I32 & point);

void ns_screen_copy(POINT_I32 & point, const CGPoint & cgpoint);


namespace macos
{


   nano_window::nano_window()
   {

   }


   nano_window::~nano_window()
   {

      delete_drawing_objects();

      m_pnanodevice.release();

   }


   void nano_window::on_initialize_object()
   {

      ::object::on_initialize_object();

   }


   void nano_window::on_char(int iChar)
   {

      m_pinterface->on_char(iChar);

   }


   void nano_window::_draw(nano_device * pnanodevice)
   {

      m_pinterface->draw(pnanodevice);

   }


   bool nano_window::is_active()
   {

      return m_pinterface->is_active();

   }


   void nano_window::delete_drawing_objects()
   {

      m_pinterface->delete_drawing_objects();

   }


   bool nano_window::get_dark_mode()
   {

      return m_psystem->node()->dark_mode();

   }


   void nano_window::create_drawing_objects()
   {

      m_pinterface->create_drawing_objects();

   }


   void nano_window::update_drawing_objects()
   {

      m_pinterface->update_drawing_objects();

   }


   void nano_window::create()
   {
      
      m_pwindowbridge = __new(nano_window_bridge);

      CGRect cgrect;
      
      ns_screen_copy(cgrect, m_pinterface->m_rectangle);
      
      m_pwindowbridge->m_pwindow = this;
      
      m_pwindowbridge->create_ns_nano_window(cgrect);
      
      create_drawing_objects();

      on_create();

   }


   void nano_window::on_left_button_down(::user::mouse * pmouse)
   {

      m_pinterface->on_left_button_down(pmouse);

   }


   void nano_window::on_left_button_up(::user::mouse * pmouse)
   {

      m_pinterface->on_left_button_up(pmouse);

   }


   void nano_window::on_right_button_down(::user::mouse * pmouse)
   {

      m_pinterface->on_right_button_down(pmouse);

   }


   void nano_window::on_right_button_up(::user::mouse * pmouse)
   {

      m_pinterface->on_right_button_up(pmouse);

   }


   void nano_window::on_mouse_move(::user::mouse * pmouse)
   {

      m_pinterface->on_mouse_move(pmouse);

   }


   ::atom nano_window::get_result()
   {

      return m_pinterface->get_result();

   }


   ::nano_child * nano_window::hit_test(::user::mouse * pmouse)
   {

      return m_pinterface->hit_test(pmouse);

   }


   void nano_window::display()
   {

      set_active();
      
      m_pwindowbridge->display();

   }


   void nano_window::set_active()
   {

   }


   void nano_window::_update_window()
   {

      if(!m_pwindowbridge)
      {
         
         return;
         
      }
      
      m_pwindowbridge->redraw();
      
   }


   bool nano_window::message_loop_step()
   {
     
      return false;

   }


   void nano_window::message_loop()
   {

      while(message_loop_step())
      {

      }

   }


   void nano_window::redraw()
   {

      _update_window();

   }


   void nano_window::destroy()
   {

      m_pwindowbridge->stop();

   }


   void nano_window::on_click(const ::atom & atom, ::user::mouse * pmouse)
   {

      m_pinterface->on_click(atom, pmouse);

   }


   void nano_window::on_right_click(const ::atom & atom, ::user::mouse * pmouse)
   {

      m_pinterface->on_right_click(atom, pmouse);

   }


   void nano_window::move_to(const ::point_i32 & point)
   {

      m_pwindowbridge->move_to(point.x, point.y);
      
   }


   void nano_window::set_capture()
   {

   }


   void nano_window::release_capture()
   {

   }


   void nano_window::get_client_rectangle(::rectangle_i32 & rectangle)
   {

   }


   void nano_window::get_window_rectangle(::rectangle_i32 & rectangle)
   {

   }


   void nano_window::_run_modal_loop()
   {
      
      m_pwindowbridge->_run_modal_loop();
      
   }


} // namespace macos


void nano_window_bridge::on_left_button_up(int x, int y)
{
   
   auto pmouse = m_pwindow->__create_new <::user::mouse>();
   
   pmouse->m_point = {x, y};
   
   m_pwindow->on_left_button_up(pmouse);
   
}


void nano_window_bridge::on_left_button_down(int x, int y)
{
   
   auto pmouse = m_pwindow->__create_new <::user::mouse>();
   
   pmouse->m_point = {x, y};

   m_pwindow->on_left_button_down(pmouse);
   
}


void nano_window_bridge::on_right_button_up(int x, int y)
{
   
   auto pmouse = m_pwindow->__create_new <::user::mouse>();
   
   pmouse->m_point = {x, y};

   m_pwindow->on_right_button_up(pmouse);
   
}


void nano_window_bridge::on_right_button_down(int x, int y)
{
   
   auto pmouse = m_pwindow->__create_new <::user::mouse>();
   
   pmouse->m_point = {x, y};

   m_pwindow->on_right_button_down(pmouse);
   
}


void nano_window_bridge::on_mouse_move(int x, int y)
{
   
   auto pmouse = m_pwindow->__create_new <::user::mouse>();
   
   pmouse->m_point = {x, y};

   m_pwindow->on_mouse_move(pmouse);
   
}


void nano_window_bridge::on_char(int iChar)
{
   
   m_pwindow->on_char(iChar);
   
}


void nano_window_bridge::_on_draw_frame(CGContextRef cg, CGSize sizeFrame)
{
   
   __pointer(quartz2d::nano_device) pnanodevice = __new(quartz2d::nano_device(cg));
   
   m_pwindow->_draw(pnanodevice);
   
}



void nano_window_bridge::on_layout(int x, int y, int w, int h)
{
   
   m_pwindow->m_pinterface->m_rectangle.left = x;
   
   m_pwindow->m_pinterface->m_rectangle.top = y;
   
   m_pwindow->m_pinterface->m_rectangle.right = x + w;
   
   m_pwindow->m_pinterface->m_rectangle.bottom = y + h;
   
}


