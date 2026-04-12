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
#include "Graphics.h"

namespace innate_subsystem
{
   // Graphics::Graphics(DeviceContext *dc)
   // : m_dc(dc)
   // {
   // }
   Graphics::Graphics()
   //: m_dc(dc)
   {
   }


   Graphics::~Graphics()
   {
   }


   DeviceContextInterface * Graphics::device_context()
   {

      return m_pparticleThis->device_context();

   }

   void Graphics::initialize_graphics(DeviceContextInterface *pdevicecontext)
//: m_dc(dc)
   {
      m_pparticleThis->initialize_graphics(pdevicecontext);
   }

   void Graphics::initialize_graphics(BitmapInterface *pbitmap)
   {
      m_pparticleThis->initialize_graphics(pbitmap);
   }

   void Graphics::setBkMode(bool transparent)
   {
      //SetBkMode(m_dc->m_dc, transparent ? TRANSPARENT : OPAQUE);
      m_pparticleThis->setBkMode(transparent);
   }

   void Graphics::setBlendModeOn(bool bSet)
   {

      m_pparticleThis->setBlendModeOn(bSet);

   }

   void Graphics::setAntiAliasOn(bool bOn)
   {

      m_pparticleThis->setAntiAliasOn(bOn);

   }


   void Graphics::setTextColor(const ::color::color & color)
   {
      //SetTextColor(m_dc->m_dc, color);
      m_pparticleThis->setTextColor(color);
   }


   void Graphics::setTextRenderingHintClearType()
   {

      m_pparticleThis->setTextRenderingHintClearType();

   }

   void Graphics::setBkColor(const ::color::color & color)
   {
      //SetBkColor(m_dc->m_dc, color);
      m_pparticleThis->setBkColor(color);
   }

   void Graphics::setBrush(BrushInterface *pbrush)
   {
      // HGDIOBJ object = (brush != 0) ? brush->m_brush : 0;
      // m_dc->selectObject(object);
      m_pparticleThis->setBrush(pbrush);
   }

   void Graphics::setPen(PenInterface *ppen)
   {
      // HGDIOBJ object = (pen != 0) ? pen->m_pen : 0;
      // m_dc->selectObject(object);
      m_pparticleThis->setPen(ppen);
   }

   void Graphics::setFont(FontInterface *pfont)
   {
      // HGDIOBJ object = (pen != 0) ? pen->m_pen : 0;
      // m_dc->selectObject(object);
      m_pparticleThis->setFont(pfont);
   }
   void Graphics::moveTo(const ::int_point & point)
   {
      //MoveToEx(m_dc->m_dc, x, y, NULL);
      m_pparticleThis->moveTo(point);
   }

   void Graphics::lineTo(const ::int_point & point)
   {
      //LineTo(m_dc->m_dc, x, y);
      m_pparticleThis->lineTo(point);
   }

   void Graphics::fillRect(const ::int_rectangle & rectangle, BrushInterface *pbrush)
   {
      //    RECT rect;
      //
      //    rect.top = t;
      //    rect.left = l;
      //    rect.bottom = b;
      //    rect.right = r;
      //
      //    FillRect(m_dc->m_dc, &rect, brush->m_brush);
      // }
      m_pparticleThis->fillRect(rectangle, pbrush);
   }

   void Graphics::fillRect(const ::int_rectangle & rectangle, const ::color::color & color)
   {

      m_pparticleThis->fillRect(rectangle, color);

   }

   void Graphics::ellipse(const ::int_rectangle & rectangle)
   {
      //Ellipse(m_dc->m_dc, l, t, r, b);
      m_pparticleThis->ellipse(rectangle);
   }

   void Graphics::rectangle(const ::int_rectangle & rectangle)
   {

      m_pparticleThis->rectangle(rectangle);
   }


   void Graphics::drawBitmap(BitmapInterface *pbitmap, const ::int_rectangle & rectangle)
   {

      m_pparticleThis->drawBitmap(pbitmap, rectangle);
      // DeviceContext memDC(m_dc);
      //
      // HGDIOBJ oldBitmap = memDC.selectObject(bitmap->m_bitmap);
      //
      // BitBlt(m_dc->m_dc, x, y, w, h, memDC.m_dc, 0, 0, SRCCOPY);
      //
      // memDC.selectObject(oldBitmap);
   }

   void Graphics::drawBitmap(BitmapInterface *pbitmap, const ::int_point & point, const ::int_rectangle & rectangle)
   {

      m_pparticleThis->drawBitmap(pbitmap, point, rectangle);

   }


   void Graphics::drawText(const char *text, int cchText, ::int_rectangle &rect, unsigned int format, enum_align ealign)
   {
      m_pparticleThis->drawText(text, cchText, rect, format, ealign);
   }
} // namespace innate_subsystem


