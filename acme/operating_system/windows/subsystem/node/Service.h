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
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once


//#include "remoting/remoting_common/util/winhdr.h"
#include "acme/subsystem/node/Service.h"
#include "acme/operating_system/windows/subsystem/_common_header.h"

//////#include "remoting/remoting_common/util/::string.h"
//#include "acme/subsystem/Exception.h"
//#include "remoting/remoting_common/thread/Thread.h"

namespace windows
{
   namespace subsystem
   {
      /**
       * Win32 service class (abstract).
       * @usage create service subclass, instanize subclass and call run() method.
       * @remark service is singleton (you can have only one service instance).
       * @author enikey.
       */
      class CLASS_DECL_ACME Service :
      virtual public ::subsystem::Service
      {
      public:
         /**
          * Creates new Service class instance.
          * @remark pointer to global service (singleton) saves here.
          * @param name name of service.
          */
         //Service(const ::scoped_string & scopedstrName);
         Service();

         /**
          * Deletes service instance.
          * @remark releases singleton pointer.
          */
         ~Service() override;

         void initialize_service(const scoped_string& scopedstrName) override;

         /**
          * Starts service execution.
          */
         void run() override;

      //protected:
         /**
          * Called from service control manager when service needs to start.
          */
         void onStart() override;
         /**
          * Service main.
          */
         void main() override;
         /**
          * Called from service control manager when service needs to stop/
          */
         void onStop()  override;

         /**
          * Win32 API service main function.
          * @see MSDN for details.
          */
         static void WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv);
         /**
          * Win32 API service control handler.
          * @see MSDN for details.
          */
         static void WINAPI ServiceControlHandler(DWORD dwCtrlCode);

      //protected:
         /**
          * @fixme add comment to it.
          */
         bool reportStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode,
                           DWORD dwWaitHint);

      //protected:
         /**
          * Service name for ServiceControlManager.
          */
         ::string m_name;

         /**
          * Current service status.
          */
         SERVICE_STATUS m_status;
         /**
          * Service handle.
          */
         SERVICE_STATUS_HANDLE m_statusHandle;

         /**
          * Flag determinates if service is terminating.
          */
         volatile bool m_isTerminating;

         /**
          * Service (global instance).
          */
         static Service *g_service;
      };
   } // namespace subsystem
} // namespace windows