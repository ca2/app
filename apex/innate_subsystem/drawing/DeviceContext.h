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
#include "acme/subsystem/particle.h"

//#include "util/CommonHeader.h"
//#include "gui/PaintWindow.h"

namespace innate_subsystem
{
   class CLASS_DECL_ACME DeviceContext :
      virtual public ::subsystem::particle_interface
   {
   public:
      // Create device context linked to window DC.
      DeviceContext(const ::operating_system::window & window);
      // Create device context complatible with other DC.
      DeviceContext(DeviceContext* compatibleDevice);
      // Destroys device context.
      virtual ~DeviceContext() = 0;

      //private:
      // Initialize class from PaintWindow
      DeviceContext(class PaintWindow * pntWnd);

      friend class PaintWindow;

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
} // namespace innate_subsystem
