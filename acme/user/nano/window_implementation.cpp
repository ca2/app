//
// Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"
#include "acme/id.h"
#include "display.h"


nano_window_implementation::nano_window_implementation()
{


}


nano_window_implementation::~nano_window_implementation()
{


}


::nano::display * nano_window_implementation::get_display()
{

   return nullptr;

}


void nano_window_implementation::draw(nano_device * pnanodevice)
{

   m_pinterface->draw(pnanodevice);

}


bool nano_window_implementation::get_dark_mode()
{

   return m_pinterface->get_dark_mode();

}


bool nano_window_implementation::is_active()
{

   return m_pinterface->is_active();

}


void nano_window_implementation::nano_window_on_create()
{

   m_psystem->node()->fetch_user_color();

   m_psystem->add_signal_handler(this, id_operating_system_user_color_change);
   
   create_drawing_objects();

   on_create();

}


void nano_window_implementation::on_create()
{

   return m_pinterface->on_create();

}


void nano_window_implementation::handle(::topic * ptopic, ::context * pcontext)
{

   if(ptopic->m_atom == id_operating_system_user_color_change)
   {

      update_drawing_objects();

      redraw();

   }

}


::size_i32 nano_window_implementation::get_main_screen_size()
{

   auto pdisplay = get_display();

   if(::is_null(pdisplay))
   {

      return {800, 600};

   }

   return pdisplay->get_main_screen_size();

}



