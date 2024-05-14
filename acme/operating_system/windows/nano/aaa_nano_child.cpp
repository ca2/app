// Created by camilo on 2021-01-21 05:10 PM <3ThomasBorregaardSorensen
#include "framework.h"
#include "acme/operating_system.h"
#include "::nano::user::child.h"
#include "nano::user::window.h"


void ::nano::user::child::set_focus()
{

   m_pwindow->m_pchildFocus = this;

}



