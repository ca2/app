//
// Created by camilo on 31/01/2022.
//
#include "framework.h"


namespace windows
{



   nano_device::nano_device(HDC hdc)
   {

      m_hdc = hd

   }


   nano_device::~nano_device()
   {


   }


   void
   nano_device::draw_text(const ::string & strMessage, const ::rectangle_i32 & rectangleText, const ::e_align & ealign,
                          ::nano_brush * pnanobrushBack, ::nano_brush * pnanobrushText,
                          ::nano_font * pnanofont)
   {

      SetBkColor(m_hdc, nanobrushBack.m_color);

      SetTextColor(m_hdc, nanobrushText.m_color);

      wstring wstrMessage(m_strMessage);

      ::SelectObject(m_hdc, (HFONT) pnanofont->operating_system_data());

      ::DrawText(m_hdc, wstrMessage, (int) wstrMessage.get_length(), (LPRECT) & rectangleText,
                 DT_LEFT | DT_TOP | DT_WORDBREAK)

   }


   void nano_device::rectangle(const ::rectangle_i32 & rectangle, ::nano_brush * pnanobrush, ::nano_pen * pnanopen)
   {

      ::SelectObject(m_hdc, (HGDIOBJ) pnanobrush->operating_system_data());

      ::SelectObject(m_hdc, (HGDIOBJ) pnanopen->operating_system_data());

      ::Rectangle(m_hdc,
                  rectangle.left,
                  rectangle.top,
                  rectangle.right,
                  rectangle.bottom);


   }


} // namespace windows





