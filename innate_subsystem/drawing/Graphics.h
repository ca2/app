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


#include "innate_subsystem/_common_header.h"

// #include "innate_subsystem/drawing/DeviceContext.h"
// #include "innate_subsystem/drawing/Bitmap.h"
// #include "innate_subsystem/drawing/Brush.h"
// #include "innate_subsystem/drawing/Pen.h"

namespace innate_subsystem
{


   class GraphicsInterface :
   virtual public ::subsystem::particle_interface<GraphicsInterface>
   {
   public:
      // Creates graphics object with specified device context.
      ///Graphics(DeviceContext *dc);
      // Graphics class destructor.
      //virtual ~GraphicsInterface() = 0;


      virtual DeviceContextInterface * device_context() = 0;


      virtual void initialize_graphics(DeviceContextInterface *dc) = 0;
      virtual void initialize_graphics(BitmapInterface *pbitmap) = 0;

      // Sets background colors mix mode.
      virtual void setBkMode(bool transparent) = 0;

      virtual void setBlendModeOn(bool bSet) = 0;

      virtual void setAntiAliasOn(bool bOn) = 0;

      // Sets background color.
      virtual void setBkColor(const ::color::color & color) = 0;

      // Sets text color.
      virtual void setTextColor(const ::color::color & color) = 0;

      virtual void setTextRenderingHintClearType() = 0;

      // Sets current brush.
      virtual void setBrush(BrushInterface *brush) = 0;
      // Sets current pen.
      virtual void setPen(PenInterface *pen) = 0;
      // Sets current font.
      virtual void setFont(FontInterface *font) = 0;

      // Moves cursor to specified position.
      virtual void moveTo(const ::int_point & point) = 0;
      // Draws line from current position to specified line.
      virtual void lineTo(const ::int_point & point) = 0;

      // Draws filled rect.
      //virtual void fillRect(int l, int t, int r, int b, BrushInterface*pbrush) = 0;
      virtual void fillRect(const ::int_rectangle & rectangle, BrushInterface * pbrush) = 0;
      virtual void fillRect(const ::int_rectangle & rectangle, const ::color::color & color) = 0;
      // Draws ellipse.
      virtual void ellipse(const ::int_rectangle & rectangle) = 0;
      // Draws rectance.
      virtual void rectangle(const ::int_rectangle & rectangle) = 0;

      // Draws bitmap.
      virtual void drawBitmap(BitmapInterface *bitmap, const ::int_rectangle & rectangle) = 0;
      virtual void drawBitmap(BitmapInterface *bitmap, const ::int_point & point, const ::int_rectangle & rectangleSrc) = 0;
      // Draws text.
      virtual void drawText(const char *text, int cchText, ::int_rectangle &rect, unsigned int format = 0, enum_align ealign = e_align_top_left) = 0;

   //protected:
     //::pointer < DeviceContext > m_pdevicecontext;
   };


   class CLASS_DECL_INNATE_SUBSYSTEM Graphics :
      virtual public ::subsystem::composite<GraphicsInterface>
   {
   public:
      // Creates graphics object with specified device context.
      ///Graphics(DeviceContext *dc);
      // Graphics class destructor.
      Graphics();
      ~Graphics() override;

      DeviceContextInterface * device_context() override;


      void initialize_graphics(DeviceContextInterface *dc) override;
      void initialize_graphics(BitmapInterface *pbitmap) override;

      // Sets background colors mix mode.
      void setBkMode(bool transparent) override;


      void setBlendModeOn(bool bSet) override;

      void setAntiAliasOn(bool bOn) override;

      // Sets background color.
      void setBkColor(const ::color::color & color) override;

      // Sets text color.
      void setTextColor(const ::color::color & color) override;

      void setTextRenderingHintClearType() override;

      // Sets current brush.
      void setBrush(BrushInterface *brush) override;
      // Sets current pen.
      void setPen(PenInterface *pen) override;
      // Sets current font.
      void setFont(FontInterface *font) override;

      // Moves cursor to specified position.
      void moveTo(const ::int_point & point) override;
      // Draws line from current position to specified line.
      void lineTo(const ::int_point & point) override;

      // Draws filled rect.
      //void fillRect(int l, int t, int r, int b, BrushInterface *pbrush) override;
      void fillRect(const ::int_rectangle & rectangle, BrushInterface * pbrush) override;
      void fillRect(const ::int_rectangle & rectangle, const ::color::color & color) override;
      // Draws ellipse.
      void ellipse(const ::int_rectangle & rectangle) override;
      // Draws rectance.
      void rectangle(const ::int_rectangle & rectangle) override;

      // Draws bitmap.
      void drawBitmap(BitmapInterface *bitmap, const ::int_rectangle & rectangle) override;
      void drawBitmap(BitmapInterface *bitmap, const ::int_point & point, const ::int_rectangle & rectangleSrc) override;
      // Draws text.
      void drawText(const char *text, int cchText, ::int_rectangle &rect, unsigned int format = 0, enum_align ealign = e_align_top_left) override;

      //protected:
      //::pointer < DeviceContext > m_pdevicecontext;
   };


} // namespace innate_subsystem