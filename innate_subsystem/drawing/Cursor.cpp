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
// Adapted by camilo on beginning of 2026-April <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "Cursor.h"
#include "DeviceContext.h"
#include "Bitmap.h"

namespace innate_subsystem
{


//
//    Cursor::Cursor()
//    //: m_bHasOwnCursor(true), m_hcursor(NULL)
//    {
//    }
//
// //    Cursor::Cursor(HICON icon)
// // : m_bHasOwnIcon(true), m_hcursor(icon)
// //    {
// //    }
// //
// //    Cursor::Cursor(Bitmap *bitmap)
// //    : m_bHasOwnIcon(true), m_hcursor(NULL)
// //    {
// //       Bitmap mask(bitmap->getWidth(), bitmap->getHeight());
// //       fromBitmap(bitmap, &mask);
// //    }
// //
// //    Cursor::Cursor(Bitmap *bitmap, Bitmap *mask)
// //    : m_bHasOwnIcon(true), m_hcursor(NULL)
// //    {
// //       fromBitmap(bitmap, mask);
// //    }
// //
// //    Cursor::Cursor(DWORD icon)
// //    : m_bHasOwnIcon(false)
// //    {
// //       HINSTANCE hInstance = GetModuleHandle(NULL);
// //       m_hcursor = LoadIcon(hInstance, MAKEINTRESOURCE(icon));
// //    }
// //
//
//
//    Cursor::~Cursor()
//    {
//       //if (m_bHasOwnIcon) {
//       //   DestroyIcon(m_hcursor);
//       //}
//    }
//
//
//    void Cursor::initialize_cursor(::innate_subsystem::CursorInterface * pcursor)
//
//    {
//
//       m_pparticleThis->initialize_cursor(pcursor);
//       //m_bHasOwnIcon = true;
//       //::cast < ::innate_subsystem_windows::Cursor > piconWin32 = ::subsystem::get_implementation(picon);
//       //m_hcursor = piconWin32->m_hcursor;
//    }
//
//    void Cursor::initialize_cursor(innate_subsystem::BitmapInterface *pbitmap)
//
//    {
//
//       m_pparticleThis->initialize_cursor(pbitmap);
//       //m_bHasOwnIcon = true;
//
//       //m_hcursor = nullptr;
//
//       //Bitmap mask;
//       //mask.initialize_bitmap(pbitmap->getSize());
//       //fromBitmap(pbitmap, &mask);
//    }
//
//    void Cursor::initialize_cursor(::innate_subsystem::BitmapInterface *bitmap, ::innate_subsystem::BitmapInterface *mask)
//    //:
//    {
//
//       m_pparticleThis->initialize_cursor(bitmap, mask);
//       //m_bHasOwnIcon = true;
//       //m_hcursor = nullptr;
//       //fromBitmap(bitmap, mask);
//    }
//
//
//    void Cursor::initialize_with_system_cursor(::enum_cursor ecursor)
//    {
//       m_pparticleThis->initialize_with_system_cursor(ecursor);
//    }
//
//
//    //void Cursor::initialize_cursor(unsigned int icon) {
//    //   m_pparticleThis->initialize_cursor(icon);
//    //}
//
//
//
//     void * Cursor::_HCURSOR()
//     {
//
//        return m_pparticleThis->_HCURSOR();
//     }
//
//         void Cursor::_setHCURSOR(void * pHCURSOR) { m_pparticleThis->_setHCURSOR(pHCURSOR); }
//
//    void Cursor::fromBitmap(::innate_subsystem::BitmapInterface *pbitmap, ::innate_subsystem::BitmapInterface *pbitmapMask)
//    {
//
//       m_pparticleThis->fromBitmap(pbitmap, pbitmapMask);
//        /*
//       CURS ii;
//
//       memset(&ii, 0, sizeof(ICONINFO));
//
//       auto pbitmapWin32 = pbitmap->impl<innate_subsystem_windows::Bitmap>();
//       auto pbitmapMaskWin32 = pbitmapMask->impl<innate_subsystem_windows::Bitmap>();
//
//       ii.hbmColor = (pbitmapWin32 != 0) ? pbitmapWin32->m_hbitmap : 0;
//       ii.hbmMask = (pbitmapMaskWin32 != 0) ? pbitmapMaskWin32->m_hbitmap : 0;
// */
//       //m_hcursor = CreateIconIndirect(&ii);
//
//    }
//
//

} // namespace innate_subsystem_windows

