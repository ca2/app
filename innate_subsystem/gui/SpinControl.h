// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
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

class SpinControlInterface :
   virtual public ::Particle
{
public:
  //SpinControl();
  //virtual ~SpinControlInterface() = 0;

  virtual void setBuddy(ControlInterface *buddyControl)= 0;
  virtual void setRange(short lower, short upper)= 0;
  virtual void setRange32(int lower, int upper)= 0;
  virtual void setAccel(::u32 nSec, ::u32 nInc)= 0;

  //
  // Auto acceleration methods
  //

  //
  // Handler, call it on UDN_DELTAPOS notification
  //

  //void autoAccelerationHandler(LPNMUPDOWN message)= 0;
    virtual void autoAccelerationHandler(int & iPos, int & iDelta)= 0;
  virtual void enableAutoAcceleration(bool enabled)= 0;
  virtual void setAutoAccelerationParams(const i32_array & limitters,
                                 const i32_array & deltas,
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

   //using SpinControlInterface = particle_interface<SpinControlInterface, ControlInterface>;

   class CLASS_DECL_INNATE_SUBSYSTEM SpinControlComposite :
   virtual public Composite < SpinControlInterface>
   {
   public:


      ImplementCompositeø(SpinControl,  spincontrol)


      //SpinControl();
      //~SpinControl() ;

      void setBuddy(ControlInterface *buddyControl)  override{ m_pspincontrol->setBuddy(buddyControl); }
      void setRange(short lower, short upper)  override{ m_pspincontrol->setRange(lower, upper); }
      void setRange32(int lower, int upper) override { m_pspincontrol->setRange32(lower, upper); }
      void setAccel(::u32 nSec, ::u32 nInc)  override{ m_pspincontrol->setAccel(nSec, nInc); }

      //
      // Auto acceleration methods
      //

      //
      // Handler, call it on UDN_DELTAPOS notification
      //

      //void autoAccelerationHandler(LPNMUPDOWN message);
       void autoAccelerationHandler(int & iPos, int & iDelta) override{ m_pspincontrol->autoAccelerationHandler(iPos, iDelta); }
      void enableAutoAcceleration(bool enabled)  override{ m_pspincontrol->enableAutoAcceleration(enabled); }
      void setAutoAccelerationParams(const i32_array & limitters,
                                     const i32_array & deltas,
                                     int maxDelta) override { m_pspincontrol->setAutoAccelerationParams(limitters, deltas, maxDelta); }
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


    class CLASS_DECL_INNATE_SUBSYSTEM SpinControlAggregate :
    virtual public Aggregate< SpinControlComposite, Control >

   {
   public:


      ImplementAggregateø(SpinControl, Control)


   };


   class CLASS_DECL_INNATE_SUBSYSTEM  SpinControl:
virtual public Object<SpinControlAggregate>
   {
   public:

      ImplementObjectø(SpinControl)

   };



} // namespace innate_subsystem

//#endif


