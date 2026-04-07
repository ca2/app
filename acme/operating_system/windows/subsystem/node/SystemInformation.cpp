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
#include "acme/operating_system/windows/subsystem/_common_header.h"
#include "SystemInformation.h"
#include "acme/prototype/geometry2d/rectangle.h"

namespace windows
{
   namespace subsystem
   {
      void SystemInformation::getDesktopAllArea(int_rectangle & rectangle)
      {
         RECT rc;
         if (GetClientRect(GetDesktopWindow(), &rc))
         {
            ::copy(rectangle, rc);
         }
      }

      bool SystemInformation::getDesktopArea(int_rectangle & rectangle)
      {
         RECT rc;
         bool bOk = !!SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);
if (bOk)
{
   ::copy(rectangle, rc);

}
         return bOk;
      }

      bool SystemInformation::_isSupportStretchBlt(HDC hdc)
      {
         int rasterCaps = GetDeviceCaps(hdc, RASTERCAPS);
         return !!(rasterCaps & RC_STRETCHBLT);
      }

      int SystemInformation::_getBitsPixel(HDC hdc)
      {
         return GetDeviceCaps(hdc, BITSPIXEL);
      }

      int SystemInformation::getMonitorCount()
      {
         return GetSystemMetrics(SM_CMONITORS);
      }
   } // namespace subsystem
} //namespace  windows