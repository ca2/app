// Copyright (C) 2010,2011,2012 GlavSoft LLC.
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


////#include "remoting/remoting_common/util/winhdr.h"
#include "acme/_operating_system.h"


//#include "SystemException.h"
#include "subsystem/particle.h"


namespace subsystem
{
   /**
    * Wrapper on WinAPI workstation functions.
    */
   class WorkstationInterface :
      virtual public ::subsystem::particle_interface<WorkstationInterface>
   {
   public:

      ///Workstation();
      //virtual ~WorkstationInterface() = 0;

      //virtual ~WorkstationInterface()=0;
      /**
       * Locks workstation.
       * @throws SystemException on fail.
       */
      virtual void workstation_lock()=0;
      /**
       * Logs off interactive user.
       * @throws SystemException on fail.
       * @remark caller must be run on interactive session.
       */
      virtual void workstation_logOff() = 0;
   };


   /**
    * Wrapper on WinAPI workstation functions.
    */
   class CLASS_DECL_SUBSYSTEM Workstation :
      virtual public ::subsystem::composite<WorkstationInterface >
   {
   public:

      Workstation();
      ~Workstation() override;
      /**
       * Locks workstation.
       * @throws SystemException on fail.
       */
      void workstation_lock() override;
      /**
       * Logs off interactive user.
       * @throws SystemException on fail.
       * @remark caller must be run on interactive session.
       */
      void workstation_logOff() override;
   };
} // namespace  subsystem