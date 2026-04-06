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

#pragma once


#include "acme/subsystem/_common_header.h"

namespace subsystem
{


   class CLASS_DECL_ACME SystemInformationInterface :
   virtual public ::subsystem::particle_interface
   {
   public:

      // get rectangle of all desktop area
      virtual void getDesktopAllArea(int_rectangle & rectangle) = 0;

      // get rectangle of user desktop area
      // without button 'Start' (only primary monitor).
      virtual bool getDesktopArea(int_rectangle & rectangle) = 0;

      // return true if StretchBlt is used
      // in provided device
      //virtual bool isSupportStretchBlt(HDC hdc) = 0;

      // return how many bits per pixel
      // for provided device
      //virtual int getBitsPixel(HDC hdc) = 0;

      // get the number of monitors that plugged
      // into video card
      virtual int getMonitorCount() = 0;
   };

   class CLASS_DECL_ACME SystemInformation :
   virtual public ::subsystem::composite<SystemInformationInterface>
   {
   public:

      SystemInformation();

      ~SystemInformation() override;

      // get rectangle of all desktop area
      void getDesktopAllArea(int_rectangle & rectangle) override;

      // get rectangle of user desktop area
      // without button 'Start' (only primary monitor).
      bool getDesktopArea(int_rectangle & rectangle) override;

      // // return true if StretchBlt is used
      // // in provided device
      // bool isSupportStretchBlt(HDC hdc);
      //
      // // return how many bits per pixel
      // // for provided device
      // int getBitsPixel(HDC hdc);

      // get the number of monitors that plugged
      // into video card
      int getMonitorCount() override;
   };

} // namespace subsystem


