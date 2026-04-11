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


#include "acme/subsystem/particle.h"
#include "apex/innate_subsystem/drawing/GraphicsObject.h"


namespace innate_subsystem
{


   class CLASS_DECL_APEX BitmapInterface :
   virtual public ::subsystem::particle_interface<BitmapInterface>,
   virtual public GraphicsObject
   {
   public:
      // // Creates empty bitmap with specified size.
      // Bitmap(const ::int_size & size);
      // // Creates compatible with dc bitmap with specified size.
      // Bitmap(DeviceContext * pdevicecontext, const ::int_size & size);
      // // Creates bitmap from HBITMAP object.
      // Bitmap(Bitmap * pbitmap);
      // Destroys bitmap object.
      virtual ~BitmapInterface() =0;

      // Creates empty bitmap with specified size.
      virtual void initialize_bitmap(const ::int_size & size) = 0;
      // Creates compatible with dc bitmap with specified size.
      virtual void initialize_bitmap(DeviceContextInterface * pdevicecontext, const ::int_size & size) = 0;
      // Creates bitmap from HBITMAP object.
      virtual void initialize_bitmap(BitmapInterface * pbitmap) = 0;

      // Returns bitmap width.
      virtual ::int_size getSize() const = 0;


      //virtual void destroyObject() = 0;
      // Returns bitmap height.
      //virtual int getHeight() const = 0;
   // protected:
   //    HBITMAP m_bitmap;
   //
   //    friend class Icon;
   //    friend class Graphics;
   //    friend class BitmapGraphics;
   };


   class CLASS_DECL_APEX Bitmap :
      virtual public ::subsystem::composite < BitmapInterface >
   {
   public:
      // // Creates empty bitmap with specified size.
      // Bitmap(const ::int_size & size);
      // // Creates compatible with dc bitmap with specified size.
      // Bitmap(DeviceContext * pdevicecontext, const ::int_size & size);
      // // Creates bitmap from HBITMAP object.
      // Bitmap(Bitmap * pbitmap);
      Bitmap();
      // Destroys bitmap object.
      ~Bitmap() override;


      //void * _HGDIOBJ() override;

      // Creates empty bitmap with specified size.
      void initialize_bitmap(const ::int_size & size) override;
      // Creates compatible with dc bitmap with specified size.
      void initialize_bitmap(DeviceContextInterface * pdevicecontext, const ::int_size & size) override;
      // Creates bitmap from HBITMAP object.
      void initialize_bitmap(BitmapInterface * pbitmap) override;

      // Returns bitmap width.
      ::int_size getSize() const override;


      void destroyGraphicsObject() override;
      // Returns bitmap height.
      //int getHeight() const override;
      // protected:
      //    HBITMAP m_bitmap;
      //
      //    friend class Icon;
      //    friend class Graphics;
      //    friend class BitmapGraphics;
   };


} // namespace innate_subsystem


