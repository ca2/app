// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
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
#include "framework.h"
#include "Bitmap.h"

namespace innate_subsystem
{
//    // Bitmap::Bitmap(const ::int_size & size)
//    // : m_bitmap(NULL)
//    // {
//    //    // Prepare buffer
//    //    int bpp = 32;
//    //    size_t size = width * height * (bpp / 8);
//    //    std::vector<unsigned char> bits(size);
//    //    if (width != 0 && height != 0) {
//    //       memset(&bits.front(), 0, size);
//    //       // Create bitmap handle
//    //       m_bitmap = CreateBitmap(width, height, 1, bpp, &bits.front());
//    //    }
//    // }
//    //
//    // Bitmap::Bitmap(HDC dc, const ::int_size & size)
//    // {
//    //    m_bitmap = CreateCompatibleBitmap(dc, width, height);
//    // }
//    //
//    // Bitmap::Bitmap(HBITMAP bitmap)
//    // : m_bitmap(bitmap)
//    // {
//    // }
//
//    Bitmap::Bitmap()
//    {
//
//
//    }
//
//
//    Bitmap::~Bitmap()
//    {
//       //if (m_bitmap != NULL) {
//       //    DeleteObject(m_bitmap);
//       // }
//    }
//
//
//    // void * Bitmap::_HGDIOBJ()
//    // {
//    //
//    //    return m_pparticleThis->_HGDIOBJ();
//    //
//    // }
//
//
//    void Bitmap::initialize_bitmap(const ::int_size & size)
// ///: m_bitmap(NULL)
//    {
//       m_pparticleThis->initialize_bitmap(size);
//       // // Prepare buffer
//       // int bpp = 32;
//       // size_t size = width * height * (bpp / 8);
//       // std::vector<unsigned char> bits(size);
//       // if (width != 0 && height != 0) {
//       //    memset(&bits.front(), 0, size);
//       //    // Create bitmap handle
//       //    m_bitmap = CreateBitmap(width, height, 1, bpp, &bits.front());
//       // }
//    }
//
//    void Bitmap::initialize_bitmap(DeviceContextInterface * pdevicecontext, const ::int_size & size)
//    {
//       //m_bitmap = CreateCompatibleBitmap(dc, width, height);
//       m_pparticleThis->initialize_bitmap(pdevicecontext, size);
//    }
//
//    void Bitmap::initialize_bitmap(BitmapInterface * pbitmap)
//    //: m_bitmap(bitmap)
//    {
//       m_pparticleThis->initialize_bitmap(pbitmap);
//
//    }
//
//    ::int_size Bitmap::getSize() const
//    {
//       // BITMAP bitmap;
//       // if (GetObject(m_bitmap, sizeof(BITMAP), &bitmap) == 0) {
//       //    return 0;
//       // }
//       // return bitmap.bmWidth;
//
//       return m_pparticleThis->getSize();
//    }
//
//
//    void Bitmap::destroyGraphicsObject()
//    {
//
//       m_pparticleThis->destroyGraphicsObject();
//
//    }
//
//
//    // int Bitmap::getHeight() const
//    // {
//    //    BITMAP bitmap;
//    //    if (GetObject(m_bitmap, sizeof(BITMAP), &bitmap) == 0) {
//    //       return 0;
//    //    }
//    //    return bitmap.bmHeight;
//    // }

} // namespace innate_subsystem


