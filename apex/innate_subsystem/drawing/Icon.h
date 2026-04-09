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

#pragma once


//#include "util/CommonHeader.h"

#include "apex/innate_subsystem/drawing/Bitmap.h"

namespace innate_subsystem
{
   class CLASS_DECL_APEX IconInterface :
   virtual public ::subsystem::particle_interface<IconInterface>
   {
   public:
      // Icon();
      // Icon(Icon * picon);
      // Icon(Bitmap *bitmap);
      // Icon(Bitmap *bitmap, Bitmap *mask);
      // Icon(unsigned int icon);
      //virtual ~IconInterface() = 0;

      virtual void initialize_icon(IconInterface * picon) = 0;
      virtual void initialize_icon(BitmapInterface *bitmap) = 0;
      virtual void initialize_icon(BitmapInterface *bitmap, BitmapInterface *mask) = 0;
      virtual void initialize_icon(unsigned int icon) = 0;

      virtual void * _HICON() = 0;

   //protected:
      virtual void fromBitmap(BitmapInterface *bitmap, BitmapInterface *mask) = 0;

   // protected:
   //    HICON m_icon;
   //    bool m_hasOwnIcon;
   };


   class CLASS_DECL_APEX Icon :
virtual public ::subsystem::composite<IconInterface>
   {
   public:
      Icon();
      // Icon(Icon * picon);
      // Icon(Bitmap *bitmap);
      // Icon(Bitmap *bitmap, Bitmap *mask);
      // Icon(unsigned int icon);
      ~Icon() override;

      virtual void initialize_icon(IconInterface * picon) override;
      virtual void initialize_icon(BitmapInterface *bitmap) override;
      virtual void initialize_icon(BitmapInterface *bitmap, BitmapInterface *mask) override;
      virtual void initialize_icon(unsigned int icon) override;

      void * _HICON() override;

      //protected:
      void fromBitmap(BitmapInterface *bitmap, BitmapInterface *mask) override;

      // protected:
      //    HICON m_icon;
      //    bool m_hasOwnIcon;
   };
} // namespace innate_subsystem


