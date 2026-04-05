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
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "SystemInformation.h"
#include "acme/prototype/geometry2d/rectangle.h"

namespace subsystem
{


   SystemInformation::~SystemInformation()
   {


   }


   SystemInformation::SystemInformation()
   {



   }


   ::int_rectangle SystemInformation::getDesktopAllArea()
   {
//      GetClientRect(GetDesktopWindow(), rc);
      return m_pparticleThis->getDesktopAllArea();
   }

   ::int_rectangle SystemInformation::getDesktopArea()
   {
  //    return !!SystemParametersInfo(SPI_GETWORKAREA, 0, rc, 0);

      return m_pparticleThis->getDesktopArea();
   }

   // bool SystemInformation::isSupportStretchBlt(HDC hdc)
   // {
   //  //  int rasterCaps = GetDeviceCaps(hdc, RASTERCAPS);
   //    //return !!(rasterCaps & RC_STRETCHBLT);
   // }
   //
   // int SystemInformation::getBitsPixel(HDC hdc)
   // {
   //    //return GetDeviceCaps(hdc, BITSPIXEL);
   // }

   int SystemInformation::getMonitorCount()
   {//return GetSystemMetrics(SM_CMONITORS);


      return m_pparticleThis->getMonitorCount();
   }

} // namespace subsystem


