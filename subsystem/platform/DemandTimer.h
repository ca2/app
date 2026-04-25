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

#pragma once


//#include "::earth::time.h"

namespace subsystem
{
   // This class help to measure time intervals. On a time interval elapse the
   // timer only change self state. It doesn't call a callback function.
   class DemandTimer
   {
   public:

      DemandTimer(const class ::time & time);
      ~DemandTimer();

      // Starts the timer from the now time.
      void reset();

      // Returns true if timer time is elapsed.
      bool isElapsed();

      class ::time m_timeTimer;
      class ::time m_timeStart;


   };


} // namespace subsystem



