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
#include "framework.h"
#include "acme/operating_system/windows/subsystem/_common_header.h"
#include "ServiceControlManagerClient.h"

//#include "remoting/remoting_common/thread/Thread.h"

namespace windows
{
   namespace  subsystem
   {
      //}
      //
      // ServiceControlManagerClientException::ServiceControlManagerClientException(int scmErrCode)
      // : SystemException("[::remoting::Exception description is not avaliable]")
      // {
      //   switch (scmErrCode) {
      //   case ERROR_ALREADY_STOPPED:
      //   case ERROR_STOP_TIMEOUT:
      //   case ERROR_ALREADY_RUNNING:
      //   case ERROR_START_TIMEOUT:
      //     break;
      //   default:
      //     _ASSERT(FALSE);
      //   };
      //
      //   m_scmErrCode = scmErrCode;
      // }
      //
      // int ServiceControlManagerClientException::getServiceControlManagerErrorCode() const
      // {
      //   return m_scmErrCode;
      // }

      ServiceControlManagerClient::ServiceControlManagerClient()
      {
         m_managerHandle = nullptr;
      }



      ServiceControlManagerClient::~ServiceControlManagerClient()
      {
         if (m_managerHandle != NULL) {
            CloseServiceHandle(m_managerHandle);
         }
      }


      void ServiceControlManagerClient::initialize_service_control_manager_client(unsigned int uDesiredAccess)
      {

         if (uDesiredAccess == 0)
         {

            uDesiredAccess = SC_MANAGER_ALL_ACCESS;

         }

         m_managerHandle = OpenSCManager(NULL, NULL, uDesiredAccess);

         if (m_managerHandle == NULL) {
            throw ::subsystem::SystemException();
         }
      }


      void ServiceControlManagerClient::installService(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrNameToDisplay,
                                     const ::scoped_string & scopedstrBinPath, const ::scoped_string & scopedstrDependencies)
      {
         SC_HANDLE serviceHandle = CreateService(
           m_managerHandle,              // ServiceControlManageranager database
           ::wstring(scopedstrName),                         // name of service
           ::wstring(scopedstrNameToDisplay),               // name to display
           SERVICE_ALL_ACCESS,           // desired access
           SERVICE_WIN32_OWN_PROCESS,
           // service type
           SERVICE_AUTO_START,           // start type
           SERVICE_ERROR_NORMAL,         // error control type
           ::wstring(scopedstrBinPath),                      // service's binary
           NULL,                         // no load ordering group
           NULL,                         // no tag identifier
           ::wstring(scopedstrDependencies),                 // dependencies
           NULL,                         // LocalSystem account
           NULL);                        // no password

         if (serviceHandle == NULL) {
            throw ::subsystem::SystemException();
         }

         // Make the service action to restart on a failure.
         SC_ACTION scAction;
         scAction.Type = SC_ACTION_RESTART; // action on failure
         scAction.Delay = 5000; // Delay before the action

         SERVICE_FAILURE_ACTIONS failureAction;
         failureAction.dwResetPeriod = 0;
         failureAction.lpRebootMsg = 0;
         failureAction.lpCommand = 0;
         failureAction.cActions = 1;
         failureAction.lpsaActions = &scAction;

         ChangeServiceConfig2(serviceHandle, SERVICE_CONFIG_FAILURE_ACTIONS,
                              &failureAction);

         CloseServiceHandle(serviceHandle);
      }

      void ServiceControlManagerClient::removeService(const ::scoped_string & scopedstrName)
      {
         try { stopService(scopedstrName); } catch (...) { }

         SC_HANDLE serviceHandle = OpenService(m_managerHandle, ::wstring(scopedstrName), SERVICE_ALL_ACCESS);

         if (serviceHandle == NULL) {
            throw ::subsystem::SystemException();
         }

         if (!DeleteService(serviceHandle)) {
            CloseServiceHandle(serviceHandle);
            throw ::subsystem::SystemException();
         }

         CloseServiceHandle(serviceHandle);

         // Wait until service entry will be removed.

         int triesCount = 0;
         while (true) {
            SC_HANDLE service = OpenService(m_managerHandle, ::wstring(scopedstrName), SERVICE_ALL_ACCESS);
            if (service == 0) {
               break;
            } else {
               CloseServiceHandle(service);
               preempt(1_s);
               // FIXME: Magic number.
               if (triesCount++ > 10) {
                  throw ::subsystem::SystemException(1070);
               }
            }
         }
      }

      void ServiceControlManagerClient::startService(const ::scoped_string & scopedstrName, bool waitCompletion)
      {
         // FIXME: Wrap SC_HANDLE into a class with a call to CloseServiceHandle()
         //        in the destructor.
         SC_HANDLE serviceHandle = OpenService(m_managerHandle, ::wstring(scopedstrName), SERVICE_START | SERVICE_QUERY_STATUS);
         if (serviceHandle == NULL) {
            throw ::subsystem::SystemException();
         }

         try {
            DWORD state = getServiceState(serviceHandle);
            if (state == SERVICE_RUNNING || state == SERVICE_START_PENDING) {
               throw ::subsystem::ServiceControlManagerClientException(::subsystem::ServiceControlManagerClientException::ERROR_ALREADY_RUNNING);
            }
            if (StartService(serviceHandle, 0, 0) == FALSE) {
               throw ::subsystem::SystemException();
            }

            if (waitCompletion) {
               int numChecks = 10;
               int msDelayBetweenChecks = 1000;

               while ((state = getServiceState(serviceHandle)) != SERVICE_RUNNING) {
                  if (--numChecks <= 0) {
                     break;
                  }
                  Sleep(msDelayBetweenChecks);
               }
               if (state != SERVICE_RUNNING) {
                  throw ::subsystem::ServiceControlManagerClientException(::subsystem::ServiceControlManagerClientException::ERROR_START_TIMEOUT);
               }
            }
         } catch(...) {
            CloseServiceHandle(serviceHandle);
            throw;
         }

         CloseServiceHandle(serviceHandle);
      }

      void ServiceControlManagerClient::stopService(const ::scoped_string & scopedstrName, bool waitCompletion)
      {
         SC_HANDLE serviceHandle = OpenService(m_managerHandle, ::wstring(scopedstrName), SERVICE_STOP | SERVICE_QUERY_STATUS);
         if (serviceHandle == NULL) {
            throw ::subsystem::SystemException();
         }

         try {
            DWORD state = getServiceState(serviceHandle);
            if (state == SERVICE_STOPPED || state == SERVICE_STOP_PENDING) {
               throw ::subsystem::ServiceControlManagerClientException(::subsystem::ServiceControlManagerClientException::ERROR_ALREADY_STOPPED);
            }
            SERVICE_STATUS status;
            if (ControlService(serviceHandle, SERVICE_CONTROL_STOP, &status) == FALSE) {
               throw ::subsystem::SystemException();
            }

            if (waitCompletion) {
               int numChecks = 10;
               int msDelayBetweenChecks = 1000;

               while ((state = getServiceState(serviceHandle)) != SERVICE_STOPPED) {
                  if (--numChecks <= 0) {
                     break;
                  }
                  Sleep(msDelayBetweenChecks);
               }
               if (state != SERVICE_STOPPED) {
                  throw ::subsystem::ServiceControlManagerClientException(::subsystem::ServiceControlManagerClientException::ERROR_STOP_TIMEOUT);
               }
            }
         } catch(...) {
            CloseServiceHandle(serviceHandle);
            throw;
         }

         CloseServiceHandle(serviceHandle);
      }

      DWORD ServiceControlManagerClient::getServiceState(SC_HANDLE hService) const
      {
         DWORD bytesNeeded;
         SERVICE_STATUS_PROCESS status;

         if (!QueryServiceStatusEx(hService, SC_STATUS_PROCESS_INFO,
                                   (LPBYTE)&status, sizeof(status), &bytesNeeded)) {
            throw ::subsystem::SystemException();
                                   }

         return status.dwCurrentState;
      }
   } // namespace subsystem
}// namespace windows