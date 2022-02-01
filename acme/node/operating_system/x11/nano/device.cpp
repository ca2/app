//
// Created by camilo on 31/01/2022 20:15 <3ThomasBorregaardSørensen!! Thomas Likes number 5!!
//
#include "framework.h"
#include "_nano.h"
#include <X11/Xlocale.h>



namespace x11
{


   nano_device::nano_device(cairo_t * pdc)
   {

      m_pdc = pdc;

   }


   nano_device::~nano_device()
   {

      cairo_destroy(m_pdc);

   }


   void nano_device::draw_text(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, ::nano_brush * pnanobrushBack, ::nano_brush * pnanobrushText, ::nano_font * pnanofont)
   {

      cairo_select_font_face(m_pdc, pnanofont->m_strFontName, CAIRO_FONT_SLANT_NORMAL, pnanofont->m_bBold ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);

      cairo_set_font_size(m_pdc, pnanofont->m_iFontSize);

      cairo_text_extents_t textextents = {};

      double x = rectangleText.left;

      double y = rectangleText.top;

      cairo_text_extents(m_pdc, str, &textextents);

      if(ealign & e_align_horizontal_center)
      {

         x += ((double) rectangleText.width() - textextents.width) / 2.0;

      }
      else if(ealign & e_align_right)
      {

         x += (double) rectangleText.width() - textextents.width;

      }

      if(ealign & e_align_vertical_center)
      {

         y += ((double) rectangleText.height() - textextents.height) / 2.0;

      }
      else if(ealign & e_align_bottom)
      {

         y += (double) rectangleText.height() - textextents.height;

      }

      _set_source(pnanobrushText->m_color);

      cairo_move_to(m_pdc, x, y + textextents.height);

      cairo_show_text(m_pdc, str);

   }


   void nano_device::rectangle(const ::rectangle_i32 & rectangle, ::nano_brush * pnanobrush, ::nano_pen * pnanopen)
   {

      int iWidth = pnanopen ? pnanopen->m_iWidth : 0;

      if (pnanobrush && pnanobrush->m_color)
      {

         auto rectangleFill = rectangle;

         rectangleFill.deflate(iWidth);

         _set_source(pnanobrush->m_color);

         cairo_rectangle(m_pdc, rectangleFill.left, rectangleFill.top, rectangleFill.width(), rectangleFill.height());

         cairo_fill(m_pdc);

      }

      if(iWidth > 0)
      {

         _set_source(pnanopen->m_color);

         cairo_set_line_width(m_pdc, iWidth);

         cairo_rectangle(m_pdc, rectangle.left, rectangle.top, rectangle.width(), rectangle.height());

         cairo_stroke(m_pdc);

      }

   }


//   XColor nano_device::_alloc_xcolor(const ::color::color & color)
//   {
//
//      auto colormap = XDefaultColormap(m_pdisplay, DefaultScreen(m_pdisplay));
//
//      XColor xcolor;
//
//      xcolor.red = color.red << 8 | color.red;
//      xcolor.green = color.green << 8 | color.green;
//      xcolor.blue = color.blue << 8 | color.blue;
//
//      XAllocColor(m_pdisplay, colormap, &xcolor);
//
//      return xcolor;
//
//   }
//
//
//
//   void nano_device::_set_foreground(const ::color::color & color)
//   {
//
//      auto xcolor = _alloc_xcolor(color);
//
//      XSetForeground(m_pdisplay, m_gc, xcolor.pixel);
//
//   }
//
//
//   void nano_device::_set_background(const ::color::color & color)
//   {
//
//      auto xcolor = _alloc_xcolor(color);
//
//      XSetBackground(m_pdisplay, m_gc, xcolor.pixel);
//
//   }

   void nano_device::_set_source(const ::color::color & color)
   {

      cairo_set_source_rgba(m_pdc, color.dr(), color.dg(), color.db(), color.da());

   }


} // namespace x11



