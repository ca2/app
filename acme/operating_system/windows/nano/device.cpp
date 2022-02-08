//
// Created by camilo on 31/01/2022.
//
#include "framework.h"
#include "acme/user/nano/_nano.h"
#include "_nano.h"


int align_to_windows_draw_text_align(enum_align ealign);

int draw_text_to_windows_draw_text(enum_draw_text edrawtext);


namespace windows
{


   nano_device::nano_device()
   {

      m_hdc = ::CreateCompatibleDC(nullptr);
      m_bDelete = true;

   }


   nano_device::nano_device(HDC hdc)
   {

      m_hdc = hdc;
      m_bDelete = false;

   }


   nano_device::~nano_device()
   {

      if (m_bDelete)
      {

         ::DeleteDC(m_hdc);

      }

   }




   void nano_device::_draw_text(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext,
                          ::nano_brush * pnanobrushBack, ::nano_brush * pnanobrushText,
                          ::nano_font * pnanofont)
   {

      SetBkColor(m_hdc, pnanobrushBack->m_color.get_COLORREF());

      SetTextColor(m_hdc, pnanobrushText->m_color.get_COLORREF());

      SetBkMode(m_hdc, OPAQUE);

      wstring wstrMessage(str);

      pnanofont->update(this);

      ::SelectObject(m_hdc, (HFONT) pnanofont->operating_system_data());

      TEXTMETRICW textmetricw = {};

      ::GetTextMetrics(m_hdc, &textmetricw);

      int iAlign = align_to_windows_draw_text_align(ealign);

      int iFlag = draw_text_to_windows_draw_text(edrawtext);

      ::DrawText(m_hdc, wstrMessage, (int)wstrMessage.get_length(), (LPRECT)&rectangleText, iAlign | iFlag);

   }


   ::size_i32 nano_device::get_text_extents(const ::string & str, ::nano_font * pnanofont)
   {

      pnanofont->update(this);

      ::SelectObject(m_hdc, (HFONT)pnanofont->operating_system_data());

      wstring wstr(str);

      ::SIZE size;

      if (!::GetTextExtentPoint32W(m_hdc, wstr, (int) wstr.length(), &size))
      {

         throw exception(error_failed);

      }

      return { size.cx, size.cy };

   }


   void nano_device::rectangle(const ::rectangle_i32 & rectangle, ::nano_brush * pnanobrush, ::nano_pen * pnanopen)
   {

      pnanobrush->update(this);

      ::SelectObject(m_hdc, (HGDIOBJ) pnanobrush->operating_system_data());

      pnanopen->update(this);

      ::SelectObject(m_hdc, (HGDIOBJ) pnanopen->operating_system_data());

      ::Rectangle(m_hdc,
                  rectangle.left,
                  rectangle.top,
                  rectangle.right,
                  rectangle.bottom);


   }




} // namespace windows




int align_to_windows_draw_text_align(enum_align ealign)
{

   int iAlign = 0;

   if (ealign & e_align_right)
   {

      iAlign |= DT_RIGHT;

   }
   else if (ealign & e_align_horizontal_center)
   {

      iAlign |= DT_CENTER;

   }
   else
   {

      iAlign |= DT_LEFT;

   }


   if (ealign & e_align_bottom)
   {

      iAlign |= DT_BOTTOM;

   }
   else if (ealign & e_align_vertical_center)
   {

      iAlign |= DT_VCENTER;

   }
   else
   {

      iAlign |= DT_TOP;

   }

   return iAlign;

}



int draw_text_to_windows_draw_text(enum_draw_text edrawtext)
{

   int iFlag = 0;

   if (edrawtext & e_draw_text_end_ellipsis)
   {

      iFlag |= DT_END_ELLIPSIS;

   }

   if (edrawtext & e_draw_text_expand_tabs)
   {

      iFlag |= DT_EXPANDTABS;

   }

   if (edrawtext & e_draw_text_single_line)
   {

      iFlag |= DT_SINGLELINE;

   }

   if (edrawtext & e_draw_text_word_break)
   {

      iFlag |= DT_WORDBREAK;

   }

   return iFlag;

}


