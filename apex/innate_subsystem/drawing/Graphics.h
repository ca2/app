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


#include "apex/innate_subsystem/_common_header.h"

// #include "apex/innate_subsystem/drawing/DeviceContext.h"
// #include "apex/innate_subsystem/drawing/Bitmap.h"
// #include "apex/innate_subsystem/drawing/Brush.h"
// #include "apex/innate_subsystem/drawing/Pen.h"

namespace innate_subsystem
{
   class CLASS_DECL_APEX GraphicsInterface :
   virtual public subsystem::particle_interface
   {
   public:
      // Creates graphics object with specified device context.
      ///Graphics(DeviceContext *dc);
      // Graphics class destructor.
      virtual ~GraphicsInterface() = 0;


      virtual void initialize_graphics(DeviceContextInterface *dc) = 0;

      // Sets background colors mix mode.
      virtual void setBkMode(bool transparent) = 0;
      // Sets background color.
      virtual void setBkColor(const ::color::color & color) = 0;

      // Sets text color.
      virtual void setTextColor(const ::color::color & color) = 0;
      // Sets current brush.
      virtual void setBrush(const BrushInterface *brush) = 0;
      // Sets current pen.
      virtual void setPen(const PenInterface *pen) = 0;

      // Moves cursor to specified position.
      virtual void moveTo(int x, int y) = 0;
      // Draws line from current position to specified line.
      virtual void lineTo(int x, int y) = 0;

      // Draws filled rect.
      virtual void fillRect(int l, int t, int r, int b, const BrushInterface*brush) = 0;
      // Draws ellipse.
      virtual void ellipse(int l, int t, int r, int b) = 0;
      // Draws rectance.
      virtual void rectangle(int l, int t, int r, int b) = 0;

      // Draws bitmap.
      virtual void drawBitmap(const BitmapInterface *bitmap, int x, int y, int w, int h) = 0;
      // Draws text.
      virtual void drawText(const char *text, int cchText, ::int_rectangle &rect, unsigned int format) = 0;

   //protected:
     //::pointer < DeviceContext > m_pdevicecontext;
   };


   class CLASS_DECL_APEX Graphics :
      virtual public subsystem::composite<GraphicsInterface>
   {
   public:
      // Creates graphics object with specified device context.
      ///Graphics(DeviceContext *dc);
      // Graphics class destructor.
      Graphics();
      ~Graphics() override;


      void initialize_graphics(DeviceContextInterface *dc) override;

      // Sets background colors mix mode.
      void setBkMode(bool transparent) override;
      // Sets background color.
      void setBkColor(const ::color::color & color) override;

      // Sets text color.
      void setTextColor(const ::color::color & color) override;
      // Sets current brush.
      void setBrush(const BrushInterface *brush) override;
      // Sets current pen.
      void setPen(const PenInterface *pen) override;

      // Moves cursor to specified position.
      void moveTo(int x, int y) override;
      // Draws line from current position to specified line.
      void lineTo(int x, int y) override;

      // Draws filled rect.
      void fillRect(int l, int t, int r, int b, const BrushInterface *brush) override;
      // Draws ellipse.
      void ellipse(int l, int t, int r, int b) override;
      // Draws rectance.
      void rectangle(int l, int t, int r, int b) override;

      // Draws bitmap.
      void drawBitmap(const BitmapInterface *bitmap, int x, int y, int w, int h) override;
      // Draws text.
      void drawText(const char *text, int cchText, ::int_rectangle &rect, unsigned int format) override;

      //protected:
      //::pointer < DeviceContext > m_pdevicecontext;
   };


} // namespace innate_subsystem