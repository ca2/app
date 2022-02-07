//
// Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"


nano_window_implementation::nano_window_implementation()
{


}


nano_window_implementation::~nano_window_implementation()
{


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


void nano_window_implementation::on_create()
{

   return m_pinterface->on_create();

}



