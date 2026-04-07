// Copyright (C) 2011,2012 GlavSoft LLC.
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
#include "acme/prototype/geometry2d/rectangle.h"
#include "Displays.h"


namespace  windows
{
   namespace subsystem
   {
      Displays::Displays()
      {
      }

      Displays::~Displays()
      {
      }

      // BOOL CALLBACK Displays::monitorEnumProc(HMONITOR hMonitor,
      //                                                HDC hdcMonitor,
      //                                                LPRECT lprcMonitor,
      //                                                LPARAM dwData)
      // {
      //    Displays *_this = (Displays *)dwData;
      //    ::int_rectangle rect(lprcMonitor->left - _this->m_xVirtualScreen,
      //              lprcMonitor->top - _this->m_yVirtualScreen,
      //              lprcMonitor->right - _this->m_xVirtualScreen,
      //              lprcMonitor->bottom - _this->m_yVirtualScreen);
      //    _this->m_displayRects.add(rect);
      //    return TRUE;
      // }

      // void Displays::update()
      // {
      //    m_pparticleThis->update();
      //    // if (!isAlreadyUpdated()) {
      //    //    m_displayRects.clear();
      //    //    m_xVirtualScreen = GetSystemMetrics(SM_XVIRTUALSCREEN);
      //    //    m_yVirtualScreen = GetSystemMetrics(SM_YVIRTUALSCREEN);
      //    //
      //    //    // Enumerate only desktop's displays. Skip mirror driver desktops.
      //    //    HDC hdc = GetDC(0);
      //    //    EnumDisplayMonitors(hdc, 0, monitorEnumProc, (LPARAM)this);
      //    //
      //    //    m_latestUpdateTime.Now();
      //    //    ReleaseDC(0, hdc);
      //    // }
      // }
      //
      // void Displays::getDisplayCoordinates(unsigned char displayNumber,
      //                                             ::int_rectangle *prectangle)
      // {
      //    m_pparticleThis->getDisplayCoordinates(displayNumber, prectangle);
      //    // AutoLock al(&m_displayRectsMutex);
      //    // update();
      //    // displayNumber--;
      //    // if (displayNumber < m_displayRects.size()) {
      //    //    *prectangle = m_displayRects[displayNumber];
      //    // } else {
      //    //    ::null(*prectangle);
      //    // }
      // }
      //
      // ::array_base<::int_rectangle> Displays::getDisplaysCoords()
      // {
      //    return m_pparticleThis->getDisplaysCoords();
      //    // AutoLock al(&m_displayRectsMutex);
      //    // update();
      //    // return m_displayRects;
      // }
      //
      // bool Displays::isAlreadyUpdated()
      // {
      //    return m_pparticleThis->isAlreadyUpdated();
      //    // if (m_latestUpdateTime.elapsed().m_iSecond > UPDATE_INTERVAL) {
      //    //    return false;
      //    // } else {
      //    //    return true;
      //    // }
      // }
      //
      // ::array_base<::int_rectangle> Displays::getDisplays()
      // {
      //    return m_pparticleThis->getDisplaysCoords();
      //    // update();
      //    // return m_displayRects;
      // }
   } // namespace subsystem
} // namespace  windows


