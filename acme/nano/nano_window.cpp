//
// Created by camilo on 31/01/2022 16:16 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "nano_user.h"


nano_window::nano_window()
{


}


nano_window::~nano_window()
{


}


void nano_window::get_client_rectangle(::rectangle_i32 & rectangle)
{


}


void nano_window::draw(nano_device * pnanodevice)
{

   get_client_rectangle(m_rectangleClient);

   __pointer(::nano_pen) pnanopenBorder;

   if (is_active())
   {

      pnanopenBorder = m_ppenBorderFocus;

   }
   else
   {

      pnanopenBorder = m_ppenBorder;

   }

   pnanodevice->rectangle(m_rectangleClient, m_pbrushWindow, m_ppenBorder);

   on_draw(pnanodevice);

   draw_children(pnanodevice);

}


void nano_window::draw_children(nano_device * pnanodevice)
{

   for (auto & pchild: m_childa)
   {

      pchild->on_draw(pnanodevice);

   }

}


