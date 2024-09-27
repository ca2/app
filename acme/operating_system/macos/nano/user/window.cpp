//
// Created by camilo on 31/01/2022 15:37 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window.h"
#include "window_bridge.h"
#include "device.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/platform/sequencer.h"
#include "acme/platform/node.h"
#include "acme/nano/user/window.h"
#include "acme/user/user/mouse.h"
#include <CoreGraphics/CoreGraphics.h>

void apple_defer_nano_application_create(::acme::system * psystem);

void ns_main_async(dispatch_block_t block);

bool ns_app_is_running();

void ns_app_run();

void ns_app_stop();

CLASS_DECL_ACME void ns_get_main_screen_size(int & cx, int & cy);

void screen_coordinates_aware_copy(CGRect & rect, const ::rectangle_i32 &rectangle);

void screen_coordinates_aware_copy(CGPoint & cgpoint, const ::point_i32 & point);

void screen_coordinates_aware_copy(::point_i32 & point, const CGPoint & cgpoint);

//void macos_defer_initialize_nano_callbacks();
namespace macos
{


   namespace nano
   {


      namespace user
      {




   window::window()
   {
      
      //macos_defer_initialize_nano_callbacks();

   }


   window::~window()
   {

      delete_drawing_objects();

      m_pnanodevice.release();

   }


#ifdef _DEBUG


i64 window::increment_reference_count()
{

return ::property_object::increment_reference_count();

}


i64 window::decrement_reference_count()
{

return ::property_object::decrement_reference_count();

}


i64 window::release()
{

return ::property_object::release();

}


#endif

   void window::on_initialize_particle()
   {

      ::object::on_initialize_particle();

   }


   void window::on_char(int iChar)
   {

      m_pinterface->on_char(iChar);

   }


   void window::_draw(::nano::graphics::device * pnanodevice)
   {

      m_pinterface->draw(pnanodevice);

   }


   bool window::is_active()
   {

      return m_pinterface->is_active();

   }


   void window::delete_drawing_objects()
   {

      m_pinterface->delete_drawing_objects();

   }


   bool window::get_dark_mode()
   {

      return system()->dark_mode();

   }


   void window::create_drawing_objects()
   {

      m_pinterface->create_drawing_objects();

   }


   void window::update_drawing_objects()
   {

      m_pinterface->update_drawing_objects();

   }


   void window::create()
   {
      
      apple_defer_nano_application_create(system());
      
      m_pwindowbridge = ::place(new nano_window_bridge());

      CGRect cgrect;
      
      screen_coordinates_aware_copy(cgrect, m_pinterface->m_rectangle);
      
      m_pwindowbridge->m_pwindow = this;
      
      m_pwindowbridge->create_ns_nano_window(cgrect);
      
      nano_window_on_create();
      
      //create_drawing_objects();

      ///on_create();

   }

void window::handle(::topic* ptopic, ::context* pcontext)
{
   
   if (ptopic->m_atom == id_set_application_dark_mode)
   {
      
      update_drawing_objects();
      //m_pimplementation->handle(ptopic, pcontext);
      redraw();
      
   }
   
}


   void window::on_left_button_down(::user::mouse * pmouse)
   {

      m_pinterface->on_left_button_down(pmouse);

   }


   void window::on_left_button_up(::user::mouse * pmouse)
   {

      m_pinterface->on_left_button_up(pmouse);

   }


   void window::on_right_button_down(::user::mouse * pmouse)
   {

      m_pinterface->on_right_button_down(pmouse);

   }


   void window::on_right_button_up(::user::mouse * pmouse)
   {

      m_pinterface->on_right_button_up(pmouse);

   }


   void window::on_mouse_move(::user::mouse * pmouse)
   {

      m_pinterface->on_mouse_move(pmouse);

   }


   ::payload window::get_result()
   {

      return m_pinterface->get_result();

   }


   ::nano::user::child * window::hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder)
   {

      return m_pinterface->hit_test(pmouse, ezorder);

   }


   void window::display()
   {

      set_active();
      
      m_pwindowbridge->display();

   }


   void window::hide()
   {

      m_pwindowbridge->hide();

   }


   void window::set_active()
   {

   }


   void window::_update_window()
   {

      if(!m_pwindowbridge)
      {
         
         return;
         
      }
      
      m_pwindowbridge->redraw();
      
   }


   bool window::message_loop_step()
   {
     
      return false;

   }


   void window::message_loop()
   {

 ///     while(aaa_message_loop_step())
    //  {

      //}
      
      ns_main_async(^()
                    {
         
         m_pwindowbridge->_run_modal_loop();
         
      });
      

   }


   void window::redraw()
   {

      _update_window();

   }


   void window::destroy()
   {

      m_pwindowbridge->stop();
      
      nano_window_on_destroy();

   }


   void window::on_click(const ::payload & payload, ::user::mouse * pmouse)
   {

      m_pinterface->on_click(payload, pmouse);

   }


   void window::on_right_click(const ::payload & payload, ::user::mouse * pmouse)
   {

      m_pinterface->on_right_click(payload, pmouse);

   }


   void window::move_to(const ::point_i32 & point)
   {

      m_pwindowbridge->move_to(point.x(), point.y());
      
   }


   void window::set_capture()
   {

   }


   void window::release_capture()
   {

   }


   void window::get_client_rectangle(::rectangle_i32 & rectangle)
   {

   }


   void window::get_window_rectangle(::rectangle_i32 & rectangle)
   {

   }


   void window::_run_modal_loop()
   {
      
      m_pwindowbridge->_run_modal_loop();
      
   }


   ::size_i32 window::get_main_screen_size()
   {
      
      ::i32 cx = 800;
      
      ::i32 cy = 600;
      
      ns_get_main_screen_size(cx, cy);
      
      return { cx, cy };
      
   }


   ::payload window::do_synchronously()
   {
      
      if(ns_app_is_running())
      {
         
         return ::nano::user::window_implementation::do_synchronously();
         
      }

      atom atomResult;

      m_pinterface->m_psequencer->then([ &atomResult ](auto psequence)
      {

         atomResult = psequence->m_payloadResult;
         
         ns_app_stop();

      });

      ns_app_run();

      //   auto pmessagebox = pparticle->__create_new < ::nano::user::message_box >();
      //
      //   atom idResult;
      //
      //   manual_reset_event event;
      //
      //   pmessagebox->display(pszMessage, pszTitle, emessagebox, pszDetails);
      //
      //   pmessagebox->m_functionClose = [&idResult, &event](window * pwindow)
      //   {
      //
      //      idResult = pwindow->m_atomResult;
      //
      //      event.SetEvent();
      //
      //   };
      //
      //   if(is_single_main_user_thread() && is_main_thread())
      //   {
      //
      //      pmessagebox->_run_modal_loop();
      //
      //   }
      //   else
      //   {
      //      event.wait();
      //
      //   }
      //
      //   //auto idResult = pmessagebox->get_result();
      //
      //   return idResult;

      return atomResult;

   }


      } //namespace user


   } //namespace nano


} // namespace macos





void nano_window_bridge::on_left_button_up(int xHost, int yHost, int xAbsolute, int yAbsolute)
{
   
   auto pmouse = m_pwindow->__create_new <::user::mouse>();
   
   pmouse->m_pointHost = {xHost, yHost};
   
   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};
   
   m_pwindow->on_left_button_up(pmouse);
   
}


void nano_window_bridge::on_left_button_down(int xHost, int yHost, int xAbsolute, int yAbsolute)
{
   
   auto pmouse = m_pwindow->__create_new <::user::mouse>();
   
   pmouse->m_pointHost = {xHost, yHost};
   
   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};

   m_pwindow->on_left_button_down(pmouse);
   
}


void nano_window_bridge::on_right_button_up(int xHost, int yHost, int xAbsolute, int yAbsolute)
{
   
   auto pmouse = m_pwindow->__create_new <::user::mouse>();
   
   pmouse->m_pointHost = {xHost, yHost};
   
   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};

   m_pwindow->on_right_button_up(pmouse);
   
}


void nano_window_bridge::on_right_button_down(int xHost, int yHost, int xAbsolute, int yAbsolute)
{
   
   auto pmouse = m_pwindow->__create_new <::user::mouse>();
   
   pmouse->m_pointHost = {xHost, yHost};
   
   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};

   m_pwindow->on_right_button_down(pmouse);
   
}


void nano_window_bridge::on_mouse_move(int xHost, int yHost, int xAbsolute, int yAbsolute)
{
   
   auto pmouse = m_pwindow->__create_new <::user::mouse>();
   
   pmouse->m_pointHost = {xHost, yHost};
   
   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};

   m_pwindow->on_mouse_move(pmouse);
   
}


void nano_window_bridge::on_char(int iChar)
{
   
   m_pwindow->on_char(iChar);
   
}


void nano_window_bridge::_on_draw_frame(CGContextRef cg, CGSize sizeFrame)
{
   
   ::pointer<quartz2d::nano::graphics::device>pnanodevice = ::place(new quartz2d::nano::graphics::device(cg));
   
   m_pwindow->_draw(pnanodevice);
   
}



void nano_window_bridge::on_layout(int x, int y, int w, int h)
{
   
   m_pwindow->m_pinterface->m_rectangle.left() = x;
   
   m_pwindow->m_pinterface->m_rectangle.top() = y;
   
   m_pwindow->m_pinterface->m_rectangle.right() = x + w;
   
   m_pwindow->m_pinterface->m_rectangle.bottom() = y + h;
   
}


bool nano_window_bridge::_is_top_most() const
{
   
   return m_pwindow->m_pinterface->m_bTopMost;
   
}


bool nano_window_bridge::_is_popup_window() const
{
   
   return m_pwindow->m_pinterface->is_popup_window();
   
}



