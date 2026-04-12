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
#include "Icon.h"

namespace innate_subsystem
{
   Icon::Icon()
   //: m_hasOwnIcon(true), m_icon(NULL)
   {
   }

   // Icon::Icon(HICON icon)
   // : m_hasOwnIcon(true), m_icon(icon)
   // {
   // }
   //
   // Icon::Icon(Bitmap *bitmap)
   // : m_hasOwnIcon(true), m_icon(NULL)
   // {
   //    Bitmap mask(bitmap->getWidth(), bitmap->getHeight());
   //    fromBitmap(bitmap, &mask);
   // }
   //
   // Icon::Icon(Bitmap *bitmap, Bitmap *mask)
   // : m_hasOwnIcon(true), m_icon(NULL)
   // {
   //    fromBitmap(bitmap, mask);
   // }
   //
   // Icon::Icon(unsigned int icon)
   // : m_hasOwnIcon(false)
   // {
   //    HINSTANCE hInstance = GetModuleHandle(NULL);
   //    m_icon = LoadIcon(hInstance, MAKEINTRESOURCE(icon));
   //}

   Icon::~Icon()
   {
      // if (m_hasOwnIcon) {
      //    DestroyIcon(m_icon);
      // }
   }


   void Icon::initialize_icon(IconInterface * picon)
//: m_hasOwnIcon(true), m_icon(icon)
   {
      m_pparticleThis->initialize_icon(picon);
   }

   void Icon::initialize_icon(BitmapInterface *pbitmap)
   //: m_hasOwnIcon(true), m_icon(NULL)
   {
      m_pparticleThis->initialize_icon(pbitmap);
      //Bitmap mask(bitmap->getWidth(), bitmap->getHeight());
      //fromBitmap(bitmap, &mask);
   }

   void Icon::initialize_icon(BitmapInterface *bitmap, BitmapInterface *mask)
   //: m_hasOwnIcon(true), m_icon(NULL)
   {
      m_pparticleThis->initialize_icon(bitmap, mask);
      //;;fromBitmap(bitmap, mask);
   }


   void * Icon::_HICON()
   {
       return m_pparticleThis->_HICON();
   }

   void Icon::fromBitmap(BitmapInterface *bitmap, BitmapInterface *mask)
   {

      m_pparticleThis->fromBitmap(bitmap, mask);
      // ICONINFO ii;
      //
      // memset(&ii, 0, sizeof(ICONINFO));
      //
      // ii.hbmColor = (bitmap != 0) ? bitmap->m_bitmap : 0;
      // ii.hbmMask = (mask != 0) ? mask->m_bitmap : 0;
      //
      // m_icon = CreateIconIndirect(&ii);
   }
} // namespace innate_subsystem