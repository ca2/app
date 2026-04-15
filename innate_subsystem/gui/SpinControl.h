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

#include "innate_subsystem/gui/Control.h"
//#include "innate_subsystem_windows/_common_header.h"
////#include <CommCtrl.h>

namespace innate_subsystem
{

class SpinControlSlice :
   virtual public ::particle_base
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

   using SpinControlInterface = particle_interface<SpinControlSlice, ControlInterface>;

   class CLASS_DECL_INNATE_SUBSYSTEM SpinControlComposite :
   virtual public composite < SpinControlSlice, Control>
   {
   public:


      implement_compositeø(SpinControl, Control, spincontrol)


      //SpinControl();
      //~SpinControl() ;

      void setBuddy(ControlInterface *buddyControl) { m_pspincontrol->setBuddy(buddyControl); }
      void setRange(short lower, short upper) { m_pspincontrol->setRange(lower, upper); }
      void setRange32(int lower, int upper) { m_pspincontrol->setRange32(lower, upper); }
      void setAccel(unsigned int nSec, unsigned int nInc) { m_pspincontrol->setAccel(nSec, nInc); }

      //
      // Auto acceleration methods
      //

      //
      // Handler, call it on UDN_DELTAPOS notification
      //

      //void autoAccelerationHandler(LPNMUPDOWN message);
      void enableAutoAcceleration(bool enabled) { m_pspincontrol->enableAutoAcceleration(enabled); }
      void setAutoAccelerationParams(const int_array & limitters,
                                     const int_array & deltas,
                                     int maxDelta) { m_pspincontrol->setAutoAccelerationParams(limitters, deltas, maxDelta); }
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


    class CLASS_DECL_INNATE_SUBSYSTEM SpinControl :
    virtual public SpinControlComposite,
    virtual public Control
   {
   public:





   };


} // namespace innate_subsystem

//#endif


