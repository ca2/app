//
// Created by camilo on 31/01/2022 20:15 <3ThomasBorregaardSorensen!! Thomas Likes number 5!!
//
#include "framework.h"
#include "device.h"
#include "acme/user/nano/font.h"
#include "acme/user/nano/brush.h"
#include "acme/user/nano/pen.h"


namespace quartz2d
{


   nano_device::nano_device()
   {
      
      m_bOwn = true;
      
      auto colorspace = CGColorSpaceCreateDeviceRGB();
      
      int width = 256;
      
      int height = 256;
      
      int bitsPerComponent = 8;
      
      int bytesPerRow = width * 4;

      m_pdc = CGBitmapContextCreate(
         nullptr,
         width, height,
         bitsPerComponent, bytesPerRow,
         colorspace, kCGImageAlphaPremultipliedLast);
      
      CGColorSpaceRelease(colorspace);

   }


   nano_device::nano_device(CGContextRef pdc)
   {
      
      m_bOwn = false;

      m_pdc = pdc;

   }


   nano_device::~nano_device()
   {
      
      if(m_bOwn)
      {

         if(m_pdc)
         {
          
            CGContextRelease(m_pdc);
            
         }
         
      }

   }


   void nano_device::_draw_text(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano_brush * pnanobrushBack, ::nano_brush * pnanobrushText, ::nano_font * pnanofont)
   {
      
      _select_font(pnanofont);
      
      float w, h;

      w = rectangleText.width();

      h = rectangleText.height();
      
      _select_font(pnanofont);

      CGContextSetTextPosition(m_pdc, 0, 0);
      CGContextSetTextDrawingMode (m_pdc, kCGTextInvisible);
      CGContextShowText (m_pdc, str, str.length());
      CGPoint pointSize = CGContextGetTextPosition(m_pdc);
      pointSize.y = pnanofont->m_iFontSize;

      CGContextSetTextDrawingMode (m_pdc, kCGTextFill);
      CGAffineTransform trans = CGAffineTransformMakeScale(1, -1);
      CGContextSetTextMatrix(m_pdc, trans);
      CGContextSetRGBFillColor (m_pdc, pnanobrushText->m_color.dr(),
                                pnanobrushText->m_color.dg(),
                                pnanobrushText->m_color.db(),
                                pnanobrushText->m_color.da());

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

      CGContextShowTextAtPoint (m_pdc, x, y, str, str.length());

   }


   ::size_i32 nano_device::get_text_extents(const ::string & str, ::nano_font * pnanofont)
   {
      
      _select_font(pnanofont);

      CGContextSetTextPosition(m_pdc, 0, 0);
      CGContextSetTextDrawingMode (m_pdc, kCGTextInvisible);//5
      CGContextShowText (m_pdc, str, str.length());//10
      CGPoint pointSize = CGContextGetTextPosition(m_pdc);

      ::size_i32 size;
      
      size.cx() = pointSize.x;
      size.cy() = pnanofont->m_iFontSize;
      
      return size;

   }


   void nano_device::rectangle(const ::rectangle_i32 & rectangle, ::nano_brush * pnanobrush, ::nano_pen * pnanopen)
   {

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


   void nano_device::_set_source(const ::color::color & color)
   {


   }


   void nano_device::_set_fill_color(const ::color::color & color)
   {

      CGContextSetRGBFillColor(m_pdc, color.dr(), color.dg(), color.db(), color.da());

   }

   
   void nano_device::_select_font(::nano_font * pnanofont)
   {
      
      CGContextSelectFont (m_pdc,
                   pnanofont->m_strFontName.c_str(),
                   pnanofont->m_iFontSize,
                   kCGEncodingMacRoman);

   }


} // namespace quartz2d



