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
#include "subsystem/platform/particle.h"

//#include "util/CommonHeader.h"
//#include "gui/PaintWindow.h"

namespace innate_subsystem
{


    class DeviceContextInterface :
      virtual public ::Particle
   {
   public:
      // Create device context linked to window DC.
      //DeviceContext(const ::operating_system::window & window);
      // Create device context complatible with other DC.
      //DeviceContext(DeviceContext* compatibleDevice);
      // Destroys device context.
      //virtual ~DeviceContextInterface() = 0;

      //private:
      // Initialize class from PaintWindow
      //DeviceContext(class PaintWindow * pntWnd);


       virtual void destroyDeviceContext() = 0;

       //private:
       // Initialize class from PaintWindow
       //virtual void initialize_device_context(PaintWindowInterface * pntWnd) = 0;
       // Create device context linked to window DC.
       virtual void initialize_device_context(const ::operating_system::window & window) = 0;
       // Create device context complatible with other DC.
       virtual void initialize_device_context(DeviceContextInterface* compatibleDevice) = 0;


      //friend class PaintWindow;

       virtual void _attachHDC(void *pHDC) = 0;

      //protected:
      // Selects an object into this device context.
      //HGDIOBJ _selectObject(HGDIOBJ object);

       virtual ::pointer < GraphicsObject > selectObject(GraphicsObject * pgraphicsobject) = 0;

      // protected:
      //   HDC m_dc;
      //   HWND m_wnd;
      //   bool m_hasOwnDC;
      //
      //   friend class Graphics;
      //   friend class BitmapGraphics;
   };


   //using DeviceContextInterface = particle_interface<DeviceContextInterface>;

   class CLASS_DECL_INNATE_SUBSYSTEM DeviceContextComposite :
      virtual public Composite < DeviceContextInterface >
   {
   public:


      ImplementCompositeø(DeviceContext, devicecontext)

      // Destroys device context.
      //DeviceContext();
      //~DeviceContext() override;

      //private:
      // Initialize class from PaintWindow
      //   void initialize_device_context(PaintWindowInterface* pntWnd) override
      //{

      //   m_pdevicecontext->initialize_device_context(pntWnd);
      //}
      // Create device context linked to window DC.
      void initialize_device_context(const ::operating_system::window& window) override
      {
         m_pdevicecontext->initialize_device_context(window);
      }
      // Create device context complatible with other DC.
      void initialize_device_context(DeviceContextInterface* compatibleDevice) override
      {
         m_pdevicecontext->initialize_device_context(compatibleDevice);
      }
      void _attachHDC(void* pHDC) override { m_pdevicecontext->_attachHDC(pHDC);

       }

      void destroyDeviceContext() override { m_pdevicecontext->destroyDeviceContext();

      }

      //friend class PaintWindow;

      //protected:
      // Selects an object into this device context.
      //HGDIOBJ _selectObject(HGDIOBJ object);

      // protected:
      //   HDC m_dc;
      //   HWND m_wnd;
      //   bool m_hasOwnDC;
      //
      //   friend class Graphics;
      //   friend class BitmapGraphics;
   };



    class CLASS_DECL_SUBSYSTEM DeviceContextAggregate :
    virtual public Aggregate< DeviceContextComposite >
    {
    public:

        ImplementBaseø(DeviceContext);

    };

   class CLASS_DECL_SUBSYSTEM DeviceContext :
   virtual public Object< DeviceContextAggregate >
   {
   public:

   };


} // namespace innate_subsystem
