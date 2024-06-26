// Created by camilo on 2022-01-21 05:10 PM <3ThomasBorregaardSorensen
#include "framework.h"
#include "child.h"
#include "window.h"
#include "device.h"
#include "button.h"
//#include "acme/operating_system.h"

namespace nano
{

   namespace user
   {
   

void child::set_focus()
{

   m_pnanowindow->m_pchildFocus = this;

   m_pnanowindow->redraw();

}


bool child::is_focusable() const
{

   return false;

}


void child::on_mouse_move(::user::mouse * pmouse)
{


}


void child::set_capture()
{

   m_pnanowindow->m_pchildCapture = this;

   m_pnanowindow->set_capture();

}


bool child::has_capture() const
{

   if (!m_pnanowindow->has_capture())
   {

      return false;

   }

   return m_pnanowindow->m_pchildCapture == this;

}


void child::release_capture()
{

   if (m_pnanowindow->m_pchildCapture == this)
   {

      m_pnanowindow->m_pchildCapture.release();

      m_pnanowindow->release_capture();

   }

}


void child::resize_to_fit()
{

   auto pdevice = __create < ::nano::user::device >();

   auto size = pdevice->get_text_extents(m_strText, m_pnanowindow->m_pfont);

   m_rectangle.right() = m_rectangle.left() + size.cx();

   m_rectangle.bottom() = m_rectangle.top() + size.cy();

}





   } // namespace user


} // namespace nano


