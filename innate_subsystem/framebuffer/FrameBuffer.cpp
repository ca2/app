// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "Framebuffer.h"
// #include aaa_<string.h>


namespace innate_subsystem
{
   Framebuffer::Framebuffer(void)
   : m_buffer(0)
   {
      memset(&m_pixelformat, 0, sizeof(m_pixelformat));
   }

   Framebuffer::~Framebuffer(void)
   {
      if (m_buffer != 0) {
         delete []m_buffer;
      }
   }

   bool Framebuffer::assignProperties(const Framebuffer * pframebufferSource)
   {
      setProperties(pframebufferSource->getDimension(),
                    pframebufferSource->getPixelFormat());
      return resizeBuffer();
   }

   bool Framebuffer::clone(const Framebuffer * pframebufferSource)
   {
      if (!assignProperties(pframebufferSource)) {
         return false;
      }

      ::int_rectangle fbRect(m_dimension);
      copyFrom(fbRect, pframebufferSource, fbRect.left, fbRect.top);

      return true;
   }

   void Framebuffer::setColor(unsigned char red, unsigned char green, unsigned char blue)
   {
      size_t sizeInPixels = m_dimension.area();
      int pixelSize = m_pixelformat.bitsPerPixel / 8;
      unsigned int redPix = (red * m_pixelformat.redMax / 255) <<
                      m_pixelformat.redShift;
      unsigned int greenPix = (green * m_pixelformat.greenMax / 255) <<
                        m_pixelformat.greenShift;
      unsigned int bluePix = (blue * m_pixelformat.blueMax / 255) <<
                       m_pixelformat.blueShift;
      unsigned int color = redPix | greenPix | bluePix;

      unsigned char *endPixPtr = (unsigned char *)m_buffer + getBufferSize();
      unsigned char *pixPtr = (unsigned char *)m_buffer;
      for (; pixPtr <= endPixPtr - pixelSize; pixPtr += pixelSize) {
         memcpy(pixPtr, &color, pixelSize);
      }
   }

   void Framebuffer::fillRect(const ::int_rectangle & rectangleTarget, unsigned int color)
   {
      ::int_rectangle clipRect = ::int_rectangle(m_dimension).intersection(rectangleTarget);

      int pixelSize = getBytesPerPixel();
      size_t sizeLineFb = getBytesPerRow();
      size_t sizeLineRect = clipRect.width() * pixelSize;

      // it's pointer to first line of rect
      unsigned char *srcLinePtr = reinterpret_cast<unsigned char *>(getBufferPtr(clipRect.left, clipRect.top));

      // it's pointer to pixel in first line
      unsigned char *pixPtr = srcLinePtr;
      for (int x = clipRect.left; x < clipRect.right; x++, pixPtr += pixelSize)
         memcpy(pixPtr, &color, pixelSize);

      // it's pointer to next line of rect
      unsigned char *dstLinePtr = srcLinePtr + sizeLineFb;
      for (int y = clipRect.top + 1; y < clipRect.bottom; y++, dstLinePtr += sizeLineFb)
         memcpy(dstLinePtr, srcLinePtr, sizeLineRect);
   }

   bool Framebuffer::isEqualTo(const Framebuffer * pframebuffer)
   {
      return m_dimension == pframebuffer->getDimension() &&
             m_pixelformat == pframebuffer->getPixelFormat();
   }

   void Framebuffer::clipRect(const ::int_rectangle & rectangleTarget, const Framebuffer * pframebufferSource,
                              const int srcX, const int srcY,
                              ::int_rectangle & rectangleTargetClipped, ::int_rectangle & rectangleSourceClipped)
   {
      ::int_rectangle srcBufferRect(pframebufferSource->getDimension());
      clipRect(rectangleTarget, srcBufferRect, srcX, srcY, rectangleTargetClipped, rectangleSourceClipped);
   }

   void Framebuffer::clipRect(const ::int_rectangle & rectangleTarget, const ::int_rectangle & srcBufferRect,
                              const int srcX, const int srcY,
                              ::int_rectangle & rectangleTargetClipped, ::int_rectangle & rectangleSourceClipped)
   {
      ::int_rectangle dstBufferRect(m_dimension);

      // Building srcRect
      ::int_rectangle srcRect(srcX, srcY, srcX + rectangleTarget.width(), srcY + rectangleTarget.height());

      // Finding common area between the rectangleTarget, srcRect and the Framebuffers
      ::int_rectangle dstRectFB = dstBufferRect.intersection(rectangleTarget);
      ::int_rectangle srcRectFB = srcBufferRect.intersection(srcRect);

      // Finding common area between the dstRectFB and the srcRectFB
      ::int_rectangle dstCommonArea(dstRectFB);
      ::int_rectangle srcCommonArea(srcRectFB);
      // Move to common place (left = 0, top = 0)
      dstCommonArea.offset(-rectangleTarget.left, -rectangleTarget.top);
      srcCommonArea.offset(-srcRect.left, -srcRect.top);

      ::int_rectangle commonRect(dstCommonArea.intersection(srcCommonArea));

      // Moving commonRect to destination coordinates and source
      rectangleTargetClipped.set(commonRect);
      rectangleTargetClipped.offset(rectangleTarget.left, rectangleTarget.top);

      rectangleSourceClipped.set(commonRect);
      rectangleSourceClipped.offset(srcRect.left, srcRect.top);
   }

   bool Framebuffer::overlay(const ::int_rectangle & rectangleTarget,
                             const Framebuffer * pframebufferSource,
                             int srcX, int srcY,
                             const char *andMask)
   {
      if (m_pixelformat != pframebufferSource->getPixelFormat()) {
         return false;
      }
      if (m_pixelformat.bitsPerPixel == 32) {
         return overlayT<unsigned int>(rectangleTarget, pframebufferSource, srcX, srcY, andMask);
      } else if (m_pixelformat.bitsPerPixel == 16) {
         return overlayT<unsigned short>(rectangleTarget, pframebufferSource, srcX, srcY, andMask);
      } else if (m_pixelformat.bitsPerPixel == 8) {
         return overlayT<unsigned char>(rectangleTarget, pframebufferSource, srcX, srcY, andMask);
      } else {
         _ASSERT(false);
      }
      return false;
   }

   template<class PIXEL_T> bool Framebuffer::overlayT(const ::int_rectangle & rectangleTarget,
                                                      const Framebuffer * pframebufferSource,
                                                      int srcX, int srcY,
                                                      const char *andMask)
   {
      ::int_rectangle rectangleSourceClipped, rectangleTargetClipped;

      clipRect(rectangleTarget, pframebufferSource, srcX, srcY, rectangleTargetClipped, rectangleSourceClipped);
      if (rectangleTargetClipped.area() <= 0 || rectangleSourceClipped.area() <= 0) {
         return true;
      }

      PIXEL_T *dstPixels = (PIXEL_T *)getBuffer();
      PIXEL_T *srcPixels = (PIXEL_T *)pframebufferSource->getBuffer();
      int srcWidth = pframebufferSource->getDimension().cx;
      int dstWidth = getDimension().cx;
      size_t bytesPerRow = (srcWidth + 7) / 8;
      for (int iRow = rectangleSourceClipped.top; iRow < rectangleSourceClipped.bottom; iRow++) {
         for (int iCol = rectangleSourceClipped.left; iCol < rectangleSourceClipped.right; iCol++) {
            unsigned char curByte = andMask[iRow * bytesPerRow + iCol / 8];
            bool andBit = (curByte & 128 >> iCol % 8) != 0;
            if (andBit) {
               int iDstRow = rectangleTargetClipped.top + iRow - srcY - rectangleSourceClipped.top;
               int iDstCol = rectangleTargetClipped.left + iCol - srcX - rectangleSourceClipped.left;
               dstPixels[iDstRow * dstWidth + iDstCol] = srcPixels[iRow * srcWidth + iCol];
            }
         }
      }
      return true;
   }

   bool Framebuffer::copyFrom(const ::int_rectangle & rectangleTarget, const Framebuffer * pframebufferSource,
                              int srcX, int srcY)
   {
      if (m_pixelformat != pframebufferSource->getPixelFormat()) {
         return false;
      }

      ::int_rectangle rectangleSourceClipped, rectangleTargetClipped;

      clipRect(rectangleTarget, pframebufferSource, srcX, srcY, rectangleTargetClipped, rectangleSourceClipped);
      if (rectangleTargetClipped.area() <= 0 || rectangleSourceClipped.area() <= 0) {
         return true;
      }

      // Shortcuts
      int pixelSize = m_pixelformat.bitsPerPixel / 8;
      int dstStrideBytes = m_dimension.cx * pixelSize;
      int srcStrideBytes = pframebufferSource->getDimension().cx * pixelSize;

      int resultHeight = rectangleTargetClipped.height();
      int resultWidthBytes = rectangleTargetClipped.width() * pixelSize;

      unsigned char *pdst = (unsigned char *)m_buffer
                    + rectangleTargetClipped.top * dstStrideBytes
                    + pixelSize * rectangleTargetClipped.left;

      unsigned char *psrc = (unsigned char *)pframebufferSource->getBuffer()
                    + rectangleSourceClipped.top * srcStrideBytes
                    + pixelSize * rectangleSourceClipped.left;

      for (int i = 0; i < resultHeight; i++, pdst += dstStrideBytes, psrc += srcStrideBytes) {
         memcpy(pdst, psrc, resultWidthBytes);
      }

      return true;
   }

   bool Framebuffer::copyFrom(const Framebuffer * pframebufferSource,
                              int srcX, int srcY)
   {
      return copyFrom(m_dimension, pframebufferSource, srcX, srcY);
   }

   bool Framebuffer::copyFromRotated90(const ::int_rectangle & rectangleTarget, const Framebuffer * pframebufferSource,
                                       int srcX, int srcY)
   {
      if (m_pixelformat.bitsPerPixel != 32 || m_pixelformat != pframebufferSource->getPixelFormat())
      {
         return false;
      }

      // Shortcuts
      int pixelSize = m_pixelformat.bitsPerPixel / 8;
      int dstStrideBytesByX = m_dimension.cx * pixelSize;
      int srcStrideBytes = pframebufferSource->getDimension().cx * pixelSize;

      ::int_rectangle rectangleSourceClipped, rectangleTargetClipped;

      ::int_size srcBuffTransposedDim = pframebufferSource->getDimension().transposed();
      ::int_rectangle srcBuffTransposedRect = srcBuffTransposedDim;
      ::int_rectangle srcRotatedCoordinates(srcX, srcY, srcX + rectangleTarget.height(), srcY + rectangleTarget.width());
      srcRotatedCoordinates.rotateOn90InsideDimension(pframebufferSource->getDimension().cy);
      int srcXinDstRotation = srcRotatedCoordinates.left;
      int srcYinDstRotation = srcRotatedCoordinates.top;
      clipRect(rectangleTarget, srcBuffTransposedRect, srcXinDstRotation, srcYinDstRotation, rectangleTargetClipped, rectangleSourceClipped);
      if (rectangleTargetClipped.area() <= 0 || rectangleSourceClipped.area() <= 0) {
         return true;
      }
      // Rotate source rect back in source rotation.
      rectangleSourceClipped.rotateOn270InsideDimension(srcBuffTransposedDim.cx);

      int resultHeight = rectangleSourceClipped.height();
      int resultWidth = rectangleSourceClipped.width();

      unsigned char *pBaseDst = (unsigned char *)m_buffer
                        + rectangleTargetClipped.top * dstStrideBytesByX
                        + pixelSize * (rectangleTargetClipped.right - 1);

      unsigned char *pBaseSrc = (unsigned char *)pframebufferSource->getBuffer()
                        + rectangleSourceClipped.top * srcStrideBytes
                        + pixelSize * rectangleSourceClipped.left;

      for (int iRow = 0; iRow < resultHeight; iRow++, pBaseDst -= pixelSize, pBaseSrc += srcStrideBytes) {
         unsigned int *pSrc = (unsigned int *)pBaseSrc;
         unsigned char *pDst = pBaseDst;
         for (int iCol = 0; iCol < resultWidth; iCol++, pSrc++, pDst += dstStrideBytesByX) {
            *(unsigned int *)pDst = *pSrc;
         }
      }

      return true;
   }

   bool Framebuffer::copyFromRotated180(const ::int_rectangle & rectangleTarget, const Framebuffer * pframebufferSource,
                                       int srcX, int srcY)
   {
      if (m_pixelformat.bitsPerPixel != 32 || m_pixelformat != pframebufferSource->getPixelFormat())
      {
         return false;
      }

      // Shortcuts
      int pixelSize = m_pixelformat.bitsPerPixel / 8;
      int dstStrideBytesByX = m_dimension.cx * pixelSize;
      int srcStrideBytes = pframebufferSource->getDimension().cx * pixelSize;

      ::int_rectangle rectangleSourceClipped, rectangleTargetClipped;

      ::int_size srcBuffTransposedDim = pframebufferSource->getDimension();
      ::int_rectangle srcBuffTransposedRect = srcBuffTransposedDim;
      ::int_rectangle srcRotatedCoordinates(srcX, srcY, srcX + rectangleTarget.width(), srcY + rectangleTarget.height());
      srcRotatedCoordinates.rotateOn180InsideDimension(pframebufferSource->getDimension().cx,
                                                       pframebufferSource->getDimension().cy);
      int srcXinDstRotation = srcRotatedCoordinates.left;
      int srcYinDstRotation = srcRotatedCoordinates.top;
      clipRect(rectangleTarget, srcBuffTransposedRect, srcXinDstRotation, srcYinDstRotation, rectangleTargetClipped, rectangleSourceClipped);
      if (rectangleTargetClipped.area() <= 0 || rectangleSourceClipped.area() <= 0) {
         return true;
      }
      // Rotate source rect back in source rotation.
      rectangleSourceClipped.rotateOn180InsideDimension(pframebufferSource->getDimension().cx,
                                                pframebufferSource->getDimension().cy);

      int resultHeight = rectangleSourceClipped.height();
      int resultWidth = rectangleSourceClipped.width();

      unsigned char *pBaseDst = (unsigned char *)m_buffer
        + (rectangleTargetClipped.bottom - 1) * dstStrideBytesByX
        + pixelSize * (rectangleTargetClipped.right - 1);

      unsigned char *pBaseSrc = (unsigned char *)pframebufferSource->getBuffer()
        + rectangleSourceClipped.top * srcStrideBytes
        + pixelSize * rectangleSourceClipped.left;

      for (int iRow = 0; iRow < resultHeight; iRow++, pBaseDst -= dstStrideBytesByX , pBaseSrc += srcStrideBytes) {
         unsigned int *pSrc = (unsigned int *)pBaseSrc;
         unsigned int *pDst = (unsigned int *)pBaseDst;
         for (int iCol = 0; iCol < resultWidth; iCol++, pSrc++, pDst--) {
            *(unsigned int *)pDst = *pSrc;
         }
      }

      return true;
   }

   bool Framebuffer::copyFromRotated270(const ::int_rectangle & rectangleTarget, const Framebuffer * pframebufferSource,
                                       int srcX, int srcY)
   {
      if (m_pixelformat.bitsPerPixel != 32 || m_pixelformat != pframebufferSource->getPixelFormat())
      {
         return false;
      }

      // Shortcuts
      int pixelSize = m_pixelformat.bitsPerPixel / 8;
      int dstStrideBytesByX = m_dimension.cx * pixelSize;
      int srcStrideBytes = pframebufferSource->getDimension().cx * pixelSize;

      ::int_rectangle rectangleSourceClipped, rectangleTargetClipped;

      ::int_size srcBuffTransposedDim = pframebufferSource->getDimension().transposed();
      ::int_rectangle srcBuffTransposedRect = srcBuffTransposedDim;
      ::int_rectangle srcRotatedCoordinates(srcX, srcY, srcX + rectangleTarget.height(), srcY + rectangleTarget.width());
      srcRotatedCoordinates.rotateOn270InsideDimension(pframebufferSource->getDimension().cx);
      int srcXinDstRotation = srcRotatedCoordinates.left;
      int srcYinDstRotation = srcRotatedCoordinates.top;
      clipRect(rectangleTarget, srcBuffTransposedRect, srcXinDstRotation, srcYinDstRotation, rectangleTargetClipped, rectangleSourceClipped);
      if (rectangleTargetClipped.area() <= 0 || rectangleSourceClipped.area() <= 0) {
         return true;
      }
      // Rotate source rect back in source rotation.
      rectangleSourceClipped.rotateOn90InsideDimension(srcBuffTransposedDim.cy);

      int resultHeight = rectangleSourceClipped.height();
      int resultWidth = rectangleSourceClipped.width();

      unsigned char *pBaseDst = (unsigned char *)m_buffer
        + (rectangleTargetClipped.bottom - 1) * dstStrideBytesByX
        + pixelSize * rectangleTargetClipped.left;

      unsigned char *pBaseSrc = (unsigned char *)pframebufferSource->getBuffer()
        + rectangleSourceClipped.top * srcStrideBytes
        + pixelSize * rectangleSourceClipped.left;

      for (int iRow = 0; iRow < resultHeight; iRow++, pBaseDst += pixelSize, pBaseSrc += srcStrideBytes) {
         unsigned int *pSrc = (unsigned int *)pBaseSrc;
         unsigned char *pDst = pBaseDst;
         for (int iCol = 0; iCol < resultWidth; iCol++, pSrc++, pDst -= dstStrideBytesByX) {
            *(unsigned int *)pDst = *pSrc;
         }
      }

      return true;
   }

   bool Framebuffer::cmpFrom(const ::int_rectangle & rectangleTarget, const Framebuffer * pframebufferSource,
                             const int srcX, const int srcY)
   {
      if (m_pixelformat != pframebufferSource->getPixelFormat())
      {
         return false;
      }

      ::int_rectangle rectangleSourceClipped, rectangleTargetClipped;

      clipRect(rectangleTarget, pframebufferSource, srcX, srcY, rectangleTargetClipped, rectangleSourceClipped);
      if (rectangleTargetClipped.area() <= 0 || rectangleSourceClipped.area() <= 0) {
         return true;
      }

      // Shortcuts
      int pixelSize = m_pixelformat.bitsPerPixel / 8;
      int dstStrideBytes = m_dimension.cx * pixelSize;
      int srcStrideBytes = pframebufferSource->getDimension().cx * pixelSize;

      int resultHeight = rectangleTargetClipped.height();
      int resultWidthBytes = rectangleTargetClipped.width() * pixelSize;

      unsigned char *pdst = (unsigned char *)m_buffer
                    + rectangleTargetClipped.top * dstStrideBytes
                    + pixelSize * rectangleTargetClipped.left;

      unsigned char *psrc = (unsigned char *)pframebufferSource->getBuffer()
                    + rectangleSourceClipped.top * srcStrideBytes
                    + pixelSize * rectangleSourceClipped.left;

      for (int i = 0; i < resultHeight; i++, pdst += dstStrideBytes, psrc += srcStrideBytes) {
         if (memcmp(pdst, psrc, resultWidthBytes) != 0) {
            return false;
         }
      }

      return true;
   }

   void Framebuffer::move(const ::int_rectangle & rectangleTarget, const int srcX, const int srcY)
   {
      ::int_rectangle rectangleSourceClipped, rectangleTargetClipped;

      clipRect(rectangleTarget, this, srcX, srcY, rectangleTargetClipped, rectangleSourceClipped);
      if (rectangleTargetClipped.area() <= 0 || rectangleSourceClipped.area() <= 0) {
         return;
      }

      // Data copy
      int pixelSize = m_pixelformat.bitsPerPixel / 8;
      int strideBytes = m_dimension.cx * pixelSize;

      int resultHeight = rectangleTargetClipped.height();
      int resultWidthBytes = rectangleTargetClipped.width() * pixelSize;

      unsigned char *pdst, *psrc;

      if (srcY > rectangleTarget.top) {
         // Pointers set to first string of the rectanles
         pdst = (unsigned char *)m_buffer + rectangleTargetClipped.top * strideBytes
                + pixelSize * rectangleTargetClipped.left;
         psrc = (unsigned char *)m_buffer + rectangleSourceClipped.top * strideBytes
                + pixelSize * rectangleSourceClipped.left;

         for (int i = 0; i < resultHeight; i++, pdst += strideBytes, psrc += strideBytes) {
            memcpy(pdst, psrc, resultWidthBytes);
         }

      } else {
         // Pointers set to last string of the rectanles
         pdst = (unsigned char *)m_buffer + (rectangleTargetClipped.bottom - 1) * strideBytes
                + pixelSize * rectangleTargetClipped.left;
         psrc = (unsigned char *)m_buffer + (rectangleSourceClipped.bottom - 1) * strideBytes
                + pixelSize * rectangleSourceClipped.left;

         for (int i = resultHeight - 1; i >= 0; i--, pdst -= strideBytes, psrc -= strideBytes) {
            memmove(pdst, psrc, resultWidthBytes);
         }
      }
   }

   bool Framebuffer::setPixelFormat(const PixelFormat & pixelFormat)
   {
      m_pixelformat = pixelFormat;
      return resizeBuffer();
   }

   bool Framebuffer::setDimension(const ::int_size & newDim)
   {
      m_dimension = newDim;
      return resizeBuffer();
   }

   void Framebuffer::setEmptyDimension(const ::int_rectangle & dimByRect)
   {
      m_dimension = dimByRect.size();
   }

   void Framebuffer::setEmptyPixelFmt(const PixelFormat & pf)
   {
      m_pixelformat = pf;
   }

   void Framebuffer::setPropertiesWithoutResize(const ::int_size & newDim, const PixelFormat & pf)
   {
      m_dimension = newDim;
      m_pixelformat = pf;
   }

   bool Framebuffer::setProperties(const ::int_size & newDim,
                                   const PixelFormat & pixelFormat)
   {
      m_pixelformat = pixelFormat;
      m_dimension = newDim;
      return resizeBuffer();
   }

   bool Framebuffer::setProperties(const ::int_rectangle & dimByRect,
                                   const PixelFormat & pixelFormat)
   {
      m_pixelformat = pixelFormat;
      m_dimension = dimByRect.size();
      return resizeBuffer();
   }

   unsigned char Framebuffer::getBitsPerPixel() const
   {
      _ASSERT((unsigned char)m_pixelformat.bitsPerPixel == m_pixelformat.bitsPerPixel);
      return (unsigned char)m_pixelformat.bitsPerPixel;
   }

   int Framebuffer::getBufferSize() const
   {
      return (int)((unsigned long long)m_dimension.area() * m_pixelformat.bitsPerPixel / 8);
   }

   bool Framebuffer::resizeBuffer()
   {
      if (m_buffer != 0) {
         delete []m_buffer;
      }
      if ((m_buffer = new unsigned char[getBufferSize()]) == 0) {
         return false;
      }
      return true;
   }
} // namespace innate_subsystem

