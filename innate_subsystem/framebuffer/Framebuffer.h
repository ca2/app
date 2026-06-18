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

#pragma once


//
#include "subsystem/framebuffer/PixelFormat.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/prototype/geometry2d/size.h"

// FIXME: Move implementation to the .cpp file.

namespace innate_subsystem
{
   class CLASS_DECL_INNATE_SUBSYSTEM Framebuffer :
   virtual public ::particle
   {
   public:
      
      ::i32_size m_size;

      ::innate_subsystem::PixelFormat m_pixelformat;
      void *m_buffer;


      
      //::i32 m_iDivisor = 1;
      Framebuffer(void);
      ~Framebuffer(void) override;

      virtual bool assignProperties(const Framebuffer * pframebufferSource);
      virtual bool clone(const Framebuffer * pframebufferSource);
      virtual void setColor(::u8 red, ::u8 green, ::u8 blue);
      virtual void fillRect(const ::i32_rectangle &  rectangleTarget, ::u32 color);

      // Return value: true - if equal
      //               false - if PixelFormats or size differs
      virtual bool isEqualTo(const Framebuffer * pframebuffer);

      // Copy to self by specified destination rectangle from the specified
      // coordinates of pframebufferSource
      virtual bool copyFrom(const ::i32_rectangle &  rectangleTarget, const Framebuffer * pframebufferSource,
                    ::i32 srcX, ::i32 srcY);
      // The same as above but destination rect is m_size
      virtual bool copyFrom(const Framebuffer * pframebufferSource,
                    ::i32 srcX, ::i32 srcY);

      // Copy to self by specified destination rectangle from the specified
      // coordinates of pframebufferSource-> When source farmebuffer and source coordinates are
      // rotated with 90 degree.
      virtual bool copyFromRotated90(const ::i32_rectangle &  rectangleTarget, const Framebuffer * pframebufferSource,
                                     ::i32 srcX, ::i32 srcY);

      // Copy to self by specified destination rectangle from the specified
      // coordinates of pframebufferSource-> When source farmebuffer and source coordinates are
      // rotated with 180 degree.
      virtual bool copyFromRotated180(const ::i32_rectangle &  rectangleTarget, const Framebuffer * pframebufferSource,
                                      ::i32 srcX, ::i32 srcY);

      // Copy to self by specified destination rectangle from the specified
      // coordinates of pframebufferSource-> When source farmebuffer and source coordinates are
      // rotated with 270 degree.
      virtual bool copyFromRotated270(const ::i32_rectangle &  rectangleTarget, const Framebuffer * pframebufferSource,
                                      ::i32 srcX, ::i32 srcY);

      // Overlays the source image to this with by the AND mask
      virtual bool overlay(const ::i32_rectangle &  rectangleTarget,
                   const Framebuffer * pframebufferSource,
                   ::i32 srcX, ::i32 srcY,
                   const_char_pointer andMask);
      virtual void move(const ::i32_rectangle &  rectangleTarget, const ::i32 srcX, const ::i32 srcY);
      // Return value: true - if equal
      //               false - if PixelFormats or data differs
      virtual bool cmpFrom(const ::i32_rectangle &  rectangleTarget, const Framebuffer * pframebufferSource,
                   const ::i32 srcX, const ::i32 srcY);

      virtual bool setDimension(const ::i32_size & newDim);
      virtual bool setDimension(const ::i32_rectangle &  rect)
      {
         ::i32_size dim(rect.size());
         return setDimension(dim);
      }

      // Sets dimension to the frame buffer without buffer resizing
      virtual void setEmptyDimension(const ::i32_rectangle &  dimByRect);

      // Sets pixel format to the frame buffer without buffer resizing
      virtual void setEmptyPixelFmt(const ::innate_subsystem::PixelFormat & pf);

      virtual void setPropertiesWithoutResize(const ::i32_size & newDim, const ::innate_subsystem::PixelFormat & pf);

      virtual ::i32_size getDimension() const { return m_size; }

      virtual bool setPixelFormat(const ::innate_subsystem::PixelFormat & pixelFormat);
      virtual ::innate_subsystem::PixelFormat getPixelFormat() const { return m_pixelformat; }

      // This function set both PixelFormat and ::i32_size
      virtual bool setProperties(const ::i32_size & newDim, const ::innate_subsystem::PixelFormat & pixelFormat);
      virtual bool setProperties(const ::i32_rectangle &  dimByRect, const ::innate_subsystem::PixelFormat & pixelFormat);

      // Return the number of bits occupied by one pixel (can be 8, 16 or 32).
      virtual ::u8 getBitsPerPixel() const;

      // Return the number of bytes occupied by one pixel (can be 1, 2 or 4).
      //virtual ::u8 getBytesPerPixel() const;

      virtual void setBuffer(void *newBuffer) { m_buffer = newBuffer; }
      virtual void *getBuffer() const { return m_buffer; }

      // Return a pointer to the pixel data specified by the coordinates of that
      // pixel. getBufferPtr(0, 0) should be equivalent to getBuffer(). This
      // function does not check if the coordinates are within the frame buffer
      // boundaries.
      //  virtual void *getBufferPtr(::i32 x, ::i32 y) const;



      ::u8 getBytesPerPixel() const
      {
         return (::u8)(m_pixelformat.bitsPerPixel / 8);
      }

      void* getBufferPtr(::i32 x, ::i32 y) const
      {
         char_pointer ptr = (char_pointer )m_buffer;
         ptr += (y * m_size.cx + x) * getBytesPerPixel();

         return (void*)ptr;
      }


      virtual ::i32 getBufferSize() const;
      virtual ::i32 getBytesPerRow() const { return m_size.cx *
                                                 m_pixelformat.bitsPerPixel / 8; }

      //protected:
      bool resizeBuffer();
      void clipRect(const ::i32_rectangle &  rectangleTarget, const Framebuffer * pframebufferSource,
                    const ::i32 srcX, const ::i32 srcY,
                    ::i32_rectangle & rectangleTargetClipped, ::i32_rectangle & rectangleSourceClipped);
      void clipRect(const ::i32_rectangle &  rectangleTarget,const ::i32_rectangle & srcBufferRect,
                    const ::i32 srcX, const ::i32 srcY,
                    ::i32_rectangle & rectangleTargetClipped, ::i32_rectangle & rectangleSourceClipped);

      template<class PIXEL_T> bool overlayT(const ::i32_rectangle &  rectangleTarget,
                                            const Framebuffer * pframebufferSource,
                                            ::i32 srcX, ::i32 srcY,
                                            const_char_pointer andMask);

   };


   //// __FRAMEBUFFER_H__
} // namespace remoting


