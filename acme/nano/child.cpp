// Created by camilo on 2021-01-21 05:10 PM <3ThomasBorregaardSørensen
#include "framework.h"
#include "acme/operating_system.h"
#include "_nano.h"


void nano_child::set_focus()
{

   m_pwindow->m_pchildFocus = this;

   m_pwindow->redraw();

}


bool nano_child::is_focusable() const
{

   return false;

}



