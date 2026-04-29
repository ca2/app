// Copyright (C) 2011,2012 GlavSoft LLC.
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


#include "subsystem/_common_header.h"
#include "subsystem/framebuffer/PixelFormat.h"
#include "acme/prototype/geometry2d/rectangle.h"

namespace subsystem
{

   // This class get info for a windows desktop.
   class ScreenInterface :
      virtual public ::Particle
   {
   public:


      //Screen();
      //virtual ~ScreenInterface() = 0;

      virtual void update() = 0;

      // Returns a PixelFormat that was at latest call of the
      // update() function.
      virtual ::innate_subsystem::PixelFormat getPixelFormat() = 0;

      // Returns a desktop dimension that was at latest call of the
      // update() function.
      // Desktop dimension is a dimension of windows virtual desktop including
      // all monitors.
      virtual ::int_size getDesktopDimension() = 0;

      // Returns a rectangle that was at latest call of the
      // update() function.
      // The rectangle is a rectangle of windows virtual desktop including
      // all monitors (coordinates can be negative).
      virtual ::int_rectangle getDesktopRect() = 0;

      // // This structure can be used by user code.
      // struct BMI
      // {
      //    BITMAPINFOHEADER bmiHeader;
      //    unsigned int red;
      //    unsigned int green;
      //    unsigned int blue;
      // };

      // struct Palette8bitBMI
      // {
      //    BITMAPINFOHEADER bmiHeader;
      //    RGBQUAD rgbQuad[256];
      // };

      // Fills the BMI structure. If dc == 0 the getBMI() function will
      // use a current desktop dc.
      //void getBMI(BMI *bmi, HDC dc);

      // Windows contain both visible and invisible pseudo-monitors
      // that are associated with mirroring drivers.
      // The function returns only visible monitor count.
      virtual int getVisibleMonitorCount() = 0;

      //private:
      // void fillPixelFormat(const BMI *bmi);
      // Find position of first true bit
      virtual int findFirstBit(const unsigned int bits) = 0;

      virtual void fillScreenRect() = 0;

      //PixelFormat m_pixelformat;
      //::int_rectangle m_virtDesktopRect;
   };


    //using ScreenInterface = particle_interface<ScreenInterface>;

   // This class get info for a windows desktop.
   class CLASS_DECL_SUBSYSTEM ScreenComposite :
      virtual public Composite<ScreenInterface >
   {
   public:

       ImplementCompositeø(Screen, screen)


          void update() override
       {

          m_pscreen->update();
       }

      // Returns a PixelFormat that was at latest call of the
      // update() function.
       ::innate_subsystem::PixelFormat getPixelFormat() override
       {

          return m_pscreen->getPixelFormat();

      }

      // Returns a desktop dimension that was at latest call of the
      // update() function.
      // Desktop dimension is a dimension of windows virtual desktop including
      // all monitors.
       ::int_size getDesktopDimension() override
       {

          return m_pscreen->getDesktopDimension();

      }

      // Returns a rectangle that was at latest call of the
      // update() function.
      // The rectangle is a rectangle of windows virtual desktop including
      // all monitors (coordinates can be negative).
       ::int_rectangle getDesktopRect() override
       {

          return m_pscreen->getDesktopRect();

      }

      // // This structure can be used by user code.
      // struct BMI
      // {
      //    BITMAPINFOHEADER bmiHeader;
      //    unsigned int red;
      //    unsigned int green;
      //    unsigned int blue;
      // };
      //
      // struct Palette8bitBMI
      // {
      //    BITMAPINFOHEADER bmiHeader;
      //    RGBQUAD rgbQuad[256];
      // };

      // Fills the BMI structure. If dc == 0 the getBMI() function will
      // use a current desktop dc.
      //void getBMI(BMI *bmi, HDC dc);

      // Windows contain both visible and invisible pseudo-monitors
      // that are associated with mirroring drivers.
      // The function returns only visible monitor count.
       int getVisibleMonitorCount() override
       {

          return m_pscreen->getVisibleMonitorCount();

      }

   //private:
      //void fillPixelFormat(const BMI *bmi);
      // Find position of first true bit
       int findFirstBit(const unsigned int bits) override
       {

          return m_pscreen->findFirstBit(bits);

      }

       void fillScreenRect() override
       {

          m_pscreen->fillScreenRect();

      }

      // PixelFormat m_pixelformat;
      // ::int_rectangle m_virtDesktopRect;
   };



    class CLASS_DECL_SUBSYSTEM ScreenAggregate :
    virtual public Aggregate< ScreenComposite >
    {
    public:

        ImplementBaseø(Screen);

    };

   class CLASS_DECL_SUBSYSTEM Screen :
    virtual public Object <ScreenAggregate >
   {
   public:

      ImplementObjectø(Screen)

   };


} // namespace  subsystem