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
#include "FrameBuffer.h"
#include <string.h>

FrameBuffer::FrameBuffer(void)
: m_buffer(0)
{
  memset(&m_pixelFormat, 0, sizeof(m_pixelFormat));
}

FrameBuffer::~FrameBuffer(void)
{
  if (m_buffer != 0) {
    delete []m_buffer;
  }
}

bool FrameBuffer::assignProperties(const FrameBuffer *srcFrameBuffer)
{
  setProperties(srcFrameBuffer->getDimension(),
                srcFrameBuffer->getPixelFormat());
  return resizeBuffer();
}

bool FrameBuffer::clone(const FrameBuffer *srcFrameBuffer)
{
  if (!assignProperties(srcFrameBuffer)) {
    return false;
  }

  ::int_rectangle fbRect(m_dimension);
  copyFrom(fbRect, srcFrameBuffer, fbRect.left, fbRect.top);

  return true;
}

void FrameBuffer::setColor(unsigned char red, unsigned char green, unsigned char blue)
{
  size_t sizeInPixels = m_dimension.area();
  int pixelSize = m_pixelFormat.bitsPerPixel / 8;
  unsigned int redPix = (red * m_pixelFormat.redMax / 255) <<
                  m_pixelFormat.redShift;
  unsigned int greenPix = (green * m_pixelFormat.greenMax / 255) <<
                    m_pixelFormat.greenShift;
  unsigned int bluePix = (blue * m_pixelFormat.blueMax / 255) <<
                   m_pixelFormat.blueShift;
  unsigned int color = redPix | greenPix | bluePix;

  unsigned char *endPixPtr = (unsigned char *)m_buffer + getBufferSize();
  unsigned char *pixPtr = (unsigned char *)m_buffer;
  for (; pixPtr <= endPixPtr - pixelSize; pixPtr += pixelSize) {
    memcpy(pixPtr, &color, pixelSize);
  }
}

void FrameBuffer::fillRect(const ::int_rectangle & dstRect, unsigned int color)
{
  ::int_rectangle clipRect = ::int_rectangle(m_dimension).intersection(dstRect);

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

bool FrameBuffer::isEqualTo(const FrameBuffer *frameBuffer)
{
  return m_dimension == frameBuffer->getDimension() &&
         m_pixelFormat == frameBuffer->getPixelFormat();
}

void FrameBuffer::clipRect(const ::int_rectangle & dstRect, const FrameBuffer *srcFrameBuffer,
                           const int srcX, const int srcY,
                           ::int_rectangle *dstClippedRect, ::int_rectangle *srcClippedRect)
{
   ::int_rectangle srcBufferRect(srcFrameBuffer -> getDimension());
  clipRect(dstRect, srcBufferRect, srcX, srcY, dstClippedRect, srcClippedRect);
}

void FrameBuffer::clipRect(const ::int_rectangle & dstRect, const ::int_rectangle & srcBufferRect,
                           const int srcX, const int srcY,
                           ::int_rectangle *dstClippedRect, ::int_rectangle *srcClippedRect)
{
   ::int_rectangle dstBufferRect(m_dimension);

  // Building srcRect
  ::int_rectangle srcRect(srcX, srcY, srcX + dstRect.width(), srcY + dstRect.height());

  // Finding common area between the dstRect, srcRect and the FrameBuffers
  ::int_rectangle dstRectFB = dstBufferRect.intersection(dstRect);
  ::int_rectangle srcRectFB = srcBufferRect.intersection(srcRect);

  // Finding common area between the dstRectFB and the srcRectFB
  ::int_rectangle dstCommonArea(dstRectFB);
  ::int_rectangle srcCommonArea(srcRectFB);
  // Move to common place (left = 0, top = 0)
  dstCommonArea.offset(-dstRect.left, -dstRect.top);
  srcCommonArea.offset(-srcRect.left, -srcRect.top);

  ::int_rectangle commonRect(dstCommonArea.intersection(srcCommonArea));

  // Moving commonRect to destination coordinates and source
  dstClippedRect->set(commonRect);
  dstClippedRect->offset(dstRect.left, dstRect.top);

  srcClippedRect->set(commonRect);
  srcClippedRect->offset(srcRect.left, srcRect.top);
}

bool FrameBuffer::overlay(const ::int_rectangle & dstRect,
                          const FrameBuffer *srcFrameBuffer,
                          int srcX, int srcY,
                          const char *andMask)
{
  if (m_pixelFormat != srcFrameBuffer->getPixelFormat()) {
    return false;
  }
  if (m_pixelFormat.bitsPerPixel == 32) {
    return overlayT<unsigned int>(dstRect, srcFrameBuffer, srcX, srcY, andMask);
  } else if (m_pixelFormat.bitsPerPixel == 16) {
    return overlayT<unsigned short>(dstRect, srcFrameBuffer, srcX, srcY, andMask);
  } else if (m_pixelFormat.bitsPerPixel == 8) {
    return overlayT<unsigned char>(dstRect, srcFrameBuffer, srcX, srcY, andMask);
  } else {
    _ASSERT(false);
  }
  return false;
}

template<class PIXEL_T> bool FrameBuffer::overlayT(const ::int_rectangle & dstRect,
                                                   const FrameBuffer *srcFrameBuffer,
                                                   int srcX, int srcY,
                                                   const char *andMask)
{
  ::int_rectangle srcClippedRect, dstClippedRect;

  clipRect(dstRect, srcFrameBuffer, srcX, srcY, &dstClippedRect, &srcClippedRect);
  if (dstClippedRect.area() <= 0 || srcClippedRect.area() <= 0) {
    return true;
  }

  PIXEL_T *dstPixels = (PIXEL_T *)getBuffer();
  PIXEL_T *srcPixels = (PIXEL_T *)srcFrameBuffer->getBuffer();
  int srcWidth = srcFrameBuffer->getDimension().cx;
  int dstWidth = getDimension().cx;
  size_t bytesPerRow = (srcWidth + 7) / 8;
  for (int iRow = srcClippedRect.top; iRow < srcClippedRect.bottom; iRow++) {
    for (int iCol = srcClippedRect.left; iCol < srcClippedRect.right; iCol++) {
      unsigned char curByte = andMask[iRow * bytesPerRow + iCol / 8];
      bool andBit = (curByte & 128 >> iCol % 8) != 0;
      if (andBit) {
        int iDstRow = dstClippedRect.top + iRow - srcY - srcClippedRect.top;
        int iDstCol = dstClippedRect.left + iCol - srcX - srcClippedRect.left;
        dstPixels[iDstRow * dstWidth + iDstCol] = srcPixels[iRow * srcWidth + iCol];
      }
    }
  }
  return true;
}

bool FrameBuffer::copyFrom(const ::int_rectangle & dstRect, const FrameBuffer *srcFrameBuffer,
                           int srcX, int srcY)
{
  if (m_pixelFormat != srcFrameBuffer->getPixelFormat()) {
    return false;
  }

  ::int_rectangle srcClippedRect, dstClippedRect;

  clipRect(dstRect, srcFrameBuffer, srcX, srcY, &dstClippedRect, &srcClippedRect);
  if (dstClippedRect.area() <= 0 || srcClippedRect.area() <= 0) {
    return true;
  }

  // Shortcuts
  int pixelSize = m_pixelFormat.bitsPerPixel / 8;
  int dstStrideBytes = m_dimension.cx * pixelSize;
  int srcStrideBytes = srcFrameBuffer->getDimension().cx * pixelSize;

  int resultHeight = dstClippedRect.height();
  int resultWidthBytes = dstClippedRect.width() * pixelSize;

  unsigned char *pdst = (unsigned char *)m_buffer
                + dstClippedRect.top * dstStrideBytes
                + pixelSize * dstClippedRect.left;

  unsigned char *psrc = (unsigned char *)srcFrameBuffer->getBuffer()
                + srcClippedRect.top * srcStrideBytes
                + pixelSize * srcClippedRect.left;

  for (int i = 0; i < resultHeight; i++, pdst += dstStrideBytes, psrc += srcStrideBytes) {
    memcpy(pdst, psrc, resultWidthBytes);
  }

  return true;
}

bool FrameBuffer::copyFrom(const FrameBuffer *srcFrameBuffer,
                           int srcX, int srcY)
{
  return copyFrom(m_dimension, srcFrameBuffer, srcX, srcY);
}

bool FrameBuffer::copyFromRotated90(const ::int_rectangle & dstRect, const FrameBuffer *srcFrameBuffer,
                                    int srcX, int srcY)
{
  if (m_pixelFormat.bitsPerPixel != 32 || m_pixelFormat != srcFrameBuffer->getPixelFormat())
  {
    return false;
  }

  // Shortcuts
  int pixelSize = m_pixelFormat.bitsPerPixel / 8;
  int dstStrideBytesByX = m_dimension.cx * pixelSize;
  int srcStrideBytes = srcFrameBuffer->getDimension().cx * pixelSize;

  ::int_rectangle srcClippedRect, dstClippedRect;

  ::int_size srcBuffTransposedDim = srcFrameBuffer->getDimension().transposed();
  ::int_rectangle srcBuffTransposedRect = srcBuffTransposedDim;
  ::int_rectangle srcRotatedCoordinates(srcX, srcY, srcX + dstRect.height(), srcY + dstRect.width());
  srcRotatedCoordinates.rotateOn90InsideDimension(srcFrameBuffer->getDimension().cy);
  int srcXinDstRotation = srcRotatedCoordinates.left;
  int srcYinDstRotation = srcRotatedCoordinates.top;
  clipRect(dstRect, srcBuffTransposedRect, srcXinDstRotation, srcYinDstRotation, &dstClippedRect, &srcClippedRect);
  if (dstClippedRect.area() <= 0 || srcClippedRect.area() <= 0) {
    return true;
  }
  // Rotate source rect back in source rotation.
  srcClippedRect.rotateOn270InsideDimension(srcBuffTransposedDim.cx);

  int resultHeight = srcClippedRect.height();
  int resultWidth = srcClippedRect.width();

  unsigned char *pBaseDst = (unsigned char *)m_buffer
                    + dstClippedRect.top * dstStrideBytesByX
                    + pixelSize * (dstClippedRect.right - 1);

  unsigned char *pBaseSrc = (unsigned char *)srcFrameBuffer->getBuffer()
                    + srcClippedRect.top * srcStrideBytes
                    + pixelSize * srcClippedRect.left;

  for (int iRow = 0; iRow < resultHeight; iRow++, pBaseDst -= pixelSize, pBaseSrc += srcStrideBytes) {
    unsigned int *pSrc = (unsigned int *)pBaseSrc;
    unsigned char *pDst = pBaseDst;
    for (int iCol = 0; iCol < resultWidth; iCol++, pSrc++, pDst += dstStrideBytesByX) {
      *(unsigned int *)pDst = *pSrc;
    }
  }

  return true;
}

bool FrameBuffer::copyFromRotated180(const ::int_rectangle & dstRect, const FrameBuffer *srcFrameBuffer,
                                    int srcX, int srcY)
{
  if (m_pixelFormat.bitsPerPixel != 32 || m_pixelFormat != srcFrameBuffer->getPixelFormat())
  {
    return false;
  }

  // Shortcuts
  int pixelSize = m_pixelFormat.bitsPerPixel / 8;
  int dstStrideBytesByX = m_dimension.cx * pixelSize;
  int srcStrideBytes = srcFrameBuffer->getDimension().cx * pixelSize;

  ::int_rectangle srcClippedRect, dstClippedRect;

  ::int_size srcBuffTransposedDim = srcFrameBuffer->getDimension();
  ::int_rectangle srcBuffTransposedRect = srcBuffTransposedDim;
  ::int_rectangle srcRotatedCoordinates(srcX, srcY, srcX + dstRect.width(), srcY + dstRect.height());
  srcRotatedCoordinates.rotateOn180InsideDimension(srcFrameBuffer->getDimension().cx,
                                                   srcFrameBuffer->getDimension().cy);
  int srcXinDstRotation = srcRotatedCoordinates.left;
  int srcYinDstRotation = srcRotatedCoordinates.top;
  clipRect(dstRect, srcBuffTransposedRect, srcXinDstRotation, srcYinDstRotation, &dstClippedRect, &srcClippedRect);
  if (dstClippedRect.area() <= 0 || srcClippedRect.area() <= 0) {
    return true;
  }
  // Rotate source rect back in source rotation.
  srcClippedRect.rotateOn180InsideDimension(srcFrameBuffer->getDimension().cx,
                                            srcFrameBuffer->getDimension().cy);

  int resultHeight = srcClippedRect.height();
  int resultWidth = srcClippedRect.width();

  unsigned char *pBaseDst = (unsigned char *)m_buffer
    + (dstClippedRect.bottom - 1) * dstStrideBytesByX
    + pixelSize * (dstClippedRect.right - 1);

  unsigned char *pBaseSrc = (unsigned char *)srcFrameBuffer->getBuffer()
    + srcClippedRect.top * srcStrideBytes
    + pixelSize * srcClippedRect.left;

  for (int iRow = 0; iRow < resultHeight; iRow++, pBaseDst -= dstStrideBytesByX , pBaseSrc += srcStrideBytes) {
    unsigned int *pSrc = (unsigned int *)pBaseSrc;
    unsigned int *pDst = (unsigned int *)pBaseDst;
    for (int iCol = 0; iCol < resultWidth; iCol++, pSrc++, pDst--) {
      *(unsigned int *)pDst = *pSrc;
    }
  }

  return true;
}

bool FrameBuffer::copyFromRotated270(const ::int_rectangle & dstRect, const FrameBuffer *srcFrameBuffer,
                                    int srcX, int srcY)
{
  if (m_pixelFormat.bitsPerPixel != 32 || m_pixelFormat != srcFrameBuffer->getPixelFormat())
  {
    return false;
  }

  // Shortcuts
  int pixelSize = m_pixelFormat.bitsPerPixel / 8;
  int dstStrideBytesByX = m_dimension.cx * pixelSize;
  int srcStrideBytes = srcFrameBuffer->getDimension().cx * pixelSize;

  ::int_rectangle srcClippedRect, dstClippedRect;

  ::int_size srcBuffTransposedDim = srcFrameBuffer->getDimension().transposed();
  ::int_rectangle srcBuffTransposedRect = srcBuffTransposedDim;
  ::int_rectangle srcRotatedCoordinates(srcX, srcY, srcX + dstRect.height(), srcY + dstRect.width());
  srcRotatedCoordinates.rotateOn270InsideDimension(srcFrameBuffer->getDimension().cx);
  int srcXinDstRotation = srcRotatedCoordinates.left;
  int srcYinDstRotation = srcRotatedCoordinates.top;
  clipRect(dstRect, srcBuffTransposedRect, srcXinDstRotation, srcYinDstRotation, &dstClippedRect, &srcClippedRect);
  if (dstClippedRect.area() <= 0 || srcClippedRect.area() <= 0) {
    return true;
  }
  // Rotate source rect back in source rotation.
  srcClippedRect.rotateOn90InsideDimension(srcBuffTransposedDim.cy);

  int resultHeight = srcClippedRect.height();
  int resultWidth = srcClippedRect.width();

  unsigned char *pBaseDst = (unsigned char *)m_buffer
    + (dstClippedRect.bottom - 1) * dstStrideBytesByX
    + pixelSize * dstClippedRect.left;

  unsigned char *pBaseSrc = (unsigned char *)srcFrameBuffer->getBuffer()
    + srcClippedRect.top * srcStrideBytes
    + pixelSize * srcClippedRect.left;

  for (int iRow = 0; iRow < resultHeight; iRow++, pBaseDst += pixelSize, pBaseSrc += srcStrideBytes) {
    unsigned int *pSrc = (unsigned int *)pBaseSrc;
    unsigned char *pDst = pBaseDst;
    for (int iCol = 0; iCol < resultWidth; iCol++, pSrc++, pDst -= dstStrideBytesByX) {
      *(unsigned int *)pDst = *pSrc;
    }
  }

  return true;
}

bool FrameBuffer::cmpFrom(const ::int_rectangle & dstRect, const FrameBuffer *srcFrameBuffer,
                          const int srcX, const int srcY)
{
  if (m_pixelFormat != srcFrameBuffer->getPixelFormat())
  {
    return false;
  }

  ::int_rectangle srcClippedRect, dstClippedRect;

  clipRect(dstRect, srcFrameBuffer, srcX, srcY, &dstClippedRect, &srcClippedRect);
  if (dstClippedRect.area() <= 0 || srcClippedRect.area() <= 0) {
    return true;
  }

  // Shortcuts
  int pixelSize = m_pixelFormat.bitsPerPixel / 8;
  int dstStrideBytes = m_dimension.cx * pixelSize;
  int srcStrideBytes = srcFrameBuffer->getDimension().cx * pixelSize;

  int resultHeight = dstClippedRect.height();
  int resultWidthBytes = dstClippedRect.width() * pixelSize;

  unsigned char *pdst = (unsigned char *)m_buffer
                + dstClippedRect.top * dstStrideBytes
                + pixelSize * dstClippedRect.left;

  unsigned char *psrc = (unsigned char *)srcFrameBuffer->getBuffer()
                + srcClippedRect.top * srcStrideBytes
                + pixelSize * srcClippedRect.left;

  for (int i = 0; i < resultHeight; i++, pdst += dstStrideBytes, psrc += srcStrideBytes) {
    if (memcmp(pdst, psrc, resultWidthBytes) != 0) {
      return false;
    }
  }

  return true;
}

void FrameBuffer::move(const ::int_rectangle & dstRect, const int srcX, const int srcY)
{
  ::int_rectangle srcClippedRect, dstClippedRect;

  clipRect(dstRect, this, srcX, srcY, &dstClippedRect, &srcClippedRect);
  if (dstClippedRect.area() <= 0 || srcClippedRect.area() <= 0) {
    return;
  }

  // Data copy
  int pixelSize = m_pixelFormat.bitsPerPixel / 8;
  int strideBytes = m_dimension.cx * pixelSize;

  int resultHeight = dstClippedRect.height();
  int resultWidthBytes = dstClippedRect.width() * pixelSize;

  unsigned char *pdst, *psrc;

  if (srcY > dstRect.top) {
    // Pointers set to first string of the rectanles
    pdst = (unsigned char *)m_buffer + dstClippedRect.top * strideBytes
           + pixelSize * dstClippedRect.left;
    psrc = (unsigned char *)m_buffer + srcClippedRect.top * strideBytes
           + pixelSize * srcClippedRect.left;

    for (int i = 0; i < resultHeight; i++, pdst += strideBytes, psrc += strideBytes) {
      memcpy(pdst, psrc, resultWidthBytes);
    }

  } else {
    // Pointers set to last string of the rectanles
    pdst = (unsigned char *)m_buffer + (dstClippedRect.bottom - 1) * strideBytes
           + pixelSize * dstClippedRect.left;
    psrc = (unsigned char *)m_buffer + (srcClippedRect.bottom - 1) * strideBytes
           + pixelSize * srcClippedRect.left;

    for (int i = resultHeight - 1; i >= 0; i--, pdst -= strideBytes, psrc -= strideBytes) {
      memmove(pdst, psrc, resultWidthBytes);
    }
  }
}

bool FrameBuffer::setPixelFormat(const PixelFormat & pixelFormat)
{
  m_pixelFormat = pixelFormat;
  return resizeBuffer();
}

bool FrameBuffer::setDimension(const ::int_size & newDim)
{
  m_dimension = newDim;
  return resizeBuffer();
}

void FrameBuffer::setEmptyDimension(const ::int_rectangle & dimByRect)
{
  m_dimension = dimByRect.size();
}

void FrameBuffer::setEmptyPixelFmt(const PixelFormat & pf)
{
  m_pixelFormat = pf;
}

void FrameBuffer::setPropertiesWithoutResize(const ::int_size & newDim, const PixelFormat & pf)
{
  m_dimension = newDim;
  m_pixelFormat = pf;
}

bool FrameBuffer::setProperties(const ::int_size & newDim,
                                const PixelFormat & pixelFormat)
{
  m_pixelFormat = pixelFormat;
  m_dimension = newDim;
  return resizeBuffer();
}

bool FrameBuffer::setProperties(const ::int_rectangle & dimByRect,
                                const PixelFormat & pixelFormat)
{
  m_pixelFormat = pixelFormat;
  m_dimension = dimByRect.size();
  return resizeBuffer();
}

unsigned char FrameBuffer::getBitsPerPixel() const
{
  _ASSERT((unsigned char)m_pixelFormat.bitsPerPixel == m_pixelFormat.bitsPerPixel);
  return (unsigned char)m_pixelFormat.bitsPerPixel;
}

int FrameBuffer::getBufferSize() const
{ 
  return (int)((unsigned long long)m_dimension.area() * m_pixelFormat.bitsPerPixel / 8);
}

bool FrameBuffer::resizeBuffer()
{
  if (m_buffer != 0) {
    delete []m_buffer;
  }
  if ((m_buffer = new unsigned char[getBufferSize()]) == 0) {
    return false;
  }
  return true;
}
