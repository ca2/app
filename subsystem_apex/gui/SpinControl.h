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
//#define _SPIN_CONTROL_H_

#include "subsystem_apex/Control.h"
////#include <CommCtrl.h>

namespace subsystem_apex
{

class SpinControlInterface :
   virtual public ::subsystem::particle_interface<SpinControlInterface>,
   public Control
{
public:
  //SpinControl();
  //virtual ~SpinControlInterface() = 0;

  virtual void setBuddy(ControlInterface *buddyControl)= 0;
  virtual void setRange(short lower, short upper)= 0;
  virtual void setRange32(int lower, int upper)= 0;
  virtual void setAccel(unsigned int nSec, unsigned int nInc)= 0;

  //
  // Auto acceleration methods
  //

  //
  // Handler, call it on UDN_DELTAPOS notification
  //

  //void autoAccelerationHandler(LPNMUPDOWN message)= 0;
  virtual void enableAutoAcceleration(bool enabled)= 0;
  virtual void setAutoAccelerationParams(const int_array & limitters,
                                 const int_array & deltas,
                                 int maxDelta)= 0;
// protected:
//   Control *m_buddy;
//
//   //
//   // Members needed for auto acceleration
//   //
//
//   bool m_isAutoAccelerationEnabled;
//   std::vector<int> m_limitters;
//   std::vector<int> m_deltas;
//   int m_maxDelta;
};

   class CLASS_DECL_APEX SpinControl :
   virtual public ::subsystem::composite < SpinControlInterface>
   {
   public:
      SpinControl();
      ~SpinControl() override;

      void setBuddy(ControlInterface *buddyControl)override;
      void setRange(short lower, short upper)override;
      void setRange32(int lower, int upper)override;
      void setAccel(unsigned int nSec, unsigned int nInc)override;

      //
      // Auto acceleration methods
      //

      //
      // Handler, call it on UDN_DELTAPOS notification
      //

      //void autoAccelerationHandler(LPNMUPDOWN message)override;
      void enableAutoAcceleration(bool enabled)override;
      void setAutoAccelerationParams(const int_array & limitters,
                                     const int_array & deltas,
                                     int maxDelta)override;
      // protected:
      //   Control *m_buddy;
      //
      //   //
      //   // Members needed for auto acceleration
      //   //
      //
      //   bool m_isAutoAccelerationEnabled;
      //   std::vector<int> m_limitters;
      //   std::vector<int> m_deltas;
      //   int m_maxDelta;
   };
} // namespace subsystem_apex

//#endif


