// Copyright (C) 2012 GlavSoft LLC.
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
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#include "DibFrameBuffer.h"
#include "util/Exception.h"


namespace windows
{
   namespace subsystem
   {
      DibFrameBuffer::DibFrameBuffer()
      : m_dibSection(0)
      {
      }

      DibFrameBuffer::~DibFrameBuffer()
      {
         releaseDibSection();
      }

      void DibFrameBuffer::setTargetDC(HDC targetDC)
      {
         checkDibValid();
         m_dibSection->setTargetDC(targetDC);
      }

      bool DibFrameBuffer::assignProperties(const FrameBuffer *srcFrameBuffer)
      {
         throw Exception(_T("Wrong: You shouln't use the DibFrameBuffer::assignProperties() function."));
      }

      bool DibFrameBuffer::clone(const FrameBuffer *srcFrameBuffer)
      {
         throw Exception(_T("Wrong: You shouln't use the DibFrameBuffer::clone() function."));
      }

      void DibFrameBuffer::setColor(unsigned int8 reg, unsigned int8 green, unsigned int8 blue)
      {
         m_fb.setColor(reg, green, blue);
      }

      void DibFrameBuffer::fillRect(const ::int_rectangle &dstRect, unsigned int32 color)
      {
         m_fb.fillRect(dstRect, color);
      }

      bool DibFrameBuffer::isEqualTo(const FrameBuffer *frameBuffer)
      {
         return m_fb.isEqualTo(frameBuffer);
      }

      bool DibFrameBuffer::copyFrom(const ::int_rectangle &dstRect, const FrameBuffer *srcFrameBuffer,
                                    int srcX, int srcY)
      {
         return m_fb.copyFrom(dstRect, srcFrameBuffer, srcX, srcY);
      }

      bool DibFrameBuffer::copyFrom(const FrameBuffer *srcFrameBuffer, int srcX, int srcY)
      {
         return m_fb.copyFrom(srcFrameBuffer, srcX, srcY);
      }

      bool DibFrameBuffer::overlay(const ::int_rectangle &dstRect, const FrameBuffer *srcFrameBuffer,
                                   int srcX, int srcY, const char *andMask)
      {
         return m_fb.overlay(dstRect, srcFrameBuffer, srcX, srcY, andMask);
      }

      void DibFrameBuffer::move(const ::int_rectangle &dstRect, const int srcX, const int srcY)
      {
         m_fb.move(dstRect, srcX, srcY);
      }

      bool DibFrameBuffer::cmpFrom(const ::int_rectangle &dstRect, const FrameBuffer *srcFrameBuffer,
                                   const int srcX, const int srcY)
      {
         return m_fb.cmpFrom(dstRect, srcFrameBuffer, srcX, srcY);
      }

      bool DibFrameBuffer::setDimension(const Dimension *newDim)
      {
         throw Exception(_T("Wrong: You shouln't use the DibFrameBuffer::clone() function."));
      }

      bool DibFrameBuffer::setDimension(const ::int_rectangle &rect)
      {
         throw Exception(_T("Wrong: You shouln't use the DibFrameBuffer::clone() function."));
      }

      void DibFrameBuffer::setEmptyDimension(const ::int_rectangle &dimByRect)
      {
         throw Exception(_T("This function is deprecated"));
      }

      void DibFrameBuffer::setEmptyPixelFmt(const PixelFormat *pf)
      {
         throw Exception(_T("This function is deprecated"));
      }

      void DibFrameBuffer::setPropertiesWithoutResize(const Dimension *newDim, const PixelFormat *pf)
      {
         throw Exception(_T("Wrong: You shouln't use the DibFrameBuffer::setPropertiesWithoutResize() function."));
      }

      inline Dimension DibFrameBuffer::getDimension() const
      {
         return m_fb.getDimension();
      }

      bool DibFrameBuffer::setPixelFormat(const PixelFormat *pixelFormat)
      {
         throw Exception(_T("Wrong: You shouln't use the DibFrameBuffer::setPixelFormat() function."));
      }

      inline PixelFormat DibFrameBuffer::getPixelFormat() const
      {
         return m_fb.getPixelFormat();
      }

      bool DibFrameBuffer::setProperties(const Dimension *newDim, const PixelFormat *pixelFormat)
      {
         throw Exception(_T("Wrong: You shouln't use this variant of the DibFrameBuffer::setProperties() function."));
      }

      bool DibFrameBuffer::setProperties(const ::int_rectangle &dimByRect, const PixelFormat *pixelFormat)
      {
         throw Exception(_T("Wrong: You shouln't use this variant of the DibFrameBuffer::setProperties() function."));
      }

      unsigned int8 DibFrameBuffer::getBitsPerPixel() const
      {
         return m_fb.getBitsPerPixel();
      }

      unsigned int8 DibFrameBuffer::getBytesPerPixel() const
      {
         return m_fb.getBytesPerPixel();
      }

      void DibFrameBuffer::setBuffer(void *newBuffer)
      {
         throw Exception(_T("Wrong: You shouln't use the DibFrameBuffer::setBuffer() function."));
      }

      inline void *DibFrameBuffer::getBuffer() const
      {
         return m_fb.getBuffer();
      }

      void *DibFrameBuffer::getBufferPtr(int x, int y) const
      {
         return m_fb.getBufferPtr(x, y);
      }

      inline int DibFrameBuffer::getBufferSize() const
      {
         return m_fb.getBufferSize();
      }

      inline int DibFrameBuffer::getBytesPerRow() const
      {
         return m_fb.getBytesPerRow();
      }

      void DibFrameBuffer::blitToDibSection(const ::int_rectangle &rect)
      {
         checkDibValid();
         m_dibSection->blitToDibSection(rect);
      }

      void DibFrameBuffer::blitTransparentToDibSection(const ::int_rectangle &rect)
      {
         checkDibValid();
         m_dibSection->blitTransparentToDibSection(rect);
      }

      void DibFrameBuffer::blitFromDibSection(const ::int_rectangle &rect)
      {
         checkDibValid();
         m_dibSection->blitFromDibSection(rect);
      }

      void DibFrameBuffer::stretchFromDibSection(const ::int_rectangle &srcRect, const ::int_rectangle &dstRect)
      {
         checkDibValid();
         m_dibSection->stretchFromDibSection(srcRect, dstRect);
      }

      void DibFrameBuffer::setProperties(const Dimension *newDim,
                                         const PixelFormat *pixelFormat,
                                         HWND compatibleWindow)
      {
         m_fb.setPropertiesWithoutResize(newDim, pixelFormat);
         void *buffer = updateDibSection(newDim, pixelFormat, compatibleWindow);
         m_fb.setBuffer(buffer);
      }

      void *DibFrameBuffer::updateDibSection(const Dimension *newDim,
                                            const PixelFormat *pixelFormat,
                                            HWND compatibleWindow)
      {
         releaseDibSection();
         m_dibSection = new DibSection(pixelFormat, newDim, compatibleWindow);
         return m_dibSection->getBuffer();
      }

      void DibFrameBuffer::releaseDibSection()
      {
         if (m_dibSection) {
            delete m_dibSection;
            m_dibSection = 0;
            m_fb.setBuffer(0);
         }
      }

      void DibFrameBuffer::checkDibValid()
      {
         if (m_dibSection == 0) {
            throw Exception(_T("Can't set target DC because it is not initialized a DIB section yet"));
         }
      }
   } // namespace subsystem
} // namespace windows