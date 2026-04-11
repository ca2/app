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

   void Graphics::moveTo(int x, int y)
   {
      //MoveToEx(m_dc->m_dc, x, y, NULL);
      m_pparticleThis->moveTo(x, y);
   }

   void Graphics::lineTo(int x, int y)
   {
      //LineTo(m_dc->m_dc, x, y);
      m_pparticleThis->lineTo(x, y);
   }

   void Graphics::fillRect(int l, int t, int r, int b, BrushInterface *pbrush)
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
      m_pparticleThis->fillRect(l, t, r, b, pbrush);
   }

   void Graphics::fillRect(const ::int_rectangle & rectangle, const ::color::color & color)
   {

      m_pparticleThis->fillRect(rectangle, color);

   }

   void Graphics::ellipse(int l, int t, int r, int b)
   {
      //Ellipse(m_dc->m_dc, l, t, r, b);
      m_pparticleThis->ellipse(l, t, r, b);
   }

   void Graphics::rectangle(int l, int t, int r, int b)
   {

      m_pparticleThis->rectangle(l, t, r, b);
   }


   void Graphics::drawBitmap(BitmapInterface *pbitmap, int x, int y, int w, int h)
   {

      m_pparticleThis->drawBitmap(pbitmap, x, y, w, h);
      // DeviceContext memDC(m_dc);
      //
      // HGDIOBJ oldBitmap = memDC.selectObject(bitmap->m_bitmap);
      //
      // BitBlt(m_dc->m_dc, x, y, w, h, memDC.m_dc, 0, 0, SRCCOPY);
      //
      // memDC.selectObject(oldBitmap);
   }

   void Graphics::drawBitmap(BitmapInterface *pbitmap, int x, int y, int srcx, int srcy, int srcW, int srcH)
   {

      m_pparticleThis->drawBitmap(pbitmap, x, y, srcx, srcy, srcW, srcH);

   }


   void Graphics::drawText(const char *text, int cchText, ::int_rectangle &rect, unsigned int format)
   {
      m_pparticleThis->drawText(text, cchText, rect, format);
   }
} // namespace innate_subsystem


