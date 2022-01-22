// Created by camilo on 2021-01-21 14:57 <3ThomasBorregaardSørensen
#include "framework.h"
#include "acme/operating_system.h"
#include "nano_button.h"
#include "nano_window.h"


void nano_button::on_draw(HDC hdc)
{

   ::SelectObject(hdc, m_pwindow->m_hbrushWindow);

   if (m_pwindow->m_pchildFocus == this)
   {

      ::SelectObject(hdc, m_pwindow->m_hpenBorderFocus);

   }
   else
   {

      ::SelectObject(hdc, m_pwindow->m_hpenBorder);
   }

   Rectangle(hdc, m_rectangle.left, m_rectangle.top, m_rectangle.right, m_rectangle.bottom);

   SetBkColor(hdc, m_pwindow->m_crWindow);

   SetTextColor(hdc, m_pwindow->m_crText);

   wstring wstrText(m_strText);

   rectangle_i32 rectangleText(m_rectangle);

   rectangleText.deflate(4);

   ::DrawText(hdc, wstrText, (int)wstrText.get_length(), (LPRECT)&rectangleText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}


void nano_button::on_char(int iChar)
{

   if (iChar == '\r' || iChar == ' ')
   {

      m_pwindow->on_click(m_id);

   }

}

