//
// Created by camilo on 31/01/2022 20:15 <3ThomasBorregaardSorensen!! Thomas Likes number 5!!
//
#include "framework.h"
#include "device.h"
#include "acid/nano/user/font.h"
#include "acid/nano/user/brush.h"
#include "acid/nano/user/pen.h"
#include "acid/primitive/geometry2d/rectangle.h"

namespace quartz2d
{

   namespace nano
   {

  
      namespace user
      {



   device::device()
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


   device::device(CGContextRef pdc)
   {
      
      m_bOwn = false;

      m_pdc = pdc;

   }


   device::~device()
   {
      
      if(m_bOwn)
      {

         if(m_pdc)
         {
          
            CGContextRelease(m_pdc);
            
         }
         
      }

   }


   void device::_draw_text(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano::user::brush * pnanobrushBack, ::nano::user::brush * pnanobrushText, ::nano::user::font * pnanofont)
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
      CGContextSetRGBFillColor (m_pdc, __expand_f32_rgba(pnanobrushText->m_color));

      double x = rectangleText.left();
      
      double y = rectangleText.top();

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


   ::size_i32 device::get_text_extents(const ::string & str, ::nano::user::font * pnanofont)
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


   void device::rectangle(const ::rectangle_i32 & rectangle, ::nano::user::brush * pnanobrush, ::nano::user::pen * pnanopen)
   {

      int iWidth = pnanopen ? pnanopen->m_iWidth : 0;

      CGRect rect;
      
      rect.origin.x = rectangle.left();
      rect.origin.y = rectangle.top();
      rect.size.width = rectangle.width();
      rect.size.height = rectangle.height();

      if (pnanobrush && pnanobrush->m_color.has_opacity())
      {
   
         _set_fill_color(pnanobrush->m_color);

         CGContextFillRect(m_pdc, rect);

      }

      if(iWidth > 0)
      {
         
         CGContextBeginPath(m_pdc);
         
         CGContextAddRect(m_pdc, rect);
         
         CGContextSetRGBStrokeColor(m_pdc, __expand_f32_rgba(pnanopen->m_color));
         
         CGContextSetLineWidth(m_pdc, pnanopen->m_iWidth);
         
         CGContextStrokePath(m_pdc);

      }

   }


   void device::_set_source(const ::color::color & color)
   {


   }


   void device::_set_fill_color(const ::color::color & color)
   {

      CGContextSetRGBFillColor(m_pdc, __expand_f32_rgba(color));

   }

   
   void device::_select_font(::nano::user::font * pnanofont)
   {
      
      CGContextSelectFont (m_pdc,
                   pnanofont->m_strFontName.c_str(),
                   pnanofont->m_iFontSize,
                   kCGEncodingMacRoman);

   }



      } //namespace user


   } //namespace nano


} // namespace quartz2d



