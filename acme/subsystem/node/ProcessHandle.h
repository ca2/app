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


//#include "acme/include/_types.h"
#include "acme/subsystem/_common_header.h"


namespace subsystem
{
   // This class is a mere envelop for process handle that will automatically
   // closed at destructor calling.
   class CLASS_DECL_ACME ProcessHandleInterface :
   virtual public ::subsystem::particle_interface

   {
   public:
      //ProcessHandle();
      virtual ~ProcessHandleInterface() =0 ;

      // @throws ::remoting::Exception on an error.
      virtual void openProcess(unsigned int dwDesiredAccess,
                       bool bInheritHandle,
                       ::process_identifier processidentifier) = 0;


      virtual ::pointer < ::subsystem::SecurityIdentifier >getProcessOwner() =0;
      // Returns the handle of the openned process by openProcess() function.
      // If openProcess() function has not been called before then getHandle()
      // will return zero.
      //HANDLE getHandle() const;

      // Returns process module path. Call the openProcess() function before.
      // @throws ::remoting::Exception on an error.
      virtual ::string getProcessModulePath() = 0;



      //private:
      //HANDLE m_hProcess;
   };


   // This class is a mere envelop for process handle that will automatically
   // closed at destructor calling.
   class CLASS_DECL_ACME ProcessHandle :
   virtual public ::subsystem::composite<ProcessHandleInterface>

   {
   public:
      ProcessHandle();
      ~ProcessHandle() override;

      // @throws ::remoting::Exception on an error.
      void openProcess(unsigned int dwDesiredAccess,
                       bool bInheritHandle,
                       ::process_identifier processidentifier) override;

      // Returns the handle of the openned process by openProcess() function.
      // If openProcess() function has not been called before then getHandle()
      // will return zero.
//         HANDLE getHandle() const;

      /**
* Returns SID of process owner.
* @param processHandle handle of process.
* @return SID of owner of specified process.
* @throws SystemException if operation failed.
* @fixme stub (returns invalid SID).
*/
      ::pointer < ::subsystem::SecurityIdentifier > getProcessOwner() override;


      // Returns process module path. Call the openProcess() function before.
      // @throws ::remoting::Exception on an error.
      ::string getProcessModulePath() override;

      //private:
      //HANDLE m_hProcess;
   };
} //namespace subsystem
