// Created by camilo on 2022-01-21 05:10 PM <3ThomasBorregaardSørensen
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


void nano_child::on_mouse_move(int x, int y)
{


}


void nano_child::set_capture()
{

   m_pwindow->m_pchildCapture = this;

   m_pwindow->set_capture();

}


bool nano_child::has_capture() const
{

   if (!m_pwindow->has_capture())
   {

      return false;

   }

   return m_pwindow->m_pchildCapture == this;

}


void nano_child::release_capture()
{

   if (m_pwindow->m_pchildCapture == this)
   {

      m_pwindow->m_pchildCapture.release();

      m_pwindow->release_capture();

   }

}



