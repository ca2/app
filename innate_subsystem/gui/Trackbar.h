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

//#ifndef _TRACKBAR_H_
//#define _TRACKBAR_H_

#pragma once

#include "innate_subsystem/Control.h"


namespace innate_subsystem
{
    class TrackbarInterface :
   virtual public ::subsystem::particle_interface<TrackbarInterface>,
         virtual public ::innate_subsystem::Control
    {
    public:

        //Trackbar();
        //virtual ~TrackbarInterface() = 0;

        // Sets the range of minimum and maximum logical positions for the slider.
        virtual void setRange(long min, long max) = 0;

        // Sets the current logical position of the slider.
        virtual void setPos(long pos) = 0;

        // Returns the current logical position of the slider.
        virtual long getPos() = 0;
    };

   class CLASS_DECL_INNATE_SUBSYSTEM Trackbar :
      virtual public ::subsystem::composite < TrackbarInterface  >
   {
   public:
      Trackbar();
      ~Trackbar() override;

      // Sets the range of minimum and maximum logical positions for the slider.
      void setRange(long min, long max) override;

      // Sets the current logical position of the slider.
      void setPos(long pos) override;

      // Returns the current logical position of the slider.
      long getPos() override;
   };

    //#endif
} // namespace innate_subsystem

