//
// Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSørensen!!
//
#include "framework.h"


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



