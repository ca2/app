// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
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

      ::i32_rectangle fbRect(m_size);
      copyFrom(fbRect, pframebufferSource, fbRect.left, fbRect.top);

      return true;
   }

   void Framebuffer::setColor(::u8 red, ::u8 green, ::u8 blue)
   {
      if (!m_buffer)
      {
         return;

      }
      size_t sizeInPixels = m_size.area();
      if (!sizeInPixels)
      {
         return;

      }
      ::i32 pixelSize = m_pixelformat.bitsPerPixel / 8;
      if (!pixelSize)
      {
         return;

      }
      ::u32 redPix = (red * m_pixelformat.redMax / 255) <<
                      m_pixelformat.redShift;
      ::u32 greenPix = (green * m_pixelformat.greenMax / 255) <<
                        m_pixelformat.greenShift;
      ::u32 bluePix = (blue * m_pixelformat.blueMax / 255) <<
                       m_pixelformat.blueShift;
      ::u32 color = redPix | greenPix | bluePix;

      ::u8 *endPixPtr = (::u8 *)m_buffer + getBufferSize();
      ::u8 *pixPtr = (::u8 *)m_buffer;
      for (; pixPtr <= endPixPtr - pixelSize; pixPtr += pixelSize) {
         memcpy(pixPtr, &color, pixelSize);
      }
   }

   void Framebuffer::fillRect(const ::i32_rectangle & rectangleTarget, ::u32 color)
   {
      ::i32_rectangle clipRect = ::i32_rectangle(m_size).intersection(rectangleTarget);

      ::i32 pixelSize = getBytesPerPixel();
      size_t sizeLineFb = getBytesPerRow();
      size_t sizeLineRect = clipRect.width() * pixelSize;

      // it's pointer to first line of rect
      ::u8 *srcLinePtr = reinterpret_cast<::u8 *>(getBufferPtr(clipRect.left, clipRect.top));

      // it's pointer to pixel in first line
      ::u8 *pixPtr = srcLinePtr;
      for (::i32 x = clipRect.left; x < clipRect.right; x++, pixPtr += pixelSize)
         memcpy(pixPtr, &color, pixelSize);

      // it's pointer to next line of rect
      ::u8 *dstLinePtr = srcLinePtr + sizeLineFb;
      for (::i32 y = clipRect.top + 1; y < clipRect.bottom; y++, dstLinePtr += sizeLineFb)
         memcpy(dstLinePtr, srcLinePtr, sizeLineRect);
   }

   bool Framebuffer::isEqualTo(const Framebuffer * pframebuffer)
   {
      return m_size == pframebuffer->getDimension() &&
             m_pixelformat == pframebuffer->getPixelFormat();
   }

   void Framebuffer::clipRect(const ::i32_rectangle & rectangleTarget, const Framebuffer * pframebufferSource,
                              const ::i32 srcX, const ::i32 srcY,
                              ::i32_rectangle & rectangleTargetClipped, ::i32_rectangle & rectangleSourceClipped)
   {
      ::i32_rectangle srcBufferRect(pframebufferSource->getDimension());
      clipRect(rectangleTarget, srcBufferRect, srcX, srcY, rectangleTargetClipped, rectangleSourceClipped);
   }

   void Framebuffer::clipRect(const ::i32_rectangle & rectangleTarget, const ::i32_rectangle & srcBufferRect,
                              const ::i32 srcX, const ::i32 srcY,
                              ::i32_rectangle & rectangleTargetClipped, ::i32_rectangle & rectangleSourceClipped)
   {
      ::i32_rectangle dstBufferRect(m_size);

      // Building srcRect
      ::i32_rectangle srcRect(srcX, srcY, srcX + rectangleTarget.width(), srcY + rectangleTarget.height());

      // Finding common area between the rectangleTarget, srcRect and the Framebuffers
      ::i32_rectangle dstRectFB = dstBufferRect.intersection(rectangleTarget);
      ::i32_rectangle srcRectFB = srcBufferRect.intersection(srcRect);

      // Finding common area between the dstRectFB and the srcRectFB
      ::i32_rectangle dstCommonArea(dstRectFB);
      ::i32_rectangle srcCommonArea(srcRectFB);
      // Move to common place (left = 0, top = 0)
      dstCommonArea.offset(-rectangleTarget.left, -rectangleTarget.top);
      srcCommonArea.offset(-srcRect.left, -srcRect.top);

      ::i32_rectangle commonRect(dstCommonArea.intersection(srcCommonArea));

      // Moving commonRect to destination coordinates and source
      rectangleTargetClipped.set(commonRect);
      rectangleTargetClipped.offset(rectangleTarget.left, rectangleTarget.top);

      rectangleSourceClipped.set(commonRect);
      rectangleSourceClipped.offset(srcRect.left, srcRect.top);
   }

   bool Framebuffer::overlay(const ::i32_rectangle & rectangleTarget,
                             const Framebuffer * pframebufferSource,
                             ::i32 srcX, ::i32 srcY,
                             const_char_pointer andMask)
   {
      if (m_pixelformat != pframebufferSource->getPixelFormat()) {
         return false;
      }
      if (m_pixelformat.bitsPerPixel == 32) {
         return overlayT<::u32>(rectangleTarget, pframebufferSource, srcX, srcY, andMask);
      } else if (m_pixelformat.bitsPerPixel == 16) {
         return overlayT<::u16>(rectangleTarget, pframebufferSource, srcX, srcY, andMask);
      } else if (m_pixelformat.bitsPerPixel == 8) {
         return overlayT<::u8>(rectangleTarget, pframebufferSource, srcX, srcY, andMask);
      } else {
         ASSERT(false);
      }
      return false;
   }

   template<class PIXEL_T> bool Framebuffer::overlayT(const ::i32_rectangle & rectangleTarget,
                                                      const Framebuffer * pframebufferSource,
                                                      ::i32 srcX, ::i32 srcY,
                                                      const_char_pointer andMask)
   {
      ::i32_rectangle rectangleSourceClipped, rectangleTargetClipped;

      clipRect(rectangleTarget, pframebufferSource, srcX, srcY, rectangleTargetClipped, rectangleSourceClipped);
      if (rectangleTargetClipped.area() <= 0 || rectangleSourceClipped.area() <= 0) {
         return true;
      }

      PIXEL_T *dstPixels = (PIXEL_T *)getBuffer();
      PIXEL_T *srcPixels = (PIXEL_T *)pframebufferSource->getBuffer();
      ::i32 srcWidth = pframebufferSource->getDimension().cx;
      ::i32 dstWidth = getDimension().cx;
      size_t bytesPerRow = (srcWidth + 7) / 8;
      for (::i32 iRow = rectangleSourceClipped.top; iRow < rectangleSourceClipped.bottom; iRow++) {
         for (::i32 iCol = rectangleSourceClipped.left; iCol < rectangleSourceClipped.right; iCol++) {
            ::u8 curByte = andMask[iRow * bytesPerRow + iCol / 8];
            bool andBit = (curByte & 128 >> iCol % 8) != 0;
            if (andBit) {
               
               ::i32 iDstRow = rectangleTargetClipped.top + iRow - srcY - rectangleSourceClipped.top;
//#ifdef __APPLE__
//               iDstRow = m_size.height() - iDstRow - 1;
//#endif
               ::i32 iDstCol = rectangleTargetClipped.left + iCol - srcX - rectangleSourceClipped.left;
               dstPixels[iDstRow * dstWidth + iDstCol] = srcPixels[iRow * srcWidth + iCol];
            }
         }
      }
      return true;
   }

   bool Framebuffer::copyFrom(const ::i32_rectangle & rectangleTarget, const Framebuffer * pframebufferSource,
                              ::i32 srcX, ::i32 srcY)
   {
      if (m_pixelformat != pframebufferSource->getPixelFormat()) {
         return false;
      }

      ::i32_rectangle rectangleSourceClipped, rectangleTargetClipped;

      clipRect(rectangleTarget, pframebufferSource, srcX, srcY, rectangleTargetClipped, rectangleSourceClipped);
      if (rectangleTargetClipped.area() <= 0 || rectangleSourceClipped.area() <= 0) {
         return true;
      }

      // Shortcuts
      ::i32 pixelSize = m_pixelformat.bitsPerPixel / 8;
      ::i32 dstStrideBytes = m_size.cx * pixelSize;
      ::i32 srcStrideBytes = pframebufferSource->getDimension().cx * pixelSize;

      ::i32 resultHeight = rectangleTargetClipped.height();
      ::i32 resultWidthBytes = rectangleTargetClipped.width() * pixelSize;

      ::i32 iDstRow = rectangleTargetClipped.top;
//#ifdef __APPLE__
  //             iDstRow = m_size.height() - iDstRow - resultHeight;
//#endif

      ::u8 *pdst = (::u8 *)m_buffer
                    + iDstRow * dstStrideBytes
                    + pixelSize * rectangleTargetClipped.left;

      ::u8 *psrc = (::u8 *)pframebufferSource->getBuffer()
                    + rectangleSourceClipped.top * srcStrideBytes
                    + pixelSize * rectangleSourceClipped.left;

      for (::i32 i = 0; i < resultHeight; i++, pdst += dstStrideBytes, psrc += srcStrideBytes) {
         memcpy(pdst, psrc, resultWidthBytes);
      }

      return true;
   }

   bool Framebuffer::copyFrom(const Framebuffer * pframebufferSource,
                              ::i32 srcX, ::i32 srcY)
   {
      return copyFrom(m_size, pframebufferSource, srcX, srcY);
   }

   bool Framebuffer::copyFromRotated90(const ::i32_rectangle & rectangleTarget, const Framebuffer * pframebufferSource,
                                       ::i32 srcX, ::i32 srcY)
   {
      if (m_pixelformat.bitsPerPixel != 32 || m_pixelformat != pframebufferSource->getPixelFormat())
      {
         return false;
      }

      // Shortcuts
      ::i32 pixelSize = m_pixelformat.bitsPerPixel / 8;
      ::i32 dstStrideBytesByX = m_size.cx * pixelSize;
      ::i32 srcStrideBytes = pframebufferSource->getDimension().cx * pixelSize;

      ::i32_rectangle rectangleSourceClipped, rectangleTargetClipped;

      ::i32_size srcBuffTransposedDim = pframebufferSource->getDimension().transposed();
      ::i32_rectangle srcBuffTransposedRect = srcBuffTransposedDim;
      ::i32_rectangle srcRotatedCoordinates(srcX, srcY, srcX + rectangleTarget.height(), srcY + rectangleTarget.width());
      srcRotatedCoordinates.rotateOn90InsideDimension(pframebufferSource->getDimension().cy);
      ::i32 srcXinDstRotation = srcRotatedCoordinates.left;
      ::i32 srcYinDstRotation = srcRotatedCoordinates.top;
      clipRect(rectangleTarget, srcBuffTransposedRect, srcXinDstRotation, srcYinDstRotation, rectangleTargetClipped, rectangleSourceClipped);
      if (rectangleTargetClipped.area() <= 0 || rectangleSourceClipped.area() <= 0) {
         return true;
      }
      // Rotate source rect back in source rotation.
      rectangleSourceClipped.rotateOn270InsideDimension(srcBuffTransposedDim.cx);

      ::i32 resultHeight = rectangleSourceClipped.height();
      ::i32 resultWidth = rectangleSourceClipped.width();

      ::u8 *pBaseDst = (::u8 *)m_buffer
                        + rectangleTargetClipped.top * dstStrideBytesByX
                        + pixelSize * (rectangleTargetClipped.right - 1);

      ::u8 *pBaseSrc = (::u8 *)pframebufferSource->getBuffer()
                        + rectangleSourceClipped.top * srcStrideBytes
                        + pixelSize * rectangleSourceClipped.left;

      for (::i32 iRow = 0; iRow < resultHeight; iRow++, pBaseDst -= pixelSize, pBaseSrc += srcStrideBytes) {
         ::u32 *pSrc = (::u32 *)pBaseSrc;
         ::u8 *pDst = pBaseDst;
         for (::i32 iCol = 0; iCol < resultWidth; iCol++, pSrc++, pDst += dstStrideBytesByX) {
            *(::u32 *)pDst = *pSrc;
         }
      }

      return true;
   }

   bool Framebuffer::copyFromRotated180(const ::i32_rectangle & rectangleTarget, const Framebuffer * pframebufferSource,
                                       ::i32 srcX, ::i32 srcY)
   {
      if (m_pixelformat.bitsPerPixel != 32 || m_pixelformat != pframebufferSource->getPixelFormat())
      {
         return false;
      }

      // Shortcuts
      ::i32 pixelSize = m_pixelformat.bitsPerPixel / 8;
      ::i32 dstStrideBytesByX = m_size.cx * pixelSize;
      ::i32 srcStrideBytes = pframebufferSource->getDimension().cx * pixelSize;

      ::i32_rectangle rectangleSourceClipped, rectangleTargetClipped;

      ::i32_size srcBuffTransposedDim = pframebufferSource->getDimension();
      ::i32_rectangle srcBuffTransposedRect = srcBuffTransposedDim;
      ::i32_rectangle srcRotatedCoordinates(srcX, srcY, srcX + rectangleTarget.width(), srcY + rectangleTarget.height());
      srcRotatedCoordinates.rotateOn180InsideDimension(pframebufferSource->getDimension().cx,
                                                       pframebufferSource->getDimension().cy);
      ::i32 srcXinDstRotation = srcRotatedCoordinates.left;
      ::i32 srcYinDstRotation = srcRotatedCoordinates.top;
      clipRect(rectangleTarget, srcBuffTransposedRect, srcXinDstRotation, srcYinDstRotation, rectangleTargetClipped, rectangleSourceClipped);
      if (rectangleTargetClipped.area() <= 0 || rectangleSourceClipped.area() <= 0) {
         return true;
      }
      // Rotate source rect back in source rotation.
      rectangleSourceClipped.rotateOn180InsideDimension(pframebufferSource->getDimension().cx,
                                                pframebufferSource->getDimension().cy);

      ::i32 resultHeight = rectangleSourceClipped.height();
      ::i32 resultWidth = rectangleSourceClipped.width();

      ::u8 *pBaseDst = (::u8 *)m_buffer
        + (rectangleTargetClipped.bottom - 1) * dstStrideBytesByX
        + pixelSize * (rectangleTargetClipped.right - 1);

      ::u8 *pBaseSrc = (::u8 *)pframebufferSource->getBuffer()
        + rectangleSourceClipped.top * srcStrideBytes
        + pixelSize * rectangleSourceClipped.left;

      for (::i32 iRow = 0; iRow < resultHeight; iRow++, pBaseDst -= dstStrideBytesByX , pBaseSrc += srcStrideBytes) {
         ::u32 *pSrc = (::u32 *)pBaseSrc;
         ::u32 *pDst = (::u32 *)pBaseDst;
         for (::i32 iCol = 0; iCol < resultWidth; iCol++, pSrc++, pDst--) {
            *(::u32 *)pDst = *pSrc;
         }
      }

      return true;
   }

   bool Framebuffer::copyFromRotated270(const ::i32_rectangle & rectangleTarget, const Framebuffer * pframebufferSource,
                                       ::i32 srcX, ::i32 srcY)
   {
      if (m_pixelformat.bitsPerPixel != 32 || m_pixelformat != pframebufferSource->getPixelFormat())
      {
         return false;
      }

      // Shortcuts
      ::i32 pixelSize = m_pixelformat.bitsPerPixel / 8;
      ::i32 dstStrideBytesByX = m_size.cx * pixelSize;
      ::i32 srcStrideBytes = pframebufferSource->getDimension().cx * pixelSize;

      ::i32_rectangle rectangleSourceClipped, rectangleTargetClipped;

      ::i32_size srcBuffTransposedDim = pframebufferSource->getDimension().transposed();
      ::i32_rectangle srcBuffTransposedRect = srcBuffTransposedDim;
      ::i32_rectangle srcRotatedCoordinates(srcX, srcY, srcX + rectangleTarget.height(), srcY + rectangleTarget.width());
      srcRotatedCoordinates.rotateOn270InsideDimension(pframebufferSource->getDimension().cx);
      ::i32 srcXinDstRotation = srcRotatedCoordinates.left;
      ::i32 srcYinDstRotation = srcRotatedCoordinates.top;
      clipRect(rectangleTarget, srcBuffTransposedRect, srcXinDstRotation, srcYinDstRotation, rectangleTargetClipped, rectangleSourceClipped);
      if (rectangleTargetClipped.area() <= 0 || rectangleSourceClipped.area() <= 0) {
         return true;
      }
      // Rotate source rect back in source rotation.
      rectangleSourceClipped.rotateOn90InsideDimension(srcBuffTransposedDim.cy);

      ::i32 resultHeight = rectangleSourceClipped.height();
      ::i32 resultWidth = rectangleSourceClipped.width();

      ::u8 *pBaseDst = (::u8 *)m_buffer
        + (rectangleTargetClipped.bottom - 1) * dstStrideBytesByX
        + pixelSize * rectangleTargetClipped.left;

      ::u8 *pBaseSrc = (::u8 *)pframebufferSource->getBuffer()
        + rectangleSourceClipped.top * srcStrideBytes
        + pixelSize * rectangleSourceClipped.left;

      for (::i32 iRow = 0; iRow < resultHeight; iRow++, pBaseDst += pixelSize, pBaseSrc += srcStrideBytes) {
         ::u32 *pSrc = (::u32 *)pBaseSrc;
         ::u8 *pDst = pBaseDst;
         for (::i32 iCol = 0; iCol < resultWidth; iCol++, pSrc++, pDst -= dstStrideBytesByX) {
            *(::u32 *)pDst = *pSrc;
         }
      }

      return true;
   }

   bool Framebuffer::cmpFrom(const ::i32_rectangle & rectangleTarget, const Framebuffer * pframebufferSource,
                             const ::i32 srcX, const ::i32 srcY)
   {
      if (m_pixelformat != pframebufferSource->getPixelFormat())
      {
         return false;
      }

      ::i32_rectangle rectangleSourceClipped, rectangleTargetClipped;

      clipRect(rectangleTarget, pframebufferSource, srcX, srcY, rectangleTargetClipped, rectangleSourceClipped);
      if (rectangleTargetClipped.area() <= 0 || rectangleSourceClipped.area() <= 0) {
         return true;
      }

      // Shortcuts
      ::i32 pixelSize = m_pixelformat.bitsPerPixel / 8;
      ::i32 dstStrideBytes = m_size.cx * pixelSize;
      ::i32 srcStrideBytes = pframebufferSource->getDimension().cx * pixelSize;

      ::i32 resultHeight = rectangleTargetClipped.height();
      ::i32 resultWidthBytes = rectangleTargetClipped.width() * pixelSize;

      ::u8 *pdst = (::u8 *)m_buffer
                    + rectangleTargetClipped.top * dstStrideBytes
                    + pixelSize * rectangleTargetClipped.left;

      ::u8 *psrc = (::u8 *)pframebufferSource->getBuffer()
                    + rectangleSourceClipped.top * srcStrideBytes
                    + pixelSize * rectangleSourceClipped.left;

      for (::i32 i = 0; i < resultHeight; i++, pdst += dstStrideBytes, psrc += srcStrideBytes) {
         if (memcmp(pdst, psrc, resultWidthBytes) != 0) {
            return false;
         }
      }

      return true;
   }

   void Framebuffer::move(const ::i32_rectangle & rectangleTarget, const ::i32 srcX, const ::i32 srcY)
   {
      ::i32_rectangle rectangleSourceClipped, rectangleTargetClipped;

      clipRect(rectangleTarget, this, srcX, srcY, rectangleTargetClipped, rectangleSourceClipped);
      if (rectangleTargetClipped.area() <= 0 || rectangleSourceClipped.area() <= 0) {
         return;
      }

      // Data copy
      ::i32 pixelSize = m_pixelformat.bitsPerPixel / 8;
      ::i32 strideBytes = m_size.cx * pixelSize;

      ::i32 resultHeight = rectangleTargetClipped.height();
      ::i32 resultWidthBytes = rectangleTargetClipped.width() * pixelSize;

      ::u8 *pdst, *psrc;

      if (srcY > rectangleTarget.top) {
         // Pointers set to first string of the rectanles
         pdst = (::u8 *)m_buffer + rectangleTargetClipped.top * strideBytes
                + pixelSize * rectangleTargetClipped.left;
         psrc = (::u8 *)m_buffer + rectangleSourceClipped.top * strideBytes
                + pixelSize * rectangleSourceClipped.left;

         for (::i32 i = 0; i < resultHeight; i++, pdst += strideBytes, psrc += strideBytes) {
            memcpy(pdst, psrc, resultWidthBytes);
         }

      } else {
         // Pointers set to last string of the rectanles
         pdst = (::u8 *)m_buffer + (rectangleTargetClipped.bottom - 1) * strideBytes
                + pixelSize * rectangleTargetClipped.left;
         psrc = (::u8 *)m_buffer + (rectangleSourceClipped.bottom - 1) * strideBytes
                + pixelSize * rectangleSourceClipped.left;

         for (::i32 i = resultHeight - 1; i >= 0; i--, pdst -= strideBytes, psrc -= strideBytes) {
            memmove(pdst, psrc, resultWidthBytes);
         }
      }
   }

   bool Framebuffer::setPixelFormat(const PixelFormat & pixelFormat)
   {
      m_pixelformat = pixelFormat;
      return resizeBuffer();
   }

   bool Framebuffer::setDimension(const ::i32_size & newDim)
   {
      m_size = newDim;
      return resizeBuffer();
   }

   void Framebuffer::setEmptyDimension(const ::i32_rectangle & dimByRect)
   {
      m_size = dimByRect.size();
   }

   void Framebuffer::setEmptyPixelFmt(const PixelFormat & pf)
   {
      m_pixelformat = pf;
   }

   void Framebuffer::setPropertiesWithoutResize(const ::i32_size & newDim, const PixelFormat & pf)
   {
      m_size = newDim;
      m_pixelformat = pf;
   }

   bool Framebuffer::setProperties(const ::i32_size & newDim,
                                   const PixelFormat & pixelFormat)
   {
      m_pixelformat = pixelFormat;
      m_size = newDim;
      return resizeBuffer();
   }

   bool Framebuffer::setProperties(const ::i32_rectangle & dimByRect,
                                   const PixelFormat & pixelFormat)
   {
      m_pixelformat = pixelFormat;
      m_size = dimByRect.size();
      return resizeBuffer();
   }

   ::u8 Framebuffer::getBitsPerPixel() const
   {
      ASSERT((::u8)m_pixelformat.bitsPerPixel == m_pixelformat.bitsPerPixel);
      return (::u8)m_pixelformat.bitsPerPixel;
   }

   ::i32 Framebuffer::getBufferSize() const
   {
      return (::i32)((::u64)m_size.area() * m_pixelformat.bitsPerPixel / 8);
   }

   bool Framebuffer::resizeBuffer()
   {
      if (m_buffer != 0) {
         delete []m_buffer;
      }
      if ((m_buffer = new ::u8[getBufferSize()]) == 0) {
         return false;
      }
      return true;
   }
} // namespace innate_subsystem

