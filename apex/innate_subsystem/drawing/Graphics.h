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

#include "apex/innate_subsystem/drawing/DeviceContext.h"
#include "apex/innate_subsystem/drawing/Bitmap.h"
#include "apex/innate_subsystem/drawing/Brush.h"
#include "apex/innate_subsystem/drawing/Pen.h"

namespace innate_subsystem
{
   class Graphics
   {
   public:
      // Creates graphics object with specified device context.
      Graphics(DeviceContext *dc);
      // Graphics class destructor.
      virtual ~Graphics();

      // Sets background colors mix mode.
      void setBkMode(bool transparent);
      // Sets background color.
      void setBkColor(COLORREF color);

      // Sets text color.
      void setTextColor(COLORREF color);
      // Sets current brush.
      void setBrush(const Brush *brush);
      // Sets current pen.
      void setPen(const Pen *pen);

      // Moves cursor to specified position.
      void moveTo(int x, int y);
      // Draws line from current position to specified line.
      void lineTo(int x, int y);

      // Draws filled rect.
      void fillRect(int l, int t, int r, int b, const Brush *brush);
      // Draws ellipse.
      void ellipse(int l, int t, int r, int b);
      // Draws rectance.
      void rectangle(int l, int t, int r, int b);

      // Draws bitmap.
      void drawBitmap(const Bitmap *bitmap, int x, int y, int w, int h);
      // Draws text.
      void drawText(const TCHAR *text, int cchText, ::int_rectangle &rect, unsigned int format);

   protected:
      DeviceContext *m_dc;
   };


} // namespace innate_subsystem