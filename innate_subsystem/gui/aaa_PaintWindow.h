// Copyright (C) 2012 GlavSoft LLC.
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


#include "innate_subsystem/gui/Window.h"
//#include "drawing/DeviceContext.h"

namespace innate_subsystem
{


   class PaintWindowInterface:
   virtual public ::Particle
   {
   public:
      //PaintWindow();
      //virtual ~PaintWindowInterface() = 0;

   //private:
      virtual ::pointer < DeviceContextInterface > getPaintDeviceContext() = 0;

      //friend class DeviceContext;

   //protected:
      //virtual void onPaint(DeviceContext *dc, PAINTSTRUCT *paintStruct);
      virtual void onPaint(DeviceContextInterface *pdevicecontext, const ::int_rectangle & rectangle) = 0;

      //bool wndProc(unsigned int message, ::wparam wparam, ::lparam lparam);

      //bool m_bIsDraw;
      //PAINTSTRUCT m_paintStruct;
      //::int_rectangle m_rectangle;
      //::pointer < DeviceContext > m_pdevicecontext;
      //HDC m_hdc;

   };
   class CLASS_DECL_INNATE_SUBSYSTEM PaintWindowCallback : virtual public Callback<PaintWindowInterface>
   {
   public:

      ImplementCallbackø(PaintWindow, paintwindow)
   };

   //using PaintWindowInterface = particle_interface<PaintWindowInterface, WindowInterface>;

       class CLASS_DECL_INNATE_SUBSYSTEM PaintWindowComposite:
   virtual public Composite<PaintWindowInterface >
   {
   public:

          ImplementCompositeWithCallbackø(PaintWindow, paintwindow)
      //PaintWindow();
      //~PaintWindow();

   //private:
      ::pointer < DeviceContextInterface > getPaintDeviceContext() { return m_ppaintwindow->getPaintDeviceContext(); }

      //friend class DeviceContext;

   //protected:
      //virtual void onPaint(DeviceContext *dc, PAINTSTRUCT *paintStruct);
      void onPaint(DeviceContextInterface *pdevicecontext, const ::int_rectangle & rectangle) {  }

      //bool wndProc(unsigned int message, ::wparam wparam, ::lparam lparam);

      //bool m_bIsDraw;
      //PAINTSTRUCT m_paintStruct;
      //::int_rectangle m_rectangle;
      //::pointer < DeviceContext > m_pdevicecontext;
      //HDC m_hdc;

   };

   class CLASS_DECL_INNATE_SUBSYSTEM PaintWindowAggregate:
virtual public Aggregate<PaintWindowComposite, WindowAggregate >
   {
   public:

      ImplementAggregateø(PaintWindow, Window)

   };

   class CLASS_DECL_INNATE_SUBSYSTEM PaintWindow :
virtual public Object<PaintWindowAggregate>
   {
   public:

      ImplementObjectø(PaintWindow)

   };


} // namespace innate_subsystem

