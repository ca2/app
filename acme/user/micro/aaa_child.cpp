// Created by camilo on 2022-01-21 05:10 PM <3ThomasBorregaardSorensen
#include "framework.h"
#include "child.h"
#include "interaction.h"
#include "acme/nano/graphics/device.h"
#include "button.h"
//#include "acme/operating_system.h"

namespace nano
{

   namespace user
   {
   

void child::set_focus()
{

   m_pinterchange->m_pchildFocus = this;

   m_pinterchange->redraw();

}


bool child::is_focusable()
{

   return false;

}


void child::on_mouse_move(::user::mouse * pmouse)
{


}


void child::set_capture()
{

   m_pinterchange->m_pchildCapture = this;

   m_pinterchange->set_capture();

}


bool child::has_capture()
{

   if (!m_pinterchange->has_capture())
   {

      return false;

   }

   return m_pinterchange->m_pchildCapture == this;

}


void child::release_capture()
{

   if (m_pinterchange->m_pchildCapture == this)
   {

      m_pinterchange->m_pchildCapture.release();

      m_pinterchange->release_capture();

   }

}


void child::resize_to_fit()
{

   auto pdevice = __øcreate < ::nano::graphics::device >();

   auto size = pdevice->get_text_extents(m_strText, m_pinterchange->m_pfont);

   m_rectangle.right() = m_rectangle.left() + size.cx();

   m_rectangle.bottom() = m_rectangle.top() + size.cy();

}





   } // namespace user


} // namespace nano


