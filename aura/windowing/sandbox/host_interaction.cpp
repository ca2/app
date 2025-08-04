//
//  host_interaction.cpp
//  aura
//
//  Copied from node/ios by Camilo Sasuke Thomas Borregaard Soerensen on 20/06/05.
//  (with refactorization: ui_interaction -> host_interaction to
//  match OPERATING_SYSTEM_NAMESPACE::create_*host*_window() naming.)
//
#include "framework.h"
#include "_sandbox.h"
#include "acme/handler/topic.h"


namespace sandbox_windowing
{


   host_interaction::host_interaction()
   {

      

   }


   host_interaction::~host_interaction()
   {


   }


   void host_interaction::on_initialize_particle()
   {
      
      ::user::interaction::on_initialize_particle();
      
      ::acme::sandbox_windowing::host_interaction::on_initialize_particle();
      
   }


   void host_interaction::destroy()
   {
      
      ::user::interaction::destroy();
      
      ::acme::sandbox_windowing::host_interaction::destroy();

   }


   ::sandbox_windowing::windowing* host_interaction::windowing()
   {

      auto pwindowing = ::user::interaction::windowing();

      auto pwindowingHere = dynamic_cast <::sandbox_windowing::windowing*>(pwindowing);

      return pwindowingHere;

   }


   void host_interaction::create_window()
   {
      
      ::user::interaction::create_window();
      
      

   }



   void host_interaction::install_message_routing(::channel* pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &host_interaction::on_message_create);

   }


   void host_interaction::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void host_interaction::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001DrawChildren(pgraphics);

   }


   void host_interaction::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_000OnDraw(pgraphics);

   }


   void host_interaction::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void host_interaction::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnDraw(pgraphics);

   }


   void host_interaction::post_redraw(bool bAscendants)
   {

      ::user::interaction::post_redraw(bAscendants);

   }


   void host_interaction::on_message_create(::message::message* pmessage)
   {

      pmessage->previous();

      auto pwindowing = windowing();

      auto pwindow = window();

      m_ewindowflag |= e_window_flag_root;

      pwindowing->m_pwindowApplicationHost = pwindow;

      display(e_display_normal);
      
      window()->show_window();

   }


   void host_interaction::on_layout(::draw2d::graphics_pointer& pgraphics)
   {

      ::int_rectangle r;

      r = this->rectangle();

      if (r.is_empty())
      {

         return;

      }

      ::pointer<::user::interaction>pinteraction = first_child();
      
//      get_child(pinteraction);

      if (::is_null(pinteraction))
      {

         return;

      }

      pinteraction->place(r);

   }


   void host_interaction::set_mouse_capture()
   {
   
      ::user::interaction::set_mouse_capture();
   
   }


bool host_interaction::has_mouse_capture()
{

   return ::user::interaction::has_mouse_capture();

}


void host_interaction::set_keyboard_focus()
{
   
   ::acme::sandbox_windowing::host_interaction::set_keyboard_focus();
   
}


void host_interaction::hide()
{

   ::user::interaction::hide();
   
}


::string host_interaction::get_title()
{
   
   return ::user::interaction::get_title();

}


::int_rectangle host_interaction::get_rectangle()
{
   
   return ::user::interaction::get_rectangle();
   
}


void host_interaction::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {
      
      ::user::interaction::handle(ptopic, phandlercontext);
      
      if(ptopic->m_bRet)
      {
         
         return;
         
      }
      
      ::acme::sandbox_windowing::host_interaction::handle(ptopic, phandlercontext);
      
   }

} // namespace sandbox_windowing



