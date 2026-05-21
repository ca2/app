// Copyright (C) 2012 GlavSoft LLC.
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
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "DibFramebuffer.h"
#include "subsystem/node/SystemException.h"
#include "acme/prototype/geometry2d/size.h"

namespace  innate_subsystem
{
   DibFramebuffer::DibFramebuffer()
   //: m_pdibsection(0)
   {
   }

   DibFramebuffer::~DibFramebuffer()
   {
      releaseDibSection();
   }

   void DibFramebuffer::setTargetDeviceContext(::innate_subsystem::DeviceContextInterface * pdevicecontext)
   {
      checkDibValid();
      m_pdibsection->setTargetDeviceContext(pdevicecontext);
      //m_pdibsection->setTargetDC(targetDC);
   }

   bool DibFramebuffer::assignProperties(const Framebuffer * pframebufferSource)
   {
      throw ::subsystem::Exception("Wrong: You shouln't use the DibFramebuffer::assignProperties() function.");
   }

   bool DibFramebuffer::clone(const Framebuffer * pframebufferSource)
   {
      throw ::subsystem::Exception("Wrong: You shouln't use the DibFramebuffer::clone() function.");
   }

   void DibFramebuffer::setColor(unsigned char reg, unsigned char green, unsigned char blue)
   {
      m_fb.setColor(reg, green, blue);
   }

   void DibFramebuffer::fillRect(const ::i32_rectangle &rectangleTarget, ::u32 color)
   {
      m_fb.fillRect(rectangleTarget, color);
   }

   bool DibFramebuffer::isEqualTo(const Framebuffer * pframebuffer)
   {
      return m_fb.isEqualTo(pframebuffer);
   }

   bool DibFramebuffer::copyFrom(const ::i32_rectangle &rectangleTarget, const Framebuffer * pframebufferSource,
                                 int srcX, int srcY)
   {
      return m_fb.copyFrom(rectangleTarget, pframebufferSource, srcX, srcY);
   }

   bool DibFramebuffer::copyFrom(const Framebuffer * pframebufferSource, int srcX, int srcY)
   {
      return m_fb.copyFrom(pframebufferSource, srcX, srcY);
   }

   bool DibFramebuffer::overlay(const ::i32_rectangle &rectangleTarget, const Framebuffer * pframebufferSource,
                                int srcX, int srcY, const char *andMask)
   {
      return m_fb.overlay(rectangleTarget, pframebufferSource, srcX, srcY, andMask);
   }

   void DibFramebuffer::move(const ::i32_rectangle &rectangleTarget, const int srcX, const int srcY)
   {
      m_fb.move(rectangleTarget, srcX, srcY);
   }

   bool DibFramebuffer::cmpFrom(const ::i32_rectangle &rectangleTarget, const Framebuffer * pframebufferSource,
                                const int srcX, const int srcY)
   {
      return m_fb.cmpFrom(rectangleTarget, pframebufferSource, srcX, srcY);
   }

   bool DibFramebuffer::setDimension(const ::i32_size &newDim)
   {
      throw ::subsystem::Exception("Wrong: You shouln't use the DibFramebuffer::clone() function.");
   }

   bool DibFramebuffer::setDimension(const ::i32_rectangle &rect)
   {
      throw ::subsystem::Exception("Wrong: You shouln't use the DibFramebuffer::clone() function.");
   }

   void DibFramebuffer::setEmptyDimension(const ::i32_rectangle &dimByRect)
   {
      throw ::subsystem::Exception("This function is deprecated");
   }

   void DibFramebuffer::setEmptyPixelFmt(const ::innate_subsystem::PixelFormat &pf)
   {
      throw ::subsystem::Exception("This function is deprecated");
   }

   void DibFramebuffer::setPropertiesWithoutResize(const ::i32_size &newDim, const ::innate_subsystem::PixelFormat &pf)
   {
      throw ::subsystem::Exception("Wrong: You shouln't use the DibFramebuffer::setPropertiesWithoutResize() function.");
   }

    ::i32_size DibFramebuffer::getDimension() const
   {
      return m_fb.getDimension();
   }

   bool DibFramebuffer::setPixelFormat(const ::innate_subsystem::PixelFormat &pixelFormat)
   {
      throw ::subsystem::Exception("Wrong: You shouln't use the DibFramebuffer::setPixelFormat() function.");
   }

   inline PixelFormat DibFramebuffer::getPixelFormat() const
   {
      return m_fb.getPixelFormat();
   }

   bool DibFramebuffer::setProperties(const ::i32_size &newDim, const ::innate_subsystem::PixelFormat &pixelFormat)
   {
      throw ::subsystem::Exception("Wrong: You shouln't use this variant of the DibFramebuffer::setProperties() function.");
   }

   bool DibFramebuffer::setProperties(const ::i32_rectangle &dimByRect, const ::innate_subsystem::PixelFormat &pixelFormat)
   {
      throw ::subsystem::Exception("Wrong: You shouln't use this variant of the DibFramebuffer::setProperties() function.");
   }

   unsigned char DibFramebuffer::getBitsPerPixel() const
   {
      return m_fb.getBitsPerPixel();
   }

   unsigned char DibFramebuffer::getBytesPerPixel() const
   {
      return m_fb.getBytesPerPixel();
   }

   void DibFramebuffer::setBuffer(void *newBuffer)
   {
      throw ::subsystem::Exception("Wrong: You shouln't use the DibFramebuffer::setBuffer() function.");
   }

   inline void *DibFramebuffer::getBuffer() const
   {
      return m_fb.getBuffer();
   }

   void *DibFramebuffer::getBufferPtr(int x, int y) const
   {
      return m_fb.getBufferPtr(x, y);
   }

   inline int DibFramebuffer::getBufferSize() const
   {
      return m_fb.getBufferSize();
   }

   inline int DibFramebuffer::getBytesPerRow() const
   {
      return m_fb.getBytesPerRow();
   }

   void DibFramebuffer::blitToDibSection(const ::i32_rectangle &rect)
   {
      checkDibValid();
      m_pdibsection->blitToDibSection(rect);
   }

   void DibFramebuffer::blitTransparentToDibSection(const ::i32_rectangle &rect)
   {
      checkDibValid();
      m_pdibsection->blitTransparentToDibSection(rect);
   }

   void DibFramebuffer::blitFromDibSection(const ::i32_rectangle &rect)
   {
      checkDibValid();
      m_pdibsection->blitFromDibSection(rect);
   }

   void DibFramebuffer::stretchFromDibSection(const ::i32_rectangle &srcRect, const ::i32_rectangle &rectangleTarget)
   {
      checkDibValid();
      m_pdibsection->stretchFromDibSection(srcRect, rectangleTarget);
   }

   void DibFramebuffer::setProperties(const ::i32_size &newDim,
                                      const ::innate_subsystem::PixelFormat &pixelFormat,
                                      const ::operating_system::window & operatingsystemwindowCompatible)
   {
      m_fb.setPropertiesWithoutResize(newDim, pixelFormat);
      void *buffer = updateDibSection(newDim, pixelFormat, operatingsystemwindowCompatible);
      m_fb.setBuffer(buffer);
   }

   void *DibFramebuffer::updateDibSection(const ::i32_size &newDim,
                                         const ::innate_subsystem::PixelFormat &pixelFormat,
                                         const ::operating_system::window & operatingsystemwindowCompatible)
   {
      releaseDibSection();
      constructø(m_pdibsection);

      m_pdibsection->initialize_dib_section(pixelFormat, newDim, operatingsystemwindowCompatible);

      return m_pdibsection->getBuffer();
   }

   void DibFramebuffer::releaseDibSection()
   {
      if (m_pdibsection) {
         //delete m_pdibsection;
         m_pdibsection.release();
         m_fb.setBuffer(0);
      }
   }

   void DibFramebuffer::checkDibValid()
   {
      if (m_pdibsection == 0) {
         throw ::subsystem::Exception("Can't set target DC because it is not initialized a DIB section yet");
      }
   }
} // namespace  innate_subsystem


