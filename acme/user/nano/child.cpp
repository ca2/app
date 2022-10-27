// Created by camilo on 2022-01-21 05:10 PM <3ThomasBorregaardSørensen
#include "framework.h"
#include "child.h"
#include "window.h"
#include "device.h"
#include "acme/operating_system.h"


void nano_child::set_focus()
{

   m_pnanowindow->m_pchildFocus = this;

   m_pnanowindow->redraw();

}


bool nano_child::is_focusable() const
{

   return false;

}


void nano_child::on_mouse_move(::user::mouse * pmouse)
{


}


void nano_child::set_capture()
{

   m_pnanowindow->m_pchildCapture = this;

   m_pnanowindow->set_capture();

}


bool nano_child::has_capture() const
{

   if (!m_pnanowindow->has_capture())
   {

      return false;

   }

   return m_pnanowindow->m_pchildCapture == this;

}


void nano_child::release_capture()
{

   if (m_pnanowindow->m_pchildCapture == this)
   {

      m_pnanowindow->m_pchildCapture.release();

      m_pnanowindow->release_capture();

   }

}


void nano_child::resize_to_fit()
{

   auto pdevice = __create < nano_device >();

   auto size = pdevice->get_text_extents(m_strText, m_pnanowindow->m_pfont);

   m_rectangle.right = m_rectangle.left + size.cx;

   m_rectangle.bottom = m_rectangle.top + size.cy;

}



