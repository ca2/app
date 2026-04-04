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


#include "remoting/remoting_common/util/CommonHeader.h"
#include "remoting/remoting_common/rfb/PixelFormat.h"
#include "acme/prototype/geometry2d/rectangle.h"


// This class get info for a windows desktop.
class CLASS_DECL_REMOTING_COMMON Screen
{
public:
  Screen();
  ~Screen();

  void update();

  // Returns a PixelFormat that was at latest call of the
  // update() function.
  PixelFormat getPixelFormat();

  // Returns a desktop dimension that was at latest call of the
  // update() function.
  // Desktop dimension is a dimension of windows virtual desktop including
  // all monitors.
  ::int_size getDesktopDimension();

  // Returns a rectangle that was at latest call of the
  // update() function.
  // The rectangle is a rectangle of windows virtual desktop including
  // all monitors (coordinates can be negative).
  ::int_rectangle getDesktopRect();

  // This structure can be used by user code.
  struct BMI
  {
    BITMAPINFOHEADER bmiHeader;
    unsigned int red;
    unsigned int green;
    unsigned int blue;
  };

  struct Palette8bitBMI
  {
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD rgbQuad[256];
  };

  // Fills the BMI structure. If dc == 0 the getBMI() function will
  // use a current desktop dc.
  void getBMI(BMI *bmi, HDC dc);

  // Windows contain both visible and invisible pseudo-monitors
  // that are associated with mirroring drivers.
  // The function returns only visible monitor count.
  size_t getVisibleMonitorCount();

private:
  void fillPixelFormat(const BMI *bmi);
  // Find position of first true bit
  static inline int findFirstBit(const unsigned int bits);

  void fillScreenRect();

  PixelFormat m_pixelFormat;
  ::int_rectangle m_virtDesktopRect;
};

//// __SCREEN_H__
