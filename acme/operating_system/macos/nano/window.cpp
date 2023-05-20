//
// Created by camilo on 31/01/2022 15:37 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "window.h"
#include "window_bridge.h"
#include "device.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/platform/sequencer.h"
#include "acme/platform/node.h"
#include "acme/user/nano/window.h"
#include "acme/user/user/mouse.h"
#include <CoreGraphics/CoreGraphics.h>

void apple_defer_nano_application_create(::acme::system * psystem);

void ns_main_async(dispatch_block_t block);

bool ns_app_is_running();

void ns_app_run();

void ns_app_stop();

CLASS_DECL_ACME void ns_get_main_screen_size(int & cx, int & cy);

void screen_coordinates_aware_copy(CGRect & rect, const RECTANGLE_I32 &rectangle);

void screen_coordinates_aware_copy(CGPoint & cgpoint, const POINT_I32 & point);

void screen_coordinates_aware_copy(POINT_I32 & point, const CGPoint & cgpoint);

//void macos_defer_initialize_nano_callbacks();

namespace macos
{


   nano_window::nano_window()
   {
      
      //macos_defer_initialize_nano_callbacks();

   }


   nano_window::~nano_window()
   {

      delete_drawing_objects();

      m_pnanodevice.release();

   }


   void nano_window::on_initialize_particle()
   {

      ::object::on_initialize_particle();

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

      return acmenode()->dark_mode();

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
      
      apple_defer_nano_application_create(acmesystem());
      
      m_pwindowbridge = __new(nano_window_bridge);

      CGRect cgrect;
      
      screen_coordinates_aware_copy(cgrect, m_pinterface->m_rectangle);
      
      m_pwindowbridge->m_pwindow = this;
      
      m_pwindowbridge->create_ns_nano_window(cgrect);
      
      nano_window_on_create();
      
      //create_drawing_objects();

      ///on_create();

   }

void nano_window::handle(::topic* ptopic, ::context* pcontext)
{
   
   if (ptopic->m_atom == id_set_dark_mode)
   {
      
      update_drawing_objects();
      //m_pimplementation->handle(ptopic, pcontext);
      redraw();
      
   }
   
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


   ::nano_child * nano_window::hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder)
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

 ///     while(message_loop_step())
    //  {

      //}
      
      ns_main_async(^()
                    {
         
         m_pwindowbridge->_run_modal_loop();
         
      });
      

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


   ::size_i32 nano_window::get_main_screen_size()
   {
      
      ::i32 cx = 800;
      
      ::i32 cy = 600;
      
      ns_get_main_screen_size(cx, cy);
      
      return { cx, cy };
      
   }


   ::payload nano_window::do_synchronously()
   {
      
      if(ns_app_is_running())
      {
         
         return nano_window_implementation::do_synchronously();
         
      }

      atom atomResult;

      m_pinterface->m_psequencer->then([ &atomResult ](auto psequence)
      {

         atomResult = psequence->m_payloadResult;
         
         ns_app_stop();

      });

      ns_app_run();

      //   auto pmessagebox = pparticle->__create_new < nano_message_box >();
      //
      //   atom idResult;
      //
      //   manual_reset_event event;
      //
      //   pmessagebox->display(pszMessage, pszTitle, emessagebox, pszDetails);
      //
      //   pmessagebox->m_functionClose = [&idResult, &event](nano_window * pwindow)
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
   
   ::pointer<quartz2d::nano_device>pnanodevice = __new(quartz2d::nano_device(cg));
   
   m_pwindow->_draw(pnanodevice);
   
}



void nano_window_bridge::on_layout(int x, int y, int w, int h)
{
   
   m_pwindow->m_pinterface->m_rectangle.left = x;
   
   m_pwindow->m_pinterface->m_rectangle.top = y;
   
   m_pwindow->m_pinterface->m_rectangle.right = x + w;
   
   m_pwindow->m_pinterface->m_rectangle.bottom = y + h;
   
}


bool nano_window_bridge::_is_top_most() const
{
   
   return m_pwindow->m_pinterface->m_bTopMost;
   
}


bool nano_window_bridge::_is_popup_window() const
{
   
   return m_pwindow->m_pinterface->is_popup_window();
   
}



