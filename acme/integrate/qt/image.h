//
// Created by camilo on 2024-09-27 18:10 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/graphics/image/pixmap.h"

#include <QPainter>


class qimage_paintable_pixmap :
   public pixmap
{

   QImage * m_pqimage;
   QImage m_qimageArgb32;
   QImage * m_pqimageArgb32;

   bool m_bConvert;


   qimage_paintable_pixmap(QImage * pqimage)
   {

      m_pqimage = pqimage;

      m_bConvert = pqimage->format() != QImage::Format_ARGB32;

      if(m_bConvert)
      {
         m_qimageArgb32 = pqimage->convertToFormat(QImage::Format_ARGB32);
         m_pqimageArgb32 = &m_qimageArgb32;
      }
      else
      {
         m_pqimageArgb32 = m_pqimage;
      }

      ::pixmap & pixmap = *this;

      pixmap.m_pimage32 = (image32_t *) m_pqimageArgb32->bits();
      pixmap.m_size.cx() = m_pqimageArgb32->width();
      pixmap.m_size.cy() = m_pqimageArgb32->height();
      pixmap.m_sizeRaw.cx() = m_pqimageArgb32->width();
      pixmap.m_sizeRaw.cy() = m_pqimageArgb32->height();
      pixmap.m_iScan = m_pqimageArgb32->bytesPerLine();
   }

   ~qimage_paintable_pixmap()
   {

      if(m_bConvert)
      {

         auto qimage = m_pqimageArgb32->convertToFormat(m_pqimage->format());

         // Now, both images should have the same format
         QPainter painter(m_pqimage);

         painter.drawImage(0, 0, qimage); // Paint at position (0, 0)


      }

   }


};


