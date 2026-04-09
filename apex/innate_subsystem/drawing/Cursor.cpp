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
#include "Icon.h"
#include "DeviceContext.h"
#include "Bitmap.h"

namespace innate_subsystem_win32
{
   Icon::Icon()
   : m_bHasOwnIcon(true), m_hicon(NULL)
   {
   }

//    Icon::Icon(HICON icon)
// : m_bHasOwnIcon(true), m_hicon(icon)
//    {
//    }
//
//    Icon::Icon(Bitmap *bitmap)
//    : m_bHasOwnIcon(true), m_hicon(NULL)
//    {
//       Bitmap mask(bitmap->getWidth(), bitmap->getHeight());
//       fromBitmap(bitmap, &mask);
//    }
//
//    Icon::Icon(Bitmap *bitmap, Bitmap *mask)
//    : m_bHasOwnIcon(true), m_hicon(NULL)
//    {
//       fromBitmap(bitmap, mask);
//    }
//
//    Icon::Icon(DWORD icon)
//    : m_bHasOwnIcon(false)
//    {
//       HINSTANCE hInstance = GetModuleHandle(NULL);
//       m_hicon = LoadIcon(hInstance, MAKEINTRESOURCE(icon));
//    }
//


   Icon::~Icon()
   {
      if (m_bHasOwnIcon) {
         DestroyIcon(m_hicon);
      }
   }


   void Icon::initialize_icon(::innate_subsystem::IconInterface * picon)

   {
      m_bHasOwnIcon = true;
      ::cast < ::innate_subsystem_win32::Icon > piconWin32 = ::subsystem::get_implementation(picon);
      m_hicon = piconWin32->m_hicon;
   }

   void Icon::initialize_icon(innate_subsystem::BitmapInterface *pbitmap)

   {
      m_bHasOwnIcon = true;

      m_hicon = nullptr;

      Bitmap mask;
      mask.initialize_bitmap(pbitmap->getSize());
      fromBitmap(pbitmap, &mask);
   }

   void Icon::initialize_icon(::innate_subsystem::BitmapInterface *bitmap, ::innate_subsystem::BitmapInterface *mask)
   //:
   {
      m_bHasOwnIcon = true;
      m_hicon = nullptr;
      fromBitmap(bitmap, mask);
   }

   void Icon::initialize_icon(unsigned int icon)
   {
      m_bHasOwnIcon = false;
      HINSTANCE hInstance = GetModuleHandle(NULL);
      m_hicon = LoadIcon(hInstance, MAKEINTRESOURCE(icon));
   }



   // HICON Icon::getHICON()
   // {
   //    return m_hicon;
   // }

   void Icon::fromBitmap(::innate_subsystem::BitmapInterface *pbitmap, ::innate_subsystem::BitmapInterface *pbitmapMask)
   {
      ICONINFO ii;

      memset(&ii, 0, sizeof(ICONINFO));

      auto pbitmapWin32 = pbitmap->impl<innate_subsystem_win32::Bitmap>();
      auto pbitmapMaskWin32 = pbitmapMask->impl<innate_subsystem_win32::Bitmap>();

      ii.hbmColor = (pbitmapWin32 != 0) ? pbitmapWin32->m_hbitmap : 0;
      ii.hbmMask = (pbitmapMaskWin32 != 0) ? pbitmapMaskWin32->m_hbitmap : 0;

      m_hicon = CreateIconIndirect(&ii);
   }
} // namespace innate_subsystem_win32

