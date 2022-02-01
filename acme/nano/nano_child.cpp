// Created by camilo on 2021-01-21 05:10 PM <3ThomasBorregaardSørensen
#include "framework.h"
#include "acme/operating_system.h"
#include "nano_user.h"
#include "nano_child.h"
#include "nano_window.h"


void nano_child::set_focus()
{

   m_pwindow->m_pchildFocus = this;

}



