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

#include "innate_subsystem/drawing/Graphics.h"
#include "innate_subsystem/drawing/Bitmap.h"


namespace innate_subsystem
{
   //
   // Object that creates bitmap with specified size and allow to
   // draw into in through Graphics class methods.
   class BitmapGraphicsInterface :
   virtual public ::Particle
   {
   public:
      // Creates BitmapGraphics object with bitmap complatible with specified dc and
      // with specified size.
      //BitmapGraphics(DeviceContext *complatibleDC, const ::int_size & size);
      // Destroys bitmap and graphics object.
      //virtual ~BitmapGraphicsInterface() = 0;


      virtual void initialize_bitmap_graphics(DeviceContextInterface * pdevicecontextCompatible, const ::int_size & size) = 0;

      // Returns target bitmap that we paint.
      virtual BitmapInterface *getBitmap() = 0;

      virtual void beginPaint() = 0;
      virtual void endPaint() = 0;

   //protected:
      // bool m_isPainting;
      // Bitmap *m_bitmap;
      // HGDIOBJ m_oldBitmap;
   };

    //using BitmapGraphicsInterface = particle_interface<BitmapGraphicsInterface, Graphics>;


   //
   // Object that creates bitmap with specified size and allow to
   // draw into in through Graphics class methods.
   class CLASS_DECL_INNATE_SUBSYSTEM BitmapGraphicsComposite :
    virtual public Composite<BitmapGraphicsInterface>
   {
   public:

       ImplementCompositeø(BitmapGraphics, bitmapgraphics)
      // Creates BitmapGraphics object with bitmap complatible with specified dc and
      // with specified size.
      //BitmapGraphics(DeviceContext *complatibleDC, const ::int_size & size);

      //BitmapGraphics();
      // Destroys bitmap and graphics object.
      //~BitmapGraphics() override;

          void initialize_bitmap_graphics(DeviceContextInterface* complatibleDC, const ::int_size& size) override
       {

          m_pbitmapgraphics->initialize_bitmap_graphics(complatibleDC, size);
       }

      // Returns target bitmap that we paint.
       BitmapInterface* getBitmap() override
       {

          return m_pbitmapgraphics->getBitmap();
      }

       void beginPaint() override
       {

          m_pbitmapgraphics->beginPaint();
      }
       void endPaint() override
       {

          m_pbitmapgraphics->endPaint();

      }

      //protected:
      // bool m_isPainting;
      // Bitmap *m_bitmap;
      // HGDIOBJ m_oldBitmap;
   };


   class CLASS_DECL_INNATE_SUBSYSTEM BitmapGraphicsAggregate :
    virtual public Aggregate<BitmapGraphicsComposite, Graphics>
   {
   public:


      ImplementAggregateø(BitmapGraphics, Graphics)


   };


   class CLASS_DECL_INNATE_SUBSYSTEM BitmapGraphics :
    virtual public Object<BitmapGraphicsAggregate>
   {
   public:


   };


} // namespace innate_subsystem