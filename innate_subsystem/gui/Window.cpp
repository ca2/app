// Copyright (C) 2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "Window.h"
#include "acme/user/user/key.h"
#include "acme/user/user/mouse.h"


namespace innate_subsystem
{


::innate_subsystem::enum_mouse e_button_state_state_to_e_mouse(const ::user::keyboard_state & keyboardstate);


} // namespace innate_subsystem


namespace innate_subsystem
{


   // Window::Window()
   // {
   //
   // }
   //
   //
   // Window::~Window()
   // {
   //
   // }


   void WindowComposite::back_on_mouse_move(::user::mouse * pmouse)
   {
      
      bool bDoDefaultProcessing = false;
      
      auto emouseButtons = ::innate_subsystem::e_button_state_state_to_e_mouse(pmouse->m_ekeystate);
      
      if(onMouseEx(pmouse->m_eusermessage, emouseButtons, 0, pmouse->m_pointHost, bDoDefaultProcessing))
      {
         
         return;
         
      }
      
      onMouse(emouseButtons, 0, pmouse->m_pointHost);
      
   }


void WindowComposite::back_on_left_button_down(::user::mouse * pmouse)
{
   
   bool bDoDefaultProcessing = false;
   
   auto emouseButtons = ::innate_subsystem::e_button_state_state_to_e_mouse(pmouse->m_ekeystate);

   if(onMouseEx(pmouse->m_eusermessage, emouseButtons, 0, pmouse->m_pointHost, bDoDefaultProcessing))
   {
      
      return;
      
   }
   
   onMouse(emouseButtons, 0, pmouse->m_pointHost);
   
}


void WindowComposite::back_on_left_button_up(::user::mouse * pmouse)
{
   
   bool bDoDefaultProcessing = false;

   auto emouseButtons = ::innate_subsystem::e_button_state_state_to_e_mouse(pmouse->m_ekeystate);

   if(onMouseEx(pmouse->m_eusermessage, emouseButtons, 0, pmouse->m_pointHost, bDoDefaultProcessing))
   {
      
      return;
      
   }
   
   onMouse(emouseButtons, 0, pmouse->m_pointHost);
   
}


void WindowComposite::back_on_right_button_down(::user::mouse * pmouse)
{
   
   bool bDoDefaultProcessing = false;
   
   auto emouseButtons = ::innate_subsystem::e_button_state_state_to_e_mouse(pmouse->m_ekeystate);
   
   if(onMouseEx(pmouse->m_eusermessage, emouseButtons, 0, pmouse->m_pointHost, bDoDefaultProcessing))
   {
      
      return;
      
   }
   
   onMouse(emouseButtons, 0, pmouse->m_pointHost);
   
}


void WindowComposite::back_on_right_button_up(::user::mouse * pmouse)
{
   
   bool bDoDefaultProcessing = false;
   
   auto emouseButtons = ::innate_subsystem::e_button_state_state_to_e_mouse(pmouse->m_ekeystate);
   
   if(onMouseEx(pmouse->m_eusermessage, emouseButtons, 0, pmouse->m_pointHost, bDoDefaultProcessing))
   {
      
      return;
      
   }
   
   onMouse(emouseButtons, 0, pmouse->m_pointHost);
   
}


void WindowComposite::on_key_down(::user::key * pkey)
{
   
   onKey(pkey->m_eusermessage, pkey->m_ekey);
   
}


void WindowComposite::on_key_up(::user::key * pkey)
{
   
   onKey(pkey->m_eusermessage, pkey->m_ekey);
   
}


   void WindowComposite::on_create()
   {
   
      onCreate(nullptr);
      
   }




//void WindowComposite::on_key_down(::user::key * pkey)
//{
//
//
//
//}
//
//
//void WindowComposite::on_key_up(::user::key * pkey)
//{
//   
//   
//}


} // namespace innate_subsystem


namespace innate_subsystem
{

::innate_subsystem::enum_mouse e_button_state_state_to_e_mouse(const ::user::keyboard_state & keyboardstate)
{
   
   ::i32 mouseButtons = 0;
   
   mouseButtons |= keyboardstate & ::user::e_key_state_right_button ? innate_subsystem::e_mouse_right : 0;
   mouseButtons |= keyboardstate & ::user::e_key_state_middle_button ? innate_subsystem::e_mouse_middle : 0;
   mouseButtons |= keyboardstate & ::user::e_key_state_left_button ? innate_subsystem::e_mouse_left : 0;
   
   return (::innate_subsystem::enum_mouse) mouseButtons;
   
}


} // namespace innate_subsystem



