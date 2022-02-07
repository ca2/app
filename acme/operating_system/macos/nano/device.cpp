//
// Created by camilo on 31/01/2022 20:15 <3ThomasBorregaardSørensen!! Thomas Likes number 5!!
//
#include "framework.h"
#include "_nano.h"
//#include <X11/Xlocale.h>



namespace quartz2d
{


   nano_device::nano_device(CGContextRef pdc)
   {

      m_pdc = pdc;

   }


   nano_device::~nano_device()
   {

      //cairo_destroy(m_pdc);

   }


   void nano_device::_draw_text(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano_brush * pnanobrushBack, ::nano_brush * pnanobrushText, ::nano_font * pnanofont)
   {
      
      float w, h;

         w = rectangleText.width();

         h = rectangleText.height();

         //CGAffineTransform myTextTransform;//2

         CGContextSelectFont (m_pdc,//3

                         pnanofont->m_strFontName,

                          pnanofont->m_iFontSize,

                          kCGEncodingMacRoman);

         //CGContextSetCharacterSpacing (myContext, 10);//4
      
      CGContextSetTextPosition(m_pdc, 0, 0);
      CGContextSetTextDrawingMode (m_pdc, kCGTextInvisible);//5
      CGContextShowText (m_pdc, str, str.length());//10
      CGPoint pointSize = CGContextGetTextPosition(m_pdc);
      pointSize.y = pnanofont->m_iFontSize;

         //CGContextSetTextDrawingMode (m_pdc, kCGTextFillStroke);//5
      CGContextSetTextDrawingMode (m_pdc, kCGTextFill);//5
      CGAffineTransform trans = CGAffineTransformMakeScale(1, -1);
      CGContextSetTextMatrix(m_pdc, trans);
         CGContextSetRGBFillColor (m_pdc, pnanobrushText->m_color.dr(),
                                   pnanobrushText->m_color.dg(),
                                   pnanobrushText->m_color.db(),
                                   pnanobrushText->m_color.da());//6

//         CGContextSetRGBStrokeColor (m_pdc,  pnanobrushText->m_color.dr(),
//                                     pnanobrushText->m_color.dg(),  pnanobrushText->m_color.db(),  pnanobrushText->m_color.da());//7

         //myTextTransform = CGAffineTransformMakeRotation (MyRadians (45));//8

         //CGContextSetTextMatrix (myContext, myTextTransform);//9
      
      
      double x = rectangleText.left;
      
      double y = rectangleText.top;

            if(ealign & e_align_horizontal_center)
            {
      
               x += ((double) rectangleText.width() - pointSize.x) / 2.0;
      
            }
            else if(ealign & e_align_right)
            {
      
               x += (double) rectangleText.width() - pointSize.x;
      
            }
      
            if(ealign & e_align_vertical_center)
            {
      
               y += ((double) rectangleText.height() - pointSize.y) / 2.0;
      
            }
            else if(ealign & e_align_bottom)
            {
      
               y += (double) rectangleText.height() - pointSize.y;
      
            }
      
      y += pointSize.y;

         CGContextShowTextAtPoint (m_pdc, x,
                                   y, str, str.length());//10

//      cairo_set_antialias(m_pdc, CAIRO_ANTIALIAS_SUBPIXEL);
//
//      cairo_select_font_face(m_pdc, pnanofont->m_strFontName, CAIRO_FONT_SLANT_NORMAL, pnanofont->m_bBold ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);
//
//      cairo_set_font_size(m_pdc, pnanofont->m_iFontSize);
//
//      cairo_text_extents_t textextents = {};
//
//      double x = rectangleText.left;
//
//      double y = rectangleText.top;
//
//      cairo_text_extents(m_pdc, str, &textextents);
//
//      if(ealign & e_align_horizontal_center)
//      {
//
//         x += ((double) rectangleText.width() - textextents.width) / 2.0;
//
//      }
//      else if(ealign & e_align_right)
//      {
//
//         x += (double) rectangleText.width() - textextents.width;
//
//      }
//
//      if(ealign & e_align_vertical_center)
//      {
//
//         y += ((double) rectangleText.height() - textextents.height) / 2.0;
//
//      }
//      else if(ealign & e_align_bottom)
//      {
//
//         y += (double) rectangleText.height() - textextents.height;
//
//      }
//
//      _set_source(pnanobrushText->m_color);
//
//      cairo_move_to(m_pdc, x, y + textextents.height);
//
//      cairo_show_text(m_pdc, str);

   }


   void nano_device::rectangle(const ::rectangle_i32 & rectangle, ::nano_brush * pnanobrush, ::nano_pen * pnanopen)
   {

//      cairo_set_antialias(m_pdc, CAIRO_ANTIALIAS_NONE);

      int iWidth = pnanopen ? pnanopen->m_iWidth : 0;

      CGRect rect;
      
      rect.origin.x = rectangle.left;
      rect.origin.y = rectangle.top;
      rect.size.width = rectangle.width();
      rect.size.height = rectangle.height();

      if (pnanobrush && pnanobrush->m_color)
      {

   
         _set_fill_color(pnanobrush->m_color);

         CGContextFillRect(m_pdc, rect);

      }

      if(iWidth > 0)
      {

         
         CGContextBeginPath(m_pdc);
         
         CGContextAddRect(m_pdc, rect);
         
         CGContextSetRGBStrokeColor(m_pdc, pnanopen->m_color.dr(), pnanopen->m_color.dg(), pnanopen->m_color.db(), pnanopen->m_color.da());
         
         CGContextSetLineWidth(m_pdc, pnanopen->m_iWidth);
         
         CGContextStrokePath(m_pdc);

      }



   }


//   void nano_device::set_antialias(bool bAntialiasOn)
//   {
//
//
//
//   }


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

      //cairo_set_source_rgba(m_pdc, color.dr(), color.dg(), color.db(), color.da());

   }

void nano_device::_set_fill_color(const ::color::color & color)
{

   CGContextSetRGBFillColor(m_pdc, color.dr(), color.dg(), color.db(), color.da());

}

} // namespace quartz2d



