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


#include "acme/subsystem/thread/Thread.h"
//#include "win-system/WindowsEvent.h"

namespace subsystem
{
   class CLASS_DECL_ACME PipeImpersonatedThread :
   public Thread
   {
   public:
      //PipeImpersonatedThread(HANDLE pipeHandle);
      PipeImpersonatedThread();
      ~PipeImpersonatedThread() override;


      virtual void initialize_pipe_impersonated_thread(FileInterface * pfilePipe) = 0;

      virtual void waitUntilImpersonated() = 0;
      virtual bool getImpersonationSuccess() = 0;
      virtual ::string getFaultReason() = 0;

   //private:
      virtual void execute() = 0;
      virtual void onTerminate() = 0;

      // HANDLE m_pipeHandle;
      // bool m_success;
      // ::string m_faultReason;
      // WindowsEvent m_impersonationReadyEvent;
      // WindowsEvent m_threadSleeper;
   };

   // class CLASS_DECL_ACME PipeImpersonatedThread :
   // virtual public ::subsystem::composite < PipeImpersonatedThreadInterface>
   // {
   // public:
   //    PipeImpersonatedThread(FileInterface * pfilePipe);
   //    PipeImpersonatedThread();
   //     ~PipeImpersonatedThread() override;
   //
   //    void initialize_pipe_impersonated_thread(FileInterface * pfilePipe) override;
   //
   //    void waitUntilImpersonated() override;
   //    bool getImpersonationSuccess() override;
   //    ::string getFaultReason() override;
   //
   // //private:
   //    void execute() override;
   //    void onTerminate() override;
   //
   //    // HANDLE m_pipeHandle;
   //    // bool m_success;
   //    // ::string m_faultReason;
   //    // WindowsEvent m_impersonationReadyEvent;
   //    // WindowsEvent m_threadSleeper;
   // };
   //
   //// __PIPEIMPERSONATEDTHREAD_H__
} // namespace subsystem

