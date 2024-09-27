//
// Created by camilo on 31/01/2022.
//
#include "framework.h"
#include "device.h"
#include "brush.h"
#include "font.h"
#include "pen.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/prototype/geometry2d/rectangle.h"
////#include "acme/exception/exception.h"


int align_to_windows_draw_text_align(enum_align ealign);

int draw_text_to_windows_draw_text(enum_draw_text edrawtext);


namespace windows
{



   namespace nano
   {


      namespace graphics
      {

         device::device()
         {

            m_hdc = ::CreateCompatibleDC(nullptr);
            m_bDelete = true;

         }




         device::~device()
         {

            if (m_bDelete)
            {

               ::DeleteDC(m_hdc);

            }

         }


         void device::attach(void * posdata)
         {

            auto hdc = (HDC)posdata;

            m_hdc = hdc;
            m_bDelete = false;

         }


         void device::_draw_text(const ::string& str, const ::rectangle_i32& rectangleText, const ::e_align& ealign, const ::e_draw_text& edrawtext,
            ::nano::graphics::brush* pnanobrushBack, ::nano::graphics::brush* pnanobrushText,
            ::nano::graphics::font* pnanofont)
         {

            COLORREF colorrefBackgroundColor = win32_COLORREF(pnanobrushBack->m_color);

            SetBkColor(m_hdc, colorrefBackgroundColor);

            COLORREF colorrefTextColor = win32_COLORREF(pnanobrushText->m_color);

            SetTextColor(m_hdc, colorrefTextColor);

            SetBkMode(m_hdc, OPAQUE);

            wstring wstrMessage(str);

            pnanofont->update(this);

            ::SelectObject(m_hdc, (HFONT)pnanofont->operating_system_data());

            TEXTMETRICW textmetricw = {};

            ::GetTextMetrics(m_hdc, &textmetricw);

            int iAlign = align_to_windows_draw_text_align(ealign);

            int iFlag = draw_text_to_windows_draw_text(edrawtext);

            ::DrawText(m_hdc, wstrMessage, (int)wstrMessage.length(), (LPRECT)&rectangleText, iAlign | iFlag);

         }


         ::size_i32 device::get_text_extents(const ::string& str, ::nano::graphics::font* pnanofont)
         {

            pnanofont->update(this);

            ::SelectObject(m_hdc, (HFONT)pnanofont->operating_system_data());

            wstring wstr(str);

            ::SIZE size;

            if (!::GetTextExtentPoint32W(m_hdc, wstr, (int)wstr.length(), &size))
            {

               throw ::exception(error_failed);

            }

            return { size.cx, size.cy };

         }


         void device::rectangle(const ::rectangle_i32& rectangle, ::nano::graphics::brush* pnanobrush, ::nano::graphics::pen* pnanopen)
         {

            pnanobrush->update(this);

            ::SelectObject(m_hdc, (HGDIOBJ)pnanobrush->operating_system_data());

            pnanopen->update(this);

            ::SelectObject(m_hdc, (HGDIOBJ)pnanopen->operating_system_data());

            ::Rectangle(m_hdc,
               rectangle.left(),
               rectangle.top(),
               rectangle.right(),
               rectangle.bottom());


         }


      } // namespace graphics


   } // namespace nano


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


