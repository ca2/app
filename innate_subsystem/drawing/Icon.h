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

#include "innate_subsystem/drawing/Bitmap.h"

namespace innate_subsystem
{
   class IconInterface :
   //virtual public particle_interface<IconInterface>
   virtual public ::Particle
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


   class CLASS_DECL_INNATE_SUBSYSTEM IconComposite :
virtual public Composite<IconInterface>
   {
   public:


      ImplementCompositeø(Icon, icon)

      //Icon();
      // Icon(Icon * picon);
      // Icon(Bitmap *bitmap);
      // Icon(Bitmap *bitmap, Bitmap *mask);
      // Icon(unsigned int icon);
      //~Icon() override;

      void initialize_icon(IconInterface* picon) override
      {
         m_picon->initialize_icon(picon);
      }
      void initialize_icon(BitmapInterface* bitmap) override { m_picon->initialize_icon(bitmap);
      }
      void initialize_icon(BitmapInterface* bitmap, BitmapInterface* mask) override
      {
         m_picon->initialize_icon(bitmap, mask);
      }
      void initialize_icon(unsigned int icon) override { m_picon->initialize_icon(icon);
      }

      void* _HICON() override { return m_picon->_HICON();

      }

      //protected:
      void fromBitmap(BitmapInterface* bitmap, BitmapInterface* mask) override
      {

        m_picon->fromBitmap(bitmap, mask);
      }

      // protected:
      //    HICON m_icon;
      //    bool m_hasOwnIcon;
   };



    class CLASS_DECL_INNATE_SUBSYSTEM IconAggregate :
    virtual public Aggregate< IconComposite >
    {
    public:

        ImplementBaseø(Icon);

    };

   class CLASS_DECL_INNATE_SUBSYSTEM Icon :
   virtual public Object< IconAggregate >
   {
   public:

      ImplementObjectø(Icon)

   };



} // namespace innate_subsystem


