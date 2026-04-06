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

#pragma once


//
#include "acme/subsystem/framebuffer/PixelFormat.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/prototype/geometry2d/size.h"

// FIXME: Move implementation to the .cpp file.

namespace remoting
{
   class CLASS_DECL_REMOTING_COMMON FrameBuffer
   {
   public:
      //int m_iDivisor = 1;
      FrameBuffer(void);
      virtual ~FrameBuffer(void);

      virtual bool assignProperties(const ::subsystem::PixelFormat &srcFrameBuffer);
      virtual bool clone(const ::subsystem::PixelFormat &srcFrameBuffer);
      virtual void setColor(unsigned char red, unsigned char green, unsigned char blue);
      virtual void fillRect(const ::int_rectangle &  dstRect, unsigned int color);

      // Return value: true - if equal
      //               false - if PixelFormats or size differs
      virtual bool isEqualTo(const ::subsystem::PixelFormat &frameBuffer);

      // Copy to self by specified destination rectangle from the specified
      // coordinates of srcFrameBuffer
      virtual bool copyFrom(const ::int_rectangle &  dstRect, const ::subsystem::PixelFormat &srcFrameBuffer,
                    int srcX, int srcY);
      // The same as above but destination rect is m_dimension
      virtual bool copyFrom(const ::subsystem::PixelFormat &srcFrameBuffer,
                    int srcX, int srcY);

      // Copy to self by specified destination rectangle from the specified
      // coordinates of srcFrameBuffer. When source farmebuffer and source coordinates are
      // rotated with 90 degree.
      virtual bool copyFromRotated90(const ::int_rectangle &  dstRect, const ::subsystem::PixelFormat &srcFrameBuffer,
                                     int srcX, int srcY);

      // Copy to self by specified destination rectangle from the specified
      // coordinates of srcFrameBuffer. When source farmebuffer and source coordinates are
      // rotated with 180 degree.
      virtual bool copyFromRotated180(const ::int_rectangle &  dstRect, const ::subsystem::PixelFormat &srcFrameBuffer,
                                      int srcX, int srcY);

      // Copy to self by specified destination rectangle from the specified
      // coordinates of srcFrameBuffer. When source farmebuffer and source coordinates are
      // rotated with 270 degree.
      virtual bool copyFromRotated270(const ::int_rectangle &  dstRect, const ::subsystem::PixelFormat &srcFrameBuffer,
                                      int srcX, int srcY);

      // Overlays the source image to this with by the AND mask
      virtual bool overlay(const ::int_rectangle &  dstRect,
                   const ::subsystem::PixelFormat &srcFrameBuffer,
                   int srcX, int srcY,
                   const char *andMask);
      virtual void move(const ::int_rectangle &  dstRect, const int srcX, const int srcY);
      // Return value: true - if equal
      //               false - if PixelFormats or data differs
      virtual bool cmpFrom(const ::int_rectangle &  dstRect, const ::subsystem::PixelFormat &srcFrameBuffer,
                   const int srcX, const int srcY);

      virtual bool setDimension(const ::int_size & newDim);
      virtual bool setDimension(const ::int_rectangle &  rect)
      {
         ::int_size dim(rect.size());
         return setDimension(dim);
      }

      // Sets dimension to the frame buffer without buffer resizing
      virtual void setEmptyDimension(const ::int_rectangle &  dimByRect);

      // Sets pixel format to the frame buffer without buffer resizing
      virtual void setEmptyPixelFmt(const ::subsystem::PixelFormat & pf);

      virtual void setPropertiesWithoutResize(const ::int_size & newDim, const ::subsystem::PixelFormat & pf);

      virtual inline ::int_size getDimension() const { return m_dimension; }

      virtual bool setPixelFormat(const ::subsystem::PixelFormat & pixelFormat);
      virtual inline ::subsystem::PixelFormat getPixelFormat() const { return m_pixelFormat; }

      // This function set both PixelFormat and ::int_size
      virtual bool setProperties(const ::int_size & newDim, const ::subsystem::PixelFormat & pixelFormat);
      virtual bool setProperties(const ::int_rectangle &  dimByRect, const ::subsystem::PixelFormat & pixelFormat);

      // Return the number of bits occupied by one pixel (can be 8, 16 or 32).
      virtual unsigned char getBitsPerPixel() const;

      // Return the number of bytes occupied by one pixel (can be 1, 2 or 4).
      //virtual unsigned char getBytesPerPixel() const;

      virtual void setBuffer(void *newBuffer) { m_buffer = newBuffer; }
      virtual inline void *getBuffer() const { return m_buffer; }

      // Return a pointer to the pixel data specified by the coordinates of that
      // pixel. getBufferPtr(0, 0) should be equivalent to getBuffer(). This
      // function does not check if the coordinates are within the frame buffer
      // boundaries.
      //  virtual void *getBufferPtr(int x, int y) const;



      unsigned char getBytesPerPixel() const
      {
         return (unsigned char)(m_pixelFormat.bitsPerPixel / 8);
      }

      void* getBufferPtr(int x, int y) const
      {
         char* ptr = (char*)m_buffer;
         ptr += (y * m_dimension.cx + x) * getBytesPerPixel();

         return (void*)ptr;
      }


      virtual inline int getBufferSize() const;
      virtual inline int getBytesPerRow() const { return m_dimension.cx *
                                                 m_pixelFormat.bitsPerPixel / 8; }

      //protected:
      bool resizeBuffer();
      void clipRect(const ::int_rectangle &  dstRect, const ::subsystem::PixelFormat &srcFrameBuffer,
                    const int srcX, const int srcY,
                    ::int_rectangle *dstClippedRect, ::int_rectangle *srcClippedRect);
      void clipRect(const ::int_rectangle &  dstRect,const ::int_rectangle & srcBufferRect,
                    const int srcX, const int srcY,
                    ::int_rectangle *dstClippedRect, ::int_rectangle *srcClippedRect);

      template<class PIXEL_T> bool overlayT(const ::int_rectangle &  dstRect,
                                            const ::subsystem::PixelFormat &srcFrameBuffer,
                                            int srcX, int srcY,
                                            const char *andMask);

      ::int_size m_dimension;

      ::subsystem::PixelFormat m_pixelFormat;
      void *m_buffer;

   };


   //// __FRAMEBUFFER_H__
} // namespace remoting


